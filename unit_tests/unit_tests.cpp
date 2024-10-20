#include "pch.h"
#include "CppUnitTest.h"
#include <filesystem>
#include "test_reflect_structs.h" // before DeserializeManager
#include "deserialize_flag.h"
#include "DeserializeManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittests
{
	TEST_CLASS(load_serialized)
	{
	public:
		
		TEST_METHOD(load_file)
		{
			auto curPath = std::filesystem::current_path();
			curPath = curPath.parent_path().parent_path().append("test_files/profiles");
			DeserializeManager::instance().load(curPath.string(), "profile_test");
		}

		TEST_METHOD(reflect_base)
		{
			auto curPath = std::filesystem::current_path();
			curPath = curPath.parent_path().parent_path().append("test_files/profiles");
			DeserializeManager::instance().load(curPath.string(), "profile_unit_test");
			
			STest_simple testStruct;
			Assert::AreEqual(testStruct.Test_short, static_cast<short>(1), L"WRONG SHORT");
			Assert::AreEqual(testStruct.Test_int, 2, L"WRONG INT");
			Assert::AreEqual(testStruct.Test_float, 3.4f, L"WRONG FLOAT");
			Assert::AreEqual(testStruct.Test_string, std::string("test"), L"WRONG STRING");
		}

		TEST_METHOD(reflect_flags)
		{
			auto curPath = std::filesystem::current_path();
			curPath = curPath.parent_path().parent_path().append("test_files");
			DeserializeManager::instance().load(curPath.string(), "profile_flag");

			FlagStruct flag;
			Assert::AreEqual(static_cast<unsigned int>(flag.flagVal), static_cast<unsigned int>(EFlag::Flag1 | EFlag::Flag2), L"WRONG FLAG");
			//Assert::AreEqual(testStruct.Test_int, 2, L"WRONG INT");
			//Assert::AreEqual(testStruct.Test_float, 3.4f, L"WRONG FLOAT");
			//Assert::AreEqual(testStruct.Test_string, std::string("test"), L"WRONG STRING");
		}
	};
}
