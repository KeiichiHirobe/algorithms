## 最短路について

### 始点固定
* Bellman–Ford
  * 負の重みあり
  * 閉路あり可
  * 始点から到達可能な負閉路を検出可能
  * O(V*E)
  * bellman_ford.cpp
* Dijkstra
  * 辺の重みが非負の場
  * 閉路あり可
  * ナイーブ実装 O(V^2) priority queueの実装は O(E*logV)
  * 密なグラフは前者の方がむしろ早い
  * dijkstra.cpp/dijkstra_pqueue.cpp
* トポロジーソート後にDP
  * DAG
  * O(V + E)
  * topology_sort_dp.cpp
* 幅優先
  * 重みなし(常に1)
  * O(V + E)
  * template.cpp

### 全頂点間の最短
* Floyd-Warshall
  * 負の重みあり
  * O(V^3)
  * 負閉路を検出可能

### 最小全域木
 * 連結な重み付きグラフに対して、全頂点をつなぐ全域木のなかで重みが最小なもの
 * クラスカル法
  * 辺の重みを小さい順にソートして、サイクルができなければ追加していくことで得られる
  * O(E*logV)

## bitDP
* 循環セールスマン
  * 始点から全ての点を1回ずつ通って始点に戻る最短距離
  * traveling_salesman.cpp/traveling_salesman_dp.cpp
  * O(V^2 * 2^V)で、V=20くらいまでいける
  * 愚直に計算すると、O(V!) V=10くらいまでならいける

## サイクル検出
### サイクルの列挙が不要な場合
* 無向グラフ
  * union_findで、unite前に既に同値であればサイクル
* 有向グラフ
  * BFSのtopological sortが途中で終わってしまったらサイクル
  * topological_sort_bfs.cpp
  * DFSのtopological sortはサイクルがないこと(DAG)を前提としているため、検出できない
  * https://algo-logic.info/topological-sort/
### サイクルの列挙が必要な場合
* 一般には難しいのでグラフに条件が必要
* 無向グラフの場合は連結成分、有向グラフの場合は弱連結成分(任意の頂点に対してs->tもしくはt->sどちらかにはパスがある)に1つ以下のサイクルがあるという条件
  * 帰りがけ順で訪れる前に行きがけ順で再度訪れたことからサイクルを検出して、辿り戻していく
  * 検出だけであればグラフに条件は不要と思われる
  * cycle_find.cpp


## 強連結成分分解
* scc.cpp
* 任意の頂点s,tについて、s->t,t->sで辿れる頂点集合を作る