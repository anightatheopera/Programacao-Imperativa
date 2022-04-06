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

//funçoes auxiliares

ABin* encontraMenor(ABin* a){
    if(!(*a)) return NULL;
    ABin* cur = a;
    while((*cur)->esq != NULL){
        cur = &((*cur)->esq);
    }
    return cur;
}

void rodaEsquerda(ABin *a){
    ABin b = (*a)->dir;
    (*a)->dir = b->esq;
    b->esq = (*a);
    *a = b;
}

void rodaDireita(ABin *a){
    ABin b = (*a)->esq;
    (*a)->esq = b->dir;
    b->dir = *a;
    *a = b;
}

int contaNodos(ABin *a){
    if(*a == NULL) return 0;
    if(!((*a)->dir) && !(*a)->esq) return 1;
    return 1 + contaNodos(&(*a)->dir) + contaNodos(&(*a)->esq);
}
//////////////////////

//alinea g
int constroiEspinha(ABin *a){
    while(*a != NULL){
        while((*a)->esq != NULL){
            rodaDireita(a);
        }
        a = &(*a)->dir;
    }
    return 1;
}

//alinea h
ABin equilibraEspinha(ABin *a, int n){
    if(n == 0){
        return *a;
    }
    int p = 0;
    for(p = 0; p < n/2; p++)
        rodaEsquerda(a);
    ABin* left = &(*a)->esq;
    constroiEspinha(left);
    (*a)->esq = equilibraEspinha(left, p);
    (*a)->dir = equilibraEspinha(&(*a)->dir, p);
    return *a;
}

//alinea i
void equilibra(ABin *a){
    int len = contaNodos(a);
    constroiEspinha(a);
    equilibraEspinha(a,len);
}

int main(){
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    ABin a = btree_fromArray(arr, sizeof(arr)/sizeof(arr[0]));
    btree_debug(a);
    printf("-----------------\n");
    //constroiEspinha(&a);
    //equilibraEspinha(&a,15);
    equilibra(&a);
    //rodaEsquerda(&a);
    btree_debug(a);
    printf("-----------------\n");
    return 0;
}