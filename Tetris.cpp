#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int delay(unsigned int);
void newBlock(int a[][20], int x, int y);
void turnBlock(int a[][20], int x, int y);

void placedBlock(int a[][20], int x, int y);

bool destroySatir(int a[][20], int x, int y);

void moveDown(int a[][20], int x, int y);
void moveRight(int a[][20], int x, int y);
void moveLeft(int a[][20], int x, int y);
int moveBottom(int a[][20], int x, int y);

bool checkMoveDown(int a[][20], int x, int y);
bool checkMoveRight(int a[][20], int x, int y);
bool checkMoveLeft(int a[][20], int x, int y);
bool checkTurn(int a[][20], int x, int y);

void printScreen(int a[][20]);

bool gameOver(int a[][20], int x, int y);

int main()
{
	int puzzle[10][20];
	
	int x=3, y=3;
	
	for (int i=0; i<20; i++)
	{
		for (int j=0; j<10; j++)
		{
			puzzle[j][i] = 0;
		}
	}
	
	do
	{
		bool tf = true;
		
		x=3; y=3;
		newBlock(puzzle, x, y);
		
		do
		{
			moveDown(puzzle, x, y);
			y++;
			
			printScreen(puzzle);
			
			for (int i=0; i<10; i++) printf(" '");
			
			int choose = delay(500);
			
			if (choose == 1 && checkTurn(puzzle, x, y))
			{
				turnBlock(puzzle, x, y);
			} 
			else if (choose == 2 && checkMoveRight(puzzle, x, y))
			{
				moveRight(puzzle, x, y);
				x++;	
			}
			else if (choose == 3 && checkMoveLeft(puzzle, x, y))
			{
				moveLeft(puzzle, x, y);
				x--;
			}
			else if (choose == 4)
			{
				y = moveBottom(puzzle, x, y);
				tf = false;
			}
		} while(checkMoveDown(puzzle, x, y) && tf);
		placedBlock(puzzle, x, y);
		destroySatir(puzzle, x, y);
	} while(gameOver(puzzle, x, y) == false);	
}

bool gameOver(int a[][20], int x, int y)
{
	bool tf;
	
	for (int i=0; i<4; i++)
	{
		for (int j=3; j<7; j++)
		{
			if (a[j][i] == 2) tf = true;
		}
	}
	
	return tf;
}

void printScreen(int a[][20])
{
	system("CLS");
	for (int i=0; i<20; i++)
	{
		printf(".");
		for (int j=0; j<10; j++)
		{
			if (a[j][i] == 0) printf("  ");
			else printf("%c%c", 219, 219);
		}
		printf(".\n");
	}			
}

int moveBottom(int a[][20], int x, int y)
{
	do
	{
		moveDown(a, x, y);
		y++;
		
		printScreen(a);
	} while(checkMoveDown(a, x, y) == true);
	
	placedBlock(a, x, y);
	
	return y;
}

bool destroySatir(int a[][20], int x, int y)
{
	for (int i=19; i>-1; i--)
	{
		bool destroy = true;
		int j = 0;
		
		do
		{
			if (a[j][i] == 0) 
			{
				destroy = false;
			}
			j++;
		} while(destroy && j<10);
		
		if (destroy)
		{
			for (int k=0; k<10; k++)
			{
				a[k][i] = 0;
			}
			for (int m=i; m>0; m--)
			{
				for (int n=0; n<10; n++)
				{
					a[n][m] = a[n][m-1];
					a[n][m-1] = 0;
				}
			}
		}		
	}
}

void placedBlock(int a[][20], int x, int y)
{
	for (int i=y-3; i<y+1; i++)
	{
		for (int j=x; j<x+4; j++)
		{
			if (a[j][i] == 1) a[j][i] = 2;	
		}	
	}	
}

bool checkMoveLeft(int a[][20], int x, int y)
{
	bool tf = true;
	for (int i=y-3; i<y+1; i++)
	{
		for (int j=x; j<x+4; j++)
		{
			if (a[j][i] == 1 && a[j-1][i] == 2) tf = false;
			if (a[j][i] == 1 && j<1) tf = false;
		}
	}
	
	return tf;
}

bool checkMoveRight(int a[][20], int x, int y)
{
	bool tf = true;
	for (int i=y-3; i<y+1; i++)
	{
		for (int j=x; j<x+4; j++)
		{
			if (a[j][i] == 1 && a[j+1][i] == 2) tf = false;
			if (a[j][i] == 1 && j>8) tf = false;
		}
	}
	
	return tf;
}

bool checkMoveDown(int a[][20], int x, int y)
{
	bool tf = true;
	for (int i=y-3; i<y+1; i++)
	{
		for (int j=x; j<x+4; j++)
		{
			if (a[j][i] == 1 && a[j][i+1] == 2) tf = false;
			if (a[j][i] == 1 && i>18) tf = false;
		}
	}
	
	return tf;
}

