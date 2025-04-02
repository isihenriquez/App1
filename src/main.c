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

  char *result = malloc(max_nombre * unicas + 50); 
  strcpy(result, "Pizza menos vendida:\n"); 

  for (int i = 0; i < unicas; i++) {
    if (conteo[i].count == min_count) {
      strcat(result, conteo[i].name);
      strcat(result, "\n");
    }
  }

  return result;
}


char *dms(const char *filename) {
  FILE *file = fopen(filename, "r");
  FechaVenta ventas_por_fecha[max_ventas];
  int unique_dates = 0;

  char line[max_linea];
  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file)) {
    trimString(line);
    if (line[0] != '\0') {
      char *token = strtok(line, ",");
      int token_index = 0;
      char *last_token = NULL;
      float total_price = 0.0;

      while (token != NULL) {
        if (token_index == 6) {
          total_price = atof(token);
        } else if (token_index == 4) {
          last_token = token;
        }
        token = strtok(NULL, ",");
        token_index++;
      }

      if (last_token != NULL) {

        int found = 0;
        for (int i = 0; i < unique_dates; i++) {
          if (strcmp(ventas_por_fecha[i].date, last_token) == 0) {
            ventas_por_fecha[i].total_sales += total_price;
            found = 1;
            break;
          }
        }

        if (!found) {
          strncpy(ventas_por_fecha[unique_dates].date, last_token, max_fecha);
          ventas_por_fecha[unique_dates].total_sales = total_price;
          unique_dates++;
        }
      }
    }
  }

  fclose(file);

  float max_venta = -1.0;
  char max_venta_fecha[max_fecha];
  for (int i = 0; i < unique_dates; i++) {
    if (ventas_por_fecha[i].total_sales > max_venta) {
      max_venta = ventas_por_fecha[i].total_sales;
      strncpy(max_venta_fecha, ventas_por_fecha[i].date, max_fecha);
    }
  }
  char *result = malloc(max_linea * sizeof(char));
  snprintf(result, max_linea,
           "Fecha con más ventas en términos de dinero: %s (con %.2f)",
           max_venta_fecha, max_venta);

  return result;
}

char *dls(const char *filename) {
  FILE *file = fopen(filename, "r");
  FechaVenta ventas_por_fecha[max_ventas];
  int unique_dates = 0;
  char line[max_linea];
  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file)) {
    trimString(line);
    if (line[0] != '\0') {
      char *token = strtok(line, ",");
      int token_index = 0;
      char *last_token = NULL;
      float total_price = 0.0;

      while (token != NULL) {
        if (token_index == 6) {
          total_price = atof(token);
        } else if (token_index == 4) {
          last_token = token;
        }
        token = strtok(NULL, ",");
        token_index++;
      }

      if (last_token != NULL) {
        int found = 0;
        for (int i = 0; i < unique_dates; i++) {
          if (strcmp(ventas_por_fecha[i].date, last_token) == 0) {
            ventas_por_fecha[i].total_sales += total_price;
            found = 1;
            break;
          }
        }

        if (!found) {
          strncpy(ventas_por_fecha[unique_dates].date, last_token, max_fecha);
          ventas_por_fecha[unique_dates].total_sales = total_price;
          unique_dates++;
        }
      }
    }
  }

  fclose(file);

  float min_ventas = FLT_MAX;
  char min_ventas_fecha[max_fecha];
  for (int i = 0; i < unique_dates; i++) {
    if (ventas_por_fecha[i].total_sales < min_ventas) {
      min_ventas = ventas_por_fecha[i].total_sales;
      strncpy(min_ventas_fecha, ventas_por_fecha[i].date, max_fecha);
    }
  }

  char *result = malloc(max_linea * sizeof(char));

  snprintf(result, max_linea,
           "Fecha con menos ventas en términos de dinero: %s (con %.2f)",
           min_ventas_fecha, min_ventas);

  return result;
}

char *dmsp(const char *filename) {
  FILE *file = fopen(filename, "r");
  FechaVenta ventas_por_fecha[max_ventas];
  int fechasuni = 0;
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
        } else if (token_index == 4) {
          last_token = token;
        }
        token = strtok(NULL, ",");
        token_index++;
      }

      if (last_token != NULL) {

        int found = 0;
        for (int i = 0; i < fechasuni; i++) {
          if (strcmp(ventas_por_fecha[i].date, last_token) == 0) {
            ventas_por_fecha[i].total_sales += quantity;
            found = 1;
            break;
          }
        }

        if (!found) {
          strncpy(ventas_por_fecha[fechasuni].date, last_token, max_fecha);
          ventas_por_fecha[fechasuni].total_sales = quantity;
          fechasuni++;
        }
      }
    }
  }

  fclose(file);

  int max_sales = -1;
  char max_sales_date[max_fecha];
  for (int i = 0; i < fechasuni; i++) {
    if (ventas_por_fecha[i].total_sales > max_sales) {
      max_sales = ventas_por_fecha[i].total_sales;
      strncpy(max_sales_date, ventas_por_fecha[i].date, max_fecha);
    }
  }

  char *result = malloc(max_linea * sizeof(char));
  snprintf(result, max_linea,
           "Fecha con mas ventas en terminos de cantidad: %s con %d",
           max_sales_date, max_sales);

  return result;
}

