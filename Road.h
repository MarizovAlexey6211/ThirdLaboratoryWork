#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

#include <stddef.h>

template<typename TVertex, typename TEdge>
class locality {
private:
	TVertex name;
	size_t num_inhabitants;
	int color = 0;
	friend class edge_link;
	class edge_link {
		TVertex src;
		TVertex dst;
		TEdge edge;
		friend class locality<TVertex, TEdge>;
	public:
		edge_link(const TVertex& src, const TVertex& dst, const TEdge& edge) : src(src), dst(dst), edge(edge) {}
		TEdge _get_edge() { return edge; }
		TVertex _get_src() { return src; }
		TVertex _get_dst() { return dst; }
		void _edit_src(const TVertex& d) { src = d; }
		void _edit_dst(const TVertex& d) { dst = d; }
		void _edit_edge(const TEdge& length) { edge = length; }
	};
	std::list<edge_link> connect;
