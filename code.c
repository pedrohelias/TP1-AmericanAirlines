#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para armazenar os dados de cada linha do arquivo CSV
typedef struct {
  int id;
  int Time;
  int Length;
  int Delay;
} Data;

typedef struct {
  int length;
  int total;
  int delayed;
} Subspace;

int main(void) {

int dataSize = 1;
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
    while (fgets(line, 1024, fp)) {  
       Data *new;
        new = realloc(data,dataSize * sizeof *data);
        if (new == NULL) {
            perror("realloc");
            free(data);
            return 2;
        }
    data = new;  
    int cnt = fscanf(fp,"%d,%d,%d,%d", &data[dataCount].id, &data[dataCount].Time, &data[dataCount].Length, &data[dataCount].Delay);
    dataSize++;
    printf("%d\n", dataSize);
    if (cnt == EOF)
        break;
    // if (cnt != 4) {
    //     printf("%d/n", cnt );
    //     printf("Error reading data\n");
    //     return 1;
    // }
    dataCount++;
    }


  // Fecha o arquivo
  fclose(fp);

  // Ordena a lista de estruturas por idade com a ordenação por inserção
  int trial = 0;
  int minLength = 99999;
  int maxLength = -99999;
  //Subspace* spaces = NULL;
  
  clock_t t = clock();

  for (int j = 1; j < (dataCount - 1)/10; j++){ 
    Data key = data[j];
    
    //addSample(spaces, key.Length, key.Delay);
    
    if(key.Length > maxLength){
      maxLength = key.Length;
    }
    if(key.Length < minLength){
      minLength = key.Length;
    }
    int k = j - 1;
    while (k >= 0 && data[k].Length > key.Length){
      data[k + 1] = data[k];
      trial++;
      k--;
    }
    data[k + 1] = key;
  }

  clock_t t2 = clock();

  printf("maxLength: %d minLength %d\n", maxLength, minLength);
  // Imprime as estruturas ordenadas
  for (int j = 0; j < (dataCount - 1)/10; j++) {
    fprintf(fp_out, "%d,%d,%d,%d\n", data[j].id, data[j].Time, data[j].Length, data[j].Delay);
  }
  
  t2 = t2 - t;  
  
   printf("Tempo de execucao: %lf", ((double)t2)/((CLOCKS_PER_SEC/1000))); //conversão para double

 // Fecha o arquivo de saída
  fclose(fp_out);
  // Libera a memória alocada para a lista
  free(data);
  //free(spaces);
  return 0;
}
