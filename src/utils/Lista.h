/**
@file Lista.h
List Utility
*/

typedef struct LL {
    int size;
    int last;
    char *lista;
} *LISTA;

typedef struct Par{
    int fst;
    int snd;
} Pares, *endPar;

/**
 * Creates an empty List
 * @param[out] list
*/
LISTA listaVazia();

/**
 * Adds and element to a list
 * @param[in] list
 * @param[in] elem
*/
void addToLista(LISTA l, char elem);

/**
 * Changes the size of a List
 * @param[in] list
 * @param[in] size
*/
void setSize(LISTA l, int size);