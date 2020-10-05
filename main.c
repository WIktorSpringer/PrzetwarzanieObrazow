/* WIktor Springer przetwarzanie obrazy cz2 06.01.2019 r */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include "o.h"
#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */

/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										    *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			    *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		    *
 * \param[out] wymx szerokosc obrazka						    *
 * \param[out] wymy wysokosc obrazka						    *
 * \param[out] odcien liczba odcieni odcien					    *
 * \return liczba wczytanych pikseli						    *
 ************************************************************************************/

int czytaj(FILE *plik_we,OBRAZ *obraz_pgm1) {

  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;


  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2'&&buf[1]!='3') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }
  obraz_pgm1->NR=buf[1]; /*zapisywanie numeru do stuktury*/
  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#')
      {         /* Czy linia rozpoczyna sie od znaku '#'? */
	if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	  koniec=1;                   /* Zapamietaj ewentualny koniec danych */
      }
    else
      {
	ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
      }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni odcien */
  if (fscanf(plik_we,"%d %d %d", &obraz_pgm1->wymx,&obraz_pgm1->wymy,&obraz_pgm1->odcien)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni odcien\n");
    return(0);
  }
  /*alokacja pamieci dla tablicy 2D za pomoca funkcji malloc*/
  obraz_pgm1->obraz_pgm=malloc(obraz_pgm1->wymy*sizeof(int*));
  for(i=0;i<obraz_pgm1->wymy;i++)
    {
      obraz_pgm1->obraz_pgm[i]=malloc(obraz_pgm1->wymx*sizeof(int));

    }

  if(obraz_pgm1->NR=='2') /*sprawdzanie czy plik jest pgm, jezeli tak to wczytaj sposobem ponizej*/
    {
      /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
      for (i=0;i<obraz_pgm1->wymy;i++) {
	for (j=0;j<obraz_pgm1->wymx;j++) {
	  if (fscanf(plik_we,"%d",&(obraz_pgm1->obraz_pgm[i][j]))!=1) {
	    fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	    return(0);
	  }
	}
      }
    }

  if(obraz_pgm1->NR=='3')/*jesli plik jest ppm to w ten sposob*/
    {
      obraz_pgm1->R=malloc(obraz_pgm1->wymy*sizeof(int*));
      for(i=0;i<obraz_pgm1->wymy;i++)
	{
	  obraz_pgm1->R[i]=malloc(obraz_pgm1->wymx*sizeof(int));
	}
      obraz_pgm1->G=malloc(obraz_pgm1->wymy*sizeof(int*));
      for(i=0;i<obraz_pgm1->wymy;i++)
	{
	  obraz_pgm1->G[i]=malloc(obraz_pgm1->wymx*sizeof(int));
	}
      obraz_pgm1->B=malloc(obraz_pgm1->wymy*sizeof(int*));
      for(i=0;i<obraz_pgm1->wymy;i++)
	{
	  obraz_pgm1->B[i]=malloc(obraz_pgm1->wymx*sizeof(int));
	}

      /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
      for (i=0;i<obraz_pgm1->wymy;i++) {
	for (j=0;j<obraz_pgm1->wymx;j++) {
	  if (fscanf(plik_we,"%d %d %d",&(obraz_pgm1->R[i][j]),&(obraz_pgm1->G[i][j]),&(obraz_pgm1->B[i][j]))!=3) {
	    fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	    return(0);
	  }
	}
      }
    }

  return obraz_pgm1->wymx*obraz_pgm1->wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

                     
/* Zwroc liczbe wczytanych pikseli */

void zapisz(FILE *neg,OBRAZ obraz_pgm1) /*funckaj zapisywania obrazu */
{

  int i,j;
  fprintf(neg,"P%c\n",obraz_pgm1.NR);
  fprintf(neg,"%d %d\n%d ",obraz_pgm1.wymx, obraz_pgm1.wymy, obraz_pgm1.odcien); /*tworzenie poczatkowej skladni obrazu pgm, zgodnie z jego budowa */



  if(obraz_pgm1.NR=='2')
    {
      for (i=0;i<obraz_pgm1.wymy;i++)
	     {
	      for (j=0;j<obraz_pgm1.wymx;j++)
	       {
	        fprintf(neg ,"%d ",(obraz_pgm1.obraz_pgm[i][j])); /*wprowadzanie tabeli wartosi do pliku*/
	       }
	     }

    }
  if(obraz_pgm1.NR=='3')
    {
      for (i=0;i<obraz_pgm1.wymy;i++)
	     {
	      for (j=0;j<obraz_pgm1.wymx;j++)
	       {
	        fprintf(neg ,"%d %d %d ",(obraz_pgm1.R[i][j]),(obraz_pgm1.G[i][j]),(obraz_pgm1.B[i][j])); /*wprowadzanie tabeli wartosi do pliku*/
	       }
	     }

    }
}



/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}


