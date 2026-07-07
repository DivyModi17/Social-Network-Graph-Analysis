#include "Graph.h"
#include <algorithm>

void Graph::addUser(string name) {
    if (adjList.count(name)) {
        cout << name << " already exists!\n";
        return;
    }
    adjList[name];
    cout << name << " added successfully!\n";
}

void Graph::removeUser(string name) {
    if (!adjList.count(name)) {
        cout << name << " not found!\n";
        return;
    }
    for (auto& neighbor : adjList[name]) {
        adjList[neighbor].erase(name);
    }
    adjList.erase(name);
    cout << name << " removed successfully!\n";
}

void Graph::addConnection(string a, string b) {
    if (!adjList.count(a) && !adjList.count(b)) {
        cout << "Both users not found!\n";
        return;
    }
    else if (!adjList.count(a)) {
        cout << "User " << a << " not found!\n";
        return;
    }
    else if (!adjList.count(b)) {
        cout << "User " << b << " not found!\n";
        return;
    }
    if (a == b) {
        cout << "Cannot connect user to themselves!\n";
        return;
    }
    if (adjList[a].count(b)) {
        cout << a << " and " << b << " are already friends!\n";
        return;
    }
    adjList[a].insert(b);
    adjList[b].insert(a);
    cout << "Connection added between "
         << a << " and " << b << "!\n";
}

void Graph::removeConnection(string a, string b) {
    if (!adjList.count(a) && !adjList.count(b)) {
        cout << "Both users not found!\n";
        return;
    }
    else if (!adjList.count(a)) {
        cout << "User " << a << " not found!\n";
        return;
    }
    else if (!adjList.count(b)) {
        cout << "User " << b << " not found!\n";
        return;
    }
    if (!adjList[a].count(b)) {
        cout << a << " and " << b << " are not friends!\n";
        return;
    }
    adjList[a].erase(b);
    adjList[b].erase(a);
    cout << "Connection removed between "
         << a << " and " << b << "!\n";
}

bool Graph::isConnected(string a, string b) {
    if (!adjList.count(a) && !adjList.count(b)) {
        cout << "Both users not found!\n";
        return false;
    }
    else if (!adjList.count(a)) {
        cout << "User " << a << " not found!\n";
        return false;
    }
    else if (!adjList.count(b)) {
        cout << "User " << b << " not found!\n";
        return false;
    }
    return adjList[a].count(b) > 0;
}

void Graph::displayConnections(string name) {
    if (!adjList.count(name)) {
        cout << name << " not found!\n";
        return;
    }
    if (adjList[name].empty()) {
        cout << name << " has no connections yet.\n";
        return;
    }
    cout << name << "'s friends: ";
    for (auto& neighbor : adjList[name]) {
        cout << neighbor << " ";
    }
    cout << "\n";
}

void Graph::displayAllUsers() {
    if (adjList.empty()) {
        cout << "Network is empty!\n";
        return;
    }
    cout << "\nAll users in network:\n";
    cout << "----------------------\n";
    int i = 1;
    for (auto& entry : adjList) {
        cout << i++ << ". " << entry.first
             << "  (" << entry.second.size()
             << " friends)\n";
    }
}

void Graph::getMutualFriends(string a, string b) {
    if (!adjList.count(a)) {
        cout << a << " not found!\n";
    }
    if (!adjList.count(b)) {
        cout << b << " not found!\n";
    }
    if (a == b) {
        cout << "Both users are the same person!\n";
    }
    if (adjList[a].empty() || adjList[b].empty()) {
        cout << a << " or " << b << " has no friends yet — no mutuals possible!\n";
    }

    const unordered_set<string>* smaller = &adjList[a];
    const unordered_set<string>* bigger  = &adjList[b];

    if (adjList[a].size() > adjList[b].size()) {
        swap(smaller, bigger);
    }

    vector<string> mutual;
    for (const string& person : *smaller) {
        if (person == a || person == b) continue;
        if (bigger->count(person)) {
            mutual.push_back(person);
        }
    }

    sort(mutual.begin(), mutual.end());

    cout << "Mutual friends are: ";
    for (int i = 0; i < mutual.size(); i++) {
        cout << mutual[i] << " ";
    }
}

