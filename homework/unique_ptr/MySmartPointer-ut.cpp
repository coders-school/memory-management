#include "gtest/gtest.h"
#include "MySmartPointer.h"

//=========== Add() Method ===========

class DefaultConstructor : public ::testing::Test
{
public:
	MySmartPointer<int> cut;
};

TEST_F(DefaultConstructor, No_Initialization_Should_Return_0)
{
	EXPECT_EQ(0, *cut.Get());
}




class PointerConstructor : public ::testing::Test
{
public:
	PointerConstructor() : cut(new int(10)) {};
	MySmartPointer<int> cut;
};

TEST_F(PointerConstructor, Initialiazed_Should_Return_True)
{
	EXPECT_EQ(10, *cut.Get());
}




class CopyConstructor : public ::testing::Test
{};

TEST_F(CopyConstructor, Destinatnion_Object_Should_Have_Value_Of_Source_Object)
{
	MySmartPointer<int> other(new int(21));
	MySmartPointer<int> cut(other);

	EXPECT_EQ(21, *cut.Get());
}

TEST_F(CopyConstructor, Source_Object_Should_Have_Value_Of_Zero)
{
	MySmartPointer<int> other(new int(21));
	MySmartPointer<int> cut(other);

	EXPECT_EQ(0, *other.Get());
}




class MoveConstructor : public ::testing::Test
{
};

TEST_F(MoveConstructor, Destinatnion_Object_Should_Have_Value_Of_Source_Object)
{
	MySmartPointer<int> other(new int(21));
	MySmartPointer<int> cut(std::move(other));

	EXPECT_EQ(21, *cut.Get());
}

TEST_F(MoveConstructor, Source_Object_Should_Have_Value_Of_Zero)
{
	MySmartPointer<int> other(new int(21));
	MySmartPointer<int> cut(std::move(other));

	EXPECT_EQ(0, *other.Get());
}



class ReleaseMethod : public ::testing::Test
{
};

TEST_F(ReleaseMethod, After_Executing_Cut_Sould_Return_Zero)
{
	MySmartPointer<int> cut(new int(21));

	auto ptr = cut.Release();

	EXPECT_EQ(0, *cut.Get());
}

TEST_F(ReleaseMethod, After_Executing_Ptr_Should_Has_Value_Of_Cut)
{
	MySmartPointer<int> cut(new int(21));

	auto ptr = cut.Release();

	EXPECT_EQ(21, *ptr);
}



class GetMethod : public ::testing::Test
{
public:
	GetMethod() : cut(new int(21)) {}

	MySmartPointer<int> cut;
};

TEST_F(GetMethod, After_Executing_Cut_Sould_Still_Hold_Old_Value)
{
	auto ptr = cut.Get();

	EXPECT_EQ(21, *cut.Get());
}

TEST_F(GetMethod, After_Executing_ptr_Sould_Point_To_Value_Of_Cut)
{
	auto ptr = cut.Get();

	EXPECT_EQ(21, *ptr);
}




class ResetMethod : public GetMethod
{
public:
	int* ptr = nullptr;

	ResetMethod()
	{
		ptr = new int(35);
	}
	~ResetMethod()
	{
	}
};

TEST_F(ResetMethod, After_Executing_Cut_Sould_Have_New_Value)
{
	cut.Reset(ptr);

	EXPECT_EQ(35, *cut.Get());
}



class CopyOperatorEqual : public ::testing::Test
{
public:
	MySmartPointer<int> cut;
	MySmartPointer<int> source;

	CopyOperatorEqual() : source(new int(35))
	{}
};

TEST_F(CopyOperatorEqual, After_Executing_Cut_Sould_Have_Source_Value)
{
	cut = source;

	EXPECT_EQ(35, *cut.Get());
}

TEST_F(CopyOperatorEqual, After_Executing_Source_Sould_Own_nullptr)
{
	cut = source;

	EXPECT_EQ(0, *source.Get());
}



class MoveOperatorEqual : public ::testing::Test
{
public:
	MySmartPointer<int> cut;
	MySmartPointer<int> source;

	MoveOperatorEqual() : source(new int(35))
	{}
};

TEST_F(MoveOperatorEqual, After_Executing_Cut_Sould_Have_Source_Value)
{
	cut = std::move(source);

	EXPECT_EQ(35, *cut.Get());
}

TEST_F(MoveOperatorEqual, After_Executing_Source_Sould_Own_nullptr)
{
	cut = source;

	EXPECT_EQ(0, *source.Get());
}




class OperatorAsterisk : public ::testing::Test
{
public:
	MySmartPointer<int> cut;

	OperatorAsterisk() : cut(new int(35))
	{
	}
};

TEST_F(OperatorAsterisk, Pointer_Should_Has_Same_Value_As_Cut)
{
	int& p = *cut;

	EXPECT_EQ(p, *cut.Get());
}
