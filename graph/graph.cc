#include "graph.h"

/**
 * Constructor of Graph class 
 */
template <typename Object>
Graph<Object>::Graph(GraphKind gk, std::string str) 
	: graphKind(gk), graphName(str) 
{
}

/**
 * Destructor of Graph class
 */
template <typename Object>
Graph<Object>::~Graph()
{
	Graph<Object>::destroyGraph();
	// this -> destroyGraph();
}

/**
 * Add vertex v to graph
 */
template <typename Object>
void Graph<Object>::addVertex(Object v, float w, Color cr)
{
	if (!isContain(v)) {
		Vertex<Object> *ver = new Vertex<Object>(v, w, cr);
		vertices[v] = ver;
	}
}

/** 
 * Add edge(s, d) to graph 
 */
template <typename Object>
void Graph<Object>::addEdge(Object s, Object d, float w)
{
	Edge<Object> *e = new Edge<Object>(d, w, vertices[s] -> firstEdge);
	Edge<Object> *re;
	switch (graphKind) {
		case UDG:
		case UDN:
			re = new Edge<Object>(s, w, vertices[d] -> firstEdge);
			vertices[d] -> firstEdge = re;
		case DG:
		case DN:
			vertices[s] -> firstEdge = e;
			break;
		default:
			;
	}
}

/** 
 * Remove vertex v from graph
 */
template <typename Object>
void Graph<Object>::removeVertex(Object v)
{
	if (isContain(v)) {
		Edge<Object> *e = vertices[v].firstEdge;
		while (e) {
			vertices[v].firstEdge = e -> nextEdge;
			delete e;
			e = vertices[v].firstEdge;
		}
		delete vertices[v];
		vertices.erase(v);
	}
}

/** 
 * Remove edge(s, d) from graph
 */
template <typename Object>
void Graph<Object>::removeEdge(Object s, Object d)
{
	Edge<Object> *pe;
	switch (graphKind) {
		case UDG:
		case UDN:
			pe = vertices[d] -> firstEdge;
			if (pe) {
				if (pe -> adjvex == s) {
					vertices[d] -> firstEdge = pe -> nestEdge;
					delete pe;
				}
				else {
					Edge<Object> *e = pe -> nestEdge;
					while (e) {
						if (e -> adjvex == s) {
							pe -> nextEdge = e -> nextEdge;
							delete e;
							break;
						}
						pe = e;
						e = e -> nextEdge;
					}
				}
			}

		case DG:
		case DN:
			pe = vertices[s] -> firstEdge;
			if (pe) {
				if (pe -> adjvex == d) {
					vertices[s] -> firstEdge = pe -> nextEdge;
					delete pe;
				}
				else {
					Edge<Object> *e = pe -> nextEdge;
					while (e) {
						if (e -> adjvex == d) {
							pe -> nextEdge = e -> nextEdge;
							delete e;
							break;
						}
						pe = e;
						e = e -> nextEdge;
					}
				}
			}
		default:
			;
	}	
}	


/**
 * Return true if graph's vertices set contains o.
 * Otherwise, return false.
 */
template <typename Object> 
bool Graph<Object>::isContain(const Object& o) const 
{
	return vertices.find(o) != vertices.end();
}

/**
 * Free memory allocated to store graph information
 */
template <typename Object>
void Graph<Object>::destroyGraph()
{
	typename std::map<Object, Vertex<Object> *>::iterator it;
	for (it = vertices.begin(); it != vertices.end(); it ++) {
		Edge<Object> *e = it -> second -> firstEdge;
		while (e){
			Edge<Object> *tmp = e -> nextEdge;
			delete e;
			e = tmp;
		}
		delete it -> second;
	}
	vertices.clear();
}

/**
 * Show the graph according to the graph kind
 */
template <typename Object>
void Graph<Object>::showGraph() const 
{
	switch (graphKind) {
		case UDG:
			showUDG();
			break;
		case UDN:
			showUDN();
			break;
		case DG:
			showDG();
			break;
		case DN:
			showDN();
			break;
		default:
			;
	}
}

