#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os dados de cada linha do arquivo CSV
typedef struct  {
  int id;
  int Time;
  int Length;
  int Delay;
}Data;

int main(void) {

int dataSize = 0;
int dataCount = 0;
Data *data = NULL;

  char line[1024];




  // Abre o arquivo para leitura
  FILE *fp = fopen("bancoAjustado4colunas.csv", "r");
  FILE *fp_out = fopen("sorted.csv", "w");

  if (fp == NULL) {
    perror("Error opening file");
    return 1;
  }

  // Aloca memória para a lista de estruturas


  // Lê o arquivo linha por linha e armazena os dados em uma estrutura
while (1) {
    if (dataCount >= dataSize) {
        Data *new;
        dataSize += 1000;
        new = realloc(data,dataSize * sizeof *data);
        if (new == NULL) {
            perror("realloc");
            free(data);
            return 2;
        }
        data = new;
    }
    while (fgets(line, 1024, fp)) {     
    int cnt = fscanf(fp,"%d, %d, %d, %d", &data[dataCount].id, &data[dataCount].Time, &data[dataCount].Length, &data[dataCount].Delay);
    if (cnt == EOF)
        break;
    if (cnt != 4) {
        printf("%d", cnt );
        printf("Error reading data\n");
        return 1;
    }
    dataCount++;
     }
}

  // Fecha o arquivo
  fclose(fp);

  // Ordena a lista de estruturas por idade com a ordenação por inserção
  for (int j = 1; j < 600000; j++) {
    Data key = data[j];
    int k = j - 1;
    while (k >= 0 && data[k].Length > key.Length) {
      data[k + 1] = data[k];
      k--;
    }
    data[k + 1] = key;
  }

  // Imprime as estruturas ordenadas
  for (int j = 0; j < 600000; j++) {
    fprintf(fp_out, "%d,%d,%d,%d\n", data[j].id, data[j].Time, data[j].Length, data[j].Delay);
  }

 // Fecha o arquivo de saída
  fclose(fp_out);

  // Libera a memória alocada para a lista
  free(data);

  return 0;
}