// Copyright 2014-2015 Isis Innovation Limited and the authors of InfiniTAM

#include "UIEngine.h"

#include <string.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef FREEGLUT
#include <GL/freeglut.h>
#include <sstream>

#else
#if (!defined USING_CMAKE) && (defined _MSC_VER)
#pragma comment(lib, "glut64")
#endif
#endif

#include "../Utils/FileUtils.h"


//==================Mapper
#include "include/stereoimage.h"


using namespace InfiniTAM::Engine;
UIEngine* UIEngine::instance;

static void safe_glutBitmapString(void *font, const char *str)
{
	size_t len = strlen(str);
	for (size_t x = 0; x < len; ++x) {
		glutBitmapCharacter(font, str[x]);
	}
}

void UIEngine::glutDisplayFunction()
{
	UIEngine *uiEngine = UIEngine::Instance();

	// get updated images from processing thread
	uiEngine->mainEngine->GetImage(uiEngine->outImage[0], nullptr, uiEngine->outImageType[0],
								   &uiEngine->freeviewPose, &uiEngine->freeviewIntrinsics);

    for (int w = 1; w < NUM_WIN; w++) {
		uiEngine->mainEngine->GetImage(uiEngine->outImage[w], nullptr, uiEngine->outImageType[w]);
	}

	// do the actual drawing
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);

	ITMUChar4Image** showImgs = uiEngine->outImage;
	Vector4f *winReg = uiEngine->winReg;
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	{
		glLoadIdentity();
		glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		{
			glEnable(GL_TEXTURE_2D);
			for (int w = 0; w < NUM_WIN; w++)	{ // Draw each sub window
				if (uiEngine->outImageType[w] == ITMMainEngine::InfiniTAM_IMAGE_UNKNOWN) continue;
				glBindTexture(GL_TEXTURE_2D, uiEngine->textureId[w]);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, showImgs[w]->noDims.x, showImgs[w]->noDims.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, showImgs[w]->GetData(MEMORYDEVICE_CPU));
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glBegin(GL_QUADS); {
                    glTexCoord2f(0, 1); glVertex2f(winReg[w][0], winReg[w][1]); // glVertex2f(0, 0);
                    glTexCoord2f(1, 1); glVertex2f(winReg[w][2], winReg[w][1]); // glVertex2f(1, 0);
					glTexCoord2f(1, 0); glVertex2f(winReg[w][2], winReg[w][3]); // glVertex2f(1, 1);
					glTexCoord2f(0, 0); glVertex2f(winReg[w][0], winReg[w][3]); // glVertex2f(0, 1);
				}
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
		}
		glPopMatrix();
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glColor3f(1.0f, 0.0f, 0.0f); glRasterPos2f(0.85f, -0.962f);

	char str[200]; sprintf(str, "%04.2lf", uiEngine->processedTime);
	safe_glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const char*)str);

	glRasterPos2f(-0.95f, -0.95f);
	if (uiEngine->freeviewActive)
	{
		sprintf(str, "n - next frame \t b - all frames \t e/esc - exit \t f - follow camera \t"
				" c - colours (currently %s) \t t - turn fusion %s", uiEngine->colourModes[uiEngine->currentColourMode].name, uiEngine->intergrationActive ? "off" : "on");
	}
	else
	{
		sprintf(str, "n - next frame \t b - all frames \t e/esc - exit \t f - free viewpoint \t"
				" t - turn fusion %s  \t w - write to disk", uiEngine->intergrationActive ? "off" : "on");
	}
	safe_glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const char*)str);

	glutSwapBuffers();
	uiEngine->needsRefresh = false;
}

void UIEngine::glutIdleFunction()
{
    // waiting for the Mapper to compute the depth 
    while( StereoImage::infinitamWaitDisparity ) usleep(1);
    StereoImage::infinitamWaitDisparity = true;
    
	UIEngine *uiEngine = UIEngine::Instance();
    
    uiEngine->ProcessFrame(); 
    uiEngine->processedFrameNo++;
    glutPostRedisplay();

}

