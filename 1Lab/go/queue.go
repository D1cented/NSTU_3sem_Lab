package main

import (
	"errors"
	"fmt"
)

type Queue struct {
	items []string
}

func NewQueue() *Queue {
	return &Queue{items: make([]string, 0)}
}

func (q *Queue) Push(val string) {
	q.items = append(q.items, val)
}

func (q *Queue) Pop() (string, error) {
	if len(q.items) == 0 {
		return "", errors.New("очередь пуста")
	}
	val := q.items[0]
	q.items = q.items[1:]
	return val, nil
}

func (q *Queue) Peek() (string, error) {
	if len(q.items) == 0 {
		return "", errors.New("очередь пуста")
	}
	return q.items[0], nil
}

func (q *Queue) Print() {
	fmt.Printf("Очередь (Front -> Back): %v\n", q.items)
}
