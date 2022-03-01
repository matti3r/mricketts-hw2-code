#pragma once

#include "list.h"

template <typename Object>
class Stack
{
public:
    bool isEmpty() const
    {
        return theList.size() == 0;
    }
    const Object& top() const
    {
        return theList.front();
    }
    void push(const Object& x)
    {
        theList.push_front(x);
    }
    Object& pop()
    {
        Object retVal = theList.front();
        theList.remove(theList.begin());
        return retVal;
    }
private:
    List<Object> theList;
};