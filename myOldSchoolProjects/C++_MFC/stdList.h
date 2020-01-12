#include <list>

typedef enum DirectionEnum 
{ 
  DIRECTION_NONE, 
  DIRECTION_FORWARD, 
  DIRECTION_BACKWARD
};

// //////////////////////////////////////////////////////////////////////////////
//  NAME:        StdListClass<TYPE>
//  DESCRIPTION: dynamic list. this list is simply a cover of the std::list
// //////////////////////////////////////////////////////////////////////////////
template <class TYPE>
class StdListClass 
{
public:

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        empty constructor
  //  DESCRIPTION: the list is created empty. one dummy element is allocated at
  //               the inner list
  // ////////////////////////////////////////////////////////////////////////////
  StdListClass();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        operator =
  //  DESCRIPTION: copy one list to other
  // ////////////////////////////////////////////////////////////////////////////
	StdListClass& operator= (const StdListClass& list);
	
  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        PushFront
  //  DESCRIPTION: push 'element' at front. the new element will be the first
  //               element in the list.
  //  RETURNS:     void
  // ////////////////////////////////////////////////////////////////////////////
  void PushFront (const TYPE& element);

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        PushBack 
  //  DESCRIPTION: push 'element' at the back. the new element will be the last
  //               element in the list
  //  RETURNS:     void
  // ////////////////////////////////////////////////////////////////////////////
  void PushBack (const TYPE& element);

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        RemoveFront
  //  DESCRIPTION: remove the element currently place at the front of the list. 
  //  RETURNS:     void
  // ////////////////////////////////////////////////////////////////////////////
  void RemoveFront ();
  
  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        RemoveBack
  //  DESCRIPTION: remove the element currently place at the back of the list. 
  //  RETURNS:     void
  // ////////////////////////////////////////////////////////////////////////////
  void RemoveBack ();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Front 
  //  DESCRIPTION: returns reference to the element currently place at the front 
  //               of the list. if the list is empty, 
  //               reference to dummy object is returned (probably garbaged)
  //  RETURNS:     TYPE&
  // ////////////////////////////////////////////////////////////////////////////
  TYPE& Front ();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Front 
  //  DESCRIPTION: returns reference to the element currently place at the front 
  //               of the list. if the list is empty,
  //               reference to dummy object is returned (probably garbaged)
  //  RETURNS:     const TYPE&
  // ////////////////////////////////////////////////////////////////////////////
  const TYPE& Front () const;

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Back
  //  DESCRIPTION: returns reference to the element currently place at the back 
  //               of the list. if the list is empty, 
  //               reference to dummy object is returned (probably garbaged)
  //  RETURNS:     TYPE&
  // ////////////////////////////////////////////////////////////////////////////
  TYPE& Back ();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Back
  //  DESCRIPTION: returns reference to the element currently place at the back 
  //               of the list.if the list is empty,
  //               reference to dummy object is returned (probably garbaged)
  //  RETURNS:     const TYPE&
  // ////////////////////////////////////////////////////////////////////////////
  const TYPE& Back () const;

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Clear
  //  DESCRIPTION: removes all the elements from the container. after clearing, 
  //               no scan is active
  //  RETURNS:     void
  // ////////////////////////////////////////////////////////////////////////////
  void Clear ();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        operator []
  //  DESCRIPTION: returns the reference of the 'index' element (cont[0] is equal
  //               to cont.Front()). is container has less than 'index' + 1 
  //               elements (indexing starts from 0), 
  //               reference to dummy object is returned (probably garbaged)
  //  RETURNS:     TYPE& 
  // ////////////////////////////////////////////////////////////////////////////
  TYPE& operator [] (unsigned int index);

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        operator []
  //  DESCRIPTION: returns the reference of the 'index' element (cont[0] is equal
  //               to cont.Front()). is container has less than 'index' + 1 
  //               elements (indexing starts from 0), 
  //               reference to dummy object is returned (probably garbaged)
  //  RETURNS:     const TYPE& 
  // ////////////////////////////////////////////////////////////////////////////
  const TYPE& operator [] (unsigned int index) const;

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        ScanInit
  //  DESCRIPTION: this method start scaning of list to the direction 'direction'.
  //               the direction may be one of DIRECTION_FORWARD or
  //               DIRECTION_BACKWARD. scaning forward starts from the first 
  //               element (the one at front), to the last one. scaning backward
  //               is the opposite. from the moment you start scaning, all the 
  //               methods: HasMoreElements, NextElement may be called. after the
  //               first call to NextElement, the methods: RemoveCurrent, 
  //               InsertBefore, InsertAfter may be called. 
  //  RETURNS:     void
  // ////////////////////////////////////////////////////////////////////////////
  void ScanInit (DirectionEnum direction) const;


  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        HasMoreElements
  //  DESCRIPTION: while scaning, you may use this method to know if there are 
  //               more elements to scan. in other words, if the next call to
  //               NextElement succeeds or fail. (!) notice that a call to 
  //               NextElement when there are no more elements cause exception.
  //  RETURNS:     BOOL
  // ////////////////////////////////////////////////////////////////////////////
  BOOL HasMoreElements() const;

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        NextElement
  //  DESCRIPTION: returns a reference to the next element in the active scan.
  //  RETURNS:     TYPE&
  // ////////////////////////////////////////////////////////////////////////////
  TYPE& NextElement ();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        NextElement
  //  DESCRIPTION: returns a reference to the next element in the active scan.
  //  RETURNS:     const TYPE&
  // ////////////////////////////////////////////////////////////////////////////
  const TYPE& NextElement () const;

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        RemoveCurrent
  //  DESCRIPTION: removes the current element. the current element is usualy the 
  //               last element whose reference received by NextElement, but it 
  //               may changed if you call to RemoveCurrent, or InsertAfter.
  //               if the operation is successful, the new "current element" is 
  //               the element previous to the last "current element", depends on
  //               the direction of scaning
  //  RETURNS:     void
  // ////////////////////////////////////////////////////////////////////////////
  void RemoveCurrent ();

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        InsertAfter
  //  DESCRIPTION: inserts 'element' after the current element (see RemoveCurrent)
  //               if the operation is successful. the new element is the new 
  //               current element
  //  RETURNS:     void
  // ////////////////////////////////////////////////////////////////////////////
  void InsertAfter ( const TYPE& element);

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        InsertBefore
  //  DESCRIPTION: inserts 'element' before the current element (see RemoveCurrent)  
	//               the current element stay same
  //  RETURNS:     void
  // ////////////////////////////////////////////////////////////////////////////
  void InsertBefore (const TYPE& element);

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        RemoveByIndex
  //  DESCRIPTION: removes the 'index' elements from the start (RemoveByIndex(0),
  //               is identical to RemoveFront()). 
  //  RETURNS:     void
  // ////////////////////////////////////////////////////////////////////////////
  void RemoveByIndex (int index);

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Size
  //  DESCRIPTION: returns the number of elements in the list
  //  RETURNS:     unsigned int 
  // ////////////////////////////////////////////////////////////////////////////
  unsigned int Size () const;

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        FindElement
  //  DESCRIPTION: found element and returns it's index
  //  RETURNS:     int 
  // ////////////////////////////////////////////////////////////////////////////
	int FindElement(const TYPE& element);

  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        IsEmpty
  //  DESCRIPTION: the list is empty if there are no elements in it. 
  //  RETURNS:     BOOL
  // ////////////////////////////////////////////////////////////////////////////
  BOOL IsEmpty() const;


