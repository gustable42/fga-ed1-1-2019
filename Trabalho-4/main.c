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

typedef struct pista {
    int num_pista;
    struct voo* voo_alocado_a_pista;
    int tempo_necessario;
} pista;

char codigo_voos[64][7] = {"VG3001", "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009", "AZ1008", "AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880", "AL0012", "TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002", "AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001", "LN7003",  "AZ1004",  "TG1504",  "AZ1005",  "TG1502",  "GL7601", "TT4500", "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392", "GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065", "LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510", "TT1020",  "AZ1098",  "BA2312",  "VG3030",  "BA2304",  "KL5609", "KL5610", "KL5611"};

voo* primeiro_da_lista = NULL;

struct voo* criar_novo_voo(char* codigo_do_voo, unsigned int nivel_de_combustivel, char modo_do_voo);
struct fila* criar_nova_fila();
struct pista* criar_nova_pista(int pista);

void liberar_voo_da_lista(struct voo* voo);

void colocar_voo_na_fila(fila* fila, voo* voo);
void colocar_voos_na_fila(fila* fila);
void colocar_voo_na_pista(pista* pista, fila* fila, int tempo);

struct voo* tirar_voo_da_fila(fila* fila);
int tirar_voo_da_fila_force(struct fila* fila, struct voo* voo);
void mostrar_fila(fila* fila);
int ordenar_voo(voo* voo_inserido);
int* criar_voos();
// void atualizar_lista();
void mostrar_ordem_voos();
int calcular_tempo_necessario(int num_pousos, int num_decolagens);

// int tam_lista();
int checa_alerta_critico(fila* fila);
int checa_pista_disponivel(struct pista* pista);

int gerar_numero_aleatorio(unsigned int min, unsigned int max);
void gerar_vetor_de_numeros_aleatorios(unsigned int* vetor, unsigned int min, unsigned int max);
int existe_no_vetor(unsigned int numero_sorteado, unsigned int* vetor);

int main() {
    struct fila* fila = criar_nova_fila();
    int* vetor_voos = criar_voos();

    printf("Aeroporto Internacional de Brasília\n");
    printf("Hora Inicial: 1\n");
    mostrar_ordem_voos();
    printf("NVoos: %d\n", *(vetor_voos));
    printf("NAproximacoes: %d\n", *(vetor_voos + 1));
    printf("NDecolagens: %d\n", *(vetor_voos + 2));
    printf("-------------------------------\n");
    printf("Listagem de eventos\n");

    colocar_voos_na_fila(fila);

    int tempo = 1;
    struct pista* pista1 = criar_nova_pista(1);
    struct pista* pista2 = criar_nova_pista(2);
    struct pista* pista3 = criar_nova_pista(3);

    struct voo* voo_atual = fila->primeiro;

    while(tempo < 200) {
        if(checa_alerta_critico(fila) > 2)
            printf("\n\nAlerta Crítico!\n\n");

        if(checa_pista_disponivel(pista1))
            colocar_voo_na_pista(pista1, fila, tempo);
        if(checa_pista_disponivel(pista2))
            colocar_voo_na_pista(pista2, fila, tempo);
        if(checa_pista_disponivel(pista3))
            colocar_voo_na_pista(pista3, fila, tempo);

        pista1->tempo_necessario--;
        pista2->tempo_necessario--;
        pista3->tempo_necessario--;

        tempo++;
    }
    
    return 0;
}

struct voo* criar_novo_voo(char* codigo_do_voo, unsigned int nivel_de_combustivel, char modo_do_voo) {
    voo* novo_voo = (struct voo*)malloc(sizeof(struct voo));
    if(novo_voo == NULL) exit(1);

    strcpy(novo_voo->codigo_do_voo, codigo_do_voo);
    novo_voo->modo_do_voo = modo_do_voo;
    novo_voo->nivel_de_combustivel = nivel_de_combustivel;
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

struct pista* criar_nova_pista(int pista) {
    struct pista* nova_pista = (struct pista*)malloc(sizeof(struct pista));
    if(nova_pista == NULL) exit(1);

    nova_pista->num_pista = pista;
    nova_pista->tempo_necessario = 0;
    nova_pista->voo_alocado_a_pista = NULL;

