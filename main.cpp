#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include "head2.h"
int main()
{
	system("color 02");
	welcome();
	CreateGraph();
	fflush(stdin);
	CreateFood();
	if (ClickControl() == 0)
	{
		finish();
	}
}
