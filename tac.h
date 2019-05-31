#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
/*****************************/
typedef struct links
{
	int x;
	int y;
	struct links *next;
}links;

typedef struct food 
{
	int x;
	int y;
}food;
/********************************/
 static links *head, *tail;
 static food *place;
 static int score = 0;
 static char click = 1;
 static int length = 0;
 static int speed;
 static int n = 28;
 static char name[20];
/**************************************/
#define up 'w'
#define down 's'
#define right 'd'
#define left 'a'
/******************************************/
void GotoXY(int x, int y);
void GotoPrint(int x, int y);
void GotoDelete(int x, int y);
void BeforeGameClickControl(char &ope);
void welcome();//main 1
void CreateNewSnake();
void CreateGraph();//main2
void ChangeBody2(int a, int b);//a，b是上一部头所在位置,辅助ChangeBody2进行身体改变
void PrintBody();//main3
int ClickControl();//兼具判断功能
void ChangeBody1();
int Judge();//在ClickControl里面
void CreateFood();//产生食物，在框内，其不可与蛇身体重叠，main5
void JudgeIfGetFood();//main 6
void finish();//main 7