void UIEngine::glutKeyUpFunction(unsigned char key, int x, int y)
{
	UIEngine *uiEngine = UIEngine::Instance();

	switch (key)
	{
	case 'n':
		printf("\nprocessing one frame (%d)...\n", uiEngine->currentFrameNo);
		uiEngine->mainLoopAction = UIEngine::PROCESS_FRAME;
		break;
	case 'b':
		printf("\nprocessing input source ...\n");
		uiEngine->mainLoopAction = UIEngine::PROCESS_VIDEO;
		break;
	case 's':
		if (uiEngine->isRecording)
		{
			printf("stopped recoding disk ...\n");
			uiEngine->isRecording = false;
		}
		else
		{
			printf("started recoding disk ...\n");
			uiEngine->currentFrameNo = 0;
			uiEngine->isRecording = true;
		}
		break;
  case 'q':
	case 'e':
	case 27: // esc key
		printf("exiting ...\n");
		uiEngine->mainLoopAction = UIEngine::EXIT;
		break;
	case 'f':
		if (uiEngine->freeviewActive)
		{
			uiEngine->outImageType[0] = ITMMainEngine::InfiniTAM_IMAGE_SCENERAYCAST;
			uiEngine->outImageType[1] = ITMMainEngine::InfiniTAM_IMAGE_ORIGINAL_DEPTH;

			uiEngine->freeviewActive = false;
		}
		else
		{
			uiEngine->outImageType[0] = ITMMainEngine::InfiniTAM_IMAGE_FREECAMERA_SHADED;
			uiEngine->outImageType[1] = ITMMainEngine::InfiniTAM_IMAGE_SCENERAYCAST;

			uiEngine->freeviewPose.SetFrom(uiEngine->mainEngine->GetTrackingState()->pose_d);
			if (uiEngine->mainEngine->GetView() != NULL) {
				uiEngine->freeviewIntrinsics = uiEngine->mainEngine->GetView()->calib->intrinsics_d;
				uiEngine->outImage[0]->ChangeDims(uiEngine->mainEngine->GetView()->depth->noDims);
			}
			uiEngine->freeviewActive = true;
		}
		uiEngine->needsRefresh = true;
		break;
	case 'c':
		uiEngine->currentColourMode++; if ((unsigned)uiEngine->currentColourMode >= uiEngine->colourModes.size()) uiEngine->currentColourMode = 0;
		uiEngine->needsRefresh = true;
		break;
	case 't':
		uiEngine->intergrationActive = !uiEngine->intergrationActive;
		if (uiEngine->intergrationActive) uiEngine->mainEngine->turnOnIntegration();
		else uiEngine->mainEngine->turnOffIntegration();
		break;
	case 'w':
		printf("saving mesh to disk ...");
		uiEngine->SaveSceneToMesh("mesh.stl");
		printf(" done\n");
		break;
	default:
		break;
	}

	if (uiEngine->freeviewActive) {
		uiEngine->outImageType[0] = uiEngine->colourModes[uiEngine->currentColourMode].type;
	}
}

void UIEngine::glutMouseButtonFunction(int button, int state, int x, int y)
{
	UIEngine *uiEngine = UIEngine::Instance();

	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON: uiEngine->mouseState = 1; break;
		case GLUT_MIDDLE_BUTTON: uiEngine->mouseState = 3; break;
		case GLUT_RIGHT_BUTTON: uiEngine->mouseState = 2; break;
		default: break;
		}
		uiEngine->mouseLastClick.x = x;
		uiEngine->mouseLastClick.y = y;

#ifdef __linux__
		// Linux typically does NOT support explicit handlers for the scroll wheel, so
		// we do it here instead.
		// Wheel reports as button 3(scroll up) and button 4(scroll down).
		// We only want to do this on 'GLUT_DOWN', since every scroll event actually
		// triggers both an UP and a DOWN callback, but we don't need both.
		if ((button == 3) || (button == 4))
		{
			int buttonDir = (button == 3) ? 1 : -1;
			UIEngine::glutMouseWheelFunction(button, buttonDir, x, y);
		}
#endif
	}
	else if (state == GLUT_UP) uiEngine->mouseState = 0;
}

static inline Matrix3f createRotation(const Vector3f & _axis, float angle)
{
	Vector3f axis = normalize(_axis);
	float si = sinf(angle);
	float co = cosf(angle);

	Matrix3f ret;
	ret.setIdentity();

	ret *= co;
	for (int r = 0; r < 3; ++r) for (int c = 0; c < 3; ++c) ret.at(c, r) += (1.0f - co) * axis[c] * axis[r];

	Matrix3f skewmat;
	skewmat.setZeros();
	skewmat.at(1, 0) = -axis.z;
	skewmat.at(0, 1) = axis.z;
	skewmat.at(2, 0) = axis.y;
	skewmat.at(0, 2) = -axis.y;
	skewmat.at(2, 1) = axis.x;
	skewmat.at(1, 2) = -axis.x;
	skewmat *= si;
	ret += skewmat;

	return ret;
}

