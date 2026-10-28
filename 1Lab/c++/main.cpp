#include <iostream>
#include <sstream>
#include <vector>
#include "Array.h"
#include "SinglyList.h"
#include "DoublyList.h"
#include "Stack.h"
#include "Queue.h"
#include "CompleteBinaryTree.h"

// Константы имен файлов для автосохранения
const std::string FILE_ARRAY = "data_array.txt";
const std::string FILE_SLIST = "data_slist.txt";
const std::string FILE_DLIST = "data_dlist.txt";
const std::string FILE_STACK = "data_stack.txt";
const std::string FILE_QUEUE = "data_queue.txt";
const std::string FILE_TREE  = "data_tree.txt";

void printHelp() {
    std::cout << "\n================= Список команд =================\n"
              << " Массив (M):\n"
              << "   MPUSH <val>                 - Добавить в конец\n"
              << "   MPUSH <idx> <val>           - Добавить по индексу\n"
              << "   MDEL <idx>                  - Удалить по индексу\n"
              << "   MGET <idx>                  - Получить по индексу\n"
              << "   MSET <idx> <val>            - Заменить по индексу\n"
              << "   MLEN                        - Длина массива\n\n"
              << " Односвязный список (F):\n"
              << "   FPUSH HEAD|TAIL <val>       - Добавить в голову/хвост\n"
              << "   FPUSH BEFORE|AFTER <t> <v>  - Добавить до/после элемента <t>\n"
              << "   FDEL HEAD|TAIL              - Удалить голову/хвост\n"
              << "   FDEL BEFORE|AFTER <target>  - Удалить до/после элемента <target>\n"
              << "   FDEL VAL <val>              - Удалить по значению\n"
              << "   FGET <idx>                  - Получить по индексу\n"
              << "   FSEARCH <val>               - Найти индекс элемента\n\n"
              << " Двусвязный список (L):\n"
              << "   LPUSH HEAD|TAIL <val>       - Добавить в голову/хвост\n"
              << "   LPUSH BEFORE|AFTER <t> <v>  - Добавить до/после элемента <t>\n"
              << "   LDEL HEAD|TAIL              - Удалить голову/хвост\n"
              << "   LDEL BEFORE|AFTER <target>  - Удалить до/после элемента <target>\n"
              << "   LDEL VAL <val>              - Удалить по значению\n"
              << "   LGET <idx>                  - Получить по индексу\n"
              << "   LSEARCH <val>               - Найти индекс элемента\n\n"
              << " Стек (S):\n"
              << "   SPUSH <val>                 - Положить в стек\n"
              << "   SPOP                        - Извлечь из стека\n"
              << "   SGET                        - Посмотреть вершину стека\n\n"
              << " Очередь (Q):\n"
              << "   QPUSH <val>                 - Добавить в очередь\n"
              << "   QPOP                        - Извлечь из очереди\n"
              << "   QGET                        - Посмотреть начало очереди\n\n"
              << " Дерево (T - Complete Binary Tree):\n"
              << "   TINSERT <val>               - Вставить узел\n"
              << "   TSEARCH <val>               - Поиск значения\n"
              << "   TCHECK                      - Проверить, является ли Complete Tree\n"
              << "   TGET                        - Чтение обходов дерева\n\n"
              << " Универсальный вывод:\n"
              << "   PRINT <M|F|L|S|Q|T>         - Вывести структуру на экран\n"
              << "   EXIT                        - Выход из программы\n"
              << "=================================================\n\n";
}

