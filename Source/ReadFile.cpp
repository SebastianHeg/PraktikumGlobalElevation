#include "StdAfx.hpp"
#include "ReadFile.hpp"


namespace ElevationData2D {

ReadFile::ReadFile()
{
}

ReadFile::~ReadFile()
{
}

void ReadFile::getData(Options& opt)
{
	GDALAllRegister();

	dataset = (GDALDataset*)GDALOpen(opt.path.c_str(), GA_ReadOnly);
	if(dataset == NULL)
	{
		logWarning() << "Can not load dataset";
		return;
	}

	GDALRasterBand* band;
	int nBlockXSize, nBlockYSize;

	band = dataset->GetRasterBand(1);
	band->GetBlockSize(&nBlockXSize, &nBlockYSize);

	int nXSize = band->GetXSize();
	int nYSize = band->GetYSize();

	if(opt.lat < 50 && opt.lat > -51)
	{
		band->RasterIO(GF_Read, opt.offsetXTopCorner, opt.offsetYTopCorner, 
				opt.imgSizeX, opt.imgSizeY, opt.rasterData + opt.numberOfElements,
				opt.imgSizeX, opt.imgSizeY, GDT_Float32, 0, 0);	
	} else
	{
		linearInterpolation(band, opt);
	}
/// offsetBuffer index des Bildes in fileNames-Array

	GDALClose(dataset);
}

void ReadFile::linearInterpolation(GDALRasterBand* band, Options& opt)
{
	float* buffer = new float(IMAGE_SIZE_G * IMAGE_SIZE_S + 1);
	band->RasterIO(GF_Read, opt.offsetXTopCorner, opt.offsetYTopCorner,
				   opt.imgSizeX, opt.imgSizeY,
				   buffer,
				   opt.imgSizeX, opt.imgSizeY, GDT_Float32,
				   0, 0);

	uint i = 0;
	while(i < (IMAGE_SIZE_G * IMAGE_SIZE_S + 1))
	{
		float averageValue;
		if(buffer[i] == NULL && nextValue != 0.0f)
		{
			averageValue = (nextValue + buffer[i]) / 2.0f;
		} else
		{
			averageValue = (buffer[i] + buffer[i + 1]) / 2.0f;
			nextValue = buffer[i + 1];
		}

		opt.rasterData[opt.numberOfElements + i] = buffer[i];
		opt.rasterData[opt.numberOfElements + i + 1] = averageValue;
		i += 2;
	}
	delete[] buffer;
}


char** ReadFile::getMetadata()
{
	return dataset->GetMetadata();
}


} // namespace ElevationData2D