char *dlsp(const char *filename) {
  FILE *file = fopen(filename, "r");

  FechaVenta ventas_por_fecha[max_ventas];
  int unique_dates = 0;

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
        } else if (token_index == 4) {
          last_token = token;
        }
        token = strtok(NULL, ",");
        token_index++;
      }

      if (last_token != NULL) {
        int found = 0;
        for (int i = 0; i < unique_dates; i++) {
          if (strcmp(ventas_por_fecha[i].date, last_token) == 0) {
            ventas_por_fecha[i].total_sales += quantity;
            found = 1;
            break;
          }
        }

        if (!found) {
          strncpy(ventas_por_fecha[unique_dates].date, last_token, max_fecha);
          ventas_por_fecha[unique_dates].total_sales = quantity;
          unique_dates++;
        }
      }
    }
  }

  fclose(file);

  float min_sales = FLT_MAX;
  char min_sales_date[max_fecha];
  for (int i = 0; i < unique_dates; i++) {
    if (ventas_por_fecha[i].total_sales < min_sales) {
      min_sales = ventas_por_fecha[i].total_sales;
      strncpy(min_sales_date, ventas_por_fecha[i].date, max_fecha);
    }
  }
  char *result = malloc(max_linea * sizeof(char));
  snprintf(result, max_linea,
           "Fecha con menos ventas en términos de cantidad: %s con %.2f",
           min_sales_date, min_sales);

  return result;
}

char *apo(const char *filename) {
  FILE *file = fopen(filename, "r");

  int total_orden = 0;
  int total_pizzas = 0;

  char line[max_linea];
  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file)) {
    trimString(line);
    if (line[0] != '\0') {
      char *token = strtok(line, ",");
      int token_index = 0;
      int quantity = 0;

      while (token != NULL) {
        if (token_index == 3) {
          quantity = atoi(token);
        }
        token = strtok(NULL, ",");
        token_index++;
      }

      total_pizzas += quantity;
      total_orden++;
    }
  }

  fclose(file);

  float prom_pizza = (float)total_pizzas / total_orden;
  char *result = malloc(max_linea * sizeof(char));
  snprintf(result, max_linea, "Promedio de pizzas por orden: %.2f", prom_pizza);

  return result;
}

char *apd(const char *filename) {
  FILE *file = fopen(filename, "r");

  FechaVenta ventas_por_fecha[max_ventas];
  int unique_dates = 0;

  char line[max_linea];
  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file)) {
    trimString(line);
    if (line[0] != '\0') {
      char *token = strtok(line, ",");
      int token_index = 0;
      char *last_token = NULL;
      int quantity = 0;
      char *date_token = NULL;

      while (token != NULL) {
        if (token_index == 3) {
          quantity = atoi(token);
        }
        if (token_index == 4) {
          date_token = token;
        }
        token = strtok(NULL, ",");
        token_index++;
      }

      if (date_token != NULL) {
        int found = 0;
        for (int i = 0; i < unique_dates; i++) {
          if (strcmp(ventas_por_fecha[i].date, date_token) == 0) {
            ventas_por_fecha[i].total_sales += quantity;
            found = 1;
            break;
          }
        }

        if (!found) {
          strncpy(ventas_por_fecha[unique_dates].date, date_token, max_fecha);
          ventas_por_fecha[unique_dates].total_sales = quantity;
          unique_dates++;
        }
      }
    }
  }

  fclose(file);
  int total_pizzas = 0;
  for (int i = 0; i < unique_dates; i++) {
    total_pizzas += ventas_por_fecha[i].total_sales;
  }

  float total_dias = unique_dates;
  float prom_dia = 0;

  if (total_dias > 0) {
    prom_dia = (float)total_pizzas / total_dias;
  }

  char *result = malloc(max_linea * sizeof(char));
  snprintf(result, max_linea, "Promedio de pizzas por día: %.2f", prom_dia);

  return result;
}


