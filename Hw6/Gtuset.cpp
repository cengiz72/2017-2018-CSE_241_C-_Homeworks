#include "GTUSet.h"
#include "GtuSetBase.cpp"

template <typename T>
GTUSet<T>::GTUSet() : GTUSetBase<T>() { /**/}

template <typename T>
GTUSet<T>::~GTUSet() {
}
template < typename T >
bool GTUSet<T>::empty() {
   
    return (this->Size==0);
}
template < typename T >
void GTUSet<T> :: clear() noexcept {
    this->Size=0;
}
template < typename T >
int GTUSet<T> :: max_size() {
    return this->max_Size;
}
template < typename T >
int GTUSet<T> :: size() const noexcept {
    return this->Size;
}
template < typename T >
int GTUSet<T> :: count(const T & value) const {
    
    int count=0;
    GTUIterator<T> temp(this->ptr);
    while(count<size()) {
        if (*temp==value) return 1;
        ++count;
        ++temp;
    }
    return 0;
}
template <typename T>
GTUIterator<T> GTUSet<T>::find(const T & value) {   
    int count=0;
    this->base.setPtr(this->ptr);
    while(count<size()) {
        if (*(this->base)==value) return this->base;
        ++count;
        ++(this->base);   
    }
    return Iterator();
}
template <typename T>
GTUIterator<T> GTUSet<T>::insert(Iterator position,const T & value) {
    T temp[max_size()];
    int count=0;
    bool flag=true;
    (this->base).setPtr(this->ptr);
    if (size()== 0) {
        this->ptr[0]=value;
        ++(this->Size);
        position.setPtr(this->ptr);
        return Iterator(this->ptr);
    }
    
    while(count<size()){
        
        if(value <= *(this->base)) {
           if (value == *(this->base)) throw invalid_argument("element is exist");
            temp[0]=value;
            ++(this->Size);
            for (int i=1; i<size()-count; ++i)
                temp[i]=this->ptr[count+i-1];
            for (int i=count,j=0; i<size() && size()-count-1; ++i,++j)
                this->ptr[i]=temp[j];
            flag=false;
            return Iterator(this->ptr);
        }
        ++count;
        ++(this->base);
    }
    
    this->ptr[this->Size]=value;
    ++(this->Size);
    return Iterator(this->ptr);
    
}
template <typename T>
int GTUSet<T>::erase(const T & value) {  
    T *temp;
    int count=0;
    this->base.setPtr(this->ptr);
    while(count<size()) {
        if (*(this->base)==value) {
            if (count==size()-1) {
                --(this->Size);
                return 1;
            }
               
            if (count==0) { 
                ++(this->ptr);
               --(this->Size);
                return 1;
            }
            
            temp =(this->base.getNode());
            for (int i=count; i < size()-1; ++i) {
                this->ptr[i]= *(++temp);
            }
            --(this->Size);
            temp=nullptr;
            
            return 1;
        }
        
        ++count;
        ++(this->base);
    }
    
    return 0;
}
template <typename T>
GTUIterator<T> GTUSet<T>::begin() const noexcept {

    GTUIterator<T> temp;
    temp.setPtr(this->ptr);
    return temp;
}
template <typename T>
GTUIterator<T> GTUSet<T>::end() const noexcept {
    GTUIterator<T> temp;
    temp.setPtr(this->ptr+this->Size);
    return temp;
}
