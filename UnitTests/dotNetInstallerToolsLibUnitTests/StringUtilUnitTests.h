#pragma once

namespace DVLib
{
	namespace UnitTests 
	{
		namespace String
		{
			class StringUtilUnitTests : public CPPUNIT_NS::TestFixture
			{
				CPPUNIT_TEST_SUITE( StringUtilUnitTests );
				CPPUNIT_TEST( teststring2long );
				CPPUNIT_TEST( teststring2ulong );
				CPPUNIT_TEST( testsplitjoin );				
                CPPUNIT_TEST( testtrim );
				CPPUNIT_TEST( testreplace );
				CPPUNIT_TEST( teststring2wstring );
				CPPUNIT_TEST( testwstring2string );
				CPPUNIT_TEST( testlong2string );
				CPPUNIT_TEST( testlong2wstring );
				CPPUNIT_TEST( testtostring );
				CPPUNIT_TEST( testtowstring );
				CPPUNIT_TEST( teststartswith );
				CPPUNIT_TEST( testendswith );
				CPPUNIT_TEST( testUTF82wstring );
				CPPUNIT_TEST_SUITE_END();
			public:
				void teststring2long();
				void teststring2ulong();
				void testsplitjoin();				
                void testtrim();
				void testreplace();
				void teststring2wstring();
				void testwstring2string();
				void testlong2string();
				void testlong2wstring();
				void testtostring();
				void testtowstring();
				void teststartswith();
				void testendswith();
				void testUTF82wstring();
			};
		}
	}
}
