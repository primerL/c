#include "Map.h"

using namespace MineSweeper;

Map::Map(){}

//初始化自定义地图
void Map::initializeMap()
{
	closegraph();
    system("mode con cols=70 lines=25");
	std::cout << "please input row column and bomb number(LB)" << std::endl;
	while (!(std::cin >> row >> column >> bomb_number) || row * column < bomb_number || row <= 0 || column <= 0 || bomb_number <= 0) {
	    std:: cout << "wrong,please input row column and bomb number(LB)" << std::endl;
		std::cin.clear();
		std::cin.sync();
	}
	row += 2;
	column += 2;
	bomb_map = new int*[row];
	bomb_map_update = new int*[row];
	for (int i = 0; i < row; i++) {
		bomb_map[i] = new int[column]();
		bomb_map_update[i] = new int[column]();
	}
	rumCreatMine(bomb_number);
	updateBombMap();
}

//初始化低中高级地图
void Map::initializeMap(int length, int height, int bomb_number)
{
	this->column = length;
	this->row = height;
	this->bomb_number = bomb_number;

	row += 2;
	column += 2;
	bomb_map = new int*[row];
	bomb_map_update = new int*[row];
	for (int i = 0; i < row; i++) {
		bomb_map[i] = new int[column]();
		bomb_map_update[i] = new int[column]();
	}

	rumCreatMine(bomb_number);
	updateBombMap();
}

//随机生成地雷
void Map::rumCreatMine(int bomb_number)
{
	for (int i = 0; i < bomb_number; i++)
	{
		srand(time(NULL));
		int x = rand() % (row - 2) + 1;
		int y = rand() % (column - 2) + 1;
		do
		{
			if (bomb_map[x][y] == 0)
			{
				bomb_map[x][y] = 1;
				break;
			}
			x = rand() % (row - 2) + 1;
			y = rand() % (column - 2) + 1;
		} while (1);
	}
}

//计算九宫格地雷数量
void Map::updateBombMap()
{
	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < column - 1; j++)
		{
			bomb_map_update[i][j] = 0;
		}
	}

	for (int i = 1; i < row - 1; i++)
		for (int j = 1; j < column - 1; j++)
			for (int k = i - 1; k < i + 2; k++)
				for (int w = j - 1; w < j + 2; w++)
				{
					bomb_map_update[i][j] += bomb_map[k][w];
				}
}

Map::~Map()
{
	delete[] bomb_map;
	delete[] bomb_map_update;
}