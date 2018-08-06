#include "StdAfx.hpp"

#include "ReadFile.hpp"
#include "ElevationData.hpp"

#include "output.hpp"

int main(int argc, char* argv[])
{
	/// Heidelberg with area close to Königstuhl, Philosophenweg
	/// and Altstadt
	String path = "";
	ElevationData2D::Coordinate c1(49.43,8.66),c2(49.40,8.73);   
	ElevationData2D::ElevationData eData("path/", c1, c2);

	std::cout << "size = " << eData.sizeX() << " " << eData.sizeY() << std::endl;

	for(int j = 0; j < eData.sizeY(); j++)
	{
		for(int i = 0; i < eData.sizeX(); i++)
			std::cout << eData(i, j) << " ";
		std::cout << std::endl;
	}

	std::string filename="output.xlsx";
	writeFile(eData,filename);
	return 0;
}
