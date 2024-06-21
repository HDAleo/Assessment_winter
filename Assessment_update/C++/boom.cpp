#include<iostream>
#include<cstdlib>
#define ROW 9
#define COL 9
#define ROWS ROW + 2
#define COLS COL + 2
#define EASY_COUNT 10
using namespace std;
void menu()
{
	cout << "********** MENU **********\n";
	cout << "******   1. play  ******\n";
	cout << "******   0. exit  ******\n";
	cout << "*************************\n";
}


class Mine
{
public:
	void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
	{
		int i = 0;
		int j = 0;
		for (i = 0; i < rows; i++)
		{
			for (j = 0; j < cols; j++)
			{
				board[i][j] = set;
			}
		}
	}
	void DisplayBoard(char board[ROWS][COLS], int row, int col)
	{
		int i = 0;
		int j = 0;
		cout << "------------扫雷------------\n";
		for (i = 0; i <= row; i++)
		{
			cout << i<<" ";
		}
		cout << "\n";
		for (i = 1; i <= row; i++)
		{
			cout << i<<" ";
			for (j = 1; j <= col; j++)
			{
				cout << board[i][j]<<" ";
			}
			cout << "\n";
		}
		cout << "------------扫雷------------\n";
	}
	void SetMine(char board[ROWS][COLS], int row, int col)
		{
	int count = EASY_COUNT;
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
		}
		count--;
	}
		}
	void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
		{
	int x = 0;
	int y = 0;
	int win = 0;
	while (win < row * col - EASY_COUNT)
	{
		cout << "请输入横坐标>";
		cin>>x;
		cout << "请输入纵坐标>";
		cin >> y;
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (show[x][y] != '*')
			{
				cout << "输入坐标重复，请重新输入\n";
			}
			else if (mine[x][y] == '1')
			{
				cout << "你被炸死了\n";
				DisplayBoard(mine, ROW, COL);
				break;
			}
			else
			{
				//不是雷，就统计x,y坐标周围有几个雷
				int c = GetMineCount(mine, x, y);
				show[x][y] = c + '0';
				DisplayBoard(show, ROW, COL);
				win++;
			}
		}
		else
		{
			cout<<"输入坐标错误，请重新输入\n";
		}
	}
	if (win == row * col - EASY_COUNT)
	{
		cout << "成功\n";
		DisplayBoard(mine, ROW, COL);
	}
}
	int GetMineCount(char mine[ROWS][COLS], int x, int y)
	{
		return mine[x + 1][y] + mine[x - 1][y] +
			mine[x][y + 1] + mine[x][y - 1] +
			mine[x + 1][y + 1] + mine[x - 1][y + 1] +
			mine[x - 1][y - 1] + mine[x + 1][y - 1] - 8 * '0';
	}
};

void game()
{
	Mine mine1;
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };
	mine1.InitBoard(mine, ROWS, COLS, '0');
	mine1.InitBoard(show, ROWS, COLS, '*');
	mine1.DisplayBoard(show, ROW, COL);
	mine1.SetMine(mine, ROW, COL);
	mine1.FindMine(mine, show, ROW, COL);
}

int main()
{
	int input = 0;
	do
	{
		menu();
		cout << "请输入选项>";
		cin>>input;
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			cout << "退出游戏";
			break;
		default:
			cout << "输入错误，请重新输入";
			break;
		}
	} while (input);
	return 0;
}
