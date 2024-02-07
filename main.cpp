#include <iostream>
#include "Graph.h"
#include <cmath>
#include <chrono>
using namespace std;
using namespace chrono;
class Algorithm
{
public:
    Graph graph;
    int start, goal;
    int* reachable;
    int count_reachable;
    int* explored;
    int count_explored;
    double* cost_start_to_node;
    int* previous;
    int* path;
    int len_path;
    Algorithm(int start, int goal, int countNodes, Graph g)
    {
        graph=g;
        len_path = 0;
        path = new int[len_path];
        CurrentMem += sizeof(int) * len_path;
        this->start = start-1;
        this->goal = goal-1;
        count_reachable = 1;
        reachable = new int[count_reachable] {this->start};
        CurrentMem += sizeof(int) * count_reachable;
        count_explored = 0;
        explored = new int[count_explored];
        CurrentMem += sizeof(int) * count_explored;
        cost_start_to_node = new double[countNodes];
        CurrentMem += sizeof(double) * countNodes;
        for (int i = 0; i <countNodes; i++)
        {
            cost_start_to_node[i] = -1;
        }
        cost_start_to_node[this->start] = 0;
        previous = new int[countNodes];
        CurrentMem += sizeof(int) * countNodes;
        if (MaxMem < CurrentMem)
        {
            MaxMem = CurrentMem;
        }
    }
    Algorithm(const Algorithm& a)
    {
        if (this != &a)
        {
            graph = a.graph;
            start = a.start;
            goal = a.goal;
            count_reachable = a.count_reachable;
            count_explored = a.count_explored;
            len_path = a.len_path;
            path = new int[len_path];
            CurrentMem += sizeof(int) * len_path;
            for (int i = 0; i < len_path; i++)
            {
                path[i] = a.path[i];
            }
            reachable = new int[count_reachable];
            CurrentMem += sizeof(int) * count_reachable;
            for (int i = 0; i < count_reachable; i++)
            {
                reachable[i] = a.reachable[i];
            }
            explored = new int[count_explored];
            CurrentMem += sizeof(int) * count_explored;
            for (int i = 0; i < count_explored; i++)
            {
                explored[i] = a.explored[i];
            }
            cost_start_to_node = new double[graph.countNodes];
            CurrentMem += sizeof(double) * graph.countNodes;
            for (int i = 0; i < graph.countNodes; i++)
            {
                cost_start_to_node[i] = a.cost_start_to_node[i];
            }
            cost_start_to_node[start] = 0;
            previous = new int[graph.countNodes];
            CurrentMem += sizeof(int) * graph.countNodes;
            for (int i = 0; i < graph.countNodes; i++)
            {
                previous[i] = a.previous[i];
            }
            if (MaxMem < CurrentMem)
            {
                MaxMem = CurrentMem;
            }
        }
    }
    Algorithm& operator=(const Algorithm& a)
    {
        if (this != &a)
        {
            this->~Algorithm();
            graph = a.graph;
            start = a.start;
            goal = a.goal;
            count_reachable = a.count_reachable;
            count_explored = a.count_explored;
            len_path = a.len_path;
            path = new int[len_path];
            CurrentMem += sizeof(int) * len_path;
            for (int i = 0; i < len_path; i++)
            {
                path[i] = a.path[i];
            }
            reachable = new int[count_reachable];
            CurrentMem += sizeof(int) * count_reachable;
            for (int i = 0; i < count_reachable; i++)
            {
                reachable[i] = a.reachable[i];
            }
            explored = new int[count_explored];
            CurrentMem += sizeof(int) * count_explored;
            for (int i = 0; i < count_explored; i++)
            {
                explored[i] = a.explored[i];
            }
            cost_start_to_node = new double[graph.countNodes];
            CurrentMem += sizeof(double) * graph.countNodes;
            for (int i = 0; i < graph.countNodes; i++)
            {
                cost_start_to_node[i] = a.cost_start_to_node[i];
            }
            cost_start_to_node[start] = 0;
            previous = new int[graph.countNodes];
            CurrentMem += sizeof(int) * graph.countNodes;
            for (int i = 0; i < graph.countNodes; i++)
            {
                previous[i] = a.previous[i];
            }
            if (MaxMem < CurrentMem)
            {
                MaxMem = CurrentMem;
            }
        }
        return *this;
    }
    ~Algorithm()
    {
        delete[] reachable;
        delete[] explored;
        delete[] cost_start_to_node;
        delete[] previous;
        delete[] path;
        CurrentMem -= (sizeof(int) * count_reachable+sizeof(int)*count_explored+sizeof(double)*graph.countNodes+sizeof(int)*graph.countNodes+sizeof(int)*len_path);
    }
    void add_reachable(int node)
    {
        int *new_reachable = new int[count_reachable + 1];
        CurrentMem += sizeof(int) * count_reachable+1;
        for (int i = 0; i < count_reachable; i++)
        {
            new_reachable[i] = reachable[i];
        }
        delete[] reachable;
        CurrentMem -= sizeof(int) * count_reachable;
        new_reachable[count_reachable] = node;
        count_reachable++;
        reachable = new_reachable;
        if (MaxMem < CurrentMem)
        {
            MaxMem = CurrentMem;
        }
    }
    void remove_reachable(int node)
    {
        int t;
        int* new_reachable = new int[count_reachable-1];
        CurrentMem += sizeof(int) * count_reachable - 1;
        for (int i = 0; i < count_reachable-1; i++)
        {
            if (reachable[i] == node)
            {
                t = reachable[count_reachable - 1];
                reachable[count_reachable - 1] = node;
                new_reachable[i] = t;
            }
            else new_reachable[i] = reachable[i];
        }
        delete[] reachable;
        CurrentMem -= sizeof(int) * count_reachable;
        count_reachable--;
        reachable = new_reachable;
        if (MaxMem < CurrentMem)
        {
            MaxMem = CurrentMem;
        }
    }
    void add_explored(int node)
    {
        int* new_explored = new int[count_explored+1];
        CurrentMem += sizeof(int) * count_explored - 1;
        for (int i = 0; i < count_explored; i++)
        {
            new_explored[i] = explored[i];
        }
        delete[] explored;
        CurrentMem -= sizeof(int) * count_explored;
        new_explored[count_explored] = node;
        count_explored++;
        explored = new_explored;
        if (MaxMem < CurrentMem)
        {
            MaxMem = CurrentMem;
        }
    }
    double cost(int node)
    {
        return cost_start_to_node[node];
    }
    void change_cost(int node, int cost)
    {
        cost_start_to_node[node] = cost;
    }
    double estimate_distance(int node, int goal_node)
    {
        return sqrt(pow(graph.coordinates[node][0] - graph.coordinates[goal_node][0], 2) + pow(graph.coordinates[node][1] - graph.coordinates[goal_node][1], 2));
    }
    int choose_node(int cur_node)
    {
        double min_cost = INFINITY;
        int best_node;
        double cost_to_node, cost_to_goal, total_cost;
        for(int i=0; i<count_reachable;i++)
         {
            cost_to_node = cost(reachable[i]);
            cost_to_goal = estimate_distance(reachable[i], goal);
            total_cost = cost_to_node + cost_to_goal;
            if (min_cost > total_cost)
            {
                min_cost = total_cost;
                best_node = reachable[i];
            }
         }
        return best_node;
    }
    void add_path(int node)
    {
        int* new_path = new int[len_path + 1];
        CurrentMem += sizeof(int) * len_path + 1;
        for (int i = 0; i < len_path; i++)
        {
            new_path[i] = path[i];
        }
        new_path[len_path] = node;
        delete[] path;
        CurrentMem -= sizeof(int) * len_path;
        len_path++;
        path = new_path;
    }
    int* build_path(int goal)
    {
        while (goal>=0)
        {
            add_path(goal+1);
            goal = previous[goal];
        }
        return path;
    }
    int A_star (Graph graph)
    {
    int cur_node = start;
    while (count_reachable)
    {
        cur_node = choose_node(cur_node);
        if (cur_node == goal) return 0;
        remove_reachable(cur_node);
        add_explored(cur_node);
        for (int j = 0; j < graph.countNodes; j++)
        {
            if (graph.adjList[cur_node][j] != 0)
            {
                bool flag = true;
                for (int i = 0; i < count_explored; i++)
                {
                    if (j == explored[i])
                    {
                        flag = false;
                        break;
                    }
                }
                for (int i = 0; i < count_reachable; i++)
                {
                    if (j == reachable[i])
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag) add_reachable(j);
                if (cost(j) == -1)
                {
                    previous[j] = cur_node;
                    change_cost(j, cost(cur_node) + graph.adjList[cur_node][j]);
                }
                else if (cost(cur_node) + graph.adjList[cur_node][j] < cost(j))
                {
                    previous[j] = cur_node;
                    change_cost(j, cost(cur_node) + graph.adjList[cur_node][j]);
                }
            }
        }
    }
    return 1;
    }
};
int randnode(int max_node)
{
    return 1+rand() % max_node;
}

