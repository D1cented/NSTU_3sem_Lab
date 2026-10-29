#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

// Подключение заголовочных файлов структур
#include "Array.h"
#include "SinglyList.h"
#include "DoublyList.h"
#include "Stack.h"
#include "Queue.h"
#include "CompleteBinaryTree.h"

// Хранилище всех именованных структур данных
struct Database {
    std::map<std::string, MyArray> arrays;
    std::map<std::string, SinglyList> slists;
    std::map<std::string, DoublyList> dlists;
    std::map<std::string, MyStack> stacks;
    std::map<std::string, MyQueue> queues;
    std::map<std::string, CompleteBinaryTree> trees;

    // Вспомогательный метод для извлечения элементов из списков при сохранении
    std::vector<std::string> getSListItems(const SinglyList& list) {
        std::vector<std::string> items;
        for (size_t i = 0; ; ++i) {
            std::string val = list.get(i);
            if (val.empty()) break;
            items.push_back(val);
        }
        return items;
    }

    std::vector<std::string> getDListItems(const DoublyList& list) {
        std::vector<std::string> items;
        for (size_t i = 0; ; ++i) {
            std::string val = list.get(i);
            if (val.empty()) break;
            items.push_back(val);
        }
        return items;
    }

    // Загрузка всей базы из одного файла
    void load(const std::string& filename) {
        std::ifstream in(filename);
        if (!in.is_open()) return;

        std::string type, name;
        size_t count;
        while (in >> type >> name >> count) {
            std::vector<std::string> items(count);
            for (size_t i = 0; i < count; ++i) in >> items[i];

            if (type == "ARRAY") {
                for (const auto& item : items) arrays[name].push_back(item);
            } else if (type == "SLIST") {
                for (const auto& item : items) slists[name].push_tail(item);
            } else if (type == "DLIST") {
                for (const auto& item : items) dlists[name].push_tail(item);
            } else if (type == "STACK") {
                for (int i = (int)items.size() - 1; i >= 0; --i) stacks[name].push(items[i]);
            } else if (type == "QUEUE") {
                for (const auto& item : items) queues[name].push(item);
            } else if (type == "TREE") {
                for (const auto& item : items) trees[name].insert(item);
            }
        }
    }

    // Сохранение всей базы в один файл
    void save(const std::string& filename) {
        std::ofstream out(filename);
        if (!out.is_open()) return;

        for (auto& [name, arr] : arrays) {
            out << "ARRAY " << name << " " << arr.size();
            for (size_t i = 0; i < arr.size(); ++i) out << " " << arr.get(i);
            out << "\n";
        }
        for (auto& [name, slist] : slists) {
            auto items = getSListItems(slist);
            out << "SLIST " << name << " " << items.size();
            for (const auto& val : items) out << " " << val;
            out << "\n";
        }
        for (auto& [name, dlist] : dlists) {
            auto items = getDListItems(dlist);
            out << "DLIST " << name << " " << items.size();
            for (const auto& val : items) out << " " << val;
            out << "\n";
        }
        for (auto& [name, st] : stacks) {
            std::vector<std::string> temp;
            while (!st.empty()) { temp.push_back(st.peek()); st.pop(); }
            out << "STACK " << name << " " << temp.size();
            for (const auto& val : temp) out << " " << val;
            out << "\n";
            for (int i = (int)temp.size() - 1; i >= 0; --i) st.push(temp[i]);
        }
        for (auto& [name, q] : queues) {
            std::vector<std::string> temp;
            while (!q.empty()) { temp.push_back(q.peek()); q.pop(); }
            out << "QUEUE " << name << " " << temp.size();
            for (const auto& val : temp) out << " " << val;
            out << "\n";
            for (const auto& val : temp) q.push(val);
        }
        for (auto& [name, tree] : trees) {
            // Для полного дерева сохранение через level-order
            // Временный файл для перехвата
            tree.saveToFile("tmp_tree.txt");
            std::ifstream tin("tmp_tree.txt");
            std::vector<std::string> items;
            std::string line;
            while (std::getline(tin, line)) if (!line.empty()) items.push_back(line);
            tin.close();
            std::remove("tmp_tree.txt");

            out << "TREE " << name << " " << items.size();
            for (const auto& val : items) out << " " << val;
            out << "\n";
        }
    }
};

