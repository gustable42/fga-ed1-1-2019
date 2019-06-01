#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct voo {
    char codigo_do_voo[6];
    char modo_do_voo;
    unsigned int nivel_de_combustivel;

    struct voo* de_tras;
} voo;

typedef struct fila {
    struct voo* primeiro;
    struct voo* ultimo;
} fila;

struct voo* criar_novo_voo(char* codigo_do_voo, char modo_do_voo);
struct fila* criar_nova_fila();
void colocar_voo_na_fila(fila* fila, voo* voo);
struct voo* tirar_voo_da_fila(fila* fila);
void mostrar_fila(fila* fila);

int gerar_numero_aleatorio(unsigned int min, unsigned int max);
void gerar_vetor_de_numeros_aleatorios(unsigned int* vetor);
int existe_no_vetor(unsigned int numero_sorteado, int* vetor);

int main() {

    struct voo* voo1 = criar_novo_voo("AG3333", 'A');
    struct voo* voo2 = criar_novo_voo("AG3323", 'A');
    struct voo* voo3 = criar_novo_voo("AG3313", 'D');
    struct fila* fila = criar_nova_fila();
    colocar_voo_na_fila(fila, voo1);
    colocar_voo_na_fila(fila, voo2);
    colocar_voo_na_fila(fila, voo3);
    mostrar_fila(fila);
    struct voo* voo_retirado = tirar_voo_da_fila(fila);
    printf("Voo retirado: %s\n", voo_retirado->codigo_do_voo);
    mostrar_fila(fila);


    return 0;
}

struct voo* criar_novo_voo(char* codigo_do_voo, char modo_do_voo) {
    voo* novo_voo = (struct voo*)malloc(sizeof(struct voo));
    if(novo_voo == NULL) exit(1);

    strcpy(novo_voo->codigo_do_voo, codigo_do_voo);
    novo_voo->modo_do_voo = modo_do_voo;
    novo_voo->nivel_de_combustivel = gerar_numero_aleatorio(0, 12);

    novo_voo->de_tras = NULL;

    return novo_voo;
}

struct fila* criar_nova_fila() {
    fila* nova_fila = (struct fila*)malloc(sizeof(struct fila));
    if(nova_fila == NULL) exit(1);

    nova_fila->primeiro = NULL;
    nova_fila->ultimo = NULL;

    return nova_fila;
}

void colocar_voo_na_fila(struct fila* fila, struct voo* voo) {
    if(fila->primeiro == NULL) {
        fila->primeiro = voo;
        fila->ultimo = voo;
    }
    fila->ultimo->de_tras = voo;
    fila->ultimo = voo;
}

struct voo* tirar_voo_da_fila(struct fila* fila) {
    if(fila->primeiro == NULL)
        return NULL;

    struct voo* voo = fila->primeiro;
    fila->primeiro = fila->primeiro->de_tras;

    return voo;
    
}

void mostrar_fila(fila* fila) {
    struct voo* voo_atual = fila->primeiro;
    printf("---\n");
    while(voo_atual) {
        printf("%s\n", voo_atual->codigo_do_voo);

        voo_atual = voo_atual->de_tras;
    }
    printf("---\n");
}

int gerar_numero_aleatorio(unsigned int min, unsigned int max) {
    return (rand() % (max + 1 - min)) + min;
}

void gerar_vetor_de_numeros_aleatorios(unsigned int* vetor) {
    for(int i = 0; i < 44; i++) {
        int numero_aleatorio = gerar_numero_aleatorio(20, 64);
        if(!existe_no_vetor(numero_aleatorio, vetor))
            vetor[i] = numero_aleatorio;
        else
            i--;
    }
}

int existe_no_vetor(unsigned int numero_sorteado, int* vetor) {
    for(int i = 0; i < 44; i++) {
        if(numero_sorteado == vetor[i]) return 1;
    }
    return 0;
}