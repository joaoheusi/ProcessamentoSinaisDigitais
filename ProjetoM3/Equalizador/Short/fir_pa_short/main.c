/* programa para testes com arquivos
-- Lendo arquivo de entrada
-- Processa
-- Gera arquivo de saida
-- walter 1.0 
*/

#include <stdio.h>
#include <string.h>
#include <cycles.h>



#define 	FrameSize 1
#define NSAMPLES 80 

static int frameCount = 1;


extern void proc_file( short *, short *, int);

int main(int argc,char *argv[])
{
	
	cycle_stats_t stats;
    
	FILE *fin,*fout,*fp;


	int i,n,n_amost;
	short entrada,saida;
	short sample[NSAMPLES] ={0x0};
	int y=0;
	int saida1=0;
	
	short fval[NSAMPLES] ={
		#include "PassaAlta3k5_short.dat"
	};
	
	printf("***************************************************************\n");
	printf("* TESTE COM ARQUIVOS					           		      *\n");
	printf("*                                                             *\n");
	printf("***************************************************************\n");
	printf("\n");

	
	
	fin = fopen("..\\sweep4k.pcm","rb");
    	if ((fin)==NULL)
  	{
    		printf("\nErro: nao abriu o arquivo de Entrada\n");
    		return 0;
  	}
    fout = fopen("..\\outPassaAlta.pcm","wb");
    	if ((fout)==NULL)
  	{
    		printf("\nErro: nao abriu o arquivo de Saida\n");
    		return 0;
  	}
	printf("Abriu entrada e saída\n");
  
  for (i = 0; i < NSAMPLES; i++)
  {
    sample[i] = 0;
  }
  CYCLES_INIT(stats);
  printf("zerou vetor de amostras\n");
  printf("Processando ... ");
  

  do{
  	CYCLES_START(stats);
  		y = 0;

    	n_amost = fread(&entrada, sizeof(short), 1, fin);
    	sample[0] = entrada;
    	
    	for (n = 0; n < NSAMPLES; n++)
		{
		  y += fval[n] * sample[n];
		}
    	
    	for (n = NSAMPLES - 1; n > 0; n--)
	    {
	      sample[n] = sample[n - 1];
	    }
    	
	    saida1 = y >>15;
	    saida = (short)saida1;
	    printf("+1");
	    fwrite(&saida, sizeof(short), 1, fout);
	
  CYCLES_STOP(stats);
  } while (n_amost);
  
    printf("terminado!\n");
		CYCLES_PRINT(stats);
    
	
		fclose(fin);
		fclose(fout);
		
    return 0;
}


