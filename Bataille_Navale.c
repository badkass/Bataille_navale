#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define TMAX 11
#define WIN 17
#define Saut printf("\n");
#define TAILLE_MAX 2000

void initTab(char Att[TMAX][TMAX], char Boat[TMAX][TMAX]);
void AffTab(char Att[TMAX][TMAX], char Boat[TMAX][TMAX]);
void FillBateauJ1(char BateauJ1[TMAX][TMAX]);
void FillBateauJ2(char BateauJ2[TMAX][TMAX]);
void Mecanique(char AttaqueJ1[TMAX][TMAX], char BateauJ1[TMAX][TMAX], char AttaqueJ2[TMAX][TMAX], char BateauJ2[TMAX][TMAX]);
int Win(int toucheJ1, int toucheJ2);
void Regle();

void Jeu();
void Menu();

int main(int argc, char const *argv[])
{
	Menu();//affichage du menu
	return 0;
}

void Menu()
{
	system("cls");//nettoyage de la console
	int choix = 0;
	printf("       BIENVENUE !  \n");
	Saut
	printf("Que voulez-vous faire ?\n");
	Saut
	printf("1. Jouer\n");
	printf("2. Regle\n");
	printf("3. Quitter\n");
	scanf("%d", &choix); fflush(stdin);
	switch(choix)
	{
		case 1: Jeu();//lancement du jeu
			break;
		case 2: Regle();//ouverture du fichier externe affichant les règles
			break;
		case 3: system("exit");//fermeture du programme
			break;
	}
}


void Jeu()
{
	char AttaqueJ1[TMAX][TMAX], BateauJ1[TMAX][TMAX];
	char AttaqueJ2[TMAX][TMAX], BateauJ2[TMAX][TMAX];

	initTab(AttaqueJ1, BateauJ1);//initialisation tableau du joueur 1
	FillBateauJ1(BateauJ1);

	initTab(AttaqueJ2, BateauJ2);//initialisation tableau du joueur 2
	FillBateauJ2(BateauJ2);

	Mecanique(AttaqueJ1, BateauJ1, AttaqueJ2, BateauJ2);


}