/**
 * Show UDG graph
 */
template <typename Object>
void Graph<Object>::showUDG() const
{
	std::ofstream out((graphName + ".dot").c_str());
	out << "graph " << graphName << "{ " << std::endl;
	typename std::map<Object, Vertex<Object> *>::const_iterator it;
	for (it = vertices.begin(); it != vertices.end(); it ++) {
		out << it -> first << ";" << std::endl;
		Edge<Object> *e = it -> second -> firstEdge;
		while (e) {
			out << it -> first << " -- " << e -> adjvex << ";" << std::endl;
			e = e -> nextEdge;
		}																																																																					
	}
	out << "} " << std::endl;
	out.close();
}
/** 
 * Show UDN graph
 */
template <typename Object>
void Graph<Object>::showUDN() const
{
	std::ofstream out((graphName + ".dot").c_str());
	out << "graph " << graphName << " { " << std::endl;
	typename std::map<Object, Vertex<Object> *>::const_iterator it;
	for (it = vertices.begin(); it != vertices.end(); it ++) {
		out << it -> first << ";" << std::endl;
		Edge<Object> *e = it -> second -> firstEdge;
		while (e) {
			out << it -> first << " -- " << e -> adjvex 
				<< "[label=\"" << e -> weight << "\"]" << ";"
				<< std::endl;
			e = e -> nextEdge;
		}
	}
	out << "} " << std::endl;
	out.close();
}

/**
 * show DG graph
 */
template <typename Object>
void Graph<Object>::showDG() const
{
	std::ofstream out((graphName + ".dot").c_str());
	out << "digraph " << graphName << " { " << std::endl;
	typename std::map<Object, Vertex<Object> *>::const_iterator it;
	for (it = vertices.begin(); it != vertices.end(); it ++) {
		out << it -> first << ";" << std::endl;
		Edge<Object> *e = it -> second -> firstEdge;
		while (e) {
			out << it -> first << " -> " << e -> adjvex << ";" << std::endl;
			e = e -> nextEdge;
		}
	}
	out << "} " << std::endl;
	out.close();
}

/**
 * show DN graph
 */
template <typename Object>
void Graph<Object>::showDN() const
{
	std::ofstream out((graphName + ".dot").																																																																																																																																																																																																																																																																																																																																																																																																																										c_str());
	out << "digraph " << graphName << " {" << std::endl;
	typename std::map<Object, Vertex<Object> *>::const_iterator it;
	for (it = vertices.begin(); it != vertices.end(); it ++) {
		out << it -> first << ";" << std::endl;
		Edge<Object> *e = it -> second -> firstEdge;
		while (e) {
			out << it -> first << " -> " << e -> adjvex 
				<< "[label=\"" << e -> weight << "\"];"
				<< std::endl;
		}
	}
	out << "} " << std::endl;
	out.close();
}

/**
 * DFS and BFS's default traval function
 */
template <typename Object>
void Graph<Object>::print(Object o)
{
	std::cout << o << " ";
}


/**
 * BFS
 */
template <typename Object>
void Graph<Object>::BFS(Object o, void visit(Object))
{
	
	if (graphKind == UDG || graphKind == DG) {
		std::ofstream out("BFS.dot");
		if (graphKind == UDG) {
			out << "graph bfs {" << std::endl;
		}
		else {
			out << "digraph bfs {" << std::endl;
		}

		typename std::map<Object, Vertex<Object> *>::iterator it;
		for (it = vertices.begin(); it != vertices.end(); it ++) {
			it -> second -> color = WHITE;
			it -> second -> start = INFINITY;
			out << it -> first << "[label=\"" << it -> first << "(INFINITY)\"];" << std::endl;
		}
		
		std::queue<Object> q;
		vertices[o] -> start = 0;
		vertices[o] -> color = GRAY;
		q.push(o);
		while (!q.empty()) {
			Object obj = q.front();
			out << obj << "[label=\"" << obj << "("
				<< vertices[obj] -> start << ")"
				<< "\"];" << std::endl;
			visit(obj);
			Edge<Object> *e = vertices[obj] -> firstEdge;
			while (e) {
				if (vertices[e -> adjvex] -> color == WHITE) {
					vertices[e -> adjvex] -> color = GRAY;
					vertices[e -> adjvex] -> start = vertices[obj] -> start + 1;
					if (graphKind == UDG) {
						out << obj << "--" << e -> adjvex << std::endl;
					}
					else {
						out << obj << "->" << e -> adjvex << std::endl;
					}
					q.push(e -> adjvex);
				}
				e = e -> nextEdge;
			}
			vertices[obj] -> color = BLACK;
			q.pop();
		}
		out << "} " << std::endl;
		out.close();
	}
	else {
		std::cout << "It doesn't make any sense to run BFS on UDN or DN!" << std::endl;
	}
}

