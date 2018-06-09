#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

void delay(unsigned int);

char keyboardHit(unsigned int);

void screen(int map[23][11], int, int);

void loadMap(int map[23][11]);

void createMonster(int map[23][11], int monsterLoc[][2], int);
void monsterMove(int map[23][11], int monsterLoc[][2], int monsterCount);

bool moveRight(int map[23][11], int, int);
bool moveLeft(int map[23][11], int, int);
bool moveUp(int map[23][11], int, int);
bool moveDown(int map[23][11], int, int);

bool plantBomb(int map[23][11], int, int, int bombLoc[5][2], int bombTimer[5], int);
int explodeBomb(int map[23][11], int bombLoc[5][2], int bombTimer[5], int, int fireLoc[50][2], int fireTimer[50], int);

int createFire(int map[23][11], int , int, int fireLoc[50][2], int fireTimer[50], int);
int clearFire(int map[23][11], int fireLoc[50][2], int fireTimer[50]);

bool isAlive(int map[23][11], int, int);
int monsterAlive(int map[23][11], int monsterLoc[][2], int);

int main()
{
	static int map[23][11];
	
	int playerX = 0, playerY = 10;
	bool alive = true;
	
	int monsterCount = 6;
	int monsterLoc[monsterCount][2];

	int bomb = 5;
	static int bombLoc[6][2];
	static int bombTimer[6];
	
	int radius = 2, fireCounter = 0; 
	static int fireLoc[50][2];
	static int fireTimer[50];
	
	loadMap(map);
	createMonster(map, monsterLoc, monsterCount);
	
	do
	{
		alive = isAlive(map, playerX, playerY);
		monsterCount -= monsterAlive(map, monsterLoc, monsterCount);
		
		screen(map, playerX, playerY);
		
		char key = keyboardHit(50);
		
		if (key == 'w') playerY -= moveUp(map, playerX, playerY);
		else if (key == 'a') playerX -= moveLeft(map, playerX, playerY);
		else if (key == 's') playerY += moveDown(map, playerX, playerY);
		else if (key == 'd') playerX += moveRight(map, playerX, playerY);
		else if (key == ' ') bomb -= plantBomb(map, playerX, playerY, bombLoc, bombTimer, 5-bomb);
		
		if ((clock()%5) == 0) monsterMove(map, monsterLoc, monsterCount);
		
		if (fireCounter > 0) fireCounter -= clearFire(map, fireLoc, fireTimer);
		
		if (bomb < 5)
		{
			int x = explodeBomb(map, bombLoc, bombTimer, radius, fireLoc, fireTimer, fireCounter);
			if (x > 0)
			{
				bomb++;
				fireCounter += x;
			}			
		}
		
	} while(alive && monsterCount > 0);
}

int monsterAlive(int map[23][11], int monsterLoc[][2], int monsterCount)
{
	int syc = 0;
	
	for (int i=0; i<monsterCount; i++)
	{
		if (map[monsterLoc[i][0]][monsterLoc[i][1]] == -1)
		{
			monsterLoc[i][0] = monsterLoc[monsterCount-1][0];
			monsterLoc[i][1] = monsterLoc[monsterCount-1][1];
			monsterLoc[monsterCount-1][0] = 66; monsterLoc[monsterCount-1][1] = 66;
			syc++;
		}
	}
	
	return syc;
}

