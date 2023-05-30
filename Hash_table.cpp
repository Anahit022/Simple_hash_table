#include <iostream>
#include <string>
#include <vector>

class Pair {
public:
    std::string key;
    int value;

    Pair(const std::string& k, int v) : key(k), value(v) {}
};

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    std::vector<Pair*> table[TABLE_SIZE];

    int hash(const std::string& key) {
        int sum = 0;
        for (char ch : key) {
            sum += ch;
        }
        return sum % TABLE_SIZE;
    }

public:
    void insert(const std::string& key, int value) {
        int index = hash(key);
        Pair* pair = new Pair(key, value);
        table[index].push_back(pair);
    }

    float get(const std::string& key) {
        int index = hash(key);
        for (Pair* pair : table[index]) {
            if (pair->key == key) {
                return pair->value;
            }
        }
        return -1; // Key not found
    }

    std::string getKey(float value) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            for (Pair* pair : table[i]) {
                if (pair->value == value) {
                    return pair->key;
                }
            }
        }
        return ""; // Grade not found
    }

    bool find(const std::string& key) {
        int index = hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if ((*it)->key == key) {
                return true;
            }
        }
        return false; // Key not found
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            for (Pair* pair : table[i]) {
                delete pair;
            }
        }
    }
};

int main() {
    HashTable hashTable;

    std::string name;
    int avg;

    // Insert student names and average grades
    for (int i = 0; i < 3; ++i) {
        std::cout << "Enter student name: ";
        std::cin >> name;

        std::cout << "Enter average grade: ";
        std::cin >> avg;

        hashTable.insert(name, avg);
    }

    // Get average grades by student names
    for (int i = 0; i < 3; ++i) {
        std::cout << "Enter student name to get average grade: ";
        std::cin >> name;

        int averageGrade = hashTable.get(name);
        if (averageGrade != -1) {
            std::cout << "Average grade for " << name << ": " << averageGrade << std::endl;
        }
        else {
            std::cout << "Student not found." << std::endl;
        }
    }

    // Find student name by grade
    for (int i = 0; i < 3; ++i) {
        std::cout << "Enter average grade to find student name: ";
        std::cin >> avg;

        std::string studentName = hashTable.getKey(avg);
        if (!studentName.empty()) {
            std::cout << "Student name for average grade " << avg << ": " << studentName << std::endl;
        }
        else {
            std::cout << "Grade not found." << std::endl;
        }
    }
    return 0;
}