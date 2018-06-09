#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void checkZero(int, int);
void openZero(int);

int a[15][15];
int b[15][15];
int sayac;

int main()
{
    int n=15, m=15;
    int temp, rand1, rand2;
    int gameOver=0;
    int x, y, tmp;
    
    int cursorX=0, cursorY=0;
    
    //0 la doldur
    for (int i=0 ; i<m ; i++)
    {
        for (int j=0 ; j<n ; j++)
        {
            a[i][j] = 0;
            b[i][j] = 0;
        }
    }
    
    //mayin olustur
    for (int i=1 ; i<3 ; i++)
    {
        for (int j=0 ; j<n ; j++)
        {
            a[j][i] = 9;
        }
    }
    
    srand(time(NULL));
    //mayinlari karistir
    for (int i=0 ; i<m ; i++)
    {
        for (int j=0 ; j<n ; j++)
        {
            rand1 = rand()%10 + 1;
            rand2 = rand()%10 + 1;
            temp = a[j][i];
            a[j][i] = a[rand1][rand2];
            a[rand1][rand2] = temp;
        }
    }
    
    //sayilari belirle
    for (int i=0 ; i<m ; i++)
    {
        for (int j=0 ; j<n ; j++)
        {
            //i ve j nin etrafindakilere bak
            if (a[j][i] != 9)
            {
                sayac = 0;
                for (int k=j-1 ; k<j+2 ; k++)
                {
                    for (int l=i-1 ; l<i+2 ; l++)
                    {
                        if (k>-1 && k<n)
                        {
                            if (l>-1 && l<m)
                            {
                                if (a[k][l] == 9)
                                {
                                    sayac++;
                                } 
                            }
                        }
                    }
                }
                a[j][i] = sayac;
            }
            
        }
    }
    
    //0 in komsularini bul
    sayac = 2;
    for (int i=0 ; i<m ; i++)
        {
            for (int j=0 ; j<n ; j++)
            {
                if (a[j][i] == 0 && b[j][i] == 0)
                {
                    b[j][i] = sayac;
                    checkZero(i,j);
                    sayac++;
                }
            }
        }
    
    do
    {
        //ekrana yazdir
        system("CLS");
        for (int i=0 ; i<m ; i++)
        {
            for (int j=0 ; j<n ; j++)
            {
                
				if (b[j][i] == 1 && a[j][i] == 0) printf("  ");
				else if (b[j][i] == 1) printf("%d " , a[j][i]);
				else printf("* ");
            }
            printf("\n");
        }
        
        //secim yap
        printf("X: "); scanf("%d" , &x);
        printf("Y: "); scanf("%d" , &y);
        
        //secim yapilan yeri ac
        if (x>-1 && x<n)
        {
            if (y>-1 && x<m)
            {
                if (a[x][y] == 9 && b[x][y] == 0)
                {
                    gameOver = 1;
                    b[x][y] = 1;
                }
                else if (a[x][y]==0 && b[x][y] != 1)
                {
                    tmp = b[x][y];
                    openZero(tmp);
                }
                else
                {
                    b[x][y] = 1;
                }
            }
        }
    } while(gameOver == 0);
    
    
    return 0;
}

void checkZero(int x, int y)
{
    for (int i=x-1; i<x+2; i++)
    {
        for (int j=y-1; j<y+2; j++)
        {
            if (i<15 && i>-1)
            {
                if (j<15 && j>-1)
                {
                    if (a[j][i]==0 && b[j][i]==0)
                    {
                        b[j][i] = sayac;
                        checkZero(i,j);
                    }
                }
            }
        }
    }
}

void openZero(int x)
{
    for (int i=0; i<15; i++)
    {
        for (int j=0; j<15; j++)
        {
            if (b[j][i] == x)
            {
            	b[j][i] = 1;
                for (int k=i-1; k<i+2; k++)
                {
                    for (int l=j-1; l<j+2; l++)
                    {
                        if (k>-1 && k<15)
                        {
                            if (l>-1 && l<15)
                            {
                            	if (b[l][k] == 0) b[l][k] = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}
