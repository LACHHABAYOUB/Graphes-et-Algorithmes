/*        A y o u b l a c h h a b*/

#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include<conio.h>
#define CMAX  10  
#define VMAX  10  
#include <cstdio>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#define ii pair<int,int>
#define pb push_back
#define INF 99999
#define ii pair<int,int>
#define pb push_back


  int NC, NV, NOPTIMAL,P1,P2,XERR;
  double TS[CMAX][VMAX];

  void Data() {
    double R1,R2;
    char R;
    int I,J;
    system("cls");
    printf("\n PROGRAMMATION LINEAIRE\n\n");
    printf(" MAXIMIZE (Oui ==>O ou No ==> n) ? "); scanf("%c", &R);scanf("%c", &R);
    printf("\n NOMBRE DE VARIABLES DE FONCTION ECONOMIQUE ? "); scanf("%d", &NV);
    printf("\n NOMBRE DE CONTRAINTES ? "); scanf("%d", &NC);
    if (R == 'O' || R=='o')
      R1 = 1.0;
    else
      R1 = -1.0;
    printf("\n COEFFICIENTS D'ENTREE DE LA FONCTION ECONOMIQUE :\n");
    for (J = 1; J<=NV; J++) {
      printf("       #%d ? ", J); scanf("%lf", &R2);
      TS[1][J+1] = R2 * R1;
    }
    printf(" la main droite ? "); scanf("%lf", &R2);
    TS[1][1] = R2 * R1;
    for (I = 1; I<=NC; I++) {
      printf("\n CONTRAINTE #%d:\n", I);
      for (J = 1; J<=NV; J++) {
        printf("       #%d ? ", J); scanf("%lf", &R2);
        TS[I + 1][J + 1] = -R2;
      }
      printf("        la main droite  ? "); scanf("%lf", &TS[I+1][1]);
    }
    printf("\n\n RESULTATS:\n\n");
    for(J=1; J<=NV; J++)  TS[0][J+1] = J;
    for(I=NV+1; I<=NV+NC; I++)  TS[I-NV+1][0] = I;
  }

  void Pivot();
  void Formula();
  void Optimize();

  void Simplex() {
e10: Pivot();
     Formula();
     Optimize();
     if (NOPTIMAL == 1) goto e10;
  }

  void Pivot() {

    double RAP,V,XMAX;
    int I,J;

    XMAX = 0.0;
    for(J=2; J<=NV+1; J++) {
	if (TS[1][J] > 0.0 && TS[1][J] > XMAX) {
        XMAX = TS[1][J];
        P2 = J;
      }
    }
    RAP = 999999.0;
    for (I=2; I<=NC+1; I++) {
      if (TS[I][P2] >= 0.0) goto e10;
      V = fabs(TS[I][1] / TS[I][P2]);
      if (V < RAP) {
        RAP = V;
        P1 = I;
      }
e10:;}
    V = TS[0][P2]; TS[0][P2] = TS[P1][0]; TS[P1][0] = V;
  }

  void Formula() {;
    //Labels: e60,e70,e100,e110;
    int I,J;

    for (I=1; I<=NC+1; I++) {
      if (I == P1) goto e70;
      for (J=1; J<=NV+1; J++) {
        if (J == P2) goto e60;
        TS[I][J] -= TS[P1][J] * TS[I][P2] / TS[P1][P2];
e60:;}
e70:;}
    TS[P1][P2] = 1.0 / TS[P1][P2];
    for (J=1; J<=NV+1; J++) {
      if (J == P2) goto e100;
      TS[P1][J] *= fabs(TS[P1][P2]);
e100:;}
    for (I=1; I<=NC+1; I++) {
      if (I == P1) goto e110;
      TS[I][P2] *= TS[P1][P2];
e110:;}
  }   

  void Optimize() {
    int I,J;
    for (I=2; I<=NC+1; I++)
      if (TS[I][1] < 0.0)  XERR = 1;
    NOPTIMAL = 0;
    if (XERR == 1)  return;
    for (J=2; J<=NV+1; J++)
      if (TS[1][J] > 0.0)  NOPTIMAL = 1;
  }

  void Results() {
    //Labels: e30,e70,e100;
    int I,J;
    
    if (XERR == 0) goto e30;
    printf(" NO SOLUTION.\n"); goto e100;
e30:for (I=1; I<=NV; I++)
    for (J=2; J<=NC+1; J++) {
      if (TS[J][0] != 1.0*I) goto e70;
      printf("       VARIABLE #%d: %f\n", I, TS[J][1]);
e70:  ;}
    printf("\n       FONCTION ECONOMIQUE: %f\n", TS[1][1]);
e100:printf("\n");
  }


void printSolution(int dist[][4]);
 

