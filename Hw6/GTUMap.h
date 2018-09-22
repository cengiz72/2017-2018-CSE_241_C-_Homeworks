#ifndef GTUMAP_H
#define GTUMAP_H
    
#include "GTUSet.h"

template<typename K,typename V>
class GTUMap : public GTUSet< std::pair <K,V> > {
    public:
        GTUMap();
        ~GTUMap();
        V& operator [] (const K& k);
        typedef GTUIterator < std::pair <K,V> > Iterator;
        Iterator insert(Iterator position , const  std::pair <K,V> & value);
};
#endif /* GTUMAP_H */

