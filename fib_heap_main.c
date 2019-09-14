#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<math.io>

typedef struct _NODE
{
    int key;
    int degree;
    struct _NODE *left_sibling;
    struct _NODE *right_sibling;
    struct _NODE *parent;
    struct _NODE *child;
    bool mark;
}NODE;

typedef struct fibanocci_heap
{
    int n;
    NODE *min;
    int phi;
}FIB_HEAP;

FIB_HEAP *make_fib_heap();
void insertion(FIB_HEAP *H,NODE *new, int val);
NODE *extract_min(FIB_HEAP *H);
void consolidate(FIB_HEAP *H);
void fib_heap_link(FIB_HEAP *H, NODE *y, NODE *x);
NODE *find_min_node(FIB_HEAP *H);
void decrease_key(FIB_HEAP *H,NODE *node, int key);
void cut(FIB_HEAP *H, NODE *node_to_be_decrease, NODE * parent_node);
void cascading_cut(FIB_HEAP *H, NODE *parent_node);
void DeleteNode(HEAP * H, NODE * x)



FIB_HEAP *make_fib_heap()
{
    FIB_HEAP *H;
    H = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
    H->n = 0;
    H->min = NULL;
    H->phi = 0;
    return H;
}

void insertion(FIB_HEAP *H,NODE *new, int val) 
{ 
    new = (NODE*)malloc(sizeof(NODE)); 
    new->key = val;
    new->degree = 0;
    new->mark = false; 
    new->parent = NULL; 
    new->child = NULL; 
    new->left_sibling = new; 
    new->right_sibling = new; 
    if (H->min == NULL)
    { 
        H->min = new; 
    } 
    else    
    { 
        H->min->left_sibling->right_sibling = new; 
        new->right_sibling = H->min; 
        new->left_sibling = H->min->left_sibling; 
        H->min->left_sibling = new; 
        if (new->key < H->min->key)
        {
            H->min = new;
        }          
    }
    (H->n)++; 
}

NODE *find_min_node(FIB_HEAP *H)
{
    return H->min;
}

int cal_degree(int n)
{
    int count = 0;
    while (n>0)
    {
        n=n/2;
        count++;
    }
    return count;
}