    return nova_pista;
}

void liberar_voo_da_lista(struct voo* voo) {
    struct voo* temp = primeiro_da_lista->de_tras;
    free(primeiro_da_lista);
    primeiro_da_lista = temp;
}

void colocar_voo_na_fila(struct fila* fila, struct voo* voo) {
    if(fila->primeiro == NULL) {
        fila->primeiro = voo;
        fila->ultimo = voo;
        return;
    }
    fila->ultimo->de_tras = voo;
    fila->ultimo = voo;
}

void colocar_voos_na_fila(fila* fila) {
    struct voo* voo_atual = primeiro_da_lista;
    while(voo_atual) {
        colocar_voo_na_fila(fila, voo_atual);

        voo_atual = voo_atual->de_tras;
    }
}

void colocar_voo_na_pista(pista* pista, fila* fila, int tempo) {
    struct voo* voo = tirar_voo_da_fila(fila);
    if((voo->modo_do_voo != 'A') && (voo->modo_do_voo != 'D')) exit(1);

    if(voo->modo_do_voo == 'A' && (checa_alerta_critico(fila) < 3) && pista->num_pista == 3) {
        colocar_voo_na_fila(fila, voo);
        return;
    }

    printf("\nCódigo do voo: %s\n",voo->codigo_do_voo);

    if(voo->modo_do_voo == 'A') {
        pista->tempo_necessario = 4;
        printf("Status: Aeronave Pousou\n");
    }
    if(voo->modo_do_voo == 'D') {
        pista->tempo_necessario = 2;
        printf("Status: Aeronave Decolou\n");
    }

    printf("Horário do início do procedimento: %d\n", tempo);
    printf("Número da pista: %d\n", pista->num_pista);

    liberar_voo_da_lista(voo);
    pista->voo_alocado_a_pista = voo;
}

struct voo* tirar_voo_da_fila(struct fila* fila) {
    if(!(fila->primeiro))
        return NULL;

    struct voo* voo = fila->primeiro;
    fila->primeiro = fila->primeiro->de_tras;
    if(fila->primeiro == NULL)
        printf("Fim da fila\n");

