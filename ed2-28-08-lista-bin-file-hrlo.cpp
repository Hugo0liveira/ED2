#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pessoa {  
    char nome[999];
    int idade;
};

void inserir(Pessoa *p) {  
    // limoar buffer do teclado
    setbuf(stdin, NULL);
    system("cls");
    printf("Nome completo: ");
    fgets(p->nome, 999, stdin);
    printf("Idade: ");
    scanf("%d", &p->idade);
}

void deletar() {  
    FILE *arq;
    // limpar arquivo
    arq = fopen("death-note.bin", "wb");
    fclose(arq);
}

void imprimirMenu() {  
    system("cls");
    printf(" ____________________________________________\n");
    printf("|                                            |\n");
    printf("|    DEATH NOTE:                             |\n");
    printf("|                                            |\n");
    printf("|   1 - Registrar pessoa                     |\n");    
    printf("|   2 - Ver lista                            |\n");
    printf("|   3 - Esquecer todos                       |\n");
    printf("|   0 - Sair                                 |\n"); // sair salvando
    printf("|____________________________________________|\n");
}

int main() {  
    // vetor de pessoas. 
    Pessoa *pessoas = (Pessoa*) malloc(sizeof(Pessoa));
    int opcao = 0; 
    int loop = 1;
    int qtdPessoas = 0;     
    // arquivo binario 
    FILE *arq;
    // leitura do arquivo binario 
    arq = fopen("death-note.bin", "rb");
    // se o arquivo existir 
    if (arq != NULL) {
        // le a quantidade de pessoas no arquivo. 
        fread(&qtdPessoas, sizeof(int), 1, arq);
        // realoca o vetor de pessoas.  
        pessoas = (Pessoa*) realloc(pessoas, qtdPessoas * sizeof(Pessoa));
        if (pessoas == NULL) {
            printf("Erro ao realocar pessoas!\n");
            system("pause");
        }
        // le o vetor de pessoas do arquivo.
        fread(pessoas, sizeof(Pessoa), qtdPessoas, arq);
        fclose(arq);
    } else {
        printf("Erro ao abrir o arquivo!\n");
        system("pause");        
    }

    do {
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
                        printf("-> %s, %d\n", pessoas[i].nome, pessoas[i].idade);
                        printf("__________\n");
                    }
                }
                system("pause");                                                               
                break;
            case 3:
                deletar();
                qtdPessoas = 0;
                break;
            case 0:
                arq = fopen("death-note.bin", "wb");
                // save the records in the file 
                fwrite(&qtdPessoas, sizeof(int), 1, arq);
                fwrite(pessoas, sizeof(Pessoa), qtdPessoas, arq);
                fclose(arq);
                free(pessoas);
                loop = 0;
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (loop != 0);

    free(pessoas);

    return 0;
}