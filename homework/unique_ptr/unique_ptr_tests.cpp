#include "gtest/gtest.h"
#include "unique_ptr.hpp"

template class my::unique_ptr<int>;

class DefaultConstructor : public ::testing::Test {
public:
	my::unique_ptr<int> cut;
};

TEST_F(DefaultConstructor, No_Initialization_Should_Return_0)
{
	EXPECT_EQ(nullptr, cut.get());
}




class PointerConstructor : public ::testing::Test
{
public:
	PointerConstructor() : cut(new int(10)) {};
    my::unique_ptr<int> cut;
};

TEST_F(PointerConstructor, Initialiazed_Should_Return_True)
{
    EXPECT_EQ(10, *cut.get());
}




class CopyConstructor : public ::testing::Test
{};

TEST_F(CopyConstructor, Destinatnion_Object_Should_Have_Value_Of_Source_Object)
{
    my::unique_ptr<int> other(new int(21));
    my::unique_ptr<int> cut(other);

	EXPECT_EQ(21, *cut.get());
}

TEST_F(CopyConstructor, Source_Object_Should_Have_Value_Of_Zero)
{
    my::unique_ptr<int> other(new int(21));
    my::unique_ptr<int> cut(other);

	EXPECT_EQ(nullptr, other.get());
}




class MoveConstructor : public ::testing::Test
{
};

TEST_F(MoveConstructor, Destinatnion_Object_Should_Have_Value_Of_Source_Object)
{
    my::unique_ptr<int> other(new int(21));
    my::unique_ptr<int> cut(std::move(other));

	EXPECT_EQ(21, *cut.get());
}

TEST_F(MoveConstructor, Source_Object_Should_Have_Value_Of_Zero)
{
    my::unique_ptr<int> other(new int(21));
    my::unique_ptr<int> cut(std::move(other));

	EXPECT_EQ(nullptr, other.get());
}



class ReleaseMethod : public ::testing::Test
{
};

TEST_F(ReleaseMethod, After_Executing_Cut_Sould_Return_Zero)
{
    my::unique_ptr<int> cut(new int(21));

	auto ptr = cut.release();

	EXPECT_EQ(nullptr, cut.get());

	delete ptr;
}

TEST_F(ReleaseMethod, After_Executing_Ptr_Should_Has_Value_Of_Cut)
{
    my::unique_ptr<int> cut(new int(21));

	auto ptr = cut.release();

	EXPECT_EQ(21, *ptr);

	delete ptr;
}



class GetMethod : public ::testing::Test
{
public:
	GetMethod() : cut(new int(21)) {}

	my::unique_ptr<int> cut;
};

TEST_F(GetMethod, After_Executing_Cut_Sould_Still_Hold_Old_Value)
{
    cut.get();

	EXPECT_EQ(21, *cut.get());
}

TEST_F(GetMethod, After_Executing_ptr_Sould_Point_To_Value_Of_Cut)
{
    auto ptr = cut.get();

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
    cut.reset(ptr);

	EXPECT_EQ(35, *cut.get());
}



class CopyOperatorEqual : public ::testing::Test
{
public:
    my::unique_ptr<int> cut;
    my::unique_ptr<int> source;

	CopyOperatorEqual() : source(new int(35))
	{}
};

TEST_F(CopyOperatorEqual, After_Executing_Cut_Sould_Have_Source_Value)
{
	cut = source;

	EXPECT_EQ(35, *cut.get());
}

TEST_F(CopyOperatorEqual, After_Executing_Source_Sould_Own_nullptr)
{
	cut = source;

	EXPECT_EQ(nullptr, source.get());
}



class MoveOperatorEqual : public ::testing::Test
{
public:
    my::unique_ptr<int> cut;
    my::unique_ptr<int> source;

	MoveOperatorEqual() : source(new int(35))
	{}
};

TEST_F(MoveOperatorEqual, After_Executing_Cut_Sould_Have_Source_Value)
{
	cut = std::move(source);

	EXPECT_EQ(35, *cut.get());
}

TEST_F(MoveOperatorEqual, After_Executing_Source_Sould_Own_nullptr)
{
	cut = source;

	EXPECT_EQ(nullptr, source.get());
}




class OperatorAsterisk : public ::testing::Test
{
public:
    my::unique_ptr<int> cut;

	OperatorAsterisk() : cut(new int(35))
	{
	}
};

TEST_F(OperatorAsterisk, Pointer_Should_Has_Same_Value_As_Cut)
{
	int& p = *cut;

	EXPECT_EQ(p, *cut.get());
}