  // ////////////////////////////////////////////////////////////////////////////
  //  NAME:        Replace
  //  DESCRIPTION: swap between two elements
  //  RETURNS:     void
  // ////////////////////////////////////////////////////////////////////////////
  void Replace (int indx1,int indx2);

protected:
  std::list<TYPE> m_list;

  mutable DirectionEnum m_direction;
  mutable std::list<TYPE>::iterator m_iter;
  mutable std::list<TYPE>::reverse_iterator m_revIter;

  TYPE* DummyElementPtr ();
  const TYPE* DummyElementPtr () const;
};

// implementations for StdListClass<TYPE>
template <class TYPE>
StdListClass<TYPE>::StdListClass<TYPE> () : m_direction (DIRECTION_NONE)
{};

template <class TYPE>
StdListClass<TYPE>& 
StdListClass<TYPE>::operator= (const StdListClass<TYPE>& list)
{
		Clear();
	  list.ScanInit(DIRECTION_FORWARD);
	  while (list.HasMoreElements()) 
		{			
	 		PushBack(list.NextElement());
		}
		return *this;
}

template <class TYPE>
TYPE* 
StdListClass<TYPE>::DummyElementPtr ()
{
  return &(*(m_list.end()));
}

template <class TYPE>
const TYPE* 
StdListClass<TYPE>::DummyElementPtr () const
{
  return &(*(m_list.end()));
}

