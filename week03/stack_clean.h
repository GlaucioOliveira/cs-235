/***********************************************************************
 * Header:
 *    stack
 * Summary:
 *    
 *    This will contain the class definition of:
 *       
 * Author
 *    Br. Helfrich
 ************************************************************************/


#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>


namespace custom
{
template <class T>
class stack
{
public:
	stack();
	stack(int numCapacity);
	stack(const stack& rhs);
	~stack();
	stack assign(stack rhs);

	int  size()     const { return numElements; }
	int capacity()  const { return numCapacity; }
	bool empty()    const {
		return !numElements;
	}
	void clear() { numElements = 0; }
	void push(const T t) {

	}

	void pop()
	{

	
	}

	void top()
	{

	}

private:
	T* array;
	int numElements;
	int numCapacity;
	void resize(int numCapacity);
};

}


#endif