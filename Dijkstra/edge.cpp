#include "edge.h"
#include "node.h"

edge_t::edge_t()
{
}

edge_t::edge_t(node_t* _from, node_t* _to, int _w)
{
	from = _from; to = _to; w = _w; next = 0;
}

edge_t::~edge_t()
{
}