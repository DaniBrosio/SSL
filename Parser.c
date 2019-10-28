#include <stdio.h>
#include <string.h>

#define NRO_TOKENS 12
#define NRO_ESTADOS 6
char * CENTINELA = "#";

typedef unsigned int estado;
// typedef char char;

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

void main(void){
    char * cadenaDeEntrada;
    char * parteCadena;
    imprimirTabla();
    cadenaDeEntrada = ingresarCadena();
    parteCadena = strtok(cadenaDeEntrada, CENTINELA);
    while (parteCadena != NULL) { 
        printf("\nProcesando \"%s\"",parteCadena);
        procesar(parteCadena); 
        parteCadena = strtok(NULL, CENTINELA); 
    }   

    printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
    printf("\n::::::::::::::::::::::::::Palabras::Reconocidas::::::::::::::::::::::::::");
    printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    for(int i = 0; i < cantPalabras; i++ )
        printf("%d) %s\n",i,palabrasReconocidas[i]);
    printf(":::::::::::::::::::::::::::::::Goodbye:::::::::::::::::::::::::::::::::::\n");

}

estado proximoEstado(char token){
    int nroColumna = encontrarColumna(token);
    // printf("\nEstado: %d \t Token[posicion]: %c[%d]", estadoActual,token,nroColumna);        //Util para debuggear
    if(nroColumna >= 0){
        // printf(" --> Nuevo Estado: %d", tablaDeTransiciones[estadoActual][nroColumna]);      //Util para debuggear
        return tablaDeTransiciones[estadoActual][nroColumna];
    }
    return 5;
}

int encontrarColumna(char token){
    for(int i = 0; i < NRO_TOKENS ; i++ ){
        if(diccionario[i] == token) return i;
    }
    return -1;
}

void procesar(char * potencialPalabra){
    for(int i = 0; i < strlen(potencialPalabra); i++){
        estadoActual = proximoEstado(potencialPalabra[i]);
    }
    switch (estadoActual){
        //Estados de rechazo
        case 0:
        case 1:
        case 2:    
        case 5:    
            estadoActual = 0;
            return;
        //Estados de Aceptacion
        case 3:
        case 4:
            estadoActual = 0;
            printf("  -->  Es Palabra!" ,potencialPalabra);
            strcpy(palabrasReconocidas[cantPalabras],potencialPalabra);
            cantPalabras++;
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
    printf("\nTabla de Transiciones:\n");
    imprimirdiccionarios();
    for(int i = 0; i < NRO_ESTADOS; i++){
        printf("\n%d\t|\t",estados[i]);
        for(int j = 0; j < NRO_TOKENS; j++)
            printf("%d\t", tablaDeTransiciones[i][j]);
    }
    printf("\n");

}

void imprimirdiccionarios(void){
    printf("\t|\t");
    for(int i=0; i < NRO_TOKENS; i++)
        printf("%c\t",diccionario[i]);
    printf("\n___________________________________________________________________________________________________________");
}

