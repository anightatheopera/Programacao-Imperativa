#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} *ABin;

// coisas de dar print 
ABin btree_node(int v, ABin l, ABin r){
    ABin ret = malloc(sizeof(ABin));
    *ret = (struct nodo) {
        .valor = v,
        .esq = l,
        .dir = r
    };
    return ret;
}

ABin btree_fromArray(int* arr, size_t len){
    if(len == 0) {
        return NULL;
    } else if(len == 1) {
        return btree_node(arr[0], NULL, NULL);
    } else {
        return btree_node(
            arr[len/2],
            btree_fromArray(arr, len/2),
            btree_fromArray(&arr[len/2+1], len/2-(1-len%2)));
    }
}

void _btree_debug(ABin a, int depth){
    if(a == NULL){
        return;
    }
    _btree_debug(a->dir, depth+1);
    for(int i=0; i<depth; i++){
        printf("    ");
    }
    printf("%d\n", a->valor);
    _btree_debug(a->esq, depth+1);
}

void btree_debug(ABin a){
    _btree_debug(a, 0);
}
//////////////////////

// funçoes auxiliares
void rodaEsquerda (ABin *a){
    ABin b = (*a)->dir;
    (*a)->dir = b->esq;
    b->esq = (*a);
    *a = b;
}

void rodaDireita (ABin *a){
    ABin b = (*a)->esq;
    (*a)->esq = b->dir;
    b->dir = *a;
    *a = b;
}

ABin* findMin(ABin *a){
    if(*a == NULL){
        return NULL;
    }
    ABin* cur = a;
    while((*cur)->esq != NULL){
        cur = &((*cur)->esq);
    }
    return cur;
}
//////////////////////

//alinea d sem rotaçoes
void promoveMenor2(ABin *a){
    // find min
    ABin* min_ptr = a;
    while((*min_ptr)->esq != NULL){
        min_ptr = &(*min_ptr)->esq;
    }
    // save min node
    ABin min = *min_ptr;
    // remove min node from tree (and rewire nodes to the right of min)
    *min_ptr = min->dir;
    // make min node point to previous root
    min->dir = *a;
    // update new root to be min node
    *a = min;
}

//alinea d com rotaçoes
void promoveMenor(ABin *a){
    if(*a == NULL || (*a)->esq == NULL){ 
        return;
    } else if ((*a)->esq->esq == NULL){
        rodaDireita(a);
    } else {
        promoveMenor(&(*a)->esq);
        rodaDireita(a);
    }
}

//alinea e sem rotaçoes
void promoveMaior2(ABin *a){
    // find max
    ABin* max_ptr = a;
    while((*max_ptr)->dir != NULL){
        max_ptr = &(*max_ptr)->dir;
    }
    // save max node
    ABin max = *max_ptr;
    // remove max node from tree (and rewire nodes to the left of max)
    *max_ptr = max->esq;
    // make max node point to previous root
    max->esq = *a;
    // update new root to be max node
    *a = max;
}

//alinea e com rotaçoes
void promoveMaior(ABin *a){
    if(*a == NULL || (*a)->dir == NULL){ 
        return;
    } else if ((*a)->dir->dir == NULL){
        rodaEsquerda(a);
    } else {
        promoveMaior(&(*a)->dir);
        rodaEsquerda(a);
    }
}

void removeMenor(ABin* a){
    promoveMenor(a);
    if(*a == NULL){
        return;
    }
    ABin to_remove = *a;
    *a = (*a)->dir;
    free(to_remove);
}


int main(){
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    ABin a = btree_fromArray(arr, sizeof(arr)/sizeof(arr[0]));
    btree_debug(a);
    printf("-----------------\n");
    removeMenor(&a);
    btree_debug(a);
    printf("-----------------\n");
    return 0;
}