//Huffman Codification
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

//Cálculo de la longitud del Árbol de Huffman
#define MAX_TREE_HT 100 

//Árbol de nodos de huffman
struct MinHeapNode { 
  
    //Caracter de Entrada 
    char data; 
  
    //Frecuencia del caracter 
    unsigned freq; 
  
    //hijos izquierdo y derecho del nodo
    struct MinHeapNode *left, *right; 
}; 
  
//conjunto de elementos de un solo nodo
struct MinHeap { 
  
    // Tamaño actual del cumulo
    unsigned size; 
  
    // capidad del cumulo
    unsigned capacity; 
  
    // Arreglo de los apuntadores del cumulo en el nodo.
    struct MinHeapNode** array; 
}; 
  
/*A utility function allocate a new 
función para almacenar un nuevo nodo 
de un cumulo a partir de caracteres dados
y la frecuencia de cada caracter. */
struct MinHeapNode* newNode(char data, unsigned freq) 
{ 
    struct MinHeapNode* temp 
        = (struct MinHeapNode*)malloc
(sizeof(struct MinHeapNode)); 
  
    temp->left = temp->right = NULL; 
    temp->data = data; 
    temp->freq = freq; 
  
    return temp; 
} 
  
/* Una utilidad de la función para crear 
un cumulo dada una capacidad */
struct MinHeap* createMinHeap(unsigned capacity) 
  
{ 
  
    struct MinHeap* minHeap 
        = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 
  
    // El tamaño actual es 0 
    minHeap->size = 0; 
  
    minHeap->capacity = capacity; 
  
    minHeap->array 
        = (struct MinHeapNode**)malloc(minHeap-> 
capacity * sizeof(struct MinHeapNode*)); 
    return minHeap; 
} 
  
/* A utility function to 
Una función para cambiar 2 nodos del cumulo */
void swapMinHeapNode(struct MinHeapNode** a, 
                     struct MinHeapNode** b) 
  
{ 
  
    struct MinHeapNode* t = *a; 
    *a = *b; 
    *b = t; 
} 
  
/* Función standar que recibe las frecuencias y el tamaño
de los cumulos */
void minHeapify(struct MinHeap* minHeap, int idx) 
  
{ 
	int smallest = idx; 
    int left = 2 * idx + 1; 
    int right = 2 * idx + 2; 
  
    if (left < minHeap->size && minHeap->array[left]-> 
freq < minHeap->array[smallest]->freq) 
        smallest = left; 
  
    if (right < minHeap->size && minHeap->array[right]-> 
freq < minHeap->array[smallest]->freq) 
        smallest = right; 
  
    if (smallest != idx) { 
        swapMinHeapNode(&minHeap->array[smallest], 
                        &minHeap->array[idx]); 
        minHeapify(minHeap, smallest); 
    } 
} 
  
/*
Una función para revisar si el tamaño 
de cumulo es 1 o no*/
int isSizeOne(struct MinHeap* minHeap) 
{ 
  
    return (minHeap->size == 1); 
} 
  
/* Una función standar para extraer el valor
mínimo del nodo a partir del cumulo */
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
  
{ 
  
    struct MinHeapNode* temp = minHeap->array[0]; 
    minHeap->array[0] 
        = minHeap->array[minHeap->size - 1]; 
  
    --minHeap->size; 
    minHeapify(minHeap, 0); 
  
    return temp; 
} 
  
/*Una función para insertar un nuevo
nodo en el cumulo */
void insertMinHeap(struct MinHeap* minHeap, 
                   struct MinHeapNode* minHeapNode) 
  
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
void buildMinHeap(struct MinHeap* minHeap) 
  
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
int isLeaf(struct MinHeapNode* root) 
  
{ 
  
    return !(root->left) && !(root->right); 
} 
  
/* Creates a min heap of capacity 
crea un cumulo de capacidad igual al tamaño
// equal to size and inserts all character of 
de insersión de todos los caracteres de data[]
en el cumulo. Al principio el tamaño (size) del cumulo
es igual a la variable capacity. */
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 
  
{ 
  
    struct MinHeap* minHeap = createMinHeap(size); 
  
    for (int i = 0; i < size; ++i) 
        minHeap->array[i] = newNode(data[i], freq[i]); 
  
    minHeap->size = size; 
    buildMinHeap(minHeap); 
  
    return minHeap; 
} 
  
// Función principal que contruye el árbol de huffman 
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) 
  
{ 
    struct MinHeapNode *left, *right, *top; 
  
    /*Paso 1: Crea un cumulo de capacidad igual a "size",
	inicialmente hay node igual a "size"*/
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 
  
    // Itera mientras el tamaño del cumulo no sea 1 
    while (!isSizeOne(minHeap)) { 
  
        /* Paso 2: Extrae las frecuncias
        más pequeñas del cumulo */
        left = extractMin(minHeap); 
        right = extractMin(minHeap); 
  
        /* Paso 3: Crea un nuevo nodo interno
        con frecuencia igual a la sumo de los
        2 nodos de frecuencias, Haz los 2 nodos
        que se extraegan hijos izquierdo y derecho
		de este nuevo nodo. Añade este nodo al cumulo
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
void printCodes(struct MinHeapNode* root, int arr[], int top) 
  
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
  
        printf("%c: ", root->data); 
        printArr(arr, top); 
    } 
} 
  
/* The main function that builds a 
Función principal que construye el Árbol de huffman
e imprime las codificaciones */
void HuffmanCodes(char data[], int freq[], int size) 
  
{ 
    //Contruye el Árbol de Huffman
    struct MinHeapNode* root 
        = buildHuffmanTree(data, freq, size); 
  
    /*Imprime las codificaciones usando 
    el árbol construido anteriormente */
    int arr[MAX_TREE_HT];
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
			beta++;
		}
		total = 0;
    }

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