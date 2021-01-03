/**
 * @file c_array.c
 * @brief Estrutura para armazenar os codigos Shannon-Fano
 * @date 2021-1-3
 *
 * @copyright Copyright (c) 2020 - André Vaz, Rui Alves
 */

#include "c_array.h"

void initCode(code_struct *code){
    code->symb = -1;
    initArray(&code->code, 8);
    code->offset = code->index = code->next = 0;
}

void initList(code_list_struct *list){
    list->codes = malloc(sizeof(code_struct));
    list->len = 0;
    list->block_size = 0;
}

void initCodesLists(codes_lists_struct *codes_lists){
    codes_lists->lists = malloc(sizeof(code_list_struct));
    codes_lists->len = 0;
}

void setCode(code_struct *code, D_Array code_arr){
    D_Array copy;
    initArray(&copy, code_arr.size);
    for(int i = 0; i < code_arr.used; i++){
        insertArray(&copy, code_arr.array[i]);
    }
    code->code = copy;
}

void getSymbCode(code_list_struct *code_list, unsigned char symb, int offset, code_struct *out_code){
    for(int i = 0; i < code_list->len; i++){
        if(code_list->codes[i].symb == symb
           && code_list->codes[i].offset == offset){
            *out_code = code_list->codes[i];
        }
    }
}

void setCodeSymb(code_struct *code, unsigned char symb){
    code->symb = symb;
}

void setCodeOffset(code_struct *code, int offset){
    code->offset = offset;
}

void setCodeIndex(code_struct *code, int index){
    code->index = index;
}

void setCodeNext(code_struct *code, int next){
    code->next = next;
}

void insertCodeList(code_list_struct *list, code_struct code){
    list->len++;
    list->codes = realloc(list->codes, (list->len+1)*sizeof(code_struct));
    list->codes[list->len-1] = code;
}

void setListBlockSize(code_list_struct *list, long block_size){
    list->block_size = block_size;
}

void insertCodesLists(codes_lists_struct *codes_lists, code_list_struct code_list){
    codes_lists->len++;
    codes_lists->lists = realloc(codes_lists->lists, (codes_lists->len+1)*sizeof(codes_lists_struct));
    codes_lists->lists[codes_lists->len-1] = code_list;
}

void printCode(code_struct *code){
    printf("symb: %c; code: ", code->symb);
    print_array(&code->code, 0);
    printf("; offset: %d; index: %d; next: %d\n", code->offset, code->index, code->next);
}

void printList(code_list_struct *list){
    for(int i = 0; i < list->len; i++){
        printCode(&list->codes[i]);
    }
}

void printCodesLists(codes_lists_struct *codes_lists){
    for(int i = 0; i < codes_lists->len; i++){
        printf("------------------------ v block: %d (%ld) v ------------------------\n", i, codes_lists->lists[i].block_size);
        printList(&codes_lists->lists[i]);
    }
    printf("--------------------------------------------------------------------\n");
}

void freeCode(code_struct *code){
    code->symb = -1;
    freeArray(&code->code);
    code->offset = code->index = code->next = 0;
}

void freeList(code_list_struct *list){
    for(int i = 0; i < list->len; i++){
        freeCode(&list->codes[i]);
    }
    free(list->codes);
    list->codes = NULL;
    list->len = 0;
    list->block_size = 0;
}

void freeCodesLists(codes_lists_struct *codes_lists){
    for(int i = 0; i < codes_lists->len; i++){
        freeList(&codes_lists->lists[i]);
    }
    free(codes_lists->lists);
    codes_lists->lists = NULL;
    codes_lists->len = 0;
}
