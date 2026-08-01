#include <assert.h>
#include <iostream>
#include "my_string.hpp"

void testDefaultConstructor() {
    MyString str;
    assert(str.length() == 0);
    std::cout << "default constructor tests passed\n";
}

void testConstructorWithCapacity() {
    MyString str(10);
    assert(str.length() == 0);
    std::cout << "constructor with specified capacity passed!\n";
}

void testConstructorWithInvalidCpacity() {
    try {
        MyString(0);
        assert(false);
    } catch (std::invalid_argument&) {
        std::cout << "invalid argument exception test passed\n";
    }
}

void testConstructorFromString() {
    MyString str("hello world!");
    assert(str.length() == 12);
    assert(str == "hello world!");
    std::cout << "constructor from specified string passed\n";
}

void testConstructorEmptyString() {
    MyString str("");
    assert(str.length() == 0);
    assert(str == "");
    std::cout << "constructor from empty string test passed\n";
}

void testCopyConstructor() {
    MyString str1("hello world!");
    MyString str2(str1);
    assert(str2 == "hello world!");
    assert(str1.length() == str2.length());
    assert(str1 == str2);
    std::cout << "copy constructor test passed\n";
}

void testCopyConstructorIndependent() {
    MyString str1("hello world!");
    MyString str2(str1);
    assert(str1 == str2);
    str1 = "hallo werld!";
    assert(str1 != str2);
    std::cout << "copy constructor independent test passed\n";
}

void testAddString() {
    MyString str("hello");
    assert(str + " world!" == "hello world!");
    assert(str == "hello");
    assert((str + " world!").length() == 12);
    std::cout << "string addition test passed\n";
}

void testAddStringWithSingleResize() {
    MyString str(10);
    str += "hello world! this text will resize str.data";
    assert(str.length() == 43);
    assert(str == "hello world! this text will resize str.data");
    std::cout << "test add triggers a single resize test passed\n";
}

void testAddStringWithMultipleResizes() {
    MyString str(2);
    str += "hello"; // size and capacity are 5 here
    str += " world!"; // size and capacity are 12 here
    str += "this text will resize str.data"; // size and capacity are 43 here
    std::cout << "test add triggers multiple resize test passed\n";
}

void testStringAssignment() {
    MyString str;
    assert(str.length() == 0);
    str = "hello world!";
    assert(str.length() == 12);
    assert(str == "hello world!");
    std::cout << "string Assignment test passed\n";
}

void testAssignmentFromEmptyString() {
    MyString str("hello world!");
    str = "";
    assert(str.length() == 0);
    assert(str == "");
    std::cout << "Assignment from empty string test passed\n";
}

void testMyStringAssignment() {
    MyString str1("hello world!");
    MyString str2("hallo werlde");
    assert(str1 != str2);
    str1 = str2;
    assert(str1 == str2);
    std::cout << "MyString Assignment test passed\n";
}

void testAssignmentIndependence() {
    MyString str1("hello world!");
    MyString str2;
    str2 = str1;
    assert(str1 == str2);
    str1 = "hallo werlde!";
    assert(str1 != str2);
    std::cout << "Assignment independent test passed\n";
}

void testSelfAssignment() {
    MyString str1("hello world!");
    str1 = str1;
    assert(str1 == "hello world!");
    std::cout << "assignment to self test passed\n";
}

void testConcatination() {
    MyString str("hello");
    str += " world!";
    assert(str.length() == 12);
    assert(str == "hello world!");
    std::cout << "string concatination test passed\n";
}

void testConcatintionWithEmptyString() {
    assert(MyString("hello") + "" == "hello");
    std::cout << "concatination with empty string test passed\n";
}

void testConcatinationFromEmptyString() {
    assert(MyString("") + "" == "");
    std::cout << "concatination from empty string test passed\n";
}

void testAtIndex() {
    std::string text = "hello world!";
    MyString str(text);
    assert(str == text);
    for (size_t i = 0; i < str.length(); i++)
        assert(str[i] == text.at(i));
    std::cout << "[] test passed\n";
}

void testIndexOutOfBounds() {
    try {
        MyString("hello world!")[1000];
        assert(false);
    } catch (std::out_of_range&) {
        std::cout << "out of bounds exception test passed\n";
    }
}

void testIndexJustOutOfBounds() {
    try {
        MyString("hello world!")[12];
        assert(false);
    } catch (std::out_of_range&) {
        std::cout << "just out of bounds exception test passed\n";
    }
}