void Regle()
{
	system("cls");
	char chaineRegle[TAILLE_MAX] = "";
	FILE *regle = NULL;

	regle = fopen("Regle.txt", "r");
	if (regle != NULL)
	{
        while (fgets(chaineRegle, TAILLE_MAX, regle) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur
        {
            printf("%s", chaineRegle); // On affiche la chaîne
            Saut
        }

		fclose(regle);//on ferme le fichier
	}
}

void Mecanique(char AttaqueJ1[TMAX][TMAX], char BateauJ1[TMAX][TMAX], char AttaqueJ2[TMAX][TMAX], char BateauJ2[TMAX][TMAX])
{
	int i, j, tour = 1, toucheJ1 = 0, toucheJ2 = 0;
	char tir = 'x', miss = 'o';

	while (tour != 2 || toucheJ1 != WIN)
	{
		system("cls");
		AffTab(AttaqueJ1, BateauJ1);
		Saut

		printf("Joueur 1, c'est a vous\n");
		Saut
		printf("Nombre de touches %d\n", toucheJ1);//on affiche le nombre de fois que le joueur à touché un bateau
		printf("Choisissez une ligne entre 1 et 10\n");
		scanf("%d", &i); fflush(stdin);
		if (i < TMAX && i > 0)
		{
			Saut
			printf("Choisissez une colonne entre 1 et 10\n");
			scanf("%d", &j);
			fflush(stdin);

			if ((AttaqueJ1[i][j] == '-') && (BateauJ2[i][j] == '0')) //Tir vrai
			{
				AttaqueJ1[i][j] = tir;
				BateauJ2[i][j] = tir;
				toucheJ1++;
			}
			if ((AttaqueJ1[i][j] == '-') && (BateauJ2[i][j] == '-')) //Tir faux
			{
				AttaqueJ1[i][j] = miss;
				tour = 2;
			}
		} else{
			printf("Entre une valeur correct\n");//si le joueur rentre une valeur non incluse dans le tableau
		}
		if (toucheJ1 == WIN)
		{

			system("cls");
			AffTab(AttaqueJ1, BateauJ1);
			Saut

			Win(toucheJ1, toucheJ2); //Message de victoire
			exit(0); //Quitte le programme
		}
	}
	while (tour != 1 || toucheJ2 != WIN)
	{
		system("cls");

		AffTab(AttaqueJ2, BateauJ2);
		Saut
		printf("Joueur 2, c'est a vous\n");
		Saut
		printf("Nombre de touches %d\n", toucheJ2);
		printf("Choisissez une ligne entre 1 et 10\n");
		scanf("%d", &i);
		fflush(stdin);
		if (i < TMAX && i > 0)
		{
			Saut
			printf("Choisissez une colonne entre 1 et 10\n");
			scanf("%d", &j);
			fflush(stdin);

			if ((AttaqueJ2[i][j] == '-') && (BateauJ1[i][j] == '0')) //Tir vrai
			{
				AttaqueJ2[i][j] = tir;
				BateauJ1[i][j] = tir;
				toucheJ2++;
			}
			if ((AttaqueJ2[i][j] == '-') && (BateauJ1[i][j] == '-')) //Tir faux
			{
				AttaqueJ2[i][j] = miss;
				tour = 1;
			}
		} else{
			printf("Entrez une valeur correct\n");//si le joueur rentre une valeur non incluse dans le tableau
		}
		if (toucheJ2 == WIN)
		{

			system("cls");
			AffTab(AttaqueJ2, BateauJ2);
			Saut

			Win(toucheJ1, toucheJ2); //Message de victoire
			exit(0);//Quitte le programme
		}
	}
}

void initTab(char Att[TMAX][TMAX], char Boat[TMAX][TMAX]) //initialisation du tableau et bateaux
{
	int i, j;

	//Grille des cibles
	Att[0][0] = 'X';
	Att[0][1] = '1';
	Att[0][2] = '2';
	Att[0][3] = '3';
	Att[0][4] = '4';
	Att[0][5] = '5';
	Att[0][6] = '6';
	Att[0][7] = '7';
	Att[0][8] = '8';
	Att[0][9] = '9';
	Att[0][10] = '0';

	Att[0][0] = 'X';
	Att[1][0] = 'A';
	Att[2][0] = 'B';
	Att[3][0] = 'C';
	Att[4][0] = 'D';
	Att[5][0] = 'E';
	Att[6][0] = 'F';
	Att[7][0] = 'G';
	Att[8][0] = 'H';
	Att[9][0] = 'I';
	Att[10][0] = 'J';

	//Grille des bateaux
	Boat[0][0] = 'X';
	Boat[0][1] = '1';
	Boat[0][2] = '2';
	Boat[0][3] = '3';
	Boat[0][4] = '4';
	Boat[0][5] = '5';
	Boat[0][6] = '6';
	Boat[0][7] = '7';
	Boat[0][8] = '8';
	Boat[0][9] = '9';
	Boat[0][10] = '0';

	Boat[0][0] = 'X';
	Boat[1][0] = 'A';
	Boat[2][0] = 'B';
	Boat[3][0] = 'C';
	Boat[4][0] = 'D';
	Boat[5][0] = 'E';
	Boat[6][0] = 'F';
	Boat[7][0] = 'G';
	Boat[8][0] = 'H';
	Boat[9][0] = 'I';
	Boat[10][0] = 'J';

	for (i = 1; i< TMAX; i++) //Init grille des cibles
	{
		for (j = 1; j< TMAX; j++)
		{
			Att[i][j] = '-';
		}
	}

	for (i = 1; i < TMAX; i++) // Init grille des bateaux
	{
		for (j = 1; j < TMAX; j++)
		{
			Boat[i][j] = '-';
		}
	}
}

void AffTab(char Att[TMAX][TMAX], char Boat[TMAX][TMAX])
{
	int i, j;
	printf("Grille des cibles\n");
	for (i = 0; i < TMAX; i++)
	{
		printf("|");
		for (j = 0; j < TMAX; j++)
		{
			printf("%c", Att[i][j]);
			printf("|");
		}
		Saut
	}

	Saut

	printf("Grille de vos bateaux\n");
	for (i = 0; i < TMAX; i++)
	{
		printf("|");
		for (j = 0; j < TMAX; j++)
		{
			printf("%c", Boat[i][j]);
			printf("|");
		}
		Saut
	}
}

void FillBateauJ1(char BateauJ1[TMAX][TMAX]) //Remplissage bateaux J1
{
	BateauJ1[2][2] = '0';
	BateauJ1[3][2] = '0';
	BateauJ1[4][2] = '0';	//bateau 5 cases
	BateauJ1[5][2] = '0';
	BateauJ1[6][2] = '0';

	BateauJ1[5][8] = '0';
	BateauJ1[6][8] = '0';	//bateau 4 cases
	BateauJ1[7][8] = '0';
	BateauJ1[8][8] = '0';

	BateauJ1[4][4] = '0';
	BateauJ1[4][5] = '0';	//bateau 3 cases 1
	BateauJ1[4][6] = '0';

	BateauJ1[2][7] = '0';
	BateauJ1[2][8] = '0';	//bateau 3 cases 2
	BateauJ1[2][9] = '0';

	BateauJ1[9][3] = '0';	//bateau 2 cases
	BateauJ1[9][4] = '0';
}

void FillBateauJ2(char BateauJ2[TMAX][TMAX]) //Remplissage bateaux joueur 2
{
	BateauJ2[2][2] = '0';
	BateauJ2[2][3] = '0';
	BateauJ2[2][4] = '0';	//bateau 5 cases
	BateauJ2[2][5] = '0';
	BateauJ2[2][6] = '0';

	BateauJ2[6][3] = '0';
	BateauJ2[6][4] = '0';	//bateau 4 cases
	BateauJ2[6][5] = '0';
	BateauJ2[6][6] = '0';

	BateauJ2[2][8] = '0';
	BateauJ2[3][8] = '0';	//bateau 3 cases 1
	BateauJ2[4][8] = '0';

	BateauJ2[3][10] = '0';
	BateauJ2[4][10] = '0';	//bateau 3 cases 2
	BateauJ2[5][10] = '0';

	BateauJ2[8][5] = '0';	//bateau 2 cases
	BateauJ2[8][6] = '0';
}

int Win(int toucheJ1, int toucheJ2)//condition de victoire
{
	if (toucheJ1 == WIN) //victoire du joueur 1
	{
		printf("Felicitations Joueur 1\n");
	}
	if(toucheJ2 == WIN) //victoire du joueur 2
	{
		printf("Felicitations Joueur 2\n");
	}
}
