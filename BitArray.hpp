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
private:
    size_t m_size_bits;
    unsigned char* m_data; //Using unsigned because it's easier for bit manipulation

    //Expands the BitArray to fit a new size in bits.
    void expand(size_t newSize);
};

#endif // BITARRAY_HPP