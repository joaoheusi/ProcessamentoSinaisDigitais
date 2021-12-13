#include <stdio.h>
#include <string.h>
#include <cycles.h>

#define NSAMPLES 80 // quantidade de coef

static int frameCount = 1;

extern void proc_file( short *, short *, int);

int main() {
  FILE * in_file, * out_file;
  cycle_stats_t stats;   
  int i, n, n_amost;
  float mi = 0.0000000000005;
  int y = 0, dn = 0;
  int erro = 0;
  int saida1 =0;


  short entrada, saida;
  short sample[NSAMPLES];

  short wn[NSAMPLES];

  CYCLES_INIT(stats);
  //Carregando os coeficientes do filtro m�dia m�vel
  short coef[NSAMPLES] = {
        #include "Coefs_PA_1k_short.dat" // NSAMPLES
  };

  /* abre os arquivos de entrada e saida */
  if ((in_file = fopen("..\\sweep_4k.pcm", "rb")) == NULL) {
    printf("\nErro: Nao abriu o arquivo de entrada\n");
    return 0;
  };
  if ((out_file = fopen("..\\resultado_filtro_adaptativo_c_short.pcm", "wb")) == NULL) {
    printf("\nErro: Nao abriu o arquivo de saida\n");
    return 0;
  };

  // zera vetor de amostras
  for (i = 0; i < NSAMPLES; i++) {
    sample[i] = 0;
    wn[i] = 0.0;
  };
	
  
  // execu��o do filtro
  do{
  	CYCLES_START(stats);
	
    //zera sa�da do filtro
    y = 0;
    dn = 0;
    //l� dado do arquivo
    n_amost = fread( & entrada, sizeof(short), 1, in_file);
    sample[0] = entrada;

    //Convolu��o da saida esperada
    for (n = 0; n < NSAMPLES; n++) {
      dn += coef[n] * sample[n];
    };

    // convolu��o da saida esperada
    int j;
    for (j= 0; j < NSAMPLES; j++) {
        y += wn[j] * sample[j];
    };


    erro = dn - y;

    //desloca amostra
    for (n = 0; n < NSAMPLES; n++) {
        wn[n] = wn[n] + 2.0 * mi * erro * sample[n];
    };

    //desloca amostra
    for (n = NSAMPLES - 1; n > 0; n--) {
        sample[n] = sample[n - 1];
    };

    saida1 =  erro >> 15 ;
    saida = (short) saida1;
	CYCLES_STOP(stats);
    //escreve no arquivo de sa�da
    fwrite( & saida, sizeof(short), 1, out_file);

  }while(n_amost);
  printf("\nAqui\n");
  
	
  //fecha os arquivos de entrada de sa�da
  CYCLES_PRINT(stats);
  fclose(out_file);
  fclose(in_file);
  return 0;
  
}

