#include "Screen.h"

using namespace MineSweeper;

Screen::Screen() : map(map) { initializeImage(); }
Screen::Screen(Map& map) : map(map)
{
	initializeImage();
	scanmine = initgraph(map.column * SIZE, (map.row - 1)*SIZE);
}

void Screen::printMap(int **player_map, int flag, int& gameover, Map& map)
{
	for (int i = 1; i < map.row - 1; i++)
	{
		for (int j = 1; j < map.column - 1; j++)
		{//���հ�
			if (player_map[i][j] == -1)
			{
				std::cout << " #\t|";
				putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[9]);
			}
			//������
			else if (player_map[i][j] == -2)
			{
				std::cout << " -2\t|";
				putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[10]);
			}
			//���ʺ�
			else if (player_map[i][j] == -3)
			{
				std::cout << " -3\t|";
				putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[12]);
			}
			else
			{
				//��ը��
				if (map.bomb_map[i][j] == 1 || player_map[i][j] == -5)
				{
					std::cout << " *\t|";
					putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[13]);
					printMap(map, player_map);
					MessageBox(scanmine, "������", "", MB_OK);
					gameover = 1;
				}
				//������
				else
				{
					std::cout << player_map[i][j] << " \t|";
					putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[player_map[i][j]]);
				}
			}
		}
		std::cout << "\n";
	}
	std::cout << "---------------\n";

	//ʵʱ����ʣ������
	TCHAR s[10];
	outtextxy((map.column - 1)*SIZE, 0, "ʣ�����:");
	sprintf_s(s, "%02d", map.bomb_number - flag);
	outtextxy((map.column + 2)*SIZE, 0, s);

	for (int i = 1; i < map.column - 1; i++)
	{
		putimage((i - 1)*SIZE, (map.row - 2)*SIZE, &img[20]);
	}
	//��Ц��
	putimage(((map.column / 2) - 1)*SIZE, (map.row - 2)*SIZE, &img[16]);
}

void Screen::initializeImage()
{
	for (int i = 0; i < IMAGE_NUM; i++)
	{
		char fileName[20] = "";
		sprintf_s(fileName, "./image/%d.gif", i);
		loadimage(&img[i], fileName, SIZE, SIZE);
	}
}

void Screen::printMap(Map& map, int **player_map)
{
	PlaySound(TEXT("music/die.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_PURGE);//������Ϸʧ������
	for (int i = 1; i < map.row - 1; i++)
	{
		for (int j = 1; j < map.column - 1; j++)
		{//���հ�
			if (player_map[i][j] == -1 && map.bomb_map[i][j] != 1)
			{
				std::cout << "#\t|";
				putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[9]);
			}
			//������
			else if (map.bomb_map[i][j] == 1 && player_map[i][j] == -1)
			{
				std::cout << "*\t|";
				putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[11]);
			}
			//������
			else if (player_map[i][j] == -2 && map.bomb_map[i][j] == 1)
			{
				std::cout << "-2\t|";
				putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[10]);
			}
			//������
			else if (player_map[i][j] == -2 && map.bomb_map[i][j] == 0)
			{
				putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[19]);
			}
			//���ʺ�
			else if (player_map[i][j] == -3)
			{
				std::cout << "-3\t|";
				putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[12]);
			}
			else
			{
				//��ը��
				if (player_map[i][j] == -5)
				{
					std::cout << "*\t|";
					putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[13]);
				}
				//������
				else
				{
					std::cout << player_map[i][j] << "\t|";
					putimage((j - 1)*SIZE, (i - 1)*SIZE, &img[player_map[i][j]]);
				}
			}
		}
		std::cout << "\n";
	}
	std::cout << "---------------\n";

	for (int i = 1; i < map.row - 1; i++)
	{
		putimage((i - 1)*SIZE, (map.column - 2)*SIZE, &img[20]);
	}
	putimage(((map.row / 2) - 1)*SIZE, (map.column - 2)*SIZE, &img[17]);
}