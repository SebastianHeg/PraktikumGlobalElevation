#ifndef COORDINATE_HPP
#define COORDINATE_HPP

namespace ElevationData2D {

class Coordinate
{
public:
	Coordinate() = default;

	/// creates an instance of class Coordinate with given coordinates
	/// and throws exception if latitude is out of interval [-90,90],
	/// longitude [-180,180]. Negative number for latitude corresponds
	/// to south pole, positive to north pole. Negative value of longitude 
	/// corresponds to coordinates on the west side of meridian, positive
	/// values to coordinates on the east side of meridian.
	Coordinate(float lat, float lon);

	~Coordinate() = default;

public:
	float getLat() const;
	float getLon() const;

	//returns true if lat is in interval [-90,90] and lon is in interval [-180,180]
	//otherwise returns false
	bool validCoordinate() const;

	void print() const;

	bool operator==(const Coordinate& c) const;

	

private:
	float lat;
	float lon;
};

} // namespace ElevationData2D

#endif
