#include <iostream>
#include <cassert>
#include "BitArray.hpp"


void TestDefaultConstructor()
{
    BitArray arr;
    assert(arr.GetAt(0) == false);
    assert(arr.GetAt(50) == false);
    assert(arr.GetAt(1000) == false);
    cout << "TestDefaultConstructor passed" << endl;
}

void TestSetAndGet()
{
    BitArray arr;

    arr.SetAt(0, true);
    assert(arr.GetAt(0) == true);

    arr.SetAt(0, false);
    assert(arr.GetAt(0) == false);

    arr.SetAt(7, true);
    assert(arr.GetAt(7) == true);
    assert(arr.GetAt(6) == false);
    
    cout << "TestSetAndGet passed" << endl;
}

void TestExpandPadding()
{
    BitArray arr;
    arr.SetAt(3, true);
    arr.SetAt(100, true);

     
    assert(arr.GetAt(3) == true);
    assert(arr.GetAt(100) == true);
    
    for (size_t i = 4; i < 100; i++)
        assert(arr.GetAt(i) == false);

    cout << "TestExpandPadding passed" << endl;
}

void TestGetBeyondCapacity()
{
    BitArray arr;
    arr.SetAt(5, true);

    assert(arr.GetAt(999) == false);
    assert(arr.GetAt(5) == true);

    cout << "TestGetBeyondCapacity passed" << endl;
}

void TestMultipleBitsInSameByte()
{
    BitArray arr;
    arr.SetAt(0, true);
    arr.SetAt(1, true);
    arr.SetAt(2, false);
    arr.SetAt(3, true);
    arr.SetAt(4, false);
    arr.SetAt(5, true);
    arr.SetAt(6, true);
    arr.SetAt(7, true);

    assert(arr.GetAt(0) == true);
    assert(arr.GetAt(1) == true);
    assert(arr.GetAt(2) == false);
    assert(arr.GetAt(3) == true);
    assert(arr.GetAt(4) == false);
    assert(arr.GetAt(5) == true);
    assert(arr.GetAt(6) == true);
    assert(arr.GetAt(7) == true);

    cout << "TestMultipleBitsInSameByte passed" << endl;
}

void TestCopyConstructor()
{
    BitArray original;
    original.SetAt(0, true);
    original.SetAt(15, true);
    original.SetAt(99, true);

    BitArray copy(original);

    assert(copy.GetAt(0) == true);
    assert(copy.GetAt(15) == true);
    assert(copy.GetAt(99) == true);
    assert(copy.GetAt(50) == false);

    copy.SetAt(0, false);
    assert(copy.GetAt(0) == false);
    assert(original.GetAt(0) == true);

    original.SetAt(15, false);
    assert(original.GetAt(15) == false);
    assert(copy.GetAt(15) == true);

    cout << "TestCopyConstructor passed" << endl;
}

void TestLargeIndex()
{
    BitArray arr;
    arr.SetAt(100000, true);

    assert(arr.GetAt(100000) == true);
    assert(arr.GetAt(99999) == false);
    assert(arr.GetAt(0) == false);

    cout << "TestLargeIndex passed" << endl;
}

void TestCopyOfEmptyArray()
{
    BitArray empty;
    BitArray copy(empty);

    assert(copy.GetAt(0) == false);
    assert(copy.GetAt(100) == false);

    cout << "TestCopyOfEmptyArray passed" << endl;
}

void TestToBinaryStr()
{
    //normal test
    char output[9];
    BitArray arr; 
    for (size_t i = 0 ; i < 8 ; i++)
    {
        arr.SetAt(i, true);
    }

    assert(arr.ToBinaryStr(output, 8) == true);
    assert(strcmp(output, "11111111") == 0);
    
    //test biger input size..
    assert(arr.ToBinaryStr(output, 12) == false);

    //test alternating 
    char output2[13];
    for (size_t i = 0 ; i < 12 ; i++)
    {
        arr.SetAt(i, i % 2);
    }

    assert(arr.ToBinaryStr(output2, 12) == true);
    assert(strcmp(output2, "101010101010") == 0);

    cout << "TestToBinaryStr passed" << endl;
}

void TestFromBinaryStr()
{
    BitArray arr;
    arr.SetAt(9, true);
    //Changing bit index 9 to false
    assert(arr.FromBinaryStr("1111111110", 10) == true);
    assert(arr.GetAt(9) == false);

    //Chaning it back to true
    assert(arr.FromBinaryStr("1111111111", 10) == true);
    assert(arr.GetAt(9) == true);
    
    char output[11];
    //Changing it so it contains zeros only
    assert(arr.FromBinaryStr("0000000000", 10) == true);
    assert(arr.ToBinaryStr(output, 10) == true);
    assert(strcmp(output, "0000000000") == 0);

    cout << "TestFromBinaryStr passed" << endl;
}
int main()
{
    TestDefaultConstructor();
    TestSetAndGet();
    TestExpandPadding();
    TestGetBeyondCapacity();
    TestMultipleBitsInSameByte();
    TestCopyConstructor();
    TestLargeIndex();
    TestCopyOfEmptyArray();
    TestToBinaryStr();
    TestFromBinaryStr();

    cout << "\nAll tests passed!" << endl;
    return 0;
}