int main(int argc, char* argv[]) {
    std::string dbFile = "";
    std::string queryStr = "";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) dbFile = argv[++i];
        else if (arg == "--query" && i + 1 < argc) queryStr = argv[++i];
    }

    if (dbFile.empty() || queryStr.empty()) {
        std::cerr << "Использование: ./dbms --file <file.data> --query '<команда>'\n";
        return 1;
    }

    Database db;
    db.load(dbFile);

    std::stringstream ss(queryStr);
    std::string cmd;
    ss >> cmd;

    // ================= 1. ОДНОСВЯЗНЫЙ СПИСОК (F) =================
    if (cmd == "FPUSH") {
        std::string name, mode;
        ss >> name >> mode;
        bool ok = false;
        std::string val;

        if (mode == "HEAD") {
            ss >> val; db.slists[name].push_head(val); ok = true;
        } else if (mode == "TAIL") {
            ss >> val; db.slists[name].push_tail(val); ok = true;
        } else if (mode == "BEFORE") {
            std::string target; ss >> target >> val;
            ok = db.slists[name].insert_before(target, val);
        } else if (mode == "AFTER") {
            std::string target; ss >> target >> val;
            ok = db.slists[name].insert_after(target, val);
        }

        if (ok) { db.save(dbFile); std::cout << "-> " << val << "\n"; }
        else { std::cout << "-> ERROR\n"; }
    }
    else if (cmd == "FDEL") {
        std::string name, mode;
        ss >> name >> mode;
        bool ok = false;
        if (db.slists.find(name) != db.slists.end()) {
            if (mode == "HEAD") ok = db.slists[name].pop_head();
            else if (mode == "TAIL") ok = db.slists[name].pop_tail();
            else if (mode == "BEFORE") { std::string t; ss >> t; ok = db.slists[name].delete_before(t); }
            else if (mode == "AFTER") { std::string t; ss >> t; ok = db.slists[name].delete_after(t); }
            else if (mode == "VAL") { std::string v; ss >> v; ok = db.slists[name].delete_value(v); }
        }
        if (ok) { db.save(dbFile); std::cout << "-> OK\n"; }
        else { std::cout << "-> FALSE\n"; }
    }
    else if (cmd == "FGET") {
        std::string name; size_t idx;
        ss >> name >> idx;
        if (db.slists.find(name) != db.slists.end()) {
            std::string val = db.slists[name].get(idx);
            std::cout << "-> " << (val.empty() ? "NULL" : val) << "\n";
        } else std::cout << "-> NULL\n";
    }

    // ================= 2. ДВУСВЯЗНЫЙ СПИСОК (L) =================
    else if (cmd == "LPUSH") {
        std::string name, mode;
        ss >> name >> mode;
        bool ok = false;
        std::string val;

        if (mode == "HEAD") {
            ss >> val; db.dlists[name].push_head(val); ok = true;
        } else if (mode == "TAIL") {
            ss >> val; db.dlists[name].push_tail(val); ok = true;
        } else if (mode == "BEFORE") {
            std::string target; ss >> target >> val;
            ok = db.dlists[name].insert_before(target, val);
        } else if (mode == "AFTER") {
            std::string target; ss >> target >> val;
            ok = db.dlists[name].insert_after(target, val);
        }

        if (ok) { db.save(dbFile); std::cout << "-> " << val << "\n"; }
        else { std::cout << "-> ERROR\n"; }
    }
    else if (cmd == "LDEL") {
        std::string name, mode;
        ss >> name >> mode;
        bool ok = false;
        if (db.dlists.find(name) != db.dlists.end()) {
            if (mode == "HEAD") ok = db.dlists[name].pop_head();
            else if (mode == "TAIL") ok = db.dlists[name].pop_tail();
            else if (mode == "BEFORE") { std::string t; ss >> t; ok = db.dlists[name].delete_before(t); }
            else if (mode == "AFTER") { std::string t; ss >> t; ok = db.dlists[name].delete_after(t); }
            else if (mode == "VAL") { std::string v; ss >> v; ok = db.dlists[name].delete_value(v); }
        }
        if (ok) { db.save(dbFile); std::cout << "-> OK\n"; }
        else { std::cout << "-> FALSE\n"; }
    }
    else if (cmd == "LGET") {
        std::string name; size_t idx;
        ss >> name >> idx;
        if (db.dlists.find(name) != db.dlists.end()) {
            std::string val = db.dlists[name].get(idx);
            std::cout << "-> " << (val.empty() ? "NULL" : val) << "\n";
        } else std::cout << "-> NULL\n";
    }

    // ================= 3. СТЕК (S) =================
    else if (cmd == "SPUSH") {
        std::string name, val;
        ss >> name >> val;
        db.stacks[name].push(val);
        db.save(dbFile);
        std::cout << "-> " << val << "\n";
    } 
    else if (cmd == "SPOP") {
        std::string name;
        ss >> name;
        if (db.stacks.find(name) != db.stacks.end() && !db.stacks[name].empty()) {
            std::string val = db.stacks[name].peek();
            db.stacks[name].pop();
            db.save(dbFile);
            std::cout << "-> " << val << "\n";
        } else std::cout << "-> NULL\n";
    }

    // ================= 4. ОЧЕРЕДЬ (Q) =================
    else if (cmd == "QPUSH") {
        std::string name, val;
        ss >> name >> val;
        db.queues[name].push(val);
        db.save(dbFile);
        std::cout << "-> " << val << "\n";
    }
    else if (cmd == "QPOP") {
        std::string name;
        ss >> name;
        if (db.queues.find(name) != db.queues.end() && !db.queues[name].empty()) {
            std::string val = db.queues[name].peek();
            db.queues[name].pop();
            db.save(dbFile);
            std::cout << "-> " << val << "\n";
        } else std::cout << "-> NULL\n";
    }

    // ================= 5. ДЕРЕВО (T) =================
    else if (cmd == "TINSERT") {
        std::string name, val;
        ss >> name >> val;
        db.trees[name].insert(val);
        db.save(dbFile);
        std::cout << "-> " << val << "\n";
    }
    else if (cmd == "ISMEMBER" || cmd == "TSEARCH") {
        std::string name, val;
        ss >> name >> val;
        bool exists = (db.trees.find(name) != db.trees.end()) && db.trees[name].search(val);
        std::cout << "-> " << (exists ? "TRUE" : "FALSE") << "\n";
    }
    else if (cmd == "TCHECK") {
        std::string name;
        ss >> name;
        bool isComplete = (db.trees.find(name) != db.trees.end()) && db.trees[name].isComplete();
        std::cout << "-> " << (isComplete ? "TRUE" : "FALSE") << "\n";
    }

    // ================= 6. МАССИВ (M) =================
    else if (cmd == "MPUSH") {
        std::string name, val;
        ss >> name >> val;
        db.arrays[name].push_back(val);
        db.save(dbFile);
        std::cout << "-> " << val << "\n";
    }
    else if (cmd == "MGET") {
        std::string name; size_t idx;
        ss >> name >> idx;
        if (db.arrays.find(name) != db.arrays.end() && idx < db.arrays[name].size()) {
            std::cout << "-> " << db.arrays[name].get(idx) << "\n";
        } else std::cout << "-> NULL\n";
    }

    // ================= ВЫВОД (PRINT) =================
    else if (cmd == "PRINT") {
        std::string name;
        ss >> name;
        if (db.slists.count(name)) db.slists[name].print();
        else if (db.dlists.count(name)) { db.dlists[name].print(); db.dlists[name].print_reverse(); }
        else if (db.stacks.count(name)) db.stacks[name].print();
        else if (db.queues.count(name)) db.queues[name].print();
        else if (db.arrays.count(name)) db.arrays[name].print();
        else if (db.trees.count(name)) db.trees[name].printTraversals();
        else std::cout << "-> Структура не найдена\n";
    }
    else {
        std::cout << "-> Неизвестная команда\n";
    }

    return 0;
}
