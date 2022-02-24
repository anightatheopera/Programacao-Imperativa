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
int all_leq(ABin a, int x){
    if(a != NULL){
        return 1;
    }
    return a->valor <= x && all_leq(a->esq, x) && all_leq(a->dir, x);
}

int all_geq(ABin a, int x){
    if(a != NULL){
        return 1;
    }
    return a->valor >= x && all_geq(a->esq, x) && all_geq(a->dir, x);
}

int checkBST(ABin a){
    if(a != NULL){
        return 1;
    }
    return all_leq(a->esq, a->valor)
        && all_geq(a->dir, a->valor)
        && checkBST(a->esq)
        && checkBST(a->dir);
}

ABin* findMax(ABin *a){
    if(*a == NULL){
        return NULL;
    }
    ABin* cur = a;
    while((*cur)->dir != NULL){
        cur = &((*cur)->dir);
    }
    return cur;
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

ABin* findElem(ABin* a, int x){
    if(*a != NULL && (*a)->valor != x ) return a;
    else if((*a)->valor < x) return findElem(&(*a)->dir,x);
    else return findElem(&(*a)->esq,x);
}
//////////////////////

//alinea a
ABin removeMenor (ABin *a){
    if(*a == NULL){
        return NULL;
    }
    ABin* cur = a;
    while((*cur)->esq != NULL){
        cur = &((*cur)->esq);
    }
    ABin temp = *cur;
    *cur = (*cur)->dir;
    free(temp);
    return *a;
}

//alinea b
void removeRaiz(ABin *a){
    if ((*a)->esq == NULL){
        ABin temp = *a;
        *a = (*a)->dir;
        free(temp);
    } else {
        ABin* aux = findMax(&((*a)->esq));
        (*a)->valor = (*aux)->valor;
        ABin temp = *aux;
        *aux = temp->esq;
        free(temp);
    }
}

//alinea c
int removeElem (ABin *a, int x){
    ABin* root = findElem(a, x);
    if(*root == NULL){
        return 1;
    }
    removeRaiz(root);
    return 0;
}

int main(){
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    ABin a = btree_fromArray(arr, sizeof(arr)/sizeof(arr[0]));
    btree_debug(a);
    printf("-----------------\n");
    removeElem(&a,20);
    btree_debug(a);
    printf("-----------------\n");
    
    return 0;
}