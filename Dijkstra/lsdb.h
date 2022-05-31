#ifndef LSDB_HEADER
#define LSDB_HEADER

class edge_t;
class node_t;
class LSDB
{
	edge_t* add_edge(edge_t*);
public:
	LSDB();
	~LSDB();
public:
	edge_t* root;
	edge_t* last;
public:
	edge_t* find_edge(node_t* _from, node_t* _to);
	edge_t* add_edge(node_t* _from, node_t* _to, int _w = 0);
	
	bool remove_edge(node_t* _from, node_t* _to);
	bool isneighbour(node_t* _from, node_t* _to);
	int size();

	int directDist(node_t* n1, node_t* n2);
	void show();
private:

};

#endif // LSDB_HEADER
