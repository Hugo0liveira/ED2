#include <stdio.h>
#include <stdlib.h>


// Aluno: Hugo R. Lisboa Oliveira
/*Instruções:

* Apresentar Programa Funcionando no encontro do dia 15/08/2023

* Utilizar o DevC++ (.cpp)

* Estrutura: Nome(30), SobreNome(30), Idade, CPF (11).  

a) O programa deverá ter um menu principal, com as opções:

1)      Inserir 

2)      Listar

3)      Sair. (Salva os registros no Arquivo DADOS.BIN). 

 

b) Detalhes do Programa:

1)      Sempre ao a abrir o programa, deverá ler os registros do arquivo .BIN e carregar os dados do arquivo em VETOR. 

2)      Quando inserir um novo registro, deverá ser inserido no final do VETOR. 

3)      Ao sair, deverá sobrescrever todo o arquivo com os dados da lista.*/

// Estrutura: Nome(30), SobreNome(30), Idade, CPF (11).

void imprimirMenu() {  
    printf(" ____________________________________________\n");
    printf("|                                            |\n");
    printf("|    MENU:                                   |\n");
    printf("|                                            |\n");
    printf("|   1 - Inserir                              |\n");
    printf("|   2 - Listar                               |\n");
    printf("|   0 - Sair                                 |\n"); // sair salvando
    printf("|____________________________________________|\n");
}

/*A funÃ§Ã£o inserirCodigo espera receber trÃªs parÃ¢metros: um ponteiro para
ponteiro de int (que representa a lista), um ponteiro de int (que representa
o nÃºmero de elementos ocupados na lista) e um ponteiro de int (que representa o tamanho atual da lista). */

void inserirCodigo(int **lista, int *ocupados, int *tamanho) {
    int codigo, posicao;
    printf("\nDigite o cÃ³digo a ser inserido (apenas nÃºmeros inteiros): ");
    while (scanf("%d", &codigo) != 1) { // verifica se o valor digitado Ã© um nÃºmero inteiro
        printf("Digite um nÃºmero inteiro vÃ¡lido: ");
        while (getchar() != '\n');
    }
    system("clear");

    printf("Digite a posiÃ§Ã£o (de 0 a %d): ", *ocupados);
    while (scanf("%d", &posicao) != 1) { // verifica se o valor digitado Ã© um nÃºmero inteiro
        printf("Digite um nÃºmero inteiro vÃ¡lido: ");
        while (getchar() != '\n');
    }
    system("clear");
    if (posicao >= 0 && posicao <= *ocupados){
        if (*ocupados == *tamanho) {
            *tamanho = *tamanho + 1; // aumenta o tamanho da lista em 1 posicao (4 bytes)
            int *nova_lista = realloc(*lista, (*tamanho) * sizeof(int)); // realoca a memÃ³ria para acomodar o novo cÃ³digo
            if (nova_lista == NULL){
                printf("Erro ao realocar memÃ³ria.\n"); sleep(3);
                exit(1);
            }
            *lista = nova_lista;
        }
        for (int i = *ocupados; i > posicao; i--){
            (*lista)[i] = (*lista)[i - 1];
        }
        (*lista)[posicao] = codigo;
        (*ocupados)++;
    }else{
        printf("ERRO em inserÃ§Ã£o! PosiÃ§Ã£o invÃ¡lida.\n"); sleep(2); system("clear");
    }
}


void retirarCodigo(int *lista, int *ocupados){
    int posicao;
    if(*ocupados ==0){
        puts("Lista vazia! ImpossÃ­vel retirar cÃ³digo!"); sleep(2); system("clear");
    } else {
        printf("\nDigite a posiÃ§Ã£o (de 0 a %d) do cÃ³digo a ser retirado: ", *ocupados - 1);
        while (scanf("%d", &posicao) != 1){               // verifica se o valor digitado Ã© um nÃºmero inteiro
            printf("Digite um nÃºmero inteiro vÃ¡lido: ");
            while (getchar() != '\n');
        }
        system("clear");

        if (posicao >= 0 && posicao < *ocupados) {
            for (int i = posicao; i < *ocupados - 1; i++) {
                lista[i] = lista[i + 1];
            }
            (*ocupados)--;
            printf("CÃ³digo removido com sucesso.\n"); sleep(2); system("clear");
        } else {
            printf("PosiÃ§Ã£o jÃ¡ estÃ¡ vazia!\n"); sleep(2); system("clear");
        }
    }
}

void consultarQuantidade(int ocupados) {
    printf("\nA quantidade de cÃ³digos cadastrados Ã©: %d \n", ocupados); 
}

void visualizarCodigos(int *lista, int ocupados) {
    printf("\nLista de cÃ³digos numÃ©ricos:\n");
    for (int i = 0; i < ocupados; i++) {
        printf("PosiÃ§Ã£o %d: %d \n", i, lista[i]);
    }
    if(ocupados == 0) { 
        puts("VAZIA!"); sleep(1);
    }
}

void listaSizeOf(int tamanho){
        printf("\nO tamanho em bytes alocado para a lista Ã©: %d\n", tamanho * sizeof(int)); sleep(1);
}

int main() {  
    system("clear");
    int *lista = NULL;  // ponteiro para a lista de cÃ³digos
    int ocupados = 0;   // quantidade de cÃ³digos cadastrados
    int tamanho = 1;
    int opcao;          // opÃ§Ã£o do menu
    int listaBytes=0;

    lista = (int *)malloc((ocupados) * sizeof(int)); // aloca memÃ³ria para a lista de cÃ³digos
    
   if (lista == NULL) {
    printf("Erro na alocaÃ§Ã£o de memÃ³ria!\n\n"); sleep(3);
    exit(1);
} else {
    printf("AlocaÃ§Ã£o de memÃ³ria efetuada com sucesso!\n"); sleep(1); system("clear");
}
  
    do {
        imprimirMenu();
        printf("Digite a opÃ§Ã£o desejada: ");
        while (scanf("%d", &opcao) != 1) { // verifica se o valor digitado Ã© um nÃºmero inteiro
            printf("Digite um nÃºmero inteiro vÃ¡lido: ");
            while (getchar() != '\n');
        }
        system("clear");

        switch (opcao) {
        case 0:
            printf("Encerrando o programa...\n"); sleep(2);
            break;
        case 1:
            inserirCodigo(&lista, &ocupados, &tamanho);
            visualizarCodigos(lista, ocupados);
            consultarQuantidade(ocupados);
            listaSizeOf(tamanho);
            break;
        case 2:
            retirarCodigo(lista, &ocupados);
            visualizarCodigos(lista, ocupados);
            consultarQuantidade(ocupados);
            listaSizeOf(tamanho);
            break;
        case 3:
            visualizarCodigos(lista, ocupados);
            consultarQuantidade(ocupados);
            listaSizeOf(tamanho);
            break;
        default:
            printf("OpÃ§Ã£o invÃ¡lida.\n"); sleep(2); system("clear");
            break;
        }
    } while (opcao != 0);

    free(lista); // libera a memÃ³ria alocada para a lista de cÃ³digos

    return 0;
}