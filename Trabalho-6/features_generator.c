#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

//Funções relacionadas ao cálculo do ILBP
int* ilbp(char* img_path);
int calcula_ilbp_do_pixel(int x, int y, int matriz_img[1025][1025]);
int binario_para_decimal(int* binario_em_vetor);
void rotaciona_vetor_9(int* vetor_9);

//Funções relacionadas ao GLCM
float* glcm(char* img_path);

float* normaliza_vetor(float* vetor, int tamanho);

int main() {

    char file_path[] = "DataSet/grass/grass_49.txt";

    int* ilbp_vetor = ilbp(file_path);
    float* glcm_caracteristicas = glcm(file_path);

    float* features = (float*)malloc(536 * sizeof(float));

    for(int i = 0; i < 512; i++) {
        *(features + i) = *(ilbp_vetor + i);
    }
    for(int i = 512; i < 536; i++) {
        int temp_i = i - 512;
        *(features + i) = *(glcm_caracteristicas + temp_i);
    }

    float* features_normalizadas = normaliza_vetor(features, 536);

    FILE* features_file = fopen("Features/grass/grass_49.txt", "w");

    for(int i = 0; i < 536; i++) {
        fprintf(features_file, "%f ", *(features_normalizadas + i));
    }

    fclose(features_file);
}

int* ilbp(char* img_path) {
    FILE* img = fopen(img_path, "r");

    int matriz_img[1025][1025];
    char line[2125];
    char buffer_ponto_e_virgula;

    if ( img != NULL ) {
		for(int i = 0; i < 1025; i++) {
          for(int j = 0; j < 1025; j++) {
            if(feof(img))
              break;
            else 
                fscanf(img, "%d%c", &matriz_img[i][j], &buffer_ponto_e_virgula);
            }
	    }
    }

    int* ilbp_vetor = (int*)calloc(512, sizeof(int));

    for(int i = 1; i < 1024; i++) {
        for(int j = 1; j < 1024; j++) {
            int ilbp_position = calcula_ilbp_do_pixel(i, j, matriz_img);
            *(ilbp_vetor + ilbp_position) = *(ilbp_vetor + ilbp_position) + 1;
        }
    }
    fclose(img);
    return ilbp_vetor;
}

int calcula_ilbp_do_pixel(int x, int y, int matriz_img[1025][1025]) {
    int vetor_vizinhanca_de_8[9] = {matriz_img[x-1][y-1], matriz_img[x][y-1], matriz_img[x+1][y-1], 
                                    matriz_img[x-1][y], matriz_img[x][y], matriz_img[x+1][y],
                                    matriz_img[x-1][y+1], matriz_img[x][y+1], matriz_img[x+1][y+1]};
    
    int media = 0;
    int i = 0;

    for(i = 0; i < 9; i++) {
        media += vetor_vizinhanca_de_8[i];
    }
    media /= 9;

    int* vetor_gerado_da_media = (int*)malloc(sizeof(int) * 9);

    for(i = 0; i < 9; i++) {
        if(vetor_vizinhanca_de_8[i] < media)
            vetor_gerado_da_media[i] = 0;
        else
            vetor_gerado_da_media[i] = 1;
    }

    int* vetor_decimais = (int*)malloc(sizeof(int) * 9);

    for(i = 0; i < 9; i++) {
        *(vetor_decimais + i) = binario_para_decimal(vetor_gerado_da_media);
        rotaciona_vetor_9(vetor_gerado_da_media);
    }

    int menor_valor;

    for(i = 1; i < 9; i++) {
        if(*(vetor_decimais + i) <= vetor_decimais[i-1])
            menor_valor = vetor_decimais[i];
    }
    return menor_valor;
}

int binario_para_decimal(int* binario_em_vetor) {
    int decimal = 0;

    for(int i = 0; i < 9; i++) {
        if(binario_em_vetor[i] != 0)
            decimal += pow(2, 8 - i);
    }
    return decimal;
}

void rotaciona_vetor_9(int* vetor_9) {
    int temp[9];
    for(int i = 0; i < 9; i++) {
        temp[i] = vetor_9[i];
    }

    vetor_9[0] = temp[8];
    vetor_9[1] = temp[0];
    vetor_9[2] = temp[1];
    vetor_9[3] = temp[2];
    vetor_9[4] = temp[3];
    vetor_9[5] = temp[4];
    vetor_9[6] = temp[5];
    vetor_9[7] = temp[6];
    vetor_9[8] = temp[7];
}

float* glcm(char* img_path) {
    FILE* img = fopen(img_path, "r");

    int matriz_img[1025][1025];
    char line[2125];
    char buffer_ponto_e_virgula;

    if ( img != NULL ) {
		for(int i = 0; i < 1025; i++) {
          for(int j = 0; j < 1025; j++) {
            if(feof(img))
              break;
            else 
                fscanf(img, "%d%c", &matriz_img[i][j], &buffer_ponto_e_virgula);
            }
	    }
    }

    int posicao_vizinho[8][2] = {{-1,-1}, {0, -1}, {1, -1},
                                 {-1, 0},          {1, 0},
                                 {-1, 1}, {0, 1},  {1, 1}};

    int matriz_glcm[8][256][256] = {0};

    for(int posicao = 0; posicao < 8; posicao++) {
        for(int i = 1; i < 1024; i++) {
            for(int j = 1; j < 1024; j++) {
                int x = matriz_img[i][j];
                int y = matriz_img[i + posicao_vizinho[posicao][0]][i + posicao_vizinho[posicao][1]];

                matriz_glcm[posicao][x][y]++;
            }
        }
    }

    float* features = (float*)calloc(24, sizeof(float));

    for(int posicao = 0; posicao < 8; posicao++) {
        double homogeniedade = 0.00;
	    double energia = 0.00;
	    double contraste = 0.00;

        int posicao_na_feature = posicao * 3;

        int somatorio_glcm = 0;

        for(int i = 0; i < 256; i++) {
            for(int j = 0; j < 256; j++) {
                somatorio_glcm += matriz_glcm[posicao][i][j];
            }
        }

        for(int i = 0; i < 256; i++) {
            for(int j = 0; j < 256; j++) {
                int mod = abs(i-j);
                double glcm_normalizado = (double)matriz_glcm[posicao][i][j]/somatorio_glcm;

                homogeniedade += (double)glcm_normalizado/ (1 + mod);
                energia += pow((double)glcm_normalizado, 2);
                contraste += pow(mod, 2)*(double)glcm_normalizado;
            }
        }

        *(features + posicao_na_feature) = homogeniedade;
        *(features + posicao_na_feature + 1) = energia;
        *(features + posicao_na_feature + 2) = contraste;
    }
    fclose(img);
    return features;
}

float* normaliza_vetor(float* vetor, int tamanho) {
    int min = 999999999;
    int max = 0;
    float* vetor_normalizado = (float*)malloc(536 * sizeof(float));

    for(int i = 0; i < tamanho; i++) {
        if(*(vetor + i) <= min)
            min = *(vetor + i);
        if(*(vetor + i) >= max)
            max = *(vetor + i);
    }

    for(int i = 0; i < tamanho; i++)
        *(vetor_normalizado + i) = (float)(*(vetor + i) - min)/ max - min;

    return vetor_normalizado;
}