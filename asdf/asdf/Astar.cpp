#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <array>
#include <unordered_set>

#include <cmath>
#include <iomanip>
#include <conio.h>

const int INF = std::numeric_limits<int>::max();
//const std::array<std::pair<int, int>, 4> directions = { {{0, 1}, {1, 0}, {0, -1}, {-1, 0}} }; // 동, 서, 남, 북

const std::array<std::pair<int, int>, 8> directions = { {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}} }; // 동, 서, 남, 북, 남동, 남서, 북동, 북서

void PrintMaze(const std::vector<std::vector<int>>& maze)
{
    for (const auto& row : maze) {
        for (int cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void PrintDistances(const std::vector<std::vector<int>>& distances)
{
    std::cout << "\nDistance grid:\n";
    for (const auto& row : distances)
    {
        for (const auto& cell : row)
        {
            if (cell == INF)
            {
                std::cout << "__ ";
            }
            else {
                std::cout << std::setw(2) << std::setfill('0') << cell << " ";
            }
        }
        std::cout << "\n";
    }
}

void PrintCurrent(const std::vector<std::vector<int>>& maze, const std::vector<std::vector<int>>& distances, int x, int y)
{
    std::vector<std::vector<int>> current = distances;

    current[x][y] = -1;

    std::cout << "\nCurrent grid: [ " << y << ", " << x << " ] " << distances[x][y] << "\n";

    for (int i = 0; i < maze.size(); ++i)
    {
        for (int j = 0; j < maze[0].size(); ++j)
        {
            if (current[i][j] == INF) //방문한 적이 없음
            {
                std::cout << "__ ";
            }
            else if (current[i][j] == -1) //현재 위치
            {
                std::cout << "XX ";
            }
            else
            {
                std::cout << std::setw(2) << std::setfill('0') << current[i][j] << " ";
            }
        }

        std::cout << "\n";

    }

    system("pause");
}

namespace DijkstraTest
{
    struct Cell
    {
        int x, y, dist;

        bool operator>(const Cell& other) const
        {
            return dist > other.dist;
        }
    };

    std::vector<std::vector<int>> Dijkstra(const std::vector<std::vector<int>>& maze, int startX, int startY)
    {
        int rows = maze.size();
        int cols = maze[0].size();
        std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, INF));

        dist[startX][startY] = 0;

        std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> pq;
        pq.push({ startX, startY, 0 });

        while (!pq.empty())
        {
            Cell current = pq.top();

            //PrintCurrent(maze, dist, current.x, current.y);

            pq.pop();

            for (const auto& direction : directions)
            {
                int newX = current.x + direction.first;
                int newY = current.y + direction.second;

                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && maze[newX][newY] == 0)
                {
                    int newDist = current.dist + 1;
                    if (newDist < dist[newX][newY])
                    {
                        dist[newX][newY] = newDist;

                        pq.push({ newX, newY, newDist });
                    }
                }
            }
        }

        PrintDistances(dist);

        return dist;
    }
}


namespace AStarTest
{
    struct Cell
    {
        int x, y, f, g, h;
        bool operator>(const Cell& other) const
        {
            return f > other.f;
        }
    };


    // 휴리스틱 함수 (맨해튼 거리)
    int heuristic(int x1, int y1, int x2, int y2)
    {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }

    // A* 알고리즘 함수

    std::vector<std::vector<int>> AStar(const std::vector<std::vector<int>>& maze, int startX, int startY, int goalX, int goalY)
    {
        int rows = maze.size();
        int cols = maze[0].size();
        std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, INF));

        dist[startX][startY] = 0;

        std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> open_list;

        std::unordered_set<int> closed_list;

        auto encode = [](int x, int y) { return x * 1000 + y; }; // 좌표를 코드로 변환

        open_list.push({ startX, startY, heuristic(startX, startY, goalX, goalY), 0, heuristic(startX, startY, goalX, goalY) });

        while (!open_list.empty())
        {
            Cell current = open_list.top();
            open_list.pop();

            int current_code = encode(current.x, current.y);

            if (current_code == encode(goalX, goalY)) break; // 목표 지점에 도달하면 종료


            if (closed_list.find(current_code) != closed_list.end())
            {
                continue; // 이미 닫힌 목록에 있는 노드는 무시
            }

            closed_list.insert(current_code);

            for (const auto& direction : directions)
            {
                int newX = current.x + direction.first;
                int newY = current.y + direction.second;

                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && maze[newX][newY] == 0)
                {
                    int newG = current.g + 1;
                    int newH = heuristic(newX, newY, goalX, goalY);
                    int newF = newG + newH;

                    if (newG < dist[newX][newY])
                    {
                        dist[newX][newY] = newG;
                        open_list.push({ newX, newY, newF, newG, newH });
                    }
                }
            }
        }

        PrintDistances(dist);

        return dist;
    }
}


int main()
{
    /*std::vector<std::vector<int>> maze = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };*/


    std::vector<std::vector<int>> maze = {
       {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
       {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
       {0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0},
       {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
       {0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0},
       {0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
       {0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
       {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
       {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
       {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
       {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0},
       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
       {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    };



    int startX = 0, startY = 0;
    int goalX = 19, goalY = 19;

    PrintMaze(maze);

    std::vector<std::vector<int>> distances = DijkstraTest::Dijkstra(maze, startX, startY);

    if (distances[goalX][goalY] == INF)
    {
        std::cout << "No path found from (" << startX << ", " << startY << ") to (" << goalX << ", " << goalY << ").\n";
    }
    else
    {
        std::cout << "Shortest distance from (" << startX << ", " << startY << ") to (" << goalX << ", " << goalY << ") is " << distances[goalX][goalY] << ".\n";
    }

    std::vector<std::vector<int>> distances2 = AStarTest::AStar(maze, startX, startY, goalX, goalY);


    if (distances2[goalX][goalY] == INF)
    {
        std::cout << "No path found from (" << startX << ", " << startY << ") to (" << goalX << ", " << goalY << ").\n";
    }
    else
    {
        std::cout << "Shortest distance from (" << startX << ", " << startY << ") to (" << goalX << ", " << goalY << ") is " << distances2[goalX][goalY] << ".\n";
    }


    return 0;
}