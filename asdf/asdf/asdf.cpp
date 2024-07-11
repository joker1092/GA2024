#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void BFS(int start, const std::vector<std::vector<int>>& list) {
  
    int v = list.size();
    std::vector<bool> visited(v, false);
    std::queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        //visited[node] = true;
        for (int b : list[node]) {
            if (!visited[b]) {
                visited[b] = true;
                q.push(b);
            }
        }
    }
}

int main()
{
    vector<vector<int>> adj_list =
    {
        {0, 1, 2},
        {1, 0, 2, 3},
        {2, 0, 1},
        {3, 1}
    };

    cout << "BFS: ";
    BFS(0, adj_list);
    cout << endl;

    return 0;
}