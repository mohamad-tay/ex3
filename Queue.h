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
  Queue(const Queue& queue);
  ~Queue();
  Queue& operator=(const Queue& queue);

  void pushBack(T newObject);               
  T& front();
  void popFront();
  int size(); 
  class Iterator;
  Iterator begin() const;
  Iterator end() const;  
  class EmptyQueue{};
}




template<class T>
class Queue<T>::Iterator {
  const Queue<T>* m_queue;
  int m_index;
  Iterator(const Queue<T>* queue, int index);
  friend class Queue<T>;

public :
  const T& operator*() const;
  Iterator& operator++();
  bool operator!=(const Iterator& iterator) const;
  class InvalidOperation{};
}



//----------------------------------------------------------------------------------

template<class T>
Queue<T>::Iterator::Iterator(const Queue<T>* queue, int index) :
m_queue(queue), m_index(index)                    //assignment operator for T
{}

template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::begin()
{
  return Iterator(this,0);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::end()
{
  return Iterator(this,m_queue.size());
}

template<class T>
const T& Queue<T>::Iterator::operator*() const {
  assert(index >= 0 && index < (m_queue.size()));       //replace the assert
  return queue->m_data[index];   //operator ->() for Queue<T>
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
  m_index++;            //const iterator hmmmm
  return *this;
} 

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator)
{
  //assert(queue == i.queue);  //== operator for 
  return ( m_index == iterator.m_index);
}
//----------------------------------------------------------------------------------

template<class T>
void Queue<T>::expand() 
{
  int newSize = m_maxSize * EXPAND_RATE;
  try
  {
  T* newData = new T[newSize];    //T should have a default c'tor //may be problematic answer in whatsapp group
  }
  catch (const std::bad_alloc& e)
  {
    cerr << e.what() << endl;
  }
  try 
  {
  for (int i = 0; i < m_nextIndex; ++i) //check
  {
    newData[i] = m_data[i];           //T should have assignment operator  +++bdeka
  }  
  }
  catch (std::exception&)
  {
    delete[] newData;
    throw;
  }
  delete[] m_data;
  m_data = newData;
  m_maxSize = newSize;
}

template<class T>
Queue<T>::Queue(int size):
m_data(new T[size]),          
m_maxSize(size),
m_nextIndex(0)
{
  if(size <= 0 )
  {
    delete[] m_data;
    throw ; // sho nzrok??
  }
}

template<class T>
Queue<T>::Queue(const Queue<T>& queue) : 
m_data(new T[queue.size()]),   
m_maxsize(queue.size()),
m_nextindex(queue.m_nextindex)
{
  try{
  for (int i=0 ; i<(queue.size()) ; ++i)
  {
    m_data[i]=queue.m_data[i];
  }
  }
  catch (std::exception&)
  {
    delete m_data;
    throw;
  }
}

template<class T>
Queue<T>::~Queue()
{
  delete[] m_data;
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue)
{
  if (this==&queue)
  {
    return *this;
  }
  try
  {
  T* newData = new T[queue.size()];    //T should have a default c'tor 
  }
  catch (const std::bad_alloc& e)
  {
    cerr << e.what() << endl;
  }
  m_maxSize=queue.m_maxSize;
  m_nextIndex=queue.m_maxIndex;
  try 
  {
  for (int i=0 ; i<(queue.size()) ; ++i)
  {
    newData[i]=queue.m_data[i];
  }
  }
  catch (std::exception&)
  {
    delete[] newData;
    throw;
  }
  delete[] m_data;
  m_data = newData;
  return *this;
}

template<class T>
void Queue<T>::pushBack(T newObject)
{
  if(nextIndex >= maxSize)
  {
    expand();
  }
  m_data[nextIndex] = newObject;     //may need try and catch 
 //copy c'tor / assignment operator for T
  nextIndex++; 
}

template<class T>
T& Queue<T>::front()
{ 
  if(m_nextIndex==0)
  {
    Queue<T>::EmptyQueue e();
    throw e;
  }
  return m_data[0];

  
}

template<class T>
void Queue<T>::popFront()
{
  if(m_nextIndex==0)
  {
    Queue<T>::EmptyQueue e();
    throw e;
  }
  for (int i=0 ; i<nextIndex-1 ; ++i)   //should be nextIndex-1  true
  {
    m_data[i]=m_data[i+1];    //maybe try catch        //careful for out of bounds //change next index?
    nextIndex--;
  }
}


template<class T>
int Queue<T>::size()
{
  if(m_nextIndex==0)
  {
    Queue<T>::EmptyQueue e();
    throw e;
  }
  return m_nextIndex; //if list is empty     no problem 
}


template<class T>
Queue<T> filter(Queue<T> queue,Condition c)      //copy c'tor for T
{      
  if(queue.m_nextIndex==0)
  {
    Queue<T>::EmptyQueue e();
    throw e;
  }                                          //template for the function object??
  Queue<T> filteredQueue;
  int size = queue.size();
  while(size>0)                                  //> true ? >= false
  {
    if(c(queue.front()))
    {
      filteredQueue.pushBack(queue.front());
    }
    queue.popFront();                           // hek mshaneem queue , lazm Queue<T> tmp = queue 
    size--;
  }
  return filteredQueue;
}


template<class T>
Queue<T>& transform(Queue<T>& queue,Object operation)
{
  if(queue.m_nextIndex==0)
  {
    Queue<T>::EmptyQueue e();
    throw e;
  }
  int size = queue.size();     
  while (size>0)                // > true or >= false
  {
  operation(queue.front());                // a3tked hen 6lt 
  queue.pushBack(queue.front());           // athem sa7 hkol lazm for(int i=0 ; i<size ; i++)
  queue.popFront();                        // { operation(m_data[i])} sa3etha lazm frined
  size--;                                  // aw lazm Queue<T> tmp = queue; ......
  }                                          
} 

#endif //Queue_H
                                         