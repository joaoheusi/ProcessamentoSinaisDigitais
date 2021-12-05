/* programa para testes com arquivos
-- Lendo arquivo de entrada
-- Processa
-- Gera arquivo de saida
-- walter 1.0 
*/

#include <stdio.h>
#include <string.h>



#define 	FrameSize 1


static int frameCount = 1;

extern void proc_file( short *, short *, int);

int main(int argc,char *argv[])
{
    
	FILE *fin,*fout,*fp;

  short Vet_entr[FrameSize];
  short Vet_sai[FrameSize];
  
	
	int i,n,n_amost;
	short entrada,saida;
	short sample[NSAMPLES] = {0x0};
	
	printf("***************************************************************\n");
	printf("* TESTE COM ARQUIVOS					           		      *\n");
	printf("*                                                             *\n");
	printf("***************************************************************\n");
	printf("\n");
	
	
	fp = fopen("..\\PassaAlta6kV2.txt","rb");
		if((fp) == NULL)
	{
		printf("\nErro: nao abriu o arquivo dos coeficientes\n");
		return 0
	}		
	
	fin = fopen("..\\audio_tst.pcm","rb");
    	if ((fin)==NULL)
  	{
    		printf("\nErro: nao abriu o arquivo de Entrada\n");
    		return 0;
  	}
    fout = fopen("..\\sai_audio_tst.pcm","wb");
    	if ((fout)==NULL)
  	{
    		printf("\nErro: nao abriu o arquivo de Saida\n");
    		return 0;
  	}

  	
  printf("Processando ... ");

  while (fread(Vet_entr,sizeof(short),FrameSize,fin) == FrameSize) 
  {

		proc_file( Vet_sai, Vet_entr, FrameSize);

		
		fwrite(&Vet_sai,sizeof(short),FrameSize,fout);	
	
		frameCount++;
	}

    printf("terminado!\n");
		
    
	
		fclose(fin);
		fclose(fout);
		
    return 0;
}


