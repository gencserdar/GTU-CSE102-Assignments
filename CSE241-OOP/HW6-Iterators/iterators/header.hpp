#include <iostream>
#include <memory>
#include <iterator>
#include <algorithm>

#ifndef HEADER
#define HEADER
namespace SPC{
    template <class T>
    class PFArray {
        public:
            class iterator : public std::iterator<std::forward_iterator_tag, T> {
                public:
                    iterator(T* it_);
                    T* getIt()const;
                    T& operator*();
                    T* operator->();
                    iterator& operator=(const iterator& other);
                    iterator& operator++();
                    iterator operator++(int);
                    iterator& operator--();
                    bool operator==(const iterator& other) const;
                    bool operator!=(const iterator& other) const;
                    bool operator>=(const iterator& other) const;
                private:
                    T* it;
            };

            class const_iterator : public std::iterator<std::forward_iterator_tag, T> {
                public:
                    const_iterator(T* it_);
                    const T* getIt()const;
                    const T& operator*()const;
                    const T* operator->()const;
                    const_iterator& operator++();
                    const_iterator operator++(int);
                    const_iterator& operator--();
                    const_iterator& operator=(const iterator& other);
                    bool operator==(const const_iterator& other) const;
                    bool operator!=(const const_iterator& other) const;
                    bool operator>=(const const_iterator& other) const;
                    
                private:
                    T* it;
            };
            PFArray();
            T& operator[](int ind);
            void push(const T& num);
            bool empty();
            int size();
            void erase(iterator ind);
            void clear();
            iterator begin();
            iterator end();
            const_iterator cbegin() const;
            const_iterator cend() const;
            ~PFArray();
        private:
            std::shared_ptr<T> arr;
            int capacity;
    };
}
#endif