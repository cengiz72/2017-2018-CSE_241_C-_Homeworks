#include "GTUITERATOR.h"
template<typename T>
GTUIterator<T>::GTUIterator() {/**/}
template<typename T>
GTUIterator<T>::~GTUIterator() {/**/}
template<typename T>
GTUIterator<T>::GTUIterator( T * other) {
    current=other;
}
template<typename T>
GTUIterator<T>& GTUIterator<T>::operator ++(){
    
    ++current;
    return *this;
}

template<typename T>
GTUIterator<T>& GTUIterator<T>::operator ++(int ignore) {
    
    ++current;
    return *this;
}

template<typename T>
GTUIterator<T> & GTUIterator<T>:: operator --() {

    --current;
    return *this;
}

template<typename T>
GTUIterator<T>& GTUIterator<T>:: operator --(int ignore) {
    --current;
    return *this;
}

template<typename T>
GTUIterator<T>::GTUIterator(const GTUIterator<T> & other) {

    //deletePtr(getNode());
    setPtr(other.getNode());
}
template<typename T>
GTUIterator<T>& GTUIterator<T>::operator = (const GTUIterator<T> & other){
  if (this==&other) return *this;
    //deletePtr(getNode());
    setPtr(other.getNode());
    return *this;
 
 }
template<typename T>
void GTUIterator<T>::deletePtr(T * nodes){
    delete nodes;
    nodes=nullptr;
}
template<typename T>
const T& GTUIterator<T>::operator *() const {
        return *current;
}

template<typename T>

bool GTUIterator<T>::operator ==(const GTUIterator<T> & object1) const {
    return (object1.current==this->current);
}

template<typename T>

T* GTUIterator<T>::operator -> () const {
   
   return current;
}


template <typename T>
bool  GTUIterator<T>::operator != (const GTUIterator<T> & other) const {
    return !(this->current==other.getNode());
}