/***********************************************************************
 * Header:
 *    Array
 * Summary:
 *    This class contains the notion of an array: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       array             : similar to std::array
 *       array :: iterator : an iterator through the array
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef ARRAY_H
#define ARRAY_H

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
 * ARRAY
 * A class that holds stuff
 ***********************************************/
template <class T>
class array
{
public:
   // constructors and destructors
   array(int num);
   array(const array & rhs);
  ~array()                         { delete [] data;   }
   array & operator = (const array & rhs);
   
   // standard container interfaces
   // array treats size and max_size the same
   int  size()     const { return num;                 }
   int  max_size() const { return num;                 }
   
   // array-specific interfaces
   // what would happen if I passed -1 or something greater than num?
   T & operator [] (int index)
   {
      return data[index];
   }
   const T & operator [] (int index) const 
   {
      return data[index];
   }
   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();

   // a debug utility to display the array
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * data;              // dynamically allocated array of T
   int num;               // both the capacity and the number of elements
};

/**************************************************
 * ARRAY ITERATOR
 * An iterator through array
 *************************************************/
template <class T>
class array <T> :: iterator
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
 * ARRAY :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename array <T> :: iterator array <T> :: end ()
{
   return iterator (data + num);
}

/*******************************************
 * ARRAY :: Assignment
 *******************************************/
template <class T>
array <T> & array <T> :: operator = (const array <T> & rhs)
{
   // we can only copy arrays of equal size. Vectors are not this way!
   if (rhs.size() != size())
   {
      throw "ERROR: Unable to copy arrays of different sizes";
   }

   assert(num == rhs.num);
   for (int i = 0; i < num; i++)
      data[i] = rhs.data[i];

   return *this;
}

/*******************************************
 * ARRAY :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
array <T> :: array(const array <T> & rhs) 
{
   assert(rhs.num >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.num == 0)
   {
      num = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity
   num = rhs.num;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < num; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * ARRAY : NON-DEFAULT CONSTRUCTOR
 * Preallocate the array to "capacity"
 **********************************************/
template <class T>
array <T> :: array(int num) 
{
   assert(num >= 0);
   
   // do nothing if there is nothing to do.
   // since we can't grow an array, this is kinda pointless
   if (num == 0)
   {
      this->num = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->num = num;
}

/********************************************
 * ARRAY : DISPLAY
 * A debug utility to display the contents of the array
 *******************************************/
template <class T>
void array <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "array<T>::display()\n";
   std::cerr << "\tnum = " << num << "\n";
   for (int i = 0; i < num; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}

}; // namespace custom

#endif // ARRAY_H

