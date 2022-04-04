## 最短路について

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