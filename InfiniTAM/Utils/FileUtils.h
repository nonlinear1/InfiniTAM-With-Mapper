// Copyright 2014-2015 Isis Innovation Limited and the authors of InfiniTAM

#pragma once

#include <stdio.h>
#include "ImageIOpfm.h"
#include "../ITMLib/Utils/ITMLibDefines.h"
#include "../Engine/ImageSourceEngine.h"

extern float focal_length_px;
extern float baseline_m;

void SaveImageToFile(const ITMUChar4Image* image, const char* fileName, bool flipVertical = false);
void SaveImageToFile(const ITMShortImage* image, const char* fileName);
void SaveImageToFile(const ITMFloatImage* image, const char* fileName);
bool ReadImageFromFile(ITMUChar4Image* image, const char* fileName);
bool ReadImageFromFile(ITMShortImage *image, const char *fileName);
void cvMatToShort(cv::Mat pfm_data, short *data);
void floatToShort(float *disparity, short *data);//exchange computed disparity to short* data 


template <typename T> void ReadFromBIN(T *data, int dataSize, const char *fileName)
{
	FILE *f = fopen(fileName, "rb");
	fread(data, dataSize * sizeof(T), 1, f);
	fclose(f);
}

template <typename T> void WriteToBIN(const T *data, int dataSize, const char *fileName)
{
	FILE *f = fopen(fileName, "wb");
	fwrite(data, dataSize * sizeof(T), 1, f);
	fclose(f);
}

