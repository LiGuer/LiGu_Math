#ifndef GRAPH_THEORY_GRAPH_H
#define GRAPH_THEORY_GRAPH_H

#include <algorithm>
#include <vector>

using namespace std;

namespace GraphTheory {

/* --------------------------------
*
*	ͼ �ڵ�
*
* -------------------------------- */
template <class T = int>
class GraphNode {
public:
	T val;

	vector<GraphNode*> next, prev;
};

}

#endif