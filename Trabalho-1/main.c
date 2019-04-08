#include <stdio.h>
#include <stdlib.h>
#define NUMERO_DE_ALUNOS 10

void recebe_notas(float *NOTAS, int numero_de_elementos, int *APR);
void conta_notas(int *APR, int numero_de_elementos, int *aprovados, int *reprovados);
int percent_aprov(float *percentual_aprovados, float *percentual_reprovados, int *aprovados, int *reprovados);

int main() {
    float NOTAS[NUMERO_DE_ALUNOS];
    int APR[NUMERO_DE_ALUNOS];
    int aprovados = 0;
    int reprovados = 0;
    float percentagem_aprovados = 0.00;
    float percentagem_reprovados = 0.00;

    printf("Insira a nota dos 10 alunos:\n");
    for(int i = 0; i < NUMERO_DE_ALUNOS; i++) {
        scanf("%f",&NOTAS[i]);
    }
    printf("\n");
    

    recebe_notas(NOTAS, NUMERO_DE_ALUNOS, APR);
    conta_notas(APR, NUMERO_DE_ALUNOS, &aprovados, &reprovados);

    int maioria_aprovados = percent_aprov(&percentagem_aprovados, &percentagem_reprovados, &aprovados, &reprovados);

    printf("Aluno(s) aprovado(s): %d\n", aprovados);
    printf("Aluno(s) reprovados(s): %d\n", reprovados);
    printf("%.2f%% dos alunos foram aprovados\n", percentagem_aprovados);
    printf("%.2f%% dos alunos foram reprovados\n", percentagem_reprovados);
    if(maioria_aprovados == 1) printf("A maioria dos alunos foi aprovada\n");
    else printf("A maioria dos alunos não conseguiram aprovação\n");

    return 0;
}

void recebe_notas(float *NOTAS, int numero_de_elementos, int *APR) {
    for(int i = 0; i < numero_de_elementos; i++) {
        if( *(NOTAS+i) >= 6.0 ) *(APR + i) = 1;
        else *(APR + i) = 0;
    }
}

void conta_notas(int *APR, int numero_de_elementos, int *aprovados, int *reprovados) {
    for(int i = 0; i < numero_de_elementos; i++) {
        if( *(APR + i) == 1 ) *(aprovados) += 1;
        else *(reprovados) += 1;
    }
}

int percent_aprov(float *percentual_aprovados, float *percentual_reprovados, int *aprovados, int *reprovados) {
    int total_de_alunos = (*aprovados + *reprovados); 
    *percentual_aprovados = (*aprovados/(float)total_de_alunos)*100.00;
    *percentual_reprovados = (*reprovados/(float)total_de_alunos)*100.00;

    if(*percentual_aprovados > 50.00) return 1;
    else return 0;
}