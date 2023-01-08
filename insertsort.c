#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os dados de cada linha do arquivo CSV
struct Data {
  int id;
  int Time;
  int Length;
  int Delay;
};

int main(void) {
  // Abre o arquivo para leitura
  FILE *fp = fopen("bancoAjustado4colunas.csv", "r");
  FILE *fp_out = fopen("sorted.csv", "w");

  if (fp == NULL) {
    perror("Error opening file");
    return 1;
  }

  // Aloca memória para a lista de estruturas
  const int num_lines = 10;
  struct Data *list = malloc(num_lines * sizeof(struct Data));
  if (list == NULL) {
    perror("Error allocating memory");
    return 1;
  }

  // Lê o arquivo linha por linha e armazena os dados em uma estrutura
  char line[1024];
  int i = 0;
  while (fgets(line, 1024, fp)) {
    sscanf(line, "%d,%d,%d,%d", &list[i].id, &list[i].Time, &list[i].Length, &list[i].Delay);
    i++;
  }

  // Fecha o arquivo
  fclose(fp);

  // Ordena a lista de estruturas por idade com a ordenação por inserção
  for (int j = 1; j < num_lines; j++) {
    struct Data key = list[j];
    int k = j - 1;
    while (k >= 0 && list[k].Length > key.Length) {
      list[k + 1] = list[k];
      k--;
    }
    list[k + 1] = key;
  }

  // Imprime as estruturas ordenadas
  for (int j = 0; j < num_lines; j++) {
    fprintf(fp_out, "%d,%d,%d,%d\n", list[j].id, list[j].Time, list[j].Length, list[j].Delay);
  }

 // Fecha o arquivo de saída
  fclose(fp_out);

  // Libera a memória alocada para a lista
  free(list);

  return 0;
}