void UIEngine::glutMouseMoveFunction(int x, int y)
{
	UIEngine *uiEngine = UIEngine::Instance();

	if (!uiEngine->freeviewActive) return;

	Vector2i movement;
    movement.x = 4*(x - uiEngine->mouseLastClick.x);
    movement.y = 4*(y - uiEngine->mouseLastClick.y);
	uiEngine->mouseLastClick.x = x;
	uiEngine->mouseLastClick.y = y;

	if ((movement.x == 0) && (movement.y == 0)) return;

    static const float scale_rotation = 0.0025f;
    static const float scale_translation = 0.05f;

	switch (uiEngine->mouseState) {
	case 1:
	{
		// left button: rotation
		Vector3f axis((float)-movement.y, (float)-movement.x, 0.0f);
		float angle = scale_rotation * sqrt((float)(movement.x * movement.x + movement.y*movement.y));
		Matrix3f rot = createRotation(axis, angle);
		uiEngine->freeviewPose.SetRT(rot * uiEngine->freeviewPose.GetR(), rot * uiEngine->freeviewPose.GetT());
		uiEngine->freeviewPose.Coerce();
		uiEngine->needsRefresh = true;
		break;
	}
	case 2:
	{
		// right button: translation in x and y direction
		uiEngine->freeviewPose.SetT(uiEngine->freeviewPose.GetT() + scale_translation * Vector3f((float)movement.x, (float)movement.y, 0.0f));
		uiEngine->needsRefresh = true;
		break;
	}
	case 3:
	{
		// middle button: translation along z axis
		uiEngine->freeviewPose.SetT(uiEngine->freeviewPose.GetT() + scale_translation * Vector3f(0.0f, 0.0f, (float)movement.y));
		uiEngine->needsRefresh = true;
		break;
	}

	default:
		break;
	}
}

// Note: this callback does NOT get called on Linux!
void UIEngine::glutMouseWheelFunction(int button, int dir, int x, int y)
{
	UIEngine *uiEngine = UIEngine::Instance();

    static const float scale_translation = 1.5f;

	uiEngine->freeviewPose.SetT(uiEngine->freeviewPose.GetT() + scale_translation * Vector3f(0.0f, 0.0f, (dir > 0) ? -1.0f : 1.0f));
	uiEngine->needsRefresh = true;
}

void UIEngine::Initialise(ImageSourceEngine *imageSource, ITMMainEngine *mainEngine,ITMLibSettings::DeviceType deviceType)
{
	this->freeviewActive = false;
	this->intergrationActive = true;
	this->currentColourMode = 0;
	this->colourModes.push_back(UIColourMode("shaded greyscale", ITMMainEngine::InfiniTAM_IMAGE_FREECAMERA_SHADED));
	if (ITMVoxel::hasColorInformation) this->colourModes.push_back(UIColourMode("integrated colours", ITMMainEngine::InfiniTAM_IMAGE_FREECAMERA_COLOUR_FROM_VOLUME));
	this->colourModes.push_back(UIColourMode("surface normals", ITMMainEngine::InfiniTAM_IMAGE_FREECAMERA_COLOUR_FROM_NORMAL));

	this->imageSource = imageSource;
	this->mainEngine = mainEngine;

    int textHeight = 40; // Height of text area
    int blackHeight = 20;
    winSize.x = (imageSource->getDepthImageSize().x) + blackHeight;
    winSize.y = (int)(1.75 * imageSource->getDepthImageSize().y + textHeight + blackHeight);

    float h1 = textHeight / (float)winSize.y;
    float h2 = 0.5*(winSize.y-textHeight-blackHeight) / 1.5 / (float)winSize.y + h1;
    float h3 = h2 + float(blackHeight)/winSize.y;
    float l1 = ((winSize.x-blackHeight)/2.0) / float(winSize.x);
    float l2 = float(blackHeight)/winSize.x+l1;

    winReg[0] = Vector4f(0, h3, 1, 1);    // Main render
    winReg[1] = Vector4f(0, h1, l1, h2);    // Side sub window 0
    winReg[2] = Vector4f(l2, h1, 1, h2);   // Side sub window 1

    winReg[3] = Vector4f(0.75, h2, 1, 1);  // Side sub window 2
    winReg[4] = Vector4f(0.75, h1, 1, h2); // Side sub window 3

//                    (winReg[w][0], winReg[w][1]); // zuo xia
//                    (winReg[w][2], winReg[w][1]); // you xia
//                    (winReg[w][2], winReg[w][3]); // you shang
//                    (winReg[w][0], winReg[w][3]); // zuo shang

	this->isRecording = false;
	this->currentFrameNo = 0;

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(winSize.x, winSize.y);
	glutCreateWindow("Mapper-InfiniTAM");
	glGenTextures(NUM_WIN, textureId);

	glutDisplayFunc(UIEngine::glutDisplayFunction);
	glutKeyboardUpFunc(UIEngine::glutKeyUpFunction);
	glutMouseFunc(UIEngine::glutMouseButtonFunction);
	glutMotionFunc(UIEngine::glutMouseMoveFunction);
	glutIdleFunc(UIEngine::glutIdleFunction);

#ifdef FREEGLUT
	glutMouseWheelFunc(UIEngine::glutMouseWheelFunction);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, 1);
