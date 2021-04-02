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
    char *tmp;
    setbuf(stdin, NULL);
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
            ++mem_left;
        }
        *(buffer + (*total_mem)) = c;
        --mem_left;
    }
    if ((tmp = (char *)realloc(buffer, (*total_mem) + 1)) == NULL)
    {
        printf("Erro ao realocar memória\n");
        system("pause");
        exit(1);
    }
    buffer = tmp;
    ++(*total_mem);
    *(buffer + (*total_mem)) = '\0';
    nomes++;
    return;
}

void listar(char *buffer)
{
    system("cls");
    int i = 0, n_name = 1, name_list = nomes;
    while (name_list > 0)
    {
        printf("%d) ", n_name);
        while (*(buffer + i) != '\0')
        {
            printf("%c", *(buffer + i));
            i++;
        }
        printf("\n");
        i++;
        --name_list;
        ++n_name;
    }
    system("pause");
}

int main()
{
    int choice, total_mem = 1;
    char *buffer;
    if ((buffer = (char *)malloc(total_mem)) == NULL)
    {
        printf("Erro ao alocar memória\n");
        system("pause");
        exit(-1);
    }
    for (;;)
    {
        system("cls");
        choice = menu();
        switch (choice)
        {
        case 1:
            adicionar(buffer, &total_mem);
            break;
        case 2:
            break;
        case 3:
            listar(buffer);
            break;
        case 4:
            return 0;
            break;
        }
    }
    return 0;
}