void floydWarshall (int graph[][4])
{
    
    int dist[4][4], i, j, k;
 
   
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            dist[i][j] = graph[i][j];
 
    
    for (k = 0; k < 4; k++)
    {
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
 
    printSolution(dist);
}
 
void printSolution(int dist[][4])
{
    printf ("La matrice suivante montre les distances les plus courtes"
            " Entre chaque paire de sommets \n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}
 

void Color(int couleurDuTexte,int couleurDeFond) 
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

char * Accent(const char * mess) {
      static char retour [80];
      CharToOem (mess,retour); // API Windows
      return retour;
   }

 

 
 
    using namespace std;
    
    int n;int e,source;
    vector<ii> g[100000];
    int dist[100000];
    bool marked[100000];
    void apply_dijkstra()
    {
    	set<ii > s;
    	s.insert(ii(0,source));
    	dist[source] = 0;marked[source] = 1;
    	while(!s.empty())
    	{	
    		ii p = *s.begin();	
    		s.erase(p);
    		marked[p.second] = 2;
    		for(int i=0;i<g[p.second].size();i++)
    			if(marked[g[p.second][i].second]==0)
    			{
    				s.insert(ii(dist[p.second]+g[p.second][i].first,g[p.second][i].second));
    				marked[g[p.second][i].second] = 1;
    				dist[g[p.second][i].second] = dist[p.second]+g[p.second][i].first;
    			}
    			else if(marked[g[p.second][i].second]==1 && dist[g[p.second][i].second] > dist[p.second]+g[p.second][i].first)
    			{
    				s.erase(ii(dist[g[p.second][i].second],g[p.second][i].second));
    				s.insert(ii(dist[p.second]+g[p.second][i].first,g[p.second][i].second));
    				dist[g[p.second][i].second] =  dist[p.second]+g[p.second][i].first;
    			} 
    	}
    	printf("Les distances les plus courtes sont\n");
    	for(int i=1;i<=n;i++)
    	{
    		printf("Node %d - %d\n",i,dist[i]);
    	}
    	printf("\n");
    }
     
   
   void matrice(int t[][100], int n)
{ int i,j,v;
printf(" Vous allez saisir les coefficients de la matrice d'adjacence du graphe.\n");
printf("La saisie se fait ligne par ligne.\n");
printf("Donnez la valeur 0 si l'arc cite n'est pas defini.\n");
printf("\n");
system ("PAUSE");
for(i=0;i<n;i++)
for (j=0;j<n;j++)
{printf ("Donner la valeur de l'arc (%d,%d):\n",i,j);
scanf ("%d",&(t[i][j]));
}
printf("\n");
printf("Vous avez saisi la matrice ci-dessous:\n");
for(i=0;i<n;i++)
{for (j=0;j<n;j++)
printf("%5d",t[i][j]);
printf("\n");
}
}



void predecesseur(int t[][100],int p[][100],int n) //fournit une matrice p[] tel que:
{ int i,j,k,cpt;
for (j=0;j<n;j++)// chaque ligne j(=un tableau) definit un sommet
{k=1; cpt=0;
printf("Les predecesseurs de %d sont gh:\n",j);
for (i=0;i<n;i++)
{if ( t[i][j]!=0)
{p[j][k]=i;
k++;
cpt++;}
p[j][0]=cpt;}
for (i=1;i<=cpt;i++)
printf("%5d",p[j][i]);
printf("\n");
}
}



int recherche(int t[],int n,int *p,int deb,int fin)
{int k, trouve,l,m;
trouve=0;
for (k=deb;k<=fin;k++)
{ l=0;m=0;
while((l==0)&&(m<n))
{if (t[m]==p[k])
l=1;
else
m++;
}
trouve=trouve+l;
}
return trouve;
}



int recher(int t[], int n,int el) 
{ int i;
int trouve=0;
for (i=0;i<n;i++)
if (t[i]==el)
trouve=1;
return trouve;}



int ordinal(int p[][100],int n,int ord[])//ordonne les sommets
// par une fonction ordinale en les rangeant dans ord[]
{int k, i,j,f;
k=0;
for (j=0;j<n;j++) //range d'abord ceux qui n'ont 
//pas de predecesseurs;il doit y en avoir un et un seul
{if (p[j][0]==0)
{ord[k]=j;
k++;}
}
if (k==0)
printf("Il n'y a pas de sommet racine\n");

if (k>1)
{printf("Il y a plus d'une racine\n");
return -1;
}
if (k==1)
{for(i=0;i<n;i++)
for (j=0;j<n;j++)
if(recherche(ord,k,p[j],1,p[j][0])==p[j][0])//verifie si pour un sommet 'j' donne
// tous les predecesseurs sont dans ord[]
if (recher(ord,k,j)==0)//s'il n'est pas encore dans ord[], l'y mettre
{ord[k]=j;
k++;
}

}

if (k==n)
{printf("La numerotation par une fonction ordinale donne:\n");
for (i=0;i<k;i++)
printf("%5d",ord[i]);
printf("\n");
return k;}//retourne le nombre de sommets effectivement ordonnes
if (k<n)
{printf("Le graphe contient un circuit\n");//si tous les sommets ne sont pas dans ord[],
// c'est parce que nous avons un circuit
return -1;} //retourne -1 s'il n'y a pas une unique racine
}


void MinIndice(int t[],int n, int*min,int*ind)//recherce le minimum 
// des elements non nuls de t[](de taille n) et fournit son indice 'ind' et sa valeur 'min'
{int i;
*min=0;
*ind=0;
for(i=0;i<n;i++)
if(t[i]!=0)
{ if(*min==0)
{*min=t[i];
*ind=i;}
else
if(*min>t[i])
{*min=t[i];
*ind=i;}
}
}


void bellman(int pred[][100], int ord[], int t[][100],int n)
{int v[100][100]; int ch[100];
int i,j,a,b,last,z,k;
int *h;
v[0][0]=0;
for (i=1;i<n;i++)
for (j=0;j<i;j++)
{MinIndice(v[j],i,&a,&b);
h=&(pred[ord[i]][1]);
v[i][j]=recher(h,pred[ord[i]][0],ord[j])*a+ t[ord[j]][ord[i]];
}
MinIndice(v[n-1],n,&a,&b);
printf("La valeur du chemin le plus court est: %d\n",a);
ch[0]=ord[n-1];
z=1;
while (b!=0)
{
ch[z]=ord[b];
last=b;
z++;
MinIndice(v[last],last+1,&a,&b);
}

printf("le chemin le plus court est:\n");
for (k=z;k>=0;k--)
printf("%5d",ch[k]);
}
   
   int  menu_p()
{
	printf("               *********************************************\n");
	printf("               **        Graphes et Algorithmes           **\n");
	printf("               *********************************************\n");
    printf("               ** 1. Methode Simplex                      **\n");
    printf("               ** 2. Algorithme dijkstra                  **\n");
    printf("               ** 3. Algorithme bellman-ford              **\n");
    printf("               ** 4. Algorithme floyd                     **\n");
    printf("               ** 0. Quitter                              **\n");
    printf("               **                                         **\n");
	printf("               *********************************************\n");
	printf("\n");
	printf("               Choiser Une Option SVP :   ");	
	
}
   
   
int main()
{
	int x,y,choix;
printf("\n\n");
printf("%s",Accent("   Bienvenu sur le cours de Graphes et Algorithmes avec la programmation c    \n"));
printf("\n");	
printf("%s",Accent("  SVP Choisi Votre Couleur de l'ecriture Prefere et la couleur de fond Prefere:    \n"));
printf("\n");
printf("                                  0 : Noir\n");
printf("%s",Accent("                                  1 : Bleu fonce\n"));
printf("%s",Accent("                                  2 : Vert fonce\n"));
printf("                                  3 : Turquoise\n");
printf("                                  4 : Rouge fonce\n");
printf("                                  5 : Violet\n");
printf("                                  6 : Vert caca d'oie\n");
printf("                                  7 : Gris clair\n");
printf("%s",Accent("                                  8 : Gris fonce\n"));
printf("                                  9 : Bleu fluo\n");
printf("                                  10 : Vert fluo\n");
printf("                                  11 : Turquoise\n");
printf("                                  12 : Rouge fluo\n");
printf("                                  13 : Violet 2\n");
printf("                                  14 : Jaune\n");
printf("                                  15 : blanc \n");
printf("\n");

printf("%s",Accent("Votre choix de colleur de l'ecriture Prefere:    \n"));
scanf("%d",&x);	
printf("%s",Accent("Votre choix de colleur du fond Prefere:    \n"));
scanf("%d",&y);	
	Color(x,y);
	system("cls");
			


           menu_p();
           
	scanf("%d",&choix);
	
	
		switch(choix)
		{
			
			case 1:
			 
			 	Data();
  				Simplex();
 				Results();
	        break;
	        
	        case 2:
	    	system("cls");
			printf("Entrez le nombre de sommets: \n");
    	scanf("%d",&n);
    	printf("Entrez le nombre de bords: \n");
    	int e;scanf("%d",&e);
    	printf("Entrez les bords et leurs poids: \n");
    	for(int i=0;i<e;i++)
    	{
    		int x,y,w;
    		scanf("%d%d%d",&x,&y,&w);
    		g[x].pb(ii(w,y));
    	}
    	printf("Entrez la source :\n");
    	scanf("%d",&source);
    	apply_dijkstra();
    	return 0;
	        break;
	        
	        case 3:
			 system("cls");
			  int t[100][100]; int p[100][100];int ord[100];
			int n; int a; int b;
		printf ("Donner le nombre de sommets...\n");
		scanf("%d",&n);
		matrice(t,n);
		predecesseur(t,p,n);
		if (ordinal(p,n,ord)==n)
		bellman(p,ord,t,n);
		printf("\n");
		system("PAUSE");
		return 0;
	        break;
	        
	        case 4:	  
    		system("cls");
			int graph[4][4] = { {0,   2,  INF, 6},
                                {INF, 0, -2, INF},
                                {INF, 5, 0,   5},
                                {-4, -1, INF, 0}};
		    floydWarshall(graph);
    		return 0;
	        break;
	        
		}
		return 0;
} 