void testStartsWith() {
    assert(!MyString("hello world!").start_with("hallo"));
    assert(MyString("hello world!").start_with("hello"));
    std::cout << "starts with test passed\n";
}

void testBasicContains() {
    assert(!MyString("hello world!").contains("hallo"));
    assert(MyString("hello world!").contains("hello"));
    assert(MyString("abababa").contains("ababa"));
    assert(MyString("abababa").contains("babab"));
    std::cout << "basic contains test passed\n";
}

void testEmptyStringContains() {
    assert(MyString("").contains(""));
    assert(!MyString("").contains("a"));
    std::cout << "empty string contains test passed\n";
}

void testComplexStringContains() {
    assert(MyString("wdYD^\\YmfX`B_mIhQovpLJdEc[XXT\\URX^iaFShNQDYsgAtWlD^ZL\\[YtUXiLfL^MWiQXIuvJTjaOfkk]Th[A[juPaMBwvNWVXQSdyhHaG\\NhGCFUrKrgpxYHRwpxJPkbOpancjbjdhspyXVZicgIK^`CD\\sxWM_lqT]qnO_Yn^GOqYVZWmcTkYKrsOlxne_PzvG[CDTveWI[N^pcAOHAbBcTWilVVXD]hAozPRr[KwCVF`_mL^UBKIxXnWL[ICuVR\\olH]wldUGcHRxqZYbFUqr_qltBWEMC`z[suMYDA[KxEfnNG^DFIzFHdnNWCQH\\Z_PkktdSCAPXCiROojagyE^vXVqShDPgnnEaKRSN^PzrqteCVuby`njwVsCBrPxhnLnYxzRpFqHLomYoEmbnlbBqzIKSnQqnz_CtnGSDsfa]hfNnkivXhJCgtXUgtdIrVPFSKD_apQC[nk_WTSM\\vrcZMNMslOzGloWRzdCQpFM]sMBeP]d").contains("gnnEaKRSN^PzrqteCVuby`njwVsCBrPxhnLnYxzRpFqHLomYoEmbnlbBqzIKSnQqnz_CtnGSDsfa]hfNnkivXhJCgtXUgtdIrVPFSKD_apQC[nk_WTSM\\vr"));
    assert(!MyString("wdYD^\\YmfX`B_mIhQovpLJdEc[XXT\\URX^iaFShNQDYsgAtWlD^ZL\\[YtUXiLfL^MWiQXIuvJTjaOfkk]Th[A[juPaMBwvNWVXQSdyhHaG\\NhGCFUrKrgpxYHRwpxJPkbOpancjbjdhspyXVZicgIK^`CD\\sxWM_lqT]qnO_Yn^GOqYVZWmcTkYKrsOlxne_PzvG[CDTveWI[N^pcAOHAbBcTWilVVXD]hAozPRr[KwCVF`_mL^UBKIxXnWL[ICuVR\\olH]wldUGcHRxqZYbFUqr_qltBWEMC`z[suMYDA[KxEfnNG^DFIzFHdnNWCQH\\Z_PkktdSCAPXCiROojagyE^vXVqShDPgnnEaKRSN^PzrqteCVuby`njwVsCBrPxhnLnYxzRpFqHLomYoEmbnlbBqzIKSnQqnz_CtnGSDsfa]hfNnkivXhJCgtXUgtdIrVPFSKD_apQC[nk_WTSM\\vrcZMNMslOzGloWRzdCQpFM]sMBeP]d").contains("MvFftnypaKrWN\\PpIpxkeuFoWvOF[fjRSYUVNqvm]^_cuGZdsdKu`FOQTs`nXYqMZso\\ei`sAZ`qE`PMtxkQUHDFXNkBFxZUibvj"));
    std::cout << "complex string contains test passed\n";
}

int main() {
    testDefaultConstructor();
    testConstructorWithCapacity();
    testConstructorWithInvalidCpacity();
    testConstructorFromString();
    testCopyConstructor();
    testCopyConstructorIndependent();
    testAddString();
    testAddStringWithSingleResize();
    testAddStringWithMultipleResizes();
    testStringAssignment();
    testAssignmentFromEmptyString();
    testAssignmentIndependence();
    testSelfAssignment();
    testConcatination();
    testConcatintionWithEmptyString();
    testConcatinationFromEmptyString();
    testAtIndex();
    testIndexOutOfBounds();
    testIndexJustOutOfBounds();
    testMyStringAssignment();
    testStartsWith();
    testBasicContains();
    testEmptyStringContains();
    testComplexStringContains();
    std::cout << "all tests passed!\n";
    return 0;
}