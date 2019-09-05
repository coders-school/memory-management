#include <gtest/gtest.h>
#include <string>
#include "smartPtr.hpp"

struct A {
    A(int inputData) : member(inputData) 
    { }
    
    void foo() 
    {
        std::cout << "The glorious integer: " << member << '\n';
    }
        
    int bar()
    {
        member *= 2;
        return member;
    }
   
    friend bool operator==(const A &a1, const A &a2)
    {
        return a1.member == a2.member;
    }
    
    int member;
};

class SmartPointerTests : public ::testing::Test {
public:
    SmartPointerTests() :
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
    
    ~SmartPointerTests()
    {
    }
    
    void SetUp()
    {
        rPtrBool1 = nullptr;
        rPtrChar1 = nullptr;
        rPtrInt1 = nullptr;
        rPtrFloat1 = nullptr;
        rPtrDouble1 = nullptr;
        rPtrString1 = nullptr;
        rPtrA1 = nullptr;
    }

    void TearDown()
    {
        delete rPtrBool1;
        delete rPtrChar1;
        delete rPtrInt1;
        delete rPtrFloat1;
        delete rPtrDouble1;
        delete rPtrString1;
        delete rPtrA1;
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
    
    SmartPointer<bool> sPtrBool1;
    SmartPointer<char> sPtrChar1;
    SmartPointer<int> sPtrInt1;
    SmartPointer<float> sPtrFloat1;
    SmartPointer<double> sPtrDouble1;
    SmartPointer<std::string> sPtrString1;
    SmartPointer<A> sPtrA1;
    
    SmartPointer<bool> sPtrBool2;
    SmartPointer<char> sPtrChar2;
    SmartPointer<int> sPtrInt2;
    SmartPointer<float> sPtrFloat2;
    SmartPointer<double> sPtrDouble2;
    SmartPointer<std::string> sPtrString2;
    SmartPointer<A> sPtrA2;     

    bool* rPtrBool1 = nullptr;
    char* rPtrChar1 = nullptr;
    int* rPtrInt1 = nullptr;
    float* rPtrFloat1 = nullptr;
    double* rPtrDouble1 = nullptr;
    std::string* rPtrString1 = nullptr;
    A* rPtrA1 = nullptr;
};

TEST_F(SmartPointerTests, canProperlyConstructAndDereferenceSmartPtr)
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

TEST_F(SmartPointerTests, canConstructSmartPtrWithMoveConstructor)
{
    // ARRANGE (done in initialization list) 
    // ACT
    SmartPointer<bool> sPtrBool3(std::move(sPtrBool2));
    SmartPointer<char> sPtrChar3(std::move(sPtrChar2));
    SmartPointer<int> sPtrInt3(std::move(sPtrInt2));
    SmartPointer<float> sPtrFloat3(std::move(sPtrFloat2));
    SmartPointer<double> sPtrDouble3(std::move(sPtrDouble2));
    SmartPointer<std::string> sPtrString3(std::move(sPtrString2));
    SmartPointer<A> sPtrA3(std::move(sPtrA2));

    // ASSERT
    ASSERT_TRUE(*sPtrBool3 == bool2);
    ASSERT_TRUE(*sPtrChar3 == char2);
    ASSERT_TRUE(*sPtrInt3 == int2);
    ASSERT_TRUE(*sPtrFloat3 == flt2);
    ASSERT_TRUE(*sPtrDouble3 == dbl2);
    ASSERT_TRUE(*sPtrString3 == str2);
    ASSERT_TRUE(*sPtrA3 == A(AInt2));
}

TEST_F(SmartPointerTests, canChangeSmartPtrValueWithDereferenceOperator)
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

TEST_F(SmartPointerTests, canUseArrowOperatorOnUnderlyingClassInstance)
{
    // ARRANGE
    const int input1 = 31;
    const int input2 = 37;
    int output1, output2;
    SmartPointer<A> APointer1 (new A(input1));
    SmartPointer<A> APointer2 (new A(input2));

    // ACT
    output1 = APointer1->bar();
    output2 = APointer2->bar();

    // ASSERT:
    ASSERT_TRUE(2*input1==output1);
    ASSERT_TRUE(2*input2==output2);
}

TEST_F(SmartPointerTests, checkIfGetMethodReturnsUnderlyingPointer)
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

TEST_F(SmartPointerTests, boolOperatorTest)
{
    // ARRANGE (partially done in initialization list)
    SmartPointer<bool> sPtrBool3(std::move(sPtrBool1));
    SmartPointer<char> sPtrChar3(std::move(sPtrChar1));
    SmartPointer<int> sPtrInt3(std::move(sPtrInt1));
    SmartPointer<float> sPtrFloat3(std::move(sPtrFloat1));
    SmartPointer<double> sPtrDouble3(std::move(sPtrDouble1));
    SmartPointer<std::string> sPtrString3(std::move(sPtrString1));
    SmartPointer<A> sPtrA3(std::move(sPtrA1));
    
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

TEST_F(SmartPointerTests, checkIfReleaseMethodSetUnderlyingPointerNullptr)
{ 
    // ARRANGE (done in initialization list nad SetUp() )
    // ACT
    rPtrBool1 = sPtrBool1.release();
    rPtrChar1 = sPtrChar1.release();
    rPtrInt1 = sPtrInt1.release();
    rPtrFloat1 = sPtrFloat1.release();
    rPtrDouble1 = sPtrDouble1.release();
    rPtrString1 = sPtrString1.release();
    rPtrA1 = sPtrA1.release();
    
    // ASSERT
    ASSERT_FALSE(sPtrBool1);
    ASSERT_FALSE(sPtrChar1);
    ASSERT_FALSE(sPtrInt1);
    ASSERT_FALSE(sPtrFloat1);
    ASSERT_FALSE(sPtrDouble1);
    ASSERT_FALSE(sPtrString1);
    ASSERT_FALSE(sPtrA1);
}

TEST_F(SmartPointerTests, checkIfReleaseMethodReturnsManagedObject)
{ 
    // ARRANGE (done in initialization list nad SetUp() )
    // ACT
    rPtrBool1 = sPtrBool1.release();
    rPtrChar1 = sPtrChar1.release();
    rPtrInt1 = sPtrInt1.release();
    rPtrFloat1 = sPtrFloat1.release();
    rPtrDouble1 = sPtrDouble1.release();
    rPtrString1 = sPtrString1.release();
    rPtrA1 = sPtrA1.release();
    
    // ASSERT
    ASSERT_EQ(*rPtrBool1, bool1);
    ASSERT_EQ(*rPtrChar1, char1);
    ASSERT_EQ(*rPtrInt1, int1);
    ASSERT_EQ(*rPtrFloat1, flt1);
    ASSERT_EQ(*rPtrDouble1, dbl1);
    ASSERT_EQ(*rPtrString1, str1);
    ASSERT_EQ(*rPtrA1, A1);
}

TEST_F(SmartPointerTests, checkIfResetReplacesManagedObject)
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

TEST_F(SmartPointerTests, IsMoveConstructorSettingNullptrOnInput)
{
    // ARRANGE (done in initialization list) 
    // ACT
    SmartPointer<bool> sPtrBool3(std::move(sPtrBool1));
    SmartPointer<char> sPtrChar3(std::move(sPtrChar1));
    SmartPointer<int> sPtrInt3(std::move(sPtrInt1));
    SmartPointer<float> sPtrFloat3(std::move(sPtrFloat1));
    SmartPointer<double> sPtrDouble3(std::move(sPtrDouble1));
    SmartPointer<std::string> sPtrString3(std::move(sPtrString1));
    SmartPointer<A> sPtrA3(std::move(sPtrA1));

    // ASSERT
    ASSERT_FALSE(sPtrBool1);
    ASSERT_FALSE(sPtrChar1);
    ASSERT_FALSE(sPtrInt1);
    ASSERT_FALSE(sPtrFloat1);
    ASSERT_FALSE(sPtrDouble1);
    ASSERT_FALSE(sPtrString1);
    ASSERT_FALSE(sPtrA1);
}