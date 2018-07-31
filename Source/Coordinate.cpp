#include "StdAfx.hpp"
#include "Coordinate.hpp"


namespace ElevationData2D {

Coordinate::Coordinate(float lat, float lon) : lat(lat), lon(lon)
{
	if(!validCoordinate())
		logWarning() << "Invalid coordinate!";
}

float Coordinate::getLat() const
{
	return lat;
}

float Coordinate::getLon() const
{
	return lon;
}

bool Coordinate::validCoordinate() const
{
	return ((lat >= -90 && lat <= 90) &&
			(lon >= -180 && lon <= 180));
}

void Coordinate::print() const
{
	std::cout << "( " << lat <<" , " << lon << " )" << std::endl;
}

bool Coordinate::operator==(const Coordinate& c) const
{
	return lat==c.lat && lon==c.lon;
}

//Coordinate::CoordMeta getMetadata()
//{
//}

} // namespace ElevationData2D
