#ifndef RECORD_HEADER
#define RECORD_HEADER

class node_t;
#define MAX_DIST 0xFFFFFFFF

class route_t
{
public:
	route_t();
	route_t(node_t* _src, node_t* _dst, node_t* prev = 0, unsigned int _min_len = MAX_DIST);
	~route_t();

	void update(node_t* _prev, unsigned int _minlen);
	void init();

public:
	node_t *src, *dst, *prev;
	unsigned int min_len;
	route_t *next;
	bool isfresh;
};

#endif // RECORD_HEADER
