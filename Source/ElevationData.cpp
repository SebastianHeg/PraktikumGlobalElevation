#include "StdAfx.hpp"
#include "ElevationData.hpp"
#include "ReadFile.hpp"
#include "FileContainer.hpp"

#include <regex>


namespace ElevationData2D {

	ElevationData::ElevationData(const String& path, const Coordinate& c1, const Coordinate& c2) : c1(c1), c2(c2)
	{
		Vector<String> files = filesSet(c1, c2);
		for (uint i = 0; i < files.size(); ++i)
			fileNames.push_back(files[i]);

		rasterData = new int[rasterDataSize()];
		createElevationArray(path);
	}

	ElevationData::~ElevationData()
	{
		deallocate();
	}


	void ElevationData::deallocate()
	{
		delete[] rasterData;
	}

	void ElevationData::createElevationArray(const String& path)
	{
		ReadFile readFile;
		ReadFile::Options opt;
		Vector<Coordinate> grid = gridVector();

		Vector<Coordinate> col = firstUpRow();
		Vector<Coordinate> row = firstLeftColumn();
		String resourcePath = path;

		opt.numberOfElements = 0;

		uint row_size=row.size();
		uint size_Y;
		uint col_size;

		for (uint i = 0; i < row_size - 2; ++i)
		{
			size_Y = sizeY(row[i]);
			for (uint k = 0; k < size_Y - 1; ++k)
			{
				col_size = col.size();
				for (uint j = 0; j < col_size; ++j)
				{
					String path(resourcePath + fileName(grid[(i+1)*col_size + j]));
					opt.path = path;
					opt.rasterData = rasterData;
					

					opt.offsetXTopCorner = get_nXOff(grid[i*col_size + j]);
					if(get_nYOff(grid[i*col_size + j]) != 0)
						opt.offsetYTopCorner = get_nYOff(grid[i*col_size + j]) - k;
					else
						opt.offsetYTopCorner = get_nYOff(grid[i*col_size + j]) + k;

					if (j == col.size() - 1)
						opt.imgSizeX = sizeX(grid[i*col_size + j]);
					else
						opt.imgSizeX = sizeX(grid[i*col_size + j]) - 1;

					opt.imgSizeY = 1;

					opt.lat = std::floor(grid[i * col_size + j].getLat());
					readFile.getData(opt);

					opt.numberOfElements += opt.imgSizeX;
				}
			}
		}

		int i = row.size() - 2;
		size_Y = sizeY(row[i]);
		for (uint k = 0; k < size_Y; ++k)
		{
			col_size = col.size();
			for (uint j = 0; j < col_size; ++j)
			{
				String path(resourcePath + fileName(grid[(i+1)*col_size + j]));
				opt.rasterData = rasterData;
				opt.path = path;

				opt.offsetXTopCorner = get_nXOff(grid[i*col_size + j]);
				if (get_nYOff(grid[i*col_size + j]) != 0)
					opt.offsetYTopCorner = get_nYOff(grid[i*col_size + j]) - k;
				else
					opt.offsetYTopCorner = get_nYOff(grid[i*col_size + j]) + k;

				if (j == col.size() - 1)
					opt.imgSizeX = sizeX(grid[i*col_size + j]);
				else
					opt.imgSizeX = sizeX(grid[i*col_size + j]) - 1;

				opt.imgSizeY = 1;

				opt.lat = std::floor(grid[i * col_size + j].getLat());

				readFile.getData(opt);

				opt.numberOfElements += opt.imgSizeX;
			}
		}

		wholeSizeX = sizeX();
	}

	Vector<Coordinate> ElevationData::gridVector() const
	{
		Vector<Coordinate> v;
		v.push_back(c1);
		int size_lon = std::floor(c2.getLon());
		int size_lat = std::floor(c2.getLat());
		int start_lat = std::floor(c1.getLat());
		int start_lon = std::floor(c1.getLon());
		float epsilon = std::numeric_limits<float>::epsilon();

		if (c2.getLon() - float(size_lon) < epsilon)
			size_lon = std::floor(c2.getLon())-1;

		if (c1.getLat() - float(start_lat) < epsilon)
			start_lat = std::floor(c1.getLat()) - 1;

		for (int i = start_lon; i < size_lon; ++i)
			v.push_back(Coordinate(c1.getLat(), float(i + 1)));

		for (int i = start_lat; i > size_lat; --i)
		{
			v.push_back(Coordinate(float(i), c1.getLon()));
			for (int j = start_lon ; j < size_lon; ++j)
				v.push_back(Coordinate(float(i), float(j+1)));
		}

		v.push_back(Coordinate(c2.getLat(),c1.getLon()));
		for (int i = start_lon; i < size_lon; ++i)
			v.push_back(Coordinate(c2.getLat(),float(i+1)));
		return v;
	}


