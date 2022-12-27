#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

#define AGRICOLE 1
#define HABITATION 2
#define FORETS 3
#define INDUSTRIELLE 4

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
