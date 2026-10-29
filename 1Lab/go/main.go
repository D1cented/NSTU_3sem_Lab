package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

const storageFile = "data.json"

func printHelp() {
	fmt.Println("\nДоступные команды:")
	fmt.Println(" --- МАССИВ (M) ---")
	fmt.Println("  MPUSH <val>            - Добавить в конец")
	fmt.Println("  MINSERT <idx> <val>    - Добавить по индексу")
	fmt.Println("  MGET <idx>             - Чтение по индексу")
	fmt.Println("  MDEL <idx>             - Удаление по индексу")
	fmt.Println("  MSET <idx> <val>       - Замена по индексу")
	fmt.Println("  MLEN                   - Длина массива")
	fmt.Println(" --- ОДНОСВЯЗНЫЙ СПИСОК (F) ---")
	fmt.Println("  FPUSH_HEAD <val>       - Добавить в голову")
	fmt.Println("  FPUSH_TAIL <val>       - Добавить в хвост")
	fmt.Println("  FADD_AFTER <tgt> <val> - Добавить после элемента")
	fmt.Println("  FADD_BEFORE <tgt> <val>- Добавить до элемента")
	fmt.Println("  FDEL_HEAD              - Удалить из головы")
	fmt.Println("  FDEL_TAIL              - Удалить из хвоста")
	fmt.Println("  FDEL_VAL <val>         - Удалить по значению")
	fmt.Println("  FDEL_AFTER <tgt>       - Удалить после элемента")
	fmt.Println("  FFIND <val>            - Поиск по значению")
	fmt.Println(" --- ДВУСВЯЗНЫЙ СПИСОК (L) ---")
	fmt.Println("  LPUSH_HEAD <val>       - Добавить в голову")
	fmt.Println("  LPUSH_TAIL <val>       - Добавить в хвост")
	fmt.Println("  LADD_AFTER <tgt> <val> - Добавить после элемента")
	fmt.Println("  LADD_BEFORE <tgt> <val>- Добавить до элемента")
	fmt.Println("  LDEL_HEAD              - Удалить из головы")
	fmt.Println("  LDEL_TAIL              - Удалить из хвоста")
	fmt.Println("  LDEL_VAL <val>         - Удалить по значению")
	fmt.Println("  LDEL_AFTER <tgt>       - Удалить после элемента")
	fmt.Println("  LFIND <val>            - Поиск по значению")
	fmt.Println("  LREV                   - Чтение в обратном порядке")
	fmt.Println(" --- СТЕК (S) ---")
	fmt.Println("  SPUSH <val>            - Положить в стек")
	fmt.Println("  SPOP                   - Извлечь из стека")
	fmt.Println("  SGET                   - Посмотреть вершину стека")
	fmt.Println(" --- ОЧЕРЕДЬ (Q) ---")
	fmt.Println("  QPUSH <val>            - Добавить в очередь")
	fmt.Println("  QPOP                   - Извлечь из очереди")
	fmt.Println("  QGET                   - Посмотреть начало очереди")
	fmt.Println(" --- COMPLETE BINARY TREE (T) ---")
	fmt.Println("  TINSERT <val>          - Добавить в дерево")
	fmt.Println("  TFIND <val>            - Поиск в дереве")
	fmt.Println("  TCHECK                 - Проверка дерева на Complete")
	fmt.Println(" --- ОБЩИЕ ---")
	fmt.Println("  PRINT [M|F|L|S|Q|T]    - Вывести указанную структуру (или все, если без параметров)")
	fmt.Println("  HELP                   - Справка")
	fmt.Println("  EXIT                   - Выход")
}