int main(int argc, char **argv)
{
  char tmp[100];
  OBRAZ obraz_pgm1; /*zadeklarowanie sktruktury*/
  int usuwanie_pliku=0; /*zmienna sluzaca do wykrywania uzycia opcji wyswietl*/
  float progow;   /*zmienna zwierajaca informacje o stopniu progowania*/
  int odczytano = 0; /*zmienna kontrolujaca wczesniejsze wczytanie pliku*/
  FILE *plik;
  char *nazwa;
  char *nazwab;
  char *nazwan;
  FILE *up;
  FILE *neg;
	
  
  float biel, czern; /* zmienne zawierajace informacje o stopniu bieli i czerni*/
  int i;
    
 
  for(i=1;i<argc;i++)
    {
      if(argv[i][0] != '-') /* sprawdzanie czy parametry podane w programie zaczynaja sie od '-'*/
	{
	  printf("do wywolania programu wymagany jest znak '-' przed patametrm. Aby otrzymac wiecej informacji wywolaj program z parametrem -h w celu uzyskania informacji\n");
	  return 0;
	}
      switch(argv[i][1])
	{
	case 'i': /*opcja wczytania pliku*/
	  
	  if(++i<argc) /*wczytujemy kolejny argument jako nazwe pliku*/
	    {
	      nazwa=argv[i];
	      plik=fopen(nazwa,"r");
	      if(plik!=NULL)
		     {              
		       czytaj(plik,&obraz_pgm1);
		       fclose(plik);  
		       odczytano=1;
					 
					 
		     }
	      else /*jesli nazwa jest bledna (nie odnaleziono takiego pliku) program nas o tym poinformuje*/
		     {
		       printf("bledna nazwa pliku\n");
		       return 0;
		     } 
	    }
	  else
	    {
	      printf("Brak nazwy pliku\n");
	      return 0;
	    }
	  break;
	case 'o':  /*opcja zapisywania*/
	  {    
	    if(odczytano==1)  /*if kontrolny, kontorluje czy wczesniej zostal plik wczytany*/
	      {            
		     if (++i<argc) /*pobranie nazwy pod jaka ma zostac plik zapisany*/
		      {       

		        nazwan=argv[i];
		        neg=fopen(nazwan,"w");
		        zapisz(neg,obraz_pgm1);
		        fclose(neg);
		      }
		     else  /*program informuje o nie podaniu nazwy pod jaka ma byc zapisany*/
		      {
		        printf("Nie podano nazwy do zapisu\n");
		      }
	      }
	    else /*w przypadku niewczytania pliku program nas o tym informuje*/
	      {
		     printf("blad: plik nie zostal wczytany! aby uzyskac wiecej informacji odpal program z parametrem -h (./a.out -h)\n");
	      }
	  }
	  break;
	case 'p': /*opcja progowania*/
	  {
	    if(odczytano==1) /*if kontrolujacy wcyztanie pliku*/
	      {
		      if (++i<argc) 
		       { /* wczytujemy kolejny argument jako wartosc progu */
		         if (sscanf(argv[i],"%f",&progow)==1)
		          {
			          progowanie(&obraz_pgm1,progow);
	  
		          }
		         else
						  {
		           return 0;     /* blad: niepoprawna wartosc progu */
							}
					 }
		      else     /* blad: brak wartosci progu */
		       {
		        printf("nie podano wartosci progowania\n");
		        return 0;
		       }
	      }   
	    else
	      {
		      printf("blad: plik nie zostal wczytany! aby uzyskac wiecej informacji odpal program z parametrem -h (./a.out -h)\n");
	      }
	  }          
	  break;
	case 'n': /*opcja negatywu*/ 
	  {
	    if(odczytano==1) /*if kontrolujacy wczytanie pliku*/
	      {
		                
		      negatyw(&obraz_pgm1);
		
	      }
	    else
	      {
		printf("blad: plik nie zostal wczytany! aby uzyskac wiecej informacji odpal program z parametrem -h (./a.out -h)\n");
	      }
	  }
	  break;
	case 'k': /*opcja konturowania*/
	  {
	    if(odczytano==1)/*if kotrolujacy wczytanie pliku*/
	      {
		                 
		      konturowanie(&obraz_pgm1);
		
	      }
	    else
	      {
		      printf("blad: plik nie zostal wczytany! aby uzyskac wiecej informacji odpal program z parametrem -h (./a.out -h)\n");
	      }
	  }
	  break;
	case 'z': /*opcja zamiany poziomow*/
	  {
	    if(odczytano) /*if kontrolujacy wczytanie pliku*/
	      {

      

		if (++i<argc)
		  { /* wczytujemy kolejny argument jako wartosc progu czerni*/
		    if (sscanf(argv[i],"%f",&czern )==1)
		      {
	  
		      } 
		    else
		      {
			     return 0;
		      }     /* blad: niepoprawna wartosc progu */
		  } 
		else
		  {
		    return 0;
		  }             /* blad: brak wartosci progu */
		if (++i<argc)   /* wczytujemy kolejny argument jako wartosc progu bieli */
		  { 
		    if (sscanf(argv[i],"%f",&biel)==1) 
		      {
			     zmiana_poziomow(&obraz_pgm1,czern,biel);
		      } 
		    else
		      {
			     return 0;     /* blad: niepoprawna wartosc progu */
		      } 
		  }
		else
		  {
		    return 0;
		  }             /* blad: brak wartosci progu */
      
	      }
	    else
	      {
		     printf("blad: plik nie zostal wczytany! aby uzyskac wiecej informacji odpal program z parametrem -h (./a.out -h)\n");
	      }
	  }
	  break; /*opcja rozmycia w pionie i poziomie*/
	case 'r': 
	  {                 /*if kontrolujacy wczesniejsze wczytanie obrazu*/
	    if(odczytano==1)
	      {
		     if(argv[i][2]=='x')  /*sprawdzenie czy zadane jest rozmycie poziome*/
      
		      {
		        rozmycie_poziom(&obraz_pgm1);
		      }
		     else if(argv[i][2]=='y') /*sprawdzenie czy zadane jest rozmycie pionowe*/
		      {
		        rozmycie_pion(&obraz_pgm1);
		      }
		     else
		      {          /*w przypadku podania nie pelnej opcji*/
		        printf("nie okreslono jaki rodzaj rozmycia jest zadany");
		       return 0;
		      }
	      }
	    else
	      {
		     printf("blad: plik nie zostal wczytany! aby uzyskac wiecej informacji odpal program z parametrem -h (./a.out -h)\n");
	      }
	  }
	  break;
	case 'd':  /*opcja wyswietlenia obrazu*/
	  {      
        
        
	    up=fopen("tmp.pgm", "w");
	    zapisz(up, obraz_pgm1);  /*towrzenie tymczasowego pliku sluzaego do zapisu aktyalnego stanu tablicy(a co zatym idzie wgladu obrazu)i rozwiazanie problemu wystwietlania go*/
	    fclose(up);
	    wyswietl("tmp.pgm");
	    usuwanie_pliku=1;
      
	  }
	  break;
	case 's': /*opcja konwersji z koloru do szarosci warunkiem jest to ze obraz jest ppm*/
	  {
	    if(odczytano==1)/*if kontrolujacy wczesniejsze wczytanie*/
	      {
		     
		        
							
		      konwersja(&obraz_pgm1);
		        
	       	
	      }
	    else
	      {
		printf("blad: plik nie zostal wczytany! aby uzyskac wiecej informacji odpal program z parametrem -h (./a.out -h)\n");
	      }
      
	  }
	  break;
	case 'h':/*opcja wyswietlenia instrukcji*/
	  {
	    printf("WITAJ! JESTEM PROGRAMEM DO OBSLUGI ZDJEC PGM/PPM\n");
	    printf("OBSŁUGA PROGRAMU:\n");
	    printf("PROGRAM DZIALA NA ZASADZIE WPISYWANIA ODPOWIEDNICH PARAMETROW PODCZAS \n");
	    printf("########################################################################################################################\n");
	    printf("# 1.---> wczytywanie obrazu: paramet -i nazwa_wczytywanego_pliku                                                       #\n");
	    printf("# 2.---> zapisywanie obrazu: paramet -o nazwa_zapisywanego obrazu                                                      #\n");
	    printf("# 3.---> progowanie: -p  wpisanie_procentowo_progu (zgodnie z zasada, ze 50%% to 0.5)                                   #\n");
	    printf("# 4.---> negatyw: -n                                                                                                   #\n");
	    printf("# 5.---> konturowanie: -k                                                                                              #\n");
	    printf("# 6.---> zmiana poziomow: -z prog_czerni prog_bieli ( progi podawane sa procentowo zgodnie z zasada, ze 50%%=0.5)       #\n");
	    printf("# 7.---> rozmucie pion/poziom: -ry /-rx                                                                                #\n");
	    printf("# 8.---> wyswietlenie obrazka: -d                                                                                      #\n");
	    printf("# 9.---> konwersja: -s (uwaga plik musi byc obrazem ppm. w przypadku pgm wyskoczy blad)                                #\n"); /*ostrzzenie o probie skonwertwoania pgm*/
	    printf("# 10.--> instrukcja obslugi: -h                                                                                        #\n");
	    printf("# UWAGA!!!! KOLEJNOSC CZYNNOSCI JAKIE WYKONUJE PROGRAM SA TAKIE SAME JAK KOLEJNOS WPISYWANYCH PARAMETROW               #\n");
	    printf("########################################################################################################################\n");

	  }
	  break;
    
    





	default:
	  {
	    return 0;
	  }
	  break;
 
	}
    }
  if(usuwanie_pliku==1) /*usuwanie pliku tymczasowego potrzebnego do wyswietlenia. + warunek sprawdzenia czy takowe wyswietlenie bylo*/
    {
      sleep(1);
      system("rm tmp.pgm");
    }
    
  return odczytano;

}


