#include "PriorityQueue.h"




/**
 * @brief Constructs a PriorityQueue with a specified capacity.
 *
 * @param capacity The maximum number of elements the priority queue can hold.
 */
template <typename T, typename Comparator>
PriorityQueue<T, Comparator>::PriorityQueue(size_t maxSize) : maxSize(maxSize) {}




/**
 * @brief Adds an item to the priority queue.
 *
 * This function inserts an item into the priority queue and maintains the heap property.
 *
 * @param item The item to add to the priority queue.
 */
template <typename T, typename Comparator>
void PriorityQueue<T, Comparator>::push(const T& item) {
    auto it = elements.begin();
    while (it != elements.end() && comparator(*it, item) <= 0) {
        ++it;
    }
    elements.insert(it, item);
    if (elements.size() > maxSize) {
        elements.pop_back();
    }
}




/**
 * @brief Removes and returns the highest priority item from the priority queue.
 *
 * @return T The item with the highest priority.
 * @throw std::runtime_error If the priority queue is empty.
 */
template <typename T, typename Comparator>
T PriorityQueue<T, Comparator>::poll() {
    if (elements.empty()) {
        throw std::out_of_range("PriorityQueue is empty");
    }
    T item = elements.front();
    elements.pop_front();
    return item;
}




/**
 * @brief Checks if the priority queue is empty.
 *
 * @return bool True if the priority queue is empty, false otherwise.
 */
template <typename T, typename Comparator>
bool PriorityQueue<T, Comparator>::isEmpty() const {
    return elements.empty();
}




/**
 * @brief Returns the number of items in the priority queue.
 *
 * @return size_t The number of items in the priority queue.
 */
template <typename T, typename Comparator>
size_t PriorityQueue<T, Comparator>::size() const {
    return elements.size();
}

// Explicit template instantiation
template class PriorityQueue<Move, MyComparator>;