void monsterMove(int map[23][11], int monsterLoc[][2], int monsterCount)
{

	for (int i=0; i<monsterCount; i++)
	{	
		int r1 = rand()%4;
		if (r1 == 0 && moveUp(map, monsterLoc[i][0], monsterLoc[i][1]) && map[monsterLoc[i][0]][monsterLoc[i][1]-1] != -2)
		{
			map[monsterLoc[i][0]][monsterLoc[i][1]-1] = map[monsterLoc[i][0]][monsterLoc[i][1]];
			map[monsterLoc[i][0]][monsterLoc[i][1]] = 0;
			monsterLoc[i][1]--;
		}
		else if (r1 == 1 && moveLeft(map, monsterLoc[i][0], monsterLoc[i][1]) && map[monsterLoc[i][0]-1][monsterLoc[i][1]] != -2)
		{
			map[monsterLoc[i][0]-1][monsterLoc[i][1]] = map[monsterLoc[i][0]][monsterLoc[i][1]];
			map[monsterLoc[i][0]][monsterLoc[i][1]] = 0;
			monsterLoc[i][0]--;
		}
		else if (r1 == 2 && moveDown(map, monsterLoc[i][0], monsterLoc[i][1]) && map[monsterLoc[i][0]][monsterLoc[i][1]+1] != -2)
		{
			map[monsterLoc[i][0]][monsterLoc[i][1]+1] = map[monsterLoc[i][0]][monsterLoc[i][1]];
			map[monsterLoc[i][0]][monsterLoc[i][1]] = 0;
			monsterLoc[i][1]++;
		}
		else if (moveRight(map, monsterLoc[i][0], monsterLoc[i][1]) && map[monsterLoc[i][0]+1][monsterLoc[i][1]] != -2)
		{
			map[monsterLoc[i][0]+1][monsterLoc[i][1]] = map[monsterLoc[i][0]][monsterLoc[i][1]];;
			map[monsterLoc[i][0]][monsterLoc[i][1]] = 0;
			monsterLoc[i][0]++;
		}
	}
}

void createMonster(int map[23][11], int monsterLoc[][2], int monsterCount)
{
	int syc = 0;
	srand(time(NULL));
	while (syc < monsterCount)
	{
		int r1 = rand()%23;
		int r2 = rand()%9;
		if (map[r1][r2] == 0)
		{
			map[r1][r2] = -2;
			monsterLoc[syc][0] = r1;
			monsterLoc[syc][1] = r2;
			syc++;
		}
	}
}

bool isAlive(int map[23][11], int pX, int pY)
{
	bool tf = true;
	
	if (map[pX][pY] < 0)
	{
		tf = false;
	}
	
	return tf;
}

int clearFire(int map[23][11], int fireLoc[50][2], int fireTimer[50])
{
	int tf = 0;
	
	while (fireTimer[0] != 0 && fireTimer[0] + 500 < clock())
	{
		map[fireLoc[0][0]][fireLoc[0][1]] = 0;
		
		for (int i=0; i<49; i++)
		{
			fireTimer[i] = fireTimer[i+1];
			
			for (int j=0; j<2; j++)
			{
				fireLoc[i][0] = fireLoc[i+1][0];
				fireLoc[i][1] = fireLoc[i+1][1];
			}
		}
		
		tf++;
	}
	
	return tf;
}

int createFire(int map[23][11], int x, int y, int radius, int fireLoc[50][2], int fireTimer[50], int fireCounter)
{
	map[x][y] = -1;
	fireLoc[fireCounter][0] = x; fireLoc[fireCounter][1] = y;
	fireTimer[fireCounter] = clock();
	fireCounter++;
	
	int syc2 = 1;
	bool tf;
	
	//yukarý
	int syc = 0; tf = true;
	while (map[x][y-1-syc] != 9 && -1 < y-1-syc && syc < radius && tf)
	{
		if (map[x][y-1-syc] == 8) tf = false;
		map[x][y-1-syc] = -1;
		syc++; syc2++;
		fireLoc[fireCounter][0] = x; fireLoc[fireCounter][1] = y-syc;
		fireTimer[fireCounter] = clock();
		fireCounter++;
	}
	//sol
	syc = 0; tf = true;
	while (map[x-1-syc][y] != 9 && -1 < x-1-syc && syc < radius && tf)
	{
		if (map[x-1-syc][y] == 8) tf = false;
		map[x-1-syc][y] = -1;
		syc++; syc2++;
		fireLoc[fireCounter][0] = x-syc; fireLoc[fireCounter][1] = y;
		fireTimer[fireCounter] = clock();
		fireCounter++;
	}
	//aþaðý
	syc = 0; tf = true;
	while (map[x][y+1+syc] != 9 && y+1+syc < 11 && syc < radius && tf)
	{
		if (map[x][y+1+syc] == 8) tf = false;
		map[x][y+1+syc] = -1;
		syc++; syc2++;
		fireLoc[fireCounter][0] = x; fireLoc[fireCounter][1] = y+syc;
		fireTimer[fireCounter] = clock();
		fireCounter++;
	}
	//saða
	syc = 0; tf = true;
	while (map[x+1+syc][y] != 9 && x+1+syc < 23 && syc < radius && tf)
	{
		if (map[x+1+syc][y] == 8) tf = false;
		map[x+1+syc][y] = -1;
		syc++; syc2++;
		fireLoc[fireCounter][0] = x+syc; fireLoc[fireCounter][1] = y;
		fireTimer[fireCounter] = clock();
		fireCounter++;
	}
	
	return syc2;
}

