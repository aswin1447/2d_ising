
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

const int ROWS=160;
const int COLUMNS=160;
const float T=5;


unsigned long genrand_int32();

double genrand_real1(void);
void init_genrand(unsigned long );



long double mag(int present[ROWS][COLUMNS])
{
long double mag=0;

for(int i=0;i<ROWS;i++)
    {   for(int j=0;j<COLUMNS;j++)
            {
               mag=mag+present[i][j];
             }

    }

return(mag/((ROWS-1)*(COLUMNS-1)));
}


long double  energy(int RANDOM[ROWS][COLUMNS])
{ 

int i,j,n,sum;
long int size=4*ROWS*COLUMNS;
unsigned long int counter[size];
int *ptr1,*ptr2;
long double energy=0;
double h=0;
int count=0;
int m=0;
float JJ=1;




for (i=0;i<ROWS;i++)

    {   for (j=0;j<COLUMNS;j++)
            

             {     

     if(i==0&&j==0) energy=energy-JJ*RANDOM[i][j]*(RANDOM[i][j+1]+RANDOM[i][COLUMNS-1]+RANDOM[ROWS-1][j]+RANDOM[i+1][j]);
    else if(i==0&&j==COLUMNS-1) energy=energy -JJ*RANDOM[i][j]*(RANDOM[i][0]+RANDOM[i][j-1]+RANDOM[ROWS-1][j]+RANDOM[i+1][j]);
 else if(i==ROWS-1&&j==0) energy=energy -JJ*RANDOM[i][j]*(RANDOM[i][j+1]+RANDOM[i][COLUMNS-1]+RANDOM[i-1][j]+RANDOM[0][j]);
else if(i==ROWS-1&&j==COLUMNS-1) energy=energy -JJ*RANDOM[i][j]*(RANDOM[i][0]+RANDOM[i][j-1]+RANDOM[i-1][j]+RANDOM[0][j]);
else if (i==0&&j!=0&&j!=COLUMNS-1) energy=energy -JJ*RANDOM[i][j]*(RANDOM[i][j+1]+RANDOM[i][j-1]+RANDOM[ROWS-1][j]+RANDOM[i+1][j]);else if(j==COLUMNS-1&&i!=0&&i!=ROWS-1) energy=energy -JJ*RANDOM[i][j]*(RANDOM[i][0]+RANDOM[i][j-1]+RANDOM[i-1][j]+RANDOM[i+1][j]);
else if(i==ROWS-1&&j!=0&&j!=COLUMNS-1) energy=energy -JJ*RANDOM[i][j]*(RANDOM[i][j+1]+RANDOM[i][j-1]+RANDOM[i-1][j]+RANDOM[0][j]);
else if(j==0&&i!=0&&i!=ROWS-1) energy=energy -JJ*RANDOM[i][j]*(RANDOM[i][j+1]+RANDOM[i][COLUMNS-1]+RANDOM[i-1][j]+RANDOM[i+1][j]);

    else 


                  energy=energy -JJ*RANDOM[i][j]*(RANDOM[i][j+1]+RANDOM[i][j-1]+RANDOM[i-1][j]+RANDOM[i+1][j]); 


          
          
                           


             }
              } 


return(energy/2);




      }




/**********evolve**********/

void evolve(int present[ROWS][COLUMNS])


{
long unsigned int i,j;

long double Ei,Ef,Ediff;
int counter;
long unsigned int k=1;

//long double kb=1.38*pow(10,-23);
int n=ROWS-1;

long unsigned int max,rand,m;
max=4294967295;
long double kb=1;
long double prob;
//unsigned long s;
time_t seconds; 
    while(k>0)
{  
    seconds = time(NULL); //seeding mtwister
//seconds=seconds+k;
init_genrand(seconds+k);

  
m=max%(n+1);


do{rand=genrand_int32(); }  //castin the random no genearator to a range 2-400,naive and wrong implementation ,needs refinement
  while(rand>=max-m);
  i=rand%(n+1);

/*if(i==0) 
   i=2;
if(i==1)
   i=3;*/

do{rand=genrand_int32();}
  while(rand>=max-m);
   j=rand%(n+1);


/*
if(j==0)
   j=2;
if(j==1)
  j=3;*/

long double magnetization=mag(present);
Ei=energy(present);  //initial energy

if(present[i][j]==1)   //flipping
  present[i][j]=-1;
else 
  present[i][j]=1;


Ef=energy(present);   //final energy


Ediff=Ef-Ei;   //energy difference


// prob=pow(2.7182,p);

double r= genrand_real1(); //random real number in [0,1]

prob=expl(-(Ediff)/(kb*T));

if(Ediff>0&&prob<r)             
  {      
          
      {if(present[i][j]==1)  present[i][j]=-1;
       else present[i][j]=1;
         
      }
   }



//printf("\n");



printf("\033[H\033[J"); //clearing the screen



for(i=0;i<ROWS;i++)     //printing the matrix
          {   counter=0;
		  for(j=0;j<COLUMNS;j++)

                  {if(present[i][j]==1)  printf("\033[07m  \033[m");
			  else printf("  ");	  //printf("\t%d",next[i][j]);
			  counter++;
			  if (counter==COLUMNS){ printf("\n");}  // printf("\n");printf("\n");}
		  }

           } 

//printf("i=%lu\tj=%lu\tgeneration=%lu\tEdiff=%Lf\tmagnetization=%Lf",i,j,k,Ediff,magnetization);
//count++;
k++;


usleep(11000);
}}





int main()

{
time_t seconds;

    seconds = time(NULL); //seeding mtwister
init_genrand(seconds);



int RANDOM[ROWS][COLUMNS];
int i,j;

for(i=0;i<ROWS;i++)

  {for(j=0;j<COLUMNS;j++)
	{  unsigned long ran=genrand_int32();

           if(ran%2==0) RANDOM[i][j]=1;
           else RANDOM[i][j]=-1;
             
        }
}
//printf("%Lf",energy(RANDOM));
 evolve(RANDOM);
}
































