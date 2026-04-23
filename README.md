# Movie Data Manager 🎬

A high-performance, command-line dataset management system built entirely in C++ to parse, store, search, and map relationships within a large movie metadata dataset. 

This project was developed for the Data Structures course to demonstrate the practical application of advanced data structures, algorithmic efficiency, and manual memory management without relying on the C++ Standard Template Library (STL) for core structures.

## ⚙️ Core Data Structures Implemented

To optimize for different types of queries and relationships, the dataset (`movie_metadata.csv`) is parsed and distributed across several custom-built data structures:

* **AVL Tree (`movie_avl.h`):** Implemented for heavily read-dependent operations. Ensures the movie database remains strictly balanced, guaranteeing `O(log n)` time complexity for searching, inserting, and alphabetical sorting.
* **Hash Table (`hashtable.h`):** Built to handle rapid, exact-match lookups (e.g., searching for a specific movie ID or title) with an average time complexity of `O(1)`.
* **Graph (`graph.h`):** Utilized to map non-linear relationships between movies, such as generating recommendations based on shared actors, directors, or genres. 
* **Linked Lists & Queues (`LL.h`, `Queue.h`):** Utilized as foundational utility structures to handle Hash Table collision chaining and Graph traversals (BFS).

## 👨‍💻 My Contributions

*Note: This system was architected as a pair-programming academic project. Below are my specific engineering contributions to the codebase:*

* **AVL Tree Implementation (`movie_avl.h`):** Designed and implemented the self-balancing tree logic, including all rotation algorithms (LL, RR, LR, RL) to maintain strict `O(log n)` height for optimized searching.
* **Hash Table Architecture (`hashtable.h`):** Built the hashing logic and underlying arrays to enable rapid, constant-time `O(1)` data retrieval for exact-match movie queries.
* **Utility Structures (`LL.h`, `Queue.h`):** Engineered the custom Linked List structures to handle Hash Table collision chaining and the Queue structures required for data traversal.
* **Project Documentation:** Authored and compiled the attached project report (`project_report.pdf`).

## 🚀 How to Compile and Run

Ensure you have a C++ compiler (like `g++` via MinGW on Windows or GCC on Linux) installed.

1. Clone the repository:
   ```bash
   git clone [https://github.com/SaadAwan701/Movie-Data-Manager.git](https://github.com/SaadAwan701/Movie-Data-Manager.git)

2. Navigate to the directory:
   cd Movie-Data-Manager

3. Compile the source code:
   g++ main.cpp -o movie_manager

4. Run the executable:
   # On Windows
  movie_manager.exe
  # On Linux/macOS
  ./movie_manager
  
