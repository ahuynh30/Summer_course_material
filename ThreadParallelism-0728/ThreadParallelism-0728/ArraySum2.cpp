/*! \file   ArraySum2.cpp
 *  \brief  Sum of array - multi threaded with bug in data race
 *  \author Yi Zhao
 *  \date   07/28/2022
 */

#include <chrono> 
#include <thread>

#include <math.h>
#include <stdio.h>

using std::chrono::high_resolution_clock;
using std::chrono::duration;

#define MAX_ARRAY_SIZE  1000000

int Array[MAX_ARRAY_SIZE];
int Sum = 0;

void ClearAll()
{
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        Array[i] = 0;
    }
}

void InitArray()
{
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        Array[i] = 1;
}

void SumArray()
{
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        Sum += round(acos(cos(Array[i])));
}

void SumArrayL()
{
    for (int i = 0; i < MAX_ARRAY_SIZE / 2; i++)
        Sum += round(acos(cos(Array[i])));
}

void SumArrayR()
{
    for (int i = MAX_ARRAY_SIZE / 2; i < MAX_ARRAY_SIZE; i++)
        Sum += round(acos(cos(Array[i])));;
}

void DisplaySum()
{
    printf("  Sum = %d\n", Sum);
}

void Test()
{
    Sum = 0;
    auto t1 = high_resolution_clock::now();
    std::thread sumL(SumArrayL);
    std::thread sumR(SumArrayR);
    sumL.join();
    sumR.join();
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> dif = t2 - t1;
    double et = dif.count();
    printf("  ET = %.3lf ms\n", et);
    DisplaySum();
}

int main()
{
    ClearAll();
    InitArray();
    for (int i = 1; i <= 10; i++)
    {
        printf("Run = %d\n", i);
        Test();
    }
    return 0;
}
