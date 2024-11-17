#include "pch.h"
#include <filesystem>
#include <iostream>
#include "CppUnitTest.h"
#include "ReflectionManager.h"
#include "Test_structs.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(Test_simple)
		{
			auto curPath = std::filesystem::current_path();
			curPath = curPath.parent_path().parent_path().append("TestFiles");
			ReflectionManager::instance().load(curPath.string(), "profile");
			Test_Simple testSimple;
			Assert::IsTrue(testSimple.booleanValue, L"Wrong boolean value");
			Assert::AreEqual(-8, testSimple.integerValue, L"Wrong integer value");
			Assert::AreEqual(static_cast<unsigned int>(5), testSimple.unsignedValue, L"Wrong unsigned integer value");
			Assert::AreEqual(60.98f, testSimple.floatValue, L"Wrong float value");
			Assert::AreEqual(1.2, testSimple.doubleValue, L"Wrong double value");
			Assert::AreEqual(std::string("Hello world"), testSimple.stringValue, L"Wrong string value");
			ReflectionManager::instance().clear();
		}

		TEST_METHOD(Test_vectors)
		{
			auto curPath = std::filesystem::current_path();
			curPath = curPath.parent_path().parent_path().append("TestFiles");
			ReflectionManager::instance().load(curPath.string(), "profileVector");
			Test_Vector testVector;
			Assert::AreEqual(4, static_cast<int>(testVector.vintegerValue.size()), L"Wrong vector integer size");
			Assert::AreEqual(-8, testVector.vintegerValue[0], L"Wrong integer value");
			Assert::AreEqual(-5, testVector.vintegerValue[1], L"Wrong integer value");
			Assert::AreEqual(3, testVector.vintegerValue[2], L"Wrong integer value");
			Assert::AreEqual(2, testVector.vintegerValue[3], L"Wrong integer value");

			Assert::AreEqual(6, static_cast<int>(testVector.vunsignedValue.size()), L"Wrong vector unsigned size");
			Assert::AreEqual(static_cast<unsigned int>(5), testVector.vunsignedValue[0], L"Wrong unsigned value");
			Assert::AreEqual(static_cast<unsigned int>(6), testVector.vunsignedValue[1], L"Wrong unsigned value");
			Assert::AreEqual(static_cast<unsigned int>(7), testVector.vunsignedValue[2], L"Wrong unsigned value");
			Assert::AreEqual(static_cast<unsigned int>(8), testVector.vunsignedValue[3], L"Wrong unsigned value");
			Assert::AreEqual(static_cast<unsigned int>(9), testVector.vunsignedValue[4], L"Wrong unsigned value");
			Assert::AreEqual(static_cast<unsigned int>(10), testVector.vunsignedValue[5], L"Wrong unsigned value");

			Assert::AreEqual(2, static_cast<int>(testVector.vfloatValue.size()), L"Wrong vector float size");
			Assert::AreEqual(60.98f, testVector.vfloatValue[0], L"Wrong float value");
			Assert::AreEqual(10.2f, testVector.vfloatValue[1], L"Wrong float value");

			Assert::AreEqual(3, static_cast<int>(testVector.vdoubleValue.size()), L"Wrong vector double size");
			Assert::AreEqual(1.2, testVector.vdoubleValue[0], L"Wrong double value");
			Assert::AreEqual(3.5, testVector.vdoubleValue[1], L"Wrong double value");
			Assert::AreEqual(8.6, testVector.vdoubleValue[2], L"Wrong double value");
			Assert::AreEqual(2, static_cast<int>(testVector.vstringValue.size()), L"Wrong vector string size");
			Assert::AreEqual(std::string("Hello world"), testVector.vstringValue[0], L"Wrong string value");
			Assert::AreEqual(std::string("Good bye"), testVector.vstringValue[1], L"Wrong string value");

			ReflectionManager::instance().clear();
		}

		TEST_METHOD(Test_nested0)
		{
			auto curPath = std::filesystem::current_path();
			curPath = curPath.parent_path().parent_path().append("TestFiles");
			ReflectionManager::instance().load(curPath.string(), "profileNested0");
			Test_Nested testNested;
			Assert::IsTrue(testNested.bValue, L"Wrong boolean value");
			Assert::IsTrue(testNested.nested.booleanValue, L"Wrong boolean value");
			Assert::AreEqual(-8, testNested.nested.integerValue, L"Wrong integer value");
			Assert::AreEqual(static_cast<unsigned int>(5), testNested.nested.unsignedValue, L"Wrong unsigned integer value");
			Assert::AreEqual(60.98f, testNested.nested.floatValue, L"Wrong float value");
			Assert::AreEqual(1.2, testNested.nested.doubleValue, L"Wrong double value");
			Assert::AreEqual(std::string("Hello world"), testNested.nested.stringValue, L"Wrong string value");
			ReflectionManager::instance().clear();
		}

		TEST_METHOD(Test_nested1)
		{
			auto curPath = std::filesystem::current_path();
			curPath = curPath.parent_path().parent_path().append("TestFiles");
			ReflectionManager::instance().load(curPath.string(), "profileNested1");
			Test_Nested testNested;
			Assert::IsTrue(testNested.bValue, L"Wrong boolean value");
			Assert::IsFalse(testNested.nested.booleanValue, L"Wrong boolean value");
			Assert::AreEqual(-4, testNested.nested.integerValue, L"Wrong integer value");
			Assert::AreEqual(static_cast<unsigned int>(9), testNested.nested.unsignedValue, L"Wrong unsigned integer value");
			Assert::AreEqual(6.98f, testNested.nested.floatValue, L"Wrong float value");
			Assert::AreEqual(15.2, testNested.nested.doubleValue, L"Wrong double value");
			Assert::AreEqual(std::string("Hello"), testNested.nested.stringValue, L"Wrong string value");
			ReflectionManager::instance().clear();
		}

		TEST_METHOD(Test_nested2)
		{
			auto curPath = std::filesystem::current_path();
			curPath = curPath.parent_path().parent_path().append("TestFiles");
			ReflectionManager::instance().load(curPath.string(), "profileNested2");
			Test_Nested testNested;
			Assert::IsTrue(testNested.bValue, L"Wrong boolean value");
			Assert::IsTrue(testNested.nested.booleanValue, L"Wrong boolean value");
			Assert::AreEqual(-1, testNested.nested.integerValue, L"Wrong integer value");
			Assert::AreEqual(static_cast<unsigned int>(3), testNested.nested.unsignedValue, L"Wrong unsigned integer value");
			Assert::AreEqual(3.2f, testNested.nested.floatValue, L"Wrong float value");
			Assert::AreEqual(1.6, testNested.nested.doubleValue, L"Wrong double value");
			Assert::AreEqual(std::string("GoodBye"), testNested.nested.stringValue, L"Wrong string value");
			ReflectionManager::instance().clear();
		}


		TEST_METHOD(Test_legacy)
		{
			auto curPath = std::filesystem::current_path();
			curPath = curPath.parent_path().parent_path().append("TestFiles");
			ReflectionManager::instance().load(curPath.string(), "profileLegacy");
			Test_Simple testSimple;
			Assert::IsTrue(testSimple.booleanValue, L"Wrong boolean value");
			Assert::AreEqual(-8, testSimple.integerValue, L"Wrong integer value");
			Assert::AreEqual(static_cast<unsigned int>(5), testSimple.unsignedValue, L"Wrong unsigned integer value");
			Assert::AreEqual(6.98f, testSimple.floatValue, L"Wrong float value");
			Assert::AreEqual(15.2, testSimple.doubleValue, L"Wrong double value");
			Assert::AreEqual(std::string("Hello"), testSimple.stringValue, L"Wrong string value");
			ReflectionManager::instance().clear();
		}


		TEST_METHOD(Test_error1)
		{
			try
			{
				auto curPath = std::filesystem::current_path();
				curPath = curPath.parent_path().parent_path().append("Test_error/error1");
				ReflectionManager::instance().load(curPath.string(), "profile");
				Assert::Fail();
			}
			catch (ReflectionException& except)
			{
				auto msg = except.message();
				std::cout << msg;
			}
		}

		TEST_METHOD(Test_error2)
		{
			try
			{
				auto curPath = std::filesystem::current_path();
				curPath = curPath.parent_path().parent_path().append("Test_error/error2");
				ReflectionManager::instance().load(curPath.string(), "profile");
				Assert::Fail();
			}
			catch (ReflectionException& except)
			{
				auto msg = except.message();
				std::cout << msg;
			}
		}

		TEST_METHOD(Test_error3)
		{
			try
			{
				auto curPath = std::filesystem::current_path();
				curPath = curPath.parent_path().parent_path().append("Test_error/error3");
				ReflectionManager::instance().load(curPath.string(), "profile");
				Assert::Fail();
			}
			catch (ReflectionException& except)
			{
				auto msg = except.message();
				std::cout << msg;
			}
		}
	};
}
