#include "Coordinate.hpp"

#include <memory>
#include <cmath>


namespace ElevationData2D {
/// returns file's name in which this coordinate is contained
std::string fileName(const ElevationData2D::Coordinate& c)
{
	std::string name;
	std::string lat_string = std::to_string(int(std::abs(std::floor(c.getLat()))));

	if(lat_string.size() < 2)
		lat_string = "0" + lat_string;

	std::string lon_string = std::to_string(int(std::abs(std::floor(c.getLon()))));

	while(lon_string.size() < 3)
		lon_string = "0" + lon_string;

	if(c.getLat() >= 0)
		name.push_back('n');
	else
		name.push_back('s');

	name += lat_string;

	name.push_back('_');

	if(c.getLon() >= 0)
		name.push_back('e');
	else
		name.push_back('w');

	name += (lon_string + "_1arc_v3.tif");

	return name;

}


/// prints file name
void printFileName(std::string name)
{
	std::cout << name << std::endl;
}

/// returns a vector with photo's names, they contain the quadrat with upper_left c_1 corner
/// and down_right c_2 corner. File names will be ordered from left to right and from up to down. 
std::vector<std::string> filesSet(const ElevationData2D::Coordinate& c1, const ElevationData2D::Coordinate& c2)
{
	std::vector<std::string> set;
	ElevationData2D::Coordinate c;
	int lat_difference = int(c1.getLat()) - int(c2.getLat());
	int lon_difference = int(c2.getLon()) - int(c1.getLon());
	for(int i = 0; i <= lat_difference; ++i)
		for(int j = 0; j <= lon_difference; ++j)
		{
			c = ElevationData2D::Coordinate(c1.getLat() - i, c1.getLon() + j);
			set.push_back(fileName(c));
		}

	return set;
}

/// prints a set
void printFilesSet(const std::vector<std::string>& set)
{
	for(size_t i = 0; i < set.size(); ++i)
		printFileName(set[i]);
}


/// returns nXOff="The pixel offset to the top left corner of the 
/// region of the band to be accessed. This would be zero to start
/// from the left side." Thus the unnecessary left side will be cut.
int get_nXOff(const ElevationData2D::Coordinate& c)
{
	int up_left_lon = std::floor(c.getLon());
	int up_left_lat = std::floor(c.getLat());

	int nXOff;

	nXOff = std::round(std::abs(c.getLon() - up_left_lon) * 3600);



	return nXOff;
}


// returns nYOff="The line offset to the top left corner of the region
// of the band to be accessed. This would be zero to start from the top."
int get_nYOff(const ElevationData2D::Coordinate& c)
{
	int up_left_lat = std::ceil(c.getLat());
	int nYOff = std::round(std::abs(up_left_lat - c.getLat()) * 3600);

	return nYOff;
}

/// returns nXSize="The width of the region of the band to be accessed in pixels."
/// c1 upper-left corner, c2 down-riight corner

int get_nXSize(const ElevationData2D::Coordinate& c1, const ElevationData2D::Coordinate& c2)
{
	std::string s = fileName(c1);
	int up_left_lat = std::stoi(s.substr(1, 2));

	int nXSize;

	if(up_left_lat >= 50)
		nXSize = std::round(std::abs(c2.getLon() - c1.getLon()) * 1800) + 1;
	else
		nXSize = std::round(std::abs(c2.getLon() - c1.getLon()) * 3600) + 1;

	return nXSize;
}

/// returns nXSize="The height of the region of the band to be accessed in lines."

int get_nYSize(const ElevationData2D::Coordinate& c1, const ElevationData2D::Coordinate& c2)
{
	return std::round(std::abs(c1.getLat() - c2.getLat()) * 3600) + 1;
}

} // namespace ElevationData2D