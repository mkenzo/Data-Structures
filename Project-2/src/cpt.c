#include "cpt.h"
#include "lista.h"
#include "libs.h"

typedef struct node {
    Info info;
    double x;
    double y;
    double xc, yc, r;
    struct node* father;
    struct node* left;
    struct node* right;
} node;

typedef struct cpt {
    node* root;
    double epsilon;
} cpt;

CPTree createCPT(double epsilon) {
    cpt* newCPT = malloc(sizeof(cpt));
    newCPT->root = NULL;
    newCPT->epsilon = epsilon;
    return newCPT;
}

bool insertCPT(CPTree b, double x, double y, Info info, VisitaNo vfindo, VisitaNo vfvoltando, void *extra) {
    cpt *tree_aux = (cpt*)b;
    node **aux = &tree_aux->root;

    node *no = (node*)malloc(sizeof(node));
      no->info = info;
      no->left = NULL;
      no->right = NULL;
      no->x = x;
      no->y = y;
    
    if (tree_aux->root == NULL) {
        tree_aux->root = no;
    } else {
        while (*aux) {
            if (x == (*aux)->x) {
                return false;
            } else if (x > (*aux)->x) {
                aux = &(*aux)->right;
            } else if (x < (*aux)->x) {
                aux = &(*aux)->left;
            }
        }
    }
    *aux = no;
    return true;
}

bool searchCPT(CPTree b, double x, double y, Info *info, VisitaNo vfindo, VisitaNo vfvoltando, void *extra) {
    cpt *tree_aux = (cpt*)b;
    node **aux = &tree_aux->root;

    while(*aux) {
        if(((*aux)->x - x < tree_aux->epsilon && (*aux)->y - y < tree_aux->epsilon && x - (*aux)->x <tree_aux->epsilon && y - (*aux)->y < tree_aux->epsilon)|| aux==NULL) {
            info = (*aux)->info;
            return true;
        } else if(x > (*aux)->x) {
            aux = &(*aux)->left;
        } else if(x < (*aux)->x) {
            aux = &(*aux)->right;
        }
    }
    return false;
}

bool removeCPT(CPTree b, double x, double y, Info *info, VisitaNo vfindo, VisitaNo vfvoltando, void *extra) {
    cpt *tree_aux = (cpt*)b;
    node **aux = &tree_aux->root;
    node **father = NULL;
    char side = ' ';

    while(*aux) {
        if(((*aux)->x - x < tree_aux->epsilon && (*aux)->y - y < tree_aux->epsilon && x - (*aux)->x <tree_aux->epsilon && y - (*aux)->y < tree_aux->epsilon)|| aux==NULL) {
            if (father == NULL) {
                if ((*aux)->left == NULL && (*aux)->right == NULL) {
                    tree_aux->root = NULL;
                    info = (*aux)->info;
                    free(aux);
                } else if ((*aux)->left != NULL && (*aux)->right == NULL) {
                    tree_aux->root = (*aux)->left;
                    info = (*aux)->info;
                    free(aux);
                } else if ((*aux)->left == NULL && (*aux)->right != NULL) {
                    tree_aux->root = (*aux)->right;
                    info = (*aux)->info;
                    free(aux);
                } else if ((*aux)->left != NULL && (*aux)->right != NULL) {
                    tree_aux->root = (*aux)->left;
                    (*aux)->left->right = (*aux)->right;
                    info = (*aux)->info;
                    free(aux);
                } 
            } else {
                if ((*aux)->left == NULL && (*aux)->right == NULL) {
                    if (side == 'l') {
                        (*father)->left = NULL;
                    } else if (side == 'r') {
                        (*father)->right = NULL;
                    }
                    info = (*aux)->info;
                    free(aux);
                } else if ((*aux)->left != NULL && (*aux)->right == NULL) {
                    if (side == 'l') {
                        (*father)->left = (*aux)->left;
                    } else if (side == 'r') {
                        (*father)->right = (*aux)->left;
                    }
                    info = (*aux)->info;
                    free(aux);
                } else if ((*aux)->left == NULL && (*aux)->right != NULL) {
                    if (side == 'l') {
                        (*father)->left = (*aux)->right;
                    } else if (side == 'r') {
                        (*father)->right = (*aux)->right;
                    }
                    info = (*aux)->info;
                    free(aux);
                } else if ((*aux)->left != NULL && (*aux)->right != NULL) {
                    if (side == 'l') {
                        (*father)->left = (*aux)->left;
                    } else if (side == 'r') {
                        (*father)->right = (*aux)->left;
                    }
                    (*aux)->left->right = (*aux)->right;
                    info = (*aux)->info;
                    free(aux);
                } 
            }
            return true;
        } else if(x > (*aux)->x) {
            father = aux;
            aux = &(*aux)->left;
            side = 'l';
        } else if(x < (*aux)->x) {
            father = aux;
            aux = &(*aux)->right;
            side = 'r';
        }
    }
    return false;
}

