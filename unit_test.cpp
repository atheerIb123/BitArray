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

    cout << "\nAll tests passed!" << endl;
    return 0;
}