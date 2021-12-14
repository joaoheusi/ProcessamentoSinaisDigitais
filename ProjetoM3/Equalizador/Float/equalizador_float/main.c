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
#define NSAMPLES 1764 

static int frameCount = 1;

extern void proc_file( short *, short *, int);

int main(int argc,char *argv[])
{
	cycle_stats_t stats;
    
	FILE *in_filePA, *in_filePB, *in_filePF, *out_file, *fp;
  int i, n, n_amost, n_PA, n_PB,n_PF;

  short entradaPA,entradaPB,entradaPF, saida;
  short samplePA[NSAMPLES] = {0x0};
  short samplePB[NSAMPLES] = {0x0};
  short samplePF[NSAMPLES] = {0x0};

  float ganhoPA, ganhoPF, ganhoPB;
  ganhoPA = 1;
  ganhoPF = 1;
  ganhoPB = 1;

  float y = 0;
  CYCLES_INIT(stats);

  //Carregando os coeficientes do filtro m�dia m�vel

  /* abre os arquivos de entrada e saida */
  if ((in_filePA = fopen("..\\outPassaAlta.pcm", "rb")) == NULL)
  {
    printf("\nErro: Nao abriu o arquivo de entrada1\n");
    return 0;
  }
  if ((in_filePB = fopen("..\\outPassaBaixa.pcm", "rb")) == NULL)
  {
    printf("\nErro: Nao abriu o arquivo de entrada2\n");
    return 0;
  }
  if ((in_filePF = fopen("..\\outPassaFaixa.pcm", "rb")) == NULL)
  {
    printf("\nErro: Nao abriu o arquivo de entrada3\n");
    return 0;
  }

  if ((out_file = fopen("..\\Sweep_Somado_1.pcm", "wb")) == NULL)
  {
    printf("\nErro: Nao abriu o arquivo de saida4\n");
    return 0;
  }

  // execu��o do filtro
  do
  {
  	CYCLES_START(stats);

    //zera sa�da do filtro
    y = 0;

    //l� dado do arquivo
    n_PA = fread(&entradaPA, sizeof(short), 1, in_filePA);
    n_PB = fread(&entradaPB, sizeof(short), 1, in_filePB);
    n_PF = fread(&entradaPF, sizeof(short), 1, in_filePF);
    samplePA[0] = entradaPA;
    samplePB[0] = entradaPB;
    samplePF[0] = entradaPF;

    y = (samplePA[0]*ganhoPA)+(samplePB[0]*ganhoPB)+(samplePF[0]*ganhoPF);

    saida = (short)y;

    //escreve no arquivo de sa�da
    fwrite(&saida, sizeof(short), 1, out_file);
	CYCLES_STOP(stats);
  } while (n_PA);

  //fecha os arquivos de entrada de sa�da
  CYCLES_PRINT(stats);
  fclose(out_file);
  fclose(in_filePA);
  fclose(in_filePB);
  fclose(in_filePF);
  return 0;
}


