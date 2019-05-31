#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include "head2.h"
/*****************************************/
void GotoXY(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);

}
/*****************************************/
void GotoPrint(int x, int y)
{
	GotoXY(x, y);
	printf("*");
}
/*****************************************/
void GotoDelete(int x, int y)
{
	GotoXY(x, y);
	printf(" ");
}
/*****************************************/
/*void BeforeGameClickControl(char &ope)
{
	if (_kbhit())
	{
		ope = _getch();
	}
}*/
/******************************************/
void welcome()
{
	char ope;
	GotoXY(20,2);
	printf("Welcome to the game。 ");
	GotoXY(20, 3);
	printf("Please put in you name :");
	gets_s(name,20);
	fflush(stdin);
	system("cls");
	GotoXY(20, 5);
	printf("Dear %s,please choose next operation.", name);
	GotoXY(10, 6);
	printf("You have two choices ,put in 'a' to begin,put in p to stop.('p'always can be used)");
	GotoXY(20,7);
	printf("Please choose :");
	scanf_s("%c", &ope,1);
	if (ope == 'p' || ope == 'P')
	{
		char c;
		while ((c= getchar()) != '\n' && c != EOF);//正确清除缓存的方法
		printf("Ok. put in \'a\' to continue,else to leave:");
		scanf_s("%c", &ope,1);
		if (ope != 'a'&&ope != 'A')
			exit(1);
		else
			for (int i = 3; i > 0; i--)
			{
				GotoXY(20, 8);
				printf("%d", i);
				Sleep(1000);
			}
		printf("hello,baby,,are you ready ? ,we will begin now");
		Sleep(1000);
		system("cls");
		CreateGraph();

	}
	else if (ope == 'a' || ope == 'A')
	{
		for (int i = 3; i > 0; i--)
		{
			GotoXY(20,8);
			printf("%d", i);
			Sleep(1000);
		}
		printf("hello,baby,,are you ready ? ,we will begin now");
		Sleep(1000);
		system("cls");
		CreateGraph();
	}
	

}
/**********************************************/
void CreateNewSnake()
{
	head = (links*)malloc(sizeof(links));
	links *p, *q;
	p= (links*)malloc(sizeof(links));
	q= (links*)malloc(sizeof(links));
	tail= (links*)malloc(sizeof(links));
	head->next = p;
	p->next = q;
	q->next = tail;
	tail->next = NULL;
	head->x = 14;
	head->y = 15;
	p->x = 14;
	p->y = 16;
	q->x = 14;
	q->y = 17;
	tail->x = 1;//no use
	tail->y = 1;//no use
}
/*********************************************/
void CreateGraph()
{
	
	for (int i = 0; i <= 2*n; i+=2)
	{
		GotoPrint(i, 0);
		GotoPrint(i, n);
    }
	for (int i = 1; i < n; i++)
	{
		GotoPrint(0, i);
		GotoPrint(2*n, i);
	}
	CreateNewSnake();
	links *teger=head;
	while (1)
	{
		GotoPrint(teger->x, teger->y);
		teger = teger->next;
		if (teger->next == NULL)
			break;
	}
	GotoXY(60, 4);
		printf("%s is playing my game ",name);
		GotoXY(60, 5);
		printf("Please don't disturb him.");
		GotoXY(60, 6);
		printf("your score is %d", score);
		GotoXY(60, 8);
		printf("this game is created by Mr.sha");
}
/*************************************************************/
void ChangeBody2(int a,int b)//a，b是上一部头所在位置,辅助ChangeBody2进行身体改变
{
	links *p;
	p = head->next;
	int a1, a2, b1, b2;
	a1 = p->x;
	a2 = p->y;
	while (p->next->next != NULL)
	{
		b1 = p->next->x;
		b2 = p->next->y;
		p->next->x = a1;
		p->next->y = a2;
		a1 = b1;
		a2 = b2;
		p = p->next;
	}
	p = head->next;
	p->x = a;
	p->y = b;
	p = head;
}
/*******************************************************/
void PrintBody()
{
	links *p = head;
	
	while (p->next != NULL)
	{
		GotoPrint(p->x, p->y);
		p = p->next;
	}
	GotoXY(60,15);
}
/*******************************************************/
int ClickControl()
{
	while (1)
	{
		if (Judge() == 0)
		return 0;
		if (_kbhit())
		{
			click = _getch();
		
		}
		links *p = head;
		while (1)
		{
			if (p->next->next == NULL)
			{
				GotoDelete(p->x, p->y);
				break;
			}
			p = p->next;
		}
		JudgeIfGetFood();
		ChangeBody1();
		PrintBody();
		p = head;
			while (p->next != NULL)
			{
				length++;
				p = p->next;
			}
		if (length <= 10)
			speed = 400;
		else if (length <= 20)
			speed = 300;
		else if (length < 25)
			speed = 200;
		else
			speed = 100;
		Sleep(speed);
		length = 0;
	}
}
/*****************************************************/
void ChangeBody1()
{
	int a, b;
	a = head->x;
	b = head->y;
	switch (click)
	{
	case up:
		head->y -= 1;
		ChangeBody2(a, b);
		break;
	case down:
		head->y += 1;
		ChangeBody2(a, b);
		break;
	case right:
		head->x += 2;
		ChangeBody2(a, b);
		break;
	case left:
		head->x -= 2;
		ChangeBody2(a, b);
		break;
	default:
		PrintBody();
			break;

	}
}
/*********************************************************/
int Judge()
{
	if (head->x == 0 || head->x == 2*n || head->y == 2*n || head->y == 0)
		return 0;
	links *p = head->next;
	while (p->next!=NULL)
	{
		if (p->x == head->x&&p->y ==head->y)
			return 0;
		p = p->next;
	}
	return 1;
}
/************************************************************/
void CreateFood()//产生食物，在框内，其不可与蛇身体重叠
{srand(time(NULL));
	place = (food*)malloc(sizeof(food));
	while (1) 
	{
		
		place->x = rand() ;
		if (place->x % 2 == 0)
			place->x = place->x % (2 * n) + 2;
		else
			place->x = (place->x + 1) % (2 * n) + 2;
		place->y = rand() % (n - 1) + 1;
		links *p = head;
		while (p->next!=NULL)
		{
			if (p->x == place->x&&p->y == place->y)
				break;
			p = p->next;
		}
		if (p->next == NULL)
			break;
		else
			continue;
	}
	GotoPrint(place->x, place->y);
}
void JudgeIfGetFood()//若吃得到食物顺便生成下一个食物。
{
	links *p = head;
	links *new1;
	new1 = (links*)malloc(sizeof(links));

	if (head->x == place->x&&head->y == place->y)
	{
		if (length < 10)
			score++;
		else if (length < 20)
			score += 2;
		else if (length < 25)
			score += 3;
		else
			score += 4;
		GotoXY(60, 6);
		printf("your score is %d", score);
		while (p->next->next != NULL)
			p = p->next;
		p->next = new1;
		new1->next = tail;
		CreateFood();
		
	}
}
/********************************************/
void finish()
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
	system("cls");
	GotoXY(10, 3);
		printf(" %s ,game over!",name);
	GotoXY(10, 5);
	printf("your score is %d", score);
	GotoXY(10, 8);
	printf("按ENTER退出 .....");
	getchar();
	
}
