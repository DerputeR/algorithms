#pragma once
#include <vector>
#include <iostream>

namespace graphs
{
    using vertex_id = int;

    struct edge
    {
        vertex_id from;
        vertex_id to;
        float weight;
    };

    struct vertex
    {
        char label;
        std::vector<edge> edges;
    };

    struct visit_times
    {
        int pre;
        int post;

        friend std::ostream &operator<<(std::ostream &os, const visit_times &vt);
    };

    struct traversal
    {
        vertex_id prev;
        float dist;
    };

    using adjacency_list = std::vector<vertex>;

    void swap_vertices(adjacency_list &graph, vertex_id a, vertex_id b);

    namespace undirected
    {
        void explore(adjacency_list &graph,
                     vertex_id vert,
                     std::vector<bool> &visited,
                     int component_number,
                     std::vector<int> &component_numbers,
                     std::vector<vertex_id> & prev);
        std::vector<vertex_id> dfs(adjacency_list &graph);
        std::vector<traversal> bfs(adjacency_list &graph, vertex_id start);
    }

    namespace directed
    {
        void explore(adjacency_list &graph,
                     vertex_id vert,
                     std::vector<bool> &visited,
                     std::vector<visit_times> &timestamps,
                     int &clock);
        std::vector<visit_times> dfs(adjacency_list &graph);
        std::vector<traversal> bfs(adjacency_list &graph, vertex_id start);
    }
}
