package pqueue

import (
	"container/heap"
	"testing"
)

func TestFromExamplePQTest(t *testing.T) {
	// Some items and their priorities.
	items := map[string]int{
		"banana": 3, "apple": 2, "pear": 4,
	}
	// Create a priority queue, put the items in it, and
	// establish the priority queue (heap) invariants.
	var pq PriorityQueue
	heap.Init(&pq)
	for value, priority := range items {
		heap.Push(&pq, &Item{
			Value:    value,
			Priority: priority,
		})
	}

	// Insert a new item and then modify its priority.
	item := &Item{
		Value:    "orange",
		Priority: 1,
	}
	heap.Push(&pq, item)
	item.Priority = 5
	heap.Fix(&pq, item.Index)
	wants := []struct {
		value    string
		priority int
	}{
		{
			"orange",
			5,
		},
		{
			"pear",
			4,
		},
		{
			"banana",
			3,
		},
		{
			"apple",
			2,
		},
	}

	for _, v := range wants {
		item := heap.Pop(&pq).(*Item)
		if item.Priority != v.priority || item.Value != v.value {
			t.Errorf("pop got %v; want %v", item.Value, v.value)
		}
	}

	if pq.Len() != 0 {
		t.Errorf("must be empty")
	}
}

type nodeValue struct {
	// ノード番号
	node int
	// 緩和される最短距離
	// 実装上、priorityはdを正負反転したものになっている
	d int
}

func upsert(q *PriorityQueue, nodeItemMap []*Item, value *nodeValue, priority int) {
	item := nodeItemMap[value.node]
	if item == nil {
		item = &Item{
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

func remove(q *PriorityQueue, nodeItemMap []*Item, value *nodeValue) {
	item := nodeItemMap[value.node]
	if item == nil {
		// unknown entry, do nothing
	} else {
		// log(N)
		heap.Remove(q, item.Index)
	}
}

// アルゴリズムとデータ構造のP.256の図14.9を再現
func TestTrackingUpdateP256(t *testing.T) {
	// N = 6
	// node number to Item mapping. If empty, nil.
	nodeItemMap := make([]*Item, 6)

	var pq PriorityQueue
	heap.Init(&pq)
	upsert(&pq, nodeItemMap, &nodeValue{1, 3}, -3)
	upsert(&pq, nodeItemMap, &nodeValue{2, 5}, -5)
	item := heap.Pop(&pq).(*Item)
	check(t, item, 1, 3)
	upsert(&pq, nodeItemMap, &nodeValue{3, 15}, -15)
	item = heap.Pop(&pq).(*Item)
	check(t, item, 2, 5)
	upsert(&pq, nodeItemMap, &nodeValue{3, 14}, -14)
	upsert(&pq, nodeItemMap, &nodeValue{4, 9}, -9)
	item = heap.Pop(&pq).(*Item)
	check(t, item, 4, 9)
	upsert(&pq, nodeItemMap, &nodeValue{5, 17}, -17)
	item = heap.Pop(&pq).(*Item)
	check(t, item, 3, 14)
	upsert(&pq, nodeItemMap, &nodeValue{5, 16}, -16)
	item = heap.Pop(&pq).(*Item)
	check(t, item, 5, 16)
	if pq.Len() != 0 {
		t.Errorf("must be empty")
	}
}

func TestTrackingUpdateOther(t *testing.T) {
	nodeItemMap := make([]*Item, 5)

	var pq PriorityQueue
	heap.Init(&pq)
	upsert(&pq, nodeItemMap, &nodeValue{0, 100}, -100)
	upsert(&pq, nodeItemMap, &nodeValue{1, 1}, -1)
	upsert(&pq, nodeItemMap, &nodeValue{2, 2}, -2)
	upsert(&pq, nodeItemMap, &nodeValue{3, 3}, -3)
	upsert(&pq, nodeItemMap, &nodeValue{4, 4}, -4)
	upsert(&pq, nodeItemMap, &nodeValue{4, 1}, -1)
	upsert(&pq, nodeItemMap, &nodeValue{3, 2}, -2)
	upsert(&pq, nodeItemMap, &nodeValue{2, 3}, -3)
	upsert(&pq, nodeItemMap, &nodeValue{1, 4}, -4)
	remove(&pq, nodeItemMap, &nodeValue{2, 3})

	item := heap.Pop(&pq).(*Item)
	check(t, item, 4, 1)
	item = heap.Pop(&pq).(*Item)
	check(t, item, 3, 2)
	item = heap.Pop(&pq).(*Item)
	check(t, item, 1, 4)
	item = heap.Pop(&pq).(*Item)
	check(t, item, 0, 100)
	if pq.Len() != 0 {
		t.Errorf("must be empty")
	}
}

func check(t *testing.T, item *Item, node int, d int) {
	value := item.Value.(*nodeValue)
	if value.node != node || value.d != d {
		t.Errorf("got %v; want node: %v, d: %v", *value, node, d)
	}
}
