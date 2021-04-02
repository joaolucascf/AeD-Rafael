#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int names = 0;

int menu();
void listar(char *main_string);
void adicionar(char *main_string, int *main_string_size);
void remover(char *main_string, int *main_string_size);

int main()
{
    char *main_string;
    int choice = 0, main_string_size = 1;
    if ((main_string = (char *)malloc(1)) == NULL)
    {
        system("cls");
        printf("Erro ao alocar memória.\n");
        system("pause");
        exit(1);
    }
    *main_string = '\0';
    for (;;)
    {
        choice = menu();
        switch (choice)
        {
        case 1:
            //add function
            adicionar(main_string, &main_string_size);
            break;
        case 2:
            remover(main_string, &main_string_size);
            break;
        case 3:
            listar(main_string);
            system("pause");
            //list function
            break;
        case 4:
            free(main_string);
            return 0;
            break;
        default:
            system("cls");
            printf("Opção inválida.\n");
            system("pause");
            break;
        }
    }
}

void remover(char *main_string, int *main_string_size)
{
    int remove_id = 0, i = 0, breaker = 0, j = 0, remove_size = 0;
    listar(main_string);
    printf("\nInsira o índice do nome a ser removido: ");
    scanf("%d", &remove_id);
    if (remove_id > names)
    {
        system("cls");
        printf("Índice inválido.\n");
        system("pause");
        return;
    }
    while (main_string[i] != '\0')
    {
        if (breaker == remove_id - 1)
            break;
        if (main_string[i++] == '!')
            breaker++;
    }
    j = i;
    while (main_string[j] != '\0' && main_string[j] != '!')
    {
        j++;
    }
    j++; // incrementa mais uma vez pra tirar o '!'
    remove_size = j - i;
    *main_string_size -= remove_size;
    strcpy(&main_string[i], &main_string[j]);
    if ((main_string = (char *)realloc(main_string, *main_string_size)) == NULL)
    {
        system("cls");
        printf("Erro ao realocar memória.\n");
        system("pause");
        exit(1);
    }
    names--;
    if (names == 0)
    {
        *main_string = '\0';
    }
    system("cls");
    printf("Nome removido com sucesso.\n");
    system("pause");
    return;
}

void adicionar(char *main_string, int *main_string_size)
{
    char new_name[50];
    int new_name_size;
    setbuf(stdin, NULL);
    system("cls");
    printf("Insira o nome a ser adicionado: ");
    scanf("%[^\n]", new_name);
    strcat(new_name, "!");
    new_name_size = strlen(new_name);
    *main_string_size += new_name_size;
    if ((main_string = (char *)realloc(main_string, *main_string_size)) == NULL)
    {
        system("cls");
        printf("Erro ao realocar memória.\n");
        system("pause");
        exit(1);
    }
    strcat(main_string, new_name);
    names++;
    system("cls");
    printf("Nome adicionado com sucesso.\n");
    system("pause");
}

int menu()
{
    int x;
    system("cls");
    printf("1) Adicionar Nome\n");
    printf("2) Remover Nome\n");
    printf("3) Listar\n");
    printf("4) Sair\n");
    printf("Digite a opção desejada:  ");
    scanf("%d", &x);
    return x;
}

void listar(char *main_string)
{
    system("cls");
    if (main_string[0] == '\0')
    {
        printf("Nenhum nome armazenado.\n");
        return;
    }
    int i = 0;
    int name_id = 1;
    printf("%d) ", name_id);
    while (main_string[i] != '\0')
    {
        if (main_string[i] == '!')
        {
            printf("\n");
            if (main_string[++i] == '\0')
                break;
            name_id++;
            printf("%d) ", name_id);
        }
        printf("%c", main_string[i++]);
    }
}