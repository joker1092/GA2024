#include <iostream>
#include <vector>
#include <random>
#include <Windows.h>

using namespace std;

vector<char> ItemInfo = { 'A','B','C','D','E','F','G','H' };
vector<int> ItemProb = { 1,3,6,10,10,20,20,30 };
vector<int> AccumulatedProb;
vector<char> ItemIndexTable;

uniform_int_distribution<int> uniform_dist(0, 99); // 0부터 99까지 균등 분포
discrete_distribution<int> discreteDist({ 1, 3, 6, 10, 10, 20, 20, 30 }); // 확률을 등록

char PickItemByAccumulatedProb(mt19937& gen)
{
    //누적 확률 테이블을 이용하여 아이템을 선택하도록 작성해 보세요.
    int a = uniform_dist(gen);
    for (size_t i = 0; i < AccumulatedProb.size(); i++)
    {
        if (AccumulatedProb[i] > a)
        {
            return 'A' + i;
        }
    }
};

char PickItemByIndexTable(mt19937& gen)
{
    // O(1) 시간에 아이템을 선택이 가능하도록 작성해 보세요.
    //uniform_dist(gen);
    //int a =ItemIndexTable[uniform_dist(gen)];

    return ItemIndexTable[uniform_dist(gen)];//'A';
}

char GetItemByDiscreteDist(mt19937& gen)
{
    // 이산 확률 분포를 이용하여 아이템을 선택하도록 작성해 보세요.
    return 'A' + discreteDist(gen);//;
}

// 테스트 코드
void Test(const int TEST_COUNT)
{
    random_device rd;
    mt19937 gen(rd());

    char _temp;

    cout << "-------- PickItemByAccumulatedProb --------" << endl << endl;
    {
        int _test1[8] = { 0 };
        ULONGLONG startTick = GetTickCount64();

        for (int i = 0; i < TEST_COUNT; i++)
        {
            _temp = PickItemByAccumulatedProb(gen);
            _test1[_temp - 'A'] += 1;
        }
        ULONGLONG endTick = GetTickCount64();

        for (int i = 0; i < 8; i++)
            cout << (char)('A' + i) << " : " << (float)_test1[i] / (float)(TEST_COUNT / 100) << endl;

        cout << "<<<<<<  테스트 결과 1 :  " << (endTick - startTick) << endl;
    }

    cout << "-------- PickItemByIndexTable --------" << endl << endl;
    {
        int _test1[8] = { 0 };
        ULONGLONG startTick = GetTickCount64();
        for (int i = 0; i < TEST_COUNT; i++)
        {
            _temp = PickItemByIndexTable(gen);
            _test1[_temp - 'A'] += 1;
        }
        ULONGLONG endTick = GetTickCount64();

        for (int i = 0; i < 8; i++)
            cout << (char)('A' + i) << " : " << (float)_test1[i] / (float)(TEST_COUNT / 100) << endl;

        cout << "<<<<<<  테스트 결과 2 :  " << (endTick - startTick) << endl;
    }

    cout << "-------- GetItemByDiscreteDist --------" << endl << endl;
    {
        int _test1[8] = { 0 };
        ULONGLONG startTick = GetTickCount64();
        for (int i = 0; i < TEST_COUNT; i++)
        {
            _temp = GetItemByDiscreteDist(gen);
            _test1[_temp - 'A'] += 1;
        }
        ULONGLONG endTick = GetTickCount64();

        for (int i = 0; i < 8; i++)
            cout << (char)('A' + i) << " : " << (float)_test1[i] / (float)(TEST_COUNT / 100) << endl;

        cout << "<<<<<<  테스트 결과 3 :  " << (endTick - startTick) << endl;
    }
}

void main()
{
    // 1. 누적확률 테이블 생성해 놓기
    for (size_t i = 0; i < ItemProb.size(); i++)
    {
        if (i == 0) {
            AccumulatedProb.push_back(ItemProb[i]);
        }
        else {
            AccumulatedProb.push_back(AccumulatedProb[i - 1] + ItemProb[i]);
        }

    }
    // 2. 인덱스 테이블 생성해 놓기   
    for (size_t i = 0; i < ItemProb.size(); i++)
    {
        for (size_t j = 0; j < ItemProb[i]; j++)
        {
            ItemIndexTable.push_back('A' + i);
        }
    }

    // 3. 테스트!
    Test(1000000);
}
