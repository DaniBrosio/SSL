#include <stdio.h>
#include <string.h>

#define NRO_TOKENS 12
#define NRO_ESTADOS 6
char * CENTINELA = "#";

typedef unsigned int estado;

char diccionario[] = {'0','1','2','3','4','5','6','7','8','9','.','F'};
const estado estados[] = {0,1,2,3,4,5};  // 0: Inicial, 3 y 4: Aceptacion, 5:Estado adicional para completar el AFD (Rechazo)
estado estadoActual = 0;
char palabrasReconocidas[100][5];
int cantPalabras = 0;
const estado tablaDeTransiciones[NRO_ESTADOS][NRO_TOKENS] = {
    {1,1,1,1,1,1,1,1,1,1,5,5},  //0
    {2,2,2,2,2,2,2,2,2,2,3,4},  //1
    {2,2,2,2,2,2,2,2,2,2,5,4},  //2
    {4,4,5,5,5,5,5,5,5,5,5,5},  //3
    {5,5,5,5,5,5,5,5,5,5,5,5},  //4
    {5,5,5,5,5,5,5,5,5,5,5,5}   //5
};

//Prototipos:
void imprimirTabla(void);
void imprimirdiccionarios(void);
char * ingresarCadena(void);
void procesar(char *);
estado proximoEstado(char);
int encontrarColumna(char);
int continuar(void);
void imprimirResultados(void);
void analizar(char *);

void main(void){
    char * cadenaDeEntrada;
    char * parteCadena;
    int continuarFlag = 1;
    imprimirTabla();

    do{
        cadenaDeEntrada = ingresarCadena();
        parteCadena = strtok(cadenaDeEntrada, CENTINELA); //Separar palabras
        while (parteCadena != NULL) { 
            procesar(parteCadena); 
            parteCadena = strtok(NULL, CENTINELA); //Separar palabras
        }   
        imprimirResultados();
        continuarFlag = continuar();
    }while(continuarFlag);
    
    printf(":::::::::::::::::::::::::::::::Goodbye:::::::::::::::::::::::::::::::::::\n");

}

//Funcion principal, analiza si la cadena es palabra
void procesar(char * cadena){
    estadoActual = 0; //Inizializar AFD
    printf("\nProcesando \"%s\"",cadena);

    if(strlen(cadena) == 0) return;
    for(int i = 0; i < strlen(cadena) && estadoActual != 5; i++){  //Mientras no llegue al FDT y no sea un estado de rechazo permanente, repetir. Además se actualiza el carácter a analizar en cada iteracion
        estadoActual = proximoEstado(cadena[i]); //Determinar el nuevo estado actual 
    }
    
    //Si el estado es de aceptacion, la cadena procesada es una palabra reconocida
    switch(estadoActual){
        //Estados de rechazo
        case 0:
        case 1:
        case 2:    
        case 5:    
            return;
        //Estados de Aceptacion
        case 3:
        case 4:
            printf("  -->  Es Palabra!" ,cadena);
            strcpy(palabrasReconocidas[cantPalabras],cadena); //Agrego la palabra a la lista
            cantPalabras++;
            return;
    }
} 

//Implementa el AFD segun la TT
estado proximoEstado(char token){
    int nroColumna = encontrarColumna(token);
    // printf("\nEstado: %d \t Token[posicion]: %c[%d]", estadoActual,token,nroColumna);        //Util para debuggear
    if(nroColumna >= 0){
        // printf(" --> Nuevo Estado: %d", tablaDeTransiciones[estadoActual][nroColumna]);      //Util para debuggear
        return tablaDeTransiciones[estadoActual][nroColumna];
    }
    return 5;
}

//Busca columna de la tabla segun token
int encontrarColumna(char token){
    for(int i = 0; i < NRO_TOKENS ; i++ ){
        if(diccionario[i] == token) return i;
    }
    return -1;
}

char * ingresarCadena(void){
    static char cadena[100];
    printf("\nIngrese una cadena de caracteres: ");
    scanf("%s",cadena);
    return cadena;
}

int continuar(void){
    char res;
    printf("\nContinuar? (S/N): ");
    scanf(" %c",&res);
    if(res == 's' || res == 'S') return 1;
    if(res == 'n' || res == 'N') return 0;

    while( res != 'n' && res != 'N' && res != 's' && res != 'S'){
        printf("\nIngrese S o N: ");
        scanf(" %c",&res);
        if(res == 's' || res == 'S') return 1;
        if(res == 'n' || res == 'N') return 0;
    }
}

void imprimirdiccionarios(void){
    printf("\t|\t");
    for(int i=0; i < NRO_TOKENS; i++)
        printf("%c\t",diccionario[i]);
    printf("\n___________________________________________________________________________________________________________");
}

void imprimirTabla(void){
    printf("\nTabla de Transiciones:\n");
    imprimirdiccionarios();
    for(int i = 0; i < NRO_ESTADOS; i++){
        printf("\n%d\t|\t",estados[i]);
        for(int j = 0; j < NRO_TOKENS; j++)
            printf("%d\t", tablaDeTransiciones[i][j]);
    }
    printf("\n");

}

void imprimirResultados(void){
    printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
    printf("\n::::::::::::::::::::::::::Palabras::Reconocidas::::::::::::::::::::::::::");
    printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    for(int i = 0; i < cantPalabras; i++ )
        printf("%d) %s\n",i,palabrasReconocidas[i]);
}