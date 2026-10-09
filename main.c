#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome_produto[100];
    int unsigned quantidade;
    float preco;
    short unsigned int id;
} tabela_produtos;

void inicializa_dados_tabela(tabela_produtos produtos[100], FILE *estoque)
{
    int j = 0;
    estoque = fopen("estoque.txt", "r");
    for(int i = 0; i < 100; i++)
    {
        if(i == 0)
        {
            char buffer[100];
            if (fscanf(estoque, "%s\t%s\t%s\t%s",buffer, buffer, buffer, buffer) == 4);
        }
        if (i != 0)
        {
            j++;
            if (j == 1)
            {
                i = 0;
            }
            else if (fscanf(estoque, "%s\t\t%d\t\t%f\t%d", produtos[i].nome_produto, &produtos[i].quantidade, &produtos[i].preco, &produtos[i].id) == 4);
        }
    }
    fclose(estoque);
}

void atualiza_arquivo(FILE *estoque, tabela_produtos produtos[100])
{
    estoque = fopen("estoque.txt", "w");
    for(int i = 0; i < 100; i++)
    {
        if (i == 0)
        {
            fprintf(estoque, "%s\t%s\t%s\t%s\n", "Produto", "Quantidade", "Preço", "ID");
        }
        fprintf(estoque, "%s\t\t%d\t\t%.2f\t%d\n", produtos[i].nome_produto, produtos[i].quantidade, produtos[i].preco, produtos[i].id);
    }
    fflush(estoque);
    fclose(estoque);
}

void add_produto(FILE *estoque, tabela_produtos produtos[100])
{   
    int resposta;
    estoque = fopen("estoque.txt", "w");
    for (int i = 0; i < 100; i++)
    {
        if (produtos[i].id != 0 && resposta == 0)
        {
            break;
        }
        if (produtos[i].id == 0)
        {
            printf("Digite o nome do produto: \n");
            scanf("%s", produtos[i].nome_produto);
            printf("Digite a quantidade do produto: \n");
            scanf("%d", &produtos[i].quantidade);
            printf("Digite o preco do produto: \n");
            scanf("%f", &produtos[i].preco);
            produtos[i].id = i + 1;
            printf("Produto adicionado com sucesso!\n");
            printf("deseja adicionar outro produto? (1 - Sim / 0 - Nao)\n");
            scanf("%d", &resposta);
            if (resposta == 0)
            {
                i = 100;
            }
        }
    }
    fclose(estoque);
}

void remove_produto(FILE *estoque, tabela_produtos produtos[100])
{
    int buffer;
    estoque = fopen("estoque.txt", "w");
    printf("Digite o ID do produto voce deseja remover\n");
    scanf("%d", &buffer);
    for (int i = 0; i < 100; i++)
    {
        if (produtos[i].id == buffer)
        {
            produtos[i].id = 0;
            strcpy(produtos[i].nome_produto, "NULL");
            produtos[i].quantidade = 0;
            produtos[i].preco = 0.0;
            printf("Produto removido com sucesso!\n");
            printf("deseja remover outro produto? (1 - Sim / 0 - Nao)\n");
            int resposta;
            scanf("%d", &resposta);
            if (resposta == 0)
            {
                i = 100;
                break;
            }
            else
            {
                printf("Digite o ID do produto você deseja remover\n");
                scanf("%d", &buffer);
                i = 0;
            }
        }
       
    }
    fclose(estoque);
}

void altera_preco(FILE *estoque, tabela_produtos produtos[100])
{
    estoque = fopen("estoque.txt", "w");
    
    fclose(estoque);
}

int main()
{
    int resposta = 0;
    // cria o arquivo caso nao exista e inicializa os dados iniciais do estoque zerando tudo, caso já exista, apenas abre o arquivo.
    FILE *estoque;
    estoque = fopen("estoque.txt", "r");
    tabela_produtos produtos[100];
    if (estoque == NULL)
    {
        fclose(estoque);
        estoque = fopen("estoque.txt", "w");
        for(int i = 0; i < 100; i++)
        {
            if (i == 0)
            {
                fprintf(estoque, "%s\t%s\t%s\t%s\n", "Produto", "Quantidade", "Preço", "ID");
            }
            fprintf(estoque, "%s\t\t%d\t\t%.2f\t%d\n", "NULL", 0, 0.0, 0);
        }
        fflush(estoque);
    }
    fclose(estoque);
    // chama a funçao para puxar os dados pra memoria ram
    inicializa_dados_tabela(produtos, estoque);
    // inicia o programa de controle de estoque
    
    while (resposta >= 0 && resposta < 2)
    {
        printf("**************************************************\n");
        printf("         BEM VINDO AO CONTROLE DE ESTOQUE \n");
        printf("**************************************************\n");
        printf("Escolha uma das opcoes abaixo: \n");
        printf("0 - Ver estoque atual\n");
        printf("1 - atulizar estoque\n");
        printf("2 - Sair\n");
        scanf("%d", &resposta);
        if (resposta == 0)
        {
            printf("**************************************\n");
            printf("Este eh o estoque atual: \n");
            printf("**************************************\n");
            for(int i = 0; i < 100; i++)
            {
                if((i+1)%2 == 0)
                {
                    printf("Produto: %s, Quantidade: %d, Preco: %.2f, ID: %d\n", produtos[i].nome_produto, produtos[i].quantidade, produtos[i].preco, produtos[i].id);
                }
                else if((i+1)%2 != 0)
                {
                    printf("Produto: %s, Quantidade: %d, Preco: %.2f, ID: %d            ", produtos[i].nome_produto, produtos[i].quantidade, produtos[i].preco, produtos[i].id);
                }
            }
            printf("\n");
        }
        else if (resposta == 2)
        {
            break;
        }
        else
        {
            printf("**************************************\n");
            printf("        O Que deseja fazer?\n");
            printf("**************************************\n");
            printf("0 - Adicionar produto\n");
            printf("1 - Remover produto\n");
            printf("2 - Alterar preco\n");
            printf("3 - Alterar quantidade\n");
            printf("4 - Voltar\n");
            scanf("%d", &resposta);
            while(resposta >= 0 && resposta <= 3)
            {
                if (resposta == 0)
                {
                    add_produto(estoque, produtos);
                    atualiza_arquivo(estoque, produtos);
                    break;
                }
                else if (resposta == 1)
                {
                    remove_produto(estoque, produtos);
                    atualiza_arquivo(estoque, produtos);
                    break;
                }
                else if (resposta == 2)
                {
                    // Alterar preço
                }
                else if (resposta == 3)
                {
                    // Alterar quantidade
                }
            }
            resposta = 0;
            printf("\n");
        }
    }
    return 0;
}