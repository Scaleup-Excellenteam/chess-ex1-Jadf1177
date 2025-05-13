#pragma once
#include <list>
#include <stdexcept>
#include "Move.h"
template <typename T, typename Comparator>
class PriorityQueue {
public:
    PriorityQueue(size_t maxSize);
    void push(const T& item);
    T poll();
    bool isEmpty() const;
    size_t size() const;

private:
    std::list<T> elements;
    size_t maxSize;
    Comparator comparator;
};

struct MyComparator {
    int operator()(const Move& a, const Move& b) const {
        return b.getScore() - a.getScore();
    }
};