/**
 * DFS
 */
template <typename Object>
int Graph<Object>::timer = 0;
template <typename Object>
int Graph<Object>::dfsTreeNum = 0;

template <typename Object>
void Graph<Object>::DFS(void visit(Object))
{
	std::ofstream out("DFS.dot");
	if (graphKind == UDG || graphKind == UDN) {
		out << "graph dfs { " << std::endl;
	}
	else {
		out << "digraph dfs { " << std::endl;
	}

	typename std::map<Object, Vertex<Object> *>::iterator it;
	for (it = vertices.begin(); it != vertices.end(); it ++) {
		it -> second -> color = WHITE;
	}

	for (it = vertices.begin(); it != vertices.end(); it ++) {
		if (it -> second -> color == WHITE) {
			dfsTreeNum ++;
			visitDFS(it -> first, visit, out);
		}
	}

	for (it = vertices.begin(); it != vertices.end(); it ++) {
		out << it -> first << "[label=\"" << it -> first << "(" << it -> second -> start 
			<< "/" << it -> second -> finish << ")\"];" << std::endl;
	}
	out << "}" << std::endl;
	out.close();
}

/**
 * Recursive DFS procedure 
 */
template <typename Object>
void Graph<Object>::visitDFS(Object o, void visit(Object), std::ofstream& out)
{
	vertices[o] -> nthDFSTree = dfsTreeNum;
	timer ++;
	visit(o);
	vertices[o] -> start = timer;
	vertices[o] -> color = GRAY;
	Edge<Object> *e = vertices[o] -> firstEdge;
	while (e) {
		if (vertices[e -> adjvex] -> color == WHITE) {
			if (graphKind == UDG || graphKind == UDN) {
				out << o << " -- " << e -> adjvex << "[label=\"T\"];" << std::endl;
			}
			else {
				out << o << " -> " << e -> adjvex << "[label=\"T\"];" << std::endl;
			}
			visitDFS(e -> adjvex, visit, out);
		}
		else if (vertices[e -> adjvex] -> color == GRAY) {
			if (graphKind == UDG || graphKind == UDN) {
				out << o << " -- " << e -> adjvex << "[label=\"B\", style=\"dotted\"];" << std::endl;
			}
			else {
				out << o << " -> " << e -> adjvex << "[label=\"B\", style=\"dotted\"];" << std::endl;
			}
		}
		else {
			if (graphKind == UDG || graphKind == UDN) {
				out << o << " -- "; 
			}
			else {
				out << o << " -> ";
			}
			out << e -> adjvex << "[label=";
			if (vertices[o] -> nthDFSTree == vertices[e -> adjvex] -> nthDFSTree) {
				out << "\"F\", style=\"dotted\"];" << std::endl;
			}
			else {
				out << "\"C\", style=\"dotted\"];" << std::endl;
			}
		}
		e = e -> nextEdge;
	}
	timer ++;
	vertices[o] -> color = BLACK;
	vertices[o] -> finish = timer;
}


/**
 * Return true if the graph is weakly connected, otherwise return false.
 */
template <typename Object>
bool Graph<Object>::isConnected()
{
	std::map<Object, Vertex<Object> *>::itrator it;
	for (it = vertices.begin(); it != vertices.end(); it ++) {
		it -> second -> color = WHITE;
	}
	
}