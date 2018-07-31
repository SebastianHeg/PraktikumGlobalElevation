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
	ElevationData2D::ElevationData eData("/home/tatev/praktikum/GlobalElevation/Include/Resources/Test/", c1, c2);
	std::cout<<eData(98,111)<<std::endl;

	std::string filename="output.xlsx";
	writeFile(eData,filename);
	return 0;
}
