/********************************************
Map.h
Author: LB
Date: 2022.4.23
Description:
创建地雷图并对九宫格内地雷计数
各函数说明：
	void initializeMap();  初始化自定义地图
	void initializeMap(int length, int height, int bomb_number); 初始化低中高级地图
	void rumCreatMine( int bomb_number); 随机生成地雷
	void updateBombMap(); 计算九宫格内地雷数
********************************************/
#ifndef MAP_H
#define MAP_H

#include<iostream>
#include<ctime>
#include<graphics.h>

namespace MineSweeper
{
class Map
{
public:
	Map();
	~Map();

	void initializeMap();
	void initializeMap(int length, int height, int bomb_number);
	void rumCreatMine(int bomb_number);
	void updateBombMap();
	

	int row, column, bomb_number;

	int **bomb_map;
	int **bomb_map_update;
	
};
}

#endif // ! MAP_H