vector<string> Graph::shortestPath(string src, string dest) {
    if (!adjList.count(src) && !adjList.count(dest)) {
        cout << "Both users not found!\n";
        return {};
    }
    else if (!adjList.count(src)) {
        cout << "User " << src << " not found!\n";
        return {};
    }
    else if (!adjList.count(dest)) {
        cout << "User " << dest << " not found!\n";
        return {};
    }
    if (src == dest) {
        cout << "Same user!\n";
        return {src};
    }

    queue<string> q;
    unordered_map<string, string> parent;
    unordered_set<string> visited;

    q.push(src);
    visited.insert(src);
    parent[src] = "";

    bool found = false;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        for (auto& neighbor : adjList[current]) {
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                parent[neighbor] = current;
                q.push(neighbor);

                if (neighbor == dest) {
                    found = true;
                    break;
                }
            }
        }
        if (found) break;
    }

    if (!found) {
        cout << src << " and " << dest
             << " are not connected!\n";
        return {};
    }

    vector<string> path;
    string current = dest;

    while (current != "") {
        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    cout << "\nShortest path from "
         << src << " to " << dest << ":\n";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1)
            cout << " -> ";
    }
    cout << "\n";
    cout << "Total connections: "
         << path.size() - 1 << "\n";

    return path;
}

int Graph::degreesOfSeparation(string src, string dest) {
    if (!adjList.count(src) && !adjList.count(dest)) {
        cout << "Both users not found!\n";
        return -1;
    }
    else if (!adjList.count(src)) {
        cout << "User " << src << " not found!\n";
        return -1;
    }
    else if (!adjList.count(dest)) {
        cout << "User " << dest << " not found!\n";
        return -1;
    }
    if (src == dest) {
        cout << "Same user — 0 degrees of separation!\n";
        return 0;
    }

    queue<string> q;
    unordered_map<string, int> distance;

    q.push(src);
    distance[src] = 0;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        for (auto& neighbor : adjList[current]) {
            if (!distance.count(neighbor)) {
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);

                if (neighbor == dest) {
                    cout << "\n" << src << " and " << dest
                         << " are " << distance[neighbor]
                         << " degree(s) of separation apart.\n";
                    return distance[neighbor];
                }
            }
        }
    }

    cout << src << " and " << dest
         << " are not connected!\n";
    return -1;
}

map<int, vector<string>> Graph::usersWithinNHops(string start, int n) {
    map<int, vector<string>> result;

    if (!adjList.count(start)) {
        cout << start << " not found!\n";
        return result;
    }
    if (n <= 0) {
        cout << "Hops must be at least 1!\n";
        return result;
    }
    if (adjList[start].empty()) {
        cout << start << " has no connections — no one reachable!\n";
        return result;
    }
    if (n > (int)adjList.size()) {
        cout << "Note: N exceeds network size. Showing all reachable users.\n";
        n = (int)adjList.size();
    }

    unordered_map<string, int> dist;
    queue<string> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        for (auto& neighbor : adjList[current]) {
            if (!dist.count(neighbor)) {
                int hopDistance = dist[current] + 1;

                if (hopDistance <= n) {
                    dist[neighbor] = hopDistance;
                    result[hopDistance].push_back(neighbor);
                    q.push(neighbor);
                }
            }
        }
    }

    if (result.empty()) {
        cout << "No users reachable from " << start
             << " within " << n << " hops.\n";
    }

    return result;
}

void Graph::dfsArticulation(string u, string parent,
                             unordered_map<string, int>& disc,
                             unordered_map<string, int>& low,
                             unordered_set<string>& visited,
                             vector<string>& bridges,
                             int& timer) {
    visited.insert(u);
    disc[u] = low[u] = timer++;

    int childCount = 0;
    bool isBridge = false;

    for (auto& neighbor : adjList[u]) {
        if (!visited.count(neighbor)) {
            childCount++;
            dfsArticulation(neighbor, u, disc, low,
                           visited, bridges, timer);

            low[u] = min(low[u], low[neighbor]);

            
            if (parent == "" && childCount > 1)
                isBridge = true;

            
            if (parent != "" && low[neighbor] >= disc[u])
                isBridge = true;

        } else if (neighbor != parent) {
            low[u] = min(low[u], disc[neighbor]);
        }
    }

    if (isBridge)
        bridges.push_back(u);
}

vector<string> Graph::findBridgeUsers() {
    vector<string> bridges;

    if (adjList.empty()) {
        cout << "Network is empty!\n";
        return bridges;
    }
    if (adjList.size() == 1) {
        cout << "Only one user in network — no bridges possible!\n";
        return bridges;
    }

    unordered_map<string, int> disc;
    unordered_map<string, int> low;
    unordered_set<string> visited;
    int timer = 0;

    for (auto& entry : adjList) {
        if (!visited.count(entry.first)) {
            dfsArticulation(entry.first, "",
                           disc, low,
                           visited, bridges, timer);
        }
    }

    if (bridges.empty()) {
        cout << "No bridge users found — ";
        cout << "network is fully resilient!\n";
    }

    return bridges;
}

