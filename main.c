#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome_produto[100];
    int quantidade;
    float preco;
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
            if (fscanf(estoque, "%s\t%s\t%s", buffer, buffer, buffer) == 3);
        }
        if (i != 0)
        {
            j++;
            if (j == 1)
            {
                i = 0;
            }
            else if (fscanf(estoque, "%s\t\t%d\t\t%f", produtos[i].nome_produto, &produtos[i].quantidade, &produtos[i].preco) == 3);
        }
    }
    fclose(estoque);
}

void add_produto(FILE *estoque, tabela_produtos produtos[100])
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
        for(int i = 0; i < 101; i++)
        {
            if (i == 0)
            {
                fprintf(estoque, "%s\t%s\t%s\n", "Produto", "Quantidade", "Preço");
            }
            fprintf(estoque, "%s\t\t%d\t\t%.2f\n", "NULL", 0, 0.0);
        }
        fflush(estoque);
    }
    fclose(estoque);
    // chama a funçao para puxar os dados pra memoria ram
    inicializa_dados_tabela(produtos, estoque);
    // inicia o programa de controle de estoque
    printf("**************************************************\n");
    printf("         BEM VINDO AO CONTROLE DE ESTOQUE \n");
    printf("**************************************************\n");
    while (resposta >= 0 && resposta < 2)
    {
        printf("Escolha uma das opcoes abaixo: \n");
        printf("0 - Ver estoque atual\n");
        printf("1 - atulizar estoque\n");
        printf("2 - Sair\n");
        scanf("%d", &resposta);
        if (resposta == 0)
        {
            printf("Este eh o estoque atual: \n");
            for(int i = 0; i < 100; i++)
            {
                if((i+1)%2 == 0)
                {
                    printf("Produto: %s, Quantidade: %d, Preco: %.2f\n", produtos[i].nome_produto, produtos[i].quantidade, produtos[i].preco);
                }
                else if((i+1)%2 != 0)
                {
                    printf("Produto: %s, Quantidade: %d, Preco: %.2f            ", produtos[i].nome_produto, produtos[i].quantidade, produtos[i].preco);
                }
            } 
        }
        else
        {
            printf("**************************************\n");
            printf("        O Que deseja fazer?\n");
            printf("**************************************\n");
            printf("0 - Adicionar produto\n");
            printf("1 - Remover produto\n");
            printf("2 - Alterar preço\n");
            printf("3 - Alterar quantidade\n");
            printf("4 - Sair\n");
            scanf("%d", &resposta);
            while(resposta >= 0 && resposta <= 4)
            {
                if (resposta == 0)
                {
                    // add_produto(estoque, produtos);
                }
                else if (resposta == 1)
                {
                    // Remover produto
                }
                else if (resposta == 2)
                {
                    // Alterar preço
                }
                else if (resposta == 3)
                {
                    // Alterar quantidade
                }
                else if (resposta == 4)
                {
                    break;
                }
            }
        }
    }
    return 0;
}