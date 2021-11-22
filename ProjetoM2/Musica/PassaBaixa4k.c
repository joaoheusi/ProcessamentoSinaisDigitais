#include <stdio.h>
#include <fcntl.h>
#include <io.h>

#define NSAMPLES 1764 // Tamanho da média

int main()
{
  FILE *in_file, *out_file, *fp;
  int i, n, n_amost;

  short entrada, saida;
  short sample[NSAMPLES] = {0x0};

  float y = 0;

  //Carregando os coeficientes do filtro média móvel

  float fval[1764];
  int coefsN, coefsI;

  fp = fopen("PassaBaixa4k.txt", "rb");
  if (fp == NULL)
  {
    printf("failed to open file\n");
    return 1;
  }
  rewind(fp);
  coefsN = 0;
  while (fscanf(fp, "%f", &fval[coefsN++]) != EOF)
    ;

  fclose(fp);
  printf("Leu os coefs\n");
  /* abre os arquivos de entrada e saida */
  if ((in_file = fopen("Sweep.pcm", "rb")) == NULL)
  {
    printf("\nErro: Nao abriu o arquivo de entrada\n");
    return 0;
  }
  if ((out_file = fopen("Sweep_PB.pcm", "wb")) == NULL)
  {
    printf("\nErro: Nao abriu o arquivo de saida\n");
    return 0;
  }
  printf("Abriu entrada e saída\n");
  // zera vetor de amostras
  for (i = 0; i < NSAMPLES; i++)
  {
    sample[i] = 0;
  }
  printf("zerou vetor de amostras\n");
  // execução do filtro
  do
  {

    //zera saída do filtro
    y = 0;

    //lê dado do arquivo
    n_amost = fread(&entrada, sizeof(short), 1, in_file);
    sample[0] = entrada;

    //Convolução e acumulação
    for (n = 0; n < NSAMPLES; n++)
    {
      y += fval[n] * sample[n];
    }

    //desloca amostra
    for (n = NSAMPLES - 1; n > 0; n--)
    {
      sample[n] = sample[n - 1];
    }

    saida = (short)y;

    //escreve no arquivo de saída
    fwrite(&saida, sizeof(short), 1, out_file);

  } while (n_amost);

  //fecha os arquivos de entrada de saída
  fclose(out_file);
  fclose(in_file);
  return 0;
}