#ifndef EX3_Queue_H
#define EX3_Queue_H

const int EXPAND_RATE =2;
const int INITIAL_SIZE = 10;


template<class T>
class Queue
{
  private:
  T* m_data;
  int m_maxSize;
  int m_nextIndex;                       

  void expand();
   
  public:
  Queue(int size = INITIAL_SIZE);         
  Queue(Queue& queue);
  ~Queue();
  void pushBack(T newObject);               
  T& front();
  void popFront();
  int size();   
}


template<class T>
void Queue<T>::expand() 
{
  int newSize = m_maxSize * EXPAND_RATE;
  try
  {
  T* newData = new int[newSize];    //T should have a default c'tor //may be problematic answer in whatsapp group
  }
  catch (const std::bad_alloc& e)
  {
    cerr << e.what() << endl;
  }
  for (int i = 0; i < size; ++i) 
  {
    newData[i] = m_data[i];           //T should have assignment operator
  }  
  delete[] m_data;
  m_data = newData;
  m_maxSize = newSize;
}

template<class T>
Queue<T>::Queue(int size):
data(new T[size]),          //how to check alloc
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
void Queue<T>::pushBack(T newObject)
{
  if(nextIndex => maxSize)
  {
    expand();
  }
  data[nextIndex] = newObject;            //copy c'tor / assignment operator for T
  nextIndex++; 
}

template<class T>
T& Queue<T>::front()
{
  return m_data[0];
}

template<class T>
void Queue<T>::popFront()
{
  for (int i=0 ; i<nextIndex-1 ; ++i)   //should be nextIndex-1
  {
    m_data[i]=m_data[i+1];            //careful for out of bounds //change next index?
    nextIndex--;
  }
}


template<class T>
int Queue<T>::size()
{
  return nextIndex; //if list is empty
}


template<class T>
Queue<T> filter(Queue<T> queue,Condition c)      //copy c'tor for T
{                                                //template for the function object??
  Queue<T> filteredQueue;
  int size = queue.size();
  while(size>0)                                  //> ? >=
  {
    if(c(queue.front()))
    {
      filteredQueue.pushBack(queue.front());
    }
    queue.popFront();
    size--;
  }
  return filteredQueue;
}


template<class T>
Queue<T>& transform(Queue<T>& queue,Object operation)
{
  int size = queue.size();      //could have been done with [] operator
  while (size>0)                // > or >=
  {
  operation(queue.front());
  queue.pushBack(queue.front());
  queue.popFront();
  size--;
  }
}


















#endif //Queue_H