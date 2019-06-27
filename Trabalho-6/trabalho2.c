#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

void Read_matrix();
int Get_decimal_ilbp(int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9);
int ilbp(int a ,int b);
void caracteristicas_glcm(int **glcm_matrix, float *decimal_frequency, int i);

int main () {
	FILE *fp; // ponteiro para o arquivo

	char file_name[] = "grass_01.txt"; //caminho do arquivo

	fp = fopen(file_name,"r");

	int matrix[1025][1025];//linhas/colunas
	char line[2125];
	int l = 0;
	int c = 0;
	char ch;
	char pixel_concatenation[4];
	int aux = 0;
	int number=0;

	if ( fp != NULL ) {
		while ( fgets ( line, sizeof line, fp ) != NULL ) {
			for (int i = 0 ; i < strlen(line) ; i++) {
				if(line[i] == ';' || line[i] < 48 || line[i] > 57 ) {

					pixel_concatenation[aux] = '\0';//garante o funcionamento de atoi
					number = atoi(pixel_concatenation);
					matrix[l][c]=number;

					if (c == 1024) {
						c = 0;
						l++;
					} else {
						c++;
					}

					pixel_concatenation[0] = '.';
					pixel_concatenation[1] = '.';
					pixel_concatenation[2] = '.';
					aux = 0;
				} else {
					pixel_concatenation[aux] = line[i];
					aux++;
				}
			}
		}
	}

	fclose(fp);

	float decimal_frequency[536] = {0};

	for(int a = 1 ; a < 1024 ; a++ ) {
		for (int b = 1 ; b < 1024 ; b ++) {
			decimal_frequency[Get_decimal_ilbp(
			matrix[a-1][b-1] , matrix[a-1][b] , matrix[a-1][b+1],
			matrix[a  ][b-1] , matrix[a  ][b] , matrix[a  ][b+1],
			matrix[a+1][b-1] , matrix[a+1][b] , matrix[a+1][b+1])]++;
		}
	}

	for (int i = 0;i < 512;i++) {
		printf("Decimal frequency %d = %d\n", i , decimal_frequency[i]);
	}

	int matrix_glcm_up         [256][256] = {0};
	int matrix_glcm_down       [256][256] = {0};
	int matrix_glcm_right      [256][256] = {0};
	int matrix_glcm_left       [256][256] = {0};
	int matrix_glcm_up_right   [256][256] = {0};
	int matrix_glcm_up_left    [256][256] = {0};
	int matrix_glcm_down_right [256][256] = {0};
	int matrix_glcm_down_left  [256][256] = {0};

	// Aqui começa o GLCM

	for (int i = 0; i < 1025; i++) {
		for (int j = 0 ; j < 1025 ; j++){
			if(i == 0){
				matrix_glcm_up    [ matrix[i][j] ][ matrix[1024][j]]++; 
				matrix_glcm_down  [ matrix[i][j] ][ matrix[i+1][j]]++;
			} else {	
				if(i == 1024) {
					matrix_glcm_up    [ matrix[i][j] ][ matrix[i-1][j] ] ++;
					matrix_glcm_down  [ matrix[i][j] ][ matrix[0][j] ] ++;
				} else {
					matrix_glcm_up    [ matrix[i][j] ][ matrix[i-1][j]] ++;
					matrix_glcm_down  [ matrix[i][j] ][ matrix[i+1][j]] ++;
				}
			}
			
			if(j == 0) {
				matrix_glcm_right [ matrix[i][j] ][ matrix[i  ][j+1]] ++;
				matrix_glcm_left  [ matrix[i][j] ][ matrix[i  ][ 1024 ]] ++;
			} else {
				if(j == 1024) {
					matrix_glcm_right [ matrix[i][j] ][ matrix[i][0]] ++;
					matrix_glcm_left  [ matrix[i][j] ][ matrix[i  ][j-1]] ++;
				} else {
					matrix_glcm_right [ matrix[i][j] ][ matrix[i  ][j+1]] ++;
					matrix_glcm_left  [ matrix[i][j] ][ matrix[i  ][j-1]] ++;
				}
			}

		//-------------------------diagonal superior direita ---------------------------------------

			if(i == 0 || j == 1024) {
				if(i == 0 && j == 1024)
					matrix_glcm_up_right [matrix[i][j]][matrix[1024][0] ]++;
				if(i == 0 && j < 1024)
					matrix_glcm_up_right [matrix[i][j]][matrix[1024][j+1] ]++;
				if(i > 0 && j == 1024 )
					matrix_glcm_up_right [matrix[i][j]][matrix[i-1][0] ]++;	
			} else {
				matrix_glcm_up_right [ matrix[i][j] ][matrix[i-1][j+1]]++;
			}

		//-------------------------diagonal superior esquerda ---------------------------------------

			if(i == 0 || j == 0) {
				if(i == 0 && j == 0)
					matrix_glcm_up_left [matrix[i][j]][matrix[1024][1024] ]++;
				if(i == 0 && j > 0)
					matrix_glcm_up_left [matrix[i][j]][matrix[1024][j-1] ]++;
				if(i > 0 && j == 0 )
					matrix_glcm_up_left [matrix[i][j]][matrix[i-1][1024] ]++;	
			} else {
				matrix_glcm_up_left [ matrix[i][j] ][matrix[i-1][j-1]]++;
			}

		//-------------------------diagonal inferior esquerda ---------------------------------------

			if(i == 1024 || j == 0) {
				if(i == 1024 && j == 0)
					matrix_glcm_down_left [matrix[i][j]][matrix[0][1024] ]++;
				if(j == 0 && i < 1024)
					matrix_glcm_down_left [matrix[i][j]][matrix[i+1][1024] ]++;
				if(j > 0 && i == 1024 )
					matrix_glcm_down_left [matrix[i][j]][matrix[0][j-1] ]++;	
			} else {
				matrix_glcm_down_left [ matrix[i][j] ][matrix[i+1][j-1]]++;
			}	

		//-------------------------diagonal inferirior direita ---------------------------------------


			if(i == 1024 || j == 1024) {
				if(i == 1024 && j == 1024)
					matrix_glcm_down_right [matrix[i][j]][matrix[0][0] ]++;
				if(i == 1024 && j < 1024)
					matrix_glcm_down_right [matrix[i][j]][matrix[0][j+1] ]++;
				if(j == 1024 && i < 1024 )
					matrix_glcm_down_right [matrix[i][j]][matrix[i+1][0] ]++;		
			} else {
				matrix_glcm_down_right [ matrix[i][j] ][matrix[i+1][j+1]]++;
			}	
		}
	}
	
	int posicao_no_array = 512;

	float homogeniedade = 0.00;
	float energia = 0.00;
	float contraste = 0.00;

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			homogeniedade += matrix_glcm_down[i][j]/(1 + abs(i-j));
			energia += pow(matrix_glcm_down[i][j],2);
			contraste += pow(abs(i-j),2)*matrix_glcm_down[i][j];
		}
	}
	decimal_frequency[posicao_no_array] = homogeniedade;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = energia;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = contraste;
	posicao_no_array++;

	homogeniedade = 0.00;
	energia = 0.00;
	contraste = 0.00;

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			homogeniedade += matrix_glcm_up[i][j]/(1 + abs(i-j));
			energia += pow(matrix_glcm_up[i][j],2);
			contraste += pow(abs(i-j),2)*matrix_glcm_up[i][j];
		}
	}
	decimal_frequency[posicao_no_array] = homogeniedade;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = energia;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = contraste;
	posicao_no_array++;

	homogeniedade = 0.00;
	energia = 0.00;
	contraste = 0.00;

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			homogeniedade += matrix_glcm_left[i][j]/(1 + abs(i-j));
			energia += pow(matrix_glcm_left[i][j],2);
			contraste += pow(abs(i-j),2)*matrix_glcm_left[i][j];
		}
	}
	decimal_frequency[posicao_no_array] = homogeniedade;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = energia;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = contraste;
	posicao_no_array++;

	homogeniedade = 0.00;
	energia = 0.00;
	contraste = 0.00;

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			homogeniedade += matrix_glcm_right[i][j]/(1 + abs(i-j));
			energia += pow(matrix_glcm_right[i][j],2);
			contraste += pow(abs(i-j),2)*matrix_glcm_right[i][j];
		}
	}
	decimal_frequency[posicao_no_array] = homogeniedade;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = energia;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = contraste;
	posicao_no_array++;

	homogeniedade = 0.00;
	energia = 0.00;
	contraste = 0.00;

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			homogeniedade += matrix_glcm_down_left[i][j]/(1 + abs(i-j));
			energia += pow(matrix_glcm_down_left[i][j],2);
			contraste += pow(abs(i-j),2)*matrix_glcm_down_left[i][j];
		}
	}
	decimal_frequency[posicao_no_array] = homogeniedade;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = energia;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = contraste;
	posicao_no_array++;

	homogeniedade = 0.00;
	energia = 0.00;
	contraste = 0.00;

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			homogeniedade += matrix_glcm_down_right[i][j]/(1 + abs(i-j));
			energia += pow(matrix_glcm_down_right[i][j],2);
			contraste += pow(abs(i-j),2)*matrix_glcm_down_right[i][j];
		}
	}
	decimal_frequency[posicao_no_array] = homogeniedade;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = energia;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = contraste;
	posicao_no_array++;

	homogeniedade = 0.00;
	energia = 0.00;
	contraste = 0.00;

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			homogeniedade += matrix_glcm_up_left[i][j]/(1 + abs(i-j));
			energia += pow(matrix_glcm_up_left[i][j],2);
			contraste += pow(abs(i-j),2)*matrix_glcm_up_left[i][j];
		}
	}
	decimal_frequency[posicao_no_array] = homogeniedade;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = energia;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = contraste;
	posicao_no_array++;

	homogeniedade = 0.00;
	energia = 0.00;
	contraste = 0.00;

	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < 256; j++) {
			homogeniedade += matrix_glcm_up_right[i][j]/(1 + abs(i-j));
			energia += pow(matrix_glcm_up_right[i][j],2);
			contraste += pow(abs(i-j),2)*matrix_glcm_up_right[i][j];
		}
	}
	decimal_frequency[posicao_no_array] = homogeniedade;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = energia;
	posicao_no_array++;
	decimal_frequency[posicao_no_array] = contraste;
	posicao_no_array++;

	for(int i = 0; i < 536; i++) {
		printf("%f\n",decimal_frequency[i]);
	}

	return 0;
}

