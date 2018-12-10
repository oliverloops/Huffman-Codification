/* Codificación de Huffman by Oliver A. López Rodríguez */
/* Proyecto de Aplicación */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

//Longitud Máxima del Árbol de Huffman
#define MAX_LENGHT 350 

//Árbol de nodos de huffman
struct nodoMenor { 
  
    //Caracter de Entrada 
    char data; 
  
    //Frecuencia del caracter 
    unsigned int freq; 
  
    //hijos izquierdo y derecho del nodo
    struct nodoMenor *left, *right; 
}; 
  
//conjunto de elementos de un solo nodo
struct nodeOne { 
  
    // Tamaño actual del cumulo
    unsigned int size; 
  
    // capacidad del cumulo
    unsigned int capacity; 
  
    // Arreglo de los apuntadores del cumulo en el nodo.
    struct nodoMenor** array; 
}; 
  
/* Función para almacenar un nuevo nodo 
de cumulos a partir de caracteres dados
y la frecuencia de cada caracter. */
struct nodoMenor* newNode(char data, unsigned freq) 
{ 
    struct nodoMenor* temp  = (struct nodoMenor*)malloc(sizeof(struct nodoMenor)); 
  
  //Si almacena un valor a la izquierda, devuelve nada a la derecha.
    temp-> left = temp-> right = NULL; 
    temp-> data = data; 
    temp-> freq = freq; 
  
    return temp; 
} 
  
/* Función para crear 
un cumulo dada una capacidad */
struct nodeOne* createMinHeap(unsigned capacity) 
  
{ 
	//Apuntador de estructura para llenar un arreglo de apuntadores
    struct nodeOne* minHeap = (struct nodeOne*)malloc(sizeof(struct nodeOne)); 
  
    // El tamaño actual es 0 
    minHeap-> size = 0; 
  
    minHeap-> capacity = capacity; 
  
    minHeap-> array = (struct nodoMenor**)malloc(minHeap-> capacity * sizeof(struct nodoMenor*)); 
    return minHeap; 
} 
  
/* Una función para cambiar 2 nodos del cumulo */
void swapMinHeapNode(struct nodoMenor** a, struct nodoMenor** b) 
{ 
    struct nodoMenor* t = *a; 
    *a = *b; 
    *b = t; 
} 
  
/* Función estándar que recibe las frecuencias y el tamaño
de los cumulos */
void minHeapify(struct nodeOne* minHeap, int val) 
  
{ 
	int smallest = val; 
    int left = 2 * val + 1; 
    int right = 2 * val + 2; 
  
    if (left < minHeap->size && minHeap->array[left]-> freq < minHeap->array[smallest]->freq) 
        smallest = left; 
  
    if (right < minHeap->size && minHeap->array[right]-> freq < minHeap->array[smallest]->freq) 
        smallest = right; 
  
    if (smallest != val) { 
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[val]); 
		minHeapify(minHeap, smallest); 
    } 
} 
  
/*
Una función para revisar si el tamaño 
de cumulo es 1 o no*/
int isSizeOne(struct nodeOne* minHeap) 
{ 
  
    return (minHeap->size == 1); 
} 
  
/* Una función estándar para extraer el valor
mínimo del nodo a partir del cumulo */
struct nodoMenor* extractMin(struct nodeOne* minHeap)  
{ 
  
    struct nodoMenor* temp = minHeap->array[0]; 
    minHeap->array[0] = minHeap->array[minHeap->size - 1]; 
    --minHeap->size; 
    minHeapify(minHeap, 0); 
  
    return temp; 
} 
  
/*Una función para insertar un nuevo
nodo en el cumulo */
void insertMinHeap(struct nodeOne* minHeap, struct  nodoMenor* minHeapNode)  
{ 
    ++minHeap->size; 
    int i = minHeap->size - 1; 
  
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 
  
        minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
        i = (i - 1) / 2; 
    } 
  
    minHeap->array[i] = minHeapNode; 
} 
  
//Una función standar para construir un nodo
void buildMinHeap(struct nodeOne* minHeap) 
{ 
    int n = minHeap->size - 1; 
    int i; 
  
    for (i = (n - 1) / 2; i >= 0; --i) 
        minHeapify(minHeap, i); 
} 
  
//Función para imprimir un arreglo de tamaño n
void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        printf("%d", arr[i]); 
  
    printf("\n"); 
} 
  
//Función para revisar si un nodo es ya una hoja
int isLeaf(struct nodoMenor* root)  
{ 
    return !(root->left) && !(root->right); 
} 
  
