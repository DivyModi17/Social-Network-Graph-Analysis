#ifndef DSU_H
#define DSU_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

class DSU {
public:
    unordered_map<string, string> parent;
    unordered_map<string, int> rank;

    void addNode(string x) {
        parent[x] = x;
        rank[x]   = 0;
    }

    string find(string x) {
        if (!parent.count(x)) return "";
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(string a, string b) {
        string rootA = find(a);
        string rootB = find(b);

        if (rootA == rootB) return;

        if (rank[rootA] < rank[rootB]) {
            parent[rootA] = rootB;
        } else if (rank[rootA] > rank[rootB]) {
            parent[rootB] = rootA;
        } else {
            parent[rootB] = rootA;
            rank[rootA]++;
        }
    }

    bool sameCommunity(string a, string b) {
        if (!parent.count(a) && !parent.count(b)) {
            cout << "Both users not found!\n";
            return false;
        }
        if (!parent.count(a)) {
            cout << "User " << a << " not found!\n";
            return false;
        }
        if (!parent.count(b)) {
            cout << "User " << b << " not found!\n";
            return false;
        }
        return find(a) == find(b);
    }

    unordered_map<string, vector<string>> getCommunities() {
        unordered_map<string, vector<string>> groups;
        for (auto& entry : parent) {
            string node = entry.first;
            string root = find(node);
            groups[root].push_back(node);
        }
        return groups;
    }

    void displayCommunities() {
        auto groups = getCommunities();

        if (groups.empty()) {
            cout << "No communities found!\n";
            return;
        }

        cout << "\n===== Communities Detected =====\n";
        int groupNum = 1;
        for (auto& entry : groups) {
            cout << "Group " << groupNum++ << ": ";
            for (auto& member : entry.second) {
                cout << member << " ";
            }
            cout << "\n";
        }
        cout << "Total communities: "
             << groups.size() << "\n";
    }
};

#endif
