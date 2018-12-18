#include <iostream>
#include <vector>
#include <random>
#include <memory>

unsigned int fib(unsigned int num, unsigned int other = 0,
                 unsigned int sum = 1)
{
    if (num == 0)
        return other;
    if (num == 1)
        return sum;
    return fib(num - 1, sum, other + sum);
}

struct Vertex
{
    unsigned int N;
    std::vector<int> Neighbors;
};

struct RandomGen
{
    std::random_device rd;
    std::mt19937 eng{rd()};
    int const MAX_N;
    int const MIN_N;

    RandomGen() : MAX_N(1), MIN_N(-1) {}
    RandomGen(int max_n) : MAX_N(max_n), MIN_N(-1) {}
    RandomGen(int min_n, int max_n) : MAX_N(max_n), MIN_N(min_n) {}

    std::uniform_int_distribution<int> dist{MIN_N, MAX_N};

    float getNum()
    {
        return dist(eng);
    }
};

void print_graph(std::vector<Vertex> &graph)
{
    std::for_each(graph.begin(), graph.end(), [&](Vertex &node) {
        std::cout << "NODE[" << node.N << "]->|";
        std::for_each(node.Neighbors.begin(), node.Neighbors.end(), [&](int neighbor) {
            std::cout << graph[neighbor].N << "\|";
        });
        std::cout << std::endl;
    });
}

int main(int argc, char const *argv[])
{
    const unsigned int MAX_NODES = 20;
    std::vector<Vertex> graph;
    RandomGen rand_gen(30, 40);
    RandomGen rand_choice(0, 1);

    for (unsigned int idx = 0; idx < MAX_NODES; ++idx)
    {
        Vertex *cur_vertex = new Vertex();
        graph.push_back(*cur_vertex);
    }

    for (unsigned int idx = 0; idx < MAX_NODES; ++idx)
    {
        Vertex *cur_vertex = &graph[idx];
        cur_vertex->N = rand_gen.getNum();
        std::cout << rand_gen.getNum() << " " << cur_vertex->N << "\n";
        for (unsigned int neighbor = idx + 1; neighbor < MAX_NODES; ++neighbor)
        {
            if (neighbor > idx)
            {
                if (cur_vertex->Neighbors.size() == 0 || rand_choice.getNum())
                {
                    cur_vertex->Neighbors.push_back(neighbor);
                }
            }
        }
    }

    print_graph(graph);

    /* code */
    return 0;
}
