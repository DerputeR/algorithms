#pragma once
#include <vector>

namespace graphs
{
    using vertex_id = int;
    using adjacency_list = std::vector<vertex>;

    struct edge
    {
        vertex_id from;
        vertex_id to;
        float weight;
    };

    struct vertex
    {
        char label;
        int component_number = 0;
        std::vector<edge> edges;
    };

    namespace undirected
    {
        void explore(adjacency_list &G,
                vertex_id vert,
                std::vector<bool> &visited,
                int component_number);
        void dfs(adjacency_list &G);
        void bfs(adjacency_list &G, vertex_id start);
    }
}
