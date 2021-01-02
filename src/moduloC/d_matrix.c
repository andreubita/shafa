#include "d_matrix.h"

void initMatrix(D_Matrix *m){
    m->arr = malloc(2*sizeof(D_Array));
    m->len = 0;
}

void addLineMatrix(D_Matrix *m, D_Array arr){
    m->arr = realloc(m->arr, (m->len+2)*sizeof(D_Array));
    D_Array copy;
    initArray(&copy, arr.size);
    for(int i = 0; i < arr.used; i++){
        insertArray(&copy, arr.array[i]);
    }
    copy.used = arr.used;
    copy.size = arr.size;

    m->arr[m->len] = copy;
    m->len++;
}

void clearMatrix(D_Matrix *m){
    m->arr = realloc(m->arr, 1*sizeof(D_Array));
    m->arr = NULL;
    m->len = 0;
}

void printMatrix(D_Matrix *m){
    int n = 0;
    for(int i = 0; i < m->len; i++){
        print_array(&m->arr[i], 0);
        n++;
        if(n == 6){
            n = 0;
            printf("\n");
        }else{
            printf(" ");
        }

    }
    printf("\n");
}

void freeMatrix(D_Matrix *m){
//    for(int i = 0; i < m->len; i++){
//        freeArray(&m->arr[i]);
//    }
    free(m->arr);
    m->arr = NULL;
    m->len = 0;
}

void initMatrixList(D_Matrix_List *m_list){
    m_list->list = malloc(1*sizeof(D_Matrix));
    m_list->len = 0;
}

void insertMatrixInList(D_Matrix_List *m_list, D_Matrix m){
    m_list->list = realloc(m_list->list, (m_list->len+2)*sizeof(D_Matrix));
    m_list->list[m_list->len] = m;
    m_list->len++;

//    D_Matrix copy;
//    initMatrix(&copy);
//    for(int i = 0; i < m.len; i++){
//        addLineMatrix(&copy, m.arr[i]);
//    }
//    copy.len = m.len;


}

void clearMatrixList(D_Matrix_List *m_list){
    m_list->list = realloc(m_list->list, 1*sizeof(D_Matrix));
    m_list->list = NULL;
    m_list->len = 0;
}

void printMatrixList(D_Matrix_List *m_list){
    for(int i = 0; i < m_list->len; i++){
        printf("------------------------- Matrix %d (%d) -------------------------\n\n", i, m_list->list[i].len);
        printMatrix(&m_list->list[i]);
    }
    printf("------------------------------------------------------------\n");
}

void freeMatrixList(D_Matrix_List *m_list){
//    for(int i = 0; i < m_list->len; i++){
//        freeMatrix(&m_list->list[i]);
//    }
    free(m_list->list);
    m_list->list = NULL;
    m_list->len = 0;
}
