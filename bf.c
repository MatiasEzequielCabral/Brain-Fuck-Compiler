#include "pila.h"
#include <stdio.h>
#include <stdlib.h>
#define TAM_VEC_CARACTERES 30000
#define TAM_VEC_POSICIONES 240000

typedef struct brainfuck{

	size_t posicion_archivo;
	size_t posicion_arreglo;
	size_t cant_ciclos;
	int caracter;
	bool lectura;
    pila_t* pila_pos_archivo;

}brainfuck_t;

brainfuck_t* crear_interprete(){

	brainfuck_t* bf = malloc(sizeof(brainfuck_t));

	if(bf == NULL)
		return NULL;

	bf->posicion_archivo = 0;
	bf->posicion_arreglo = 0;
	bf->lectura = true;
	bf->cant_ciclos = 0;
	bf->pila_pos_archivo = pila_crear();

	return bf;
}

size_t conv_size_t(void* valor){
    return *((size_t*) valor);
}

void apilar_posiciones(FILE* archivo, brainfuck_t* bf, size_t* arreglo_posiciones, unsigned char* caracter_ASCII){

	if(caracter_ASCII[bf->posicion_arreglo] == 0){

		bf->cant_ciclos++;

		if(bf->lectura)
			bf->lectura = false;
	}

	else{

		arreglo_posiciones[bf->posicion_archivo] = ftell(archivo);
		pila_apilar(bf->pila_pos_archivo, &arreglo_posiciones[bf->posicion_archivo]);
		bf->posicion_archivo++;
	}
}

void ciclar(FILE* archivo, brainfuck_t* bf, unsigned char* caracter_ASCII){

	if(bf->cant_ciclos != 0){

		bf->cant_ciclos--;

		if(bf->cant_ciclos == 0)
			bf->lectura = true;
	}

	else if(caracter_ASCII[bf->posicion_arreglo] == 0){

		pila_desapilar(bf->pila_pos_archivo);
	}

	else{

		fseek(archivo, conv_size_t(pila_ver_tope(bf->pila_pos_archivo)), SEEK_SET);
	}
}

void desifrar_caracter(FILE* archivo, brainfuck_t* bf){

	unsigned char caracter_ASCII[TAM_VEC_CARACTERES] = {0};
	size_t arreglo_posiciones[TAM_VEC_POSICIONES] = {0};

	while((bf->caracter = fgetc(archivo)) != EOF){

		switch(bf->caracter){
	        case '+' :
	        	if(bf->lectura){
	        		caracter_ASCII[bf->posicion_arreglo]++;
	        	}
	        	break;
			case '-' : 
				if(bf->lectura){
	        		caracter_ASCII[bf->posicion_arreglo]--;
	        	}
	       		break;
	        case ',':
	        	if(bf->lectura){
	        		caracter_ASCII[bf->posicion_arreglo] = (unsigned char)getchar();
	        	}
	        	break;
	        case '.' : 
	        	if(bf->lectura){
	        		fprintf(stdout, "%c", caracter_ASCII[bf->posicion_arreglo]);
	        	}
	            break;
	        case '>' : 
	        	if(bf->lectura){
	        		bf->posicion_arreglo++;
	        	}
	            break;
	        case '<' :
	        	if(bf->lectura){
	        		bf->posicion_arreglo--;
	        	}
	            break;
	        case '[':
	        	apilar_posiciones(archivo, bf, arreglo_posiciones, caracter_ASCII);
		        break;
	        case ']':
	        	ciclar(archivo, bf, caracter_ASCII);
		        break;
		}
	}
}

int main(int argc, char* argv[]){

	if(argc != 2){
		fprintf(stderr, "Error: Cantidad erronea de parametros\n");
		return 1;
	}

	FILE* archivo = fopen(argv[1] ,"r");

    if(archivo == NULL){
    	fprintf(stderr, "Error: archivo fuente inaccesible\n");
    	return 1;
    }

    brainfuck_t* bf = crear_interprete();
    desifrar_caracter(archivo, bf);
    pila_destruir(bf->pila_pos_archivo);
    free(bf);
    fclose(archivo);
	return 0;
}