bool checkTurn(int a[][20], int x, int y)
{
	int b[4][4];
	
	for (int i=y-3; i<y+1; i++)
	{
		for (int j=x; j<x+4; j++)
		{
			b[j-x][i-y+3] = a[j][i]; 	
		} 
	}
	
	int tmp;
	
	for (int i=0; i<3; i++)
	{
		for (int j=i+1; j<4; j++)
		{
			tmp = b[j][i];
			b[j][i] = b[i][j];
			b[i][j] = tmp;
		}
	}
	
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<2; j++)
		{
			tmp = b[j][i];
			b[j][i] = b[3-j][i];
			b[3-j][i] = tmp;
		}
	}
	
	bool tf = true;
	
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			if (b[j][i] == 1)
			{
				if (a[j+x][i+y-3] == 2) tf = false;
				if (j+x < 0 || 9 < j+x) tf = false;	
			}	
		}	
	}
	
	return tf;	
}

void turnBlock(int a[][20], int x, int y)
{
	int b[4][4];
	
	for (int i=y-3; i<y+1; i++)
	{
		for (int j=x; j<x+4; j++)
		{
			b[j-x][i-y+3] = a[j][i]; 	
		} 
	}
	
	int tmp;
	
	for (int i=0; i<3; i++)
	{
		for (int j=i+1; j<4; j++)
		{
			tmp = b[j][i];
			b[j][i] = b[i][j];
			b[i][j] = tmp;
		}
	}
	
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<2; j++)
		{
			tmp = b[j][i];
			b[j][i] = b[3-j][i];
			b[3-j][i] = tmp;
		}
	}
	
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			if (a[j+x][i+y-3] == 1)
			{
				a[j+x][i+y-3] = 0;
			}
		}
	}
	
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			if (b[j][i] == 1)
			{
				a[j+x][i+y-3] = b[j][i];
			}
		}
	}
	/*int tmp;
	
	for (int i=y-3; i<y; i++)
	{
		for (int j=x-y+i+4; j<x+4; j++)
		{
			tmp = a[j][i];
			a[j][i] = a[x-y+3+i][j-x+y-3];
			a[x-y+3+i][j-x+y-3] = tmp;
		}
	}
	
	for (int i=y-3; i<y+1; i++)
	{
		for (int j=x; j<x+2; j++)
		{
			tmp = a[j][i];
			a[j][i] = a[x+3-(j-x)][i];
			a[x+3-(j-x)][i] = tmp;
		}
	}*/
}

void newBlock(int a[][20], int x, int y)
{
	int block1[4][4] = {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}};
	int block2[4][4] = {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}};
	int block3[4][4] = {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}};
	int block4[4][4] = {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}};
	int block5[4][4] = {{0,0,0,0},{0,1,1,1},{0,0,0,1},{0,0,0,0}};
	int block6[4][4] = {{0,0,0,0},{0,0,0,1},{0,1,1,1},{0,0,0,0}};
	int block7[4][4] = {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}};
	
	int rand1;
	
	srand(time(NULL));
	rand1 = rand()%2+1;
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			if (rand1 == 1) a[j+x][i] = block1[j][i];
			else if (rand1 == 2) a[j+x][i] = block2[j][i];
			else if (rand1 == 3) a[j+x][i] = block3[j][i];
			else if (rand1 == 4) a[j+x][i] = block4[j][i];
			else if (rand1 == 5) a[j+x][i] = block5[j][i];
			else if (rand1 == 6) a[j+x][i] = block6[j][i];
			else if (rand1 == 7) a[j+x][i] = block7[j][i];
		}
	}
}

void moveDown(int a[][20], int x, int y)
{
	for (int i=y; i>y-4; i--)
	{
		for (int j=x; j<x+4; j++)
		{
			if (a[j][i] == 1)
			{
				a[j][i+1] = a[j][i];
				a[j][i] = 0;
			}
		}
	}
}

void moveRight(int a[][20], int x, int y)
{
	for (int i=y; i>y-4; i--)
	{
		for (int j=x+3; j>x-1; j--)
		{
			if (a[j][i] == 1)
			{
				a[j+1][i] = a[j][i];
				a[j][i] = 0;
			}
		}
	}
}

void moveLeft(int a[][20], int x, int y)
{
	for (int i=y; i>y-4; i--)
	{
		for (int j=x; j<x+4; j++)
		{
			if (a[j][i] == 1)
			{
				a[j-1][i] = a[j][i];
				a[j][i] = 0;
			}
		}
	}
}

int delay(unsigned int time)
{
	char key;
	int value;
	clock_t goal;
	goal = clock() + time;
	
	while (clock() < goal)
	{		
		while (kbhit())
		{
			key = getch(); 
		}
		if (key == 32) value = 1;
		else if (key == 100) value = 2;
		else if (key == 97) value = 3;
		else if (key == 115) value = 4;
		else value = 0;
	}
	
	return value;
}
