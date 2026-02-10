#ifndef BITARRAY_HPP
#define BITARRAY_HPP

class BitArray
{
public:
    BitArray();
    BitArray(const BitArray& copy);
    ~BitArray();
    //Sets the bit at the specified index to the given value. If the index is out of the current bounds of the BitArray, we call expand.
    void SetAt(size_t index, bool value);
    //Returns the value of the bit at the specified index.
    bool GetAt(size_t index) const;
    //Converts an amount of bits values from the BitArray to string binary representation.
    bool ToBinaryStr(char* o_binary_string, size_t binary_string_size) const;
    //Changes content of a BitArray according to a binary string
    bool FromBinaryStr(const char* i_binary_string, size_t binary_string_length);
private:
    size_t m_size_bits;
    unsigned char* m_data; 
    //Expands the BitArray to fit a new size in bits.
    void expand(size_t newSize);
};

#endif // BITARRAY_HPP