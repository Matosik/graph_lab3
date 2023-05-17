#pragma once
#include <iostream>
#include <vector>

using namespace std;

enum Color {
    WHITE, GRAY, BLACK
};

template<typename V = int, typename D = double>// Vertex - вершина  Distance - растояние
class Graph {
private:
    struct Edge {
        Edge* next;
        V vertex;
        D weight;
        Edge(D weight, V vertex, Edge* next = nullptr) :weight(weight), vertex(vertex), next(next) {}
    };
    struct Vertex {
        Edge* edges;
        V name;
        Color color;
        Vertex(V name, Color color = WHITE, Edge* edges = nullptr) : name(name), color(color), edges(edges) {}
    };
    vector<Vertex> Verts;
public:
    ~Graph() {
        Verts.clear();
    }
    bool find_E(V from , V to){
        int id_from = find_index_V(from);
        if (id_from == -1) { throw("Вершины откуда нет"); }
        int id_to = find_index_V(to);
        if (id_to == -1) { throw("Вершины куда нет"); }
        Edge* tmp = Verts[id_from];
        while (tmp != nullptr) {
            if (tmp->vertex == Verts[id_to].name) {
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }
    bool find_V(V name) {
        for (int i = 0; i < Verts.size(); i++) {
            if (Verts[i].name == name) {
                return true;
            }
        }
        return false;
    }
    int find_index_V(V name) {
        for (int i = 0; i < Verts.size(); i++) {
            if (Verts[i].name == name) {
                return i;
            }
        }
        return -1;
    }
    bool add_V(V name){
        if (find_V(name) == false) {
            Verts.push_back(Vertex(name));
            return true;
        }
        return false;
    }
    void delete_E(V from , V to){
         
    }



    void delete_V(V name){
        int id = find_index_V(name);
        if (id == -1) {
            throw("Такой вершины нет. тилт....");
        }
        for (int i=0; i < Verts.size(); i++) {
            
            if(find_E(Verts[id].name, Verts[i].name)) == true{
                delete_E(Verts[id].name, Verts[i].name);
            }

            if (find_E(Verts[id].name, Verts[i].name)) == true{
                delete_E(Verts[id].name, Verts[i].name);
            }
        }
        Verts.erase(Verts.begin() + id);        
    }




    void add_E(V from, V to, D weight) {
        int id_from = find_index_V(from);
        int id_to = find_index_V(to);
        if (id_to == -1) {
            throw("Вершины туда куда ведет ребро нет");
        }
        if (id_from == -1) {
            throw("Вершины, откуда ведет ребро, нет ");
        }
        Edge* new_edge = new Edge(weight, to);
        if (Verts[id_from].edges == nullptr) {
            Verts[id_from].edges = new_edge;
            return;
        }
        Edge* tmp = Verts[id_from].edges;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = new_edge;
    }
    void firma_gerasim_belim_krasim() {
        for (int i = 0; i < Verts.size(); i++) {
            Verts[i].color = WHITE;
        }
    }
    void deep_cool(Vertex& current, vector<V>& result) {
        current.color = GRAY;
        result.push_back(current.name);
        Edge* tmp = current.edges;
        while (tmp != nullptr) {
            int id = find_index_V(tmp->vertex);
            if (Verts[id].color == WHITE) {
                deep_cool(Verts[id], result);
            }
            tmp = tmp->next;
        }
        current.color = BLACK;
    }

    vector<V> walk_in_deep(V start) {
        vector<V> result;
        int id = find_index_V(start);
        if (id == -1) {
            throw"Отправная вершина не найдена... наш корабль идет ко дну.. помоги мне я утону..";
        }
        deep_cool(Verts[id], result);
        firma_gerasim_belim_krasim();
        return result;
    }

};
