#ifndef GTU_SET_BASE_H
#define GTU_SET_BASE_H
#include "GTUITERATOR.h"
#include "Gtuiterator.cpp"
#include <memory>
#include <exception>
template<typename T>
class GTUSetBase {
    public:
        GTUSetBase ();
        ~GTUSetBase();
        typedef GTUIterator<T> Iterator;
        virtual bool empty() = 0;
        virtual void clear() noexcept = 0;
        virtual int max_size() = 0;
        virtual int size() const noexcept = 0;
        virtual int  count(const T & value) const = 0;
        virtual Iterator  find(const T & value) = 0;
        virtual  Iterator insert(Iterator position , const T & value) = 0; 
        virtual int erase(const T & value) = 0;
        virtual  Iterator  begin() const noexcept = 0;
        virtual  Iterator  end() const noexcept = 0;
        Iterator  base;
    protected:
        int Size;
        int max_Size;
        shared_ptr<T> node;
        T * ptr;

};
#endif /* GTU_BASE_SET_H */