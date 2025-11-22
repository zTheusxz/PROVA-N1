#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    char cpf[12];
    int idade;
    char email[50];
} Pessoa;

Pessoa pessoas[200];
int qtd = 0;

int CPFvalido(char cpf[]) {
    int tamanho = strlen(cpf);
    if (tamanho != 11) return 0;
    for (int i = 0; i < 11; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') return 0;
    }
    return 1;
}

int CPFexiste(char cpf[]) {
    for (int i = 0; i < qtd; i++) {
        if (strcmp(pessoas[i].cpf, cpf) == 0) return 1;
    }
    return 0;
}

void salvarArquivo() {
    FILE *f = fopen("pessoas.dat", "wb");
    if (!f) return;
    fwrite(pessoas, sizeof(Pessoa), qtd, f);
    fclose(f);
}

void carregarArquivo() {
    FILE *f = fopen("pessoas.dat", "rb");
    if (!f) return;
    qtd = 0;
    while (fread(&pessoas[qtd], sizeof(Pessoa), 1, f) == 1) {
        qtd++;
        if (qtd >= 200) break;
    }
    fclose(f);
}

void Cadastrar() {
    Pessoa p;
    char cpf_temp[50];

    printf("\nDigite o nome: ");
    scanf("%s", p.nome);

    do {
        printf("Digite o CPF (11 digitos): ");
        scanf("%s", cpf_temp);

        if (!CPFvalido(cpf_temp)) {
            printf("CPF invalido\n");
            continue;
        }

        if (CPFexiste(cpf_temp)) {
            printf("CPF ja cadastrado\n");
            continue;
        }

        strcpy(p.cpf, cpf_temp);
        break;

    } while (1);

    printf("Digite a idade: ");
    scanf("%d", &p.idade);

    printf("Digite o email: ");
    scanf("%s", p.email);

    if (qtd < 200) {
        pessoas[qtd] = p;
        qtd++;
        salvarArquivo();
        printf("\nCadastro concluido\n");
    } else {
        printf("\nCapacidade maxima atingida\n");
    }
}

void Listar() {
    if (qtd == 0) {
        printf("\nNenhuma pessoa cadastrada\n");
        return;
    }

    printf("\n===== LISTA =====\n");

    for (int i = 0; i < qtd; i++) {
        printf("\nPessoa %d\n", i + 1);
        printf("Nome: %s\n", pessoas[i].nome);
        printf("CPF: %s\n", pessoas[i].cpf);
        printf("Idade: %d\n", pessoas[i].idade);
        printf("Email: %s\n", pessoas[i].email);
    }

    printf("\n");
}

int BuscarIndice(char cpf[]) {
    for (int i = 0; i < qtd; i++) {
        if (strcmp(pessoas[i].cpf, cpf) == 0) return i;
    }
    return -1;
}

void Buscar() {
    char cpf[12];
    int i;

    printf("\n============================================\n");
    printf("Digite o CPF para buscar: ");
    scanf("%s", cpf);

    i = BuscarIndice(cpf);

    printf("--------------------------------------------\n");

    if (i == -1) {
        printf("CPF nao encontrado\n");
    } else {
        printf("Nome:  %s\n", pessoas[i].nome);
        printf("CPF:   %s\n", pessoas[i].cpf);
        printf("Idade: %d\n", pessoas[i].idade);
        printf("Email: %s\n", pessoas[i].email);
    }

    printf("============================================\n\n");
}

void Atualizar() {
    char cpf[12];
    int i;

    printf("\nDigite o CPF para atualizar: ");
    scanf("%s", cpf);

    i = BuscarIndice(cpf);

    if (i == -1) {
        printf("CPF nao encontrado\n");
        return;
    }

    printf("Novo nome: ");
    scanf("%s", pessoas[i].nome);

    printf("Nova idade: ");
    scanf("%d", &pessoas[i].idade);

    printf("Novo email: ");
    scanf("%s", pessoas[i].email);

    salvarArquivo();
    printf("\nAtualizado com sucesso\n");
}

void Remover() {
    char cpf[12];
    int i;

    printf("\nDigite o CPF para remover: ");
    scanf("%s", cpf);

    i = BuscarIndice(cpf);

    if (i == -1) {
        printf("CPF nao encontrado\n");
        return;
    }

    for (int j = i; j < qtd - 1; j++) {
        pessoas[j] = pessoas[j + 1];
    }

    qtd--;
    salvarArquivo();

    printf("Removido com sucesso\n");
}

int main() {
    int opcao;
    carregarArquivo();

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Buscar\n");
        printf("4 - Atualizar\n");
        printf("5 - Remover\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: Cadastrar(); break;
            case 2: Listar(); break;
            case 3: Buscar(); break;
            case 4: Atualizar(); break;
            case 5: Remover(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida\n");
        }

    } while (opcao != 0);

    return 0;
}
