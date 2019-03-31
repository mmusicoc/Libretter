#include <stdio.h>
#include <stdlib.h>

int getBookSize(){
	char aux;
	int bookSize;
	for(;;){
		system("cls");
		printf("\nEste es un programa que genera el orden de impresion de las paginas de un archivo\n");
		printf("para que quede en forma de cuadernillo. Formatos disponibles:\n");
		printf("Cuadernillo A5: 2 pag/cara (Cuartilla) >> 4 pag/hoja\n");
		printf("Cuadernillo A6: 4 pag/cara (Octavilla) >> 8 pag/hoja\n");
		printf("Indique el NUMERO DE PAGINAS que quedan por HOJA: ");
		fflush(stdout);
		scanf("%c", &aux);
		bookSize = aux - '0';
		if (bookSize == 4 || bookSize == 8) return bookSize;
	}
	
}

int getRealPages(){
	int realPages;
	for(;;){
		system("cls");
		printf("\nIndique el numero de paginas CON CONTENIDO que tiene el documento: ");
		fflush(stdout);
		scanf("%d", &realPages);
		if (realPages > 0) return realPages;
	}
}

int getPrintMode(){
	char aux;
	int printMode;
	for(;;){
		system("cls");
		printf("\nDispone de dos modos de impresion:\n");
		printf("1: Copia unica con la mitad en cada parte de la hoja\n");
		printf("2: Doble copia con ambas mitades de la hoja iguales\n");
		printf("Indique el modo deseado: ");
		fflush(stdout);
		scanf("%c", &aux);
		printMode = aux - '0';
		if (printMode == 1 || printMode == 2) return printMode;
	}
}

int start(int *bookSize, int *realPages, int *totalPages){
	int printMode;
	*bookSize = getBookSize();
	if (*bookSize == 8) printMode = getPrintMode();
	else printMode = 1;
	*realPages = getRealPages();
	if (*realPages % (*bookSize / printMode) == 0) {
		*totalPages = *realPages;		
	}
	else {
		*totalPages = (*realPages / (*bookSize / printMode) + 1) * (*bookSize / printMode);
		printf("\nATENCION: Incluya al final del documento 1 hoja en blanco.\n\n");
		system("pause");
	}
	return printMode;
}

void showVector(int* vector, int dimension){
	int i;
	printf("\n");
	for (i = 0; i < dimension; i++) printf("%d\t", vector[i]);
	printf("\n");
}

void copyVector(int* vector2,  int* vector1, int dimension){
	int i;
	for (i = 0;  i < dimension; i++) vector2[i] = vector1[i];
}

void orderPages(int* vector, int totalPages){
	int i, j = 0, k = totalPages - 1, counter = -1;
	int *vector2 = (int*)malloc(totalPages*sizeof(int));
	for (i = 0; i < totalPages; i++){
		if (counter < 0){
			vector2[i] = vector[k];
			counter++;
			if (counter == 0) counter = 2;
			k--;
		}
		else if (counter > 0){
			vector2[i] = vector[j];
			counter--;
			if (counter == 0) counter = -2;
			j++;
		}
	}
	copyVector(vector, vector2, totalPages);	
	free(vector2);
}

void modeA61(int* vector, int totalPages){
	int i, j = 0, k = totalPages / 2, counter = 2;
	int *vector2 = (int*)malloc(totalPages*sizeof(int));
	for (i = 0; i < totalPages; i++){
		if (counter < 0){
			vector2[i] = vector[k];
			counter++;
			if (counter == 0) counter = 2;
			k++;
		}
		else if (counter > 0){
			vector2[i] = vector[j];
			counter--;
			if (counter == 0) counter = -2;
			j++;
		}
	}
	copyVector(vector, vector2, totalPages);	
	free(vector2);
}

void modeA62(int* vector, int totalPages){
	int i;
	for (i = 0; i < totalPages / 2; i++) vector[i + totalPages / 2] = vector[i];
	modeA61(vector, totalPages);
}

void limitRange(int* vector, int realPages, int totalPages){
	int i;
	for (i = 0; i < totalPages; i++) if (vector[i] > realPages) vector[i] = realPages + 1;
}

void exportVector(int* vector, int totalPages){
	FILE* outputFile;
	int i;
	if((outputFile = fopen("Libretto2.txt","w+")) == NULL) printf("\nError al generar el archivo.\n");
	else{
		for (i = 0; i < totalPages; i++){
			fprintf(outputFile, "%d", vector[i]);
			if ((i + 1) % 20 == 0) fprintf(outputFile, "\n");
			else fprintf(outputFile, ",");
		}
		fclose(outputFile);
	}
}

int main(){
	int bookSize, printMode, realPages, totalPages, i; 
	for(;;){
		printMode = start(&bookSize, &realPages, &totalPages);
		int *vector = (int*)malloc(2 * totalPages*sizeof(int));
		for (i=0; i < totalPages; i++) vector[i] = i+1;
		orderPages(vector, totalPages);
		if (bookSize == 4);
		else if (printMode == 1) modeA61(vector, totalPages);
		else {
			totalPages *= 2;
			modeA62(vector, totalPages);
		}
		limitRange(vector, realPages, totalPages);
		exportVector(vector, totalPages);
		free(vector);
	}
	return 0;
}

