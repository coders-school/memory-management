#include "uniqueptr.hpp"

template <class T> 
T unique_ptr<T>::get()
{
  return raw_ptr;
}
template <class T> 
T unique_ptr<T>::release()
{
  return
}



