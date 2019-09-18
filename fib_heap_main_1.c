#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

typedef struct _NODE
{
    int key;
    int degree;
    struct _NODE *left_sibling;
    struct _NODE *right_sibling;
    struct _NODE *parent;
    struct _NODE *child;
    bool mark;
    bool visited;
}NODE;

typedef struct fibanocci_heap
{
    int n;
    NODE *min;
    int phi;
    int degree;
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

FIB_HEAP *make_fib_heap()
{
    FIB_HEAP *H;
    H = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
    H->n = 0;
    H->min = NULL;
    H->phi = 0;
    H->degree = 0;
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
    new->visited = false; 
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
    if(H==NULL)
    {
        printf(" \n Fibonacci heap not yet created \n");
        return NULL;
    }
    else
        return H->min;
}

FIB_HEAP *unionHeap(FIB_HEAP *H1,FIB_HEAP *H2)
{
    FIB_HEAP *Hnew;
    Hnew=make_fib_heap();
    Hnew->min=H1->min;

    /*concat H2 to Hnew*/
    NODE *temp1, *temp2;
    temp1 = Hnew->min->right_sibling;
    temp2 = H2->min->left_sibling;

    Hnew->min->right_sibling->left_sibling = H2->min->left_sibling;
    Hnew->min->right_sibling = H2->min;
    H2->min->left_sibling = Hnew->min;
    temp2->right_sibling = temp1;    
    if((H1->min==NULL)||(H2->min!=NULL && H2->min->key<H1->min->key))
        Hnew->min = H2->min;
    Hnew->n=H1->n+H2->n;
return Hnew;
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
    printf("insert called");
    NODE *parent_node;
    printf("node to dec = %d, new key =%d", node_to_be_decrease->key, new_key);
    if(H == NULL)
    {
        printf("FIbonacci heap not created ");
    }
    else
    {
        if(node_to_be_decrease->key < new_key)
        {
            printf("\n Invalid new key for decrease key operation \n ");
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
    
}

NODE *find_node(NODE *find_use, int key)
{
    find_use->visited = true;
    if(find_use->key == key)
    {
        printf("node found");
        find_use->visited = false;
        return find_use;
    }
    else 
    {
        if(find_use->child!=NULL)
            find_use = find_node(find_use->child, key);
        if(find_use->right_sibling->visited!= true)
            find_use = find_node(find_use->right_sibling, key);
    }
    find_use->visited = false;
}

void print_heap(FIB_HEAP *heap)
{ 
    if(heap == NULL)
    {
        printf("Fibonacci heap is not created yet \n");
    }
    else
    {       
        NODE *root_list, *total_child_check;
        root_list = heap->min;
        do
        {
            printf("\n\n root node= %d with degree = %d", root_list->key, root_list->degree);
            total_child_check = root_list->child;
            while (total_child_check!= NULL)
            {
                NODE *temp1;
                temp1 = total_child_check;
                printf("\n \n child nodes are ");
                do
                {
                    printf(" %d with degree = %d ", temp1->key, temp1->degree);
                    temp1 = temp1->right_sibling;
                } while (temp1!= total_child_check);
                
                total_child_check = total_child_check->child;
            }
            root_list = root_list->right_sibling;
        }while (root_list!=heap->min);    
    } 
}

FIB_HEAP *insertion_procedure()
{
    FIB_HEAP *temp;
    int no_of_nodes, ele, i;
    NODE *new_node;
    temp = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
    temp = NULL;
    if(temp == NULL)
    {
        temp = make_fib_heap();
    }
    printf(" enter number of nodes to be insert = ");
    scanf("%d", &no_of_nodes);
    for(i=1;i<=no_of_nodes;i++)
    {
        printf("\n node %d and its key value = ", i);
        scanf("%d",&ele);
        insertion(temp,new_node,ele);
    }
    return temp;
}

int main(int argc, char **argv)
{
    NODE *new_node, *min_node, *extracted_min, *node_to_be_decrease, *find_use;
    FIB_HEAP *heap, *h1, *h2;
    int operation_no, new_key, dec_key, ele, i, no_of_nodes;
    

    heap = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
    heap = NULL;

    while (1)
    {
        printf(" \n *********** Fibonacci Heap and its Functions *************** / \n ");
        printf(" \n choose below operations \n 1. Create Fibonacci heap \n 2. Insert nodes into fibonacci heap \n 3. Find min \n 4. Union \n 5. Extract min \n 6. Decrease key \n 7. print heap \n 8. exit \n enter operation_no = ");
        scanf("%d", &operation_no);

        switch (operation_no)
        {
        case 1: heap = make_fib_heap(); /* Create Fibanocci Heap */
                break;

        case 2: if(heap == NULL)
                {
                    heap = make_fib_heap();
                }
                printf(" enter number of nodes to be insert = ");
                scanf("%d", &no_of_nodes);
                for(i=1;i<=no_of_nodes;i++)
                {
                    printf("\n node %d and its key value = ", i);
                    scanf("%d",&ele);
                    insertion(heap,new_node,ele);
                }
                break;
        
        case 3: min_node = find_min_node(heap);
                if(min_node == NULL)
                    printf("No minimum value");
                else                
                    printf("\n min value = %d",min_node->key);
                break;

        case 4: if(heap == NULL)
                {
                    printf("\n no FIbonacci heap is created please create fibonacci heap \n ");
                    break;
                }
                h1 = insertion_procedure();
                heap = unionHeap(heap, h1);
                break;

        case 5: /* Extract min in Fibanocci Heap */
                extracted_min = extract_min(heap);
                printf("\n min value = %d",extracted_min->key);
                break;

        case 6: printf(" node to be decreased = ");
                scanf("%d", &dec_key);
                printf("new key = ");
                scanf("%d", &new_key);
                find_use = heap->min;
                node_to_be_decrease = find_node(find_use, dec_key);
                printf("=======node found = %d ========", node_to_be_decrease->key);
                decrease_key(heap, node_to_be_decrease, new_key);
                break;
        
        case 7: print_heap(heap); /*  Display Fib Heap */
                break;

        case 8: free(new_node);
                free(heap);
                exit(0);
        }
    }
    return 0;
} 