#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include "mainFunctions.h"

#pragma region Definition

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

struct objet 
{
	parcelle val;
	objet* suiv;
};

#pragma endregion

#pragma region File

//déclaration de la File
//typedef parcelle Telm;
typedef objet Telm;
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

#pragma endregion

struct themeParcelle
{
	File f;
	int nature;
};

struct theme {
	File* objets;
	int nature;
};

typedef parcelle** carte;

BOOL parcelleEqual(parcelle p1, parcelle p2)
{
	return p1.nature == p2.nature &&
		p1.x == p2.x &&
		p1.y == p2.y;

}

void creationCarte(carte c, int n, int m)
{
	BOOL doubleY = FALSE;


	for (int i = 0; i < n; i++)
	{
		BOOL doubleX = FALSE;
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

objet* extraireObjet(parcelle** c, parcelle p, int n, int m, int nature)
{
	if (p.x > n || p.y > m || p.nature != nature)
	{
		return NULL;
	}

	objet* result = (objet*)malloc(sizeof(objet));
	result->val = p;
	
	if (p.x + 1 < n)
	{
		parcelle pDroit;
		pDroit.nature = c[p.x + 1][p.y].nature;
		pDroit.x = p.x + 1;
		pDroit.y = p.y;
		result->suiv = extraireObjet(c, pDroit, n, m, nature);
		
	}

	objet* temp = result;


	while (temp->suiv)
	{
		temp = temp->suiv;
	}

	if (p.y + 1 < m)
	{
		parcelle pBas;
		pBas.nature = c[p.x][p.y + 1].nature;
		pBas.x = p.x;
		pBas.y = p.y + 1;
		temp->suiv = extraireObjet(c, pBas, n, m, nature);
	}

	return result;
}

BOOL existInObjet(objet* o, parcelle p)
{
	objet* temp = o;

	while (temp)
	{
		if (temp->val.nature == p.nature &&
			temp->val.x == p.x &&
			temp->val.y == p.y
			)
		{
			return TRUE;
		}

		temp = temp->suiv;

	}

	return FALSE;
}

carte creationCarteObjet(objet* o, int n, int m)
{
	parcelle** c = (parcelle**)malloc(sizeof(parcelle*) * m);

	for (int i = 0; i < m; i++)
	{
		c[i] = (parcelle*)malloc(sizeof(parcelle) * n);

	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			c[i][j].nature = 0;
			c[i][j].x = i;
			c[i][j].y = j;
		}
	}


	objet* temp = o;

	while (temp->suiv)
	{
		c[temp->val.x][temp->val.y].nature = temp->val.nature;
		temp = temp->suiv;
	}

	return c;
}

void afficheObjet(objet o, int n, int m)
{
	carte c = creationCarteObjet(&o, n, m);
	afficheCarte(c, n, m);
}

BOOL existInTheme(theme* t, parcelle p)
{
	BOOL result = FALSE;

	File* f;
	Initfile(f);

	objet* temp = NULL;
	objet* temp2 = NULL;

	while (!Filevide(*(t->objets)))
	{
		Defiler(t->objets, temp);
		temp2 = temp;

		while (temp2 && !result)
		{
			if (parcelleEqual(temp2->val, p))
			{
				result = TRUE;
			}
		}

		Enfiler(f, *temp);
	}

	while (!Filevide(*f))
	{
		Defiler(f, temp);
		Enfiler(t->objets, *temp);
	}

	return result;
}

void extraireTheme(carte c, theme* t, int n, int m, int nature)
{

	Initfile(t->objets);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (c[i][j].nature == nature)
			{
				if (!existInTheme(t, c[i][j]))
				{
					objet* temp = extraireObjet(c, c[i][j], n, m, nature);
					Enfiler(t->objets, *temp);
				}

			}
		}
	}
}

carte creationCarteTheme(theme t, int n , int m)
{
	parcelle** c = (parcelle**)malloc(sizeof(parcelle*) * m);

	for (int i = 0; i < m; i++)
	{
		c[i] = (parcelle*)malloc(sizeof(parcelle) * n);

	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			c[i][j].nature = 0;
			c[i][j].x = i;
			c[i][j].y = j;
		}
	}

	File* f = t.objets;
	while (!Filevide(*f))
	{
		objet* temp;
		Defiler(f, temp);

		while (temp)
		{
			parcelle x = temp->val;
			c[x.x][x.y].nature = x.nature;

			temp = temp->suiv;

		}

	}

	return c;
}

void afficheTheme(themeParcelle t, int n, int m)
{
	carte c = creationCarteTheme(t, n, m);
	afficheCarte(c, n, m);
}

void extraireTheme(carte c, themeParcelle* t, int n, int m, int nature)
{
	Initfile(&(t->f));

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (c[i][j].nature == nature)
			{
				Enfiler(&(t->f), c[i][j]);
			}
		}
	}

}

int main()
{	
	srand(time(0));
	int n = 11;
	int m = 11;

	parcelle** c = (parcelle**)malloc(sizeof(parcelle*) * m);
	
	for (int i = 0; i < m; i++)
	{
		c[i] = (parcelle*)malloc(sizeof(parcelle) * n);

	}

	//creationTEST(c1, n, m);
	creationCarte(c, n, m);
	afficheCarte(c, n, m);

	printf("\n");

	/*themeParcelle* t1 = (themeParcelle*)malloc(sizeof(themeParcelle));
	extraireTheme(c, t1, n, m, 2);
	afficheTheme(*t1, n, m);*/

	parcelle p;
	p.nature = 1;
	p.x = 0;
	p.y = 0;

	objet* o = (objet*)malloc(sizeof(objet));
	o = extraireObjet(c, p, n, m, 1);
	afficheObjet(*o, n, m);


	return 0;


}