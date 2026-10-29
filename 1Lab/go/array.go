package main

import (
	"errors"
	"fmt"
)

type DynamicArray struct {
	data []string
}

func NewArray() *DynamicArray {
	return &DynamicArray{data: make([]string, 0)}
}

// Добавление в конец
func (a *DynamicArray) PushBack(val string) {
	a.data = append(a.data, val)
}

// Вставка по индексу
func (a *DynamicArray) Insert(idx int, val string) error {
	if idx < 0 || idx > len(a.data) {
		return errors.New("индекс вне диапазона")
	}
	a.data = append(a.data, "")
	copy(a.data[idx+1:], a.data[idx:])
	a.data[idx] = val
	return nil
}

// Получение по индексу
func (a *DynamicArray) Get(idx int) (string, error) {
	if idx < 0 || idx >= len(a.data) {
		return "", errors.New("индекс вне диапазона")
	}
	return a.data[idx], nil
}

// Удаление по индексу
func (a *DynamicArray) Delete(idx int) error {
	if idx < 0 || idx >= len(a.data) {
		return errors.New("индекс вне диапазона")
	}
	a.data = append(a.data[:idx], a.data[idx+1:]...)
	return nil
}

// Замена по индексу
func (a *DynamicArray) Set(idx int, val string) error {
	if idx < 0 || idx >= len(a.data) {
		return errors.New("индекс вне диапазона")
	}
	a.data[idx] = val
	return nil
}

// Длина
func (a *DynamicArray) Len() int {
	return len(a.data)
}

// Чтение/Вывод
func (a *DynamicArray) Print() {
	fmt.Printf("Массив (длина %d): %v\n", len(a.data), a.data)
}
