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
    bool ToBinaryStr(char* o_binary_string, size_t binary_string_size) const;
    bool FromBinaryStr(const char* i_binary_string, size_t binary_string_length);

private:
    size_t m_size_bits;
    unsigned char* m_data; //Using unsigned because it's easier for bit manipulation
    
    void expand(size_t newSize);
};

#endif // BITARRAY_HPP