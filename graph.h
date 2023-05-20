#pragma once
#include <iostream>
#include <vector>
#include <string>

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
    vector<Vertex> graph;
public:
    ~Graph() {
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
        throw("Такая вершина уже есть");
    }
    bool add_E(V from, V to, D weight) {
        int id_from = find_index_V(from);
        if (id_from == -1) { throw("Вершины откуда нет"); }
        int id_to = find_index_V(to);
        if (id_to == -1) { throw("Вершины куда нет"); }
        if (find_E(from, to) == true) { throw("Упс такое ребро уже есть, больше дороги строить не будем!"); }
        graph[id_from].edges.push_back(Edge(to, weight));
    }
    void delete_E(V from, V to) {
        if (find_E(from, to) == false) { throw("Такого ребра нет"); }
        int id_from = find_index_V(from);
        vector<Edge>& tmp = graph[id_from].edges;
        for (int i = 0; i < tmp.size(); i++) {
            if (tmp[i].vertex == to) {
                tmp.erase(tmp.begin() + i);
                break;
            }
        }
    }

};
