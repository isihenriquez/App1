#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_linea 1000
#define max_pizza 100
#define max_nombre 100
#define max_a 12
#define max_ventas 10000
#define max_fecha 10
#define max_cant 100
#define max_item 100

typedef struct {
  char name[max_nombre];
  int count;
} NombrePizza;

typedef struct {
  char date[max_fecha];
  float total_sales;
} FechaVenta;

void limpiar(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (str[i] == '"') {
      str[i] = ' ';
    }
  }
}

void agregar_espacios(char *str) {
  int len = strlen(str);
  for (int i = 1; i < len; i++) {
    if (isupper(str[i]) && !isspace(str[i - 1])) {
      memmove(&str[i + 1], &str[i], len - i + 1);
      str[i] = ' ';
      len++;
      i++;
    }
  }
}

void trimString(char *str) {
  int i = strlen(str) - 1;
  while (i >= 0 && (str[i] == '\n' || str[i] == '\r')) {
    str[i] = '\0';
    i--;
  }
}

char *pms(const char *filename) {
  FILE *file = fopen(filename, "r");
  
  NombrePizza conteo[max_cant];
  int unicas = 0;

  char line[max_linea];
  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file)) {
    trimString(line);
    if (line[0] != '\0') {
      char *token = strtok(line, ",");
      int token_index = 0;
      char *last_token = NULL;
      int quantity = 0;

      while (token != NULL) {
        if (token_index == 3) {
          quantity = atoi(token);
        }
        last_token = token;
        token = strtok(NULL, ",");
        token_index++;
      }

      if (last_token != NULL) {
        if (last_token[0] == '"' && last_token[strlen(last_token) - 1] == '"') {
          memmove(last_token, last_token + 1, strlen(last_token) - 2);
          last_token[strlen(last_token) - 2] = '\0';
        }

        int found = 0;
        for (int i = 0; i < unicas; i++) {
          if (strcmp(conteo[i].name, last_token) == 0) {
            conteo[i].count += quantity;
            found = 1;
            break;
          }
        }

        if (!found) {
          strncpy(conteo[unicas].name, last_token, max_nombre);
          conteo[unicas].count = quantity;
          unicas++;
        }
      }
    }
  }

  fclose(file);

  int max_count = -1;
  for (int i = 0; i < unicas; i++) {
    if (conteo[i].count > max_count) {
      max_count = conteo[i].count;
    }
  }

  char *result = malloc(max_nombre * unicas + 50); 
  strcpy(result, "Pizza mas vendida:\n"); 

  for (int i = 0; i < unicas; i++) {
    if (conteo[i].count == max_count) {
      strcat(result, conteo[i].name);
      strcat(result, "\n");
    }
  }

  return result;
}


char *pls(const char *filename) {
  FILE *file = fopen(filename, "r");

  NombrePizza conteo[max_cant];
  int unicas = 0;

  char line[max_linea];
  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file)) {
    trimString(line);
    if (line[0] != '\0') {
      char *token = strtok(line, ",");
      int token_index = 0;
      char *last_token = NULL;
      int quantity = 0;

      while (token != NULL) {
        if (token_index == 3) {
          quantity = atoi(token);
        }
        last_token = token;
        token = strtok(NULL, ",");
        token_index++;
      }

      if (last_token != NULL) {
        if (last_token[0] == '"' && last_token[strlen(last_token) - 1] == '"') {
          memmove(last_token, last_token + 1, strlen(last_token) - 2);
          last_token[strlen(last_token) - 2] = '\0';
        }

        int found = 0;
        for (int i = 0; i < unicas; i++) {
          if (strcmp(conteo[i].name, last_token) == 0) {
            conteo[i].count += quantity;
            found = 1;
            break;
          }
        }

        if (!found) {
          strncpy(conteo[unicas].name, last_token, max_nombre);
          conteo[unicas].count = quantity;
          unicas++;
        }
      }
    }
  }

  fclose(file);

  int min_count = __INT_MAX__;
  for (int i = 0; i < unicas; i++) {
    if (conteo[i].count < min_count) {
      min_count = conteo[i].count;
    }
  }
  