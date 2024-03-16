#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//eux jsp pk ils sont la askip ils m'aident a faire les clearscreen sous linux
#include <unistd.h>
#ifdef _WIN32
#define CLEAR "cls"
#else 
#define CLEAR "clear"
#endif

//declaration d'une personne
struct personne
{
	char nom[50];
	int points;
	int nombreChoisi ;
	int estElimine;
};


//code principal
int main( )
{ 
	char rejouer;
	do {
		system(CLEAR); // Efface l'écran
		printf("\nJEU DE  DEVINETTE \n-------------------\n ");
		printf("REGLES et OBJETIFS DU JEU\n--------------------\n");
		printf("N°1- Au debut du jeu le(s) joueur(s) ont 100 points , a chaques mauvaises reponses 10 points sont perdus\nN°2- Pour le mode Multi chaques joueurs joue a tour de role , une fois le nombre trouvé le jeu s'arrete");
		printf("\n");
		printf("\n\nappuyez sur 1 pour jouer solo et sur 2 pour jouer multijoueurs : ");
		char choix ;
		do {
			scanf(" %c",&choix);
			if (choix != '1' && choix != '2') {
				printf("Choix invalide. Veuillez appuyer sur 1 pour jouer solo et sur 2 pour jouer multijoueurs : ");
			}
		} while (choix != '1' && choix != '2');
		//les 2 lignes qui suivent sont la pour créer un nombre aléartoir
		srand(time(NULL));
		int nombre = rand() % 101 ;
		int nombrechoisi ;
		switch (choix)
		{
		//mode solo
		case '1':
			system(CLEAR); // Efface l'écran
			printf("\nJEU DE  DEVINETTE \n-------------------\n\n ");
			struct personne joueur ;
			printf("veuillez entrer votre nom :");
			scanf("%s",joueur.nom);
			joueur.points= 100 ;
			do
			{	
				printf("entre ton nombre : ");
				do {
					scanf("%d",&nombrechoisi);
					//petit control de saisi
					if (nombrechoisi < 0 || nombrechoisi > 100) {
						printf("Nombre invalide. Veuillez entrer un nombre entre 0 et 100 : ");
					}
				} while (nombrechoisi < 0 || nombrechoisi > 100);
				//indiations et penalisations
				if (nombrechoisi > nombre) {printf("‘Plus petit ! Toi aussi va doucement.\n’");joueur.points -= 10 ;}
				else if (nombrechoisi < nombre) {printf("Plus grand ! Fait un effort tu peux y arriver\n");joueur.points -= 10 ;}
				else if (nombrechoisi == nombre) printf("%s tu as trouvé le nombre secret a la tentative N°%d !",joueur.nom , (100-joueur.points)/10 +1);
				else {printf("tu as entrer un truc chelou\n");joueur.points -= 10 ;}
			} while (nombrechoisi != nombre);
			break;
		//mode multi
		case '2':
			system(CLEAR);
			printf("\nJEU DE  DEVINETTE \n-------------------\n\n ");

			printf("COMBIEN IL Y A T'IL DE JOUEUR ?\n");
			int nombreJoueurs ;
			printf("veuillez saisir le nombre de joueurs : ");
			scanf("%d",&nombreJoueurs); 
			struct personne joueurs[nombreJoueurs] ;
			for (int i=0 ; i<nombreJoueurs ; i++)
			{	
				printf("joueur N°%d",i+1);
				joueurs[i].points= 100 ;
				joueurs[i].estElimine = 0;
				printf("veuillez entrer votre nom :");
				scanf("%s", joueurs[i].nom); 
			}
			system(CLEAR);
			printf("\nJEU DE  DEVINETTE \n-------------------\n\n ");
			int i;
			int trouvé=0;
			char gagnant[50];
			do 
			{ 
				for(i=0 ; i<nombreJoueurs ; i++)
				{ 
					//je verifi si les points ne sont pas egaux a 0 et je le saute si cest le cas
					if(joueurs[i].points <= 0 && joueurs[i].estElimine == 0) {
						printf("%s a été éliminé du jeu car ses points sont égaux à 0\n", joueurs[i].nom);
						joueurs[i].estElimine = 1;
						continue;
					}
					if(joueurs[i].estElimine == 1) {
						continue;
					}
					printf("\nTOUR DE %s \n----------",joueurs[i].nom);
					printf("\nentre ton nombre : ");
					do {
						scanf("%d",&joueurs[i].nombreChoisi);
						if (joueurs[i].nombreChoisi < 0 || joueurs[i].nombreChoisi > 100) {
							printf("Nombre invalide. Veuillez entrer un nombre entre 0 et 100 : ");
						}
					} while (joueurs[i].nombreChoisi < 0 || joueurs[i].nombreChoisi > 100);
				} 
				system(CLEAR);
				for(i=0 ; i<nombreJoueurs ; i++)
				{ 
					if(joueurs[i].estElimine == 1) {
						continue;
					}
					if (joueurs[i].nombreChoisi > nombre) {printf("%s Plus petit ! Toi aussi va doucement.\n’",joueurs[i].nom);joueurs[i].points -= 10 ;}
					else if (joueurs[i].nombreChoisi < nombre) {printf("%s Plus grand ! Fait un effort tu peux y arriver\n",joueurs[i].nom);joueurs[i].points -= 10 ;}
					else if (joueurs[i].nombreChoisi == nombre) {printf("%s as trouvé le nombre secret a la tentative N°%d !",joueurs[i].nom , (100-joueurs[i].points)/10 +1); trouvé=1; strcpy(gagnant,joueurs[i].nom) ; break ;}
					else {printf("tu as entrer un truc chelou\n");joueurs[i].points -= 10 ;}
					if(joueurs[i].points <= 0 && joueurs[i].estElimine == 0) {
						printf("%s a été éliminé du jeu car ses points sont égaux à 0\n", joueurs[i].nom);
						joueurs[i].estElimine = 1;
					}
				}
			} while (trouvé == 0) ;


			// Affichage du tableau des scores
			printf("\n\nTableau des scores :\n");
			for(i=0 ; i<nombreJoueurs ; i++)
			{
				printf("%s : %d points\n", joueurs[i].nom, joueurs[i].points);
			}
			break;
		}
		printf("\nVoulez-vous rejouer ? (O pour oui, N pour non) : ");
		do {
			scanf(" %c", &rejouer);
			if (rejouer != 'O' && rejouer != 'N') {
				printf("Choix invalide. Veuillez appuyer sur O pour oui et N pour non : ");
			}
		} while (rejouer != 'O' && rejouer != 'N');
	} while (rejouer == 'O');




	getchar();
	return 0;
}
