// Miner.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define Nmax 30
using namespace std;
void bomber(int **a, int row, int col, int bomb);
void show(int **a, int row, int col);
void ctbb(int **a, int x, int y);
int main(int argc, char*argv[])
{
	srand(time(NULL));
	int N, M;
	cout << "輸入大小:      ";
	cin >> N;
	cout << "輸入炸彈數量:  ";
	cin >> M;
	if (N > Nmax)
	{
		printf("error\n");
		exit(0);
	}
	int **ptr2 = NULL;
	ptr2 = (int**)malloc(sizeof(int*) * 35);
	for (int i = 0; i<35; i++)
		ptr2[i] = (int*)malloc(sizeof(int) * 35);
	bomber(ptr2, N, N, M);
	show(ptr2, N, N);
	do {
		int y = 0;
		int x = 0;
		int win1 = 0;
		//scanf("%d%d",&x,&y);
		cout << "輸入x座標: ";
		cin >> x;
		cout << "輸入y座標: ";
		cin >> y;
		// cout<<"(";
		// cin>>x;
		// cout<<",";
		// cin>>y;
		// cout<<")"<<endl; 
		//system("clear");
		if (x > (N - 1) || y > (N - 1)) {
			show(ptr2, N, N);
			printf("Segmentation fault\n");
			exit(0);
		}
		if (ptr2[x][y] == 99)
		{
			show(ptr2, N, N);
			printf("you are dead!!");
			exit(0);
		}
		ctbb(ptr2, x, y);
		show(ptr2, N, N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (ptr2[i][j] == -1 || ptr2[i][j] == 99) {
					win1 = win1 + 1;
				}
			}
		}
		if (win1 == M) { printf("you win!\n"); break; }
		printf("\n");
	} while (1);


	for (int i = 0; i<35; i++)
	{
		free(ptr2[i]);
	}
	free(ptr2);
	return 0;
}
void bomber(int **a, int row, int col, int bomb)
{
	int hide1, hide2;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			a[i][j] = -1;
		}
	}
	for (int i = 1; i <= bomb; i++)
	{
		hide1 = rand() % (row - 1 - 0 + 1);
		hide2 = rand() % (col - 1 - 0 + 1);
		if (a[hide1][hide2] == 99)
		{
			continue;
		}
		a[hide1][hide2] = 99;
	}
}
void show(int **a, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (a[i][j] == -1 || a[i][j] == 99)
				printf("?");
			else if (a[i][j] == 0)
				printf("_");
			else
				printf("%d", a[i][j]);
		}
		printf("\n");
	}
}
void ctbb(int **a, int x, int y)
{
	int count = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if ((i + x)<0 || (j + y)<0)
				continue;
			if (a[i + x][j + y] == 99)
			{
				count += 1;
			}
		}
	}
	if (count == 0)
	{
		a[x][y] = 0;
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if ((i + x<0) || (j + y)<0)
					continue;
				if (a[i + x][j + y] == -1)
				{
					ctbb(a, i + x, j + y);
				}
			}
		}
	}
	else
	{
		a[x][y] = count;
	}
}
