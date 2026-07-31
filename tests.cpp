#include <assert.h>
#include <iostream>
#include "my_string.hpp"

void testDefaultConstructor() {
    MyString str1;
    assert(str1.length() == 0);
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
    std::cout << "constructor from specified string passed!\n";
}

void testCopyConstructor() {
    MyString str1("hello world!");
    MyString str2(str1);
    assert(str1.length() == str2.length());
    assert(str1 == str1);
}

void testAddString() {
    MyString str("hello");
    assert(str + " world!" == "hello world!");
    assert((str + " world!").length() == 12);
    std::cout << "string addition test passed\n";
}

void testAddStringWithResize() {
    MyString str(10);
    str += "hello world! this text will resize str.data";
    assert(str.length() == 43);
    assert(str == "hello world! this text will resize str.data");
    std::cout << "test add triggers resize test passed\n";
}

void testEqString() {
    MyString str;
    assert(str.length() == 0);
    str = "hello world!";
    assert(str.length() == 12);
    assert(str == "hello world!");
    std::cout << "string eq test passed\n";
}

void testConcatination() {
    MyString str("hello");
    str += " world!";
    assert(str.length() == 12);
    assert(str == "hello world!");
    std::cout << "string concatination test passed\n";
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

void testEqMyString() {
    MyString str1("hello world!");
    MyString str2("hallo werlde");
    assert(str1 != str2);
    str1 = str2;
    assert(str1 == str2);
    std::cout << "MyString Eq test passed\n";
}

void testStartsWith() {
    MyString str("hello world!");
    assert(!str.start_with("hallo"));
    assert(str.start_with("hello"));
    std::cout << "starts with test passed\n";
}

void testContains() {
    MyString str("hello world!");
    assert(!str.contains("hallo"));
    assert(str.contains("hello"));
    assert(MyString("").contains(""));
    assert(!MyString("").contains("a"));
    assert(MyString("abababa").contains("ababa"));
    assert(MyString("abababa").contains("babab"));
    assert(MyString("wdYD^\\YmfX`B_mIhQovpLJdEc[XXT\\URX^iaFShNQDYsgAtWlD^ZL\\[YtUXiLfL^MWiQXIuvJTjaOfkk]Th[A[juPaMBwvNWVXQSdyhHaG\\NhGCFUrKrgpxYHRwpxJPkbOpancjbjdhspyXVZicgIK^`CD\\sxWM_lqT]qnO_Yn^GOqYVZWmcTkYKrsOlxne_PzvG[CDTveWI[N^pcAOHAbBcTWilVVXD]hAozPRr[KwCVF`_mL^UBKIxXnWL[ICuVR\\olH]wldUGcHRxqZYbFUqr_qltBWEMC`z[suMYDA[KxEfnNG^DFIzFHdnNWCQH\\Z_PkktdSCAPXCiROojagyE^vXVqShDPgnnEaKRSN^PzrqteCVuby`njwVsCBrPxhnLnYxzRpFqHLomYoEmbnlbBqzIKSnQqnz_CtnGSDsfa]hfNnkivXhJCgtXUgtdIrVPFSKD_apQC[nk_WTSM\\vrcZMNMslOzGloWRzdCQpFM]sMBeP]d").contains("gnnEaKRSN^PzrqteCVuby`njwVsCBrPxhnLnYxzRpFqHLomYoEmbnlbBqzIKSnQqnz_CtnGSDsfa]hfNnkivXhJCgtXUgtdIrVPFSKD_apQC[nk_WTSM\\vr"));
    assert(!MyString("wdYD^\\YmfX`B_mIhQovpLJdEc[XXT\\URX^iaFShNQDYsgAtWlD^ZL\\[YtUXiLfL^MWiQXIuvJTjaOfkk]Th[A[juPaMBwvNWVXQSdyhHaG\\NhGCFUrKrgpxYHRwpxJPkbOpancjbjdhspyXVZicgIK^`CD\\sxWM_lqT]qnO_Yn^GOqYVZWmcTkYKrsOlxne_PzvG[CDTveWI[N^pcAOHAbBcTWilVVXD]hAozPRr[KwCVF`_mL^UBKIxXnWL[ICuVR\\olH]wldUGcHRxqZYbFUqr_qltBWEMC`z[suMYDA[KxEfnNG^DFIzFHdnNWCQH\\Z_PkktdSCAPXCiROojagyE^vXVqShDPgnnEaKRSN^PzrqteCVuby`njwVsCBrPxhnLnYxzRpFqHLomYoEmbnlbBqzIKSnQqnz_CtnGSDsfa]hfNnkivXhJCgtXUgtdIrVPFSKD_apQC[nk_WTSM\\vrcZMNMslOzGloWRzdCQpFM]sMBeP]d").contains("MvFftnypaKrWN\\PpIpxkeuFoWvOF[fjRSYUVNqvm]^_cuGZdsdKu`FOQTs`nXYqMZso\\ei`sAZ`qE`PMtxkQUHDFXNkBFxZUibvj"));
    std::cout << "conatins test passed\n";
}

int main() {
    testDefaultConstructor();
    testConstructorWithCapacity();
    testConstructorWithInvalidCpacity();
    testConstructorFromString();
    testCopyConstructor();
    testAddString();
    testAddStringWithResize();
    testEqString();
    testConcatination();
    testAtIndex();
    testIndexOutOfBounds();
    testEqMyString();
    testStartsWith();
    testContains();
    std::cout << "all tests passed!\n";
    return 0;
}