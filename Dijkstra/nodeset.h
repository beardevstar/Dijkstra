#ifndef NODESET_HEADER
#define NODESET_HEADER

#include "node.h"
#include "lsdb.h"

class NodeSet
{
public:
	NodeSet();
	~NodeSet();

	node_t** node_root;
	int cnt;
public:
	node_t* add(char* _name);
	node_t* find(char* _name);

	void update(LSDB* _lsdb);
	void init();
	void show();
};

#endif // NODESET_HEADER
