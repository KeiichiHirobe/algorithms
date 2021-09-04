package main

// This code is written based on
// https://github.com/drken1215/book_algorithm_solution/blob/master/codes/chap14/code_14_4.cpp
// update value of element of priority queue.
import (
	"bufio"
	"container/heap"
	"fmt"
	"os"

	"github.com/algorithms/go/pqueue"
)

const INF int = 1 << 60

type Edge struct {
	to int
	w  int
}

type Graph = [][]Edge

func chmin(a *int, b *int) bool {
	if *a > *b {
		*a = *b
		return true
	}
	return false
}

type nodeValue struct {
	// ノード番号
	node int
	// 緩和される最短距離
	// 実装上、priorityはdを正負反転したものになっている
	d int
}

func upsert(q *pqueue.PriorityQueue, nodeItemMap []*pqueue.Item, value *nodeValue, priority int) {
	item := nodeItemMap[value.node]
	if item == nil {
		item = &pqueue.Item{
			Value:    value,
			Priority: priority,
		}
		// log(N)
		heap.Push(q, item)
		nodeItemMap[value.node] = item
	} else {
		item.Value = value
		item.Priority = priority
		// log(N)
		heap.Fix(q, item.Index)
	}
}

func main() {
	// Nは頂点数, Mは辺数、Sは始点ノード
	N, M, S := ReadInt(), ReadInt(), ReadInt()
	G := make(Graph, N)
	for i := 0; i < M; i++ {
		// a->b の辺がwの距離
		// a,bともに0-indexed
		a, b, w := ReadInt(), ReadInt(), Readint()
		G[a] = append(G[a], Edge{b, w})
	}
	// ダイクスクストラ
	dist := make([]int, N)
	for i, _ := range dist {
		dist[i] = INF
	}
	dist[S] = 0
	// node number to Item mapping. If empty, nil.
	nodeItemMap := make([]*pqueue.Item, N)
	var pq pqueue.PriorityQueue
	heap.Init(&pq)
	upsert(&pq, nodeItemMap, &nodeValue{S, 0}, -0)
	for pq.Len() > 0 {
		item := heap.Pop(&pq).(*pqueue.Item)
		value := item.Value.(*nodeValue)
		for _, v := range G[value.node] {
			d := value.d + v.w
			if chmin(&dist[v.to], &d) {
				// 更新があるならヒープに新たに挿入
				upsert(&pq, nodeItemMap, &nodeValue{v.to, d}, -d)
			}
		}
	}
	// 結果出力
	for v := 0; v < N; v++ {
		if dist[v] < INF {
			fmt.Println(dist[v])
		} else {
			fmt.Println("INF")
		}
	}
}

var reader = bufio.NewReader(os.Stdin)

func Scan(a ...interface{}) {
	if _, err := fmt.Fscan(reader, a...); err != nil {
		panic(err)
	}
}
func ReadInt() (i int) { Scan(&i); return }
func Readint() (i int) { Scan(&i); return }
