#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contato {
    char nome_completo[101];
    char telefone[11];
    char endereco[101];
    char cep[9];
    char data_de_nascimento[11];

    struct contato *anterior;
    struct contato *posterior;
} contato;

// Cabeçalho
struct contato *cabecalho=NULL;

struct contato* criar_novo_contato(char* nome_completo, char* telefone, char* endereco, char* cep, char* data_de_nascimento);
void inserir_contato(contato* contato);
void liberar_contato(contato* contato);

struct contato* filtrar_contato_por_nome(char* nome_completo);

void criar_lista_com_arquivo();
void inserir_novo_registro();
int remover_registro();
int mostrar_registro();
void mostrar_todos_registros();
void sair();

void mostrar_menu();

int main() {
    criar_lista_com_arquivo();
    mostrar_menu();

    return 0;
}

struct contato* criar_novo_contato(char* nome_completo, char* telefone, char* endereco, char* cep, char* data_de_nascimento) {
    contato *novo_contato = (struct contato*)malloc(sizeof(struct contato));
    if(novo_contato == NULL) exit(1);

    strcpy(novo_contato->nome_completo, nome_completo);
    strcpy(novo_contato->telefone, telefone);
    strcpy(novo_contato->endereco, endereco);
    strcpy(novo_contato->cep, cep);
    strcpy(novo_contato->data_de_nascimento, data_de_nascimento);

    novo_contato->anterior = NULL;
    novo_contato->posterior = NULL;

    return novo_contato;
}

void inserir_contato(contato *contato) {
    if(cabecalho == NULL) {
        cabecalho = contato;
        return;
    }

    cabecalho->anterior = contato;
    contato->posterior = cabecalho;
    cabecalho = contato;
}

void liberar_contato(contato* contato) {
    if(cabecalho == NULL || contato == NULL)
        return;
    
    if(contato == cabecalho)
        cabecalho = contato->posterior;

    if(contato->posterior != NULL)
        contato->posterior->anterior = contato->anterior;

    if(contato->anterior != NULL)
        contato->anterior->posterior = contato->posterior;

    free(contato);
}

struct contato* filtrar_contato_por_nome(char* nome_completo) {
    contato* contato_temporario = cabecalho;

    while(contato_temporario) {
        if(!strcmp(contato_temporario->nome_completo, nome_completo)) {
            return contato_temporario;
        }

        contato_temporario = contato_temporario->posterior;
    }
    return NULL;
}

void criar_lista_com_arquivo() {
    FILE *contatos_arquivo;
    contatos_arquivo = fopen("contatos.txt","r");

    if(!contatos_arquivo) 
        exit(1);

    char nome_completo[101];
    char telefone[11];
    char endereco[101];
    char cep[9];
    char data_de_nascimento[11];    

    while (!feof(contatos_arquivo)) {
        fscanf(contatos_arquivo, "%[^\n]s ", nome_completo);
        fscanf(contatos_arquivo, "%s\n", telefone);
        fscanf(contatos_arquivo, "%[^\n]s ", endereco);
        fscanf(contatos_arquivo, "%s\n", cep);
        fscanf(contatos_arquivo, "%s\n", data_de_nascimento);
        fscanf(contatos_arquivo, "$\n");

        contato* novo_contato = criar_novo_contato(nome_completo, telefone, endereco, cep, data_de_nascimento);
        inserir_contato(novo_contato);
    }
    fclose(contatos_arquivo);
}

void inserir_novo_registro() {
    char nome_completo[101];
    char telefone[11];
    char endereco[101];
    char cep[9];
    char data_de_nascimento[11];

    printf("Insira o nome completo: ");
    gets(nome_completo);
    printf("Insira o telefone: ");
    gets(telefone);
    printf("Insira o endereco: ");
    gets(endereco);
    printf("Insira seu CEP: ");
    gets(cep);
    printf("Insira a data de nascimento: ");
    gets(data_de_nascimento);

    contato* contato = criar_novo_contato(nome_completo, telefone, endereco, cep, data_de_nascimento);
    inserir_contato(contato);
    mostrar_menu();
}

