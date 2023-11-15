#include <iostream>
#include <fstream>


template<typename T, typename U>
struct max_type { using type = typename std::conditional<(sizeof(T) > sizeof(U)), T, U>::type; };


template <typename T>
struct List {
    List *next = nullptr;
    List *prev = nullptr;
    int index = 0;
    T value = 0;
};


template <typename T>
class Polynom {
    friend class Polynom<int>;
    friend class Polynom<double>;
    friend class Polynom<long double>;
private:
    List<T> *head, *end, *cash = nullptr;
    int length = 0;

    explicit Polynom(List<T>* _head, List<T>* _end, int _length) noexcept {
        head = _head;
        end = _end;
        length = _length;
    }
public:
    explicit Polynom(const std::string& filename) {
        std::ifstream file(filename);

        if (!file.is_open())
            throw std::runtime_error("file error");

        double value;
        head = new List<T>;

        while (file >> value) {
            length++;

            if (value == 0)
                continue;

            if (length != 1) {
                auto newItem = new List<T>;
                newItem->next = head;
                head->prev = newItem;
                head = newItem;
            } else {
                end = head;
            }

            head->value = value;
            head->index = length - 1;
        }
    }

    T getCoefficient(int index) noexcept {
        try {
            return operator[](index);
        } catch (const std::exception&) {
            return 0;
        }
    }

    void setCoefficient(int index, T value) noexcept {
        if (head == nullptr) {
            head = end = new List<T>;
            head->index = 0;
            head->value = value;
            length = index + 1;
            return;
        }

        index = length - index - 1;

        auto range = [index](List<T>* item) {
            return std::abs(item->index - index);
        };

        List<T>* start = head;

        if (cash != nullptr && range(cash) < range(start))
            start = cash;
        if (range(end) < range(start))
            start = end;

        bool way = start->index < index;
        List<T>* next;

        while (true) {
            next = (way) ? start->prev : start->next;

            if ((next == nullptr) || ((way) ? next->index > index : next->index < index)) {
                List<T>* old = (way) ? start->prev : start->next;
                next = (((way) ? start->prev : start->next) = new List<T>);
                next->index = index;
                next->value = value;
                ((way) ? next->next : next->prev) = start;
                ((way) ? next->prev : next->next) = old;
                cash = next;
                break;
            }

            if (next->index == index) {
                next->value = value;
                cash = next;
                return;
            }
        }

        if (index < 0) {
            int old_length = length;
            length = length - index;
            List<T> *item = (end = next);

            while (item != nullptr) {
                item->index += length - old_length;
                item = item->prev;
            }
        }
    }

    void print() noexcept {
        if (head == nullptr) {
            std::cout << 0;
            return;
        }

        List<T>* item = end;

        do {
            if (item == end)
                std::cout << item->value;
            else {
                if (item->value < 0)
                    std::cout << " - ";
                else
                    std::cout << " + ";
                std::cout << std::abs(item->value);
            }

            if (item->index != length - 1) {
                std::cout << "x";

                if (item->index != length - 2)
                    std::cout << "^";
                else
                    continue;

                std::cout << length - item->index - 1;
            }
        } while ((item = item->prev) != nullptr);
    }

    T& operator[](int index) {
        if (index < 0 || index >= length)
            throw std::runtime_error("index error");

        index = length - index - 1;

        auto range = [index](List<T>* item) {
            return std::abs(item->index - index);
        };

        List<T>* start = head;

        if (cash != nullptr && range(cash) < range(start))
            start = cash;
        if (range(end) < range(start))
            start = end;

        bool way = start->index < index;

        while (true) {
            if (start->index == index) break;

            if ((way) ? start->index > index : start->index < index) throw std::runtime_error("error index");

            start = (way) ? start->prev : start->next;

            if (start == nullptr) throw std::runtime_error("error index");
        }

        return (cash = start)->value;
    }

    template <typename U>
    Polynom<typename max_type<T, U>::type> operator+(Polynom<U> &other) noexcept {
        int _length = std::max(length, other.length);
        using type = typename max_type<T, U>::type;

        List<type> *_head = new List<type>, *_end;
        bool flag = true;

        for (int index = _length - 1; index >= 0; index--) {
            type result = getCoefficient(index) + other.getCoefficient(index);

            if (result == 0) {
                if (flag) {
                    _length--;
                }
                continue;
            }


            if (!flag) {
                auto newItem = new List<type>;
                newItem->next = _head;
                _head->prev = newItem;
                _head = newItem;
            } else {
                _end = _head;
            }

            flag = false;
            _head->index = _length - index - 1;
            _head->value = result;
        }

        if (_length == 0) {
            _head = _end = nullptr;
        }

        return Polynom<type>(_head, _end, _length);
    }

    template <typename U>
    Polynom<typename max_type<T, U>::type> operator-(Polynom<U> &other) noexcept {
        int _length = std::max(length, other.length);
        using type = typename max_type<T, U>::type;

        List<type> *_head = new List<type>, *_end;
        bool flag = true;

        for (int index = _length - 1; index >= 0; index--) {
            type result = getCoefficient(index) - other.getCoefficient(index);

            if (result == 0) {
                if (flag) {
                    _length--;
                }
                continue;
            }


            if (!flag) {
                auto newItem = new List<type>;
                newItem->next = _head;
                _head->prev = newItem;
                _head = newItem;
            } else {
                _end = _head;
            }

            flag = false;
            _head->index = _length - index - 1;
            _head->value = result;
        }

        if (_length == 0) {
            _head = _end = nullptr;
        }

        return Polynom<type>(_head, _end, _length);
    }

    template <typename U>
    Polynom<typename max_type<T, U>::type> operator*(Polynom<U> &other) noexcept {
        using type = typename max_type<T, U>::type;

        Polynom<type> result(nullptr, nullptr, 0);
        List<T>* first = head;

        while (first != nullptr) {
            List<U>* second = other.head;

            while (second != nullptr) {
                result.setCoefficient(length - first->index + other.length - second->index - 2,
                                      first->value * second->value);

                second = second->next;
            }

            first = first->next;
        }

        return result;
    }
};
