#include <iostream>
#include <fstream>

#include "StdAfx.hpp"
#include "ElevationData.hpp"


/// writes the elevation data in external file filename
void writeFile(const ElevationData2D::ElevationData& eData, const std::string& filename) {
	
	std::ofstream file;
	file.open(filename);

	for(int i=0;i<eData.sizeY();++i)
		for(int j=0;j<eData.sizeX();++j)
			file<<eData(i,j)<<"\n";

	file.close();
}


