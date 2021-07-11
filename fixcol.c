#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	if(argc != 3){
		fprintf(stderr, "Error: Cantidad erronea de parametros\n");
		return 1;
	}

 	FILE* archivo = fopen(argv[1], "r");

 	if(archivo == NULL){
		fprintf(stderr, "Error: archivo fuente inaccesible\n");
		return 1;
	}

	int largo_cadena = atoi(argv[2]);
	int contador = 0;
	int c;

	while((c = fgetc(archivo)) != EOF){

		if(c == '\n'){
			contador = 0;
			fprintf(stdout, "%c", c);
			continue;
		}

		if(contador == largo_cadena){
			fprintf(stdout, "\n");
			contador = 0;
		}

		fprintf(stdout, "%c", c);
		contador++;
	}

 	fclose(archivo);
	return 0;
}