void Graph::suggestFriends(string user) {

    
    if (!adjList.count(user)) {
        cout << user << " not found!\n";
        return;
    }
    if (adjList[user].empty()) {
        cout << user << " has no friends yet"
             << " — can't suggest anyone!\n";
        return;
    }

    unordered_set<string> directFriends;
    for (auto& f : adjList[user])
        directFriends.insert(f);


    unordered_map<string, int> score;

    for (auto& f : adjList[user]) {
        for (auto& ff : adjList[f]) {

           
            if (ff == user) continue;

            
            if (directFriends.count(ff)) continue;

            
            score[ff]++;
        }
    }

    
    if (score.empty()) {
        cout << "No suggestions for " << user
             << " — everyone nearby is already connected!\n";
        return;
    }


    vector<pair<int, string>> ranked;
    for (auto& entry : score)
        ranked.push_back({entry.second, entry.first});


    sort(ranked.begin(), ranked.end(), [](
        const pair<int, string>& a,
        const pair<int, string>& b) {
            if (a.first != b.first)
                return a.first > b.first;
            return a.second < b.second;
    });

    
    cout << "\n===== Friend Suggestions for "
         << user << " =====\n";

    for (int i = 0; i < ranked.size(); i++) {
        cout << i + 1 << ". " << ranked[i].second;

        if (ranked[i].first == 1)
            cout << "  --  1 mutual friend\n";
        else
            cout << "  --  " << ranked[i].first
                 << " mutual friends\n";
    }

    cout << "Total suggestions: "
         << ranked.size() << "\n";
}

void Graph::computePageRank(int iterations = 20, double damping = 0.85) {

    
    if (adjList.empty()) {
        cout << "Network is empty!\n";
        return;
    }

    
    if (adjList.size() == 1) {
        cout << "Only one user — ranking not meaningful!\n";
        return;
    }

    
    unordered_map<string, double> score;
    unordered_map<string, double> newScore;

    for (auto& entry : adjList) {
        score[entry.first] = 1.0;
    }

    
    for (int i = 0; i < iterations; i++) {

        
        for (auto& entry : adjList) {
            newScore[entry.first] = 0.0;
        }

        
        for (auto& entry : adjList) {
            string user = entry.first;
            int friendCount = entry.second.size();


            if (friendCount == 0) {
                newScore[user] += 0.0;
                continue;
            }

            double contribution = score[user] / friendCount;

            for (auto& neighbor : entry.second) {
                newScore[neighbor] += contribution;
            }
        }

        
        for (auto& entry : adjList) {
            string user = entry.first;
            newScore[user] = (1.0 - damping)
                           + damping * newScore[user];
        }

      
        score = newScore;
    }

    
    vector<pair<double, string>> ranked;
    for (auto& entry : score) {
        ranked.push_back({entry.second, entry.first});
    }
    sort(ranked.rbegin(), ranked.rend());

    
    cout << "\n===== Influencer Ranking (PageRank) =====\n";
    cout << "Iterations : " << iterations << "\n";
    cout << "Damping    : " << damping << "\n\n";

    cout << "Rank  User             Score      Friends\n";
    cout << "----  ---------------  ---------  -------\n";

    int rank = 1;
    for (auto& entry : ranked) {
        double s = entry.first;
        string user = entry.second;
        int friends = adjList[user].size();

        cout << rank++ << ".    "
             << user;

        
        int padding = 17 - user.size();
        for (int i = 0; i < padding; i++) cout << " ";

        cout << s;

        
        cout << "\t   " << friends << "\n";
    }

    cout << "\nMost Influential: "
         << ranked[0].second << "\n";


    vector<string> bridges = findBridgeUsers();
    unordered_set<string> bridgeSet(bridges.begin(),
                                     bridges.end());

   
    int topCount = max(1, (int)(ranked.size() * 0.3));
    vector<string> superspreaders;

    for (int i = 0; i < topCount; i++) {
        string user = ranked[i].second;
        if (bridgeSet.count(user)) {
            superspreaders.push_back(user);
        }
    }

    if (!superspreaders.empty()) {
        cout << "\n Superspreaders Detected:\n";
        for (auto& user : superspreaders) {
            cout << "  ! " << user
                 << " — high influence + bridge user\n";
        }
    }
}

void Graph::loadFromFile(string filename) {
    ifstream file(filename);

   
    if (!file.is_open()) {
        cout << "Error: Could not open file: "
             << filename << "\n";
        cout << "Make sure the file is in the "
             << "correct folder!\n";
        return;
    }

    cout << "Loading dataset...\n";

    int edgeCount = 0;
    int userCount = 0;
    string line;

    while (getline(file, line)) {

       
        if (line.empty() || line[0] == '#')
            continue;

        
        istringstream ss(line);
        string a, b;

        if (!(ss >> a >> b))
            continue;

        
        if (!adjList.count(a)) {
            adjList[a];
            userCount++;
        }
        if (!adjList.count(b)) {
            adjList[b];
            userCount++;
        }

        
        if (!adjList[a].count(b)) {
            adjList[a].insert(b);
            adjList[b].insert(a);
            edgeCount++;
        }
    }

    file.close();

    cout << "Dataset loaded successfully!\n";
    cout << "Users loaded     : " << userCount << "\n";
    cout << "Connections loaded: " << edgeCount << "\n";
}

