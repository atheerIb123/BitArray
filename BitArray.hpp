#ifndef BITARRAY_HPP
#define BITARRAY_HPP

#include <iostream>
#include <cstring>
#include <cmath> 

using namespace std;

class BitArray
{
public:
    BitArray();
    BitArray(const BitArray& copy);
    ~BitArray();
    void SetAt(size_t index, bool value);
    bool GetAt(size_t index) const;

private:
    size_t m_size_bits;
    unsigned char* m_data; //Using unsigned because it's easier for bit manipulation

    void expand(size_t newSize);
};

#endif // BITARRAY_HPP