int main()
{
    srand(time(NULL));
    int r;
    std::cout << "MODE: 1-auto, 2-manual\n";
    std::cin >> r;
    switch (r)
    {
    case 1:
    {
        int n, start, goal;
        std::cout << "Enter count nodes Graph:";
        std::cin >> n;
        Graph graph(n);
        graph.randgraph();
        do {
            start = randnode(n);
            goal = randnode(n);
        } while (start > goal);
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        Algorithm a(start, goal, n, graph);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "\nThe time: " << time_span.count() << " seconds\n";
        std::cout << "Max Memory: " << MaxMem<<"\n";
        if (a.A_star(graph) == 0)
        {
            a.build_path(goal - 1);
            std::cout << "Path: ";
            for (int i = 0; i < a.len_path; i++)
            {
                std::cout << a.path[i] << ' ';
            }
        }
    }
    break;
    case 2:
    {
        int n, m, start, goal;
        std::cout << "Enter count nodes Graph:";
        std::cin >> n;
        Graph graph(n);
        std::cout << "Enter count edges:";
        std::cin >> m;
        int u, v, cost, x ,y, x1, y1;
        for (int i = 0; i < m; i++)
        {
            std::cout << "Enter node from:";
            std::cin >> u;
            std::cout << "Enter node to:";
            std::cin >> v;
            std:: cout << "Enter cost:";
            std::cin >> cost;
            /*std::cout << "Enter coordinates 1st node x and y:";
            std::cin >> x>>y;*/
            graph.add(--u, --v, cost);
            /*graph.coordinates[u][0] = x;
            graph.coordinates[u][1] = y;*/
           /* std::cout << "Enter coordinates second node x and y:";
            std::cin >> x1 >> y1;*/
            /*graph.coordinates[v][0] = x1;
            graph.coordinates[v][0] = y1;*/
        }
        std::cout << "Enter start:\n";
        std::cin >> start;
        std::cout << "Enter goal:\n";
        std::cin >> goal;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        Algorithm a(start, goal, n, graph);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "\nThe time: " << time_span.count() << " seconds\n";
        std::cout << "Max Memory: " << MaxMem<<"\n";
        if (a.A_star(graph) == 0)
        {
            a.build_path(goal - 1);
            std::cout << "Path: ";
            for (int i = 0; i < a.len_path; i++)
            {
                std::cout << a.path[i] << ' ';
            }
        }
    }
    break;
    default:
        break;
    }
    return 0;
}
