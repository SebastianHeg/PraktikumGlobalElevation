#ifndef READ_FILE_HPP
#define READ_FILE_HPP

#include "Coordinate.hpp"

#include <gdal_priv.h>
#include <cpl_conv.h>


namespace ElevationData2D {

class ReadFile
{
public:
	ReadFile();
	~ReadFile();

	struct Options
	{
		String path;			///< the path of saved data with file name
		int* rasterData;		///< array with read elevation data
		int numberOfElements;   ///< the number of previous read elements, serves to
								///< control to fill rasterData with pointer arithmetic
		int offsetXTopCorner;   ///< most left pixel which must be read first in this file
		int offsetYTopCorner;   ///< most upper pixel which must be read first in this file
								///< if both offsetXTopCorner and offsetYTopCorner are equal
								///< to 0, the picture will be read from the beginning
		int imgSizeX;			///< width of data
		int imgSizeY;			///< height of data
		int lat;				///< down rounded latitude of pixel which is read. Serves to 
								///< check is interpolation neccessary
	};

public:
	/// reads a tiff file and writes it to an array. With a longitude less than 50 and greater than -51 
	/// all values are copied into the array. For all other images, a linear interpolation over the 
	/// neighboring pixels is performed and the mean value is formed. This is stored twice in the array.
	void getData(Options& opt);	
	char** getMetadata();

private:
	/// A dataset from GDAL which contains various information.
	/// On the one hand, a raster band in which the height data are located
	GDALDataset* dataset;
	Vector<Coordinate> rasterGrid;
	float nextValue = 0;

	/// Linear interpolation of given image. Saves the results twice in the array
	void linearInterpolation(GDALRasterBand* band, Options& opt);
	//String fileName(const ElevationData2D::Coordinate& c);
};

} // namespace ElevationData2D

#endif
