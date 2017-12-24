#include <iostream>

struct node {
    int value;
    node* next;

    node()
            : next(nullptr)
    { }

    node(int x)
            : value(x)
            , next(nullptr)
    { }
};

class ForwardList {
public:
    ForwardList()
            : first(nullptr)
            , size(0)
    { }

    ~ForwardList() {
        node* current = first;
        while (current) {
            node* next = current->next;
            delete current;
            current = next;
        }
    }

    void push(int x) {
        node* current = new node;
        current->value = x;
        if (first) {
            current->next = first;
        }
        first = current;
        ++size;
    }

    void reverse() {
        node* current = first;
        node* previous = nullptr;
        while (current) {
            node* next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        first = previous;
    }

    node* front() {
        return first;
    }

private:
    node* first;
    int size;
};

void MergeSort(node* it, int length) {
    if (length == 1) {
        return;
    } else {
        node* first = it;
        node* second = it;

        for (int i = 0; i != length / 2; ++i) {
            second = second->next;
        }

        MergeSort(first, length / 2);
        MergeSort(second, length - length / 2);

        ForwardList result;

        int f = 0, s = 0;
        while (f != length / 2 || s != length - length / 2) {
            if (f == length / 2) {
                result.push(second->value);
                second = second->next;
                ++s;
            } else if (s == length - length / 2) {
                result.push(first->value);
                first = first->next;
                ++f;
            } else if (first->value < second->value) {
                result.push(first->value);
                first = first->next;
                ++f;
            } else {
                result.push(second->value);
                second = second->next;
                ++s;
            }
        }

        result.reverse();

        node* current = result.front();
        while (current) {
            it->value = current->value;
            it = it->next;
            current = current->next;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(0);

    int n;
    std::cin >> n;

    ForwardList a;

    for (int i = 0; i != n; ++i) {
        int x;
        std::cin >> x;
        a.push(x);
    }

    a.reverse();

    MergeSort(a.front(), n);

    auto current = a.front();
    while (current) {
        std::cout << current->value << ' ';
        current = current->next;
    }
    std::cout << '\n';

    return 0;
}