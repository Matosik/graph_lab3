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
    void deep_helper(V v, vector<V>& result) {
        int id_current = find_index_V(v);
        graph[id_current].color = GRAY;
        result.push_back(v);

        for (auto i = graph[id_current].edges.begin(); i != graph[id_current].edges.end(); ++i)
            if (graph[find_index_V(i->vertex)].color == WHITE)
                deep_helper(i->vertex, path);
        graph[id_current].color = BLACK;
    }
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
        if (find_index_V(v) == -1) { throw("Такой вершины нет."); }
        vector<V> result;
        deep_helper(v, result);
        whitewash();
        return result;
    }





};
