#include <iostream>
#include <cstring>

#include "BitArray.hpp"

using namespace std;

static const size_t BITS_IN_BYTE = 8;
static const size_t ROUND_UP = BITS_IN_BYTE - 1;

inline size_t bitsToBytes(size_t bitsAmount)
{
    return (bitsAmount + ROUND_UP) / BITS_IN_BYTE;
}

//Changed to uniform initialization
BitArray::BitArray() : m_size_bits{0}, m_data{nullptr} {}

BitArray::BitArray(const BitArray& copy) : m_size_bits(copy.m_size_bits), m_data(nullptr)
{
    if (this->m_size_bits > 0)
    {
        size_t numBytes = bitsToBytes(m_size_bits);

        try {
            this->m_data = new unsigned char[numBytes];
        } 
        catch (const bad_alloc&)
        {
            throw;
        }

        memcpy(this->m_data, copy.m_data, numBytes);
    }
}

BitArray::~BitArray()
{
    delete[] this->m_data;
}

void BitArray::expand(size_t newSizeBits)
{
    size_t newAmountOfBytes = bitsToBytes(newSizeBits);
    size_t oldAmountOfBytes = bitsToBytes(this->m_size_bits);

    //Excluding the case of empty array because it should be initialized with 1 byte
    if (this->m_size_bits > 0 && newAmountOfBytes == oldAmountOfBytes)
    {
        this->m_size_bits = newSizeBits;
        return;
    }

    unsigned char* newData;

    try{
        newData = new unsigned char[newAmountOfBytes];
    }
    catch(const bad_alloc&)
    {
        throw;
    }

    memset(newData, 0, newAmountOfBytes);

    if (m_data)
    {
        memcpy(newData, this->m_data, oldAmountOfBytes);
        delete[] m_data;
    }   
    
    this->m_size_bits = newSizeBits;
    this->m_data = newData;
}

void BitArray::SetAt(size_t index, bool value)
{
    if (index >= m_size_bits)
    {
        expand(index + 1);
    }

    size_t byteIndex = index / BITS_IN_BYTE;
    size_t bitIndexInByte = index % BITS_IN_BYTE;

    unsigned char bitMask = 1 << bitIndexInByte;

    if (value)
    {
        this->m_data[byteIndex] = this->m_data[byteIndex] | bitMask;
    }
    else
    {
        this->m_data[byteIndex] = this->m_data[byteIndex] & ~(bitMask);
    }
}

bool BitArray::GetAt(size_t index) const
{
    if (index >= this->m_size_bits)
    {
        return false;
    }

    size_t indexInBytes = index / BITS_IN_BYTE; 
    size_t indexInSpecificByte = index % BITS_IN_BYTE; 
    unsigned char bitMask = 1 << indexInSpecificByte;
    
    return (this->m_data[indexInBytes] & bitMask) != 0; 
}

bool BitArray::ToBinaryStr(char* o_binary_string, size_t binary_string_size) const
{
    if (binary_string_size < this->m_size_bits)
    {
        return false;
    }
    
    if (binary_string_size == 0)
    {
        return true;
    }

    for (size_t i = 0 ; i < this->m_size_bits ; ++i)
    {
        size_t outputIndex = this->m_size_bits - 1 - i;
        o_binary_string[outputIndex] = this->GetAt(i) == true ? '1' : '0';
    }

    //This way surely m_size_bits <= string size because of the condition at the beginning of the function 
    o_binary_string[this->m_size_bits] = '\0';
    return true;
}

bool BitArray::FromBinaryStr(const char* i_binary_string, size_t binary_string_length)
{
    //Supposing someone sends an empty string "\0"...
    if (binary_string_length == 0)
    {
        return true;
    }

    for (int i = binary_string_length - 1 ; i >= 0 ; i--)
    {
        //Input sanity check
        if (i_binary_string[i] > '1' || i_binary_string[i] < '0')
            return false;
        bool currentVal = i_binary_string[i] == '1' ? true : false;
        this->SetAt(i, currentVal);
    }

    return true;
}