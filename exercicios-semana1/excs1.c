#include <stdio.h>
#include <stdlib.h>

int nomes = 0;

int menu()
{
    int x;
    printf("1) Adicionar nome\n");
    printf("2) Remover nome\n");
    printf("3) Listar\n");
    printf("4) Sair\n");
    printf("Digite a opção desejada: ");
    scanf("%d", &x);
    return x;
}

void adicionar(char *buffer, int *total_mem)
{
    int mem_left = 1;
    char c = 0;
    int length = 0;
    char *tmp;
    if ((buffer = (char *)malloc(mem_left)) == NULL)
    {
        printf("Erro ao alocar memória\n");
        system("pause");
        exit(-1);
    }
    while ((c = getchar()) != '\n')
    {
        if (mem_left == 0)
        {
            if ((tmp = (char *)realloc(buffer, (*total_mem) + 1)) == NULL)
            {
                printf("Erro ao realocar memória\n");
                system("pause");
                exit(1);
            }
            buffer = tmp;
            ++(*total_mem);
            mem_left = 1;
        }
        *(buffer + (length++)) = c;
        --mem_left;
    }
    *(buffer + length) = '\0';
    printf("%s\n", buffer);
    return;
}

int main()
{
    system("cls");
    int choice;
    char *buffer, total_mem = 2;
    for (;;)
    {
        choice = menu();
        switch (choice)
        {
        case 1:
            adicionar(buffer, &total_mem);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            return 0;
            break;
        }
    }
    return 0;
}