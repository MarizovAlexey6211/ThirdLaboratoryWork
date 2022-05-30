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
};