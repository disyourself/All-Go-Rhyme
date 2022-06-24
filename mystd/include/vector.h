#ifndef VECTOR_H
#define VECTOR_H

namespace mystd
{

template
class vector
{
private:
    int size;
    int capacity;
    void* begin, *end;

public:
    vector();
    ~vector();
};

vector::vector()
{

    
}

vector::~vector()
{
}






















} // namespace mystd
#endif
