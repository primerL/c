/********************************************
Map.h
Author: LB
Date: 2022.4.23
Description:
��������ͼ���ԾŹ����ڵ��׼���
������˵����
	void initializeMap();  ��ʼ���Զ����ͼ
	void initializeMap(int length, int height, int bomb_number); ��ʼ�����и߼���ͼ
	void rumCreatMine( int bomb_number); ������ɵ���
	void updateBombMap(); ����Ź����ڵ�����
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

