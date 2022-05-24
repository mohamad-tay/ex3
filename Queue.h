#ifndef EX3_Queue_H
#define EX3_Queue_H

const int EXPAND_RATE =2;
const int INITAL_SIZE = 10;


template<class T>
class Queue
{
  private:
  T* data;
  int maxSize;
  int nextIndex;                          //done

  void expand();
   
  public:
  Queue(int size = INITAL_SIZE);           //done
  Queue(Quene& queue);
  ~Queue();
  void pushBack( T organ );               // done

     
}

//----------------------------------------------------------------------------

template<class T>
void Queue<T>::expand() 
{
  int newSize = maxSize * EXPAND_RATE;
  T* newData = new int[newSize];
  for (int i = 0; i < size; ++i) 
  {
    newData[i] = data[i]
  }  
  delete[] data;
  data = newData;
  maxSize = newSize;
}

template<class T>
Quene<T>::Queue(int size = INITAL_SIZE):
data(newT[size]),
maxSize(size),
nextIndex(0)
{
  if(size <= 0 )
  {
    delete[] data;
    throw InvalidSize; // sho nzrok??
  }
}

template<class T>
void Queue<T>::pushBack( T organ)
{
  if(nextIndex => maxSize)
  {
    expand();
  }
  data[nextIndex] = organ;
  nextIndex++; 
}










#endif //Queue_H