/*
TESTY:
Program dziala na zasdzie wyolywania parametrow. Musza one zostac podane w odpowiedniej kolejnosci. Program obluguje obrazy pgm i ppm. 
Obrazy ppm moga zostac jedynie zapisane, wyswietlone  oraz skonwertwane na szarosc. Na obrazach pgm mozemy uzyc kazdej opcji jakie program 
nam oferuje oprocz skonwertowania.


Testowanie proogramu polegalo na zadawaniu programowi danej operacji na pliku i porownywaniu go z obrazem zawartym w pliku dolaczony do strony kursu.(kubus.pgm) 
Jezeli chodzi o obrazy kolorowe to testowanie przebieglo na obrazku Claudia.ppm dostepnego na serwerze diablo u prof. R. Muszynskiego
Wszystkie proby testowania funckji przerabiajacych obraz przebiegly pomyslnie. Program zmienia obrazek w taki sposob ze jest odzwierciedleniem swojego odpowiednika 
w pliku dolaczonym do strony kursu.

Program prawidlowo wyswietla i wczytuje oraz zapisuje pliki z roz. ppm

Program prawidlowo wyswietla i wczytuje oraz zapisuje pliki z roz. pgm

testowanie dzialania parametrow rowniez przebiego poprawnie. parametry dzialaja tak, jak sa opisane w instrukcji programu.




Z nie wiadomych dla mnie przyczyn program mimo proby zablokowania mozliwosc kowersji pgm (if(obrazek.pgm.NR==3)) (przed wywolaniem funkcji) czyta obrazek ppm jako pgm. Jest to spowodowane 
najprawdopodobniej przez zmiane P3 na P2 w tej funkcji. Nie znalazlem rozwiazania na pozbycie sie tego problemu. assercja w tym wypadku jest zawarta w istrukcji programu.



Uwazam ze program pomimo nie blokowania kowersji pgm dziala poprawnie.
*/
