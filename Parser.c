#include <stdio.h>
#include <string.h>

#define NRO_TOKENS 12
#define NRO_ESTADOS 5
char * CENTINELA = "#";

typedef unsigned int estado;
// typedef char char;

char indice[] = {'0','1','2','3','4','5','6','7','8','9','.','F'};
const estado estados[] = {0,1,3,4,2};
estado estadoActual = 0;
char palabrasReconocidas[100][3];
int cantPalabras = 0;
const estado tablaDeTransiciones[NRO_ESTADOS][NRO_TOKENS] = {
    {1,1,1,1,1,1,1,1,1,1,4,4},
    {4,4,4,4,4,4,4,4,4,4,3,2},
    {2,2,4,4,4,4,4,4,4,4,4,4},
    {4,4,4,4,4,4,4,4,4,4,4,4},
    {4,4,4,4,4,4,4,4,4,4,4,4}
};

//Prototipos:
void imprimirTabla(void);
void imprimirIndices(void);
char * ingresarCadena(void);
void procesar(char *);
estado proximoEstado(char);
int encontrarColumna(char);

void main(void){
    char * cadenaDeEntrada;
    char * parteCadena;
    imprimirTabla();
    cadenaDeEntrada = ingresarCadena();
    parteCadena = strtok(cadenaDeEntrada, CENTINELA);
    while (parteCadena != NULL) { 
        procesar(parteCadena); 
        parteCadena = strtok(NULL, CENTINELA); 
    } 

    printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    for(int i = 0; i < cantPalabras; i++ )
        printf("\n%d) %s",i,palabrasReconocidas[i]);
}

estado proximoEstado(char token){
    printf("\n:proximoEstado:");
    int nroColumna = encontrarColumna(token);
    return tablaDeTransiciones[estadoActual][nroColumna];
}

int encontrarColumna(char token){
    printf("\n:encontrarColumna:");

    int i = 0;
    while ( indice[i] != token ){
        i++;
    }
    return i;
}

void procesar(char * potencialPalabra){
    printf("\n:procesar:");
    for(int i = 0; i < strlen(potencialPalabra); i++){
        estadoActual = proximoEstado(potencialPalabra[i]);
    }
    switch (estadoActual){
        case 0:
        case 1:
        case 3:    
        case 4:
            return;

        case 2:
            cantPalabras++;
            strcpy(palabrasReconocidas[cantPalabras],potencialPalabra);
            return;

    }
}

char * ingresarCadena(void){
    static char cadena[100];
    printf("\nIngrese una cadena de caracteres: ");
    scanf("%s",cadena);
    return cadena;
}

void imprimirTabla(void){
    imprimirIndices();
    for(int i = 0; i < NRO_ESTADOS; i++){
        printf("\n%d\t|\t",estados[i]);
        for(int j = 0; j < NRO_TOKENS; j++)
            printf("%d\t", tablaDeTransiciones[i][j]);
    }
}

void imprimirIndices(void){
    printf("\t|\t");
    for(int i=0; i<NRO_TOKENS; i++)
        printf("%c\t",indice[i]);
    printf("\n___________________________________________________________________________________________________________");
}

