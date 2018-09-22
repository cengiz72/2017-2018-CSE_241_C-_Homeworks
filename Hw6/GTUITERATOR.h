#ifndef GTUITERATOR_H
#define GTUITERATOR_H
#include <iostream>
using namespace std;
template<typename T>
class GTUIterator {
    public:
        
         GTUIterator();
        ~GTUIterator();
        GTUIterator(const GTUIterator & other);
        GTUIterator(T * other);
        GTUIterator& operator ++ ();
        GTUIterator& operator -- ();
        GTUIterator& operator ++ (int ignore);
        GTUIterator& operator -- (int ignore);
        const T & operator *() const;
        GTUIterator & operator = (const GTUIterator & other);
        bool operator == (const GTUIterator<T> & object1) const;
        bool operator != (const GTUIterator<T> & other) const;
        T* operator -> () const;
        T*  getNode() const { return current;}
        void setPtr(T * other)  { current = other;}
        void deletePtr(T * node);
    private:
        T *current;
};
#endif /* GTUITERATOR_H */

