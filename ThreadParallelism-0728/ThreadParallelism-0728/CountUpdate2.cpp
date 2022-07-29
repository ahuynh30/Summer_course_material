/*! \file   CountUpdate2.cpp
 *  \brief  Update count - multi threaded with bug in data race
 *  \author Yi Zhao
 *  \date   07/28/2022
 */

#include <chrono> 
#include <thread>

#include <math.h>
#include <stdio.h>

using namespace std::chrono_literals;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

int Count = 0;
int IncNum = 101;
int DecNum = 100;

void IncreaseCount()
{
    for (int i = 0; i < IncNum; i++)
    {
        std::this_thread::sleep_for(1ms);
        ++Count;
    }
}

void DecreaseCount()
{
    for (int i = 0; i < DecNum; i++)
    {
        std::this_thread::sleep_for(1ms);
        --Count;
    }
}

void DisplayCount()
{
    printf("  Count = %d\n", Count);
}

void Test()
{
    Count = 0;
    auto t1 = high_resolution_clock::now();
    std::thread incCount(IncreaseCount);
    std::thread decCount(DecreaseCount);
    incCount.join();
    decCount.join();
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> dif = t2 - t1;
    double et = dif.count();
    printf("  ET = %.3lf ms\n", et);
    DisplayCount();
}

int main()
{
    for (int i = 1; i <= 10; i++)
    {
        printf("Run = %d\n", i);
        Test();
    }
    return 0;
}