	int ElevationData::rasterDataSize() const
	{
		return sizeX()*sizeY();
	}

	String ElevationData::resourcepath() const
	{
		std::cout << "Specify resourcepath. ";
		String RESOURCEPATH;
		std::cin >> RESOURCEPATH;
		return RESOURCEPATH;
	}

	Pair<int, int> ElevationData::getLatLon(const String& name) const
	{
		int lat;
		int lon;

		lat = std::stoi(name.substr(1, 2));
		lon = std::stoi(name.substr(5, 3));

		if (name[0] == 's')
			lat = -lat;

		if (name[4] == 'w')
			lon = -lon;

		return std::make_pair(lat, lon);
	}

	int ElevationData::sizeX(const Coordinate& coord) const
	{
		ElevationData2D::Coordinate c;
		if (std::floor(coord.getLon()) == std::floor(c2.getLon()))
		{
			c = ElevationData2D::Coordinate(std::floor(coord.getLat()), c2.getLon());
		}
		else
		{
			c = ElevationData2D::Coordinate(std::floor(coord.getLat()), std::floor(coord.getLon()) + 1);
		}

		return get_nXSize(c, coord);
	}


	int ElevationData::sizeX() const
	{
		int size = 0;
		Vector<Coordinate> width = firstUpRow();
		for (uint i = 0; i < width.size() - 1; ++i)
			size += (sizeX(width[i]) - 1);

		size += get_nXSize(width[width.size() - 1], Coordinate(std::floor(width[width.size() - 1].getLat()), c2.getLon()));
		return size;
	}


	int ElevationData::sizeY(const Coordinate& coord) const
	{
		ElevationData2D::Coordinate c;
		float down_lat = float(std::floor(c2.getLat())+1);
		if (coord.getLat() == c1.getLat())
		{
			if (c1.getLat() - c2.getLat() <= 1. && c1.getLon() - c2.getLon() <= 1.)
				c = c2;
			else
				c = ElevationData2D::Coordinate(std::floor(coord.getLat()), std::floor(coord.getLon()) + 1);
		}
		if (coord.getLat() == down_lat)
			c = ElevationData2D::Coordinate(c2.getLat(),float(std::floor(coord.getLon())+1));
		if(!(coord.getLat() == c1.getLat() || coord.getLat() == down_lat))
			c = ElevationData2D::Coordinate(std::floor(coord.getLat()) - 1, std::floor(coord.getLon()) + 1);

		return get_nYSize(c, coord);
	}


	int ElevationData::sizeY() const
	{
		int size = 0;
		Vector<Coordinate> height = firstLeftColumn();

		for (uint i = 0; i < height.size() - 2; ++i)
			size += (sizeY(height[i]) - 1);

		size += get_nYSize(height[height.size() - 2], Coordinate(c2.getLat(), std::floor(c1.getLon()) + 1));

		return size;
	}


	Vector<Coordinate> ElevationData::firstLeftColumn() const
	{
		Vector<Coordinate> col;
		Vector<Coordinate> grid = gridVector();
		for (uint i = 0; i < grid.size(); ++i)
			if (grid[i].getLon() == c1.getLon())
				col.push_back(grid[i]);

		return col;
	}

	Vector<Coordinate> ElevationData::firstUpRow() const
	{
		Vector<Coordinate> row;
		Vector<Coordinate> grid = gridVector();
		for (uint i = 0; i < grid.size(); ++i)
			if (grid[i].getLat() == c1.getLat())
				row.push_back(grid[i]);

		return row;
	}

	int ElevationData::operator()(int i, int j) const
	{
		return rasterData[j * wholeSizeX + i];
	}

}
