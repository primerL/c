/******************************************
Screen.h
Author: LB
Date: 2022.4.23
Description:
���û���ͼ��ӡ����Ļ���Ѿ���Ϸʧ�����е��׵���ʾ
������˵����
	void printMap(int **player_map, int flag, int& gameover, Map& map); ��ӡ�û���ͼ
	void printMap(Map& map, int **player_map); ��ӡ��Ϸʧ�ܵĵ�ͼ
	void initializeImage(); ����ͼƬ�ز�
*******************************************/
#ifndef SCREEN_H
#define SCREEN_H

#include "Map.h"
#include <graphics.h>
#include <fstream>


#define SIZE 25//ͼƬ��С
#define IMAGE_NUM 21//ͼƬ����

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

