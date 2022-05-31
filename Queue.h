#ifndef EX3_Queue_H
#define EX3_Queue_H

#include <iostream>
#include <new>

const int EXPAND_RATE =2;
const int INITIAL_SIZE = 10;

//line 74 very important comment 
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
  void popFront();
  //int size();
  int size() const;  //added const here
  class Iterator;
  class ConstIterator;
  Iterator begin();
  Iterator end(); 
  ConstIterator begin() const;
  ConstIterator end() const; 
  class EmptyQueue{};
};




 template<class T>
 class Queue<T>::Iterator {
   friend class Queue<T>;
   Queue<T>* m_queue; //typename?  //removed cons from here 
   int m_index;
   Iterator(Queue<T>* queue, int index);   //removed const from queue parameter 
  

 public :
   const T& operator*(); //removed const from here -- needed
   Iterator& operator++();
   bool operator!=(Iterator iterator) const ;
   class InvalidOperation{};
 };



//----------------------------------------------------------------------------------

template<class T>
Queue<T>::Iterator::Iterator(Queue<T>* queue, int index) :
m_queue(queue), m_index(index)                    //assignment operator for T
{}

template<class T>
typename Queue<T>::Iterator Queue<T>::begin() //const problematic 
{
  return Iterator(this,0);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end() //remmoved const from herer and from begin 
{
  return Iterator(this,(*this).size());  // the *this is problematic
}

template<class T>
const T& Queue<T>::Iterator::operator*()  { //removed const from here
  //assert(index >= 0 && index < (m_queue.size()));       //replace the assert
    if( m_index>=m_queue->size())  //==1?
    {
        throw InvalidOperation();
    }
  return m_queue->m_data[m_index]; //operator ->() for Queue<T>
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
  if(m_index>=(m_queue->size()-1))
  {
      throw InvalidOperation();
  }
  m_index++;            //const iterator hmmmm
  return *this;
} 

template<class T>
bool Queue<T>::Iterator::operator!=(Iterator iterator) const //removed & from here t6l3 blmtseget brdo
{
  //assert(queue == i.queue);  //== operator for 
  return ( m_index == iterator.m_index);
}
//----------------------------------------------------------------------------------
 template<class T>
 class Queue<T>::ConstIterator {
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
m_queue(queue), m_index(index)                    //assignment operator for T
{}                       

template<class T>
const T& Queue<T>::ConstIterator::operator*() const {
  //assert(index >= 0 && index < (m_queue.size()));       //replace the assert
    if(m_index>=m_queue->size()) //added now
    {
        throw InvalidOperation();
    }
  return m_queue->m_data[m_index];   //operator ->() for Queue<T> ??
}

template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if(m_index>=m_queue->size()-1) //added now
    {
        throw InvalidOperation();
    }
  m_index++;            //const iterator hmmmm
  return *this;         //this should be a const iterator - we define it to be a const iterator 
} 

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& iterator) const
{
  //assert(queue == i.queue);  //== operator for 
  return ( m_index == iterator.m_index);
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const  //overload begin and end 
{
  return ConstIterator(this,0);
}


template<class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
  return ConstIterator(this,m_nextIndex); //check validity
}



//-----------------------------------------------------------------------------------
template<class T>
void Queue<T>::expand() 
{

    int newSize = m_maxSize * EXPAND_RATE;  //removed try catch
    T *newData = new T[newSize];
//T should have a default c'tor //may be problematic answer in whatsapp group
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
    throw ; // sho nzrok??
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
  T* newData = new T[queue.size()];    //T should have a default c'tor //removed try catch
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
  if(m_nextIndex >= m_maxSize)
  {
    expand();
  }
  m_data[m_nextIndex] = newObject;     //may need try and catch
 //copy c'tor / assignment operator for T
  m_nextIndex++;
}

