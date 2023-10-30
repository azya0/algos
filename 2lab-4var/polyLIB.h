#include <iostream>
#include <fstream>


template<typename T, typename U>
struct max_type { using type = typename std::conditional<(sizeof(T) > sizeof(U)), T, U>::type; };

template <typename T> requires (
        std::is_same<T, int>::value ||
        std::is_same<T, double>::value ||
        std::is_same<T, long double>::value
)
class Polynom {
private:
    int length;
    T* coefficients;
public:
    explicit Polynom(int size) noexcept {
        length = size;
        coefficients = new T[length];
    }

    explicit Polynom(const std::string& filename) {
        std::ifstream file(filename);

        if (!file.is_open())
            throw std::runtime_error("File not found");

        typedef struct list {
            list* next = nullptr;
            T value = 0;
        } List;

        length = 0;
        List head, *newElm = new List();

        while (file >> newElm->value) {
            newElm->next = head.next;
            head.next = newElm;
            newElm = new List();
            length++;
        }

        coefficients = new T[length];

        for (int index = 0; index < length; index++) {
            head = *head.next;
            coefficients[index] = head.value;
        }
    }

    [[nodiscard]] int getLength() const {
        return length;
    }

    void print() noexcept {
        for (int index = length - 1; index >= 0; index--) {
            T value = coefficients[index];

            if (value == 0)
                continue;

            if (index != length - 1) {
                if (value < 0)
                    std::cout << " - ";
                else
                    std::cout << " + ";
                std::cout << std::abs(value);
            } else
                std::cout << value;

            if (index != 0) {
                std::cout << "x";

                if (index != 1)
                    std::cout << "^" << index;
            }
        }
    }

    [[nodiscard]] T get(int index) const noexcept {
        if (index >= length || index < 0)
            return 0;
        return coefficients[index];
    }

    T& operator[](int index) {
        if (index >= length || index < 0)
            throw std::runtime_error("index error");
        return coefficients[index];
    }

    template <typename U>
    Polynom<typename max_type<T, U>::type> operator+(const Polynom<U> &other) {
        Polynom<typename max_type<T, U>::type> result(std::max(length, other.getLength()));

        for (int index = 0; index < result.getLength(); index++) {
            result[index] = this->get(index) + other.get(index);
        }

        return result;
    }

    template <typename U>
    Polynom<typename max_type<T, U>::type> operator-(const Polynom<U> &other) {
        Polynom<typename max_type<T, U>::type> result(std::max(length, other.getLength()));

        for (int index = 0; index < result.getLength(); index++) {
            result[index] = this->get(index) - other.get(index);
        }

        return result;
    }

    template <typename U>
    Polynom<typename max_type<T, U>::type> operator*(const Polynom<U> &other) {
        Polynom<typename max_type<T, U>::type> result(length + other.getLength() - 1);

        for (int i = 0; i < length; i++) {
            for (int j = 0; j < other.getLength(); j++) {
                result[i + j] += get(i) * other.get(j);
            }
        }

        return result;
    }

    template<typename U>
    Polynom<U> convert() {
        Polynom<U> result(length);

        for (int index = 0; index < length; index++) {
            result[index] = (U)(coefficients[index]);
        }

        return result;
    }
};