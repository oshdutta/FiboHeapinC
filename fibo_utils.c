typedef struct _heap
{
int n;
struct _node *min; 
/*struct _node *prev; 
struct _node *next; */
int th;
int mh;
int phi; 
} HEAP;

typedef struct _node
{
	int key;
	struct _node *pa;
	struct _node *ch;
	struct _node *lt;
	struct _node *rt;
	int deg;/*no. of children of this node*/
	bool mark;
} NODE;

HEAP * makefibheap()
{
	HEAP *h;
	h= (HEAP *) malloc(sizeof(HEAP));
	h.n=0;
	h.min=NULL;
	h.th=0;
	h.mh=0;
	h.phi=0;
	return h;
}
NODE * assignnode(k)
{
	NODE *x;
	x= (NODE *) malloc(sizeof(NODE));
	x.key=k;
	x.pa=NULL;
	x.ch=NULL;
	x.deg=0;
	x.mark=false;
	return x;
}































