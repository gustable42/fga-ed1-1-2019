/*
## Alunos 
* Gustavo Veloso - 17/0065251
* Wictor Girardi - 17/0047326
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ALCANCE_MAX 15000
#define NUM_DE_FEATURES 536

typedef struct Neuronio {
    double *pesos;
    double bias;
} Neuronio;

double* montar_vetor(char* file_path);
double** montar_vetores();
double gerar_numero_aleatorio();
Neuronio* criar_camada(Neuronio* camada, int num_pesos, int num_neuronios);
Neuronio** criar_rede_neural(int tam_camada_escondida);
double* alimentar_camada(Neuronio* camada, int num_features, int num_neuronios, double* features);
double derivada_f_logistica(double x);
void backpropagation(Neuronio** rede_neural, double* features, double erro, double* vetor_1_p_2, double* vetor_2_p_3, double saida, int tam_camada_escondida);
double calcular_MSE(double *erros);

int main(int argc, char *argv[]) {
    double mse = 1;
    double erros[50] = {0};
    int epoca = 0;
    int tam_camada_escondida = atoi(argv[1]);
    Neuronio** rede_neural = criar_rede_neural(tam_camada_escondida);
    double** features = montar_vetores();

    printf("teste antes de entrar no while\n");

    while(epoca <= 1000 || mse > 0.2) {
        printf("teste antes de entrar em cada for\n");
        for(int i = 0; i < 50; i++) {
            printf("teste dentro do for\n");

            printf("a\n");
            double* vetor_1_p_2 = alimentar_camada(rede_neural[0], 536, 536, features[i]);
            printf("a\n");
            double* vetor_2_p_3 = alimentar_camada(rede_neural[1], 536, tam_camada_escondida, vetor_1_p_2);
            printf("a\n");
            double* vetor_3 = alimentar_camada(rede_neural[2], tam_camada_escondida, 1, vetor_2_p_3);
            printf("a\n");
            double saida_3 = *(vetor_3);

            printf("teste depois de alimentar as camadas\n");

            if(i % 2 == 0) erros[i] = 0 - saida_3;
            else erros[i] = 1 - saida_3;

            printf("teste antes do backpropagation\n");

            backpropagation(rede_neural, features[i], erros[i], vetor_1_p_2, vetor_2_p_3, saida_3, tam_camada_escondida);

            printf("teste depois do backpropagation\n");

            free(vetor_1_p_2);
            free(vetor_2_p_3);
            free(vetor_3);
        }
        mse = calcular_MSE(erros);
        epoca++;
        printf("\nÉpoca %d\n", epoca);
        printf("MSE: %lf\n", mse);
    }

    return 0;
}

double* montar_vetor(char* file_path) {
    FILE* features = fopen(file_path, "r");
    double* vetor = (double*)malloc(536 * sizeof(double));

    char buffer_espaco;

    if ( features != NULL ) {
		for(int i = 0; i < 536; i++) {
            if(feof(features))
                break;
            else 
                fscanf(features, "%lf%c", (vetor + i), &buffer_espaco);
	    }
    }

    fclose(features);
    return vetor;
}

double** montar_vetores() {
    char* files_id[25] = {"01", "03", "04", "06", "09", "12", "15", "16", "18", "19", "23", "24", "27", "28", "29", "31", "33", "34", "36", "39", "40", "42", "43", "46", "49"};
    double** features = (double**)malloc(50 * sizeof(double*));
    for( int i = 0; i < 50; i++)
        features[i] = (double*)malloc(536 * sizeof(double));

    for(int i = 0; i < 25; i++) {
        char txt[5] = ".txt";

        char file_path_asphalt[50] = "Features/asphalt/asphalt_";
        strcat(file_path_asphalt, files_id[i]);
        strcat(file_path_asphalt, txt);

        char file_path_grass[50] = "Features/grass/grass_";
        strcat(file_path_grass, files_id[i]);
        strcat(file_path_grass, txt);

        int posicao = i * 2;

        features[posicao] = montar_vetor(file_path_asphalt);
        features[posicao + 1] = montar_vetor(file_path_grass);
    }

    return features;
}

double gerar_numero_aleatorio()  {
    double numero_aleatorio = rand() % ALCANCE_MAX;
    double signal = rand() % 2;
    if(signal == 0) signal = -1;
    else signal = 1;

    if(numero_aleatorio == 0) numero_aleatorio++; 

    return signal * numero_aleatorio;
}

Neuronio* criar_camada(Neuronio* camada, int num_pesos, int num_neuronios) {
    for(int i = 0; i < num_neuronios; i++) {
        Neuronio neuronio_temp;

        neuronio_temp.pesos = (double*)malloc(num_pesos * sizeof(double));
        for(int j = 0; j < num_neuronios; j++)
            *(neuronio_temp.pesos + j) = gerar_numero_aleatorio();

        neuronio_temp.bias = gerar_numero_aleatorio();
        *(camada + i) = neuronio_temp;
    }
    
    return camada;
}

Neuronio** criar_rede_neural(int tam_camada_escondida) {
    Neuronio** rede_neural = (Neuronio**)malloc(3 * sizeof(Neuronio*));

    rede_neural[0] = (Neuronio*)malloc(536 * sizeof(Neuronio));
    rede_neural[1] = (Neuronio*)malloc(tam_camada_escondida * sizeof(Neuronio));
    rede_neural[2] = (Neuronio*)malloc(1 * sizeof(Neuronio));

    rede_neural[0] = criar_camada(rede_neural[0], 536, 536);
    rede_neural[1] = criar_camada(rede_neural[0], 536, tam_camada_escondida);
    rede_neural[2] = criar_camada(rede_neural[0], tam_camada_escondida, 1);

    return rede_neural;

}

double* alimentar_camada(Neuronio* camada, int num_features, int num_neuronios, double* features) {
    printf("--- comeco alimentar camada ---\n");
    double* vetor_resultante = (double*)malloc(sizeof(double) * num_neuronios);
    const double e = 2.7182818284;

    for(int i = 0; i < num_neuronios; i++) {
        double somatorio = camada[i].bias;
        printf("bias = %.2lf\n", camada[i].bias);
        for(int j = 0; j < num_features; j++) {
            printf("peso = %.2lf\n", camada[i].pesos[j]);
            somatorio += features[j] * camada[i].pesos[j];
        }
        vetor_resultante[i] = (double)1.0/(1.0 + pow(e, -somatorio));
    }
    printf("--- finalizou alimentar camada ---\n");

    return vetor_resultante;
}

double derivada_f_logistica(double x) {
    const double e = 2.7182818284;

    return pow(e, -x)/pow(pow(e, -x) + 1.0, 2.0);
}

void backpropagation(Neuronio** rede_neural, double* features, double erro, double* vetor_1_p_2, double* vetor_2_p_3, double saida, int tam_camada_escondida) {
    int tam_entrada = 536;
    
    double delta;
    double deltas[tam_camada_escondida];
    double pesos12[tam_camada_escondida][tam_entrada], pesos23[tam_camada_escondida];

    Neuronio* camada_de_entrada = rede_neural[0];
    Neuronio* camada_escondida = rede_neural[1];
    Neuronio* camada_de_saida = rede_neural[2];

    for(int i = 0; i < tam_camada_escondida; i++) {
        for(int j = 0; j < tam_entrada; j++)
            pesos12[i][j] = camada_escondida[i].pesos[j];
    }

    for(int i = 0; i < tam_camada_escondida; i++)
        pesos23[i] = camada_de_saida[0].pesos[i];

    double saidaDelta = derivada_f_logistica(saida) * erro;

    for(int i = 0; i < tam_camada_escondida; i++) {
        camada_de_saida[0].pesos[i] += vetor_2_p_3[i] * saidaDelta;
    }

    camada_de_saida[0].bias += saidaDelta;

    for(int i = 0; i < tam_camada_escondida; i++){
        delta = derivada_f_logistica(vetor_2_p_3[i]) * pesos23[i] * saidaDelta;

        for(int j = 0; j < tam_entrada; j++)
            camada_escondida[i].pesos[j] += vetor_1_p_2[j] * delta;

        camada_escondida[i].bias += delta;
        deltas[i] = delta;
    }

    for(int i = 0; i < tam_entrada; i++) {
        double somatorio = 0;

        for(int j = 0; j < tam_camada_escondida; j++)
            somatorio += deltas[j] * pesos12[j][i];

        delta = derivada_f_logistica(vetor_1_p_2[i]) * somatorio;     

        for(int k = 0; k < tam_entrada; k++)
            camada_de_entrada[i].pesos[k] += features[k] * delta;
        camada_de_entrada[i].bias += delta;
    } 
}

double calcular_MSE(double *erros) {
    double somatorio = 0.0;
    for(int i = 0; i < 50; i++)
        somatorio += pow(erros[i], 2);

    double MSE = somatorio/50.00;
    return MSE;
}