int explodeBomb(int map[23][11], int bombLoc[5][2], int bombTimer[5], int radius, int fireLoc[50][2], int fireTimer[50], int fireCounter)
{
	int rv = 0;
	
	if (bombTimer[0] + 2000 < clock() || map[bombLoc[0][0]][bombLoc[0][1]] == -1)
	{
		map[bombLoc[0][0]][bombLoc[0][1]] = 0;
		rv = createFire(map, bombLoc[0][0], bombLoc[0][1], radius, fireLoc, fireTimer, fireCounter);
		
		for (int i=0; i<5; i++)
		{
			bombTimer[i] = bombTimer[i+1];
			
			for (int j=0; j<2; j++)
			{
				bombLoc[i][0] = bombLoc[i+1][0];
				bombLoc[i][1] = bombLoc[i+1][1];
			}
		}
	}
	
	return rv;
}

bool plantBomb(int map[23][11], int pX, int pY, int bombLoc[5][2], int bombTimer[5], int bomb)
{
	bool tf = false;
	
	if (bomb < 5 && map[pX][pY] == 0)
	{
		map[pX][pY] = 7;
		
		bombLoc[bomb][0] = pX;
		bombLoc[bomb][1] = pY;
		
		bombTimer[bomb] = clock();
		
		tf = true;	
	}
	
	return tf;
}

bool moveUp(int map[23][11], int pX, int pY)
{
	bool tf = false;
	
	if (map[pX][pY-1] <= 0 && pY > 0)
	{
		tf = true;
	}
	
	return tf;
}

bool moveLeft(int map[23][11], int pX, int pY)
{
	bool tf = false;
	
	if (map[pX-1][pY] <= 0 && pX > 0)
	{
		tf = true;
	}
	
	return tf;
}

bool moveDown(int map[23][11], int pX, int pY)
{
	bool tf = false;
	
	if (map[pX][pY+1] <= 0 && pY < 10)
	{
		tf = true;
	}
	
	return tf;
}

bool moveRight(int map[23][11], int pX, int pY)
{
	int tf = false;
	
	if (map[pX+1][pY] <= 0 && pX < 22)
	{
		tf = true;
	}
	
	return tf;
}

void loadMap(int map[23][11])
{
	for (int i=0; i<5; i++)
	{
		for (int j=0; j<23; j++)
		{
			map[j][i] = 8;	
		}	
	}
	srand(time(NULL));
	for (int i=0; i<11; i++)
	{
		for (int j=0; j<23; j++)
		{
			int r1 = rand()%23;
			int r2 = rand()%11;
			
			int tmp = map[r1][r2];
			map[r1][r2] = map[j][i];
			map[j][i] = tmp;
		}
	}
	for (int i=1; i<11; i=i+2)
	{
		for (int j=1; j<23; j=j+2)
		{
			map[j][i] = 9;
		}
	}
	map[0][10] = 0; map[0][9] = 0; map[1][10] = 0;
}

void screen(int map[23][11], int pX, int pY)
{
	system("CLS");
	
	for (int i=0; i<25; i++)
		printf("%c%c", 219, 219);
		
	printf("\n");
	for (int i=0; i<11; i++)
	{
		printf("%c%c", 219, 219);
		for (int j=0; j<23; j++)
		{
			if (map[j][i] == 9) printf("%c%c", 219, 219);
			else if (map[j][i] == 8) printf("%c%c", 177, 177);
			else if (map[j][i] == -1) printf("**");
			else if (map[j][i] == -2) printf("!!");
			else if (j == pX && i == pY) printf("<>");
			else if (map[j][i] == 7) printf("()");
			else printf("  ");
		}
		printf("%c%c\n", 219,219);
	}
	
	for (int i=0; i<25; i++)
		printf("%c%c", 219, 219);
}

char keyboardHit(unsigned int time)
{
	char key;
	clock_t goal;
	goal = time + clock();
	
	while (clock() < goal)
	{
		while (kbhit())
		{
			key = getch();
		}
	}
	
	return key;
}

void delay(unsigned int time)
{
	clock_t goal;
	goal = time + clock();
	while (clock() < goal);
}
