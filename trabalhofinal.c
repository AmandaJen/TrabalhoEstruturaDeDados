#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define SAIR 11

// UTILIDADES
int randomizarVetor(int vetor[], unsigned int tam_vetor) {
    for(int i = 0; i < tam_vetor; i++) {
        do {
            vetor[i] = rand() % 1000;
        } while (vetor[i] > 1000 && vetor[i] < 0);
    }
    return 0;
}
void printVetor(int vetor[], unsigned int tam_vetor) {
    for (unsigned short i = 0; i < tam_vetor; i++) printf("%i ", vetor[i]);
    putchar('\n');
}
int trocarValores(int* a, int*b) {
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
    return 0;
}
// ========================================================================================

// BUBBLE SORT
int bubbleSort(int vetor[], unsigned int tam_vetor) {
    for (int i = tam_vetor-1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (vetor[i] < vetor[j]) {
                trocarValores(&vetor[i], &vetor[j]);
            }
        }
    }
}
// ========================================================================================

// SELECTION SORT
int selectionSort(int vetor[], unsigned int tam_vetor) {
    int pos_menor;

    for (int i = 0; i < tam_vetor; i++) {
        pos_menor = i;

        for (int j = i+1; j < tam_vetor; j++) {
            if (vetor[j] < vetor[pos_menor]) pos_menor = j;
        }

        trocarValores(&vetor[pos_menor], &vetor[i]);

    }
}
// ========================================================================================

// INSERTION SORT
int insertionSort(int vetor[], unsigned int tam_vetor) {

    for (int i = 0; i < tam_vetor - 1; i++) {
        if (vetor[i] > vetor[i+1]) {
            for (int j = i+1; j != 0; j--) {
                if (vetor[j-1] <= vetor[j]) break;

                trocarValores(&vetor[j-1], &vetor[j]);
            }
        }
    }
}
// ========================================================================================

// QUICKSORT
int novoIndicePivo(int esquerda, int direita) {
    return (rand() % (direita - esquerda + 1)) + esquerda;
}
void organizarVetorPivo(int vetor[], int esquerda, int direita, int* indice_pivo) {
    trocarValores(&vetor[*indice_pivo], &vetor[direita]);
    
    int i, j;

    for (i = esquerda - 1, j = esquerda; j < direita; ++j) {
        if (vetor[j] < vetor[direita]) {
            ++i;
            trocarValores(&vetor[i], &vetor[j]);
        }
    }

    *indice_pivo = i+1;

    trocarValores(&vetor[*indice_pivo], &vetor[direita]);
}
void quickSort(int vetor[], int esquerda, int direita) {
    if (esquerda >= direita) return;
    
    int indice_pivo = novoIndicePivo(esquerda, direita);

    organizarVetorPivo(vetor, esquerda, direita, &indice_pivo);


    quickSort(vetor, esquerda, indice_pivo-1);
    quickSort(vetor, indice_pivo+1, direita);
}
// ========================================================================================

// HEAP SORT
void sift(int heap[], int i) {
    int j = i, indice_pai = j/2;

    do {
        if (heap[j] >= heap[indice_pai]) break;

        trocarValores(&heap[j], &heap[indice_pai]);
        j = indice_pai;
        indice_pai = j/2;

    } while (j > 0);
}
void converterParaHeap(int vetor[], unsigned int tam_vetor) {
    int heap[tam_vetor];

    for (int i = 0; i < tam_vetor; i++) {
        heap[i] = vetor[i];
        sift(heap, i);
    }

    for (int i = 0; i < tam_vetor; i++) {
        vetor[i] = heap[i];
    }
}
void inserirPrimeiroNoFinalHeap(int heap[], unsigned int tam_heap) {
    for (int i = 0; i < tam_heap-1; i++) trocarValores(&heap[i], &heap[i+1]);
}
int heapSort(int vetor[], unsigned int tam_vetor) {

    converterParaHeap(vetor, tam_vetor);

    for (unsigned short i = 0; i < tam_vetor; i++) {
        inserirPrimeiroNoFinalHeap(vetor, tam_vetor);
        converterParaHeap(vetor, tam_vetor-1-i);
    }
}

