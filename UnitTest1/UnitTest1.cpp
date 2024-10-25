#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <cstdio> 
#include "../PDS_LAB_9/PDS_LAB_9.cpp"  

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestReadGraph)
        {
            const char* filename = "test_graph.txt";

            
            std::ofstream testFile(filename);
            testFile << "0 1 0\n";
            testFile << "1 0 1\n";
            testFile << "0 1 0\n";
            testFile.close();

            
            auto graph = readGraph(filename);

           
            Assert::AreEqual(3, static_cast<int>(graph.size())); 
            Assert::AreEqual(3, static_cast<int>(graph[0].size())); 

            
            int expectedGraph[3][3] = {
                {0, 1, 0},
                {1, 0, 1},
                {0, 1, 0}
            };

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    Assert::AreEqual(expectedGraph[i][j], graph[i][j]);
                }
            }

            
            std::remove(filename);
        }
    };
}
