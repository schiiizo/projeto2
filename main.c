//JOSUE MACHICADO AGUILERA FARINHA - 32374410
//GUILHERME GARCIA MARRETTO - 32276631


#include <stdio.h>

// Função para verificar a imagem
void verificaImagem(int matriz[100][100], int x1, int y1, int x2, int y2) {
  // Obtém a cor do ponto inicial (canto superior esquerdo)
  int cor = matriz[x1][y1];

  // Percorre a submatriz delimitada pelos pontos (x1, y1) e (x2, y2)
  for (int i = x1; i <= x2; i++) {
      for (int j = y1; j <= y2; j++) {
          // Se encontrar uma cor diferente, imprime "X" e divide em quadrantes
          if (matriz[i][j] != cor) {
              printf("X");
              // Chama a função recursivamente para cada quadrante
              verificaImagem(matriz, x1, y1, (x1 + x2) / 2, (y1 + y2) / 2);       // 1º quadrante
              verificaImagem(matriz, x1, (y1 + y2) / 2 + 1, (x1 + x2) / 2, y2);  // 2º quadrante
              verificaImagem(matriz, (x1 + x2) / 2 + 1, y1, x2, (y1 + y2) / 2);  // 3º quadrante
              verificaImagem(matriz, (x1 + x2) / 2 + 1, (y1 + y2) / 2 + 1, x2, y2);  // 4º quadrante
              return;
          }
      }
  }
  printf(cor == 0 ? "P" : "B");
  
}

// Função para ler a imagem PBM do arquivo
void lerPBM(int matriz[1024][768], int* n, int* m, char* filename) {
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
      // Se não conseguir abrir o arquivo, imprime uma mensagem de erro
      printf("Não foi possível abrir o arquivo\n");
      return;
  }

  // Ler o cabeçalho do arquivo PBM
  char magicNumber[3];
  fscanf(file, "%s", magicNumber);
  fscanf(file, "%d %d", n, m);

  // Ler os pixels da imagem
  for (int i = 0; i < *n; i++) {
      for (int j = 0; j < *m; j++) {
          fscanf(file, "%d", &matriz[i][j]);
      }
  }

  fclose(file);
  
}



int main() {
  int opcao, n, m;
  int matriz[100][100];
  
  do {
      printf("\n### Bem-vindo ao Verificador de Imagens ###\n");
      printf("Escolha uma opção:\n");
      printf("1 - Inserir manualmente uma matriz\n");
      printf("2 - Ler uma matriz a partir de uma imagem PBM\n");
      printf("3 - Ajuda\n");
      printf("0 - Sair\n");
      printf("Número: ");
      scanf("%d", &opcao);
  
      if (opcao == 1) {
          printf("\n### Inserir Manualmente uma Matriz ###\n");
          printf("Informe as dimensões da imagem (dê espaço!): ");
          scanf("%d %d", &n, &m);
  
          printf("Digite os elementos da matriz (1 para branco, 0 para preto):\n");
          for (int i = 0; i < n; i++) {
              for (int j = 0; j < m; j++) {
                  printf("\nElemento [%d][%d]: ", i, j);
                  scanf("%d", &matriz[i][j]);
              }
          }
  
          printf("\n### Imagem Inserida com Sucesso ###\n");
          printf("Código gerado: ");
          verificaImagem(matriz, 0, 0, n - 1, m - 1);
          printf("\n");
      } else if (opcao == 2) {
          printf("\n### Ler Matriz a partir de uma Imagem PBM ###\n");
          printf("Informe o caminho do arquivo PBM: ");
          char filename[256];
          scanf("%s", filename);
          lerPBM(matriz, &n, &m, filename);
  
          printf("\n### Imagem Lida com Sucesso ###\n");
          printf("Código gerado: ");
          verificaImagem(matriz, 0, 0, n - 1, m - 1);
          printf("\n");
      } else if (opcao == 3) {
          printf("\n### Ajuda ###\n");
          printf("Este programa permite verificar uma imagem binária e gerar um código correspondente.\n");
          printf("1. Escolha a opção para inserir manualmente ou ler de um arquivo PBM.\n");
          printf("2. Siga as instruções fornecidas para inserção manual ou informe o caminho do arquivo PBM.\n");
          printf("3. Após a leitura ou inserção, o programa exibirá o código gerado para a imagem verificada.\n");
          printf("4. Repita o processo conforme necessário.\n");
      } else if (opcao == 0) {
          printf("\nAté logo!\n");
      } else {
          printf("\nOpção inválida. Tente novamente.\n");
      }
  
  } while (opcao != 0);
  
  return 0;
}
  