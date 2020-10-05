#include"o.h"

void progowanie(OBRAZ * obrazek, float prog)/*funkcja progowania obrazu */
{

  int i,j;


  for (i=0;i<obrazek->wymy;i++)
    {
      for (j=0;j<obrazek->wymx;j++)
	{
	  if((obrazek->obraz_pgm[i][j])<(int)(prog*(obrazek->odcien))) /*warunek zmiany wartoci ,,okienka,, tabeli na 0 i rzutowanie tej  wartosci na int */
	    {
	      obrazek->obraz_pgm[i][j]=0;
	    }
	  else
	    {
	      obrazek->obraz_pgm[i][j]=obrazek->odcien; /*zamiana na ,,okienka,, tabeli na czern */
	    }
	}

    }



}


void konturowanie(OBRAZ * obrazek) /* konturowanie obrazu*/
{

  int i,j;

  for (i=0;i<obrazek->wymy-1;i++) /* indeksowanie tablei z jednoczesna zmiana jej wartosi aby powstal obraz konturowany*/
    {
      for (j=0;j<obrazek->wymx-1;j++)
	{

	  obrazek->obraz_pgm[i][j]=abs( obrazek->obraz_pgm[i+1][j]- obrazek->obraz_pgm[i][j])+abs( obrazek->obraz_pgm[i][j+1]- obrazek->obraz_pgm[i][j]);


	}
    }



}



void rozmycie_poziom(OBRAZ * obrazek) /*funkcja rozmycia obrazu w poziomie */
{
  int tabl[MAX][MAX];
  int i,j;

  for (i=1;i<obrazek->wymy-1;i++)
    {
      for (j=1;j<obrazek->wymx-1;j++)
	{

	  tabl[i][j] = (int) (( obrazek->obraz_pgm[i-1][j]+ obrazek->obraz_pgm[i][j]+ obrazek->obraz_pgm[i+1][j])/3.0);  /*nadanie tabeli tabl wartosci opratej o tabele obraz.. z jednoczesnym uwzgledniemiem zakresu tabeli (obrazek->wymy-1 i obrazek->wymx-1) aby program nie probowal odczytac wartosci z okiena o indeksach wiekszych niz te w ktorych obraz jest zapisany*/


	}
    }
  for (i=1;i<obrazek->wymy-1;i++)
    {
      for (j=1;j<obrazek->wymx-1;j++)
	{

	  obrazek->obraz_pgm[i][j]= tabl[i][j]; /*podstawienie wartosci ,,okienek,, tabeli tabl do ,,okienek,, tabeli obraz..*/


	}
    }



}
void rozmycie_pion(OBRAZ * obrazek) /*funkcja przerabiajaca obra pgm na obraz rozmyty w pion */
{
  int zam[MAX][MAX];
  int i,j;

  for (i=1;i<obrazek->wymy-1;i++)
    {
      for (j=1;j<obrazek->wymx-1;j++)
	{

	  zam[i][j] = (int) (( obrazek->obraz_pgm[i][j-1]+ obrazek->obraz_pgm[i][j]+ obrazek->obraz_pgm[i][j+1])/3.0); /*nadanie tabeli zam  wartosci opratej o tabele obraz.. z jednoczesnym uwzgledniemiem zakresu tabeli (obrazek->wymy-1 i obrazek->wymx-1) aby program nie probowal odczytac wartosci z okiena o indeksach wiekszych niz te w ktorych obraz jest zapisany*/


	}
    }
  for (i=1;i<obrazek->wymy-1;i++)
    {
      for (j=1;j<obrazek->wymx-1;j++)
	{

	  obrazek->obraz_pgm[i][j]= zam[i][j]; /*podstawienie wartosci okienek obraz.. na wartosci okienek o tych samych indeksach tabeli zam*/


	}
    }
}


void negatyw(OBRAZ * obrazek) /*funkcja zamieniajac obraz pgm na negatyw */
{

  int i,j;

  for (i=1;i<obrazek->wymy-1;i++)
    {
      for (j=1;j<obrazek->wymx-1;j++)
	{

	  obrazek->obraz_pgm[i][j]= (obrazek->odcien-obrazek->obraz_pgm[i][j]);


	}
    }



}

void zmiana_poziomow(OBRAZ * obrazek, float biel ,float czern)
{
  int i,j;
  int biel_1, czern_1;
  czern_1=obrazek->odcien*czern;
  biel_1=obrazek->odcien*biel;

  for(i=0;i<obrazek->wymy;i++)
    
    {
      
      for(j=0;j<obrazek->wymx;j++)
	
	{
	  
	  if(obrazek->obraz_pgm[i][j]<=czern_1)
	    
	    {
	      obrazek->obraz_pgm[i][j]=0;
            }
      
	  else if(obrazek->obraz_pgm[i][j]>=biel_1)
	
	    {
	      obrazek->obraz_pgm[i][j]=obrazek->odcien;
	    }

	  else
	    {
	      obrazek->obraz_pgm[i][j]=(obrazek->obraz_pgm[i][j]-czern_1)*(obrazek->odcien)/(biel_1-czern_1);
	    }
	}
    }

}
void konwersja(OBRAZ * obrazek) /* konturowanie obrazu*/
{

  int i,j;
  
  
 
  obrazek->NR='2';
  for (i=0;i<obrazek->wymy;i++) /* indeksowanie tablei z jednoczesna zmiana jej wartosi aby powstal obraz konturowany*/
    {
      for (j=0;j<obrazek->wymx;j++)
	{

	  obrazek->obraz_pgm[i][j]=(obrazek->R[i][j]+ obrazek->G[i][j]+ obrazek->B[i][j])/3;
	}

    }
  

}
