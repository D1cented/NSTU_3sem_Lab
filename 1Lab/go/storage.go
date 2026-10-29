package main

import (
	"encoding/json"
	"os"
)

type DataStorage struct {
	Array []string `json:"array"`
	SList []string `json:"slist"`
	DList []string `json:"dlist"`
	Stack []string `json:"stack"`
	Queue []string `json:"queue"`
	Tree  []string `json:"tree"`
}

func SaveData(filename string, arr *DynamicArray, sl *SinglyLinkedList, dl *DoublyLinkedList, st *Stack, q *Queue, tr *CompleteBinaryTree) error {
	data := DataStorage{
		Array: arr.data,
		SList: sl.ToSlice(),
		DList: dl.ToSlice(),
		Stack: st.items,
		Queue: q.items,
		Tree:  tr.ToSlice(),
	}

	bytes, err := json.MarshalIndent(data, "", "  ")
	if err != nil {
		return err
	}
	return os.WriteFile(filename, bytes, 0644)
}

func LoadData(filename string, arr *DynamicArray, sl *SinglyLinkedList, dl *DoublyLinkedList, st *Stack, q *Queue, tr *CompleteBinaryTree) error {
	bytes, err := os.ReadFile(filename)
	if err != nil {
		if os.IsNotExist(err) {
			return nil // Файла ещё нет, стартуем пустыми
		}
		return err
	}

	var data DataStorage
	if err := json.Unmarshal(bytes, &data); err != nil {
		return err
	}

	arr.data = data.Array
	for _, v := range data.SList {
		sl.PushTail(v)
	}
	for _, v := range data.DList {
		dl.PushTail(v)
	}
	st.items = data.Stack
	q.items = data.Queue
	for _, v := range data.Tree {
		tr.Insert(v)
	}
	return nil
}
