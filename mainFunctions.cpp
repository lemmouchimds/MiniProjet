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

//typedef parcelle** carte;

struct pixel
{
	int x;
	int y;
	int nature;
};

typedef pixel parcelle;

struct objet 
{
	parcelle val;
	objet* suiv;
};

/*
//déclaration de la File
typedef parcelle Telm;
typedef struct Element* EFile;
typedef struct Element { Telm  Val; EFile Suiv; } CelluleF;
typedef struct { EFile Tete, Queue; } File;

////primitives des Files
//procedure Initfile
void Initfile(File* F)
{
	(*F).Tete = NULL; (*F).Queue = NULL;
}

//procedure Enfiler
void Enfiler(File* F, Telm x)
{
	EFile V;
	V = (EFile)malloc(sizeof(CelluleF));
	V->Val = x;
	V->Suiv = NULL;
	if ((*F).Tete == NULL) (*F).Tete = V; //la file est vide
	else (*F).Queue->Suiv = V;
	(*F).Queue = V;
}

//procedure Defiler
void Defiler(File* F, Telm* x)
{
	EFile V;
	V = (*F).Tete;
	*x = V->Val; //ou  *x=(*F).Tete->Val;
	if ((*F).Tete == (*F).Queue) { (*F).Tete = NULL; (*F).Queue = NULL; }
	else (*F).Tete = (*F).Tete->Suiv; // ou  (*F).Tete=V->Suiv;
	free(V);
}

//Fonction Filevide
int Filevide(File F)
{
	if (F.Tete == NULL) return 1;
	else return 0;
}

//Fonction Tetefile
Telm Tetefile(File F)
{
	return F.Tete->Val;
}
*/

struct theme
{
	//File f;
	int nature;
};

void afficheCarte(parcelle** c, int n, int m)
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

void creationCarte(parcelle** c, int n, int m)
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
					
					int random = (rand() % 4) + 1;
					c[i][j].nature = random;
					doubleX = TRUE;
				}
				else
				{
					c[i][j].nature = c[i][j - 1].nature;

					doubleX = FALSE;
				}
					c[i][j].x = i;
					c[i][j].y = j;
			}

			doubleY = TRUE;
		}
		else
		{

			for (int j = 0; j < m; j++)
			{
				c[i][j].x = i;
				c[i][j].y = j;
				c[i][j].nature = c[i - 1][j].nature;
			}
			doubleY = FALSE;
		}

	}
}

void creationTEST(int** c, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			c[i][j] = (rand() % 4) + 1;
		}
	}
}

int main()
{	
	srand(0);
	int n = 10;
	int m = 10;

	parcelle** c = (parcelle**)malloc(sizeof(parcelle*) * m);
	
	for (int i = 0; i < m; i++)
	{
		c[i] = (parcelle*)malloc(sizeof(parcelle) * n);

	}

	//creationTEST(c1, n, m);
	creationCarte(c, n, m);
	afficheCarte(c, n, m);

	return 0;


}