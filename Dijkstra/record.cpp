#include "record.h"

route_t::route_t()
{
	init();
}

route_t::route_t(node_t* _src, node_t* _dst, node_t* _prev /*= 0*/, unsigned int _min_len /*= 0*/)
{
	src = _src; dst = _dst; prev = _prev; min_len = _min_len;next=0;
	init();
}

route_t::~route_t()
{

}

void route_t::update(node_t* _prev, unsigned int _minlen)
{
	prev = _prev; min_len = _minlen;
	isfresh = true;
}

void route_t::init()
{
	isfresh = false;
	min_len = MAX_DIST;
}
