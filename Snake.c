#include <conio.h>
#include <time.h>

int pos[100][2], yemX, yemY;
int boy, yon;
int i, j, k, l;
char key;

void delay(int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock())
    {
	    	while (kbhit())
		{
			key = getch();
		}
		if (key == 97 && yon != 4)
		{
			yon = 2;
		}
		if (key == 100 && yon != 2)
		{
			yon = 4;
		}
		if (key == 119 && yon != 3)
		{
			yon = 1;
		}
		if (key == 115 && yon != 1)
		{
			yon = 3;
		}
    }
}

void collision()
{
	for (i=1 ; i<boy ; i++)
	{
		if (pos[0][0] == pos[i][0] && pos[0][1] == pos[i][1])
		{
			exit(0);
		}	
	}
}

void screen()
{	
	system("CLS");
	
	for (i=0 ; i<=21 ; i++)
	{
		for (j=0 ; j<=41 ; j=j+1)
		{
			if (i == 0 && j == 0)
			{
				printf("%c" , 218);	
			}
			else if (i == 0 && j == 41)
			{
				printf("%c" , 191);	
			}
			else if (i == 21 && j == 0)
			{
				printf("%c" , 192);	
			}
			else if (i == 21 && j == 41)
			{
				printf("%c" , 217);	
			}
			else if (i == 0 || i == 21)
			{
				printf("%c" , 196);
			}
			else if (j == 0 || j == 41)
			{
				printf("%c" , 179);
			}
			else if (pos[0][0]*2 == j && pos[0][1] == i)
			{
				printf("©");
			}
			else if (yemX*2 == j && yemY == i)
			{
				printf("+");
			}
			else if (j%2 == 1)
			{
				printf(" ");
			}
			else
			{
				printf(" ");
			}
			for (k=1 ; k<boy ; k++)
			{
				if (pos[k][0]*2 == j && pos[k][1] == i)
				{
					printf("%c" , 8);
					printf("o");
				}
			}			
		}
		printf("\n");
	}
	printf("%d" , boy);
}

void yem()
{
	if (pos[0][0] == yemX && pos[0][1] == yemY)
	{
		boy++;
		yemX = (rand() % 20) + 1; 	
		yemY = (rand() % 20) + 1;
	}	
	
	for (i=1 ; i<boy ; i++)
	{
		if (pos[i][0] == yemX && pos[i][1] == yemY)
		{			
			yemX = (rand() % 20) + 1; 	
			yemY = (rand() % 20) + 1;
		}	
	}
}

void start()
{
	yemX = (rand() % 20) + 1;
	yemY = (rand() % 20) + 1;
	pos[0][0] = 1;
	pos[0][1] = 1;
	boy = 2;
	yon = 4;
}

void hareket()
{
	if (yon == 1)
	{
		for (i=boy ; i>=0 ; i--)
		{
			pos[i+1][0] = pos[i][0];
			pos[i+1][1] = pos[i][1];
		}
		pos[0][1]--;
	}
	if (yon == 2)
	{
		for (i=boy ; i>=0 ; i--)
		{
			pos[i+1][0] = pos[i][0];
			pos[i+1][1] = pos[i][1];
		}
		pos[0][0]--;
	}
	if (yon == 3)
	{
		for (i=boy ; i>=0 ; i--)
		{
			pos[i+1][0] = pos[i][0];
			pos[i+1][1] = pos[i][1];
		}
		pos[0][1]++;
	}
	if (yon == 4)
	{
		for (i=boy ; i>=0 ; i--)
		{
			pos[i+1][0] = pos[i][0];
			pos[i+1][1] = pos[i][1];
		}
		pos[0][0]++;
	}
	if (pos[0][0] == 0)
	{
		pos[0][0] = 20;
	}
	if (pos[0][0] == 21)
	{
		pos[0][0] = 1;
	}
	if (pos[0][1] == 0)
	{
		pos[0][1] = 20;
	}
	if (pos[0][1] == 21)
	{
		pos[0][1] = 1;
	}
}

int main()
{
	start();
	do
	{
		screen();
		hareket();
		yem();
		collision();
		delay(150);
	} while(1);
}
