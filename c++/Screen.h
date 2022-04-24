/******************************************
Screen.h
Author: LB
Date: 2022.4.23
Description:
将用户地图打印到屏幕，已经游戏失败所有地雷的显示
各函数说明：
	void printMap(int **player_map, int flag, int& gameover, Map& map); 打印用户地图
	void printMap(Map& map, int **player_map); 打印游戏失败的地图
	void initializeImage(); 载入图片素材
*******************************************/
#ifndef SCREEN_H
#define SCREEN_H

#include "Map.h"
#include <graphics.h>
#include <fstream>


#define SIZE 25//图片大小
#define IMAGE_NUM 21//图片数量

namespace MineSweeper
{
class Screen
{
public:
	Screen();
	Screen(Map& map);

	void printMap(int **player_map, int flag, int& gameover, Map& map);
	void printMap(Map& map, int **player_map);

	HWND scanmine;

	IMAGE img[IMAGE_NUM];

private:
	Map& map;
	void initializeImage();
};
}

#endif // !SCREEN_H

