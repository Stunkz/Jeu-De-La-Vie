#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAXX 60
#define MAXY 35

#define WAIT 100000

#define MINVOISIN 2
#define MAXVOISIN 3
#define NUMVOISIN 3

void Affichage(int tab[MAXY][MAXX]);
void Calcul(int tab[MAXY][MAXX], int tabAlt[MAXY][MAXX]);
void RandomInit(int tab[MAXY][MAXX]);

int main(void) {

    int map[MAXY][MAXX] = { 0 };
    int mapAlt[MAXY][MAXX] = { 0 };

    RandomInit(map);

    system("clear");

    for (int i = 0; ++i < 1000;) {
        printf("Etape : %d\n", i);
        Affichage(map);
        Calcul(map, mapAlt);
        usleep(WAIT);
        system("clear");
    }
    

    return 0;
}

void Calcul(int tab[MAXY][MAXX], int tabAlt[MAXY][MAXX]) {
    for (int i = 0; i<MAXY; i++) {
        for (int j = 0;  j<MAXX; j++) {
            /*Additionne le nombre de voisins*/
            int somme = 0;
            for (int g = 0; g<3; g++) {
                for (int h = 0; h<3; h++) {
                    if ( ( i+g-1 >= 0 ) && ( i+g-1 < MAXY ) && ( j+h-1 >= 0 ) && ( j+h-1 < MAXX ) ) {
                        somme += tab[i+g-1][j+h-1];
                    }
                }
            }
            somme -= tab[i][j];
            tabAlt[i][j] = (tab[i][j] == 1) ? ( somme >= MINVOISIN && somme <= MAXVOISIN ) : ( somme == NUMVOISIN);
        }
    }

    for (int i = 0; i<MAXY; i++) {
        for (int j = 0;  j<MAXX; j++) {
            tab[i][j] = tabAlt[i][j];
        }
    }

}

void Affichage(int tab[MAXY][MAXX]) {

    for ( int i = 0; i<MAXY; i++ ) {
        for ( int j = 0; j<MAXX; j++ ) {
            if ( tab[i][j] == 1 ) {
                printf( "■ " );
            } else {
                printf( "□ " );
            }
        }
        printf("\n");
    }

}

void RandomInit(int tab[MAXY][MAXX]) {

    srand(time(NULL));

    for (int i = 0; i<MAXY; i++) {
        for (int j = 0;  j<MAXX; j++) {
            tab[i][j] = rand() % 2;
        }
    }

}
