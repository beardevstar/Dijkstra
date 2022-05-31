#include "node.h"
#include "lsdb.h"
#include "nodeset.h"

#include <stdlib.h>
#include <stdio.h>

extern NodeSet ndset;
extern LSDB lsdb;

void node_t::calc(NodeSet* _ndset, LSDB* _lsdb)
{

}

node_t::node_t()
{
	routelist = 0;
	last = routelist;
}

node_t::~node_t()
{
	release();
}

void node_t::init()
{
	release();
	addRecord(this, this, 0);
}

void node_t::release()
{
	route_t* temp = routelist, *next = 0;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	routelist = 0; last = 0;
}

int node_t::size()
{
	route_t* temp = routelist;
	int cnt = 0;
	while (temp)
	{
		cnt++;
		temp = temp->next;
	}
	return cnt;
}

void node_t::update(NodeSet* _ndset, LSDB* _lsdb)
{
	init();
	route_t* foc = routelist;
	int prev_size = 0, after_size = 1;

	while (prev_size < after_size)
	{
		prev_size = size();
		while (foc)
		{
			//getting neighbour list
			node_t* focnode = foc->dst;
			for (int i = 0; i < _ndset->cnt; i++) {
				node_t* item = _ndset->node_root[i];
				if (_lsdb->isneighbour(focnode, item)) {//item is neightbor of focnode
					route_t* ori = findRecord(item);
					unsigned int newlen = _lsdb->directDist(item, focnode) + foc->min_len;

					if (!ori) {//null - add
						if(focnode == this) addRecord(item, item, newlen);
						else addRecord(item, focnode, newlen);
					}
					else {//exist - change
						if (newlen < ori->min_len) addRecord(item, focnode, newlen);
					}
				}
			}
			//recalc spset
			foc = foc->next;
		}
		after_size = size();
	}
}

void node_t::addRecord(node_t* _to, node_t* _prev, int _min)
{
	bool isnew = false;
	route_t* _rec = findRecord(_to);

	if (!_rec) {
		isnew = true;
		_rec = new route_t(this, _to, _prev);
	}
	_rec->min_len = _min;
	_rec->prev = _prev;

	if (!routelist) {
		routelist = _rec;
		last = _rec;
		return;
	}
	if (isnew) {
		last->next = _rec;last = _rec;
	}
}

void node_t::removeRecord(node_t* _dst)
{
	route_t* temp = routelist, *prev = routelist;
	while (temp)
	{
		if (temp->src == this && temp->dst == _dst) {
			prev->next = temp->next;
			if (temp == routelist) {
				routelist = 0; last = 0;
			}
			free(temp);
			return;
		}
		prev = temp;
		temp = temp->next;
	}
}

route_t* node_t::findRecord(node_t* _dst)
{
	route_t* temp = routelist;
	while (temp)
	{
		if (temp->src == this && temp->dst == _dst) return temp;
		temp = temp->next;
	}
	return 0;
}

void node_t::updateRecord(node_t* _dst, node_t* _prev, unsigned int _minlen)
{
	route_t* rec = findRecord(_dst);
	if (rec) rec->update(_prev, _minlen);
}

unsigned int node_t::getDist(node_t* _dest)
{
	route_t* rec = findRecord(_dest);
	if (rec) return rec->min_len;
	return MAX_DIST;
}

void node_t::showRouteTable()
{
	route_t* temp = routelist;
	while (temp)
	{
		if(temp->min_len < MAX_DIST && this != temp->dst) 
			printf("%s, %s, %u\n",temp->dst->name, temp->prev->name,temp->min_len);
		temp = temp->next;
	}
}

void node_t::show(){
	printf("\n%s Neighbour Table:\n",name);
	for (int i=0;i < ndset.cnt;i++)
	{
		node_t* _temp = ndset.node_root[i];
		if(_temp == this) continue;
		unsigned int len = lsdb.directDist(this, _temp);
		if(len != MAX_DIST) printf("%s %u\n", _temp->name, len);
	}
	printf("\n%s LSDB:\n",name);
	lsdb.show();

	printf("\n%s Routing Table:\n", name);
	showRouteTable();
}