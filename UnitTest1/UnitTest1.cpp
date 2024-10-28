#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <utility>
#include "../Lab7/Lab7.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestCalculateDegrees)
		{
			int n = 5;
			std::vector<std::pair<int, int>> edges = { {1, 2}, {2, 3}, {3, 4}, {4, 5} };
			std::vector<std::vector<int>> adjacencyMatrix = createAdjacencyMatrix(n, edges);

			std::vector<int> degrees(n);
			calculateDegrees(adjacencyMatrix, n, degrees);

			std::vector<int> expectedDegrees = { 1, 2, 2, 2, 1 };

			for (int i = 0; i < n; ++i) {
				Assert::AreEqual(expectedDegrees[i], degrees[i], L"Stepen vertex ne vidhovidaye ochikuvannyu");
			}
		}

		TEST_METHOD(TestIsHomogeneous)
		{
			std::vector<int> degrees1 = { 2, 2, 2, 2 }; // Однорідний граф
			std::vector<int> degrees2 = { 1, 2, 2, 1 }; // Не однорідний граф

			Assert::IsTrue(isHomogeneous(degrees1), L"Graf povynen buty odnoridnym");
			Assert::IsFalse(isHomogeneous(degrees2), L"Graf ne povynen buty odnoridnym");
		}

		TEST_METHOD(TestFindIsolatedAndHangingVertices)
		{
			std::vector<int> degrees = { 1, 2, 2, 2, 1 };
			std::vector<int> isolated;
			std::vector<int> hanging;

			findIsolatedAndHangingVertices(degrees, isolated, hanging);

			std::vector<int> expectedIsolated = {}; // В цьому графі немає ізольованих вершин
			std::vector<int> expectedHanging = { 1, 5 }; // Вершини 1 і 5 є висячими

			Assert::AreEqual(expectedIsolated.size(), isolated.size(), L"Kilkist izolovanuh ne vidhovidaye ochikuvannyu");
			for (size_t i = 0; i < isolated.size(); ++i) {
				Assert::AreEqual(expectedIsolated[i], isolated[i], L"Znahodzhena izolovana vershyna ne vidhovidaye ochikuvannyu");
			}

			Assert::AreEqual(expectedHanging.size(), hanging.size(), L"Kilkist vysiachyh ne vidhovidaye ochikuvannyu");
			for (size_t i = 0; i < hanging.size(); ++i) {
				Assert::AreEqual(expectedHanging[i], hanging[i], L"Znahodzhena vysiacha vershyna ne vidhovidaye ochikuvannyu");
			}
		}
	};
}
