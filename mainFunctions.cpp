#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<Windows.h>
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
	F->Tete = NULL; F->Queue = NULL;
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

void printNature(int nature)
{
	switch (nature)
	{

	case 1:
		printf("Agricole");
		break;
	case 2:
		printf("Habitation");
		break;
	case 3:
		printf("Forets");
		break;
	case 4:
		printf("Industialle");

	default:
		break;
	}
}

#pragma region Carte

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

					int random = (rand() % MAX_TYPES) + 1;
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

	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			SetConsoleTextAttribute(hConsole, c[i][j].nature);


			printf("%d ", c[i][j].nature);
		}


		printf("\n");

	}

	int white = 15;
	SetConsoleTextAttribute(hConsole, white);
}

#pragma endregion

#pragma region Objet

objet* extraireObjet(carte c, parcelle p, int n, int m, int nature)
{
	if (p.x > n || p.y > m || p.nature != nature)
	{
		return NULL;
	}

	objet* result = (objet*)malloc(sizeof(objet));
	result->val = p;
	result->suiv = NULL;

	if (p.x + 1 < n) // aller a droite
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
	if (p.y + 1 < m) // aller en bas
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
		if (parcelleEqual(temp->val, p))
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

	while (temp)
	{
		c[temp->val.x][temp->val.y].nature = temp->val.nature;
		temp = temp->suiv;
	}

	return c;
}

void afficheObjet(objet o, int n, int m)
{
	printf("\n\n---Affichage d'un objet ---\n\n");
	carte c = creationCarteObjet(&o, n, m);
	afficheCarte(c, n, m);
}

#pragma endregion

#pragma region Theme

BOOL existInTheme(theme* t, parcelle p)
{
	BOOL result = FALSE;

	objet* temp = (objet*)malloc(sizeof(objet));
	objet* temp2 = (objet*)malloc(sizeof(objet));

	File* tempFile = t->objets;
	File* f = (File*)malloc(sizeof(File));
	Initfile(f);

	while (!Filevide(*tempFile))
	{
		Defiler(tempFile, temp);
		Enfiler(f, *temp);
		temp2 = temp;

		while (temp2 && !result)
		{
			if (parcelleEqual(temp2->val, p))
			{
				result = TRUE;
			}
			temp2 = temp2->suiv;

		}

	}

	t->objets = f;

	return result;
}

void extraireTheme(carte c, theme* t, int n, int m, int nature)
{
	t->objets = (File*)malloc(sizeof(File));
	t->objets->Tete = NULL; t->objets->Queue = NULL; //initfile(f);
	t->nature = nature;

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

carte creationCarteTheme(theme t, int n, int m)
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
		objet* temp = (objet*)malloc(sizeof(objet));
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

void afficheTheme(theme t, int n, int m)
{
	printf("\n\n---Affichage de theme de la nature ");
	printNature(t.nature);
	printf("--- \n\n");
	carte c = creationCarteTheme(t, n, m);
	afficheCarte(c, n, m);
}

#pragma endregion

#pragma region Stat

int countParcelles(carte c, int n, int m, int nature)
{
	int result = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (c[i][j].nature == nature)
			{
				result++;
			}
		}
	}

	return result;
}

void afficheStat(theme t, int count, int n, int m)
{
	afficheTheme(t, n, m);

	printf("Il y'a %d de parcelle de type ", count);
	printNature(t.nature);

	float surface = n * m;
	
	float pourcentage = ((count / surface) * 100);

	printf("\nCe qui fait %.2f %% de la surface total.\n", pourcentage);
}

void stat(carte c, int n, int m)
{

	printf("\t--- Statistique ---\n");

	theme t[MAX_TYPES];

	for (int i = 1; i <= MAX_TYPES; i++)
	{
		extraireTheme(c, &t[i - 1], n, m, i);

	}

	for (int i = 1; i <= MAX_TYPES; i++)
	{
		int count = countParcelles(c, n, m, t[i - 1].nature);
		afficheStat(t[i - 1], count, n, m);
		printf("\n");
	}

}

#pragma endregion

#pragma region Interface

int choisirFonction()
{
	printf("\n---Vous pouver :---\n");
	printf("1- Cree une carte.\n");
	printf("2- Afficher la carte\n");
	printf("3- Extraire et afficher un objet\n");
	printf("4- Extraire et afficher un theme\n");
	printf("5- Afficher des statistiques\n");
	printf("0- Sortire de l'application\n");

	int respone = -1;
	while (respone < 0 || respone > 5)
	{
		printf("Donner le numero de la fonction : ");
		scanf_s("%d", &respone);
	}

	return respone;
}


void Choix1(parcelle** c, int n, int m)
{
	creationCarte(c, n, m);
	printf("Voici la carte cree :\n");
	afficheCarte(c, n, m);
}

void Choix3(carte c, int n, int m)
{
	printf("Donner la position d'une parcelle :\n");
	int x = -1;
	while (x < 0 || x > n)
	{
		printf("x = ");
		scanf_s("%d", &x);
	}

	int y = -1;
	while (y < 0 || y > n)
	{
		printf("y = ");
		scanf_s("%d", &y);
	}

	parcelle p;
	p.x = x;
	p.y = y;
	p.nature = c[x][y].nature;
	objet* o = (objet*)malloc(sizeof(objet));
	o = extraireObjet(c, p, n, m, p.nature);
	afficheObjet(*o, n, m);
}

void Choix4(carte c, int n, int m)
{
	int nature = -1;
	while (nature < 0 || nature > MAX_TYPES)
	{
		printf("Donner une nature a extraire (entre 1 et %d) : ", MAX_TYPES);
		scanf_s("%d", &nature);
	}
	theme* t = (theme*)malloc(sizeof(theme));
	extraireTheme(c, t, n, m, nature);
	afficheTheme(*t, n, m);
}

void consolInterface()
{
	printf("Bonjour\n");
	int n = 0;
	int m = 0;

	while (n <= 0)
	{
		printf("Donner la taille de la carte : ");
		scanf_s("%d", &n);
	}


	m = n;
	int choix = 0;

	parcelle** c = (parcelle**)malloc(sizeof(parcelle*) * m);

	for (int i = 0; i < m; i++)
	{
		c[i] = (parcelle*)malloc(sizeof(parcelle) * n);

	}

	creationCarte(c, n, m);
	printf("Une carte a ete generer\n\n");

	do
	{
		choix = choisirFonction();
		switch (choix)
		{
			case 1:
				Choix1(c, n, m);
				break;
			case 2:
				afficheCarte(c, n, m);
				break;
			case 3:
				Choix3(c, n, m);
				break;

			case 4:
				Choix4(c, n, m);
				break;
			case 5:
				stat(c, n, m);

			default:
				break;
		}
	} while (choix);


	printf("---Merci !---");

}

#pragma endregion


int main()
{
	srand(time(0));

	consolInterface();
	return 0;


}