template <class TYPE>
void 
StdListClass<TYPE>::PushFront (const TYPE& element)
{  
  m_list.push_front (element);
  m_direction = DIRECTION_NONE;
}

template <class TYPE>
void 
StdListClass<TYPE>::PushBack (const TYPE& element)
{
  m_list.push_back (element);
  m_direction = DIRECTION_NONE;
}

template <class TYPE>
void
StdListClass<TYPE>::RemoveFront ()
{
  if (!m_list.empty()) 
	{
    m_list.pop_front();
    m_direction = DIRECTION_NONE;
  }
}

template <class TYPE>
void 
StdListClass<TYPE>::RemoveBack ()
{
  if (!m_list.empty()) 
	{
    m_list.pop_back();
    m_direction = DIRECTION_NONE;
  }
}

template <class TYPE>
TYPE& 
StdListClass<TYPE>::Front ()
{
  TYPE *elementPtr;
  if (m_list.empty())
  {
    elementPtr = DummyElementPtr();
  }
  else
	{
		elementPtr = &(*m_list.begin());
	}

  return *elementPtr;
}

template <class TYPE>
const TYPE& 
StdListClass<TYPE>::Front () const
{
  const TYPE *elementPtr;

  if (m_list.empty())
  {
    elementPtr = DummyElementPtr();
  }
  else
	{
		elementPtr = &(*m_list.begin());
	}  

  return *elementPtr;
}

template <class TYPE>
TYPE& 
StdListClass<TYPE>::Back ()
{
  TYPE *elementPtr;

  if (m_list.empty())
  {
    elementPtr = DummyElementPtr();
  }
  else
	{
		elementPtr = &(*(--m_list.end()));
	}  

  return *elementPtr;
}

template <class TYPE>
const TYPE& 
StdListClass<TYPE>::Back () const
{
  const TYPE *elementPtr;

  if (m_list.empty())
  {
    elementPtr = DummyElementPtr();
  }
  else
	{
		 elementPtr = &(*(--m_list.end()));
	}   

  return *elementPtr;
}

template <class TYPE>
void StdListClass<TYPE>::Clear ()
{
  m_list.clear();
  m_direction = DIRECTION_NONE;
}

template <class TYPE>
TYPE& 
StdListClass<TYPE>::operator [] (unsigned int index)
{
  std::list<TYPE>::iterator tempIter;
  int ind = index;
  TYPE *elementPtr;

  for (tempIter = m_list.begin();
       tempIter != m_list.end() && ind;
       tempIter++, ind--);

  if (tempIter == m_list.end())
  {
    elementPtr = DummyElementPtr();
  }
  else
  {
    elementPtr = &(*tempIter);
  }

  return *elementPtr;
}

template <class TYPE>
const TYPE& 
StdListClass<TYPE>::operator [] (unsigned index) const
{
  std::list<TYPE>::const_iterator tempIter;
  int ind = index;
  const TYPE *elementPtr;

  for (tempIter = m_list.begin();
       tempIter != m_list.end() && ind;
       tempIter++, ind--);

  if (tempIter == m_list.end())
  {
    elementPtr = DummyElementPtr();
  }
  else
  {
    elementPtr = &(*tempIter);
  }

  return *elementPtr;
}

template <class TYPE>
void StdListClass<TYPE>::ScanInit (DirectionEnum direction) const
{

  std::list<TYPE> *innerList = const_cast <std::list<TYPE> *> (&m_list);
  if (direction == DIRECTION_FORWARD)
  {
    m_direction = DIRECTION_FORWARD;
    m_iter = innerList->begin();
  }
  else if (direction == DIRECTION_BACKWARD)
  {
    m_direction = DIRECTION_BACKWARD;
    m_revIter = innerList->rbegin();
  }
  else
  {
    m_direction = DIRECTION_NONE;
  }
}

template <class TYPE>
BOOL StdListClass<TYPE>::HasMoreElements () const 
{
  BOOL result = FALSE;

  if (m_direction == DIRECTION_FORWARD)
	{
		result = BOOL(std::list<TYPE>::const_iterator(m_iter) != m_list.end());
	}  
  else
	{
		 result = BOOL(std::list<TYPE>::const_reverse_iterator(m_revIter.base()) != m_list.rend());
	}   

  return result;
}

