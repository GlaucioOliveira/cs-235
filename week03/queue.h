/***********************************************************************
 * Header:
 *    Array
 * Summary:
 *    This class contains a queue data structure
 *
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>
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
	 * queue
	 * A class that holds stuff
	 ***********************************************/
	template <class T>
	class queue
	{
	public:
		// constructors and destructors
		queue() {
			initializeFields();
		}

		queue(int numCapacity);
		queue(const queue& rhs);
		~queue() {
			if (numCapacity > 0)
			{
				try
				{
					delete[] array;
				}
				catch (const std::exception&)
				{

				}
			}

		}
		queue& operator = (const queue& rhs);	//assign

		// standard container interfaces
		// queue treats size and max_size the same
		int  size()     const { return numElements; }
		int  max_size() const { return numElements; }
		int capacity()  const { return numCapacity; }
		bool  empty()   const { return numElements == 0; }

		void clear() {
			numPop = 0;
			numPush = 0;
			iHead = 0;
			iTail = 0; //-1
			numElements = 0;
			hasSpace = false;
		}

		void push(T item) {
			expandArray();

			array[iTail] = item;

			numElements++;
			numPush++;
		}

		void pop() {
			//array[iHead] = NULL;

			iHead++;
			numPop++;
			numElements--;
		}

		T back() const {
			if (numElements > 0)
				return array[iTail];
			else
				throw "ERROR: Unable to reference the element from an empty queue";
		}

		//@todo: create a getter and a setter for this function...
		T front() const {
			if (numElements > 0)
			{
				if (iHead == 0)
					return array[0];
				else
					return array[iHead];
			}
			else
				throw "ERROR: Unable to reference the element from an empty queue";
		}

		// a debug utility to display the queue
		// this gets compiled to nothing if NDEBUG is defined
		void display() const;

	private:
		T* array;
		int numElements;
		int numCapacity;
		int numPush;
		int numPop;
		int iHead;
		int iTail;
		bool hasSpace;
		bool fromNonDefaultConstructor;

		void initializeFields(){
			numPop = 0;
			numPush = 0;
			numCapacity = 0;
			array = NULL;
			iHead = 0;
			iTail = 0; // -1
			numElements = 0;
			hasSpace = false;
			fromNonDefaultConstructor = false;
		}

		void expandArray()
		{
			int nextElementCount = numElements + 1 + numPop;

			if (nextElementCount > numCapacity)
			{
				if (nextElementCount <= (numCapacity + numPop))
				{
					if (numPop > 0 && hasSpace == false)
					{
						hasSpace = true;
						iTail = 0;
						return;
					}

					if ((iTail /*+ 1*/) < iHead)
					{
						iTail++;
						return;
					}
				}

				T* tempArray = NULL;

				if (numCapacity > 0)
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
					if (hasSpace)
					{
						int tempArrayIndex = 0;

						for (int i = iHead - 1; i < numPush; i++)
						{
							tempArray[tempArrayIndex] = array[i];
							tempArrayIndex++;
						}

						for (int i = 0; i < iTail; i++)
						{
							tempArray[tempArrayIndex] = array[i];
							tempArrayIndex++;
						}

						iHead = 0;
						iTail = numElements - 1;
						hasSpace = false;
					}
					else
					{
						for (int i = 0; i < numElements; i++)
						{
							tempArray[i] = array[i];
						}
					}

					delete[] array;
					array = tempArray;
				}
				else
				{
					array = tempArray;
					return;
				}
			}

			if(iTail == 0 && fromNonDefaultConstructor == false)
				iTail++;
		}
	};

	/*******************************************
	 * queue :: Assignment
	 *******************************************/
	template <class T>
	queue <T>& queue <T> :: operator = (const queue <T>& rhs)
	{
		if (numCapacity < rhs.size())
		{
			//resize(rhs.size());
		   //throw "ERROR: Unable to copy queues of different sizes";
			try
			{
				initializeFields();

				delete[] array;

				array = new T[rhs.size()];
				numElements = rhs.numElements;
				numCapacity = rhs.numCapacity;

			}
			catch (std::bad_alloc)
			{
				throw "ERROR: Unable to allocate a new buffer for queue";
			}
		}

		//assert(numElements == rhs.numElements);

		for (int i = 0; i < rhs.numElements; i++)
			array[i] = rhs.array[i];

		return *this;
	}

	/*******************************************
	 * queue :: COPY CONSTRUCTOR
	 *******************************************/
	template <class T>
	queue <T> ::queue(const queue <T>& rhs)
	{
		assert(rhs.numCapacity >= 0);

		// do nothing if there is nothing to do
		if (rhs.numElements == 0)
		{
			initializeFields();
			return;
		}

		// attempt to allocate
		try
		{
			array = new T[rhs.numCapacity];
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: Unable to allocate a new buffer for queue";
		}

		// copy over the capacity
		numElements = rhs.numElements;
		numCapacity = rhs.numCapacity;
		numPush = rhs.numPush;
		numPop = rhs.numPop;
		iHead = rhs.iHead;
		iTail = rhs.iTail;
		hasSpace = rhs.hasSpace;

		// copy the items over one at a time using the assignment operator
		for (int i = 0; i < numElements; i++)
			array[i] = rhs.array[i];
	}

	/**********************************************
	 * queue : NON-DEFAULT CONSTRUCTOR
	 * Preallocate the queue to "capacity"
	 **********************************************/
	template <class T>
	queue <T> ::queue(int numCapacity)
	{
		assert(numCapacity >= 0);

		initializeFields();

		// do nothing if there is nothing to do.
		// since we can't grow an queue, this is kinda pointless
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
		fromNonDefaultConstructor = true;
	}

	/********************************************
	 * queue : DISPLAY
	 * A debug utility to display the contents of the queue
	 *******************************************/
	template <class T>
	void queue <T> ::display() const
	{
#ifndef NDEBUG
		std::cerr << "queue<T>::display()\n";
		std::cerr << "\tnumElements = " << numElements << "\n";
		for (int i = 0; i < numElements; i++)
			std::cerr << "\tarray[" << i << "] = " << array[i] << "\n";
#endif // NDEBUG
	}

}; // namespace custom

#endif // queue_H

