/*
* Arduino JSON library
* Benoit Blanchon 2014 - MIT License
*/

#include "CppUnitTest.h"
#include "JsonParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ArduinoJson::Parser;

namespace ArduinoJsonParserTests
{
	TEST_CLASS(JsonArrayTests)
	{
		JsonParser<32> parser;

	public:
		
		TEST_METHOD(EmptyString)
		{
			char json[] = "";

			JsonArray array = parser.parseArray(json);
			Assert::IsFalse(array.success());
		}

		TEST_METHOD(EmptyArray)
		{
			char json[] = "[]";

			JsonArray array = parser.parseArray(json);
			Assert::IsTrue(array.success());
		}

		TEST_METHOD(TooFewClosingBrackets)
		{
			char json[] = "[[]";

			JsonArray array = parser.parseArray(json);
			Assert::IsFalse(array.success());
		}

		TEST_METHOD(TooManyClosingBrackets)
		{
			char json[] = "[]]";

			JsonArray array = parser.parseArray(json);
			Assert::IsFalse(array.success());
		}
		
		TEST_METHOD(OneDimensionArray)
		{
			char json [] = "[0,0]";

			JsonArray array = parser.parseArray(json);
			Assert::IsTrue(array.success());
			Assert::AreEqual(2, array.getLength());

			for (int i = 0; i < 2; i++)
			{
				Assert::AreEqual(0L, array.getLong(i));
			}
		}

		TEST_METHOD(TwoDimensionsArray)
		{
			char json[] = "[[0,0],[0,0]]";

			JsonArray array1 = parser.parseArray(json);
			Assert::IsTrue(array1.success());
			Assert::AreEqual(2, array1.getLength());

			for (int i = 0; i < 2; i++)
			{
				JsonArray array2 = array1.getArray(i);

				Assert::AreEqual(2, array2.getLength());

				for (int j = 0; j < 2; j++)
				{
					Assert::AreEqual(0L, array2.getLong(j));
				}
			}
		}

		TEST_METHOD(TreeDimensionsArray)
		{
			char json[] = "[[[0,0],[0,0]],[[0,0],[0,0]]]";

			JsonArray array1 = parser.parseArray(json);
			Assert::IsTrue(array1.success());
			Assert::AreEqual(2, array1.getLength());

			for (int i = 0; i < 2; i++)
			{
				JsonArray array2 = array1.getArray(i);

				Assert::AreEqual(2, array2.getLength());

				for (int j = 0; j < 2; j++)
				{
					JsonArray array3 = array2.getArray(j);

					Assert::AreEqual(2, array3.getLength());

					for (int k = 0; k < 2; k++)
					{
						Assert::AreEqual(0L, array3.getLong(k));
					}
				}
			}
		}

		TEST_METHOD(OneDimensionArrayInHashTable)
		{
			char json[] = "{a:[0,0],b:[0,0]}";

			JsonHashTable root = parser.parseHashTable(json);
			Assert::IsTrue(root.success());

			JsonArray arrayA = root.getArray("a");
			Assert::IsTrue(arrayA.success());
			Assert::AreEqual(2, arrayA.getLength());

			JsonArray arrayB = root.getArray("b");
			Assert::IsTrue(arrayB.success());
			Assert::AreEqual(2, arrayB.getLength());
		}

		TEST_METHOD(TwoDimensionsArrayInHashTable)
		{
			char json[] = "{a:[[0],[0]],b:[[0],[0]]}";

			JsonHashTable root = parser.parseHashTable(json);
			Assert::IsTrue(root.success());

			JsonArray arrayA = root.getArray("a");
			Assert::IsTrue(arrayA.success());
			Assert::AreEqual(2, arrayA.getLength());

			JsonArray arrayB = root.getArray("b");
			Assert::IsTrue(arrayB.success());
			Assert::AreEqual(2, arrayB.getLength());
		}

        TEST_METHOD(MatrixOfDoubles)
        {
            char json[] = "[[1.2,3.4],[5.6,7.8]]";

            JsonArray array = parser.parseArray(json);
            Assert::IsTrue(array.success());

            Assert::AreEqual(2, array.getLength());

            JsonArray innerArray0 = array.getArray(0);
            Assert::AreEqual(2, innerArray0.getLength());
            Assert::AreEqual(1.2, innerArray0.getDouble(0));
            Assert::AreEqual(3.4, innerArray0.getDouble(1));

            JsonArray innerArray1 = array.getArray(1);
            Assert::AreEqual(2, innerArray1.getLength());
            Assert::AreEqual(5.6, innerArray1.getDouble(0));
            Assert::AreEqual(7.8, innerArray1.getDouble(1));
        }
	};
}