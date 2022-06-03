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
public:
	locality(TVertex name, size_t num_inhabitants) : name(name), num_inhabitants(num_inhabitants) {}
	TVertex get_name() { return name; }
	size_t get_num() { return num_inhabitants; }
	int get_color() { return color; }
	void edit_color(const int& new_color) { color = new_color; }
	void edit_name(const TVertex& src) {
		name = src;
		auto i = begin_edge();
		auto e = end_edge();
		while (i != e) {
			i->_edit_src(name);
			++i;
		}
	}
	void edit_num(const size_t& num) {
		num_inhabitants = num;
	}
	std::list<edge_link> get_list() { return connect; }
	using EdgeIterator = typename std::list<edge_link>::iterator;
	void add_connect(const TVertex& src, const TVertex& dst, const TEdge& edge)
	{
		edge_link ins(src, dst, edge);
		connect.insert(end_edge(), ins);
	}
	void erase_edge(EdgeIterator del)
	{
		connect.erase(del);
	}

	EdgeIterator find_edge(const TVertex& dst)
	{
		auto i = begin_edge();
		auto e = end_edge();
		while (i != e) {
			if (i->_get_dst() == dst) return i;
			++i;
		}
		return e;
	}
	EdgeIterator find_min_edge(const TVertex& src) 
	{
		auto i = begin_edge();
		auto e = end_edge();
		TEdge min = i->_get_edge();
		auto min_edge = i;
		while (i != e) {
			if (i->_get_edge() < min)
			{
				min = i->_get_edge();
				min_edge = i;
			}
			++i;
		}
		return min_edge;
	}
	EdgeIterator find_edge_and_dist(const TVertex& dst, const TEdge& need_dist)
	{
		auto i = begin_edge();
		auto e = end_edge();
		while (i != e) {
			if (i->_get_dst() == dst && i->_get_edge() == need_dist) return i;
			++i;
		}
		return e;
	}
	EdgeIterator begin_edge()
	{
		return connect.begin();
	}
	EdgeIterator end_edge()
	{
		return connect.end();
	}
};
template < typename TVertex, typename TEdge, typename TVertexContainer = std::vector<locality<TVertex, TEdge>>>
class road_network {
	TVertexContainer _vertices;