func main() {
	arr := NewArray()
	slist := NewSinglyList()
	dlist := NewDoublyList()
	stack := NewStack()
	queue := NewQueue()
	tree := NewCompleteBinaryTree()

	// Загрузка состояния из файла
	if err := LoadData(storageFile, arr, slist, dlist, stack, queue, tree); err != nil {
		fmt.Printf("Предупреждение: ошибка загрузки данных (%v)\n", err)
	} else {
		fmt.Println("Состояние успешно загружено из файла:", storageFile)
	}

	save := func() {
		if err := SaveData(storageFile, arr, slist, dlist, stack, queue, tree); err != nil {
			fmt.Printf("Ошибка сохранения: %v\n", err)
		}
	}

	scanner := bufio.NewScanner(os.Stdin)
	fmt.Println("Программа инициализирована. Введите HELP для справки.")

	for {
		fmt.Print("\n> ")
		if !scanner.Scan() {
			break
		}
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}
		parts := strings.Fields(line)
		cmd := strings.ToUpper(parts[0])

		switch cmd {
		case "EXIT":
			fmt.Println("Завершение работы.")
			return
		case "HELP":
			printHelp()

		// --- PRINT ---
		case "PRINT":
			target := ""
			if len(parts) > 1 {
				target = strings.ToUpper(parts[1])
			}
			switch target {
			case "M":
				arr.Print()
			case "F":
				slist.Print()
			case "L":
				dlist.Print()
			case "S":
				stack.Print()
			case "Q":
				queue.Print()
			case "T":
				tree.Print()
			default:
				arr.Print()
				slist.Print()
				dlist.Print()
				stack.Print()
				queue.Print()
				tree.Print()
			}

		// --- ARRAY (M) ---
		case "MPUSH":
			if len(parts) < 2 {
				fmt.Println("Использование: MPUSH <val>")
				continue
			}
			arr.PushBack(parts[1])
			save()
			fmt.Println("Элемент добавлен.")
		case "MINSERT":
			if len(parts) < 3 {
				fmt.Println("Использование: MINSERT <idx> <val>")
				continue
			}
			idx, err := strconv.Atoi(parts[1])
			if err != nil || arr.Insert(idx, parts[2]) != nil {
				fmt.Println("Ошибка: некорректный индекс.")
				continue
			}
			save()
			fmt.Println("Элемент вставлен.")
		case "MGET":
			if len(parts) < 2 {
				fmt.Println("Использование: MGET <idx>")
				continue
			}
			idx, _ := strconv.Atoi(parts[1])
			val, err := arr.Get(idx)
			if err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				fmt.Println("Значение:", val)
			}
		case "MDEL":
			if len(parts) < 2 {
				fmt.Println("Использование: MDEL <idx>")
				continue
			}
			idx, _ := strconv.Atoi(parts[1])
			if err := arr.Delete(idx); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Элемент удален.")
			}
		case "MSET":
			if len(parts) < 3 {
				fmt.Println("Использование: MSET <idx> <val>")
				continue
			}
			idx, _ := strconv.Atoi(parts[1])
			if err := arr.Set(idx, parts[2]); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Элемент заменен.")
			}
		case "MLEN":
			fmt.Println("Длина массива:", arr.Len())

		// --- SINGLY LIST (F) ---
		case "FPUSH_HEAD":
			if len(parts) < 2 {
				fmt.Println("Использование: FPUSH_HEAD <val>")
				continue
			}
			slist.PushHead(parts[1])
			save()
			fmt.Println("Добавлено в голову списка.")
		case "FPUSH_TAIL", "FPUSH":
			if len(parts) < 2 {
				fmt.Println("Использование: FPUSH_TAIL <val>")
				continue
			}
			slist.PushTail(parts[1])
			save()
			fmt.Println("Добавлено в хвост списка.")
		case "FADD_AFTER":
			if len(parts) < 3 {
				fmt.Println("Использование: FADD_AFTER <tgt> <val>")
				continue
			}
			if err := slist.AddAfter(parts[1], parts[2]); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Элемент добавлен.")
			}
		case "FADD_BEFORE":
			if len(parts) < 3 {
				fmt.Println("Использование: FADD_BEFORE <tgt> <val>")
				continue
			}
			if err := slist.AddBefore(parts[1], parts[2]); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Элемент добавлен.")
			}
		case "FDEL_HEAD":
			if err := slist.DelHead(); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Голова удалена.")
			}
		case "FDEL_TAIL":
			if err := slist.DelTail(); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Хвост удален.")
			}
		case "FDEL_VAL", "FDEL":
			if len(parts) < 2 {
				fmt.Println("Использование: FDEL_VAL <val>")
				continue
			}
			if err := slist.DelVal(parts[1]); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Элемент удален.")
			}
		case "FDEL_AFTER":
			if len(parts) < 2 {
				fmt.Println("Использование: FDEL_AFTER <tgt>")
				continue
			}
			if err := slist.DelAfter(parts[1]); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Элемент удален.")
			}
		case "FFIND":
			if len(parts) < 2 {
				fmt.Println("Использование: FFIND <val>")
				continue
			}
			pos := slist.Search(parts[1])
			if pos != -1 {
				fmt.Printf("Элемент найден на позиции: %d\n", pos)
			} else {
				fmt.Println("Элемент не найден.")
			}

		// --- DOUBLY LIST (L) ---
		case "LPUSH_HEAD":
			if len(parts) < 2 {
				fmt.Println("Использование: LPUSH_HEAD <val>")
				continue
			}
			dlist.PushHead(parts[1])
			save()
			fmt.Println("Добавлено в голову списка.")
		case "LPUSH_TAIL", "LPUSH":
			if len(parts) < 2 {
				fmt.Println("Использование: LPUSH_TAIL <val>")
				continue
			}
			dlist.PushTail(parts[1])
			save()
			fmt.Println("Добавлено в хвост списка.")
		case "LADD_AFTER":
			if len(parts) < 3 {
				fmt.Println("Использование: LADD_AFTER <tgt> <val>")
				continue
			}
			if err := dlist.AddAfter(parts[1], parts[2]); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Элемент добавлен.")
			}
		case "LADD_BEFORE":
			if len(parts) < 3 {
				fmt.Println("Использование: LADD_BEFORE <tgt> <val>")
				continue
			}
			if err := dlist.AddBefore(parts[1], parts[2]); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Элемент добавлен.")
			}
		case "LDEL_HEAD":
			if err := dlist.DelHead(); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Голова удалена.")
			}
		case "LDEL_TAIL":
			if err := dlist.DelTail(); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Хвост удален.")
			}
		case "LDEL_VAL", "LDEL":
			if len(parts) < 2 {
				fmt.Println("Использование: LDEL_VAL <val>")
				continue
			}
			if err := dlist.DelVal(parts[1]); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Элемент удален.")
			}
		case "LDEL_AFTER":
			if len(parts) < 2 {
				fmt.Println("Использование: LDEL_AFTER <tgt>")
				continue
			}
			if err := dlist.DelAfter(parts[1]); err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Элемент удален.")
			}
		case "LFIND":
			if len(parts) < 2 {
				fmt.Println("Использование: LFIND <val>")
				continue
			}
			pos := dlist.Search(parts[1])
			if pos != -1 {
				fmt.Printf("Элемент найден на позиции: %d\n", pos)
			} else {
				fmt.Println("Элемент не найден.")
			}
		case "LREV":
			dlist.PrintReverse()

		// --- STACK (S) ---
		case "SPUSH":
			if len(parts) < 2 {
				fmt.Println("Использование: SPUSH <val>")
				continue
			}
			stack.Push(parts[1])
			save()
			fmt.Println("Помещено в стек.")
		case "SPOP":
			val, err := stack.Pop()
			if err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Извлечено из стека:", val)
			}
		case "SGET":
			val, err := stack.Peek()
			if err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				fmt.Println("Вершина стека:", val)
			}

		// --- QUEUE (Q) ---
		case "QPUSH":
			if len(parts) < 2 {
				fmt.Println("Использование: QPUSH <val>")
				continue
			}
			queue.Push(parts[1])
			save()
			fmt.Println("Помещено в очередь.")
		case "QPOP":
			val, err := queue.Pop()
			if err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				save()
				fmt.Println("Извлечено из очереди:", val)
			}
		case "QGET":
			val, err := queue.Peek()
			if err != nil {
				fmt.Println("Ошибка:", err)
			} else {
				fmt.Println("Начало очереди:", val)
			}

		// --- TREE (T) ---
		case "TINSERT":
			if len(parts) < 2 {
				fmt.Println("Использование: TINSERT <val>")
				continue
			}
			tree.Insert(parts[1])
			save()
			fmt.Println("Узел добавлен в дерево с сохранением Complete-структуры.")
		case "TFIND":
			if len(parts) < 2 {
				fmt.Println("Использование: TFIND <val>")
				continue
			}
			if tree.Search(parts[1]) {
				fmt.Println("Элемент найден в дереве.")
			} else {
				fmt.Println("Элемент не найден.")
			}
		case "TCHECK":
			if tree.IsComplete() {
				fmt.Println("Результат: Дерево является полным (Complete Binary Tree).")
			} else {
				fmt.Println("Результат: Дерево НЕ является полным (Not Complete).")
			}

		default:
			fmt.Println("Неизвестная команда. Введите HELP.")
		}
	}
}
