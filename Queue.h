#ifndef EX3_Queue_H
#define EX3_Queue_H

#include <iostream>

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
  explicit Queue(int size = INITIAL_SIZE);
  Queue(const Queue& queue);
  ~Queue();
  Queue& operator=(const Queue& queue);

  void pushBack(T newObject);               
  T& front();
  const T& front() const; 
  void popFront();
  int size() const;  
  class Iterator;
  class ConstIterator;
  Iterator begin();
  Iterator end(); 
  ConstIterator begin() const;
  ConstIterator end() const; 
  class EmptyQueue{};
};


template<class T>
class Queue<T>::Iterator 
{
  friend class Queue<T>;
  Queue<T>* m_queue; 
  int m_index;
  Iterator(Queue<T>* queue, int index);    
  public :
  T& operator*(); 
  Iterator& operator++();
  bool operator!=(Iterator iterator) const ;
  class InvalidOperation{};
};

template<class T>
Queue<T>::Iterator::Iterator(Queue<T>* queue, int index) :
m_queue(queue), m_index(index)                    
{}

template<class T>
typename Queue<T>::Iterator Queue<T>::begin()  
{
  return Iterator(this,0);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end()  
{
  return Iterator(this,(*this).size());  
}

template<class T>
 T& Queue<T>::Iterator::operator*()
{ 
  if( m_index>=m_queue->size())
  {
    throw InvalidOperation();
  }
  return m_queue->m_data[m_index]; 
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
  m_index++;
    if( m_index>m_queue->size())
    {
      throw InvalidOperation();
    }
  return *this;
} 

template<class T>
bool Queue<T>::Iterator::operator!=(Iterator iterator) const 
{
  return ( !(m_index == iterator.m_index)); 
}


template<class T>
class Queue<T>::ConstIterator
{
  friend class Queue<T>;
  const Queue<T>* m_queue;
  int m_index;
  ConstIterator(const Queue<T>* queue, int index);
  

 public :
  const T& operator*() const; 
  ConstIterator& operator++();
  bool operator!=(const ConstIterator& iterator) const;
  class InvalidOperation{};
};


template<class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, int index) :
m_queue(queue), m_index(index)                   
{}                       

template<class T>
const T& Queue<T>::ConstIterator::operator*() const {
  if(m_index>=m_queue->size()) 
  {
    throw InvalidOperation();
  }
  return m_queue->m_data[m_index];   
}

template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
  m_index++;
  if(m_index>m_queue->size()) 
  {
    throw InvalidOperation();
  }
  return *this;         
} 

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& iterator) const
{
  return ( !(m_index == iterator.m_index)); 
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const   
{
  return ConstIterator(this,0);
}


template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
  return ConstIterator(this,m_nextIndex); 
}

template<class T>
 const T& Queue<T>::front() const
{
  if(m_nextIndex<=0)
  {
     throw  EmptyQueue();
  }
  return m_data[0];
}

template<class T>
void Queue<T>::expand() 
{

  int newSize = m_maxSize * EXPAND_RATE;  
  T *newData = new T[newSize];
  try
  {
  for (int i = 0; i < m_nextIndex; ++i) 
    {
      newData[i] = m_data[i];           
    }
  }
  catch (std::exception&)
  {
    delete[] newData;
    throw ;
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
    throw ; 
  }
}

template<class T>
Queue<T>::Queue(const Queue<T>& queue) : 
m_data(new T[queue.size()]),   
m_maxSize(queue.size()),
m_nextIndex(queue.m_nextIndex)
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
  T* newData = new T[queue.size()];    
  m_maxSize=queue.m_maxSize;
  m_nextIndex=queue.m_nextIndex;
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
  if(m_nextIndex >= m_maxSize)
  {
    expand();
  }
  m_data[m_nextIndex] = newObject;     
  m_nextIndex++;
}

template<class T>
T& Queue<T>::front()
{ 
  if(m_nextIndex<=0)
  {
    throw  EmptyQueue();
  }
  return m_data[0];
}

template<class T>
void Queue<T>::popFront()
{
  if(m_nextIndex<=0)
  {
    throw EmptyQueue();    
  }
  for (int i=0 ; i<m_nextIndex-1 ; ++i)   
  {
    m_data[i]=m_data[i+1];    
  }
    m_nextIndex--;
}


template<class T>
int Queue<T>::size() const
{
  return m_nextIndex;  
}


template<class T,typename Condition>
Queue<T> filter(Queue<T> queue,Condition condition)      
{                                   
  Queue<T> filteredQueue;
  int size = queue.size(); 
  while(size>0)                                  
  {
    if(condition(queue.front()))
    {
      filteredQueue.pushBack(queue.front());
    }
    queue.popFront();                            
    size--;
  }
  return filteredQueue;
}

template<class T,typename Operation>
Queue<T>& transform(Queue<T>& queue,Operation operation)
{
  int size = queue.size();     
  while (size>0)                
  {
  operation(queue.front());                 
  queue.pushBack(queue.front());           
  queue.popFront();                        
  size--;                                  
  }
  return queue;                                              
} 

#endif //Queue_H
