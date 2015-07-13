#ifndef _TEST_CHECK_H_
#define _TEST_CHECK_H_

#include <stdio.h>
#include <string.h>

class TestCheck
{
public:

	void Subject(const char* title)
	{
		printf("Check Subject: %s\n", title);
	}

	template<typename T>
	void Equals(T val1, T val2, const char* msg)
	{
		PrintResult(val1 == val2, msg);
	}

	void StringEquals(const char* str1, const char* str2, const char* msg)
	{
		PrintResult(strcmp(str1, str2) == 0, msg);
	}

	template<typename T>
	void Negative(T val, const char* msg)
	{
		PrintResult(val < 0, msg);
	}

	template<typename T>
	void NotNegative(T val, const char* msg)
	{
		PrintResult(val >= 0, msg);
	}

	template<typename T>
	void Positive(T val, const char* msg)
	{
		PrintResult(val > 0, msg);
	}

	template<typename T>
	void NotPositive(T val, const char* msg)
	{
		PrintResult(val <= 0, msg);
	}

	void True(bool val, const char* msg)
	{
		PrintResult(val, msg);
	}

	void False(bool val, const char* msg)
	{
		PrintResult(!val, msg);
	}

	template<typename T>
	void Zero(T val, const char* msg)
	{
		PrintResult(val == 0, msg);
	}

	void Null(void* val, const char* msg)
	{
		PrintResult(val == NULL, msg);
	}

	void NotNull(void* val, const char* msg)
	{
		PrintResult(val != NULL, msg);
	}

	template<typename T>
	void Bigger(T big, T small, const char* msg)
	{
		PrintResult(big > small, msg);
	}

	template<typename T>
	void BiggerOrEqual(T big, T small, const char* msg)
	{
		PrintResult(big >= small, msg);
	}

	void Pass(const char* msg)
	{
		printf("Check: %s - PASS\n", msg);
	}

	void Fail(const char* msg)
	{
		printf("Check: %s - FAIL\n", msg);
	}

	void PrintResult(bool pass, const char* msg)
	{
		if (pass)
			Pass(msg);
		else
			Fail(msg);
	}
};

static TestCheck Check;

#endif
