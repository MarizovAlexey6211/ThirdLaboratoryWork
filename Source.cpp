#include "Road.h"
#include <iostream>

	template < typename TVertex, typename TEdge>
	void print(road_network<TVertex, TEdge> g)
	{
		auto begin = g.begin();
		auto end = g.end();
		while (begin != end) {
			std::cout << begin->get_name() << "  (population " << begin->get_num() << ")" << std::endl;
			{
				auto b = begin->begin_edge();
				auto e = begin->end_edge();
				while (b != e) {
					std::cout << "\n\t" << b->_get_src() << " --->     " << b->_get_dst() << " Distance::: " << b->_get_edge() << std::endl;
					++b;
				}
			}
			++begin;
			std::cout << std::endl;
		}
	}
	void print_between() {
		std::cout << "----------------------------------------------------------------------" << std::endl;
		std::cout << "----------------------------------------------------------------------" << std::endl;
		std::cout << "----------------------------------------------------------------------" << std::endl;
		std::cout << "----------------------------------------------------------------------" << std::endl;
	}
