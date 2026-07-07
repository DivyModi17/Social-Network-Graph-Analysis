#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <climits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Graph {
public:
    unordered_map<string, unordered_set<string>> adjList;

    void addUser(string name);
    void removeUser(string name);
    void addConnection(string a, string b);
    void removeConnection(string a, string b);
    bool isConnected(string a, string b);
    void displayConnections(string name);
    void displayAllUsers();

    void getMutualFriends(string a, string b);

    vector<string> shortestPath(string src, string dest);

    int degreesOfSeparation(string src, string dest);

    map<int, vector<string>> usersWithinNHops(string start, int n);

    void dfsArticulation(string u, string parent,
                         unordered_map<string, int>& disc,
                         unordered_map<string, int>& low,
                         unordered_set<string>& visited,
                         vector<string>& bridges,
                         int& timer);

    vector<string> findBridgeUsers();

    void suggestFriends(string user);

    void computePageRank(int iterations, double damping);

    void loadFromFile(string filename);

    void simulateMisinformation(string source, double probability);

    void saveToFile(string filename);
    
    void loadSavedNetwork(string filename);
};

#endif
