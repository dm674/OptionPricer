#ifndef WRAPPER_H
#define WRAPPER_H


// provides various functionalities which are intended to make it act like a pointer
// to a single object but with added responsibilities
template< class T> // Template => not cpp file
class Wrapper
{
public:
    // Need default constructor, to allow Wrapper pointing to nothing (e.g. for vector<Wrapper>)
    Wrapper()
    { DataPtr =0;}

    Wrapper(const T& inner)
    {
        DataPtr = inner.clone();
    }

    ~Wrapper() {
        if (DataPtr != 0)
            delete DataPtr;
    }

    Wrapper(const Wrapper<T>& original)
    {
        if (original.DataPtr !=0)
            DataPtr = original.DataPtr->clone();
        else
            DataPtr=0;
    }

    // object previously pointed to must be deleted,
    // and then a copy of the new object must be created
    // so each Wrapper still owns precisely one object.
    Wrapper& operator=(const Wrapper<T>& original)
    {
        if (this != &original)
        {
            if (DataPtr!=0)
                delete DataPtr;
            DataPtr = (original.DataPtr !=0) ?
                      original.DataPtr->clone() : 0;
        }
        return *this;
    }

    // Need to be able to dereference the Wrapper to obtain underlying object
    T& operator*()
    {
        return *DataPtr;
    }

    const T& operator*() const
    {
        return *DataPtr;
    }

    // Need to be able to access methods; more elegant than (*mywrapper).theMethod()
    const T* const operator->() const
    {
        return DataPtr;
    }

    T* operator->()
    {
        return DataPtr;
    }
private:
    T* DataPtr;
};

#endif