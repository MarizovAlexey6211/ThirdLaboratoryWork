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
	int main() {
		try
		{
			road_network<std::string, double> g;
			g.add_vertex("Moscow", 12000000);
			g.add_vertex("Saratov", 200000);
			g.add_vertex("Kursk", 447424);
			g.add_vertex("Ufa", 1121221);
			g.add_vertex("Ryazan", 550000);
			g.add_edge("Moscow", "Kursk", 12);
			g.add_edge("Moscow", "Ufa", 7);
			g.add_edge("Saratov", "Moscow", 8);
			g.add_edge("Ufa", "Saratov", 4);
			g.add_edge("Ufa", "Ryazan", 6);
			g.add_edge("Kursk", "Ufa", 5);
			g.add_edge("Kursk", "Ryazan", 2);
			print(g);
			print_between();


			std::cout << "DFS " << std::endl;
			g.dfs("Kursk");
			std::cout << std::endl;

			auto result = Dijkstra(g, "Moscow", "Ryazan");
			std::cout << " SHORTEST DISTANCE " << result.second << std::endl;
			std::cout << " MINIMAL WAY DIJKSTRA :::::::  ";
			auto end = --result.first.end();
			auto i = result.first.begin();
			for (end; end != i; end--)
				std::cout << *end << ' ';
			std::cout << *i << std::endl;


			g.add_edge("Ryazan", "Saratov", 3);
			print(g);
			print_between();

			g.erase_edge("Ufa", "Ryazan", 6);
			print(g);
			print_between();

			g.erase_vertex("Saratov");
			print(g);
			print_between();

			g.add_vertex("Tver", 400003);
			print(g);
			print_between();

			g.add_edge("Ryazan", "Tver", 6);
			print(g);
			print_between();

			g.erase_edge("Ryazan", "Tver", 6);
			print(g);
			print_between();

			g.edit_vertex("Tver", "Volgograd");
			print(g);
			print_between();
			//


			g.add_edge("Ryazan", "Volgograd", 6);
			print(g);
			print_between();

			g.edit_number("Volgograd", 500006);
			print(g);
			print_between();
			//
			g.edit_edge_distance("Ryazan", "Volgograd", 9);
			print(g);
			print_between();

			g.add_vertex("Irkutsk", 362766);
			print(g);
			print_between();

			g.edit_edge_dst("Ryazan", "Volgograd", "Irkutsk");
			print(g);
			print_between();
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
		}

	}