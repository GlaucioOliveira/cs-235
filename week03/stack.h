/***********************************************************************
 * Header:
 *    Array
 * Summary:
 *    This class contains a stack data structure
 *
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <cassert>  // because I am paranoid
#include <iostream>

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * STACK
 * A class that holds stuff
 ***********************************************/
template <class T>
class stack
{
public:
   // constructors and destructors
    stack() { numElements = 0; numCapacity = 0; array = NULL; }
   stack(int numElements);
   stack(const stack & rhs);
  ~stack() { 
      if (numCapacity > 0 )
      {
            delete[] array;
      }
          
  }
   stack & operator = (const stack & rhs);
   
   // standard container interfaces
   // stack treats size and max_size the same
   int  size()     const { return numElements;                 }
   int  max_size() const { return numElements;                 }
   int capacity()  const { return numCapacity; }
   bool  empty()   const { return numElements == 0; }

   void clear() { 
       numElements = 0; 
   }
   
   
   void push(T t) {
       expandArray();

       array[numElements] = t;
       numElements++;   
   }

   void pop() {
       if(numElements > 0)
        numElements--;
   }

   T top() const {
       if (numElements > 0)
           return array[numElements - 1];
       else
           throw "ERROR: Unable to reference the element from an empty Stack";
   }

   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (array); }
   iterator end();

   // a debug utility to display the stack
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * array;
   int numElements;
   int numCapacity;

   void expandArray() {
       //if there is no more space to add another item on the array
       if (numElements + 1 > capacity())
       {
           T* tempArray = NULL;

           if (capacity() > 0)
               numCapacity *= 2;
           else
               numCapacity = 1;

           try
           {
               tempArray = new T[numCapacity];
           }
           catch (std::bad_alloc)
           {
               throw "ERROR: Unable to allocate buffer";
           }
           
           if (numCapacity > 1) {
               for (int i = 0; i < numElements; i++)
                   tempArray[i] = array[i];

               delete[] array;
               array = tempArray;
           }
           else
           {
               array = tempArray;
           }
       }
   }
};

/**************************************************
 * STACK ITERATOR
 * An iterator through stack
 *************************************************/
template <class T>
class stack <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }
   
private:
   T * p;
};


/********************************************
 * STACK :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename stack <T> :: iterator stack <T> :: end ()
{
   return iterator (array + numElements);
}

/*******************************************
 * STACK :: Assignment
 *******************************************/
template <class T>
stack <T> & stack <T> :: operator = (const stack <T> & rhs)
{
   // we can only copy stacks of equal size. Vectors are not this way!
   if (rhs.size() != size())
   {
      //throw "ERROR: Unable to copy stacks of different sizes";
       try
       {
           array = NULL;
           delete[] array;

           array = new T[rhs.size()];
           numElements = rhs.numElements;
           numCapacity = rhs.numCapacity;

       }
       catch (std::bad_alloc)
       {
           throw "ERROR: Unable to allocate a new buffer for stack";
       }
   }

   assert(numElements == rhs.numElements);

   for (int i = 0; i < numElements; i++)
      array[i] = rhs.array[i];

   return *this;
}

/*******************************************
 * STACK :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
stack <T> :: stack(const stack <T> & rhs) 
{
   assert(rhs.numElements >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.numElements == 0)
   {
      numElements = 0;
      numCapacity = 0;
      array = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      array = new T[rhs.numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for stack";
   }
   
   // copy over the capacity
   numElements = rhs.numElements;
   numCapacity = rhs.numCapacity;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      array[i] = rhs.array[i];
}

/**********************************************
 * STACK : NON-DEFAULT CONSTRUCTOR
 * Preallocate the stack to "capacity"
 **********************************************/
template <class T>
stack <T> :: stack(int numCapacity) 
{
   assert(numElements >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an stack, this is kinda pointless
   if (numCapacity == 0)
   {
      this->numCapacity = 0;
      numElements = 0;

      this->array = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      array = new T[numCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   this->numElements = 0;
   this->numCapacity = numCapacity;
}

/********************************************
 * STACK : DISPLAY
 * A debug utility to display the contents of the stack
 *******************************************/
template <class T>
void stack <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "stack<T>::display()\n";
   std::cerr << "\tnumElements = " << numElements << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tarray[" << i << "] = " << array[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // STACK_H

