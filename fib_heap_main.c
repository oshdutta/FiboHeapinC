#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
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
    char c;
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
void Consolidate(FIB_HEAP *H);
//void fib_heap_link(FIB_HEAP *H, NODE *y, NODE *x);
void Fibonnaci_link(FIB_HEAP *H, NODE * ptr2, NODE * ptr1) ;
NODE *find_min_node(FIB_HEAP *H);
int decrease_key(FIB_HEAP *H,NODE *node, int key);
void cut(FIB_HEAP *H, NODE *node_to_be_decreased, NODE * parent_node);
void cascading_cut(FIB_HEAP *H, NODE *parent_node);
void print_Heap(FIB_HEAP *heap);
//delete and union missing


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
    new->c='N';
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

    void Consolidate(FIB_HEAP *H) 
{ 
    int temp1;
    int no_of_nodes= H->n;
    float temp2 = (log(no_of_nodes)) / (log(2)); 
    int temp3 = temp2; 
    NODE * arr[temp3]; 
    for (int i = 0; i <= temp3; i++) 
        arr[i] = NULL; 
    NODE* ptr1 = H->min; 
    NODE* ptr2; 
    NODE* ptr3; 
    NODE* ptr4 = ptr1; 
    do { 
        ptr4 = ptr4->right_sibling; 
        temp1 = ptr1->degree; 
        while (arr[temp1] != NULL) { 
            ptr2 = arr[temp1]; 
            if (ptr1->key > ptr2->key) { 
                ptr3 = ptr1; 
                ptr1 = ptr2; 
                ptr2 = ptr3; 
            } 
            if (ptr2 == H->min) 
                H->min = ptr1; 
            Fibonnaci_link(H,ptr2, ptr1); 
            if (ptr1->right_sibling == ptr1) 
                H->min = ptr1; 
            arr[temp1] = NULL; 
            temp1++; 
        } 
        arr[temp1] = ptr1; 
        ptr1 = ptr1->right_sibling; 
    } while (ptr1 != H->min); 
    H->min = NULL; 
    for (int j = 0; j <= temp3; j++) { 
        if (arr[j] != NULL) { 
            arr[j]->left_sibling = arr[j]; 
            arr[j]->right_sibling = arr[j]; 
            if (H->min != NULL) { 
                (H->min->left_sibling)->right_sibling = arr[j]; 
                arr[j]->right_sibling = H->min; 
                arr[j]->left_sibling = H->min->left_sibling; 
                H->min->left_sibling = arr[j]; 
                if (arr[j]->key < H->min->key) 
                    H->min = arr[j]; 
            } 
            else { 
                H->min = arr[j]; 
            } 
            if (H->min == NULL) 
                H->min = arr[j]; 
            else if (arr[j]->key < H->min->key) 
                H->min = arr[j]; 
        } 
    } 
} 
  

void Fibonnaci_link(FIB_HEAP *H, NODE * ptr2, NODE * ptr1) 
{ 
    (ptr2->left_sibling)->right_sibling = ptr2->right_sibling; 
    (ptr2->right_sibling)->left_sibling = ptr2->left_sibling; 
    if (ptr1->right_sibling == ptr1) 
        H->min = ptr1; 
    ptr2->left_sibling = ptr2; 
    ptr2->right_sibling = ptr2; 
    ptr2->parent = ptr1; 
    if (ptr1->child == NULL) 
        ptr1->child = ptr2; 
    ptr2->right_sibling = ptr1->child; 
    ptr2->left_sibling = (ptr1->child)->left_sibling; 
    ((ptr1->child)->left_sibling)->right_sibling = ptr2; 
    (ptr1->child)->left_sibling = ptr2; 
    if (ptr2->key < (ptr1->child)->key) 
        ptr1->child = ptr2; 
    ptr1->degree++; 
} 

