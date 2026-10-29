package main

import (
	"errors"
	"fmt"
)

type Stack struct {
	items []string
}

func NewStack() *Stack {
	return &Stack{items: make([]string, 0)}
}

func (s *Stack) Push(val string) {
	s.items = append(s.items, val)
}

func (s *Stack) Pop() (string, error) {
	if len(s.items) == 0 {
		return "", errors.New("стек пуст")
	}
	lastIdx := len(s.items) - 1
	val := s.items[lastIdx]
	s.items = s.items[:lastIdx]
	return val, nil
}

func (s *Stack) Peek() (string, error) {
	if len(s.items) == 0 {
		return "", errors.New("стек пуст")
	}
	return s.items[len(s.items)-1], nil
}

func (s *Stack) Print() {
	fmt.Printf("Стек (Top -> Bottom): %v\n", s.items)
}
