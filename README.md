# Social Network Graph Analysis

A C++ based Social Network Simulator that uses graph algorithms to model and analyze relationships between users. The project supports operations like friend recommendations, shortest path discovery, community detection, PageRank-based influencer ranking, bridge user detection, and misinformation spread simulation.

---

## Features

- Add and remove users
- Create and remove friendships
- Display user connections
- Find mutual friends
- Shortest path between two users
- Degrees of separation
- Users within N hops
- Community detection using Disjoint Set Union (DSU)
- Bridge user detection
- Friend recommendation system
- Influencer ranking using PageRank
- Misinformation spread simulation
- Load real-world Facebook dataset
- Save and restore social network

---

## Algorithms Used

- Breadth First Search (BFS)
- Depth First Search (DFS)
- Disjoint Set Union (Union Find)
- PageRank Algorithm
- Graph Traversal
- Connected Components
- Bridge Detection

---

## Technologies Used

- C++
- STL
- Graph Data Structure
- Queue
- Stack
- Hash Map
- Unordered Map
- File Handling

---

## Project Structure

```
.
├── main.cpp
├── Graph.cpp
├── Graph.h
├── DSU.h
├── facebook_combined.txt
└── README.md
```

---

## How to Run

1. Clone the repository

```
git clone https://github.com/DivyModi17/Social-Network-Graph-Analysis.git
```

2. Open the project in VS Code.

3. Compile

```
g++ main.cpp Graph.cpp -o SocialNetwork
```

4. Run

```
./SocialNetwork
```

---

## Dataset

This project uses the Facebook Combined Dataset for testing graph algorithms and social network analysis.

---

## Future Improvements

- Graph visualization
- GUI Interface
- User authentication
- Database integration
- Real-time messaging
- Better recommendation algorithm

---