template<class T>
T& Queue<T>::front()
{ 
  if(m_nextIndex<=0)
  {
    //EmptyQueue e();   //how can it be replaced
    throw  EmptyQueue();
  }
  return m_data[0];

  
}

template<class T>
void Queue<T>::popFront()
{
  if(m_nextIndex<=0)
  {
    //Queue<T>::EmptyQueue error();
    throw EmptyQueue();    //chnaged to reference 
  }
  for (int i=0 ; i<m_nextIndex-1 ; ++i)   //should be nextIndex-1  true //problem is here
  {
    m_data[i]=m_data[i+1];    //maybe try catch        //careful for out of bounds //change next index?
  }
    m_nextIndex--;
}


template<class T>
int Queue<T>::size() const
{
//  if(m_nextIndex<0)
//  {
//   // Queue<T>::EmptyQueue error();
//    throw EmptyQueue();
// }
  return m_nextIndex; //if list is empty     no problem 
}


template<class T,typename Condition>
Queue<T> filter(Queue<T> queue,Condition condition)      //copy c'tor for T
{      
//  if(queue.size()<=0)
//  {
//    throw typename Queue<T>::EmptyQueue();
//  }                                          //template for the function object??
  Queue<T> filteredQueue;
  int size = queue.size(); //hen emkn
  while(size>0)                                  //> true ? >= false
  {
    if(condition(queue.front()))
    {
      filteredQueue.pushBack(queue.front());
    }
    queue.popFront();                           // hek mshaneem queue , lazm Queue<T> tmp = queue 
    size--;
  }
  return filteredQueue;
}

template<class T,typename Operation>
Queue<T>& transform(Queue<T>& queue,Operation operation)
{
//  if(queue.size()<=0)
//  {
//    //typename Queue<T>::EmptyQueue e();         //no one catches here
//    throw typename Queue<T>::EmptyQueue();
//  }
  int size = queue.size();     
  while (size>0)                // > true or >= false
  {
  operation(queue.front());                // a3tked hen 4lt 
  queue.pushBack(queue.front());           // athen sa7 hkol lazm for(int i=0 ; i<size ; i++)
  queue.popFront();                        // { operation(m_data[i])} sa3etha lazm frined
  size--;                                  // aw lazm Queue<T> tmp = queue; ......
  }
  return queue;    //or queue&                                          
} 

#endif //Queue_H


//the purpose of making an iterator and a const iterator is to use the regular 
// - non const iterator to change the queue that it points to 
// for example we can use the non const iterator for the transfrom fucntion
// while const iterator just gives you the ability to iterate over a Queue in read only

//  template<class T>
//  class Queue<T>::ConstIterator {
//    friend class Queue<T>;
//    const Queue<T>* m_queue;
//    int m_index;
//    ConstIterator(const Queue<T>* queue, int index);
  

//  public :
//    const T& operator*() const;
//    Iterator& operator++();
//    bool operator!=(const Iterator& iterator) const;
//    class InvalidOperation{};
//  };


// template<class T>
// Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, int index) :
// m_queue(queue), m_index(index)                    //assignment operator for T
// {}                       

// template<class T>
// const T& Queue<T>::ConstIterator::operator*() const {
//   //assert(index >= 0 && index < (m_queue.size()));       //replace the assert
//   return m_queue->m_data[m_index];   //operator ->() for Queue<T>
// }

// template<class T>
// typename Queue<T>::ConstIterator& Queue<T>::Iterator::operator++()
// {
//   m_index++;            //const iterator hmmmm
//   return *this;         //this should be a const iterator - we define it to be a const iterator 
// } 

// template<class T>
// bool Queue<T>::Iterator::operator!=(const Iterator& iterator) const
// {
//   //assert(queue == i.queue);  //== operator for 
//   return ( m_index == iterator.m_index);
// }


//changed the non const Iterator to be non const so that there will be nom conflicts
//between its methods and ConstIterator methods removed &from operator != in non const but it's there 
//in constiterator 

//changed e in throw to errors was conflicting - why?