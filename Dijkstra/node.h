#ifndef NODE_HEADER
#define NODE_HEADER

#include "define.h"
#include "nodeset.h"
#include "record.h"

class route_t;
class LSDB;
class NodeSet;

class node_t
{
	void calc(NodeSet*, LSDB*);
public:
	char name[NAME_LEN];
	route_t	*routelist, *last;

	node_t();
	~node_t();
	
	void init();
	void release();
	int size();

	void update(NodeSet*, LSDB*);

	void addRecord(node_t*, node_t*, int _min = MAX_DIST);
	void removeRecord(node_t* );
	route_t* findRecord(node_t*);
	void updateRecord(node_t* _dest, node_t* _prev,unsigned int _minlen);

	unsigned int getDist(node_t* _dest);
	void showRouteTable();
	void show();
};

#endif // NODE_HEADER
