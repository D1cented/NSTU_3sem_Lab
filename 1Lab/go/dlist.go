package main

import (
	"errors"
	"fmt"
	"strings"
)

type DNode struct {
	Val  string
	Prev *DNode
	Next *DNode
}

type DoublyLinkedList struct {
	Head *DNode
	Tail *DNode
}

func NewDoublyList() *DoublyLinkedList {
	return &DoublyLinkedList{}
}

// 4 способа добавления:
// 1. В голову
func (l *DoublyLinkedList) PushHead(val string) {
	newNode := &DNode{Val: val, Next: l.Head}
	if l.Head != nil {
		l.Head.Prev = newNode
	} else {
		l.Tail = newNode
	}
	l.Head = newNode
}

// 2. В хвост
func (l *DoublyLinkedList) PushTail(val string) {
	newNode := &DNode{Val: val, Prev: l.Tail}
	if l.Tail != nil {
		l.Tail.Next = newNode
	} else {
		l.Head = newNode
	}
	l.Tail = newNode
}

// 3. После значения
func (l *DoublyLinkedList) AddAfter(target, val string) error {
	curr := l.Head
	for curr != nil && curr.Val != target {
		curr = curr.Next
	}
	if curr == nil {
		return errors.New("элемент не найден")
	}
	newNode := &DNode{Val: val, Prev: curr, Next: curr.Next}
	if curr.Next != nil {
		curr.Next.Prev = newNode
	} else {
		l.Tail = newNode
	}
	curr.Next = newNode
	return nil
}

// 4. До значения
func (l *DoublyLinkedList) AddBefore(target, val string) error {
	curr := l.Head
	for curr != nil && curr.Val != target {
		curr = curr.Next
	}
	if curr == nil {
		return errors.New("элемент не найден")
	}
	newNode := &DNode{Val: val, Prev: curr.Prev, Next: curr}
	if curr.Prev != nil {
		curr.Prev.Next = newNode
	} else {
		l.Head = newNode
	}
	curr.Prev = newNode
	return nil
}

// 4 способа удаления:
// 1. Из головы
func (l *DoublyLinkedList) DelHead() error {
	if l.Head == nil {
		return errors.New("список пуст")
	}
	if l.Head == l.Tail {
		l.Head = nil
		l.Tail = nil
		return nil
	}
	l.Head = l.Head.Next
	l.Head.Prev = nil
	return nil
}

// 2. Из хвоста
func (l *DoublyLinkedList) DelTail() error {
	if l.Tail == nil {
		return errors.New("список пуст")
	}
	if l.Head == l.Tail {
		l.Head = nil
		l.Tail = nil
		return nil
	}
	l.Tail = l.Tail.Prev
	l.Tail.Next = nil
	return nil
}

// 3. По значению
func (l *DoublyLinkedList) DelVal(val string) error {
	curr := l.Head
	for curr != nil && curr.Val != val {
		curr = curr.Next
	}
	if curr == nil {
		return errors.New("элемент не найден")
	}
	if curr == l.Head {
		return l.DelHead()
	}
	if curr == l.Tail {
		return l.DelTail()
	}
	curr.Prev.Next = curr.Next
	curr.Next.Prev = curr.Prev
	return nil
}

// 4. Удаление после значения
func (l *DoublyLinkedList) DelAfter(target string) error {
	curr := l.Head
	for curr != nil && curr.Val != target {
		curr = curr.Next
	}
	if curr == nil || curr.Next == nil {
		return errors.New("нет элемента для удаления после указанного")
	}
	toDel := curr.Next
	if toDel == l.Tail {
		return l.DelTail()
	}
	curr.Next = toDel.Next
	toDel.Next.Prev = curr
	return nil
}

// Поиск
func (l *DoublyLinkedList) Search(val string) int {
	idx := 0
	curr := l.Head
	for curr != nil {
		if curr.Val == val {
			return idx
		}
		idx++
		curr = curr.Next
	}
	return -1
}

// Чтение в прямом порядке
func (l *DoublyLinkedList) Print() {
	var elements []string
	curr := l.Head
	for curr != nil {
		elements = append(elements, curr.Val)
		curr = curr.Next
	}
	fmt.Printf("Двусвязный список (вперед): [%s]\n", strings.Join(elements, " <-> "))
}

// Чтение в обратном порядке
func (l *DoublyLinkedList) PrintReverse() {
	var elements []string
	curr := l.Tail
	for curr != nil {
		elements = append(elements, curr.Val)
		curr = curr.Prev
	}
	fmt.Printf("Двусвязный список (назад):  [%s]\n", strings.Join(elements, " <-> "))
}

func (l *DoublyLinkedList) ToSlice() []string {
	var res []string
	curr := l.Head
	for curr != nil {
		res = append(res, curr.Val)
		curr = curr.Next
	}
	return res
}
