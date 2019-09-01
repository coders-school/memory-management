#include <gtest/gtest.h>
#include <string>
#include "smartPtr.hpp"
#include "A.hpp"

class smartPointerTests : public ::testing::Test {
public:
    smartPointerTests() :
        bool1(true),
        char1('a'), 
        int1(11), 
        flt1(1.41421356237), 
        dbl1(3.14159265359), 
        str1("Lorem ipsum dolor sit amet"), 
        AInt1(17),
        A1(17),
        
        bool2(false), 
        char2('b'), 
        int2(13), 
        flt2(1.73205080757),
        dbl2(2.718281828459), 
        str2("Consectetur adipiscing elit"),
        AInt2(29),
        A2(29),
        
        sPtrBool1(new bool(true)),
        sPtrChar1(new char('a')),
        sPtrInt1(new int(11)),
        sPtrFloat1(new float(1.41421356237)),
        sPtrDouble1(new double(3.14159265359)),
        sPtrString1(new std::string("Lorem ipsum dolor sit amet")),
        sPtrA1(new A(17)),
        
        sPtrBool2(new bool(false)),
        sPtrChar2(new char('b')),
        sPtrInt2(new int(13)),
        sPtrFloat2(new float(1.73205080757)),
        sPtrDouble2(new double(2.718281828459)),
        sPtrString2(new std::string("Consectetur adipiscing elit")),
        sPtrA2(new A(29)) 
    {
    }
    
    ~smartPointerTests()
    {
    }
   
    bool bool1;
    char char1;
    int int1;
    float flt1;
    double dbl1;
    std::string str1;
    int AInt1;
    A A1;
    
    bool bool2;
    char char2;
    int int2;
    float flt2;
    double dbl2;
    std::string str2;
    int AInt2;
    A A2;
    
    smartPointer<bool> sPtrBool1;
    smartPointer<char> sPtrChar1;
    smartPointer<int> sPtrInt1;
    smartPointer<float> sPtrFloat1;
    smartPointer<double> sPtrDouble1;
    smartPointer<std::string> sPtrString1;
    smartPointer<A> sPtrA1;
    
    smartPointer<bool> sPtrBool2;
    smartPointer<char> sPtrChar2;
    smartPointer<int> sPtrInt2;
    smartPointer<float> sPtrFloat2;
    smartPointer<double> sPtrDouble2;
    smartPointer<std::string> sPtrString2;
    smartPointer<A> sPtrA2;      
};

TEST_F(smartPointerTests, canProperlyConstructAndDereferenceSmartPtr)
{
    // ARRANGE (done in initialization list) 
    // ACT (done in initialization list) 
    // ASSERT
    ASSERT_TRUE(*sPtrBool1 == bool1);
    ASSERT_TRUE(*sPtrChar1 == char1);
    ASSERT_TRUE(*sPtrInt1 == int1);
    ASSERT_TRUE(*sPtrFloat1 == flt1);
    ASSERT_TRUE(*sPtrDouble1 == dbl1);
    ASSERT_TRUE(*sPtrString1 == str1);
    ASSERT_TRUE(*sPtrA1 == A(AInt1));
}

TEST_F(smartPointerTests, canConstructSmartPtrWithMoveConstructor)
{
    // ARRANGE (done in initialization list) 
    // ACT
    smartPointer<bool> sPtrBool3(std::move(sPtrBool2));
    smartPointer<char> sPtrChar3(std::move(sPtrChar2));
    smartPointer<int> sPtrInt3(std::move(sPtrInt2));
    smartPointer<float> sPtrFloat3(std::move(sPtrFloat2));
    smartPointer<double> sPtrDouble3(std::move(sPtrDouble2));
    smartPointer<std::string> sPtrString3(std::move(sPtrString2));
    smartPointer<A> sPtrA3(std::move(sPtrA2));

    // ASSERT
    ASSERT_TRUE(*sPtrBool3 == bool2);
    ASSERT_TRUE(*sPtrChar3 == char2);
    ASSERT_TRUE(*sPtrInt3 == int2);
    ASSERT_TRUE(*sPtrFloat3 == flt2);
    ASSERT_TRUE(*sPtrDouble3 == dbl2);
    ASSERT_TRUE(*sPtrString3 == str2);
    ASSERT_TRUE(*sPtrA3 == A(AInt2));
}

TEST_F(smartPointerTests, canChangeSmartPtrValueWithDereferenceOperator)
{
    // ARRANGE (done in initialization list)
    // ACT
    *sPtrBool1 = bool2;
    *sPtrChar1 = char2;
    *sPtrInt1 = int2;
    *sPtrFloat1 = flt2;
    *sPtrDouble1 = dbl2;
    *sPtrString1 = str2;
    *sPtrA1 = A2;

    // ASSERT:
    ASSERT_TRUE(*sPtrBool1==bool2);
    ASSERT_TRUE(*sPtrChar1==char2);
    ASSERT_TRUE(*sPtrInt1==int2);
    ASSERT_TRUE(*sPtrFloat1==flt2);
    ASSERT_TRUE(*sPtrDouble1==dbl2);
    ASSERT_TRUE(*sPtrString1==str2);
    ASSERT_TRUE(*sPtrA1==A2);
}

