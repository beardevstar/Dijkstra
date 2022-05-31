#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "nodeset.h"
#include "lsdb.h"
#include "edge.h"

//#define BIG_EXAMPLE

#define END_NODE_STR "LINKSTATE"
#define END_LINK_STR "UPDATE"
#define END_UPDATE_STR "END"
#define END_ALL END_UPDATE_STR
#define SPACE_CH ' '
#define COMMA (char*)","
#pragma warning(disable : 4996)
NodeSet ndset;
LSDB lsdb;

bool isspace(char c) {
	return c == ' ' || c == '\r' || c == '\n' || c == '\t';
}

void getArgs(char* _src, char* _from, char* _to, int* _w, char* _list) {
	if (!_src) return;
	int len = 0;

	char* pfrom = strchr(_src, SPACE_CH);
	len = pfrom - _src;
	memcpy(_from, _src, len);
	_from[len] = 0;

	char* pto = strchr(pfrom + 1, SPACE_CH);
	len = pto - pfrom - 1;

	memcpy(_to, pfrom + 1, len);
	_to[len] = 0;

	char* pw = strchr(pto + 1, SPACE_CH);

	if (pw) len = pw - pto - 1;
	else len = strlen(_src) - (pto + 2 - _src);//remove \n

	char ww[16];
	memcpy(ww, pto + 1, len); ww[len] = 0;
	*_w = atoi(ww);

	if (!pw) _list[0] = 0;
	else {

#ifdef _WIN32
		len = strlen(pw + 1) - 1;
#endif // _WIN32

#ifdef __linux__
		len = strlen(pw + 1) - 2;
#endif // __linux__
		memcpy(_list, pw + 1, len);
		_list[len] = 0;
	}
}

void readLinkState(char* _buf, int _max_size) {
	int weight = 0;
	char* from = (char*)calloc(1, NAME_LEN), * to = (char*)calloc(1, NAME_LEN), * list = (char*)calloc(sizeof(char), _max_size);

	getArgs(_buf, from, to, &weight, list);
	node_t* nfrom = ndset.find(from), * nto = ndset.find(to);

	if (!nfrom)
		nfrom = ndset.add(from);
	if (!nto)
		nto = ndset.add(to);

	if (weight < 0)
		lsdb.remove_edge(nfrom, nto);
	else {
		lsdb.add_edge(nfrom, nto, weight);
	}

	ndset.update(&lsdb);
	if (list[0]) {
		char* token;
		/* get the first token */
		token = strtok(list, COMMA);
		/* walk through other tokens */
		while (token != NULL) {
			node_t* item = ndset.find(token);
			if (item) item->show();
			token = strtok(NULL, COMMA);
		}
	}
	free(from);
	free(to);
	free(list);
}

void readUpdateLink(char* _buf, int _max_size) {
	readLinkState(_buf, _max_size);
}

void readFromFile() {
	FILE* fp = fopen("input.txt", "r");
	char caption[NAME_LEN];
	while (true)
	{
		fscanf(fp, "%s", caption);
		if (memcmp(caption, END_NODE_STR, strlen(END_NODE_STR)) == 0) break;
		ndset.add(caption);
	}

	int max_buf_size = MAX_NODE_CNT * NAME_LEN;
	char* buf = (char*)malloc(max_buf_size);
	while (true) {
		char* s = fgets(buf, max_buf_size, fp);
		if (isspace(buf[0])) continue;
		if (memcmp(buf, END_LINK_STR, strlen(END_LINK_STR)) == 0) break;
		readLinkState(buf, max_buf_size);
	}

	while (true) {
		char* s = fgets(buf, max_buf_size, fp);
		if (isspace(buf[0])) continue;
		if (memcmp(buf, END_ALL, strlen(END_ALL)) == 0) break;
		readLinkState(buf, max_buf_size);
	}
	return;
	fclose(fp);
}

int main() {
	readFromFile();
	return 0;
}
