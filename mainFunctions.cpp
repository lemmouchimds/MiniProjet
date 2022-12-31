#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int BOOL;

#define AGRICOLE 1
#define HABITATION 2
#define FORETS 3
#define INDUSTRIELLE 4

#define MAX_TYPES 4

struct pixel
{
	int x;
	int y;
	int nature;
};

typedef pixel parcelle;
typedef parcelle** carte;


struct objet 
{
	parcelle val;
	objet* suiv;
};

struct theme
{
	//file de pixels
};

void afficheCarte(carte c, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", c[i][j].nature);
		}

		printf("\n");

	}
}

void creationCarte(carte* c, int n, int m)
{
	BOOL doubleX = FALSE;
	BOOL doubleY = FALSE;


	for (int i = 0; i < n; i++)
	{
		if (!doubleY)
		{
			for (int j = 0; j < m; j++)
			{
				if (!doubleX)
				{
					c[i][j] = (parcelle*)malloc(sizeof(parcelle));
					/*if (C)
					{
						C->nature = 0;
					}*/
					//(*c[i][j]).nature = 0;//(rand() % 4) + 1;
					doubleX = TRUE;
				}
				else
				{
					c[i][j]->nature = c[i][j - 1]->nature;

					doubleX = FALSE;
				}
					c[i][j]->x = i;
					c[i][j]->y = j;
			}

			doubleY = TRUE;
		}
		else
		{

			for (int j = 0; j < m; j++)
			{
				c[i][j]->x = i;
				c[i][j]->y = j;
				c[i][j]->nature = c[i - 1][j]->nature;
			}
			doubleY = FALSE;
		}

	}
}

int main()
{
	int n = 10;
	int m = 10;

	carte* c = (carte*)malloc(sizeof(carte) * m * n);
	creationCarte(c, n, m);

	afficheCarte(*c, n, m);

	return 0;


}