package main

import (
	"errors"
	"fmt"
	"strings"
)

type SNode struct {
	Val  string
	Next *SNode
}

type SinglyLinkedList struct {
	Head *SNode
}

func NewSinglyList() *SinglyLinkedList {
	return &SinglyLinkedList{}
}

// 4 способа добавления:
// 1. В голову
func (l *SinglyLinkedList) PushHead(val string) {
	newNode := &SNode{Val: val, Next: l.Head}
	l.Head = newNode
}

// 2. В хвост
func (l *SinglyLinkedList) PushTail(val string) {
	newNode := &SNode{Val: val}
	if l.Head == nil {
		l.Head = newNode
		return
	}
	curr := l.Head
	for curr.Next != nil {
		curr = curr.Next
	}
	curr.Next = newNode
}

// 3. После значения
func (l *SinglyLinkedList) AddAfter(target, val string) error {
	curr := l.Head
	for curr != nil && curr.Val != target {
		curr = curr.Next
	}
	if curr == nil {
		return errors.New("элемент не найден")
	}
	newNode := &SNode{Val: val, Next: curr.Next}
	curr.Next = newNode
	return nil
}

// 4. До значения
func (l *SinglyLinkedList) AddBefore(target, val string) error {
	if l.Head == nil {
		return errors.New("список пуст")
	}
	if l.Head.Val == target {
		l.PushHead(val)
		return nil
	}
	curr := l.Head
	for curr.Next != nil && curr.Next.Val != target {
		curr = curr.Next
	}
	if curr.Next == nil {
		return errors.New("элемент не найден")
	}
	newNode := &SNode{Val: val, Next: curr.Next}
	curr.Next = newNode
	return nil
}

// 4 способа удаления:
// 1. Из головы
func (l *SinglyLinkedList) DelHead() error {
	if l.Head == nil {
		return errors.New("список пуст")
	}
	l.Head = l.Head.Next
	return nil
}

// 2. Из хвоста
func (l *SinglyLinkedList) DelTail() error {
	if l.Head == nil {
		return errors.New("список пуст")
	}
	if l.Head.Next == nil {
		l.Head = nil
		return nil
	}
	curr := l.Head
	for curr.Next.Next != nil {
		curr = curr.Next
	}
	curr.Next = nil
	return nil
}

// 3. Удаление по значению
func (l *SinglyLinkedList) DelVal(val string) error {
	if l.Head == nil {
		return errors.New("список пуст")
	}
	if l.Head.Val == val {
		l.Head = l.Head.Next
		return nil
	}
	curr := l.Head
	for curr.Next != nil && curr.Next.Val != val {
		curr = curr.Next
	}
	if curr.Next == nil {
		return errors.New("элемент не найден")
	}
	curr.Next = curr.Next.Next
	return nil
}

// 4. Удаление после заданного значения
func (l *SinglyLinkedList) DelAfter(target string) error {
	curr := l.Head
	for curr != nil && curr.Val != target {
		curr = curr.Next
	}
	if curr == nil || curr.Next == nil {
		return errors.New("нет элемента для удаления после указанного")
	}
	curr.Next = curr.Next.Next
	return nil
}

// Поиск по значению
func (l *SinglyLinkedList) Search(val string) int {
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

// Чтение/Вывод (прямой обход)
func (l *SinglyLinkedList) Print() {
	var elements []string
	curr := l.Head
	for curr != nil {
		elements = append(elements, curr.Val)
		curr = curr.Next
	}
	fmt.Printf("Односвязный список: [%s]\n", strings.Join(elements, " -> "))
}

// Преобразование в слайс для сохранения
func (l *SinglyLinkedList) ToSlice() []string {
	var res []string
	curr := l.Head
	for curr != nil {
		res = append(res, curr.Val)
		curr = curr.Next
	}
	return res
}
