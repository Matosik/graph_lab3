#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

enum Color {
    WHITE, GRAY, BLACK
};

template<typename V, typename D>
class Graph {
private:
    struct Edge {
        V vertex;
        D weight;
        Edge(V vertex, D weight) : vertex(vertex), weight(weight) {}
    };
    struct Vertex {
        vector<Edge> edges;
        V name;
        Color color;
        Vertex(V name, Color color = WHITE) :name(name), color(color) {}
    };
    void deep_helper(V v, vector<V>& result) {
        int id_current = find_index_V(v);
        graph[id_current].color = GRAY;
        result.push_back(v);

        for (auto i = graph[id_current].edges.begin(); i != graph[id_current].edges.end(); ++i)
            if (graph[find_index_V(i->vertex)].color == WHITE)
                deep_helper(i->vertex, result);
        graph[id_current].color = BLACK;
    }
    vector<Vertex> graph;
    void ford_helper(V from, V to, vector<V>& result, D& distance) {
        // инициализировать расстояния до всех вершин как бесконечные и расстояние до источника как 0
        vector<D> dist(graph.size(), numeric_limits<D>::max());
        dist[find_index_V(from)] = 0;

        // инициализировать предшественников всех вершин как -1
        vector<int> pred(graph.size(), -1);

        // релаксация вершин 
        for (int i = 0; i < graph.size() - 1; ++i) {
            bool updated = false;
            for (int v = 0; v < graph.size(); ++v) {
                for (Edge edge : graph[v].edges) {
                    int u = find_index_V(edge.vertex);
                    if (dist[v] != numeric_limits<D>::max() && dist[v] + edge.weight < dist[u]) {
                        dist[u] = dist[v] + edge.weight;
                        pred[u] = v;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }

        //проверка отрицательного цикла
        for (int v = 0; v < graph.size(); ++v) {
            for (Edge edge : graph[v].edges) {
                int u = find_index_V(edge.vertex);
                if (dist[v] != numeric_limits<D>::max() && dist[v] + edge.weight < dist[u]) {
                    throw "Graph contains a negative-weight cycle";
                }
            }
        }

        // Храним кратчайший путь от from до to
        distance = dist[find_index_V(to)];

        // Теперь, чтобы получить путь, мы должны вернуться назад от вершины "to".
        for (V v = to; v != from; v = graph[pred[find_index_V(v)]].name) {
            result.insert(result.begin(), v);
        }
        result.insert(result.begin(), from);
    }
public:
    void visualizeGraph() const {
        std::ofstream dotFile("graph.dot");
        dotFile << "digraph G {\n";
        for (const auto& vertex : graph) {
            dotFile << "    " << vertex.name << ";\n";
        }
        for (const auto& vertex : graph) {
            for (const auto& edge : vertex.edges) {
                dotFile << "    " << vertex.name << " -> " << edge.vertex << " [label=\"" << edge.weight << "\"];\n";
            }
        }

        dotFile << "}\n";
        dotFile.close();

        // Generate the graph image using GraphViz
        std::system("dot -Tpng graph.dot -o graph.png");

        // Open the graph image using the default image viewer
#ifdef _WIN32
        std::system("start graph.png");
#endif
    }
    ~Graph() {
        graph.clear();
    }
    void clean() {
        graph.clear();
    }
    int size_g() { return graph.size(); }
    bool find_E(V from, V to) {
        int id_from = find_index_V(from);
        if (id_from == -1) { throw("Вершины откуда нет"); }
        int id_to = find_index_V(to);
        if (id_to == -1) { throw("Вершины куда нет"); }
        vector<Edge>& tmp = graph[id_from].edges;
        for (int i = 0; i < tmp.size(); i++) {
            if (tmp[i].vertex == to) {
                return true;
            }
        }
        return false;
    }
    int find_index_V(V name) {
        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].name == name) {
                return i;
            }
        }
        return -1;
    }
    void add_V(V name) {
        if (find_index_V(name) == -1) {
            Vertex tmp = Vertex(name);
            graph.push_back(tmp);
            return;
        }
        throw("Такая вершина уже есть\n");
    }
    bool add_E(V from, V to, D weight) {
        int id_from = find_index_V(from);
        if (id_from == -1) { throw("Вершины откуда нет\n"); }
        int id_to = find_index_V(to);
        if (id_to == -1) { throw("Вершины куда нет\n"); }
        if (find_E(from, to) == true) { throw("Упс такое ребро уже есть, больше дороги строить не будем!\n"); }
        graph[id_from].edges.push_back(Edge(to, weight));
    }
    void delete_V(V value) {
        int id = find_index_V(value);
        if (id == -1) { throw("Такой вершины нет\n"); }
        for (int i = 0; i < graph.size(); i++) {
            if (i == id) { continue; }
            vector<Edge>& tmp = graph[i].edges;
            for (int j = 0; j < tmp.size(); j++) {
                if (tmp[j].vertex == value) {
                    delete_E(graph[i].name, value);
                    break;
                }
            }
        }
        graph.erase(graph.begin() + id);
    }
    void delete_E(V from, V to) {
        if (find_E(from, to) == false) { throw("Такого ребра нет\n"); }
        int id_from = find_index_V(from);
        vector<Edge>& tmp = graph[id_from].edges;
        for (int i = 0; i < tmp.size(); i++) {
            if (tmp[i].vertex == to) {
                tmp.erase(tmp.begin() + i);
                break;
            }
        }
    }
    void whitewash() {
        for (int i = 0; i < graph.size(); i++) {
            graph[i].color = WHITE;
        }
    }
    vector<V> deep_cool(V v) {
        if (find_index_V(v) == -1) { throw("Такой вершины нет.\n"); }
        vector<V> result;
        deep_helper(v, result);
        for (int i = 0; i < graph.size(); i++) {
            if (graph[i].color == WHITE) {
                deep_helper(graph[i].name, result);
            }
        }
        whitewash();
        return result;
    }
    pair<vector<V>, D> belman_ford(V from , V to) {
        if (find_index_V(from) == -1) { throw "Нет вершины (откуда)"; }
        if (find_index_V(to) == -1) { throw"Нет вершины (куда)"; }
        vector<V> result;
        D distanse = 0;
        ford_helper(from, to, result, distanse);
        return pair<vector<V>, D>(result, distanse);
    }
    V good_place() {
        D min = numeric_limits<D>::max();
        int id=0;
        for (int i = 0; i < graph.size(); i++) {
            D max_all = numeric_limits<D>::max();
            for (int j = 0; j < graph.size(); j++) {
                if (j == i) { continue; }
                pair<vector<V>, D> p = belman_ford(graph[i].name, graph[j].name);
                if(p.second<max_all){
                    max_all = p.second;
                }
            }
            if (max_all < min) {
                min = max_all;
                id = i;
            }
        }
        return graph[id].name;
    }
};


template class Graph<int, int>;
template class Graph<string, int>;
template class Graph<char, int>;
template class Graph<double, int>;
template class Graph<int, double>;
template class Graph<string, double>;
template class Graph<char, double>;
template class Graph<double, double>;
