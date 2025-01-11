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
    int aux;

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

//Remover caracteres
void removercarac(int tam, char lista[tam]){
    int contagem;
    char antigo = ",";
    char novo = "\n";
    for (contagem=0;contagem<=tam;contagem++){
        if (lista[contagem]==antigo){
            lista[contagem]==novo;
        }
    }
}

int main(){
    //Arquivos para contagem do bubble sort
    FILE *BBSort500, *BBSort1000, *BBSort1500, *BBSort2000, *BBSort2500, *BBSort3000, *BBSort3500, *BBSort4000, *BBSort4500, *BBSort5000;
    //Arquivos para contagem do selection sort
    FILE *SLSort500, *SLSort1000, *SLSort1500, *SLSort2000, *SLSort2500, *SLSort3000, *SLSort3500, *SLSort4000, *SLSort4500, *SLSort5000;
    //Arquivos para contagem do insertion sort
    FILE *INSort500, *INSort1000, *INSort1500, *INSort2000, *INSort2500, *INSort3000, *INSort3500, *INSort4000, *INSort4500, *INSort5000;
    //Arquivos para contagem do quick sort
    FILE *QCKSort500, *QCKSort1000, *QCKSort1500, *QCKSort2000, *QCKSort2500, *QCKSort3000, *QCKSort3500, *QCKSort4000, *QCKSort4500, *QCKSort5000;
    //Arquivos para contagem do heap sort
    FILE *HPSort500, *HPSort1000, *HPSort1500, *HPSort2000, *HPSort2500, *HPSort3000, *HPSort3500, *HPSort4000, *HPSort4500, *HPSort5000;
    //Arquivos para contagem do merge sort
    FILE *MGSort500, *MGSort1000, *MGSort1500, *MGSort2000, *MGSort2500, *MGSort3000, *MGSort3500, *MGSort4000, *MGSort4500, *MGSort5000;
    //Arquivo de numero
    FILE *Exemplo;

    Exemplo = fopen ("exemplo.txt", "r");

    char arquivo[24337];
    double execucao = 0.0;                // para armazenar o tempo de execução do código
    int lista[5000];
    
    //transformar a lista de caracteres em numeros
    removercarac (sizeof(arquivo),arquivo);
    
    //lista=arquivo;

    // 

    //clock_t begin = clock();
    //clock_t end = clock();
 
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    // time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    //fprintf("The elapsed time is %f seconds", time_spent);


}