/*! \file   ArrayAdd1.cpp
 *  \brief  Array addition - single threaded
 *  \author Yi Zhao
 *  \date   07/28/2022
 */

#include <chrono> 

#include <math.h>
#include <stdio.h>

using std::chrono::high_resolution_clock;
using std::chrono::duration;

#define MAX_ARRAY_SIZE  1000000

double ArrayA[MAX_ARRAY_SIZE];
double ArrayB[MAX_ARRAY_SIZE];
double ArrayC[MAX_ARRAY_SIZE];

void ClearAll()
{
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        ArrayA[i] = ArrayB[i] = ArrayC[i] = 0;
    }
}

void InitArray()
{
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        ArrayA[i] = rand();
        ArrayB[i] = rand();
    }
}

void AddArray()
{
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        ArrayC[i] = cos(ArrayA[i]) + sin(ArrayB[i]);
}

void Test()
{
    auto t1 = high_resolution_clock::now();
    AddArray();
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> dif = t2 - t1;
    double et = dif.count();
    printf("  ET = %.3lf ms\n", et);
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
