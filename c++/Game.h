/***************************************
Game.h
Author: LB
Date: 2022.4.23
Description: 
用户地图的创建以及游戏操作实现
各函数说明：
	void run();  游戏开始运行
	void play(); 用户操作
	void initializePlayer(int row, int column); 初始化用户地图
	void blankOpen(int r, int c); 对无地雷格子展开
	void open(int r, int c);      对已标记地雷九宫格展开
	void restart();               游戏结束后重新开始
	int win();                    判断游戏是否赢
******************************************/

#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Screen.h"
#include<ctime>
#include<windows.h>
#include<mmSystem.h>
#pragma comment (lib,"winmm.lib") 

namespace MineSweeper
{
class Game
{
public:
	Game();
	~Game();

	void run();
	void play();
	void initializePlayer(int row, int column);
	void blankOpen(int r, int c);
	void open(int r, int c);
	void restart();
	int win();

	int gameover = 0;
	int **player_map;

	Map map;
	Screen screen;

private:
	MOUSEMSG msg;

	double startTime, nowTime;
	clock_t tic = clock(); //游戏开始时间
};
}

#endif // ! GAME_H

