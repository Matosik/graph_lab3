#pragma once
#include <iostream>
#include <vector>
using namespace std;

template<typename Vertex, typename Distance = double>// Vertex - �������  Distance - ���������
class Graph {
public:
    struct Edge 
    { 

    }

    struct 

    //��������-����������-�������� ������
    bool has_vertex(const Vertex& v) const;
    void add_vertex(const Vertex& v);
    bool remove_vertex(const Vertex& v);
    vector<Vertex> vertices() const;


    //��������-����������-�������� �����
    void add_edge(const Vertex& from, const Vertex& to, const Distance& d);
    bool remove_edge(const Vertex& from, const Vertex& to);
    bool remove_edge(const Edge& e); //c ������ ����������
    bool has_edge(const Vertex& from, const Vertex& to) const;
    bool has_edge(const Edge& e); //c ������ ���������� � Edge

    //��������� ���� �����, ��������� �� �������
    vector<Edge> edges(const Vertex& vertex);

    size_t order() const; //�������
    size_t degree() const; //�������


    //����� ����������� ����
    vector<Edge> shortest_path(const Vertex& from,const Vertex& to) const;
    //�����
    vector<Vertex> walk(const Vertex& start_vertex)const;
};