int remover_registro() {
    char nome_completo[101];
    printf("Insira o nome completo do contato: ");
    gets(nome_completo);

    contato* contato = filtrar_contato_por_nome(nome_completo);
    if(contato == NULL) {
        printf("Registro não encontrado\n");
        mostrar_menu();
        return 0;
    }
    liberar_contato(contato);

    mostrar_menu();
    return 1;
}

int mostrar_registro() {
    char nome_completo[101];
    printf("Insira o nome completo do contato: ");
    gets(nome_completo);

    contato* contato = filtrar_contato_por_nome(nome_completo);
    if(contato == NULL) {
        printf("Registro não encontrado\n");
        mostrar_menu();
        return 0;
    }
    printf(" --- CONTATO ENCONTRADO --- \n");
    printf("Nome:\t%s\n",contato->nome_completo);
    printf("Telefone:\t%s\n",contato->telefone);
    printf("Endereco:\t%s\n",contato->endereco);
    printf("CEP:\t%s\n",contato->cep);
    printf("Data de Nascimento:\t%s\n",contato->data_de_nascimento);
    printf(" --------------------------- \n");

    mostrar_menu();
    return 1;
}

void mostrar_todos_registros() {
    contato* contato_temporario = cabecalho;
    if(contato_temporario == NULL) {
        printf(" --------------------------- \n");
        printf("Nenhum contato registrado\n");
        printf(" --------------------------- \n");
    }

    while(contato_temporario) {
        if(contato_temporario == NULL) 
            break;

        printf(" --------------------------- \n");
        printf("Nome:\t%s\n",contato_temporario->nome_completo);
        printf("Telefone:\t%s\n",contato_temporario->telefone);
        printf("Endereco:\t%s\n",contato_temporario->endereco);
        printf("CEP:\t%s\n",contato_temporario->cep);
        printf("Data de Nascimento:\t%s\n",contato_temporario->data_de_nascimento);
        printf(" --------------------------- \n");

        contato_temporario = contato_temporario->posterior;
    }
    mostrar_menu();
}

void sair() {
    FILE *contatos_arquivo;
    contatos_arquivo = fopen("contatos.txt","w");

    contato* contato_temporario = cabecalho;
    while(contato_temporario) {
        if(contato_temporario == NULL) 
            break;

        fprintf(contatos_arquivo, "%s\n", contato_temporario->nome_completo);
        fprintf(contatos_arquivo, "%s\n", contato_temporario->telefone);
        fprintf(contatos_arquivo, "%s\n", contato_temporario->endereco);
        fprintf(contatos_arquivo, "%s\n", contato_temporario->cep);
        fprintf(contatos_arquivo, "%s\n", contato_temporario->data_de_nascimento);
        fprintf(contatos_arquivo, "$\n");

        contato_temporario = contato_temporario->posterior;
    }

    fclose(contatos_arquivo);
    exit(1);
}

void mostrar_menu() {
    printf(" --------------------------- \n");
    printf("Digite o número, indicado na frente de cada feature, para executá-la:\n");
    printf("1 - Inserir novo registro\n");
    printf("2 - Remover registro por nome\n");
    printf("3 - Visualizar registro por nome\n");
    printf("4 - Visualizar todos os registros\n");
    printf("5 - Sair do programa\n");
    printf(" --------------------------- \n");
    
    char opcao[2];
    gets(opcao);
    switch(opcao[0]){
        case '1':
            inserir_novo_registro();
            break;
        case '2':
            remover_registro();
            break;
        case '3':
            mostrar_registro();
            break;
        case '4':
            mostrar_todos_registros();
            break;
        case '5':
            sair();
            break;
        default:
            printf("Opção não encontrada!");
            mostrar_menu();
            break;
    }
} 