#endif

	bool allocateGPU = false;
	if (deviceType == ITMLibSettings::DEVICE_CUDA) allocateGPU = true;

	for (int w = 0; w < NUM_WIN; w++)
		outImage[w] = new ITMUChar4Image(imageSource->getDepthImageSize(), true, allocateGPU);

	inputRGBImage = new ITMUChar4Image(imageSource->getRGBImageSize(), true, allocateGPU);
	inputRawDepthImage = new ITMShortImage(imageSource->getDepthImageSize(), true, allocateGPU);
	inputIMUMeasurement = new ITMIMUMeasurement();

	saveImage = new ITMUChar4Image(imageSource->getDepthImageSize(), true, false);

	outImageType[0] = ITMMainEngine::InfiniTAM_IMAGE_SCENERAYCAST;
	outImageType[1] = ITMMainEngine::InfiniTAM_IMAGE_ORIGINAL_DEPTH;
	outImageType[2] = ITMMainEngine::InfiniTAM_IMAGE_ORIGINAL_RGB;
	if (inputRGBImage->noDims == Vector2i(0,0)) {
		// This seems to be used for depth-only input.
		outImageType[2] = ITMMainEngine::InfiniTAM_IMAGE_UNKNOWN;
	}
	// Placeholders for when we want to display more info.
	outImageType[3] = ITMMainEngine::InfiniTAM_IMAGE_UNKNOWN;
	outImageType[4] = ITMMainEngine::InfiniTAM_IMAGE_UNKNOWN;

	mainLoopAction = PROCESS_PAUSED;
	mouseState = 0;
	needsRefresh = false;
	processedFrameNo = 0;
	processedTime = 0.0f;

#ifndef COMPILE_WITHOUT_CUDA
    ITMSafeCall(cudaThreadSynchronize());
#endif

	sdkCreateTimer(&timer_instant);
	sdkCreateTimer(&timer_average);

	sdkResetTimer(&timer_average);

    printf("Initialised.\n");
}

void UIEngine::SaveScreenshot(const char *filename) const
{
	ITMUChar4Image screenshot(getWindowSize(), true, false);
	GetScreenshot(&screenshot);
	SaveImageToFile(&screenshot, filename, true);
}

void UIEngine::SaveSceneToMesh(const char *filename) const
{
	mainEngine->SaveSceneToMesh(filename);
}

void UIEngine::GetScreenshot(ITMUChar4Image *dest) const
{
	glReadPixels(0, 0, dest->noDims.x, dest->noDims.y, GL_RGBA, GL_UNSIGNED_BYTE, dest->GetData(MEMORYDEVICE_CPU));
}

void UIEngine::ProcessFrame()
{
//	if (!imageSource->hasMoreImages()) return;
	imageSource->getImages(inputRGBImage, inputRawDepthImage);
    
	sdkResetTimer(&timer_instant);
	sdkStartTimer(&timer_instant); sdkStartTimer(&timer_average);

	//actual processing on the mailEngine
    mainEngine->ProcessFrame(inputRGBImage, inputRawDepthImage);

#ifndef COMPILE_WITHOUT_CUDA
	ITMSafeCall(cudaThreadSynchronize());
#endif
	sdkStopTimer(&timer_instant); sdkStopTimer(&timer_average);

	//processedTime = sdkGetTimerValue(&timer_instant);
	processedTime = sdkGetAverageTimerValue(&timer_average);

	currentFrameNo++;
}

void UIEngine::Run() { glutMainLoop(); }
void UIEngine::Shutdown()
{
	sdkDeleteTimer(&timer_instant);
	sdkDeleteTimer(&timer_average);

	for (int w = 0; w < NUM_WIN; w++)
		delete outImage[w];

	delete inputRGBImage;
	delete inputRawDepthImage;
	delete inputIMUMeasurement;

	delete saveImage;
	delete instance;
	instance = NULL;
}
