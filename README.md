
<img width=100% src="https://capsule-render.vercel.app/api?type=waving&color=03800b&height=120&section=header"/>

[![Typing SVG](https://readme-typing-svg.herokuapp.com/?color=03800b&size=45&center=true&vCenter=true&width=1000&lines=CENTRAL+MAZE)](https://git.io/typing-svg)

## ❔ About

**Central Maze** is a maze game created in the **C** language for a course completion project **(Algorithms and Data Structures 2)**.

### Code Organization and Data Structures:
The code is organized and modularized using Abstract Data Types (ADTs) to facilitate maintenance and new implementations. Efficient data structures are employed in its development. The application includes the ADTs: tree, graph, stack, and ranking.

The program uses the Graph data structure in adjacency list format to represent the mazes, allowing users to navigate between vertices to reach an "exit" vertex while avoiding sinkholes.

### **Game Features**:

The game comprises two types of areas: common and central. The difference lies in their data structure, with the common area being an unweighted graph, while the central area is weighted.
In terms of gameplay, the central area allows users to return using their acquired points, whereas in the common area, reaching a sinkhole results in an instant loss.
Data Structure Usage:
The Tree data structure is used as a map for the graphs (mazes), ensuring that the central area is visited last. The game progresses through traversing the tree nodes, each representing a graph.

The program employs a player structure to store user information. This structure includes the player's name, accumulated points, and playtime. These data are later used in the ranking system.

### **Ranking and Sorting**:
The program uses a file to create a ranking, storing the top 10 positions sorted either by points or by the longest time spent in the Central Area. The ranking is organized using the Insertion Sort algorithm, efficiently sorting players in descending order based on the chosen criteria (time or points). This ensures that players with higher scores or times occupy higher positions in the ranking.

The progressive increase in the number of rooms (nodes) in each new area (level) adds complexity to the game incrementally. This can be visualized as a graph expansion, where each new level adds an additional node compared to the previous one. As depicted in the diagram, each node that increases complexity does so geometrically.

> [!Note]
> The program may not work very well on other operating systems, I'm sorry :(

## 🤝 Contributors
[![LucasPMartins](https://github.com/LucasPMartins.png?size=60)](https://github.com/LucasPMartins "LucasPMartins on GitHub")
[![pedrootrevisan](https://github.com/pedrootrevisan.png?size=60)](https://github.com/pedrootrevisan "Pedro Trevisan on GitHub")
[![CaueGrassi7](https://github.com/CaueGrassi7.png?size=60)](https://github.com/CaueGrassi7 "CaueGrassi7 on GitHub")

## 🛠 Tools:
![Visual Studio Code](https://img.shields.io/badge/-Visual%20Studio%20Code-0D1117?style=for-the-badge&logo=visual-studio-code&logoColor=007ACC&labelColor=0D1117)&nbsp;
![Git](https://img.shields.io/badge/-Git-0D1117?style=for-the-badge&logo=git&labelColor=0D1117)&nbsp;
![GitHub](https://img.shields.io/badge/-GitHub-0D1117?style=for-the-badge&logo=github&labelColor=0D1117)&nbsp;
![Windows](https://img.shields.io/badge/-Windows-0D1117?style=for-the-badge&logo=windows&logoColor=0a58ee)&nbsp;
![Replit](https://img.shields.io/badge/Replit-0D1117?style=for-the-badge&logo=Replit&logoColor=fc2c03)

## 👨‍💻 Programming Language
![C](https://img.shields.io/badge/c-0D1117?style=for-the-badge&logo=c&logoColor=0a58ee)

<table>
  <tr>
    <td>
      <img src="https://github.com/LucasPMartins/Tic-tac-toe-in-C/assets/127567616/b2856451-8b46-407f-8220-25fa68f36d37" alt="Imagem Maior 1" width="500" />
    </td>
    <td>
      <img src="https://github.com/LucasPMartins/Tic-tac-toe-in-C/assets/127567616/7f07158b-f6a5-4a61-add6-8990d89ecea7" alt="Imagem Maior 2" width="500" />
    </td>
  </tr>
</table>

<div align="center">
<table>
   <tr>
    <td text-align: center>
      <img src="https://github.com/LucasPMartins/Tic-tac-toe-in-C/assets/127567616/52b1d11a-d4fa-416c-a87f-ec9fef11d053" alt="Imagem 3" width="500" />
    </td>
  </tr>
</table>
</div>

<img width=100% src="https://capsule-render.vercel.app/api?type=waving&color=03800b&height=120&section=footer"/>

