#include "Game.h"

using namespace MineSweeper;

Game::Game()
{
	PlaySound(TEXT("music/bg_music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//���ű�������
	
	screen.scanmine = initgraph(550, 550);

	loadimage(NULL, _T("image/22.jpg"), 550, 550);//�����ʼҳ��
	
	Sleep(2000);
}

void Game::run()
{
	loadimage(NULL, _T("image/21.png"), 550, 550);
	int flag = 1;

	MOUSEMSG msg = { 0 };
	while (flag)
	{
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{
			//�������ж�
		case WM_LBUTTONDOWN:
			//�ж���������������ʼ��Ϸ����Χ
			if (msg.x >= 200 && msg.x <= 275 && msg.y >= 150 && msg.y <= 200)
			{
				flag = 0;
				map.initializeMap(9, 9, 10);
			}
			else if (msg.x >= 200 && msg.x <= 275 && msg.y >= 250 && msg.y <= 300)
			{
				flag = 0;
				map.initializeMap(16, 16, 40);
			}
			else if (msg.x >= 200 && msg.x <= 275 && msg.y >= 350 && msg.y <= 375)
			{
				flag = 0;
				map.initializeMap(30, 16, 99);
			}
			else if (msg.x >= 200 && msg.x <= 300 && msg.y >= 430 && msg.y <= 470)
			{
				flag = 0;
				map.initializeMap();
			}
			initializePlayer(map.row, map.column);
			play();
			break;

		default:
			flag = 1;
		}
	}
}

void Game::initializePlayer(int row, int column)
{
	row += 2;
	column += 2;
	player_map = new int*[row];
	for (int i = 0; i < row; i++) {
		player_map[i] = new int[column]();
	}

	//��ʼ���û�ҳ������
	for (int i = 1; i < row - 1; i++)
	{
		for (int j = 1; j < column - 1; j++)
		{
			player_map[i][j] = -1;
		}
	}
}

void Game::play()
{
	screen.scanmine = initgraph(map.column * SIZE + 100, (map.row - 1) * SIZE);
	screen.printMap(player_map, 0, gameover, map);

	msg = { 0 };
	bool first = true;
	int r, c;
	int flag = 0; //�������ӵ�����
	while (1)
	{
		TCHAR s[10] = "";
		nowTime = GetTickCount();
		outtextxy((map.column - 1)*SIZE, 25, "ʱ��:");
		sprintf_s(s, "%02d", (first ? 0 : (int)((nowTime - startTime + 1000) / 1000)));
		outtextxy((map.column + 2)*SIZE, 25, s);

		msg = GetMouseMsg();
		switch (msg.uMsg)
		{
			//�����������
		case WM_LBUTTONDOWN:
			r = msg.y / SIZE + 1;
			c = msg.x / SIZE + 1;
			//���Ц��λ�ÿ���ˢ�±�����Ϸ
			if (c == (map.column / 2) && r == map.row - 1)
			{
				map.initializeMap(map.column - 2, map.row - 2, map.bomb_number);
				initializePlayer(map.row-2, map.column-2);
				play();
			}
			if (r > 0 && r < map.row - 1 && c > 0 && c < map.column - 1)
			{
				//��֤��һ�β�����
				if (first == true)
				{
					first = false;
					startTime = GetTickCount(); //�ӵ�һ�ε����ʼ��ʱ
					if (map.bomb_map[r][c] == 1)
					{
						map.rumCreatMine(1);
						map.bomb_map[r][c] = 0;
						map.updateBombMap();
					}
				}

				if (player_map[r][c] == -1)
				{
					if (map.bomb_map[r][c] != 1)
					{
						player_map[r][c] = map.bomb_map_update[r][c];
						if (player_map[r][c] == 0)
						{
							blankOpen(r, c);
						}
						std::cout << player_map[r][c];
					}
					else
					{
						player_map[r][c] = -5;
						screen.printMap(map, player_map);
						MessageBox(screen.scanmine, "������", "", MB_OK);
						restart();
					}
				}
				else if (player_map[r][c] > 0)
				{
					open(r, c);
				}

				if (win() == 1)
				{
					screen.printMap(player_map, flag, gameover, map);
					putimage(((map.column / 2) - 1)*SIZE, (map.row - 2)*SIZE, &screen.img[18]);
					MessageBox(screen.scanmine, "��Ӯ��", "", MB_OK);
					restart();
				}
			}
			break;

			//�����ӣ�������
		case WM_RBUTTONDOWN:
			r = msg.y / SIZE + 1;
			c = msg.x / SIZE + 1;
			if (r > 0 && r < map.row - 1 && c>0 && c < map.column - 1)
			{
				if (player_map[r][c] == -1)
				{
					if (flag < map.bomb_number)
					{
						flag++;
						player_map[r][c] = -2;
					}
				}
				else if (player_map[r][c] == -2)
				{
					flag--;
					player_map[r][c] = -3;
				}
				else if (player_map[r][c] == -3)
				{
					player_map[r][c] = -1;
				}
			}
			break;
		}

		screen.printMap(player_map,flag, gameover, map);
		if (gameover == 1)
		{
			gameover = 0;
			restart();
		}

		clock_t elapsed = 1 - (clock() - tic); 
		Sleep(elapsed > 0 ? elapsed : 0); 
		tic = clock();
	}

}

void Game::blankOpen(int r, int c)
{
	for (int i = r - 1; i <= r + 1; i++)
	{
		for (int j = c - 1; j <= c + 1; j++)
		{
			//�ж�����λ�ã���ֹ����չ��Խ�磻�ж���û���Ų���������0����չ��
			if (i >= 1 && i < map.row - 1 && j >= 1 && j < map.column - 1 && player_map[i][j] == -1)
			{
				if (map.bomb_map_update[i][j] == 0)
				{
					player_map[i][j] = map.bomb_map_update[i][j];
					blankOpen(i, j);
				}
				else
				{
					player_map[i][j] = map.bomb_map_update[i][j];
				}

			}
		}
	}
}

void Game::open(int r, int c)
{
	int flag = 0;//�Ź�����������
	for (int i = r - 1; i <= r + 1; i++)
	{
		for (int j = c - 1; j <= c + 1; j++)
		{
			if (player_map[i][j] == -2)
			{
				flag++;
			}
		}
	}

    //�����������ڸ������֣��Ź���չ��
	if (flag == player_map[r][c])
	{
		for (int i = r - 1; i <= r + 1; i++)
		{
			for (int j = c - 1; j <= c + 1; j++)
			{
				if (player_map[i][j] == -1)
				{
					if (map.bomb_map[i][j] == 1)
					{
						player_map[i][j] = -5;
					}
					//����ǿհ׸񣬵ݹ�չ��
					else if (map.bomb_map_update[i][j] == 0)
					{
						player_map[i][j] = map.bomb_map_update[i][j];
						blankOpen(i, j);
					}
					else
					{
						player_map[i][j] = map.bomb_map_update[i][j];
					}
				}
			}
		}
	}
}

void Game::restart()
{
	PlaySound(TEXT("music/bg_music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//���ű�������
	screen.scanmine = initgraph(550, 550);
	loadimage(NULL, _T("image/23.png"), 550, 550);

	int flag = 1;

	MOUSEMSG msg = { 0 };
	while (flag)
	{
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{
			//�������ж�
		case WM_LBUTTONDOWN:
			//�ж���������������ʼ��Ϸ����Χ
			if (msg.x >= 200 && msg.x <= 250 && msg.y >= 250 && msg.y <= 325)
			{
				flag = 0;
				system("cls");
				run();
			}
			else if (msg.x >= 185 && msg.x <= 250 && msg.y >= 375 && msg.y <= 450)
			{
				std::cout << "��";
				exit(0);
			}
			break;

		default:
			flag = 1;
		}

	}

	system("pause");
}

int Game::win()
{
	int flag_right = 0;//��ȷ��ǵ�����
	int rest = 0;
	for (int i = 1; i < map.row - 1; i++)
	{
		for (int j = 1; j < map.column - 1; j++)
		{
			if (player_map[i][j] == -2 && map.bomb_map[i][j] == 1)
			{
				flag_right++;
			}
			else if (player_map[i][j] == -1)
			{
				rest++;
			}
		}
	}

	if (flag_right + rest == map.bomb_number)
	{
		return 1;
	}
}

Game::~Game()
{
	delete[] player_map;
}
