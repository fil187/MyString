#include <gtest/gtest.h>
#include "my_string.hpp"

TEST(MyStringTest, DefaultConstructor) {
    MyString str;
    EXPECT_EQ(0, str.length());
    EXPECT_EQ("", str);
}

TEST(MyStringTest, ConstructorWithCapacity) {
    MyString str(10);
    EXPECT_EQ(0, str.length());
    EXPECT_EQ("", str);
}

TEST(MyStringTest, ConstructorWithInvalidCpacity) {
    EXPECT_THROW(MyString(0), std::invalid_argument);
}

TEST(MyStringTest, ConstructorFromString) {
    MyString str("hello world!");
    EXPECT_EQ(12, str.length());
    EXPECT_EQ("hello world!", str);
}

TEST(MyStringTest, ConstructorEmptyString) {
    MyString str("");
    EXPECT_EQ(0, str.length());
    EXPECT_EQ("", str);
}

TEST(MyStringTest, CopyConstructor) {
    MyString str1("hello world!");
    MyString str2(str1);
    EXPECT_EQ("hello world!", str2);
    EXPECT_EQ(str1.length(), str2.length());
    EXPECT_EQ(str1, str2);
}

TEST(MyStringTest, CopyConstructorIndependent) {
    MyString str1("hello world!");
    MyString str2(str1);
    EXPECT_EQ(str1, str2);
    str1 = "hallo werld!";
    EXPECT_NE(str1, str2);
}

TEST(MyStringTest, AddString) {
    MyString str("hello");
    EXPECT_EQ("hello world!", str + " world!");
    EXPECT_EQ("hello", str);
    EXPECT_EQ(12, (str + " world!").length());
}

TEST(MyStringTest, AddStringWithSingleResize) {
    MyString str(10);
    str += "hello world! this text will resize str.data";
    EXPECT_EQ(43, str.length());
    EXPECT_EQ("hello world! this text will resize str.data", str);
}

TEST(MyStringTest, AddStringWithMultipleResizes) {
    MyString str(2);
    str += "hello"; // size and capacity are 5 here
    EXPECT_EQ("hello", str);
    EXPECT_EQ(5, str.length());
    str += " world!"; // size and capacity are 12 here
    EXPECT_EQ("hello world!", str);
    EXPECT_EQ(12, str.length());
    str += " this text will resize str.data"; // size and capacity are 43 here
    EXPECT_EQ("hello world! this text will resize str.data", str);
    EXPECT_EQ(43, str.length());
}

TEST(MyStringTest, StringAssignment) {
    MyString str;
    EXPECT_EQ(0, str.length());
    str = "hello world!";
    EXPECT_EQ(12, str.length());
    EXPECT_EQ("hello world!", str);
}

TEST(MyStringTest, AssignmentFromEmptyString) {
    MyString str("hello world!");
    str = "";
    EXPECT_EQ(0, str.length());
    EXPECT_EQ("", str);
}

TEST(MyStringTest, MyStringAssignment) {
    MyString str1("hello world!");
    MyString str2("hallo werlde");
    EXPECT_NE(str1, str2);
    str1 = str2;
    EXPECT_EQ(str1, str2);
}

TEST(MyStringTest, AssignmentIndependence) {
    MyString str1("hello world!");
    MyString str2;
    str2 = str1;
    EXPECT_EQ(str1, str2);
    str1 = "hallo werlde!";
    EXPECT_NE(str1, str2);
}

TEST(MyStringTest, SelfAssignment) {
    MyString str1("hello world!");
    str1 = str1;
    EXPECT_EQ("hello world!", str1);
}

TEST(MyStringTest, Concatination) {
    MyString str("hello");
    str += " world!";
    EXPECT_EQ(12, str.length());
    EXPECT_EQ("hello world!", str);
}

TEST(MyStringTest, ConcatintionWithEmptyString) {
    EXPECT_EQ("hello", MyString("hello") + "");
}

TEST(MyStringTest, ConcatinationFromEmptyString) {
    EXPECT_EQ("", MyString("") + "");
}

TEST(MyStringTest, AtIndex) {
    std::string text = "hello world!";
    MyString str(text);
    EXPECT_EQ(text, str);
    for (size_t i = 0; i < str.length(); i++)
        EXPECT_EQ(text.at(i), str[i]);
}

