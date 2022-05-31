#ifndef EDGE_HEADER
#define EDGE_HEADER

class node_t;
class edge_t
{
public:
	edge_t();
	edge_t(node_t* _from, node_t* _to, int _w);
	~edge_t();
public:
	int w;  /* edge cost */
	node_t *from, *to;
	edge_t* next;
};

#endif // EDGE_HEADER
