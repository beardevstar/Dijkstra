#include "nodeset.h"
#include "define.h"
#include "edge.h"
#include "lsdb.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern NodeSet ndset;
extern LSDB lsdb;
NodeSet::NodeSet()
{
	cnt = 0;
	node_root = 0;// (node_t**)malloc(sizeof(node_t*));
}

NodeSet::~NodeSet()
{
	
}

node_t* NodeSet::add(char* _name)
{
	if(!cnt) node_root = (node_t**)realloc(node_root, cnt + 1);
	node_t* item = new node_t;
	node_root[cnt] = item;
	memcpy(item->name, _name, strlen(_name) + 1);	
	cnt++;
	return item;
}

node_t* NodeSet::find(char* _name)
{
	for (int i=0;i<cnt;i++)
	{
		node_t* item = node_root[i];
		if (memcmp(item->name, _name, strlen(_name)) == 0) {
			return item;
		}
	}
	return 0;
}

void NodeSet::update(LSDB* _lsdb)
{
	for (int i = 0; i < cnt; i++)
		node_root[i]->update(this, _lsdb);
}

void NodeSet::init()
{
	for (int i = 0; i < cnt; i++)
		node_root[i]->init();
}
void NodeSet::show(){
	for (int i = 0; i < cnt; i++)
		node_root[i]->show();
}
