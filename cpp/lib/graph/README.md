## 最短路について

### 始点固定

- Bellman–Ford
  - 負の重みあり
  - 閉路あり可
  - 始点から到達可能な負閉路を検出可能
  - O(V\*E)
  - bellman_ford.cpp
- Dijkstra
  - 辺の重みが非負の場
  - 閉路あり可
  - ナイーブ実装 O(V^2) priority queue の実装は O(E\*logV)
  - 密なグラフは前者の方がむしろ早い
  - dijkstra.cpp/dijkstra_pqueue.cpp
- トポロジーソート後に DP
  - DAG
  - O(V + E)
  - topology_sort_dp.cpp
- 幅優先
  - 重みなし(常に 1)
  - O(V + E)
  - template.cpp

### 全頂点間の最短

- Floyd-Warshall
  - 負の重みあり
  - O(V^3)
  - 負閉路を検出可能

### 最小全域木

- 連結な重み付きグラフに対して、全頂点をつなぐ全域木のなかで重みが最小なもの
- クラスカル法
- 辺の重みを小さい順にソートして、サイクルができなければ追加していくことで得られる
- O(E\*logV)

## bitDP

- 循環セールスマン
  - 始点から全ての点を 1 回ずつ通って始点に戻る最短距離
  - traveling_salesman.cpp/traveling_salesman_dp.cpp
  - O(V^2 \* 2^V)で、V=20 くらいまでいける
  - 愚直に計算すると、O(V!) V=10 くらいまでならいける

## サイクル検出

### サイクルの列挙が不要な場合

- 無向グラフ
  - union_find で、unite 前に既に同値であればサイクル
- 有向グラフ
  - BFS の topological sort が途中で終わってしまったらサイクル
  - topological_sort_bfs.cpp
  - DFS の topological sort はサイクルがないこと(DAG)を前提としているため、検出できない
  - https://algo-logic.info/topological-sort/

### サイクルの列挙が必要な場合
サイクルの列挙の仕方による

- 無向グラフ
  - サイクルの列挙の単位を何にするかが難しい
  -  辺を共有するサイクルを1つとカウントし、外側のサイクルを列挙する。∞のような点だけ共有するサイクルを想定しないのであればlowlinkが同じノードがサイクルを形成する
  - DFSにおいてv->xとして辿ったのを戻る時に、ord[v] = low[x] であればサイクルであると検知することにすると∞を必ず2つと判断できそうではあるが、不確か
  - lowlink.cpp

- 有向グラフ
  - 点や辺を共有するサイクルは1つとしてカウントし、∞は1つのサイクルとみなすのであれば、sccで同じ連結成分をサイクルとして列挙できる
  - lowlink_scc.cpp

- 無向グラフの場合は連結成分、有向グラフの場合は弱連結成分(任意の頂点に対して向きを無視するとどちらかにはパスがある)に 1 つ以下のサイクルがあるというゆるい条件であれば楽に実装できる
  - 帰りがけ順で訪れる前に行きがけ順で再度訪れたことからサイクルを検出して、辿り戻していく
  - 検出だけであればグラフに条件は不要と思われる
  - cycle_find.cpp

## 強連結成分分解

- scc.cpp
- 任意の頂点 s,t について、s->t,t->s で辿れる頂点集合を作る

## 木の性質

- 直径
  - 木の頂点間の最大距離を木の直径と呼ぶ
  - 任意の頂点から最も遠い頂点は木の直径の端点である
  - https://algo-logic.info/tree-diameter/
  - tree_diameter.cpp

- lcc
  - 最近共通祖先（LCA：Lowest Common Ancestor) をダブリングで求めることができる
  - 事前計算 O(NlogN),クエリO(logN)
  - https://algo-logic.info/lca/
  - LCAが求められれば、以下が可能
    - 任意の2頂点間の距離が分かる
    - 頂点がある２頂点のパス上にあるか判定できる
  - tree_lca.cpp