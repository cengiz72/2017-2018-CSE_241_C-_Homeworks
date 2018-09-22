#include "GTU_SET_BASE.h"
template<typename T>
GTUSetBase<T>::GTUSetBase() : Size(0),max_Size(200),node(new T [max_Size]),ptr(node.get())
{
}
template<typename T>  
GTUSetBase<T>::~GTUSetBase() {
    
}