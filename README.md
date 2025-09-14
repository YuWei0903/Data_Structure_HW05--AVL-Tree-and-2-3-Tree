# Data_Structure_HW05--AVL-Tree-and-2-3-Tree
Use C++ to implement a data structure program.  
Write a program with the C++ to implement AVL tree and 2-3 tree operations including insertion, deletion, and tree printing.  

本專案使用 C++ 實作 AVL 樹與 2-3 樹，包括整數插入、刪除與樹狀結構列印。程式先輸入多個整數建立樹，之後互動操作」。  

**輸入格式**  
輸入整數數量（輸入 -1 停止）：  
val1  
val2  
...  
valN  
之後操作：  
輸入值插入 AVL 樹：val  
輸入值刪除 AVL 樹：val  
輸入值插入 2-3 樹：val  
輸入值刪除 2-3 樹：val  

**輸出範例**  
輸入 (建立AVL tree)：  
10  
20  
25  
31  
60  
100  
254  
256  
1  
-1  

輸出：  
*AVL Tree:  
  *Root: 25  
    *L: 10  
      *L: 1  
      *R: 20  
    *R: 60  
      *L: 31  
      *R: 254  
        *L: 100  
        *R: 256  

新增數值至AVL tree：11  
AVL Tree:  
  Root: 25  
    L: 10  
      L: 1  
      R: 20  
        L: 11  
    R: 60  
      L: 31  
      R: 254  
        L: 100  
        R: 256  
...
