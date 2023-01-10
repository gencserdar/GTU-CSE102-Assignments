#include "header.hpp"

template <class T>
//operator overloads for iterator class
SPC::PFArray<T>::iterator::iterator(T* it_) : it(it_){};

template <class T>
T* SPC::PFArray<T>::iterator::getIt()const{return it;} //getter returns it pointer

template <class T>
T& SPC::PFArray<T>::iterator::operator*() {return *it;}

template <class T>
T* SPC::PFArray<T>::iterator::operator->() {return it;}

template <class T>
typename SPC::PFArray<T>::iterator& SPC::PFArray<T>::iterator::operator=(const iterator& other){
    if(this != &other){
        it = other.it;
    }
    return *this;
}

template <class T>
typename SPC::PFArray<T>::iterator& SPC::PFArray<T>::iterator::operator++(){
    ++it;
    return *this;
}

template <class T>
typename SPC::PFArray<T>::iterator SPC::PFArray<T>::iterator::operator++(int) {
    iterator itt = *this;
    ++*this;
    return itt;
}

template <class T>
typename SPC::PFArray<T>::iterator& SPC::PFArray<T>::iterator::operator--(){
    --it;
    return *this;
}

template <class T>
bool SPC::PFArray<T>::iterator::operator==(const iterator& other) const{return (it==other.it);}

template <class T>
bool SPC::PFArray<T>::iterator::operator!=(const iterator& other) const{return (it!=other.it);}

template <class T>
bool SPC::PFArray<T>::iterator::operator>=(const iterator& other) const{return (it>=other.it);}




//operator overloads for const_iterator class
template <class T>
SPC::PFArray<T>::const_iterator::const_iterator(T* it_) : it(it_){};

template <class T>
const T* SPC::PFArray<T>::const_iterator::getIt()const{return it;}

template <class T>
const T& SPC::PFArray<T>::const_iterator::operator*()const {return *it;}

template <class T>
const T* SPC::PFArray<T>::const_iterator::operator->()const { return it;}

template <class T>
typename SPC::PFArray<T>::const_iterator& SPC::PFArray<T>::const_iterator::operator++(){
    ++it;
    return *this;
}

template <class T>
typename SPC::PFArray<T>::const_iterator SPC::PFArray<T>::const_iterator::operator++(int) {
    const_iterator itt = *this;
    ++*this;
    return itt;
}

template <class T>
typename SPC::PFArray<T>::const_iterator& SPC::PFArray<T>::const_iterator::operator--(){
    --it;
    return *this;
}

template <class T>
typename SPC::PFArray<T>::const_iterator& SPC::PFArray<T>::const_iterator::operator=(const iterator& other){
    if(this != &other){
        it = other.it;
    }
    return *this;
}

template <class T>
bool SPC::PFArray<T>::const_iterator::operator==(const const_iterator& other) const{return (it==other.it);}

template <class T>
bool SPC::PFArray<T>::const_iterator::operator!=(const const_iterator& other) const{return (it!=other.it);}

template <class T>
bool SPC::PFArray<T>::const_iterator::operator>=(const const_iterator& other) const{return (it>=other.it);}



//PFArray Class
template <class T>
SPC::PFArray<T>::PFArray() : capacity(0), arr(NULL){}; //constructor to set capacity to 0 and arr to NULL

template <class T> //[] operator overload to access the elements
T& SPC::PFArray<T>::operator[](int ind){
    if (ind<0 || ind >=capacity) throw std::out_of_range("Invalid index."); //if entered index is invalid throw an exception
    return arr[ind];
}

template <class T>
void SPC::PFArray<T>::push(const T& num){   //push function to add values to the array
    std::shared_ptr<T> newArr(new T[capacity+1], std::default_delete<T[]>());
    for (int i=0; i<capacity; i++){
        newArr.get()[i]=arr.get()[i];
    }
    newArr.get()[capacity++] = num;
    arr=newArr;
}

template <class T> //function to check if the array is empty
bool SPC::PFArray<T>::empty(){
    int count;
    for(auto p=begin();p!=end();p++)
        count++;

    if(count>0) return false;
    return true;
}

template <class T> //function to return the array size
int SPC::PFArray<T>::size(){
    int count=0;
    for (auto p=begin(); p!=end();p++) if(*p!='\0') count++; 
    return count;
}

template <class T> //function to erase the element in the entered index
void SPC::PFArray<T>::erase(iterator ind) {
    if (ind >= end()) throw std::out_of_range("Invalid index.");
    std::shared_ptr<T> newArr(new T[capacity-1], std::default_delete<T[]>());
    auto old_begin = arr.get();
    auto old_end = arr.get() + capacity;
    auto new_begin = newArr.get();

    std::copy(old_begin, ind.getIt(), new_begin);
    std::copy(ind.getIt() + 1, old_end, new_begin + (ind.getIt() - old_begin));
    arr = newArr;
    capacity--;
}

template <class T> //delete everything in array 
void SPC::PFArray<T>::clear() {
    arr.reset();
    capacity=0;
}

template <class T> //return iterator to first index of array
typename SPC::PFArray<T>::iterator SPC::PFArray<T>::begin(){ return iterator(arr.get());}

template <class T> //return iterator to end of array
typename SPC::PFArray<T>::iterator SPC::PFArray<T>::end(){ return iterator(arr.get()+capacity);}

template <class T> //return const_iterator to first index of array
typename SPC::PFArray<T>::const_iterator SPC::PFArray<T>::cbegin() const { return const_iterator(arr.get());}

template <class T> //return const_iterator to end of array
typename SPC::PFArray<T>::const_iterator SPC::PFArray<T>::cend() const { return const_iterator(arr.get()+capacity);}

template <class T> //destructor
SPC::PFArray<T>::~PFArray(){
    arr.reset();
    arr=nullptr;
}
