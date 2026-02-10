#include "BitArray.hpp"

/*
Constructor: Initializes an empty BitArray with no allocated memory.
 */
BitArray::BitArray() : m_size_bits(0), m_data(nullptr) {}

/*
Copy Constructor: Creates a new BitArray as a copy of an existing one.
*/
BitArray::BitArray(const BitArray& copy) : m_size_bits(copy.m_size_bits), m_data(nullptr)
{
    if (this->m_size_bits > 0)
    {
        size_t numBytes = (m_size_bits + 7) / 8; // Suppose I have 7 bits that occupy a space in the array. I'd like to have 1 byte and not 0 that's why I need sort of a ceil
        this->m_data = new unsigned char[numBytes];
        memcpy(this->m_data, copy.m_data, numBytes);
    }
}

/*
Destructor: Frees allocated memory when a BitArray object is destroyed.
*/
BitArray::~BitArray()
{
    delete[] this->m_data;
}

/*
expand: Expands the BitArray to fit a new size in bits.
*/
void BitArray::expand(size_t newSizeBits)
{
    size_t newAmountOfBytes = (newSizeBits + 7) / 8;
    unsigned char* newData = new unsigned char[newAmountOfBytes];
    memset(newData, 0, newAmountOfBytes);

    if (m_data)
    {
        size_t oldAmountOfBytes = (this->m_size_bits + 7) / 8;
        memcpy(newData, this->m_data, oldAmountOfBytes);
        delete[] m_data;
    }   
    
    this->m_size_bits = newSizeBits;
    this->m_data = newData;
}

/*
SetAt: sets the bit at the specified index to the given value.
If the index is out of the current bounds of the BitArray, we call expand.
*/
void BitArray::SetAt(size_t index, bool value)
{
    if (index >= m_size_bits)
    {
        expand(index + 1);
    }

    size_t byteIndex = index / 8;
    size_t bitIndexInByte = index % 8;

    unsigned char bitMask = 1 << bitIndexInByte;

    if (value == true)
    {
        this->m_data[byteIndex] = this->m_data[byteIndex] | bitMask;
    }
    else
    {
        this->m_data[byteIndex] = this->m_data[byteIndex] & ~(bitMask);
    }
}

/*
GetAt: returns the value of the bit at the specified index.
*/
bool BitArray::GetAt(size_t index) const
{
    if (index >= this->m_size_bits)
    {
        return false;
    }

    size_t indexInBytes = index / 8; //no need for ceil because we start from indexBytes = 0
    size_t indexInSpecificByte = index % 8; //here we'd get which bit of the given byte we want to return
    unsigned char bitMask = 1 << indexInSpecificByte;
    
    return (this->m_data[indexInBytes] & bitMask) != 0; //bitwise AND for getting the value of the specific index (1 would be in the bit we'd like to return from m_data)
}


/*
A static helper method that converts and appends a given (integer) value to o_binary_string 
*/
// 

/*
ToBinaryStr: converts an amount of bits values from the BitArray to string binary representation.
*/
bool BitArray::ToBinaryStr(char* o_binary_string, size_t binary_string_size) const
{
    if (binary_string_size > this->m_size_bits)
    {
        return false;
    }
    
    if (binary_string_size == 0)
    {
        return true;
    }

    size_t offset = binary_string_size - 1;
    for (int i = offset ; i >= 0 ; i--)
    {
        o_binary_string[i] = this->GetAt(offset - i) == true ? '1' : '0';
    }
    
    o_binary_string[binary_string_size] = '\0';
    return true;
}

bool BitArray::FromBinaryStr(const char* i_binary_string, size_t binary_string_length)
{
    //Assuming same constraint as for ToBinaryStr
    if (binary_string_length > this->m_size_bits)
    {
        return false;
    }
    
    //Supposing someone sends an empty string "\0"...
    if (binary_string_length == 0)
    {
        return true;
    }

    for (int i = binary_string_length - 1 ; i >= 0 ; i--)
    {
        bool currentVal = i_binary_string[i] == '1' ? true : false;
        this->SetAt(i, currentVal);
    }

    return true;
}