void Read_matrix() {

}

//--------------------------------------------ILBP------------------------------------------------//
int Get_decimal_ilbp(int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8,int a9) {
	double media = 0;
	int matrix[3][3];

	matrix[0][0]=a1;    
	matrix[0][1]=a2;
	matrix[0][2]=a3;
	matrix[1][0]=a4;
	matrix[1][1]=a5;
	matrix[1][2]=a6;
	matrix[2][0]=a7;
	matrix[2][1]=a8;
	matrix[2][2]=a9;

	for (int i = 0; i < 3 ; i ++) {
		for (int j = 0 ; j < 3 ; j++) {
			media += matrix[i][j];
		}
	}

	media = media/9;

	//printf ("\n Media = %lf \n\n",media);

	for (int i = 0; i < 3 ; i ++) {
		for (int j = 0 ; j < 3 ; j++) {
			if(matrix[i][j] >= media ){
				matrix[i][j] = 1;
			}else{
				matrix[i][j] = 0;
			}
		}
	}

	int decimal_string[9];

	int binary_string_1[9];
	int binary_string_2[9];
	int binary_string_3[9];
	int binary_string_4[9];
	int binary_string_5[9];
	int binary_string_6[9];
	int binary_string_7[9];
	int binary_string_8[9];
	int binary_string_9[9];

	binary_string_1[0] = matrix[0][0];
	binary_string_1[1] = matrix[0][1];
	binary_string_1[2] = matrix[0][2];
	binary_string_1[3] = matrix[1][0];
	binary_string_1[4] = matrix[1][1];
	binary_string_1[5] = matrix[1][2];
	binary_string_1[6] = matrix[2][0];
	binary_string_1[7] = matrix[2][1];
	binary_string_1[8] = matrix[2][2];

	decimal_string[0] = 
	binary_string_1[8] * 1 + 
	binary_string_1[7] * 2 +
	binary_string_1[6] * 4 +
	binary_string_1[5] * 8 +
	binary_string_1[4] * 16 +
	binary_string_1[3] * 32 +
	binary_string_1[2] * 64 +
	binary_string_1[1] * 128+
	binary_string_1[0] * 256;

	binary_string_2[1] = matrix[0][0];
	binary_string_2[2] = matrix[0][1];
	binary_string_2[3] = matrix[0][2];
	binary_string_2[4] = matrix[1][0];
	binary_string_2[5] = matrix[1][1];
	binary_string_2[6] = matrix[1][2];
	binary_string_2[7] = matrix[2][0];
	binary_string_2[8] = matrix[2][1];
	binary_string_2[0] = matrix[2][2];

	decimal_string[1] =
	binary_string_2[8] * 1 +
	binary_string_2[7] * 2 +
	binary_string_2[6] * 4 +
	binary_string_2[5] * 8 +
	binary_string_2[4] * 16 +
	binary_string_2[3] * 32 +
	binary_string_2[2] * 64 +
	binary_string_2[1] * 128+
	binary_string_2[0] * 256;

	binary_string_3[2] = matrix[0][0];
	binary_string_3[3] = matrix[0][1];
	binary_string_3[4] = matrix[0][2];
	binary_string_3[5] = matrix[1][0];
	binary_string_3[6] = matrix[1][1];
	binary_string_3[7] = matrix[1][2];
	binary_string_3[8] = matrix[2][0];
	binary_string_3[0] = matrix[2][1];
	binary_string_3[1] = matrix[2][2];

	decimal_string[2] =
	binary_string_3[8] * 1 +
	binary_string_3[7] * 2 +
	binary_string_3[6] * 4 +
	binary_string_3[5] * 8 +
	binary_string_3[4] * 16 +
	binary_string_3[3] * 32 +
	binary_string_3[2] * 64 +
	binary_string_3[1] * 128+
	binary_string_3[0] * 256;

	binary_string_4[3] = matrix[0][0];
	binary_string_4[4] = matrix[0][1];
	binary_string_4[5] = matrix[0][2];
	binary_string_4[6] = matrix[1][0];
	binary_string_4[7] = matrix[1][1];
	binary_string_4[8] = matrix[1][2];
	binary_string_4[0] = matrix[2][0];
	binary_string_4[1] = matrix[2][1];
	binary_string_4[2] = matrix[2][2];

	decimal_string[3] =
	binary_string_4[8] * 1 +
	binary_string_4[7] * 2 +
	binary_string_4[6] * 4 +
	binary_string_4[5] * 8 +
	binary_string_4[4] * 16 +
	binary_string_4[3] * 32 +
	binary_string_4[2] * 64 +
	binary_string_4[1] * 128+
	binary_string_4[0] * 256;

	binary_string_5[4] = matrix[0][0];
	binary_string_5[5] = matrix[0][1];
	binary_string_5[6] = matrix[0][2];
	binary_string_5[7] = matrix[1][0];
	binary_string_5[8] = matrix[1][1];
	binary_string_5[0] = matrix[1][2];
	binary_string_5[1] = matrix[2][0];
	binary_string_5[2] = matrix[2][1];
	binary_string_5[3] = matrix[2][2];

	decimal_string[4] =
	binary_string_5[8] * 1 +
	binary_string_5[7] * 2 +
	binary_string_5[6] * 4 +
	binary_string_5[5] * 8 +
	binary_string_5[4] * 16 +
	binary_string_5[3] * 32 +
	binary_string_5[2] * 64 +
	binary_string_5[1] * 128+
	binary_string_5[0] * 256;

	binary_string_6[5] = matrix[0][0];
	binary_string_6[6] = matrix[0][1];
	binary_string_6[7] = matrix[0][2];
	binary_string_6[8] = matrix[1][0];
	binary_string_6[0] = matrix[1][1];
	binary_string_6[1] = matrix[1][2];
	binary_string_6[2] = matrix[2][0];
	binary_string_6[3] = matrix[2][1];
	binary_string_6[4] = matrix[2][2];

	decimal_string[5] =
	binary_string_6[8] * 1 +
	binary_string_6[7] * 2 +
	binary_string_6[6] * 4 +
	binary_string_6[5] * 8 +
	binary_string_6[4] * 16 +
	binary_string_6[3] * 32 +
	binary_string_6[2] * 64 +
	binary_string_6[1] * 128+
	binary_string_6[0] * 256;


	binary_string_7[6] = matrix[0][0];
	binary_string_7[7] = matrix[0][1];
	binary_string_7[8] = matrix[0][2];
	binary_string_7[0] = matrix[1][0];
	binary_string_7[1] = matrix[1][1];
	binary_string_7[2] = matrix[1][2];
	binary_string_7[3] = matrix[2][0];
	binary_string_7[4] = matrix[2][1];
	binary_string_7[5] = matrix[2][2];

	decimal_string[6] =
	binary_string_7[8] * 1 +
	binary_string_7[7] * 2 +
	binary_string_7[6] * 4 +
	binary_string_7[5] * 8 +
	binary_string_7[4] * 16 +
	binary_string_7[3] * 32 +
	binary_string_7[2] * 64 +
	binary_string_7[1] * 128+
	binary_string_7[0] * 256;

	binary_string_8[7] = matrix[0][0];
	binary_string_8[8] = matrix[0][1];
	binary_string_8[0] = matrix[0][2];
	binary_string_8[1] = matrix[1][0];
	binary_string_8[2] = matrix[1][1];
	binary_string_8[3] = matrix[1][2];
	binary_string_8[4] = matrix[2][0];
	binary_string_8[5] = matrix[2][1];
	binary_string_8[6] = matrix[2][2];

	decimal_string[7] =
	binary_string_8[8] * 1 +
	binary_string_8[7] * 2 +
	binary_string_8[6] * 4 +
	binary_string_8[5] * 8 +
	binary_string_8[4] * 16 +
	binary_string_8[3] * 32 +
	binary_string_8[2] * 64 +
	binary_string_8[1] * 128+
	binary_string_8[0] * 256;


	binary_string_9[8] = matrix[0][0];
	binary_string_9[0] = matrix[0][1];
	binary_string_9[1] = matrix[0][2];
	binary_string_9[2] = matrix[1][0];
	binary_string_9[3] = matrix[1][1];
	binary_string_9[4] = matrix[1][2];
	binary_string_9[5] = matrix[2][0];
	binary_string_9[6] = matrix[2][1];
	binary_string_9[7] = matrix[2][2];

	decimal_string[8] =
	binary_string_9[8] * 1 +
	binary_string_9[7] * 2 +
	binary_string_9[6] * 4 +
	binary_string_9[5] * 8 +
	binary_string_9[4] * 16 +
	binary_string_9[3] * 32 +
	binary_string_9[2] * 64 +
	binary_string_9[1] * 128+
	binary_string_9[0] * 256;

	/*
	for (int i =0;i<9;i++)
	printf("%d", binary_string_1[i]);
	printf("\n");
	for (int i =0;i<9;i++)
	printf("%d", binary_string_2[i]);
	printf("\n");
	for (int i =0;i<9;i++)
	printf("%d", binary_string_3[i]);
	printf("\n");
	for (int i =0;i<9;i++)
	printf("%d", binary_string_4[i]);
	printf("\n");
	for (int i =0;i<9;i++)
	printf("%d", binary_string_5[i]);
	printf("\n");
	for (int i =0;i<9;i++)
	printf("%d", binary_string_6[i]);
	printf("\n");
	for (int i =0;i<9;i++)
	printf("%d", binary_string_7[i]);
	printf("\n");
	for (int i =0;i<9;i++)
	printf("%d", binary_string_8[i]);
	printf("\n");
	for (int i =0;i<9;i++)
	printf("%d", binary_string_9[i]);
	printf("\n\n");

	for (int i =0;i<9;i++){
	printf("Binario %d = %d",i, decimal_string[i]);
	printf("\n");
	}
	*/
	int lower = 512;

	for (int i =0;i<9;i++){
		if(decimal_string[i] <= lower) {
			lower = decimal_string[i];
		}
	}

	return lower;
}

//--------------------------------------------------------------------------------------------------------//

int ilbp(int a ,int b) {

	FILE *fp; // ponteiro para o arquivo

	char file_name[] = "grass_01.txt"; //caminho do arquivo

	fp = fopen(file_name,"r");

	int matrix[1025][1025];//linhas/colunas
	char line[2125];
	int l = 0;
	int c = 0;
	char ch;
	char pixel_concatenation[4];
	int aux = 0; 
	int number=0;

	if ( fp != NULL ) {
		while ( fgets ( line, sizeof line, fp ) != NULL ) {	
			for (int i = 0 ; i < strlen(line) ; i++) {
				if(line[i] == ';' || line[i] < 48 || line[i] > 57 ) {
							
					pixel_concatenation[aux] = '\0';//garante o funcionamento de atoi
					number = atoi(pixel_concatenation);
					matrix[l][c]=number;

					if (c == 1024) {
						c = 0;
						l++;
					} else {
						c++;
					}

					pixel_concatenation[0] = '.';
					pixel_concatenation[1] = '.';
					pixel_concatenation[2] = '.';
					aux = 0;
				} else {
					pixel_concatenation[aux] = line[i];
					aux++;
				}
			}
		}
	}

	fclose(fp);
	return matrix[a][b];
}
