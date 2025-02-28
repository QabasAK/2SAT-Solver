# 2SAT Solver using Tarjan's Algorithm
A **C++** implementation of a 2-SAT solver. It constructs an **implication graph** from the 2-SAT clauses and uses **Tarjan's Algorithm** to find Strongly Connected Components (SCCs).

### Overview
2-SAT is a special case of **Boolean satisfiability** where each clause contains **exactly two literals**. The goal is to determine whether there exists a valid truth assignment that satisfies all clauses. An implication graph is constructed and then the strongly connected components (SCC) are found:
+ If a variable and its negation are in the **same SCC**, return unsatisfiable.
+ Otherwise, return satisfiable.

Finding Valid Assignments:
+ If no contradictions exist, SCCs are processed in **reverse topological order** to assign values.
  
This problem can be efficiently solved in $`O(n + m)`$ time, where $n$ is the number of **variables** and $m$ is the number of **clauses**.

### Example
Starting with a **CNF** of exactly two literals in every clause.
<p align="center">
   <img src="https://github.com/user-attachments/assets/d2c43dab-dcb3-42d2-8e6c-4a14fa5af6ca" alt="2SATCNF">

Each variable is identified by its subscript **(e.g. $`x_1`$, $`x_2`$)** and the sign (positive or negative) indicates whether the literal refers to the variable itself or its negation.
```
formula = {{1, 2}, {-2, 3}, {-1, -2}, {3, 4}, {-3, 5}, {-4, -5}, {-3, 4}};
```
For **$n$** Boolean variables, the implication graph needs **$2n$** nodes, one for the *variable* and the other for its *negation*. 

For a clause like **$\left( x \lor y \right)$**, you need to capture what happens if **$x$** is false (forcing **$y$** to be true) and vice versa.
+ **$\neg x \to y$**
+ **$\neg y \to x$**

Afterwards, Tarjan's Algorithm is used to find SCCs. If a variable and its negation appear in the same SCC, they are mutually dependent (a **contradiction**) meaning the formula is **unsatisfiable**.

<p align="center">
   <img src="https://github.com/user-attachments/assets/c7b7d7c0-2884-4369-ac5a-49132461d8a6" alt="ImplicationGraph" width=40%>
 </p>
 
 This approach handles 2-SAT formulae using a **single DFS pass**.
 
 ### TL;DR
 SAT is <3
