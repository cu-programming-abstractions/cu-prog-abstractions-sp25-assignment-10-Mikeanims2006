#include "knight.h"
#include <algorithm>
#include <cmath>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// 8 possible knight moves
const vector<pair<int, int>> directions = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

//minKnightMoves
int minKnightMoves(const Pos& start, const Pos& target) {
    if (start == target) return 0;

    unordered_set<Pos, PosHash> visited;
    queue<pair<Pos, int>> q;  // pair<position, moves>
    q.push({start, 0});
    visited.insert(start);

    while (!q.empty()) {
        auto [curr, dist] = q.front(); q.pop();

        for (auto [dr, dc] : directions) {
            Pos next = {curr.row + dr, curr.col + dc};
            if (next == target) return dist + 1;

            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push({next, dist + 1});
            }
        }
    }

    return -1; // Should never reach here on infinite board
}

//getKnightPath
vector<Pos> getKnightPath(const Pos& start, const Pos& target) {
    if (start == target) return {start};

    unordered_map<Pos, Pos, PosHash> parent;
    unordered_set<Pos, PosHash> visited;
    queue<Pos> q;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        Pos curr = q.front(); q.pop();

        for (auto [dr, dc] : directions) {
            Pos next = {curr.row + dr, curr.col + dc};

            if (visited.find(next) != visited.end())
                continue;

            parent[next] = curr;
            visited.insert(next);
            q.push(next);

            if (next == target) {
                // Reconstruct path
                vector<Pos> path;
                for (Pos p = target; p != start; p = parent[p])
                    path.push_back(p);
                path.push_back(start);
                reverse(path.begin(), path.end());
                return path;
            }
        }
    }

    return {}; // Shouldn't happen on infinite board
}

//isValidPosition
bool isValidPosition(const Pos& pos, int boardSize) {
    if (boardSize == -1) return true; // Infinite board
    return pos.row >= 0 && pos.row < boardSize &&
           pos.col >= 0 && pos.col < boardSize;
}