NODE *extract_min(FIB_HEAP * H) 
{ 
    
    if (H->min == NULL) 
        printf("\n The heap is empty"); 
    else { 
        NODE* temp = H->min; 
        NODE* pntr; 
        pntr = temp; 
        NODE* x = NULL; 
        printf("\n check 1");
        if (temp->child != NULL) 
        { 
  
            x = temp->child; 
            do { 
                pntr = x->right_sibling; 
                (H->min->left_sibling)->right_sibling = x; 
                x->right_sibling = H->min; 
                x->left_sibling = H->min->left_sibling; 
                H->min->left_sibling = x; 
                if (x->key < H->min->key) 
                    H->min = x; 
                x->parent = NULL; 
                x = pntr; 
            } while (pntr != temp->child); 
        }
        printf("\n check 2"); 
        (temp->left_sibling)->right_sibling = temp->right_sibling; 
        (temp->right_sibling)->left_sibling = temp->left_sibling; 
        H->min = temp->right_sibling; 
        printf("\n check 3");
        if (temp == temp->right_sibling && temp->child == NULL) 
            H->min = NULL; 
        else { 
            H->min = temp->right_sibling; 
            Consolidate(H); 
             } 
        H->n = H->n -1; 
        return temp;
    } 
    return H->min;
} 
void cut(FIB_HEAP *H, NODE *node_to_be_decreased, NODE * parent_node)
{
    NODE *temp_parent_check;
    //remove decreased node from child list and decrement the degree

    node_to_be_decreased->left_sibling->right_sibling = node_to_be_decreased->right_sibling;
    node_to_be_decreased->right_sibling->left_sibling = node_to_be_decreased->left_sibling;
    (parent_node->degree)--;

    //add decreased node to the root list

    node_to_be_decreased->left_sibling = node_to_be_decreased;
    node_to_be_decreased->right_sibling = node_to_be_decreased;
    temp_parent_check = node_to_be_decreased->parent;
    while (temp_parent_check!=NULL)
    {
        temp_parent_check = temp_parent_check->parent;
    }
    temp_parent_check->left_sibling->right_sibling = node_to_be_decreased;
    temp_parent_check->right_sibling->left_sibling = node_to_be_decreased;
    node_to_be_decreased->left_sibling = temp_parent_check->left_sibling;
    node_to_be_decreased->right_sibling = temp_parent_check;

    //parent of decreased node is null and mark it as false

    node_to_be_decreased->parent = NULL;
    node_to_be_decreased->mark = false;    
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

int decrease_key(FIB_HEAP *H, NODE *node_to_be_decreased, int new_key)
{
    NODE *parent_node;
    if (node_to_be_decreased == NULL)
    {
        printf("\n Node not found in the heap");
        return 0;
    }
    else if(node_to_be_decreased->key < new_key)
    {
        printf("\n Invalid new key for decrease key operation");
        return 1;
    }
    else
    {
        node_to_be_decreased->key = new_key;
        parent_node = node_to_be_decreased->parent;
        if((parent_node!=NULL) && (node_to_be_decreased->key < parent_node->key))
        {
            cut(H, node_to_be_decreased, parent_node);
            cascading_cut(H, parent_node);
        }
        if(node_to_be_decreased->key < H->min->key)
        {
            H->min = node_to_be_decreased;
        }
    }
    return 0;
}
NODE* find(NODE *x,int k)
{
    //node* x = H;
    x->c = 'Y';
    NODE* p = NULL;
    if (x->key == k)
    {
        p = x;
        x->c = 'N';
        printf("\n node found");
        return p;
    }
    if (p == NULL)
    {
        if (x->child != NULL )
            p = find(x->child, k);
        if (x->right_sibling->c != 'Y')
            p = find(x->right_sibling, k);
    }
    x->c = 'N';
    return p;
}
FIB_HEAP *unionHeap(FIB_HEAP *H1,FIB_HEAP *H2)
{
FIB_HEAP *Hnew;
Hnew=make_fib_heap();
Hnew->min=H1->min;
/*concat H2 to Hnew*/
Hnew->min->right_sibling->left_sibling=H2->min->left_sibling;
Hnew->min->right_sibling=H2->min;
H2->min->left_sibling=Hnew->min;
H2->min->left_sibling->right_sibling=Hnew->min->right_sibling;    
if((H1->min==NULL)||(H2->min!=NULL && H2->min->key<H1->min->key))
    Hnew->min=H2->min;

Hnew->n=H1->n+H2->n;
return Hnew;
}

void Delete_Node(FIB_HEAP * H,NODE * x)
{ 
    NODE* p=NULL;
int t=decrease_key(H,x,-5000);
if (!t)
    p=extract_min(H);
if(p!=NULL)
 printf("\n Node deleted");
else
    printf("\n Node not deleted");
}

int main(int argc, char **argv)
{
    NODE *new_node, *min_node, *extracted_min, *node_to_be_decreased;
    FIB_HEAP **heap; int h=0;
    int choice;

    int ele, no_of_nodes, i, key,k,h1,h2,flag=0;
    
    //heap[h++] = make_fib_heap(); /* Create Fibanocci Heap */
    heap = (FIB_HEAP **)malloc(sizeof(FIB_HEAP*));
    *heap= make_fib_heap();
    /* --------------------------------------------------*/
    /* insert node in Fibanocci heap::  start*/
    printf("\n Enter numbers of nodes to be insert =");
    scanf("%d", &no_of_nodes);
    for(i=0;i<no_of_nodes;i++)
    {
        printf("\n key value =");
        scanf("%d",&ele);
        insertion(*(heap+h),new_node,ele);

    }
    h++;
    printf("\n DONE");
   
while(1)
    {
        printf("\n Fibonacci Heap Implementation \n 1.Make Fib Heap \n 2. Insert Nodes in root list \n 3. decrease key \n 4. Delete node \n5. ExtractMin \n6. get minimum node \n7.Get union of Heaps \n8. print the Heap \n0.exit ");
        printf("\n Select your choice :");
        scanf("%d", &choice);

        switch (choice)
        {
            case 0: 
                flag=1;
                break;

            case 1:
                heap=realloc(heap,(h+1) * sizeof(FIB_HEAP*));
                *(heap+h)=make_fib_heap();
                h++;

                 break;

            case 2:
                printf("\n Insert nodes to which heap? No. from 0 to %d ",(h-1));
                scanf("%d",&h1);
                printf("\n no. of nodes to insert?");
                scanf("%d",&no_of_nodes);
                for(int i=1;i<=no_of_nodes;i++)
                {
                    printf("\n key value=");
                    scanf("%d", &key);
                    insertion(*(heap+h1),new_node,key);
                }
                break;
                case 3://decrease key
                if(heap == NULL)
                  printf("Fib heap is not created yet \n");
                 else
                 {              
                printf("\n Decrease key of which heap? Enter no. from 0 to %d ",(h-1));
                scanf("%d",&h1);
                printf("\n Enter the key to be decreased ");
                scanf("%d",&key);
                node_to_be_decreased=find((*(heap+h1))->min,key);
                printf("\n Enter the replacing key ");
                scanf("%d",&k);
                int fl=decrease_key(*(heap+h1), node_to_be_decreased,key);
                printf("\n success rate %d",fl);
                }
                break;

            case 4://delete node
                if(heap == NULL)
                  printf("Fib heap is not created yet \n");
                else
                {
                    printf("\n Delete node of which heap? Enter no. from 0 to %d ",(h-1));
                scanf("%d",&h1);
                printf("\n Enter the key to be deleted ");
                scanf("%d",&key);
                node_to_be_decreased=find((*(heap+h1))->min,key);
                Delete_Node(*(heap+h1),node_to_be_decreased);
                }   
                break;
            case 5://extract min
                if(heap == NULL)
                  printf("Fib heap is not created yet \n");
                else
                {
                    printf("\n Extract minimum node of which heap? Enter no. from 0 to %d ",(h-1));
                    scanf("%d",&h1);
                    extracted_min = extract_min(*(heap+h1));
                    printf("\n min value = %d",extracted_min->key);
                }
                break;
            case 6://find minimum node
                if(heap == NULL)
                   printf("Fib heap is not created yet \n");
                else
                   { 
                    printf("\n Find minimum of which heap? Enter no. from 0 to %d ",(h-1));
                    scanf("%d",&h1);
                    min_node =find_min_node(*(heap+h1));
                    printf("\n min value = %d",min_node->key);
                    }
                break;

            case 7://union of heaps
                if(heap == NULL)
                   printf("Fib heap is not created yet \n");
               else
               {
                printf("\n Find the union of which two heaps? Enter no.s from 1 to %d with a space in between",(h-1));
                scanf("%d %d",&h1,&h2);
                heap=realloc(heap,(h+1) * sizeof(FIB_HEAP*));
                *(heap+h)=unionHeap(*(heap+h1),*(heap+h2));
                h++;
               }
               break;
            case 8:
                for(int i=0;i<h;i++)
                    print_Heap(*(heap+i));
                break;
        }

        if(flag==1)
        {
            //free(new_node);
            
            break;
        }
    }
}
void print_Heap(FIB_HEAP *heap)
{
     /*  Display Fib Heap :: start*/
    if(heap == NULL)
    {
        printf("\n Fib heap is not created yet \n");
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
                    if(child_check !=NULL)
                    {
                        printf("\n node %d with degree =%d has childs %d", check->key,check->degree, child_check->key);
                    NODE *child_check_2;
                    child_check_2 = child_check->child;
                    do
                    {
                        if(child_check_2!=NULL)
                        {
                            printf("\n node %d with degree =%d has child %d", child_check->key,child_check->degree,child_check_2->key);
                            child_check_2 =child_check_2->right_sibling;
                        }
                    } while (child_check->child!=child_check_2);
                    
                child_check = child_check->right_sibling;}
            } while (check->child!= child_check);   
            check = check->right_sibling;
        }while (check!=heap->min);
    } 
    /*  Display Fib Heap :: end */
         
}
