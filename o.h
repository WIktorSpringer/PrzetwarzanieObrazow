#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#define MAX 512 

struct OBRAZ { /*struktura zawierajaca zminne do obslugi obrazu*/
  char NR;
  int wymx;
  int wymy;
  int odcien;
  int **obraz_pgm;
  int **R;
  int **G;
  int **B;

};
typedef  struct OBRAZ OBRAZ;

/* prototypu funkcji*/
void progowanie(OBRAZ * obrazek, float prog);
void konturowanie(OBRAZ * obrazek);
void rozmycie_poziom(OBRAZ * obrazek);
void rozmycie_pion(OBRAZ * obrazek);
void negatyw(OBRAZ * obrazek);
void zmiana_poziomow(OBRAZ *obrazek, float biel, float czern);
void konwersja(OBRAZ *obrazek);