/*
crea un cumulo de capacidad igual al tamaño
de insersión de todos los caracteres de data[]
en el cumulo. Al principio el tamaño (size) del cumulo
es igual a la variable capacity. */
struct nodeOne* createAndBuildMinHeap(char data[], int freq[], int size) 
{ 
    struct nodeOne* minHeap = createMinHeap(size); 
  
    for (int i = 0; i < size; ++i) 
        minHeap->array[i] = newNode(data[i], freq[i]); 
  
    minHeap->size = size; 
    buildMinHeap(minHeap); 
  
    return minHeap; 
} 
  
// Función principal que contruye el árbol de huffman 
struct nodoMenor* buildHuffmanTree(char data[], int freq[], int size) 
  
{ 
    struct nodoMenor *left, *right, *top; 
  
    /*Paso 1: Crea un cumulo de capacidad igual a "size",
	inicialmente hay node igual a "size"*/
    struct nodeOne* minHeap = createAndBuildMinHeap(data, freq, size); 
  
    // Se itera mientras el tamaño del cumulo no sea 1 
    while (!isSizeOne(minHeap)) { 
  
        /* Paso 2: Se extrae las frecuncias
        más pequeñas del cumulo */
        left = extractMin(minHeap); 
        right = extractMin(minHeap); 
  
        /* Paso 3: Se crea un nuevo nodo interno
        con frecuencia igual a la suma de los
        2 nodos de frecuencias, los 2 nodos se hacen
        que se extraegan hijos izquierdo y derecho
		de este nuevo nodo. Se añade este nodo al cumulo
		El simbolo $ estaba en documentación*/
        top = newNode('$', left->freq + right->freq); 
  
        top->left = left; 
        top->right = right; 
  
        insertMinHeap(minHeap, top); 
    } 
  
    /* Paso 4: Lo restante del nodo
    es la raíz del nodo y el arbol esta completo. */
    return extractMin(minHeap); 
} 
  
// Imprime la codificación desde la raíz del árbol de Huffman
void printCodes(struct nodoMenor* root, int arr[], int top) 
{ 
    // Asigna 0 a un brazo (izquierdo)
    if (root->left) { 
  
        arr[top] = 0; 
        printCodes(root->left, arr, top + 1); 
    } 
  
    // Asigna 1 a un brazo (derecho)
    if (root->right) { 
  
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1); 
    } 
  
    /*Si esto es la hoja del nodo, entonces
    contine una de las entradas de 
	caracteres,Imprime el caracter
    y su codificación desde:  arr[] */
    if (isLeaf(root)) { 
  
        printf("El caracter %c ahora es -> ", root->data); 
        printArr(arr, top); 
    } 
} 
  
/* Función principal que construye el Árbol de huffman
e imprime las codificaciones */
void HuffmanCodes(char data[], int freq[], int size) 
  
{ 
    //Contruye el Árbol de Huffman
    struct nodoMenor* root = buildHuffmanTree(data, freq, size); 
  
    /*Imprime las codificaciones usando 
    el árbol construido anteriormente */
    int arr[MAX_LENGHT];
	int top = 0; 
  
    printCodes(root, arr, top); 
} 

int main() 
{ 
	//Llamada la archivo de texto
    FILE *ptr_file = fopen("./tale.txt","r");
    int i,j, total = 0;
    char *diff = malloc(sizeof(char) * 100), *text = malloc(sizeof(char) * 100);

	//Lectura y almacenamiento de caracteres
     for(i = 0; i < 22; i++){
        fscanf(ptr_file, "%c", &diff[i]);
    }

	//Transformación a minisculas
	for(int u = 0; u < 22; u++){
		text[u] = tolower(diff[u]);
	}

    int count = strlen(text);
    char *abc = (char *)malloc(sizeof(char) * 25);

    //Generador del alfabeto
    int a, p = 0;
    for(a = 97; a <= 122; a++){
        abc[p] = (char)a;
        p++;
    }

	char *new_data = malloc(sizeof(char) * 25);
    int *freq = malloc(sizeof(int) * 25), beta = 0; i = 0;

	/*Recorrido para comparar caracteres
	y obtener las frecuencias de cada uno*/
    for(i = 0; i <= 25; i++){
        for(j = 0; j < count; j++){
            if(abc[i] == text[j]){
                total += 1;
			}
     	}
		 //almacenamiento de los caracteres que se repiten
        if(total != 0){
			freq[i] = total;
			new_data[beta] = abc[i];
			printf("| %c | frecuencia: %d ",new_data[beta],freq[i]);
			beta++;
		}
		total = 0;
    }

	printf("\n\n\n");

	//Invocación a la función que contruye el arbol de nodos.
	HuffmanCodes(new_data, freq, beta); 

    free(text);
    free(abc);
    free(freq);
	free(new_data);
    fclose(ptr_file);

    printf("\n");

	return 0; 
} 