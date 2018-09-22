#ifndef GTUSET_H
#define GTUSET_H
#include "GTU_SET_BASE.h"
template <typename T> 
class GTUSet: public GTUSetBase<T> {
 
     public:
        GTUSet();
        ~GTUSet();
        typedef GTUIterator<T> Iterator;
        bool empty();
        void clear() noexcept;
        int max_size();
        int size() const noexcept;
        int  count(const T & value) const;
        Iterator find(const T & value);
        Iterator insert(Iterator position , const T & value) ; 
        int erase(const T & value);
        Iterator begin() const noexcept;
        Iterator end() const noexcept;
     private:
             
 };

#endif /* GTUSET_H */