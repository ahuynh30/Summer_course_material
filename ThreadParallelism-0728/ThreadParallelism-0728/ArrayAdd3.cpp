/*! \file   ArrayAdd3.cpp
 *  \brief  Array addition - comparison of single/double threaded
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

double ArrayA[MAX_ARRAY_SIZE];
double ArrayB[MAX_ARRAY_SIZE];
double ArrayC[MAX_ARRAY_SIZE];
double ArrayD[MAX_ARRAY_SIZE];

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

void AddArrayL()
{
    for (int i = 0; i < MAX_ARRAY_SIZE / 2; i++)
        ArrayD[i] = cos(ArrayA[i]) + sin(ArrayB[i]);
}

void AddArrayR()
{
    for (int i = MAX_ARRAY_SIZE / 2; i < MAX_ARRAY_SIZE; i++)
        ArrayD[i] = cos(ArrayA[i]) + sin(ArrayB[i]);
}

double GetSAD()
{
    double SAD = 0;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        SAD += fabs(ArrayC[i] - ArrayD[i]);
    return SAD;
}

void Test()
{
    {
        auto t1 = high_resolution_clock::now();
        AddArray();
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> dif = t2 - t1;
        double et = dif.count();
        printf("  ET-1 = %.3lf ms\n", et);
    }
    {
        auto t1 = high_resolution_clock::now();
        std::thread addL(AddArrayL);
        std::thread addR(AddArrayR);
        addL.join();
        addR.join();
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> dif = t2 - t1;
        double et = dif.count();
        printf("  ET-2 = %.3lf ms\n", et);
    }
    printf("  SAD = %.6lf\n", GetSAD());
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