void consolidate(FIB_HEAP *H)
{
    int degree,i,d;
    degree = cal_degree(H->n);
    printf("degree = %d",degree);
    NODE *A[degree], *x, *y, *exchange_help;
    for(i=0;i<=degree;i++)
    {
        A[i] = NULL;
    }
    x = H->min;
    do
    {
        d = x->degree;
        while (A[d]!=NULL)
        {
            y = A[d];
            printf("\n\n degree = %d,X =%d Y = %d \n",d, x->key, y->key);
            printf("---------------------");
            if(x->key > y->key)
            {
                exchange_help = x;
                x = y;
                y = exchange_help;
            }
            fib_heap_link(H,y,x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
        x = x->right_sibling;
    } while(x!=H->min);
    H->min = NULL;
    for(i=0;i<degree;i++)
    {
        if(A[i]!= NULL)
        {
            if(H->min == NULL)
            {
                H->min = A[i];
            }
            else
            {
                H->min->left_sibling->right_sibling = A[i];
                A[i]->right_sibling = H->min;
                A[i]->left_sibling = H->min->left_sibling;
                if(A[i]->key < H->min->key)
                {
                    H->min = A[i];
                }
            }   
        }
    }
} 

void fib_heap_link(FIB_HEAP *H, NODE *y, NODE *x)
{
    y->right_sibling->left_sibling = y->left_sibling;
    y->left_sibling->right_sibling = y->right_sibling;

    y->left_sibling = y;
    y->right_sibling = y;
    y->parent = x;

    if(x->child == NULL)
    {
        x->child = y;
    }
    else
    {
        y->right_sibling = x->child; 
        y->left_sibling = x->child->left_sibling; 
        x->child->left_sibling->right_sibling = y; 
        x->child->left_sibling = y;
        if ((y->key) < (x->child->key)) 
            x->child = y; 
    }
    (x->degree)++;  
}

NODE *extract_min(FIB_HEAP *H)
{
    NODE *aux_node,*temp_child, *temp_child_next;
    aux_node = H->min;
    if(aux_node!=NULL)
    {
        if(aux_node->child!=NULL)
        {
            temp_child = aux_node->child;
            do
            {
                temp_child->left_sibling = H->min->left_sibling;
                temp_child->right_sibling = H->min;
                H->min->left_sibling->right_sibling = temp_child;
                temp_child_next = temp_child->right_sibling;
                if(temp_child->key < H->min->key)
                {
                    H->min = temp_child;
                }
                temp_child->parent = NULL;
                temp_child = temp_child->right_sibling;
            } while(temp_child_next!=aux_node->child);
        }
        aux_node->left_sibling->right_sibling = aux_node->right_sibling;
        aux_node->right_sibling->left_sibling = aux_node->left_sibling;
        if(aux_node == aux_node->right_sibling)
        {
            H->min = NULL;
        }
        else
        {
            H->min = aux_node->right_sibling;
            consolidate(H);
        }
        (H->n)--; 
    }
    else
    {
        printf("Fibanocci Heap is empty");
    }
    return aux_node;
}

void cut(FIB_HEAP *H, NODE *node_to_be_decrease, NODE * parent_node)
{
    NODE *temp_parent_check;
    //remove decreased node from child list and decrement the degree

    node_to_be_decrease->left_sibling->right_sibling = node_to_be_decrease->right_sibling;
    node_to_be_decrease->right_sibling->left_sibling = node_to_be_decrease->left_sibling;
    (parent_node->degree)--;

    //add decreased node to the root list

    node_to_be_decrease->left_sibling = node_to_be_decrease;
    node_to_be_decrease->right_sibling = node_to_be_decrease;
    temp_parent_check = node_to_be_decrease->parent;
    while (temp_parent_check!=NULL)
    {
        temp_parent_check = temp_parent_check->parent;
    }
    temp_parent_check->left_sibling->right_sibling = node_to_be_decrease;
    temp_parent_check->right_sibling->left_sibling = node_to_be_decrease;
    node_to_be_decrease->left_sibling = temp_parent_check->left_sibling;
    node_to_be_decrease->right_sibling = temp_parent_check;

    //parent of decreased node is null and mark it as false

    node_to_be_decrease->parent = NULL;
    node_to_be_decrease->mark = false;    
}

void cascading_cut(FIB_HEAP *H, NODE *parent_node)
{
    NODE *aux;
    aux= parent_node->parent;
    if(aux!=NULL)
    {
        if(parent_node->mark == false)
        {
            parent_node->mark= true;
        }
        else
        {
            cut(H,parent_node,aux);
            cascading_cut(H,aux);
        }
    }
}

void decrease_key(FIB_HEAP *H, NODE *node_to_be_decrease, int new_key)
{
    NODE *parent_node;
    if(node_to_be_decrease->key < new_key)
    {
        printf("Invalid new key for decrease key operation");
    }
    else
    {
        node_to_be_decrease->key = new_key;
        parent_node = node_to_be_decrease->parent;
        if((parent_node!=NULL) && (node_to_be_decrease->key < parent_node->key))
        {
            cut(H, node_to_be_decrease, parent_node);
            cascading_cut(H, parent_node);
        }
        if(node_to_be_decrease->key < H->min->key)
        {
            H->min = node_to_be_decrease;
        }
    }
}
void DeleteNode(HEAP * H, NODE * x)
{
decrease_key(H,x,-INFINITY);
extract_min(H);
}

int main(int argc, char **argv)
{
    NODE *new_node, *min_node, *extracted_min, *node_to_be_decrease;
    FIB_HEAP *heap;
    int ele, no_of_nodes, i, key;

    heap = make_fib_heap(); /* Create Fibanocci Heap */

    /* --------------------------------------------------*/
    /* insert node in Fibanocci heap::  start*/
    printf("\n Enter numbers of nodes to be instert =");
    scanf("%d", &no_of_nodes);
    for(i=0;i<no_of_nodes;i++)
    {
        printf("\n key value =");
        scanf("%d",&ele);
        insertion(heap,new_node,ele);
    }
    /* insert node in Fibanocci heap :: end */

    /* --------------------------------------------------*/
    /* finding minimum node in Fibanocci heap :: start */
    min_node =find_min_node(heap);
    printf("\n min value = %d",min_node->key);
    /* finding minimum node in Fibanocci heap :: end */

    /* --------------------------------------------------*/
    /* Extract min in Fibanocci Heap START*/
    extracted_min = extract_min(heap);
    printf("\n min value = %d",extracted_min->key);
    /* Extract min in Fibanocci Heap END*/

    /* --------------------------------------------------*/
    /* Decrease key in Fibanocci Heap START*/

    decrease_key(heap, node_to_be_decrease,key);

    /* Decrease min in Fibanocci Heap END*/
    /* --------------------------------------------------*/
     
     /*  Display Fib Heap :: start*/
    if(heap == NULL)
    {
        printf("Fib heap is not created yet \n");
    }
    else
    {        
        NODE *check;
        check = heap->min;
        do
        {
            printf("\n node - %d ",check->key);
            NODE *child_check;
            child_check = check->child;
            do
            {
                    printf("\n node %d with degree =%d has childs %d", check->key,check->degree, child_check->key);
                    NODE *child_check_2;
                    child_check_2 = child_check->child;
                    do
                    {
                        if(child_check_2!=NULL)
                        {
                            printf("node %d with degree =%d has child %d", child_check->key,child_check->degree,child_check_2->key);
                        }
                        child_check_2 =child_check_2->right_sibling;
                    } while (child_check->child!=child_check_2);
                    
                child_check = child_check->right_sibling;
            } while (check->child!= child_check);            
            check = check->right_sibling;
        }while (check!=heap->min);
    } 
    /*  Display Fib Heap :: end */

    /* --------------------------------------------------*/
    printf("\n New min value = %d", heap->min->key);
    free(new_node);
    free(heap);

    return 0;
}
