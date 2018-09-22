#include "GTUSet.h"
#include "Gtuset.cpp"
#include "GTUMap.h"
#include  "GtuMap.cpp"
template<class T>
shared_ptr<GTUSetBase<T> > setIntersection (const GTUSetBase<T>&,const GTUSetBase<T>&);

int main(int argc, char** argv) {

GTUSet<int> SET;
GTUSet<int> SET1;
GTUSet<int>::Iterator it;
GTUMap<int,double> MAP;
GTUMap<int,double>::Iterator at;
try {
    it=SET.insert(it,20);
    it=SET.insert(it,12);
    it=SET.insert(it,30);
    it=SET.insert(it,4);
    it=SET.insert(it,21);
    it=SET.insert(it,13);
    it=SET.insert(it,35);
    it=SET.insert(it,8);
}

catch(invalid_argument a) {
    cout<<a.what()<<endl;
    exit(1);
}
for (it=SET.begin(); it != SET.end(); ++it)
    cout<< *it <<endl;
cout<<"\n\n";
SET.erase(20);
SET.erase(8);
SET.erase(4);
cout<<"\n\n";
for (it=SET.begin(); it != SET.end(); ++it)
    cout<< *it <<endl;
cout<<"\n\n";
cout<<SET.size()<<endl;
cout<<"\n\n";
cout<<SET.max_size()<<endl;
cout<<"\n\n";
cout<<SET.empty()<<endl;
cout<<"\n\n";
cout<<SET.count(35)<<endl;
cout<<"\n\n";

try {
    MAP.insert(at,std::pair<int,double>(1,3.10));
    MAP.insert(at,std::pair<int,double>(2,15.0));
    MAP.insert(at,std::pair<int,double>(3,2.5));
    MAP.insert(at,std::pair<int,double>(-1,1.14));
    MAP.insert(at,std::pair<int,double>(10,3.14));
    MAP.insert(at,std::pair<int,double>(12,3.15));
    MAP.insert(at,std::pair<int,double>(5,3.14));
}

catch (invalid_argument error) {
    cout<<error.what()<<endl;
    exit(1);
}

cout<<"\n\n";
for (at=MAP.begin(); at != MAP.end(); ++at)
    cout<<(*at).first<<"<----->"<<at->second<<endl;
cout<<"\n\n";
cout<<MAP[1]<<endl;
cout<<"\n\n";
MAP[1]=10;
cout<<MAP[1]<<endl;
cout<<"\n\n";
at=MAP.begin();
cout<<MAP.size()<<endl;
cout<<"\n\n";
cout<<MAP.empty()<<endl;
cout<<"\n\n";
cout<<MAP.count(*at)<<endl;
cout<<"\n\n";
at=MAP.begin();
MAP.erase(*at);
MAP.erase(*(++at));
MAP.erase(*(++at));
cout<<"\n\n";
for (at=MAP.begin(); at != MAP.end(); ++at)
    cout<<(*at).first<<"<----->"<<at->second<<endl;
cout<<"\n\n";
it=SET1.insert(it,5);
it=SET1.insert(it,3);
it=SET1.insert(it,-3);
it=SET1.insert(it,4);
it=SET1.insert(it,21);
it=SET1.insert(it,13);
it=SET1.insert(it,23);
it=SET1.insert(it,8);
//
auto set2 = setIntersection(SET, SET1);
for (it=set2->begin(); it != set2->end(); ++it)
    cout<< *it <<endl;
SET.clear();
it=SET.insert(it,30);
it=SET.insert(it,4);
it=SET.insert(it,21);
it=SET.insert(it,13);
cout<<"\n\n";
for (it=SET.begin(); it != SET.end(); ++it)
    cout<< *it <<endl;
cout<<"\n\n";
    return 0;
}

template<class T>
shared_ptr<GTUSetBase<T> > setIntersection (const GTUSetBase<T>& set1,const GTUSetBase<T>& set2)
{
    shared_ptr<GTUSet<T> > temp = make_shared<GTUSet<T> > ();
    typename GTUSet<T>::Iterator p1;
    typename GTUSet<T>::Iterator p2;
    
    for (p1 = set1.begin(); p1 != set1.end(); ++p1) {
        
        for (p2 = set2.begin(); p2 != set2.end(); ++p2) {
            if (*p1 == *p2)
                temp->insert(p1, *p1);
        }
    }
    return temp;
}