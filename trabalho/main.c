#include <stdio.h>
#include <stdlib.h>

#define MAX_PRODUTOS 100
#define MAX_VENDEDORES 100
#define MAX_VENDAS 100

struct Produto {
    int ID;
    float preco;
    char descricao[100];
};

struct Vendedor {
    int ID;
    char nome[100];
};

struct Venda {
    int IDVendedor;
    int IDProduto;
    int UniVendidas;
};

int main() {
    FILE *arquivoProdutos = fopen("produtos.txt", "r");
    if (arquivoProdutos == NULL) {
        perror("Erro ao abrir o arquivo de produtos");
        exit(1);
    }

    int numProdutos;
    fscanf(arquivoProdutos, "%d", &numProdutos);

    struct Produto produtos[MAX_PRODUTOS];
    for (int i = 0; i < numProdutos; i++) {
        fscanf(arquivoProdutos, "%d %f %s", &produtos[i].ID, &produtos[i].preco, produtos[i].descricao);
    }

    fclose(arquivoProdutos);

    FILE *arquivoVendedores = fopen("vendedores.txt", "r");
    if (arquivoVendedores == NULL) {
        perror("Erro ao abrir o arquivo de vendedores");
        exit(1);
    }

    int numVendedores;
    fscanf(arquivoVendedores, "%d", &numVendedores);

    struct Vendedor vendedores[MAX_VENDEDORES];
    for (int i = 0; i < numVendedores; i++) {
        fscanf(arquivoVendedores, "%d %s", &vendedores[i].ID, vendedores[i].nome);
    }

    fclose(arquivoVendedores);

    FILE *arquivoVendas = fopen("vendas.txt", "r");
    if (arquivoVendas == NULL) {
        perror("Erro ao abrir o arquivo de vendas");
        exit(1);
    }

    int numVendas;
    fscanf(arquivoVendas, "%d", &numVendas);

    struct Venda vendas[MAX_VENDAS];
    for (int i = 0; i < numVendas; i++) {
        fscanf(arquivoVendas, "%d %d %d", &vendas[i].IDVendedor, &vendas[i].IDProduto, &vendas[i].UniVendidas);
    }

    fclose(arquivoVendas);

    float totalGeral = 0;
    float totalPorProduto[MAX_PRODUTOS] = {0};
    float totalPorVendedor[MAX_VENDEDORES] = {0};

    // Calcular os totais
    for (int i = 0; i < numVendas; i++) {
        int codigoProduto = vendas[i].IDProduto;
        int codigoVendedor = vendas[i].IDVendedor;
        int unidadesVendidas = vendas[i].UniVendidas;

        totalGeral += produtos[codigoProduto].preco * unidadesVendidas;
        totalPorProduto[codigoProduto] += produtos[codigoProduto].preco * unidadesVendidas;
        totalPorVendedor[codigoVendedor] += produtos[codigoProduto].preco * unidadesVendidas;
    }

    FILE *arquivoTotais = fopen("totais.txt", "w");
    if (arquivoTotais == NULL) {
        perror("Erro ao abrir o arquivo de totais");
        exit(1);
    }

    // Escrever os totais no arquivo de saída
    fprintf(arquivoTotais, "Log de Vendas:\n");
    for (int i = 0; i < numVendas; i++) {
        fprintf(arquivoTotais, "[%d] %d %d %d\n", i, vendas[i].IDVendedor, vendas[i].IDProduto, vendas[i].UniVendidas);
    }

    fprintf(arquivoTotais, "Catalogo de Produtos:\n");
    for (int i = 0; i < numProdutos; i++) {
        fprintf(arquivoTotais, "[%d] %d %.2f %s\n", i, produtos[i].ID, produtos[i].preco, produtos[i].descricao);
    }

    fprintf(arquivoTotais, "Lista de Vendedores:\n");
    for (int i = 0; i < numVendedores; i++) {
        fprintf(arquivoTotais, "[%d] %d %s\n", i, vendedores[i].ID, vendedores[i].nome);
    }

    fprintf(arquivoTotais, "Total geral vendido: %.2f\n", totalGeral);

    fprintf(arquivoTotais, "Total de vendas de cada produto:\n");
    for (int i = 0; i < numProdutos; i++) {
        fprintf(arquivoTotais, "Produto %d (%s): R$%.2f\n", produtos[i].ID, produtos[i].descricao, totalPorProduto[i]);
    }

    fprintf(arquivoTotais, "Total de vendas de cada vendedor:\n");
    for (int i = 0; i < numVendedores; i++) {
        fprintf(arquivoTotais, "Vendedor %d (%s): R$%.2f\n", vendedores[i].ID, vendedores[i].nome, totalPorVendedor[i]);
    }

    fclose(arquivoTotais);

    printf("Totais calculados e salvos em totais.txt.\n");

    return 0;
}