// MERGE SORT
void merge(int vetor_original[], int esquerda, int meio, int direita) {

    unsigned int tam_esquerda = meio-esquerda+1, tam_direita = direita-meio, tam_original = direita-esquerda+1;
    int vetor_esquerda[tam_esquerda], vetor_direita[tam_direita];
    unsigned int i;

    for (i = 0; i < tam_esquerda; ++i) {
        vetor_esquerda[i] = vetor_original[esquerda + i];
    }

    for (i = 0; i < tam_direita; ++i) {
        vetor_direita[i] = vetor_original[meio + i + 1];
    }

    unsigned int indice_esquerda = 0, indice_direita = 0, indice_original = esquerda;

    while (indice_esquerda < tam_esquerda && indice_direita < tam_direita) {
        if (vetor_esquerda[indice_esquerda] <= vetor_direita[indice_direita]) {
            vetor_original[indice_original] = vetor_esquerda[indice_esquerda];
            ++indice_esquerda;
        }
        else {
            vetor_original[indice_original] = vetor_direita[indice_direita];
            ++indice_direita;
        }
        ++indice_original;
    }
    
    while (indice_esquerda < tam_esquerda) {
        vetor_original[indice_original] = vetor_esquerda[indice_esquerda];
        ++indice_esquerda;
        ++indice_original;
    }

    while (indice_direita < tam_direita) {
        vetor_original[indice_original] = vetor_direita[indice_direita];
        ++indice_direita;
        ++indice_original;
    }
}
void mergeSort(int vetor[], unsigned int esquerda, unsigned int direita) {

    if (esquerda >= direita) return;

    unsigned int meio = (direita+esquerda)/2;

    mergeSort(vetor, esquerda, meio);
    mergeSort(vetor, meio+1, direita);

    merge(vetor, esquerda, meio, direita);
}
// ========================================================================================

void ArqPString(char letra, char Exemplo, int cont, char arquivo[cont]){
    for (letra=getc(Exemplo); letra!=EOF; letra=getc(Exemplo)){ //Transformar o arquivo em uma string
        arquivo[cont]=letra;
        cont++;
    }
}

void StringPVetor (char arquivo[24337], int lista[5000]){  //Transformar a string em um Vetor
    char ajuda[5];
    int contA, contL=0, aju=0;
    for (contA=0;contA<24337;contA++){
        ajuda[aju]=arquivo[contA];
        if (strcmp(ajuda[aju],",")==0){
            ajuda[aju]='\0';
            lista[contL]=atoi(ajuda[aju]);
            contL++;
            aju=-1;
        }
        aju++;
    }
    
}



int main(){
    //Arquivs para contagem do bubble sort
    FILE *BBSort;
    
    //Arquivo para contagem do selection sort
    FILE *SLSort;
    
    //Arquivo para contagem do insertion sort
    FILE *INSort;

    //Arquivo para contagem do quick sort
    FILE *QCKSort;

    //Arquivo para contagem do heap sort
    FILE *HPSort;
    
    //Arquivo para contagem do merge sort
    FILE *MGSort;
    
    //Arquivo de numero
    FILE *Exemplo;

    Exemplo = fopen ("exemplo.txt", "r");
    if (Exemplo==NULL){
        printf ("Erro ao abrir o arquivo");
        return 1;
    }

    char arquivo[24337], letra;
    float execucao = 0;                // para armazenar o tempo de execução do código
    int lista[5000], cont=0;
    int mil;

    ArqPString(letra, Exemplo, cont, arquivo[24337]);
    fclose (Exemplo);

    StringPVetor(arquivo[sizeof(arquivo)], lista[sizeof(lista)]);

    for(mil=0;mil<1000;mil++){
        clock_t comeco = clock();
        bubbleSort(lista,500);
        clock_t fim = clock ();
        execucao += (double)(fim-comeco)/CLOCKS_PER_SEC;
        StringPVetor(arquivo[sizeof(arquivo)], lista[sizeof(lista)]);

    }
        BBSort = fopen ("BubbleSort.txt", "w");
        fprintf (BBSort, "A media do tempo utilizado em 500 numeros foi %f \n", execucao);



}