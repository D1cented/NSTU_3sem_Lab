package main

import (
	"fmt"
	"strings"
)

type TreeNode struct {
	Val   string
	Left  *TreeNode
	Right *TreeNode
}

type CompleteBinaryTree struct {
	Root *TreeNode
}

func NewCompleteBinaryTree() *CompleteBinaryTree {
	return &CompleteBinaryTree{}
}

// Вставка с сохранением свойства Complete Binary Tree (по уровням слева направо)
func (t *CompleteBinaryTree) Insert(val string) {
	newNode := &TreeNode{Val: val}
	if t.Root == nil {
		t.Root = newNode
		return
	}

	queue := []*TreeNode{t.Root}
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]

		if curr.Left == nil {
			curr.Left = newNode
			return
		} else {
			queue = append(queue, curr.Left)
		}

		if curr.Right == nil {
			curr.Right = newNode
			return
		} else {
			queue = append(queue, curr.Right)
		}
	}
}

// Поиск значения в дереве (BFS)
func (t *CompleteBinaryTree) Search(val string) bool {
	if t.Root == nil {
		return false
	}
	queue := []*TreeNode{t.Root}
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		if curr.Val == val {
			return true
		}
		if curr.Left != nil {
			queue = append(queue, curr.Left)
		}
		if curr.Right != nil {
			queue = append(queue, curr.Right)
		}
	}
	return false
}

// Проверка: является ли дерево полным двоичным деревом (Complete Binary Tree)
func (t *CompleteBinaryTree) IsComplete() bool {
	if t.Root == nil {
		return true
	}
	queue := []*TreeNode{t.Root}
	seenNonFullNode := false

	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]

		if curr.Left != nil {
			if seenNonFullNode {
				return false
			}
			queue = append(queue, curr.Left)
		} else {
			seenNonFullNode = true
		}

		if curr.Right != nil {
			if seenNonFullNode {
				return false
			}
			queue = append(queue, curr.Right)
		} else {
			seenNonFullNode = true
		}
	}
	return true
}

// Чтение/Обход дерева (Level-order)
func (t *CompleteBinaryTree) Print() {
	if t.Root == nil {
		fmt.Println("Дерево пусто")
		return
	}
	fmt.Println("Complete Binary Tree (Обход по уровням):")
	queue := []*TreeNode{t.Root}
	level := 0
	for len(queue) > 0 {
		levelSize := len(queue)
		var levelVals []string
		for i := 0; i < levelSize; i++ {
			curr := queue[0]
			queue = queue[1:]
			levelVals = append(levelVals, curr.Val)
			if curr.Left != nil {
				queue = append(queue, curr.Left)
			}
			if curr.Right != nil {
				queue = append(queue, curr.Right)
			}
		}
		fmt.Printf(" Уровень %d: %s\n", level, strings.Join(levelVals, " | "))
		level++
	}
}

// Для сохранения в файл
func (t *CompleteBinaryTree) ToSlice() []string {
	var res []string
	if t.Root == nil {
		return res
	}
	queue := []*TreeNode{t.Root}
	for len(queue) > 0 {
		curr := queue[0]
		queue = queue[1:]
		res = append(res, curr.Val)
		if curr.Left != nil {
			queue = append(queue, curr.Left)
		}
		if curr.Right != nil {
			queue = append(queue, curr.Right)
		}
	}
	return res
}
