#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// m'aident a faire les clearscreen sous linux
#include <unistd.h>
#ifdef _WIN32
#define CLEAR "cls"
#else 
#define CLEAR "clear"
#endif

//declaration d'une personne
typedef struct 
{
	char nom[50];
	int score;
	int nombre_choisi ;
	bool estElimine;
} joueur_t ;


//code principal
void main( )
{ 
	char rejouer;
	do {
		system(CLEAR); // Efface l'écran
		printf("JEU DE  DEVINETTE\n");
		printf("-----------------\n" );
		printf("REGLES et OBJETIFS DU JEU\n");
		printf("--------------------------\n");
		printf("N°1- Au debut du jeu le(s) joueur(s) ont 100 points , a chaques mauvaises reponses 10 points sont perdus\n");
		printf("N°2- Pour le mode Multi chaques joueurs joue a tour de role , une fois le nombre trouvé le jeu s'arrete\n");

		printf("\n\nappuyez sur 1 pour jouer solo et sur 2 pour jouer multijoueurs : ");
		char choix ;

		do {
			scanf("%c",&choix);

			if (choix != '1' && choix != '2') {
				printf("Choix invalide. Veuillez appuyer sur 1 pour jouer solo et sur 2 pour jouer multijoueurs : ");
			}
		} while (choix != '1' && choix != '2');

		//les 2 lignes qui suivent sont la pour créer un nombre aléartoire
		srand(time(NULL));
		int nombre_secret = rand() % 101 ;
		int nombre_choisi ;
		bool premier_essaie = 1 ;


		switch (choix)
		{
		//mode solo
		case '1':
			system(CLEAR); // Efface l'écran
			printf("JEU DE  DEVINETTE\n");
			printf("-------------------\n\n");
			joueur_t joueur ;
			printf("veuillez entrer votre nom :");
			scanf("%s",joueur.nom);
			system(CLEAR);
			printf("JEU DE  DEVINETTE\n");
			printf("-------------------\n\n");
			joueur.score = 100 ;

			do {

				printf("entre ton nombre : ");
				scanf("%d",&joueur.nombre_choisi);
				//indications et penalisations
				if (joueur.nombre_choisi > nombre_secret ) 
				{
					printf("Plus petit ! Toi aussi va doucement.\n");
					joueur.score -= 10 ;
				}
				else if (joueur.nombre_choisi < nombre_secret) 
				{
					printf("Plus grand ! Fait un effort tu peux y arriver\n");
					joueur.score -= 10 ;
				}
				else if (joueur.nombre_choisi == nombre_secret) 
				{ 
				system(CLEAR);
				printf("%s tu as trouvé le nombre secret a la tentative N°%d ! sur 100 points il t'en reste : %d \n\n",joueur.nom , (100-joueur.score)/10 +1 , joueur.score);
				}

				else if (joueur.nombre_choisi == nombre_secret && premier_essaie == 1 )
				printf("%s tu as trouvé le nombre secret a la tentative N°1 !sorcier \n\n",joueur.nom );

				else 
				printf("tu as entrer un truc non conforme ressaie \n");

				premier_essaie = 0 ;
				} while (joueur.nombre_choisi != nombre_secret);
		break;

		//mode multi
		case '2':
			int i = 0 ;
			system(CLEAR);
			printf("JEU DE  DEVINETTE\n");
			printf("-----------------\n\n ");

			printf("COMBIEN IL Y A T'IL DE JOUEUR ?\n");
			int nombreJoueurs ;
			printf("veuillez saisir le nombre de joueurs : ");
			scanf("%d",&nombreJoueurs); 
			//je crée un tableau qui contient les info des joueurs
			joueur_t joueurs[nombreJoueurs] ;
			system(CLEAR);
			printf("JEU DE  DEVINETTE\n");
			printf("-----------------\n\n ");
			//je récupère les noms
			for ( i=0 ; i<nombreJoueurs ; i++)
			{	
				printf("joueur N° %d veuillez entrer votre nom :",i+1);
				scanf("%s", joueurs[i].nom); 
				joueurs[i].score= 100 ;
				joueurs[i].estElimine = 0;

			}

			system(CLEAR);
			printf("JEU DE  DEVINETTE\n");
			printf("-----------------\n\n ");

			bool trouvé = 0;
			char gagnant[50];	
			
			do 
			{ 	//je commence par prendre le nombre saisi de chaques joueurs un a un 
				for( i=0 ; i<nombreJoueurs ; i++)
				{ 
					//je verifi si les points ne sont pas egaux a 0 et je le saute si cest le cas
					if( joueurs[i].score <= 0 && joueurs[i].estElimine == 0 ) 
					{
						printf("%s a été éliminé du jeu car ses points sont égaux à 0\n", joueurs[i].nom);
						joueurs[i].estElimine = 1;
						continue;
					}

					if(joueurs[i].estElimine == 1) continue;

					printf("TOUR DE %s\n",joueurs[i].nom);
					printf("----------\n");
					printf("entre ton nombre : ");
					scanf("%d",&joueurs[i].nombre_choisi);

				}	
				system(CLEAR);
				printf("JEU DE  DEVINETTE\n");
				printf("-----------------\n\n ");
				// maintenant je fais le sindications et pénalités
				for(int i=0 ; i<nombreJoueurs ; i++)
				{ 
					if (joueurs[i].nombre_choisi > nombre_secret) 
					{
						printf("%s Plus petit ! Toi aussi va doucement.\n\n’",joueurs[i].nom);
						joueurs[i].score -= 10 ;
					}
					else if (joueurs[i].nombre_choisi < nombre_secret) 
					{
						printf("%s Plus grand ! Fait un effort tu peux y arriver\n\n",joueurs[i].nom);
						joueurs[i].score -= 10 ;
					}
					else if (joueurs[i].nombre_choisi == nombre_secret) 
					{
						printf("%s as trouvé le nombre secret a la tentative N°%d !\n\n",joueurs[i].nom , (100-joueurs[i].score)/10 +1); 
						trouvé=1; 
					}
					else if (joueurs[i].nombre_choisi == nombre_secret && premier_essaie == 1 ) 
					{ 
						printf("%s tu as trouvé le nombre secret a la tentative N°1 !sorcier ",joueurs[i].nom );
						trouvé=1;
					}
					else 
					{
						printf("tu as entrer un truc non valide fait mieux la prochaine fois \n");
					}	
					premier_essaie = 0;
				}
			
			} while (trouvé == 0) ;


			// Affichage du tableau des scores
			printf("Tableau des scores :\n");
			printf("--------------------");
			for(int i=0 ; i<nombreJoueurs ; i++)
			{
				printf("%s : %d points\n", joueurs[i].nom, joueurs[i].score);
			}
			break;
		}

		printf("Voulez-vous rejouer ? (O pour oui, N pour non) : ");
		
		do {
			scanf("%c", &rejouer);
			if (rejouer != 'O' && rejouer != 'N') {
				printf("Choix invalide. Veuillez appuyer sur O pour oui et N pour non : ");
			}
		} while (rejouer != 'O' && rejouer != 'N');
	} while (rejouer == 'O'|| rejouer == 'o');


	getchar();

}