    return voo;
    
}

// int tirar_voo_da_fila_force(struct fila* fila, struct voo* voo) {
//     if(voo == NULL)
//         return 0;

//     struct voo* voo_atual = primeiro_da_lista;

//     while (voo_atual) {
//         if(strcmp(voo_atual->de_tras->codigo_do_voo, voo->codigo_do_voo)) {
//             struct voo* temp = voo_atual->de_tras;
//             voo_atual->de_tras = temp->de_tras;
//             free(temp);
//             return 1;
//         }

//         voo_atual = voo_atual->de_tras;
//     }
    
//     return 0;
    
// }

void mostrar_fila(fila* fila) {
    struct voo* voo_atual = fila->primeiro;
    printf("---\n");
    while(voo_atual) {
        char prioridade[6] = "Baixa";
        int de_tras = 1;
        if(voo_atual->nivel_de_combustivel == 0)
            strcpy(prioridade, "Alta");

        
        printf("%s - %c - %s\n", voo_atual->codigo_do_voo, voo_atual->modo_do_voo, prioridade);

        voo_atual = voo_atual->de_tras;
    }
    printf("---\n");
}

int ordenar_voo(voo* voo_inserido) {
    if(primeiro_da_lista == NULL) {
        primeiro_da_lista = voo_inserido;
        return 1;
    }

    struct voo* voo_atual = primeiro_da_lista;

    if(!(voo_inserido->nivel_de_combustivel == 0)) {
        while(voo_atual) {
            if(!voo_atual->de_tras) {
                voo_atual->de_tras = voo_inserido;
                return 1;
            }
            voo_atual = voo_atual->de_tras;
        }
    } else {
        voo_inserido->de_tras = primeiro_da_lista;
        primeiro_da_lista = voo_inserido;

        return 1;
    }

    return 0;
}

int* criar_voos() {
    int* vetor_retorno = (int*)malloc(sizeof(int) * 3);

    int num_decolagem = gerar_numero_aleatorio(10, 32);
    int num_pouso = gerar_numero_aleatorio(10, 32);
    int num_voos = num_pouso + num_decolagem;

    *(vetor_retorno) = num_voos;
    *(vetor_retorno + 1) = num_pouso;
    *(vetor_retorno + 2) = num_decolagem;

    unsigned int vetor_num_aleatorios[num_voos];

    gerar_vetor_de_numeros_aleatorios(vetor_num_aleatorios, 1, num_voos);

    for(int i = 0; i < num_voos; i++) {
        int nivel_de_combustivel = 12; 
        char modo_de_voo;
        if(i < num_decolagem) modo_de_voo = 'D';
        else modo_de_voo = 'A';

        if(modo_de_voo == 'A') nivel_de_combustivel = gerar_numero_aleatorio(0, 12);

        struct voo* novo_voo = criar_novo_voo(codigo_voos[vetor_num_aleatorios[i]], nivel_de_combustivel, modo_de_voo);
        int result_ordenacao = ordenar_voo(novo_voo);
        if(result_ordenacao == 0) break;
    }

    return vetor_retorno;
}

// void atualizar_lista() {

//     struct voo *temp1, *temp2;

//     for(temp1 = primeiro_da_lista; temp1!=NULL; temp1=temp1->de_tras) {
//         for(temp2 = temp1->de_tras; temp2!=NULL; temp2=temp2->de_tras) {
//             if(temp2->nivel_de_combustivel >= temp1->nivel_de_combustivel) {
//                 char codigo_do_voo[6];
//                 strcpy(codigo_do_voo, temp2->codigo_do_voo);
//                 struct voo* de_tras = temp2->de_tras;
//                 char modo_do_voo = temp2->modo_do_voo;
//                 int nivel_de_combustivel = temp2->nivel_de_combustivel;

//                 strcpy(temp2->codigo_do_voo, temp1->codigo_do_voo);
//                 temp2->de_tras = temp1->de_tras;
//                 temp2->modo_do_voo = temp1->modo_do_voo;
//                 temp2->nivel_de_combustivel = temp1->nivel_de_combustivel;

//                 strcpy(temp1->codigo_do_voo, codigo_do_voo);
//                 temp1->de_tras = de_tras;
//                 temp1->modo_do_voo = modo_do_voo;
//                 temp1->nivel_de_combustivel = nivel_de_combustivel;

//             }
//         }
//     }
// }

void mostrar_ordem_voos() {
    struct voo* voo_atual = primeiro_da_lista;
    printf("---\n");
    while(voo_atual) {
        char prioridade[6] = "Baixa";
        if(voo_atual->nivel_de_combustivel == 0)
            strcpy(prioridade, "Alta");
        
        printf("%s - %c - %s\n", voo_atual->codigo_do_voo, voo_atual->modo_do_voo, prioridade);

        voo_atual = voo_atual->de_tras;
    }
    printf("---\n");
}

int calcular_tempo_necessario(int num_pousos, int num_decolagens) {
    return 0;
}

// int tam_lista() {
//     struct voo* voo_atual = primeiro_da_lista;
//     int num_lista = 0;

//     while(voo_atual) {
//         num_lista++;
//         voo_atual = voo_atual->de_tras;
//     }

//     return num_lista;
// }

int checa_alerta_critico(fila* fila) {
    struct voo* voo_atual = fila->primeiro;
    int num_nivel_critico = 0;

    while(voo_atual) {
        if(voo_atual->nivel_de_combustivel == 0)
            num_nivel_critico++;
        else
            break;
        voo_atual = voo_atual->de_tras;
    }
    return num_nivel_critico;
}

int checa_pista_disponivel(struct pista* pista) {
    if(pista->tempo_necessario < 1) return 1;
    else return 0;
}

// ---------------------------------------- //

int gerar_numero_aleatorio(unsigned int min, unsigned int max) {
    return (rand() % (max + 1 - min)) + min;
}

void gerar_vetor_de_numeros_aleatorios(unsigned int* vetor, unsigned int min, unsigned int max) {
    for(int i = min - 1; i < max; i++) {
        int numero_aleatorio = gerar_numero_aleatorio(20, 64);
        if(!existe_no_vetor(numero_aleatorio, vetor))
            vetor[i] = numero_aleatorio;
        else
            i--;
    }
}

int existe_no_vetor(unsigned int numero_sorteado, unsigned int* vetor) {
    for(int i = 0; i < 64; i++) {
        if(numero_sorteado == vetor[i]) return 1;
    }
    return 0;
}