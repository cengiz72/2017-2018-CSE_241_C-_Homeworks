#include "GTUMap.h"

template<typename K,typename V>
GTUMap <K,V>::GTUMap() : GTUSet< std::pair <K,V> >() {}
template <typename K,typename V>
GTUMap <K,V> ::~GTUMap() {}
template<typename K,typename V>
V& GTUMap<K,V>::operator [] (const K& k) {
    int count=0;
    this->base.setPtr(this->ptr);
    while(count < this->size()) {
        if ((*(this->base)).first==k) { 
           return (this->base.getNode()[count].second);
            
        }
        ++count;
        ++(this->base);   
    }        
}
template<typename K,typename V>
GTUIterator < std::pair <K,V > >GTUMap<K,V>::insert(Iterator position , const  std::pair <K,V> & value){
    std::pair <K,V> temp[this->size()];
    int count=0;
    bool flag=true;
    (this->base).setPtr(this->ptr);
    if (this->size()== 0) {
        this->ptr[0]=value;
        ++(this->Size);
        position.setPtr(this->ptr);
        return Iterator(this->ptr);
    }
    
    while(count<this->size()){
        
        if(value <= *(this->base)) {
           if (value.first == (*(this->base)).first )
               throw invalid_argument("element is exist");
            temp[0]=value;
            ++(this->Size);
            for (int i=1; i<this->Size -count; ++i)
                temp[i]=this->ptr[count+i-1];
            for (int i=count,j=0; i<this->size() && this->size()-count-1; ++i,++j)
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