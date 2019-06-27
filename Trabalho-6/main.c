#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float* montar_vetor(char* file_path);
char* concatenar_file_path(int type, const char file_number[3]);

int main(int argc, char *argv[]) {
    char* files_id[25] = {"01", "03", "04", "06", "09", "12", "15", "16", "18", "19", "23", "24", "27", "28", "29", "31", "33", "34", "36", "39", "40", "42", "43", "46", "49"};
    float* features[50];
    for( int i = 0; i < 50; i++)
        features[i] = (float*)malloc(536 * sizeof(float));

    for(int i = 0; i < 25; i++) {
        char file_path_asphalt[50];
        char file_path_grass[50];
        
        strcpy(file_path_asphalt, concatenar_file_path(0, files_id[i]));
        strcpy(file_path_grass, concatenar_file_path(1, files_id[i]));

        int posicao = i * 2;
        
        printf("%s\n",file_path_asphalt);

        features[posicao] = montar_vetor(file_path_asphalt);
        features[posicao + 1] = montar_vetor(file_path_grass);
    }

    // for(int vetor = 0; vetor < 50; vetor++) {
    //     for(int feature = 0; feature < 536; feature++) {
    //         printf("%.5f ", *(*(features + vetor) + feature));
    //     }
    //     printf("\n");
    // }

    return 0;
}

float* montar_vetor(char* file_path) {
    // printf("%s\n", file_path);
    FILE* features = fopen(file_path, "r");
    float* vetor = (float*)malloc(536 * sizeof(float));

    char buffer_espaco;

    if ( features != NULL ) {
		for(int i = 0; i < 536; i++) {
            if(feof(features))
                break;
            else 
                fscanf(features, "%f%c", (vetor + i), &buffer_espaco);
	    }
    }
    fclose(features);


    return vetor;
}

/*
    Type == 0 => asphalt
    Type == 1 => grass
 */
char* concatenar_file_path(int type, const char file_id[3]) {

    switch(type) {
        case 0:
        {
            char file_path[50] = "Features/asphalt/asphalt_";
            strcat(file_path, file_id);
            char txt[5] = ".txt";
            strcat(file_path, txt);

            return file_path;
        }
        case 1:
        {
            char file_path[50] = "Features/grass/grass_";
            strcat(file_path, file_id);
            char txt[5] = ".txt";
            strcat(file_path, txt);

            return file_path;
        }
    }
}