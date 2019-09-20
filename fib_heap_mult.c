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
    bool visited;
    bool mark;
    char c;
    //bool visited;
}NODE;

typedef struct fibanocci_heap
{
    int n;
    NODE *min;
    int phi;
}FIB_HEAP;

/*FIB_HEAP *make_fib_heap();
void insertion(FIB_HEAP *H,NODE *new, int val);
NODE *extract_min(FIB_HEAP *H);
void Consolidate(FIB_HEAP *H);
//void fib_heap_link(FIB_HEAP *H, NODE *y, NODE *x);
void Fibonnaci_link(FIB_HEAP *H, NODE * temp2, NODE * temp1) ;
NODE *find_min_node(FIB_HEAP *H);
void decrease_key(FIB_HEAP *H,NODE *node, int key);
void cut(FIB_HEAP *H, NODE *node_to_be_decreased, NODE * parent_node);
void cascading_cut(FIB_HEAP *H, NODE *parent_node);
//void new_print_Heap(NODE * n);
//delete and union missing*/


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
    new->visited = false; 
    new->parent = NULL; 
    new->child = NULL; 
    new->mark=false;
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
    int no_of_nodes= H->n;
    float cald = (log(no_of_nodes)) / (log(2)); 
    int deg = cald; int tempdeg;
    NODE * arr[deg]; 
    for (int i = 0; i <= deg; i++) 
        arr[i] = NULL; 
    NODE* temp1 = H->min; 
    NODE* temp2; 
    NODE* temp3; 
    NODE* ptr4 = temp1; 
    do { 
        ptr4 = ptr4->right_sibling; 
        tempdeg = temp1->degree; 
        while (arr[tempdeg] != NULL) { 
            temp2 = arr[tempdeg]; 
            if (temp1->key > temp2->key) { 
                temp3 = temp1; 
                temp1 = temp2; 
                temp2 = temp3; 
            } 
            if (temp2 == H->min) 
                H->min = temp1; 
            Fibonnaci_link(H,temp2, temp1); 
            if (temp1->right_sibling == temp1) 
                H->min = temp1; 
            arr[tempdeg] = NULL; 
            tempdeg++; 
        } 
        arr[tempdeg] = temp1; 
        temp1 = temp1->right_sibling; 
    } while (temp1 != H->min); 
    H->min = NULL; 
    for (int j = 0; j <= deg; j++) { 
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
  

void Fibonnaci_link(FIB_HEAP *H, NODE * temp2, NODE * temp1) 
{ 
    (temp2->left_sibling)->right_sibling = temp2->right_sibling; 
    (temp2->right_sibling)->left_sibling = temp2->left_sibling; 
    if (temp1->right_sibling == temp1) 
        H->min = temp1; 
    temp2->left_sibling = temp2; 
    temp2->right_sibling = temp2; 
    temp2->parent = temp1; 
    if (temp1->child == NULL) 
        temp1->child = temp2; 
    temp2->right_sibling = temp1->child; 
    temp2->left_sibling = (temp1->child)->left_sibling; 
    ((temp1->child)->left_sibling)->right_sibling = temp2; 
    (temp1->child)->left_sibling = temp2; 
    if (temp2->key < (temp1->child)->key) 
        temp1->child = temp2; 
    temp1->degree++; 
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

void decrease_key(FIB_HEAP * H,NODE *node_to_be_decrease, int new_key)
{
    NODE *parent_node;
    if(H == NULL)
    {
        printf("\n FIbonacci heap not created ");
        return;
    }
    if(node_to_be_decrease == NULL)
    	{printf("Node is not in the heap");//return 0;
}
    
    else
    {
        if(node_to_be_decrease->key < new_key)
        {
            printf("\n Invalid new key for decrease key operation \n ");
          //  return 0;
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
   // return 1;
}

void *find_node(FIB_HEAP *H,NODE *n, int key,int new_key)
{
	NODE * find_use=n;
	NODE *f=NULL;
    find_use->visited = true;
    if(find_use->key == key)
    {
        find_use->visited = false;
        f=find_use;
        decrease_key(H,f,new_key);
    }
      if(find_use->child!=NULL)
	    {
	        find_node(H,find_use->child, key,new_key);
	    }
	    if((find_use->right_sibling->visited!= true))
	    {
	        find_node(H,find_use->right_sibling, key,new_key);
	    }
	
    find_use->visited = false;
    
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

void Delete_Node(FIB_HEAP * H,int dec_key)
{ 
    NODE* p=NULL;
find_node(H,H->min,dec_key,-5000);
	p=extract_min(H);
if(p!=NULL)
 printf("\n Node deleted");
else
    printf("\n Node not deleted:some error");
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
                
                printf("\n Enter the replacing key ");
                scanf("%d",&k);
                NODE * find_use = (*(heap+h1))->min;
                    find_node(*(heap+h1),find_use, key,k);
                    printf("\n Key decreased- Corresponding heap:\n");
                    new_print_heap((*(heap+h1))->min);
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
                Delete_Node(*(heap+h1),key);
        		printf("\n Node Deleted- Corresponding heap:\n");
                new_print_heap((*(heap+h1))->min);
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
                    printf("\n Updated heap: \n");
                    new_print_heap((*(heap+h1))->min);
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
                printf("\n Find the union of which two heaps? Enter two no.s from 0 to %d ",(h-1));
                scanf("%d",&h1);
                scanf("%d",&h2);
                heap=realloc(heap,(h+1) * sizeof(FIB_HEAP*));
                *(heap+h)=unionHeap(*(heap+h1),*(heap+h2));
                
                printf("Unified Heap:\n");
                new_print_heap((*(heap+h))->min);
                h++;
               }
               break;
            case 8:
                for(int i=0;i<h;i++)
                {
                	printf("Heap %d", i);
                   new_print_heap((*(heap+i))->min);
                }
                break;
        }

        if(flag==1)
        {
            //free(new_node);
            
            break;
        }
    }
}

void new_print_heap(NODE *n)
{
	NODE *x;
for (x= n; ; x = x->right_sibling) 
	{
           
            if( x->child == NULL)
             {
                printf("node with no child (%d) \n", x->key);
            } else {
            	//if(x->parent!=NULL)
            		printf("NODE(%d) with child (%d)\n", x->key, x->child->key);
                new_print_heap(x->child);
            }
            if(x->right_sibling == n) 
            {
                break;
            }
    }
}