char *ims(const char *filename) {
  FILE *file = fopen(filename, "r");

  typedef struct {
    char ingredient[max_nombre];
    int count;
  } Ingrediente;

  Ingrediente ingredientes[max_cant];
  int num_ingr = 0;
  char line[max_linea];
  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file)) {
    trimString(line);
    if (line[0] != '\0') {
      char *token = strtok(line, ",");
      int token_index = 0;
      char *last_token = NULL;

      while (token != NULL) {
        if (token_index == 11) {
          char s_ingre[max_linea];
          strncpy(s_ingre, token, max_linea);
          char *ingre_token = strtok(s_ingre, ",");
          while (ingre_token != NULL) {
            if (ingre_token[0] == '"' &&
                ingre_token[strlen(ingre_token) - 1] == '"') {
              memmove(ingre_token, ingre_token + 1, strlen(ingre_token) - 2);
              ingre_token[strlen(ingre_token) - 2] = '\0';
            }
            for (int i = 0; ingre_token[i]; i++) {
              ingre_token[i] = tolower(ingre_token[i]);
            }
            int found = 0;
            for (int i = 0; i < num_ingr; i++) {
              if (strcmp(ingredientes[i].ingredient, ingre_token) == 0) {
                ingredientes[i].count++;
                found = 1;
                break;
              }
            }
            if (!found) {
              strncpy(ingredientes[num_ingr].ingredient, ingre_token,
                      max_nombre);
              ingredientes[num_ingr].count = 1;
              num_ingr++;
            }
            ingre_token = strtok(NULL, ",");
          }
        }
        token = strtok(NULL, ",");
        token_index++;
      }
    }
  }

  fclose(file);
  char ingre_mas_v[max_nombre];
  int max_count = -1;
  for (int i = 0; i < num_ingr; i++) {
    if (ingredientes[i].count > max_count) {
      max_count = ingredientes[i].count;
      strncpy(ingre_mas_v, ingredientes[i].ingredient, max_nombre);
    }
  }
  char *result = malloc(max_linea * sizeof(char));
  snprintf(result, max_linea,
           "Ingrediente más vendido: %s - Cantidad vendida: %d", ingre_mas_v,
           max_count);

  return result;
}

char *hp(const char *filename) {
  FILE *file = fopen(filename, "r");

  typedef struct {
    char category[max_nombre];
    int count;
  } CategoriaPizza;

  CategoriaPizza categorias[max_cant];
  int num_categorias = 0;

  char line[max_linea];
  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file)) {
    trimString(line);
    if (line[0] != '\0') {
      char *token = strtok(line, ",");
      int token_index = 0;
      char *last_token = NULL;
      char category[max_nombre];

      while (token != NULL) {
        if (token_index == 9) {
          strncpy(category, token, max_nombre);
        }
        last_token = token;
        token = strtok(NULL, ",");
        token_index++;
      }

      int found = 0;
      for (int i = 0; i < num_categorias; i++) {
        if (strcmp(categorias[i].category, category) == 0) {
          categorias[i].count++;
          found = 1;
          break;
        }
      }

      if (!found) {
        strncpy(categorias[num_categorias].category, category, max_nombre);
        categorias[num_categorias].count = 1;
        num_categorias++;
      }
    }
  }

  fclose(file);

  char *result = malloc(max_linea * num_categorias * sizeof(char));
  result[0] = '\0';
  for (int i = 0; i < num_categorias; i++) {
    char temp[max_linea];
    snprintf(temp, sizeof(temp),
             "Categoría: %s - Cantidad de pizzas vendidas: %d\n",
             categorias[i].category, categorias[i].count);
    strcat(result, temp);
  }

  return result;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Uso: %s <archivo.csv> <métrica1> [<métrica2> ...]\n",
            argv[0]);
    return 1;
  }

  char *archivo = argv[1];

  for (int i = 2; i < argc; i++) {
    char *metrica = argv[i];
    char *resultado = NULL;

    if (strcmp(metrica, "pms") == 0) {
      resultado = pms(archivo);
    } else if (strcmp(metrica, "pls") == 0) {
      resultado = pls(archivo);
    } else if (strcmp(metrica, "dms") == 0) {
      resultado = dms(archivo);
    } else if (strcmp(metrica, "dls") == 0) {
      resultado = dls(archivo);
    } else if (strcmp(metrica, "dmsp") == 0) {
      resultado = dmsp(archivo);
    } else if (strcmp(metrica, "dlsp") == 0) {
      resultado = dlsp(archivo);
    } else if (strcmp(metrica, "apo") == 0) {
      resultado = apo(archivo);
    } else if (strcmp(metrica, "apd") == 0) {
      resultado = apd(archivo);
    } else if (strcmp(metrica, "ims") == 0) {
      resultado = ims(archivo);
    } else if (strcmp(metrica, "hp") == 0) {
      resultado = hp(archivo);
    }
    if (resultado != NULL) {
      printf("%s\n", resultado);
      free(resultado);
    }
  }

  return 0;
}