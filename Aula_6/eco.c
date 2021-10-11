#include <stdio.h>

void Gerador_Eco(FILE *Data_in, FILE *Data_out, int Delays[], float Pesos[]){

    fseek(Data_in, 0L, SEEK_END);
    int len = (ftell(Data_in) / 2), pos = 0, Input, Eco_Out;
    rewind(Data_in);

    short Eco[len];

    for(int i = 0; i < len; i++){

        fread(&Input, sizeof(short), 1, Data_in);
        Eco[i] = Input;
    }

    for(int i = 0; i < len; i++){

        if((pos + 1) == (sizeof(Delays)/sizeof(Delays[0]))){

            Eco_Out = Eco[i - Delays[1]] * Pesos[1];
        }else if(i < Delays[pos + 1]){
            Eco_Out = Eco[i - Delays[pos]] * Pesos[pos];
        }else{
            pos++;
        }

        fwrite(&Eco_Out, sizeof(short), 1, Data_out);
        Eco_Out = 0;
    }
}

int main()
{

    FILE *Data_in, *Data_out;

    if((Data_in = fopen("teste.pcm", "rb")) == NULL){

        printf("\nErro: Nao abriu o arquivo de entrada");
        return 0;
    }

    if((Data_out = fopen("Eco.pcm", "wb")) == NULL){

        printf("\nErro: Nao abriu o arquivo de saida");
        return 0;
    }

    int FS = 8000, d1 = 0.05*FS, d2 = 0.250*FS;
    float TS = 1/FS, P0 = 1, P1 = 0.7, P2 = 0.5;

    int Delays[2] = {d1, d2};
    float Pesos[2] = {P1, P2};

    Gerador_Eco(Data_in, Data_out, Delays, Pesos);

    fclose(Data_in);
    fclose(Data_out);

    return 0;
}