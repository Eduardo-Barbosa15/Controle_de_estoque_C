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
    estoque = fopen("estoque.txt", "r");
    for(int i = 0; i < 100; i++)
    {
        fscanf(estoque, "%s %d %.2f", produtos[i].nome_produto, &produtos[i].quantidade, &produtos[i].preco);
    }
    fclose(estoque);
}

void atualiza_estoque(FILE *estoque, tabela_produtos produtos[100])
{
    estoque = fopen("estoque.txt", "w");
    fclose(estoque);
}

int main()
{
    // cria o arquivo caso nao exista e inicializa os dados iniciais do estoque zerando tudo, caso já exista, apenas abre o arquivo.
    FILE *estoque;
    estoque = fopen("estoque.txt", "r");
    tabela_produtos produtos[100];
    for(int i = 0; i < 100; i++)
    {
        strcpy(produtos[i].nome_produto, " ");
        produtos[i].quantidade = 0;
        produtos[i].preco = 0.0;
    }
    if (estoque == NULL)
    {
        fclose(estoque);
        estoque = fopen("estoque.txt", "+w");
        fclose(estoque);
        estoque = fopen("estoque.txt", "w");
        for(int i = 0; i < 100; i++)
        {
            fprintf(estoque, "%s %d %.2f\n", " ", 0, 0.0);
        }
        fclose(estoque);
    }
    fclose(estoque);
    // chama a funçao para puxar os dados pra memoria ram
    inicializa_dados_tabela(produtos, estoque);
    // inicia o programa de controle de estoque
    printf("**************************************************\n");
    printf("         BEM VINDO AO CONTROLE DE ESTOQUE \n");
    printf("**************************************************\n");
    printf("Este eh o estoque atual: \n");
    for(int i = 0; i < 100; i++)
    {
        if(i%2 == 0)
        {
            printf("Produto: %s, Quantidade: %d, Preco: %.2f\n", produtos[i].nome_produto, produtos[i].quantidade, produtos[i].preco);
        }
        if(i%2 != 0)
        {
            printf("Produto: %s, Quantidade: %d, Preco: %.2f            ", produtos[i].nome_produto, produtos[i].quantidade, produtos[i].preco);
        }
    }
    atualiza_estoque(estoque, produtos);
    return 0;
}