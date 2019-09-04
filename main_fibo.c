#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "fibo_utils.c"
#include "linked_utils.c"

HEAP * insertnode(HEAP *, NODE *,int);
HEAP * unionHeap(HEAP *,HEAP *);
void main()
{
	HEAP *H;
	H=makefibheap();
	/*make choices - switch case-runs till exit command given*/


}
HEAP * insertnode(HEAP * H,NODE * x,int k)
{
x=assignnode(k);
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
	if((H1.min==NULL)||(H2.min!=NULL && H2.min.key<H1.min.key))
		Hnew.min=H2.min;
Hnew.n=H1.n+H2.n;
return Hnew;
}




