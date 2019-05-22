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
void ordenar_lista();

void criar_lista_com_arquivo();
void inserir_novo_registro();
int remover_registro();
int mostrar_registro();
void mostrar_todos_registros();
void sair();

void mostrar_menu();

int validar_nome_completo(char* nome_completo);
int validar_telefone(char* telefone);
int validar_endereco(char* endereco);
int validar_cep(char* cep);
int validar_data_de_nascimento(char* data_de_nascimento);

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
    printf("Contato não encontrado\n");
    printf("Lembre-se que nomes e sobrenomes comecao com letra maiúscula");
    return NULL;
}

void ordenar_lista() {
    contato *i, *j, *temp;

    for(i=cabecalho; i->posterior != NULL; i=i->posterior) {
        for(j=i->posterior; j != NULL; j=j->posterior) {
            if(strcmp(i->nome_completo, j->nome_completo) > 0) {
                strcpy(temp->nome_completo, i->nome_completo);
                strcpy(temp->telefone, i->telefone);
                strcpy(temp->endereco, i->endereco);
                strcpy(temp->cep, i->cep);
                strcpy(temp->data_de_nascimento, i->data_de_nascimento);

                strcpy(i->nome_completo, j->nome_completo);
                strcpy(i->telefone, j->nome_completo);
                strcpy(i->endereco, j->endereco);
                strcpy(i->cep, j->cep);
                strcpy(i->data_de_nascimento, j->data_de_nascimento);

                strcpy(j->nome_completo, temp->nome_completo);
                strcpy(j->telefone, temp->telefone);
                strcpy(j->endereco, temp->endereco);
                strcpy(j->cep, temp->cep);
                strcpy(j->data_de_nascimento, temp->data_de_nascimento);
            }
        }
    }
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
    while(!validar_nome_completo(nome_completo)) {
        gets(nome_completo);
    }

    printf("Insira o telefone: ");
    gets(telefone);
    while(!validar_telefone(telefone)) {
        printf("O formato para o telefone é: 00000-0000\n");
        gets(telefone);
    }

    printf("Insira o endereco: ");
    gets(endereco);
    while(!validar_endereco(endereco)) {
        gets(endereco);
    }

    printf("Insira seu CEP: ");
    gets(cep);
    while(!validar_cep(cep)) {
        gets(cep);
    }

    printf("Insira a data de nascimento: ");
    gets(data_de_nascimento);
    while(!validar_data_de_nascimento(data_de_nascimento)) {
        gets(data_de_nascimento);
    }

    contato* contato = criar_novo_contato(nome_completo, telefone, endereco, cep, data_de_nascimento);
    inserir_contato(contato);
    mostrar_menu();
}

int remover_registro() {
    char nome_completo[101];
    printf("Insira o nome completo do contato: ");
    while(!validar_nome_completo(nome_completo)) {
        gets(nome_completo);
    }

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
    while(!validar_nome_completo(nome_completo)) {
        gets(nome_completo);
    }

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
    ordenar_lista();
    
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

int validar_nome_completo(char* nome_completo) {
    int tamanho = strlen(nome_completo);

    for(int i = 0; i < tamanho; i++) {
        if(nome_completo[i] == ' ') return 1;
    }

    printf("Seu nome deve ser completo\n");
    return 0;
}

int validar_telefone(char* telefone) {
    int digitos = 0;
    int traco = 0;
    
    if(strlen(telefone) != 10) {
        printf("Seu telefone deve ter 10 dígitos contando o traco\n");
        return 0;
    }

    for(int i = 0; i < 10; i++) {
        if(i < 5 || i > 5)
            if(telefone[i] == '-') {
                return 0;
            } else
                digitos++;
        if(i == 5)
            if(telefone[i] != '-') {
                return 0;
            } else
                traco++;
    }
    if(digitos == 9 && traco == 1)
        return 1;
    else 
        return 0;
}

int validar_endereco(char* endereco) {
    if(strlen(endereco) < 5) {
        printf("Seu endereço não possui o numero de caracteres minimo\n");
        return 0;
    } else if(strlen(endereco) > 100) {
        printf("Seu endereco excede o número máximo de caracteres\n");
        return 0;
    } else
        return 1;
    
}

int validar_cep(char* cep) {
    if(strlen(cep) != 8) {
        printf("CEP possui 8 digitos\n");
        return 0;
    }
    return 1;
}

int validar_data_de_nascimento(char* data_de_nascimento) {
    int tamanho = strlen(data_de_nascimento);

    if(strlen(data_de_nascimento) != 10) {
        printf("Sua data de nascimento foi inserida errada, digite novamente\n");
        return 0;
    }
    if(data_de_nascimento[2] != '/' || data_de_nascimento[5] != '/') {
        printf("O formato aceito para data de nascimento é: DD/MM/AAAA\n");
        printf("Não se esqueça das barras\n");
        return 0;
    }

    int dia[2];
    dia[0] = (int)data_de_nascimento[0] - '0';
    dia[1] = (int)data_de_nascimento[1] - '0';

    if(dia[0] > 3 || (dia[0] == 3 && dia[1] > 1)) {
        printf("Dia inválido\n");
        return 0;
    }

    int mes[2];
    mes[0] = (int)data_de_nascimento[3] - '0';
    mes[1] = (int)data_de_nascimento[4] - '0';

    if(mes[0] > 1 || (mes[0] == 1 && mes[1] > 2)) {
        printf("Mês inválido\n");
        return 0;
    }

    int ano[4];
    ano[0] = (int)data_de_nascimento[6] - '0';
    ano[1] = (int)data_de_nascimento[7] - '0';
    ano[2] = (int)data_de_nascimento[8] - '0';
    ano[3] = (int)data_de_nascimento[9] - '0';

    if(ano[0] > 2 || (ano[0] == 2 && ano[1] > 0) || (ano[0] == 2) && ano[2] > 1) {
        printf("Você é um viajante do tempo?\n");
        printf("Ainda ninguém nasceu nessa data\n");
        return 0;
    }

    return 1;
}