#ifndef header
#define header

#include <stdexcept>
/*#include <iterator>*/

template <class T>
class RingBuffer {
public:
    RingBuffer(int capacity) {
        this->capacity = capacity;
        this->buffer = new T[capacity + 1];
        this->head = buffer;
        this->tail = buffer;
        this->end_ptr = buffer + 1;
        this->size = 0;
    }
    ~RingBuffer() {
        delete[] buffer;
    }

    void push_back(T value) {
        if (size == 0) {
            *tail = value;
            size++;
        }
        else if (size == capacity) {
            *end_ptr = value;
            tail = end_ptr;
            end_ptr = head;
            head = ( (head == buffer + capacity) ? buffer : head + 1 );
        }
        else if (size < capacity) {
            *end_ptr = value;
            tail = end_ptr;
            end_ptr = ( (end_ptr == buffer + capacity) ? buffer : end_ptr + 1 );
            size++;
        }
    }

    void pop_back() {
        if (size == 0) {
            throw std::runtime_error("Buffer is empty");
        }
        end_ptr = tail;
        tail = ( (tail == buffer) ? buffer + capacity : tail - 1 );
        size--;
    }

    void push_front(T value) {
        if (size == 0) {
            *head = value;
            size++;
        }
        else if (size == capacity) {
            *end_ptr = value;
            head = end_ptr;
            end_ptr = tail;
            tail = ( (tail == buffer) ? buffer + capacity : tail - 1);
        }
        else if (size < capacity) {
            *( (head == buffer) ? buffer + capacity : head - 1 ) = value;
            head = ( (head == buffer) ? buffer + capacity : head - 1 );
            size++;
        }
    }

    void pop_front() {
        head = ( (head == buffer + capacity) ? buffer : head + 1 );
        size--;
    }

    void resize(int value) {
        T* newBuffer = new T[value + 1];
        for (int i = 0; i < size; i++) {
            newBuffer[i] = (*this)[i];
        }
        delete[] buffer;
        buffer = newBuffer;
        capacity = value;
        head = newBuffer;
        tail = newBuffer + size - 1;
        end_ptr = newBuffer + size;
    }

    T front() {
        return *head;
    }

    T back() {
        return *tail;
    }

    T& operator [] (int index) {
        if (index >= size or index < 0) {
            throw std::runtime_error("Index out of range");
        }
        T* tempPtr = tail - (size - index) + 1;
        if (tempPtr < head) {
            return *( (tempPtr + capacity == buffer + capacity) ? buffer : tempPtr + capacity + 1 );
        }
        return *tempPtr;
    }

    class Iterator  /*: public std::iterator <std::random_access_iterator_tag, T>*/  {
    public:
        Iterator(RingBuffer <T>* rb,  T* ptr) {
            this->buffer = rb;
            this->ptr = &(*ptr);
        }

        T& operator * () {
            return *ptr;
        }

        void operator ++ () {
            ptr = ( (ptr == buffer->buffer + buffer->capacity) ? buffer->buffer : ptr + 1 );
        }

        void operator -- () {
            ptr = ( (ptr == buffer->buffer) ? buffer->buffer + buffer->capacity : ptr - 1 );
        }

        bool operator != (const Iterator& it) {
            return this->ptr != it.ptr;
        }

        Iterator operator + (int shift) {
            Iterator newIterator = *this;
            T* tempPtr = ptr;
            for (int i = 0; i < shift; i++) {
                tempPtr = ( (tempPtr == buffer->buffer + buffer->capacity) ? buffer->buffer : tempPtr + 1 );
            }
            newIterator.ptr = tempPtr;
            return newIterator;
        }

        Iterator operator - (int shift) {
            Iterator newIterator = *this;
            T* tempPtr = ptr;
            for (int i = 0; i < shift; i++) {
                tempPtr = ( (tempPtr == buffer->buffer) ? buffer->buffer + buffer->capacity : tempPtr - 1 );
            }
            newIterator.ptr = tempPtr;
            return newIterator;
        }

        bool isCorrect() {
            if (buffer->size < buffer->capacity) {
                if (buffer->head > buffer->tail) {
                    if (ptr < buffer->head and ptr > buffer->tail) return false;
                }
                if (ptr < buffer->head or ptr > buffer->tail) return false;
            }
            return true;
        }

    private:
        RingBuffer* buffer;
        T* ptr;
    };

    Iterator begin() {
        return Iterator(this, this->head);
    }

    Iterator end() {
        return Iterator(this, this->end_ptr);
    }

    void insert(Iterator it, T value) {
        if (size == capacity) {
            throw std::runtime_error("Ring-buffer is full");
        }
        if (!it.isCorrect()) {
            throw std::runtime_error("Iterator is not correct");
        }
        Iterator tempIt = end();
        tail = end_ptr;
        end_ptr = ( (end_ptr == buffer + capacity) ? buffer : end_ptr + 1 );
        while (tempIt != it) {
            *tempIt = *(tempIt - 1);
            --tempIt;
        }
        *it = value;
        size++;
    }

    void erase(Iterator it) {
        if (size == 0) {
            throw std::runtime_error("Ring-buffer is empty");
        }
        if (!it.isCorrect()) {
            throw std::runtime_error("Iterator is not correct");
        }
        while (it != end()) {
            *it = *(it - 1);
            ++it;
        }
        end_ptr = tail;
        tail = ( (tail == buffer) ? buffer + capacity : tail - 1 );
        size--;
    }

private:
    T* buffer;
    int capacity;
    int size;
    T* head;
    T* tail;
    T* end_ptr;
};

#endif