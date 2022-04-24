/***************************************
Game.h
Author: LB
Date: 2022.4.23
Description: 
�û���ͼ�Ĵ����Լ���Ϸ����ʵ��
������˵����
	void run();  ��Ϸ��ʼ����
	void play(); �û�����
	void initializePlayer(int row, int column); ��ʼ���û���ͼ
	void blankOpen(int r, int c); ���޵��׸���չ��
	void open(int r, int c);      ���ѱ�ǵ��׾Ź���չ��
	void restart();               ��Ϸ���������¿�ʼ
	int win();                    �ж���Ϸ�Ƿ�Ӯ
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
	clock_t tic = clock(); //��Ϸ��ʼʱ��
};
}

#endif // ! GAME_H

