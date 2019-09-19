#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

typedef struct _NODE //structure of node in the fibonacci heap
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

typedef struct fibanocci_heap //structure of fibonacci heap
{
    int n;
    NODE *min;
    int phi;
    int degree;
}FIB_HEAP;

FIB_HEAP *make_fib_heap(); //create fibonacci heap with default values
void insertion(FIB_HEAP *H,NODE *new, int val); //insert the new node to the fibonacci heap
NODE *extract_min(FIB_HEAP *H); //extract the minimum node from the fibonacci heap and return min node
void consolidate(FIB_HEAP *H); //consolidating fibonacci heap
void fib_heap_link(FIB_HEAP *H, NODE *y, NODE *x); //create link between parent and child
NODE *find_min_node(FIB_HEAP *H); //minimum value will be returned from the fibonacci heap
void decrease_key(FIB_HEAP *H,NODE *node, int key); // decrease the node in the fibonacci heap
void cut(FIB_HEAP *H, NODE *node_to_be_decrease, NODE * parent_node); //cut the decreased node from its parent and add to root list
void cascading_cut(FIB_HEAP *H, NODE *parent_node); //recusive procudure untill it find either root or 

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

NODE *new_print_heap(NODE *x)
{
    x->visited = true;
    if(x->child==NULL && x->parent == NULL)
        printf("rootlist node = %d",x->key);
    printf(" \n Node %d left = %d, right = %d \n", x->key,x->left_sibling->key, x->right_sibling->key);
    if(x->child!=NULL)
    {
        printf("\n  Node %d left = %d, right = %d and child = %d \n", x->key,x->left_sibling->key, x->right_sibling->key, x->child->key);
        x = new_print_heap(x->child);
    }
    else if(x->right_sibling->visited!= true)
    {
        x = new_print_heap(x->right_sibling);
    }
    x->visited = false;
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
    NODE *A[degree], *x, *y, *z;
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
                NODE *exchange_help;
                exchange_help = x;
                x = y;
                y = exchange_help;
            }
            if(y == H->min)
                H->min = x;
            fib_heap_link(H,y,x);
            if(y->right_sibling == x)
                H->min = x;
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
            A[i]->left_sibling = A[i];
            A[i]->right_sibling = A[i];
            if(H->min == NULL)
            {
                H->min = A[i];
            }
            else
            {
                H->min->left_sibling->right_sibling = A[i];
                A[i]->right_sibling = H->min;
                A[i]->left_sibling = H->min->left_sibling;
                H->min->left_sibling = A[i];
                if(A[i]->key < H->min->key)
                {
                    H->min = A[i];
                }
            } 
            if (H->min == NULL)
            {
                H->min = A[i];
            }
            else if(A[i]->key<H->min->key)
            {
                H->min = A[i];
            }            
              
        }
    }
} 

void fib_heap_link(FIB_HEAP *H, NODE *y, NODE *x)
{
    y->right_sibling->left_sibling = y->left_sibling;
    y->left_sibling->right_sibling = y->right_sibling;

    if(x->right_sibling == x)
        H->min = x;

    y->left_sibling = y;
    y->right_sibling = y;
    y->parent = x;

    if(x->child == NULL)
    {
        x->child = y;
    }
    y->right_sibling = x->child; 
    y->left_sibling = x->child->left_sibling; 
    x->child->left_sibling->right_sibling = y; 
    x->child->left_sibling = y;
    if ((y->key) < (x->child->key)) 
        x->child = y; 
    
    (x->degree)++;  
}

NODE *extract_min(FIB_HEAP *H)
{
    NODE *extracted_node;
    if(H->min!=NULL)
    {
        NODE *aux_node, *temp_child;
        aux_node = H->min; 
        NODE *tc_right; 
        tc_right = aux_node; 
        temp_child = NULL; 
        if (aux_node->child != NULL) 
        { 
            temp_child = aux_node->child; 
            do { 
                tc_right = temp_child->right_sibling; 
                (H->min->left_sibling)->right_sibling = temp_child; 
                temp_child->right_sibling = H->min; 
                temp_child->left_sibling = H->min->left_sibling; 
                H->min->left_sibling = temp_child; 
                if (temp_child->key < H->min->key) 
                    H->min = temp_child; 
                temp_child->parent = NULL; 
                temp_child = tc_right; 
            } while(tc_right != aux_node->child); 
        }        
        aux_node->left_sibling->right_sibling = aux_node->right_sibling;
        aux_node->right_sibling->left_sibling = aux_node->left_sibling;
        if(aux_node == aux_node->right_sibling && aux_node->child == NULL)
        {
            H->min = NULL;
        }
        else
        {
            H->min = aux_node->right_sibling;
            consolidate(H);
        }
        (H->n)--; 
        return aux_node;
    }
    else
    {
        printf("\n Fibanocci Heap is empty \n");
        return NULL;
    }
}

void cut(FIB_HEAP *H, NODE *node_to_be_decrease, NODE * parent_node)
{
    NODE *temp_parent_check;

    if(node_to_be_decrease == node_to_be_decrease->right_sibling)
        parent_node->child = NULL;

    //remove decreased node from child list and decrement the degree
    node_to_be_decrease->left_sibling->right_sibling = node_to_be_decrease->right_sibling;
    node_to_be_decrease->right_sibling->left_sibling = node_to_be_decrease->left_sibling;
    if(node_to_be_decrease == parent_node->child)
        parent_node->child = node_to_be_decrease->right_sibling;
    (parent_node->degree)--;

    //add decreased node to the root list
    node_to_be_decrease->left_sibling = node_to_be_decrease;
    node_to_be_decrease->right_sibling = node_to_be_decrease;
    H->min->left_sibling->right_sibling = node_to_be_decrease; 
    node_to_be_decrease->right_sibling = H->min; 
    node_to_be_decrease->left_sibling = H->min->left_sibling; 
    H->min->left_sibling = node_to_be_decrease;

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
    if(H == NULL)
    {
        printf("\n FIbonacci heap not created ");
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
                printf("\n cut called");
                cut(H, node_to_be_decrease, parent_node);
                printf("\n cascading cut called");
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
        find_use->visited = false;
        return find_use;
    }
    else if(find_use->child!=NULL)
    {
        find_use = find_node(find_use->child, key);
    }
    else if(find_use->right_sibling->visited!= true)
    {
        find_use = find_node(find_use->right_sibling, key);
    }
    find_use->visited = false;
    
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
    printf(" \n enter number of nodes to be insert = ");
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
    while(1)
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
                if(heap == NULL)
                    printf("Fibonacci heap is empty");
                else
                {
                    extracted_min = extract_min(heap);
                    printf("\n min value = %d",extracted_min->key);
                }
                break;

        case 6: if(heap == NULL)
                    printf("Fibonacci heap is empty");
                else
                {
                    printf(" node to be decreased = ");
                    scanf("%d", &dec_key);
                    find_use = heap->min;
                    node_to_be_decrease = find_node(find_use, dec_key);
                    if(node_to_be_decrease== NULL)
                        printf("\n node not found ");
                    else
                    {
                        printf("\n=======node found = %d ========", node_to_be_decrease->key);
                        printf(" enter the new key = ");
                        scanf("%d", &new_key);
                        decrease_key(heap, node_to_be_decrease, new_key);
                    }
                }
                break;
        case 7: new_print_heap(heap->min);  /*  Display Fib Heap */
                break;

        case 8: free(new_node);
                free(heap);
                exit(0);

        default: printf("Invalid choice ");
        }
    }
    return 0;
} 