bool SearchFor(node* raiz, double xc, double yc, double r, void* lista, bool found)
{
      if(raiz->x < xc + r && raiz->x > xc - r && raiz->y > yc - r && raiz->y > yc + r)
      {
            insert(lista,raiz->info);
            found = true;
      }
      SearchFor(raiz->left, xc, yc, r, lista, found);
      SearchFor(raiz->right, xc, yc, r, lista, found);
      return found;
}

bool findInRegionCPT(CPTree b, double xc, double yc, double r, Lista lres) {
    cpt *tree = (cpt*)b;
    if(tree == NULL) return false;
    node *aux = tree->root;
    bool res = false;
    SearchFor(aux, xc, yc, r, lres, res);
    return res;
}

void getCircCPT(CPTree b, TreeNode n, double *x, double *y, double *r) {
    cpt *tree = (cpt*)b;
    node *auxNode = tree->root;

    if (auxNode != NULL) {
        *x = auxNode->xc;
        *y = auxNode->yc;
        *r = auxNode->r;
    }
    return;
}

void symmetric_recursive(node* node, VisitaNo fVisita, void* extra)
{
      if (node)
      {
            void* right = node->right;
            symmetric_recursive(node->left, fVisita, extra);
            fVisita(node->x, node->y, node->info, node->xc, node->yc, node->r, extra);
            symmetric_recursive(right, fVisita, extra);
      }
      else return;
}

void percursoSimetrico(CPTree b, VisitaNo vf, void *extra) {
    cpt *tree = (cpt*)b;
    symmetric_recursive(tree->root, vf, extra);
}

Info getInfoCPT(CPTree b, TreeNode n) {
    cpt* tree_aux = (cpt*) b;
    
    if (tree_aux->root != NULL) {
        node* node_aux = n;
        return node_aux->info;
    }
    else return NULL;
}

void dfs_aux(node *no, VisitaNo vf, void *aux){
    if(no ==NULL) {
        return;
    } else {
        vf(no->x,no->y, no->info, no->xc, no->yc, no->r, aux);

        dfs_aux(no->left, vf, aux);
        printf("oi");
        dfs_aux(no->right, vf, aux);
    }
}

void dfs(CPTree b, VisitaNo vf, void *extra) {
    cpt *tree = (cpt*)b;
    node *auxNode = tree->root;
    dfs_aux(auxNode, vf, extra);
}

void bfs_aux(node *node, VisitaNo vf, void *aux) {
    int ind;
        for(ind=0;ind<3;ind++){
            if(ind==0 && node->left!=NULL){
                vf(node->left->x,node->left->y, node->left->info, node->left->xc, node->left->yc, node->left->r, aux);
            }
            if(ind==2 && node->right!=NULL){
                vf(node->right->x, node->right->y, node->right->info, node->right->xc, node->right->yc, node->right->r, aux);
            }
        }
}

void bfs_aux2(node *node, VisitaNo vf,void *aux) {
    if(node->left!=NULL){
        bfs_aux(node->left, vf, aux);
    }
    if(node->right!=NULL){
        bfs_aux(node->right, vf, aux);
    }

    if(node->left!=NULL){
        bfs_aux2(node->left, vf, aux);
    }
    if(node->right!=NULL){
        bfs_aux2(node->right, vf, aux);
    }
}

void bfs(CPTree b, VisitaNo vf, void *extra) {
    cpt *tree= (cpt*)b;
    node *auxNode = tree->root;
  
    vf(auxNode->x, auxNode->y, getInfoCPT(b, auxNode), auxNode->xc, auxNode->yc, auxNode->r, extra);

    bfs_aux(auxNode, vf, extra);
    bfs_aux2(auxNode, vf, extra);
}

/////////////////////////////////////////DESTROY CPTREE/////////////////////////////////////////
void percorreRemoveAUX(node *node, VisitaNo vf, void *aux) {
    if (node == NULL) {
        return;
    } else {
    
    percorreRemoveAUX(node->left,vf,aux);

    percorreRemoveAUX(node->right,vf,aux);

    vf(node->x,node->y, node->info, node->xc, node->yc, node->r, aux);
    }
}

void percorreRemovendo(CPTree b, VisitaNo vf, void *aux) {

  cpt *tree= (cpt*)b;
  node *auxNode = tree->root;
  percorreRemoveAUX(auxNode, vf, aux);

}

void destroyNode(double x, double y, Info i, double cx, double cy, double r, void *aux) {
  free(((node*)i)->info);
  free(i);
}

void destroyCPT(CPTree b) {
    void* aux;
    percorreRemovendo(b, destroyNode, aux);
    free(b);
}