int main() {
    MyArray arr;
    SinglyList slist;
    DoublyList dlist;
    MyStack stack;
    MyQueue queue;
    CompleteBinaryTree tree;

    // Загрузка начальных данных из файлов
    arr.loadFromFile(FILE_ARRAY);
    slist.loadFromFile(FILE_SLIST);
    dlist.loadFromFile(FILE_DLIST);
    stack.loadFromFile(FILE_STACK);
    queue.loadFromFile(FILE_QUEUE);
    tree.loadFromFile(FILE_TREE);

    std::cout << "Данные успешно загружены из файлов.\n";
    printHelp();

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "EXIT" || cmd == "exit") {
            break;
        } else if (cmd == "HELP" || cmd == "help") {
            printHelp();
        } 
        // ================== PRINT ==================
        else if (cmd == "PRINT") {
            std::string type;
            ss >> type;
            if (type == "M") arr.print();
            else if (type == "F") slist.print();
            else if (type == "L") { dlist.print(); dlist.print_reverse(); }
            else if (type == "S") stack.print();
            else if (type == "Q") queue.print();
            else if (type == "T") tree.printTraversals();
            else std::cout << "Неизвестный тип структуры! Используйте M, F, L, S, Q, T.\n";
        }
        // ================== МАССИВ (M) ==================
        else if (cmd == "MPUSH") {
            std::string arg1, arg2;
            ss >> arg1;
            if (ss >> arg2) {
                size_t idx = std::stoul(arg1);
                arr.insert(idx, arg2);
            } else {
                arr.push_back(arg1);
            }
            arr.saveToFile(FILE_ARRAY);
            std::cout << "Элемент добавлен в массив.\n";
        } else if (cmd == "MDEL") {
            size_t idx;
            if (ss >> idx && arr.remove(idx)) {
                arr.saveToFile(FILE_ARRAY);
                std::cout << "Элемент успешно удален.\n";
            } else {
                std::cout << "Ошибка: неверный индекс.\n";
            }
        } else if (cmd == "MGET") {
            size_t idx;
            if (ss >> idx && idx < arr.size()) {
                std::cout << "M[" << idx << "] = " << arr.get(idx) << "\n";
            } else {
                std::cout << "Ошибка: индекс за пределами массива.\n";
            }
        } else if (cmd == "MSET") {
            size_t idx;
            std::string val;
            if (ss >> idx >> val && arr.replace(idx, val)) {
                arr.saveToFile(FILE_ARRAY);
                std::cout << "Элемент успешно изменен.\n";
            } else {
                std::cout << "Ошибка: неверный индекс.\n";
            }
        } else if (cmd == "MLEN") {
            std::cout << "Длина массива: " << arr.size() << "\n";
        }
        // ================== ОДНОСВЯЗНЫЙ СПИСОК (F) ==================
        else if (cmd == "FPUSH") {
            std::string mode;
            ss >> mode;
            if (mode == "HEAD") {
                std::string val; ss >> val;
                slist.push_head(val);
            } else if (mode == "TAIL") {
                std::string val; ss >> val;
                slist.push_tail(val);
            } else if (mode == "BEFORE") {
                std::string target, val; ss >> target >> val;
                if (!slist.insert_before(target, val)) std::cout << "Цель не найдена!\n";
            } else if (mode == "AFTER") {
                std::string target, val; ss >> target >> val;
                if (!slist.insert_after(target, val)) std::cout << "Цель не найдена!\n";
            }
            slist.saveToFile(FILE_SLIST);
        } else if (cmd == "FDEL") {
            std::string mode;
            ss >> mode;
            bool res = false;
            if (mode == "HEAD") res = slist.pop_head();
            else if (mode == "TAIL") res = slist.pop_tail();
            else if (mode == "BEFORE") {
                std::string target; ss >> target;
                res = slist.delete_before(target);
            } else if (mode == "AFTER") {
                std::string target; ss >> target;
                res = slist.delete_after(target);
            } else if (mode == "VAL") {
                std::string val; ss >> val;
                res = slist.delete_value(val);
            }
            if (res) {
                slist.saveToFile(FILE_SLIST);
                std::cout << "Удаление выполнено успешно.\n";
            } else {
                std::cout << "Ошибка удаления.\n";
            }
        } else if (cmd == "FGET") {
            size_t idx; ss >> idx;
            std::cout << "F[" << idx << "] = " << slist.get(idx) << "\n";
        } else if (cmd == "FSEARCH") {
            std::string val; ss >> val;
            std::cout << "Позиция: " << slist.search(val) << "\n";
        }
        // ================== ДВУСВЯЗНЫЙ СПИСОК (L) ==================
        else if (cmd == "LPUSH") {
            std::string mode;
            ss >> mode;
            if (mode == "HEAD") {
                std::string val; ss >> val;
                dlist.push_head(val);
            } else if (mode == "TAIL") {
                std::string val; ss >> val;
                dlist.push_tail(val);
            } else if (mode == "BEFORE") {
                std::string target, val; ss >> target >> val;
                if (!dlist.insert_before(target, val)) std::cout << "Цель не найдена!\n";
            } else if (mode == "AFTER") {
                std::string target, val; ss >> target >> val;
                if (!dlist.insert_after(target, val)) std::cout << "Цель не найдена!\n";
            }
            dlist.saveToFile(FILE_DLIST);
        } else if (cmd == "LDEL") {
            std::string mode;
            ss >> mode;
            bool res = false;
            if (mode == "HEAD") res = dlist.pop_head();
            else if (mode == "TAIL") res = dlist.pop_tail();
            else if (mode == "BEFORE") {
                std::string target; ss >> target;
                res = dlist.delete_before(target);
            } else if (mode == "AFTER") {
                std::string target; ss >> target;
                res = dlist.delete_after(target);
            } else if (mode == "VAL") {
                std::string val; ss >> val;
                res = dlist.delete_value(val);
            }
            if (res) {
                dlist.saveToFile(FILE_DLIST);
                std::cout << "Удаление выполнено успешно.\n";
            } else {
                std::cout << "Ошибка удаления.\n";
            }
        } else if (cmd == "LGET") {
            size_t idx; ss >> idx;
            std::cout << "L[" << idx << "] = " << dlist.get(idx) << "\n";
        } else if (cmd == "LSEARCH") {
            std::string val; ss >> val;
            std::cout << "Позиция: " << dlist.search(val) << "\n";
        }
        // ================== СТЕК (S) ==================
        else if (cmd == "SPUSH") {
            std::string val; ss >> val;
            stack.push(val);
            stack.saveToFile(FILE_STACK);
            std::cout << "Добавлено в стек.\n";
        } else if (cmd == "SPOP") {
            if (stack.pop()) {
                stack.saveToFile(FILE_STACK);
                std::cout << "Верхний элемент извлечен.\n";
            } else {
                std::cout << "Стек пуст!\n";
            }
        } else if (cmd == "SGET") {
            if (!stack.empty()) std::cout << "Top: " << stack.peek() << "\n";
            else std::cout << "Стек пуст!\n";
        }
        // ================== ОЧЕРЕДЬ (Q) ==================
        else if (cmd == "QPUSH") {
            std::string val; ss >> val;
            queue.push(val);
            queue.saveToFile(FILE_QUEUE);
            std::cout << "Добавлено в очередь.\n";
        } else if (cmd == "QPOP") {
            if (queue.pop()) {
                queue.saveToFile(FILE_QUEUE);
                std::cout << "Первый элемент извлечен.\n";
            } else {
                std::cout << "Очередь пуста!\n";
            }
        } else if (cmd == "QGET") {
            if (!queue.empty()) std::cout << "Front: " << queue.peek() << "\n";
            else std::cout << "Очередь пуста!\n";
        }
        // ================== ДЕРЕВО (T) ==================
        else if (cmd == "TINSERT") {
            std::string val; ss >> val;
            tree.insert(val);
            tree.saveToFile(FILE_TREE);
            std::cout << "Элемент добавлен в дерево.\n";
        } else if (cmd == "TSEARCH") {
            std::string val; ss >> val;
            bool found = tree.search(val);
            std::cout << (found ? "Элемент найден." : "Элемент не найден.") << "\n";
        } else if (cmd == "TCHECK") {
            bool complete = tree.isComplete();
            std::cout << "Дерево " << (complete ? "ЯВЛЯЕТСЯ" : "НЕ ЯВЛЯЕТСЯ") 
                      << " Complete Binary Tree.\n";
        } else if (cmd == "TGET") {
            tree.printTraversals();
        } else {
            std::cout << "Неизвестная команда! Введите HELP для списка команд.\n";
        }
    }

    return 0;
}
