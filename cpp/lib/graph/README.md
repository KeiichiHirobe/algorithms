## 最短路について

## 始点固定
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

## 全頂点間の最短
* Floyd-Warshall
  * 負の重みあり
  * O(V^3)
  * 負閉路を検出可能

## bitDP
* 循環セールスマン
  * 始点から全ての点を1回ずつ通って始点に戻る最短距離
  * traveling_salesman.cpp/traveling_salesman_dp.cpp
  * O(V^2 * 2^V)で、V=20くらいまでいける
  * 愚直に計算すると、O(V!) V=10くらいまでならいける