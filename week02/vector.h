/***********************************************************************
 * Header:
 *    Array
 * Summary:
 *    This class contains the notion of an vector: a bucket to hold
 *    array for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       vector             : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * VECTOR
 * A class that holds stuff
 ***********************************************/
template <class T>
class vector
{
public:
   // constructors and destructors
    vector() { numElements = 0; numCapacity = 0; }
   vector(int numElements);
   vector(const vector & rhs);
  ~vector() { if(numCapacity > 0) delete[] array; }
   vector & operator = (const vector & rhs);
   
   // standard container interfaces
   // vector treats size and max_size the same
   int  size()     const { return numElements;                 }
   int  max_size() const { return numElements;                 }
   int capacity()  const { return numCapacity; }
   bool  empty()   const { return numElements == 0; }

   void clear() { 
       //array = NULL;
       //delete[] array;

       numElements = 0; 
       //numCapacity = 0;

       //array = new T[numCapacity];
   }
   
   void push_back(T t) {
       expandArray();
       array[numElements] = t;

       numElements++;   
   }

   T & operator [] (int index) throw (const char*)
   {
       if (index > numCapacity || index < 0)
       {
           throw "Index needs to be from 0 to " + numCapacity;
       }
           return array[index];    
   }

   //Read-only [] operator
   const T & operator [] (int index) const throw (const char*)
   {
       if (index > numCapacity || index < 0)
       {
           throw "Index needs to be from 0 to " + numCapacity;
       }
           return array[index]; 
   }
   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (array); }
   iterator end();

   // a debug utility to display the vector
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * array;              // dynamically allocated vector of T
   int numElements;               // both the capacity and the numElementsber of elements
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
 * VECTOR ITERATOR
 * An iterator through vector
 *************************************************/
template <class T>
class vector <T> :: iterator
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
 * VECTOR :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename vector <T> :: iterator vector <T> :: end ()
{
   return iterator (array + numElements);
}

/*******************************************
 * VECTOR :: Assignment
 *******************************************/
template <class T>
vector <T> & vector <T> :: operator = (const vector <T> & rhs)
{
   // we can only copy vectors of equal size. Vectors are not this way!
   if (rhs.size() != size())
   {
      //throw "ERROR: Unable to copy vectors of different sizes";
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
           throw "ERROR: Unable to allocate a new buffer for vector";
       }
   }

   assert(numElements == rhs.numElements);

   for (int i = 0; i < numElements; i++)
      array[i] = rhs.array[i];

   return *this;
}

/*******************************************
 * VECTOR :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
vector <T> :: vector(const vector <T> & rhs) 
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
      throw "ERROR: Unable to allocate a new buffer for vector";
   }
   
   // copy over the capacity
   numElements = rhs.numElements;
   numCapacity = rhs.numCapacity;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++)
      array[i] = rhs.array[i];
}

/**********************************************
 * VECTOR : NON-DEFAULT CONSTRUCTOR
 * Preallocate the vector to "capacity"
 **********************************************/
template <class T>
vector <T> :: vector(int numElements) 
{
   assert(numElements >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an vector, this is kinda pointless
   if (numElements == 0)
   {
      this->numElements = 0;
      numCapacity = 0;

      this->array = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      array = new T[numElements];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->numElements = numElements;
   numCapacity = numElements;
}

/********************************************
 * VECTOR : DISPLAY
 * A debug utility to display the contents of the vector
 *******************************************/
template <class T>
void vector <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "vector<T>::display()\n";
   std::cerr << "\tnumElements = " << numElements << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tarray[" << i << "] = " << array[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // VECTOR_H

