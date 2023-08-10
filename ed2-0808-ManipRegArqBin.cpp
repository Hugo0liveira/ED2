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
    // avoid the ENTER key to be read in the next fgets
    setbuf(stdin, NULL);
    // clean console
    system("cls");
    printf("Digite o nome: ");
    fgets(p->nome, 30, stdin);
    printf("Digite o sobrenome: ");
    fgets(p->sobrenome, 30, stdin);
    printf("Digite o CPF: ");
    fgets(p->cpf, 11, stdin);
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
        // check if the reallocation was successful
        if (pessoas == NULL) {
            printf("Erro ao realocar o vetor de pessoas!\n");
            system("pause");
            return 0;
        }
        // le o vetor de pessoas do arquivo.
        fread(pessoas, sizeof(Pessoa), qtdPessoas, arq);
        fclose(arq);
    } else {
        // if error when opening the file
        printf("Erro ao abrir o arquivo!\n");
        system("pause");        
    }

    do {
        // clean console
        system("cls");
        imprimirMenu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                // reallocate the vector of people to add a new record  
                pessoas = (Pessoa*) realloc(pessoas, (qtdPessoas + 1) * sizeof(Pessoa));
                // check if the reallocation was successful
                if (pessoas == NULL) {
                    printf("Erro ao realocar o vetor de pessoas!\n");
                    system("pause");
                    return 0;
                } 
                // add a new record in the end of the vector
                inserir(&pessoas[qtdPessoas]);
                qtdPessoas++;
                break;
            case 2:
                setbuf(stdin, NULL);
                // clean console
                system("cls");
                // print the records
                // if there is not records
                if (qtdPessoas == 0) {
                    printf("Zero registros!\n");
                } else {
                    for (int i = 0; i < qtdPessoas; i++) {
                        printf("Nome: %s\n", pessoas[i].nome);
                        printf("Sobrenome: %s\n", pessoas[i].sobrenome);
                        printf("CPF: %s\n", pessoas[i].cpf);
                        printf("Idade: %d\n", pessoas[i].idade);
                        printf("\n\n");
                    }
                }
                // pause the console after print the records and wait for the user to press any key
                system("pause");                                                               
                break;
            case 3:
                // delete all records from the file
                deletar();
                qtdPessoas = 0;
                break;
            case 0:
                // save the records in the DADOS.BIN File and close the file and the program
                arq = fopen("DADOS.BIN", "wb");
                // save the records in the file 
                fwrite(&qtdPessoas, sizeof(int), 1, arq);
                fwrite(pessoas, sizeof(Pessoa), qtdPessoas, arq);
                fclose(arq);
                free(pessoas);
                break;
            default:
                printf("Opção invalida!\n");
                break;
        }
    } while (opcao != 0);

    free(pessoas);

    return 0;
}