#include <iostream>
#include <fstream>

using namespace std;

class Human {
public:
    wstring secondName;
    wstring firstName;
    wstring patronymic;

    Human(wstring& secondName, wstring& firstname, wstring& patronymic) {
        this->secondName = secondName;
        this->firstName = firstname;
        this->patronymic = patronymic;
    }

    friend bool operator> (const Human& first, const Human& second) {
        if (first.secondName != second.secondName) return first.secondName > second.secondName;
        if (first.firstName != second.firstName) return first.firstName > second.firstName;
        if (first.patronymic != second.patronymic) return first.patronymic > second.patronymic;
        return false;
    }
};


template <typename T>
class SelfOrderList {
    class Item {
    public:
        T* value;
        Item* next;

        Item() {
            value = nullptr;
            next = nullptr;
        }

        explicit Item(T* value) : Item() {
            this->value = value;
        }
    };
private:
    Item* first = new Item();
    int length = 0;
public:
    T** get(int* counter) {
        if (length == 0) return nullptr;

        T** list = new T*[length];

        Item* current = first->next;
        for (int index = 0; index < length; index++) {
            list[index] = current->value;
            current = current->next;
        }

        *counter = length;

        return list;
    }

    int getLength() {
        return length;
    }

    void add(T* value) {
        Item* current = first;
        Item* newItem = new Item(value);

        while (true) {
            if (current->next == nullptr) {
                current->next = newItem;
                break;
            }

            if (*(current->next->value) > *value) {
                newItem->next = current->next;
                current->next = newItem;
                break;
            }

            current = current->next;
        }

        length++;
    }
};


class Program {
private:
    string filename;
    SelfOrderList<Human> list = SelfOrderList<Human>();

    void readFile() {
        wifstream file(filename, ios::in);

        if (!file.is_open()) {
            file.close();
            throw runtime_error("file error.");
        }

        wstring firstName, secondName, patronymic;

        while (file >> secondName >> firstName >> patronymic) {
            list.add(new Human(secondName, firstName, patronymic));
        }

        file.close();

        if (list.getLength() == 0) throw runtime_error("file is empty.");
    }

    void print() {
        int length = 0;
        Human** data = list.get(&length);

        for (int index = 0; index < length; index++) {
            Human* item = data[index];
            wcout << index + 1 << ". " << item->secondName << ' ' << item->firstName << ' ' << item->patronymic << '\n';
        }
    }

    void filter() {
        int length = 0;
        Human** data = list.get(&length);

        wstring fSecondName, fFirstName, fPatronymic;
        cout << "Enter the filter for second name:\n";
        getline(wcin, fSecondName);
        cout << "Enter the filter for first name:\n";
        getline(wcin, fFirstName);
        cout << "Enter the filter for patronymic name:\n";
        getline(wcin, fPatronymic);

        int counter = 0;

        cout << "Match list:\n";

        for (int index = 0; index < length; index++) {
            Human* item = data[index];
            if (item->secondName.find(fSecondName) == 0
            && item->firstName.find(fFirstName) == 0
            && item->patronymic.find(fPatronymic) == 0) {
                wcout << ++counter << ". " << item->secondName << ' '
                << item->firstName << ' ' << item->patronymic << '\n';
            }
        }

        if (counter == 0) cout << "No matches.\n";
    }

public:
    void run() {
        cout << "Enter filename:\n";
        cin >> filename;
        readFile();

        cout << "Would you like to print list? [Y/n]\n";
        char input;
        cin >> input;

        if (tolower(input) == 'y') print();

        cout << "Would you like to filter list? [Y/n]\n";
        (cin >> input).get();

        if (tolower(input) == 'y') filter();
    }
};



int main() {
    system("chcp 1251");

    try {
        Program().run();
    } catch (exception& error) {
        cout << error.what();
    }

    return 0;
}