template <class TYPE>
TYPE& 
StdListClass<TYPE>::NextElement()
{
  TYPE* elementPtr;

  if (!HasMoreElements())
  {
    elementPtr = DummyElementPtr();
  }
  else
  {
    if (m_direction == DIRECTION_FORWARD) 
		{
      elementPtr = &(*m_iter);
      m_iter++;
    }
    else
    {
      elementPtr = &(*m_revIter);
      m_revIter++;
    }
  }

  return *elementPtr;
}

template <class TYPE>
const TYPE& 
StdListClass<TYPE>::NextElement() const
{
  const TYPE* elementPtr;

  if (!HasMoreElements())
  {
    elementPtr = DummyElementPtr();
  }
  else
  {
    if (m_direction == DIRECTION_FORWARD) 
		{
      elementPtr = &(*m_iter);
      m_iter++;
    }
    else
    {
      elementPtr = &(*m_revIter);
      m_revIter++;
    }
  }

  return *elementPtr;
}

template <class TYPE>
void StdListClass<TYPE>::RemoveCurrent ()
{
  if (m_direction != DIRECTION_NONE)
  {
		if (m_direction == DIRECTION_FORWARD) 
		{
			if (m_iter != m_list.begin())
			{
				m_iter--;
				m_iter = m_list.erase (m_iter);
			}
		}
		else
		{
			if (m_revIter != m_list.rbegin())
			{
				m_revIter = std::list<TYPE>::reverse_iterator(m_list.erase (m_revIter.base()));
			}
		}
	}
}

template <class TYPE>
void
StdListClass<TYPE>::InsertAfter (const TYPE& element)
{
  if (m_direction != DIRECTION_NONE)
  {
		if (m_direction == DIRECTION_FORWARD) 
		{
			if (m_iter != m_list.begin())
			{
				m_list.insert (m_iter, element);
			}				
		}
		else
		{
			if (m_revIter != m_list.rbegin())
			{
				std::list<TYPE>::iterator tempItem = m_list.insert(m_revIter.base(), element);
				m_revIter = std::list<TYPE>::reverse_iterator(tempItem);
			}
		}
	}
}


template <class TYPE>
void
StdListClass<TYPE>::InsertBefore (const TYPE& element)
{  
  if (m_direction != DIRECTION_NONE)
  {
		if (m_direction == DIRECTION_FORWARD) 
		{
			if (m_iter != m_list.begin())
			{
				std::list<TYPE>::iterator tempIter = m_iter;
				m_list.insert(--tempIter, element);
			}
		}
		else
		{
			if (m_revIter != m_list.rbegin())
			{
				std::list<TYPE>::iterator tempIter = m_revIter.base();
				m_list.insert(++tempIter, element);
			}
		}
	}
}

template <class TYPE>
void
StdListClass<TYPE>::RemoveByIndex (int index)
{
  std::list<TYPE>::iterator tempIter;
  int ind = index;

  for (tempIter = m_list.begin();
       tempIter != m_list.end() && ind;
       tempIter++, ind--);

  if (tempIter != m_list.end())
  {
    m_list.erase (tempIter);
    m_direction = DIRECTION_NONE;
  }
}

template <class TYPE>
unsigned int StdListClass<TYPE>::Size () const
{
  return m_list.size();
}

template <class TYPE>
int 
StdListClass<TYPE>::FindElement(const TYPE& element)
{
  int retVal = NOT_FOUND; 
  int i = 0;

  std::list<TYPE>::const_iterator myIter = m_list.begin();

  while (myIter != m_list.end())
  {
    if (element == *myIter)
    {
      retVal = i;
      break;
    }
		else
		{
			i++;
		}
     
    myIter++;
  }
  return retVal;
}

template <class TYPE>
BOOL 
StdListClass<TYPE>::IsEmpty () const
{
  return m_list.empty();
}

template <class TYPE>
void
StdListClass<TYPE>::Replace (int indx1,int indx2)
{
  std::list<TYPE>::iterator tempIter1;
  std::list<TYPE>::iterator tempIter2;

  int ind1 = indx1;
  int ind2 = indx2;

  TYPE tempElement;
  
  for (tempIter1 = m_list.begin();
       tempIter1 != m_list.end() && ind1;
       tempIter1++, ind1--);

	for (tempIter2 = m_list.begin();
       tempIter2 != m_list.end() && ind2;
       tempIter2++, ind2--);

  if (tempIter1 != m_list.end() && tempIter2 != m_list.end())
  {    
    tempElement = *tempIter1;
		*tempIter1 = *tempIter2;
		*tempIter2 = tempElement;
  }
}