TEST(MyStringTest, IndexOutOfBounds) {
    EXPECT_THROW(MyString("hello world!")[1000], std::out_of_range);
}

TEST(MyStringTest, IndexJustOutOfBounds) {
    EXPECT_THROW(MyString("hello world!")[12], std::out_of_range);
}

TEST(MyStringTest, StartsWith) {
    EXPECT_FALSE(MyString("hello world!").start_with("hallo"));
    EXPECT_TRUE(MyString("hello world!").start_with("hello"));
}

TEST(MyStringTest, BasicContains) {
    EXPECT_FALSE(MyString("hello world!").contains("hallo"));
    EXPECT_TRUE(MyString("hello world!").contains("hello"));
    EXPECT_TRUE
    (MyString("abababa").contains("ababa"));
    EXPECT_TRUE
    (MyString("abababa").contains("babab"));
}

TEST(MyStringTest, EmptyStringContains) {
    EXPECT_TRUE(MyString("").contains(""));
    EXPECT_FALSE(MyString("").contains("a"));
}

TEST(MyStringTest, ContainsLongerString) {
    EXPECT_FALSE(MyString("hello").contains("hello world"));
}

TEST(MyStringTest, ContainsExactMatch) {
    EXPECT_TRUE(MyString("hello").contains("hello"));
}

TEST(MyStringTest, ComplexStringContains) {
    EXPECT_TRUE(MyString("wdYD^\\YmfX`B_mIhQovpLJdEc[XXT\\URX^iaFShNQDYsgAtWlD^ZL\\[YtUXiLfL^MWiQXIuvJTjaOfkk]Th[A[juPaMBwvNWVXQSdyhHaG\\NhGCFUrKrgpxYHRwpxJPkbOpancjbjdhspyXVZicgIK^`CD\\sxWM_lqT]qnO_Yn^GOqYVZWmcTkYKrsOlxne_PzvG[CDTveWI[N^pcAOHAbBcTWilVVXD]hAozPRr[KwCVF`_mL^UBKIxXnWL[ICuVR\\olH]wldUGcHRxqZYbFUqr_qltBWEMC`z[suMYDA[KxEfnNG^DFIzFHdnNWCQH\\Z_PkktdSCAPXCiROojagyE^vXVqShDPgnnEaKRSN^PzrqteCVuby`njwVsCBrPxhnLnYxzRpFqHLomYoEmbnlbBqzIKSnQqnz_CtnGSDsfa]hfNnkivXhJCgtXUgtdIrVPFSKD_apQC[nk_WTSM\\vrcZMNMslOzGloWRzdCQpFM]sMBeP]d").contains("gnnEaKRSN^PzrqteCVuby`njwVsCBrPxhnLnYxzRpFqHLomYoEmbnlbBqzIKSnQqnz_CtnGSDsfa]hfNnkivXhJCgtXUgtdIrVPFSKD_apQC[nk_WTSM\\vr"));
    EXPECT_FALSE(MyString("wdYD^\\YmfX`B_mIhQovpLJdEc[XXT\\URX^iaFShNQDYsgAtWlD^ZL\\[YtUXiLfL^MWiQXIuvJTjaOfkk]Th[A[juPaMBwvNWVXQSdyhHaG\\NhGCFUrKrgpxYHRwpxJPkbOpancjbjdhspyXVZicgIK^`CD\\sxWM_lqT]qnO_Yn^GOqYVZWmcTkYKrsOlxne_PzvG[CDTveWI[N^pcAOHAbBcTWilVVXD]hAozPRr[KwCVF`_mL^UBKIxXnWL[ICuVR\\olH]wldUGcHRxqZYbFUqr_qltBWEMC`z[suMYDA[KxEfnNG^DFIzFHdnNWCQH\\Z_PkktdSCAPXCiROojagyE^vXVqShDPgnnEaKRSN^PzrqteCVuby`njwVsCBrPxhnLnYxzRpFqHLomYoEmbnlbBqzIKSnQqnz_CtnGSDsfa]hfNnkivXhJCgtXUgtdIrVPFSKD_apQC[nk_WTSM\\vrcZMNMslOzGloWRzdCQpFM]sMBeP]d").contains("MvFftnypaKrWN\\PpIpxkeuFoWvOF[fjRSYUVNqvm]^_cuGZdsdKu`FOQTs`nXYqMZso\\ei`sAZ`qE`PMtxkQUHDFXNkBFxZUibvj"));
}