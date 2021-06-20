#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

void clear()
{
    for (int i = 0; i < 10; i++)
        printf("\n\n\n\n\n\n\n\n\n\n");
}

void pause()
{
    setbuf(stdin, NULL);
    printf("Pressione alguma tecla para continuar.\n");
    getchar();
}

void reset_vet(int *vet, int *vet2, int n)
{
    for (int i = 0; i < n; i++)
        vet[i] = vet2[i];
}

void quickSort(int *vet, int ini, int fim)
{
    int center, aux, esq, dir;
    esq = ini;
    dir = fim;
    center = vet[(ini + fim) / 2];
    while (esq <= dir)
    {
        while (vet[esq] < center)
            esq++;
        while (vet[dir] > center)
            dir--;
        if (esq <= dir)
        {
            aux = vet[esq];
            vet[esq] = vet[dir];
            vet[dir] = aux;
            esq++;
            dir--;
        }
    }
    if (ini < dir)
        quickSort(vet, ini, dir);
    if (esq < fim)
        quickSort(vet, esq, fim);
}

void selectionSort(int *vet, int n)
{
    int i, j, minor = 0, aux = 0;
    for (i = 0; i < n - 1; i++)
    {
        minor = i;
        for (j = i + 1; j < n; j++)
        {
            if (vet[j] < vet[minor])
                minor = j;
        }
        if (minor != i)
        {
            aux = vet[i];
            vet[i] = vet[minor];
            vet[minor] = aux;
        }
    }
}

void insertionSort(int *vet, int n)
{
    int i, j, aux;
    for (i = 1; i < n; i++)
    {
        aux = vet[i];
        for (j = i; j > 0 && (aux < vet[j - 1]); j--)
            vet[j] = vet[j - 1];
        vet[j] = aux;
    }
}

void merge(int *vet, int ini, int meio, int fim)
{
    int *vetAux, p1, p2, tam, i, j;
    int fim1 = 0, fim2 = 0;
    tam = fim - ini + 1;
    p1 = ini;
    p2 = meio + 1;
    if ((vetAux = (int *)malloc(tam * sizeof(int))) != NULL)
    {
        for (i = 0; i < tam; i++)
        {
            if (fim1 == 0 && fim2 == 0)
            {
                if (vet[p1] < vet[p2])
                    vetAux[i] = vet[p1++];
                else
                    vetAux[i] = vet[p2++];
                if (p1 > meio)
                    fim1 = 1;
                if (p2 > fim)
                    fim2 = 1;
            }
            else
            {
                if (fim1 == 0)
                    vetAux[i] = vet[p1++];
                else
                    vetAux[i] = vet[p2++];
            }
        }
        for (i = 0, j = ini; i < tam; i++, j++)
            vet[j] = vetAux[i];
    }
    else
    {
        printf("Erro ao alocar memória!\n");
        pause();
        return;
    }
    free(vetAux);
}

void mergeSort(int *vet, int ini, int fim)
{
    int meio;
    if (ini < fim)
    {
        meio = floor((ini + fim) / 2);
        mergeSort(vet, ini, meio);
        mergeSort(vet, meio + 1, fim);
        merge(vet, ini, meio, fim);
    }
}

int checkOrder(int *vet, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (vet[j] < vet[i])
                return 0;
        }
    }
    return 1;
}

int main()
{
    int i, n = 0;
    int *vet, *vet2;
    clock_t timer;
    printf("Insira o tamanho do vetor: ");
    scanf("%d", &n);
    printf("\n");
    if ((vet = (int *)malloc(n * sizeof(int))) == NULL)
    {
        printf("Erro ao alocar memória.\n");
        pause();
        exit(0);
    }
    if ((vet2 = (int *)malloc(n * sizeof(int))) == NULL)
    {
        printf("Erro ao alocar memória.\n");
        pause();
        exit(0);
    }
    srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        vet[i] = rand() % 200;
        vet2[i] = vet[i];
        printf("Valor %d: %d\n", i + 1, vet[i]);
    }
    //SS
    printf("\nSelection Sort:\n");
    reset_vet(vet, vet2, n);
    timer = clock();
    selectionSort(vet, n);
    timer = clock() - timer;
    printf("Vetor ordenado: \n");
    for (i = 0; i < n; i++)
    {
        printf("[%d]", vet[i]);
    }
    printf("\n");
    //vet[n-1]=-1;
    if (!checkOrder(vet, n))
    {
        printf("ERRO! Selection Sort não retornou um vetor ordenado!\n\n");
        pause();
    }
    else
        printf("Tudo certo por aqui, o vetor está ordenado e o código está funcionando perfeitamente! S2\n");
    printf("\nTempo de execução: %f milissegundos\n\n", ((float)timer) / CLOCKS_PER_SEC);
    //IS
    reset_vet(vet, vet2, n);
    printf("Insertion Sort: \n");
    timer = clock();
    insertionSort(vet, n);
    timer = clock() - timer;
    printf("Vetor ordenado: \n");
    for (i = 0; i < n; i++)
    {
        printf("[%d]", vet[i]);
    }
    printf("\n");
    //vet[n-1]=-1;
    if (!checkOrder(vet, n))
    {
        printf("ERRO! Insertion Sort não retornou um vetor ordenado!\n\n");
        pause();
    }
    else
        printf("Tudo certo por aqui, o vetor está ordenado e o código está funcionando perfeitamente! S2\n");
    printf("\nTempo de execução: %f milissegundos\n\n", ((float)timer) / CLOCKS_PER_SEC);
    //QS
    reset_vet(vet, vet2, n);
    printf("Quick Sort: \n");
    timer = clock();
    quickSort(vet, 0, n - 1);
    timer = clock() - timer;
    printf("Vetor ordenado: \n");
    for (i = 0; i < n; i++)
    {
        printf("[%d]", vet[i]);
    }
    printf("\n");
    //vet[n-1]=-1;
    if (!checkOrder(vet, n))
    {
        printf("ERRO! Quick Sort não retornou um vetor ordenado!\n\n");
        pause();
    }
    else
        printf("Tudo certo por aqui, o vetor está ordenado e o código está funcionando perfeitamente! S2\n");
    printf("\nTempo de execução: %f milissegundos\n\n", ((float)timer / CLOCKS_PER_SEC));
    //MS
    reset_vet(vet, vet2, n);
    printf("Merge Sort: \n");
    timer = clock();
    mergeSort(vet, 0, n - 1);
    timer = clock() - timer;
    printf("Vetor ordenado: \n");
    for (i = 0; i < n; i++)
    {
        printf("[%d]", vet[i]);
    }
    printf("\n");
    //vet[n-1]=-1;
    if (!checkOrder(vet, n))
    {
        printf("ERRO! Merge Sort não retornou um vetor ordenado!\n\n");
        pause();
    }
    else
        printf("Tudo certo por aqui, o vetor está ordenado e o código está funcionando perfeitamente! S2\n");
    printf("\nTempo de execução: %f milissegundos\n\n", ((float)timer) / CLOCKS_PER_SEC);
    free(vet);
    free(vet2);
    return 0;
}