TEST_F(smartPointerTests, canUseArrowOperatorOnUnderlyingClassInstance)
{
    // ARRANGE
    const int input1 = 31;
    const int input2 = 37;
    int output1, output2;
    smartPointer<A> APointer1 (new A(input1));
    smartPointer<A> APointer2 (new A(input2));

    // ACT
    output1 = APointer1->bar();
    output2 = APointer2->bar();

    // ASSERT:
    ASSERT_TRUE(2*input1==output1);
    ASSERT_TRUE(2*input2==output2);
}

TEST_F(smartPointerTests, checkIfGetMethodReturnsUnderlyingPointer)
{
    // ARRANGE (partially done in initialization list)
    bool* rPtrBool1 = nullptr;
    char* rPtrChar1 = nullptr;
    int* rPtrInt1 = nullptr;
    float* rPtrFloat1 = nullptr;
    double* rPtrDouble1 = nullptr;
    std::string* rPtrString1 = nullptr;
    A* rPtrA1 = nullptr;

    // ACT
    rPtrBool1 = sPtrBool1.get();
    rPtrChar1 = sPtrChar1.get();
    rPtrInt1 = sPtrInt1.get();
    rPtrFloat1 = sPtrFloat1.get();
    rPtrDouble1 = sPtrDouble1.get();
    rPtrString1 = sPtrString1.get();
    rPtrA1 = sPtrA1.get();

    // ASSERT
    ASSERT_TRUE(rPtrBool1==sPtrBool1.get());
    ASSERT_TRUE(rPtrChar1==sPtrChar1.get());
    ASSERT_TRUE(rPtrInt1==sPtrInt1.get());
    ASSERT_TRUE(rPtrFloat1==sPtrFloat1.get());
    ASSERT_TRUE(rPtrDouble1==sPtrDouble1.get());
    ASSERT_TRUE(rPtrString1==sPtrString1.get());
    ASSERT_TRUE(rPtrA1==sPtrA1.get());  
}

TEST_F(smartPointerTests, boolOperatorTest)
{
    // ARRANGE (partially done in initialization list)
    smartPointer<bool> sPtrBool3(std::move(sPtrBool1));
    smartPointer<char> sPtrChar3(std::move(sPtrChar1));
    smartPointer<int> sPtrInt3(std::move(sPtrInt1));
    smartPointer<float> sPtrFloat3(std::move(sPtrFloat1));
    smartPointer<double> sPtrDouble3(std::move(sPtrDouble1));
    smartPointer<std::string> sPtrString3(std::move(sPtrString1));
    smartPointer<A> sPtrA3(std::move(sPtrA1));
    
    // ACT
    bool bBool1 = sPtrBool1;
    bool bChar1 = sPtrChar1;
    bool bInt1 = sPtrInt1;
    bool bFloat1 = sPtrFloat1;
    bool bDouble1 = sPtrDouble1;
    bool bString1 = sPtrString1;
    bool bA1 = sPtrA1;
    bool bBool3 = sPtrBool3;
    bool bChar3 = sPtrChar3;
    bool bInt3 = sPtrInt3;
    bool bFloat3 = sPtrFloat3;
    bool bDouble3 = sPtrDouble3;
    bool bString3 = sPtrString3;
    bool bA3 = sPtrA3;

    // ASSERT
    ASSERT_TRUE(bBool3);
    ASSERT_TRUE(bChar3);
    ASSERT_TRUE(bInt3);
    ASSERT_TRUE(bFloat3);
    ASSERT_TRUE(bDouble3);
    ASSERT_TRUE(bString3);
    ASSERT_TRUE(bA3);
    ASSERT_FALSE(bBool1);
    ASSERT_FALSE(bChar1);
    ASSERT_FALSE(bInt1);
    ASSERT_FALSE(bFloat1);
    ASSERT_FALSE(bDouble1);
    ASSERT_FALSE(bString1);
    ASSERT_FALSE(bA1);        
}

TEST_F(smartPointerTests, checkIfReleaseSetsUnderlyingPointerNullptr)
{ 
    // ARRANGE (done in initialization list)
    // ACT
    sPtrBool1.release();
    sPtrChar1.release();
    sPtrInt1.release();
    sPtrFloat1.release();
    sPtrDouble1.release();
    sPtrString1.release();
    sPtrA1.release();
    
    // ASSERT
    ASSERT_FALSE(sPtrBool1);
    ASSERT_FALSE(sPtrChar1);
    ASSERT_FALSE(sPtrInt1);
    ASSERT_FALSE(sPtrFloat1);
    ASSERT_FALSE(sPtrDouble1);
    ASSERT_FALSE(sPtrString1);
    ASSERT_FALSE(sPtrA1);
}

TEST_F(smartPointerTests, checkIfResetReplacesManagedObject)
{
    // ARRANGE (done in initialization list)
    // ACT
    sPtrBool1.reset(new bool(bool2));
    sPtrChar1.reset(new char(char2));
    sPtrInt1.reset(new int(int2));
    sPtrFloat1.reset(new float(flt2));
    sPtrDouble1.reset(new double(dbl2));
    sPtrString1.reset(new std::string(str2));
    sPtrA1.reset(new A(AInt2));

    // ASSERT
    ASSERT_TRUE(*sPtrBool1==bool2);
    ASSERT_TRUE(*sPtrChar1==char2);
    ASSERT_TRUE(*sPtrInt1==int2);
    ASSERT_TRUE(*sPtrFloat1==flt2);
    ASSERT_TRUE(*sPtrDouble1==dbl2);
    ASSERT_TRUE(*sPtrString1==str2);
    ASSERT_TRUE(*sPtrA1==AInt2);
}
