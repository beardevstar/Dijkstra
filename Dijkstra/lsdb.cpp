#include "lsdb.h"
#include "edge.h"
#include "node.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

LSDB::LSDB()
{
	root = 0; last = 0;	//LSDB
}

LSDB::~LSDB()
{
	edge_t* temp = root;
	while (temp) {
		edge_t* next = temp->next;
		free(temp);
		temp = next;
	}
}

edge_t* LSDB::find_edge(node_t* _from, node_t* _to) {
	edge_t* temp = root;
	while (temp) {
		edge_t* next = temp->next;
		if (temp->from == _from && temp->to == _to) return temp;
		temp = next;
	}
	return 0;
}

edge_t* LSDB::add_edge(edge_t* item) {
	if (!root) {
		root = item; last = item;
		return item;
	}

	//arranging...
	edge_t* temp = root, *prev = NULL;
	while (temp) {
		edge_t* next = temp->next;
		int cplen = strlen(temp->from->name) > strlen(item->from->name) ? strlen(item->from->name) : strlen(temp->from->name);
		int res = memcmp(temp->from->name, item->from->name, cplen);
		if (res > 0) {	//item is first
			if (prev == NULL) { 
				item->next = root; root = item; 
			}
			else {
				prev->next = item; item->next = temp;
			}
			return item;
		}
		if (res == 0) {
			if (memcmp(temp->to->name, item->to->name, cplen) > 0) {
				if (prev == NULL) {
					item->next = root; root = item;
				}
				else {
					prev->next = item; item->next = temp;
				}
				return item;
			}
		}
		prev = temp;temp = next;
	}
	
	last->next = item;
	last = item;
	return item;
}

edge_t* LSDB::add_edge(node_t* _from, node_t* _to, int _w /*= 0*/)
{
	edge_t* ret = find_edge(_from, _to);
	int a = size();
	if (!ret) {
		ret = new edge_t(_from, _to, _w);
		add_edge(ret);
	}
	else {
		ret->w = _w;
	}
	a = size();
	return ret;
}

int LSDB::size()
{
	int cnt = 0;
	edge_t* temp = root;
	while (temp) {
		temp = temp->next; cnt++;
	}
	return cnt;
}

int LSDB::directDist(node_t* _n1, node_t* _n2)
{
	edge_t* n1 = find_edge(_n1, _n2);
	if (n1) return n1->w;
	
	edge_t* n2 = find_edge(_n2, _n1);
	if (n2) return n2->w;

	return MAX_DIST;
}

void LSDB::show()
{
	//printf("###\n");
	edge_t* temp = root;
	while (temp) {
		printf("%s, %s, %d\n", temp->from->name, temp->to->name, temp->w);
		temp = temp->next;
	}
}

bool LSDB::remove_edge(node_t* _from, node_t* _to) {
	edge_t* temp = root, *prev = root;
	while (temp) {
		edge_t* next = temp->next;
		if (temp->from == _from && temp->to == _to) {
			prev->next = next;
			free(temp);
			return true;
		}
		prev = temp; temp = next;
	}
	return false;
}

bool LSDB::isneighbour(node_t* _from, node_t* _to)
{
	if (_from == _to) return false;
	return !(find_edge(_from, _to) == 0 && find_edge(_to, _from) == 0);
}
