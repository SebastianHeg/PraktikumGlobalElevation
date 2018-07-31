#ifndef ELEVATION_DATA_HPP
#define ELEVATION_DATA_HPP

#if WINDOWS
#include <windows.h>
#elif LINUX
#include <sys/types.h>
#include <dirent.h>
#endif

#include "Coordinate.hpp"

namespace ElevationData2D {

class ElevationData
{
public:

	/// creates ElevationData instance with upper-left corner c1 and 
	/// down-right corner c2.
	/// creates and fills the array with all elevation data
	ElevationData(const String& path, const Coordinate& c1, const Coordinate& c2);
	ElevationData(const ElevationData& eData) = delete;
	~ElevationData();

public:
	/// returns the vectors with coordinates which are the intersection
	/// points of grid axes and intersection points of selected area's
	/// edges with grid axes apart the points on the right edge
	Vector<Coordinate> gridVector() const;

	/// returns the number of Pixels in x axes direction
	/// or the width of the data
	int sizeX() const;

	/// returns the number of Pixels in y axes direction
	/// or the height of the data
	int sizeY() const;

	/// returns the witdth of data, which is built with coord
	/// and next gridVector points on the right side and down
	int sizeX(const Coordinate& coord) const;

	/// returns the height of data, which is built with coord
	/// and next gridVector points on the right side and down
	int sizeY(const Coordinate& coord) const;

	/// returns the vector of points from VectorGrid, that have 
	/// the same latitude as c1
	Vector<Coordinate> firstLeftColumn() const;

	/// returns the vector of points from VectorGrid, that have 
	/// the same longitude as c1
	Vector<Coordinate> firstUpRow() const;

	/// return (i,j) value of data
	float operator()(int i, int j) const;

private:
	Coordinate c1;   ///< upper-left corner of selected area
	Coordinate c2;   ///< down-right corner of selected aea

	float* rasterData;  ///< elevation data with upper-left corner c1 and down-right corner c2

	Vector<String> fileNames;  ///< includes all file names that have a pixels from data
	int numOfPixels;

private:
	/// releases the allocated memory on heap
	void deallocate();

	/// fills the raster data with elevetion data, that was read from .tif files
	/// note: if there are many .tif files include the selected area, the files
	/// will be read line by line along the same latitude
	void createElevationArray(const String& path);
	String resourcepath() const;

	// the number of pixels of hole elevation data
	int rasterDataSize() const;

	/// returns a pair of latitude and longitude constructed from name of file
	Pair<int, int> getLatLon(const String& name) const;
};


} // namespace ElevationData2D

#endif