void Graph::simulateMisinformation(string source, double probability) {

    if (adjList.empty()) {
        cout << "Network is empty!\n";
        return;
    }
    if (!adjList.count(source)) {
        cout << "User " << source << " not found!\n";
        return;
    }
    if (probability <= 0.0 || probability > 1.0) {
        cout << "Probability must be between 0 and 1!\n";
        return;
    }
    if (adjList[source].empty()) {
        cout << source << " has no connections!\n";
        return;
    }

    srand(time(0));

    queue<string> q;
    unordered_set<string> infected;

    q.push(source);
    infected.insert(source);

    int round = 0;
    int totalInfected = 1;

    cout << "\n===== Misinformation Spread Simulator =====\n";
    cout << "Source user       : " << source << "\n";
    cout << "Spread probability: " << probability << "\n";
    cout << "Network size      : " << adjList.size() << "\n";
    cout << "\nRunning simulation...\n\n";

    while (!q.empty()) {
        round++;
        int levelSize = q.size();
        int newlyInfected = 0;

        for (int i = 0; i < levelSize; i++) {
            string current = q.front();
            q.pop();

            for (auto& neighbor : adjList[current]) {
                if (infected.count(neighbor))
                    continue;

                double roll = (double)rand() / RAND_MAX;

                if (roll < probability) {
                    infected.insert(neighbor);
                    q.push(neighbor);
                    newlyInfected++;
                    totalInfected++;
                }
            }
        }

        if (newlyInfected > 0) {
            cout << "Round " << round
                 << " — Newly infected: "
                 << newlyInfected << " users\n";
        }
    }

    double percentage = ((double)totalInfected
                        / adjList.size()) * 100.0;

    cout << "\n--- Simulation Complete ---\n";
    cout << "Total infected : " << totalInfected
         << " / " << adjList.size() << " users\n";
    cout << "Spread depth   : " << round << " rounds\n";
    cout << "Infection rate : " << percentage << "%\n";

    if (percentage > 50.0)
        cout << "Severity: CRITICAL!\n";
    else if (percentage > 20.0)
        cout << "Severity: HIGH\n";
    else if (percentage > 5.0)
        cout << "Severity: MODERATE\n";
    else
        cout << "Severity: LOW\n";
}

void Graph::saveToFile(string filename) {

    
    if (adjList.empty()) {
        cout << "Network is empty — nothing to save!\n";
        return;
    }

    ofstream file(filename);

   
    if (!file.is_open()) {
        cout << "Error: Could not create file: "
             << filename << "\n";
        return;
    }

    
    unordered_set<string> written;

   
    for (auto& entry : adjList) {
        string user = entry.first;
        for (auto& neighbor : entry.second) {


            string edgeKey = (user < neighbor)
                           ? user + " " + neighbor
                           : neighbor + " " + user;

            if (!written.count(edgeKey)) {
                file << user << " "
                     << neighbor << "\n";
                written.insert(edgeKey);
            }
        }
    }


    for (auto& entry : adjList) {
        if (entry.second.empty()) {
            file << entry.first << "\n";
        }
    }

    file.close();

    cout << "Network saved to "
         << filename << "!\n";
    cout << "Users saved      : "
         << adjList.size() << "\n";
    cout << "Connections saved: "
         << written.size() << "\n";
}

void Graph::loadSavedNetwork(string filename) {

    ifstream file(filename);


    if (!file.is_open()) {
        cout << "Error: Could not open file: "
             << filename << "\n";
        return;
    }

    adjList.clear();
    cout << "Previous network cleared.\n";
    cout << "Loading saved network...\n";

    int userCount = 0;
    int edgeCount = 0;
    string line;

    while (getline(file, line)) {

        
        if (line.empty()) continue;

        istringstream ss(line);
        string a, b;
        ss >> a;

       
        if (ss >> b) {
            if (!adjList.count(a)) {
                adjList[a];
                userCount++;
            }
            if (!adjList.count(b)) {
                adjList[b];
                userCount++;
            }
            if (!adjList[a].count(b)) {
                adjList[a].insert(b);
                adjList[b].insert(a);
                edgeCount++;
            }
        }
        
        else {
            if (!adjList.count(a)) {
                adjList[a];
                userCount++;
            }
        }
    }

    file.close();

    cout << "Network restored successfully!\n";
    cout << "Users loaded      : " << userCount << "\n";
    cout << "Connections loaded: " << edgeCount << "\n";
}