	void all_color_null() {
		auto i = begin();
		auto e = end();
		while (i != e) {
			i->edit_color(0);
			++i;
		}
	}
	void dfs_without(const TVertex& src)
	{
		auto i = find_v(src);
		if (i == end()) {
			throw std::logic_error("You are trying to change a non-existent edge");
		}
		static TVertex name = src;
		std::cout << src << " ";
		i->edit_color(1);
		auto begin = i->begin_edge();
		auto final = i->end_edge();
		for (begin; begin != final; begin++)
		{
			auto dst_edge = begin->_get_dst();
			auto dst_vert = find_v(begin->_get_dst());
			if (dst_vert->get_color() != 1)
			{
				static int ind = 0;
				++ind;
				dfs_without(dst_edge);
			}
		}
	}
public:
	using VertexIterator = typename TVertexContainer::iterator;
	void add_vertex(const TVertex& vertex, const size_t number) {
		auto begin = _vertices.begin();
		auto end = _vertices.end();
		locality<TVertex, TEdge> ins_vertex(vertex, number);
		_vertices.insert(_vertices.end(), ins_vertex);
	}
	bool check_exist_vertexes(const TVertex& src, const TVertex& dst)
	{
		bool start = false;
		bool final = false;
		auto begin = _vertices.begin();
		auto end = _vertices.end();
		while (begin != end) {
			if (begin->get_name() == src)
				start = true;
			if (begin->get_name() == dst)
				final = true;
			++begin;
		}
		if (start == true && final == true)return true;
		else return false;
	}
	bool check_e_vertex(const TVertex& src)
	{
		bool key = false;
		auto begin = _vertices.begin();
		auto end = _vertices.end();
		while (begin != end) {
			if (begin->get_name() == src)
				key = true;
			++begin;
		}
		if (key == true)return true;
		else return false;
	}
	void add_edge(const TVertex& src, const TVertex& dst, const TEdge& edge) {
		if (check_exist_vertexes(src, dst) == false)
			throw std::logic_error("You entered a non-existent locality");
		auto begin = _vertices.begin();
		while (begin->get_name() != src)
		{
			++begin;
		}
		begin->add_connect(src, dst, edge);
	}
	void edit_vertex(const TVertex& old, const TVertex& neew) {
		auto i = find_v(old);
		if (i != end())
		{
			i->edit_name(neew);
		}
		else
			throw std::logic_error("You are trying to change a non-existent vertex");
	}
	void edit_number(const TVertex& old, const size_t& neew) {
		auto i = find_v(old);
		if (i != end())
		{
			i->edit_num(neew);
		}
		else
			throw std::logic_error("You are trying to change a non-existent vertex");
	}
	void edit_edge_distance(const TVertex& src, const TVertex& dst, const TEdge& edge)
	{
		auto i = find_v(src);
		if (i != end())
		{
			auto need = i->find_edge(dst);//��������� �����
			if (need != i->end_edge())
				need->_edit_edge(edge);//����� ����������
			else
				throw std::logic_error("There is no such final path");
		}
		else
			throw std::logic_error("You are trying to change a non-existent edge");
	}
	void edit_edge_dst(const TVertex& src, const TVertex& dst, const TVertex& new_dst)
	{
		auto i = find_v(src);
		if (i != end())
		{
			auto need = i->find_edge(dst);
			if (need != i->end_edge())
				need->_edit_dst(new_dst);
			else
				throw std::logic_error("There is no such final path");
		}
		else
			throw std::logic_error("You are trying to change a non-existent edge");
	}
	void erase_edge(const TVertex& src, const TVertex& dst, const TEdge& edge)
	{
		auto i = find_v(src);
		if (i != end())
		{
			auto need = i->find_edge_and_dist(dst, edge);
			if (need != i->end_edge())
				i->erase_edge(need);
			else
				throw std::logic_error("There is no such final path");
		}
		else
			throw std::logic_error("You are trying to change a non-existent edge");
	}
	void erase_vertex(const TVertex& src)
	{
		if (check_e_vertex(src) == false)
			throw std::logic_error("You entered a non-existent locality");
		auto i = begin();
		auto e = end();
		while (i != e) {
			auto start_edge = i->begin_edge();
			auto final_edge = i->end_edge();
			while (start_edge != final_edge) {
				auto copy = start_edge;
				++start_edge;
				if (copy->_get_src() == src || copy->_get_dst() == src) {
					i->erase_edge(copy);
				}
			}
			++i;
		}
		auto del_vertex = find_v(src);
		_vertices.erase(del_vertex);
	}
	size_t size() const {
		return _vertices.size();
	}
	VertexIterator find_v(const TVertex& src) {
		auto begin = _vertices.begin();
		auto end = _vertices.end();
		while (begin != end) {
			if (begin->get_name() == src) return begin;
			++begin;
		}
		return end;
	}

	VertexIterator begin() {
		return _vertices.begin();
	}

	VertexIterator end() {
		return _vertices.end();
	}


	void dfs(const TVertex& src)
	{
		dfs_without(src);
		all_color_null();
	}
	VertexIterator min_elem_di()
	{
		auto begin = _vertices.begin();
		auto end = _vertices.end();
		size_t min = SIZE_MAX;
		auto min_vert = begin;
		while (begin != end)
		{
			if (begin->get_num() < min && begin->get_color() != 2)
			{
				min = begin->get_num();
				min_vert = begin;
			}
			++begin;
		}
		return min_vert;
	}

};

std::pair<std::vector<std::string>, double> Dijkstra(road_network<std::string, double>& g, const std::string& src, const std::string& dst)
{
	road_network<std::string, double> l = g;
	road_network<std::string, double> way;
	std::vector<std::string> p;
	std::pair<std::vector<std::string>, double> rz;
	if (g.check_exist_vertexes(src, dst) == false)
	{
		return std::make_pair(p, -1);
	}
	auto b = l.begin();
	auto end = l.end();
	for (b; b < end; b++)
	{
		way.add_vertex(b->get_name(), b->get_num());
		way.add_edge(b->get_name(), b->get_name(), 0);
		if (b->get_name() == src)
		{
			b->edit_num(0);
		}
		else
			b->edit_num(LLONG_MAX);
	}
	auto size = g.size();
	for (size_t i = 0; i < size; ++i)
	{
		auto v = l.min_elem_di();
		if (l.find_v(v->get_name())->get_num() == LLONG_MAX) {
			break;
		}
		v->edit_color(2);
		auto begin_v = v->begin_edge();
		auto end_v = v->end_edge();
		while (begin_v != end_v) {
			auto link = *begin_v;
			auto q = l.find_v(link._get_dst()); 
			auto w = link._get_edge(); 
			if (v->get_num() + w < q->get_num()) {
				q->edit_num(v->get_num() + w);
				way.find_v(q->get_name())->begin_edge()->_edit_dst(v->get_name());
			}
			++begin_v;
		}
	}
}
