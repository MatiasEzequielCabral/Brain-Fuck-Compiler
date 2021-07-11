#include "strutil.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#define MEM_FIN_CADENA 1
#define TAM_INICIAL 5
#define MEM_SEPARADOR 1

/*
 * Devuelve una nueva cadena con los primeros ‘n’ caracteres de la cadena
 * ‘str’. La liberación de la memoria dinámica devuelta queda a cargo de
 * quien llame a esta función.
 *
 * Devuelve NULL si no se pudo reservar suficiente memoria.
 */
char *substr(const char *str, size_t n){

	size_t largo = strlen(str);

	if(largo < n)
		n = largo;

	if(largo == 0)
		n = 0;

	char* sub_cadena = malloc((n + MEM_FIN_CADENA) * sizeof(char));

	if(sub_cadena == NULL)
        return NULL;

    if(largo == 0){

		sub_cadena[n] = '\0';
		return sub_cadena;
    }

	else{

		for(size_t i = 0 ; i < n; i++){

			sub_cadena[i] = str[i];
		}
	}
	
	sub_cadena[n] = '\0';
	return sub_cadena;
}
/*
 * Devuelve en un arreglo dinámico terminado en NULL todos los subsegmentos de
 * ‘str’ separados por el carácter ‘sep’. Tanto el arreglo devuelto como las
 * cadenas que contiene se ubicarán en nuevos espacios de memoria dinámica.
 *
 * La liberación de la memoria dinámica devuelta queda a cargo de quien llame a
 * esta función. La función devuelve NULL en caso de error.
 */
char **split(const char *str, char sep){

	int cant_en_vector = 2;
	size_t pos_en_cadena = 0;
	size_t pos_en_vector = 0;

	for(size_t j = 0; str[j] != '\0'; j++){

		if(str[j] == sep){
			cant_en_vector++;
		}
	}
	char** vector_spliteado = malloc(cant_en_vector * sizeof(char*));
	size_t i = 0;

	while(str[i] != '\0'){

		if(str[i] == sep){

			vector_spliteado[pos_en_vector] = substr(str + pos_en_cadena, i-pos_en_cadena);
			pos_en_cadena = i+1;
			pos_en_vector++;
		}

		if(str[i+1] == '\0'){
			vector_spliteado[pos_en_vector] = substr(str + pos_en_cadena, i+1);
			pos_en_vector++;
		}
		i++;
	}

	if(i == 0){//si la cadena esta vacia
		vector_spliteado[pos_en_vector] = substr(str, i);
		pos_en_vector++;
	}

	vector_spliteado[pos_en_vector] = NULL;
    return vector_spliteado;
}

/*
 * Devuelve la cadena resultante de unir todas las cadenas del arreglo
 * terminado en NULL ‘str’ con ‘sep’ entre cadenas. La cadena devuelta se
 * ubicará en un nuevo espacio de memoria dinámica.
 *
 * La liberación de la memoria dinámica devuelta queda a cargo de quien llame a
 * esta función. La función devuelve NULL en caso de error.
 */

char* join(char** strv, char sep){

	size_t largo = 1;

	for(size_t j = 0; strv[j] != NULL; j++){

		if(strv[j+1] == NULL){
			largo += strlen(strv[j]);
			break;
		}

		largo += strlen(strv[j])+1;
	}

	size_t i = 0;
	char* cadena_completa = malloc(largo * sizeof(char));
	size_t k;
	size_t l = 0;

	while(strv[i] != NULL){

		for(k = 0; strv[i][k] != '\0'; k++){

			cadena_completa[l] = strv[i][k];
			l++;
		}

		if(strv[i+1] == NULL){
			cadena_completa[l] = '\0';
			return cadena_completa;
		}

		if(sep != '\0'){
			cadena_completa[l] = sep;
			l++;
		}
		i++;
  	}

	if(i == 0)
  		cadena_completa[i] = '\0';
  
	return cadena_completa;
}

/*
 * Libera un arreglo dinámico de cadenas, y todas las cadenas que contiene.
 */
void free_strv(char *strv[]){

	int i = 0;

	while(strv[i] != NULL){
		free(strv[i]);
		i++;
	}

	free(strv);

}