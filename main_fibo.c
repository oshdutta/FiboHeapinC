#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "fibo_utils.c"

HEAP * insertnode(HEAP *, NODE *,int);
HEAP * unionHeap(HEAP *,HEAP *);
void main()
{
	HEAP *H;
	NODE * x;int key;
	int flag=0;
	/*make choices - switch case-runs till exit command given*/
	while(1)
	{
		printf("Fibonacci Heap Implementation \n 1.Make Fib Heap \n 2. Insert Node in root list \n 0. to exit");
    	printf("select your choice :");
    	scanf("%d", &choice);

	    switch (choice)
	    {
	    	case 0: 
	    	flag=1;break;

		    case 1:
		    H=makefibheap();

			break;

		    case 2:
		    printf("assign the node key value");
		    scanf("%d", &key);
		    x=assignnode(key);
		    H=insertnode(H,x,key);
		    break;

	    }
	    if(flag==1)
	    	break;
	}
}
HEAP * insertnode(HEAP * H,NODE * x,int k)
{

	if(H.min == NULL)
	{
		H.min=x;
		x.lt=x;
		x.rt=x;
	}
	else 
	{
		x.lt=H.min.lt;
		x.rt=H.min;
		H.min.lt=x;
		if(x.key< H.min)
			H.min=x;
	}
	H.n=H.n+1;
	return H;
}
HEAP * unionHeap(HEAP * H1,HEAP * H2)
{
Hnew=makefibheap();
Hnew.min=H1.min;
/*concat h2 to Hnew*/
Hnew.min.rt.lt=H2.min.lt;
Hnew.min.rt=H2.min;	
	if((H1.min==NULL)||(H2.min!=NULL && H2.min.key<H1.min.key))
		Hnew.min=H2.min;
Hnew.n=H1.n+H2.n;
return Hnew;
}




