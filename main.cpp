#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Graph.h"
#include "DSU.h"

using namespace std;

int main() {
    Graph g;
    DSU dsu;
    int choice;

    while (true) {
        cout << "\n===== Social Network =====\n";
        cout << "1.  Add User\n";
        cout << "2.  Remove User\n";
        cout << "3.  Add Connection\n";
        cout << "4.  Remove Connection\n";
        cout << "5.  Check if Connected\n";
        cout << "6.  Display User Connections\n";
        cout << "7.  Display All Users\n";
        cout << "8.  Mutual Friends\n";
        cout << "9.  Users Within N Hops\n";
        cout << "10. Shortest Connection Path\n";
        cout << "11. Degrees of Separation\n";
        cout << "12. Detect Communities\n";
        cout << "13. Check Same Community\n";
        cout << "14. Find Bridge Users\n";
        cout << "15. Friend Suggestions\n";
        cout << "16. Influencer Ranking\n";
        cout << "17. Simulate Misinformation\n";
        cout << "18. Load Stanford Dataset\n";
        cout << "19. Save Network\n";
        cout << "20. Restore Network\n";
        cout << "21. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            cout << "Enter username: ";
            cin >> name;
            g.addUser(name);
            dsu.addNode(name);
        }
        else if (choice == 2) {
            string name;
            cout << "Enter username to remove: ";
            cin >> name;
            g.removeUser(name);
        }
        else if (choice == 3) {
            string a, b;
            cout << "Enter first username: ";
            cin >> a;
            cout << "Enter second username: ";
            cin >> b;
            g.addConnection(a, b);
            dsu.unite(a, b);
        }
        else if (choice == 4) {
            string a, b;
            cout << "Enter first username: ";
            cin >> a;
            cout << "Enter second username: ";
            cin >> b;
            g.removeConnection(a, b);
        }
        else if (choice == 5) {
            string a, b;
            cout << "Enter first username: ";
            cin >> a;
            cout << "Enter second username: ";
            cin >> b;
            if (g.isConnected(a, b))
                cout << a << " and " << b
                     << " ARE connected!\n";
            else
                cout << a << " and " << b
                     << " are NOT connected.\n";
        }
        else if (choice == 6) {
            string name;
            cout << "Enter username: ";
            cin >> name;
            g.displayConnections(name);
        }
        else if (choice == 7) {
            g.displayAllUsers();
        }
        else if (choice == 8) {
            string a, b;
            cout << "Enter first username: ";
            cin >> a;
            cout << "Enter second username: ";
            cin >> b;
            g.getMutualFriends(a, b);
        }
        else if (choice == 9) {
            string name;
            int n;
            cout << "Enter username: ";
            cin >> name;
            cout << "Enter N (hops): ";
            cin >> n;

            map<int, vector<string>> hops = g.usersWithinNHops(name, n);

            if (hops.empty()) {
                cout << "No users found within "
                     << n << " hops of " << name << "!\n";
            } else {
                cout << "\nUsers within " << n
                     << " hops of " << name << ":\n";
                int total = 0;
                for (auto& entry : hops) {
                    cout << "Hop " << entry.first << ": ";
                    for (auto& user : entry.second)
                        cout << user << "  ";
                    cout << "\n";
                    total += entry.second.size();
                }
                cout << "Total: " << total
                     << " user(s) reachable within "
                     << n << " hops\n";
            }
        }
        else if (choice == 10) {
            string a, b;
            cout << "Enter starting user: ";
            cin >> a;
            cout << "Enter destination user: ";
            cin >> b;
            g.shortestPath(a, b);
        }
        else if (choice == 11) {
            string a, b;
            cout << "Enter first user: ";
            cin >> a;
            cout << "Enter second user: ";
            cin >> b;
            g.degreesOfSeparation(a, b);
        }
        else if (choice == 12) {
            dsu.displayCommunities();
        }
        else if (choice == 13) {
            string a, b;
            cout << "Enter first username: ";
            cin >> a;
            cout << "Enter second username: ";
            cin >> b;
            if (dsu.sameCommunity(a, b))
                cout << a << " and " << b
                     << " are in SAME community!\n";
            else
                cout << a << " and " << b
                     << " are in DIFFERENT communities!\n";
        }
        else if (choice == 14) {
            vector<string> bridges = g.findBridgeUsers();
            if (!bridges.empty()) {
                cout << "\n===== Bridge User Detection =====\n";
                cout << "Bridge Users Found: "
                     << bridges.size() << "\n\n";
                for (auto& user : bridges) {
                    cout << " ! " << user
                         << " is a critical connection point\n";
                    cout << "    Removing this user would "
                         << "disconnect parts of the network!\n";
                }
            }
        }
        else if (choice == 15) {
            string name;
            cout << "Enter username: ";
            cin >> name;
            g.suggestFriends(name);
        }
            else if (choice == 16) {
        cout << "Enter iterations (recommended 20): ";
        int iter;
        cin >> iter;
        g.computePageRank(iter, 0.85);
    }

            else if (choice == 17) {
            string source;
            double prob;
            cout << "Enter source user: ";
            cin >> source;
            cout << "Enter spread probability (0.1 to 1.0): ";
            cin >> prob;
            g.simulateMisinformation(source, prob);
        }

        else if (choice == 18) {
        g.loadFromFile("facebook_combined.txt");
    }
        else if (choice == 19) {
            string filename;
            cout << "Enter filename (e.g. network.txt): ";
            cin >> filename;
            g.saveToFile(filename);
        }
        else if (choice == 20) {
            string filename;
            cout << "Enter filename to restore from: ";
            cin >> filename;
            g.loadSavedNetwork(filename);
        }
        else if (choice == 21) {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}
