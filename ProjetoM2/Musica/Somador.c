#include <stdio.h>
#include <fcntl.h>
#include <io.h>

#define NSAMPLES 1764 // Tamanho da média

int main()
{
  FILE *in_filePA, *in_filePB, *in_filePF, *out_file, *fp;
  int i, n, n_amost, n_PA, n_PB,n_PF;

  short entradaPA,entradaPB,entradaPF, saida;
  short samplePA[NSAMPLES] = {0x0};
  short samplePB[NSAMPLES] = {0x0};
  short samplePF[NSAMPLES] = {0x0};

  float ganhoPA, ganhoPF, ganhoPB;
  ganhoPA = 1.5;
  ganhoPF = 1.4;
  ganhoPB = 0.7;

  float y = 0;

  //Carregando os coeficientes do filtro média móvel

  /* abre os arquivos de entrada e saida */
  if ((in_filePA = fopen("Sweep_PA.pcm", "rb")) == NULL)
  {
    printf("\nErro: Nao abriu o arquivo de entrada\n");
    return 0;
  }
  if ((in_filePB = fopen("Sweep_PB.pcm", "rb")) == NULL)
  {
    printf("\nErro: Nao abriu o arquivo de entrada\n");
    return 0;
  }
  if ((in_filePF = fopen("Sweep_PF.pcm", "rb")) == NULL)
  {
    printf("\nErro: Nao abriu o arquivo de entrada\n");
    return 0;
  }

  if ((out_file = fopen("Sweep_Somado.pcm", "wb")) == NULL)
  {
    printf("\nErro: Nao abriu o arquivo de saida\n");
    return 0;
  }

  // execução do filtro
  do
  {

    //zera saída do filtro
    y = 0;

    //lê dado do arquivo
    n_PA = fread(&entradaPA, sizeof(short), 1, in_filePA);
    n_PB = fread(&entradaPB, sizeof(short), 1, in_filePB);
    n_PF = fread(&entradaPF, sizeof(short), 1, in_filePF);
    samplePA[0] = entradaPA;
    samplePB[0] = entradaPB;
    samplePF[0] = entradaPF;

    y = (samplePA[0]*ganhoPA)+(samplePB[0]*ganhoPB)+(samplePF[0]*ganhoPF);

    saida = (short)y;

    //escreve no arquivo de saída
    fwrite(&saida, sizeof(short), 1, out_file);

  } while (n_PA);

  //fecha os arquivos de entrada de saída
  fclose(out_file);
  fclose(in_filePA);
  fclose(in_filePB);
  fclose(in_filePF);
  return 0;
}