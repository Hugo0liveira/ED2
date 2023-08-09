#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Aluno: Hugo R. Lisboa Oliveira
/* Structure: Name(30), LastName(30), Age, CPF (11).

a) The program must have a main menu, with the options:

1) Insert
2) List
3) Delete
3) Leave. (Save the records in the DADOS.BIN File).
b) Program Details:
1) Whenever you open the program, you must read the .BIN file records and load the data from the file in VECTOR.
2) When inserting a new record, it must be inserted at the end of the VECTOR.
3) When exiting, you must overwrite the entire file with the list data.*/

struct Pessoa {  
    char nome[30];
    char sobrenome[30];    
    char cpf[11];
    int idade;
};

// pointer to struct Pessoa 
void inserir(Pessoa *p) {  
    // clean console
    system("cls");
    printf("Digite o nome: ");
    scanf("%s", p->nome);
    printf("Digite o sobrenome: ");
    scanf("%s", p->sobrenome);
    printf("Digite o CPF: ");
    scanf("%s", p->cpf);
    printf("Digite a idade: ");
    scanf("%d", &p->idade);
}

// delete all records from the file
void deletar() {  
    FILE *arq;
    // open the file in write mode and overwrite it with nothing 
    arq = fopen("DADOS.BIN", "wb");
    fclose(arq);
}

void imprimirMenu() {  
    system("cls");
    printf(" ____________________________________________\n");
    printf("|                                            |\n");
    printf("|    MENU:                                   |\n");
    printf("|                                            |\n");
    printf("|   1 - Inserir                              |\n");    
    printf("|   2 - Listar                               |\n");
    printf("|   3 - Deletar                              |\n");
    printf("|   0 - Sair                                 |\n"); // sair salvando
    printf("|____________________________________________|\n");
}

int main() {  
    // vetor de pessoas. 
    Pessoa *pessoas = (Pessoa*) malloc(sizeof(Pessoa));
    int opcao = 0;
    // quantidade de pessoas no vetor de pessoas 
    int qtdPessoas = 0;     
    // arquivo binario 
    FILE *arq;
    // leitura do arquivo binario 
    arq = fopen("DADOS.BIN", "rb");
    // se o arquivo existir 
    if (arq != NULL) {
        // le a quantidade de pessoas no arquivo. 
        fread(&qtdPessoas, sizeof(int), 1, arq);
        // realoca o vetor de pessoas.  
        pessoas = (Pessoa*) realloc(pessoas, qtdPessoas * sizeof(Pessoa));
        // le o vetor de pessoas do arquivo.
        fread(pessoas, sizeof(Pessoa), qtdPessoas, arq);
        fclose(arq);
    }

    do {
        imprimirMenu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                // realoca o vetor de pessoas. 
                pessoas = (Pessoa*) realloc(pessoas, (qtdPessoas + 1) * sizeof(Pessoa));
                // insere a pessoa no vetor de pessoas.
                inserir(&pessoas);
                qtdPessoas++;
                break;
            case 2:
                for (int i = 0; i < qtdPessoas; i++) {
                    printf("Nome: %s\n", pessoas[i].nome);
                    printf("Sobrenome: %s\n", pessoas[i].sobrenome);
                    printf("CPF: %s\n", pessoas[i].cpf);
                    printf("Idade: %d\n", pessoas[i].idade);
                    printf("\n\n");
                }
                break;
            case 3:
                deletar();
                qtdPessoas = 0;
                pessoas = (Pessoa*) realloc(pessoas, qtdPessoas * sizeof(Pessoa));
                break;
            case 0:
                arq = fopen("DADOS.BIN", "wb");
                fwrite(&qtdPessoas, sizeof(int), 1, arq);
                fwrite(pessoas, sizeof(Pessoa), qtdPessoas, arq);
                fclose(arq);
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    free(pessoas);

    return 0;
}