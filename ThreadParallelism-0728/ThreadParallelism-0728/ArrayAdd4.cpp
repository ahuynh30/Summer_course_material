/*! \file   ArrayAdd4.cpp
 *  \brief  Array addition - general multi threaded
 *  \author Yi Zhao
 *  \date   07/28/2022
 */

#include <chrono> 
#include <thread>
#include <vector>

#include <math.h>
#include <stdio.h>

using std::chrono::high_resolution_clock;
using std::chrono::duration;

#define MAX_ARRAY_SIZE  1000000

double ArrayA[MAX_ARRAY_SIZE];
double ArrayB[MAX_ARRAY_SIZE];
double ArrayC[MAX_ARRAY_SIZE];
double ArrayD[MAX_ARRAY_SIZE];

int numThread = 2;

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

void AddArrayT(int head, int tail)
{
    for (int i = head; i < tail; i++)
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
        std::vector<std::thread*> workers;
        for (int i = 0; i < numThread; i++)
        {
            std::thread* current = new std::thread(AddArrayT, i * MAX_ARRAY_SIZE / numThread,
                (i + 1) * MAX_ARRAY_SIZE / numThread);
            workers.push_back(current);
        }
        for (int i = 0; i < numThread; i++)
        {
            if (workers[i]->joinable())
                workers[i]->join();
        }
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> dif = t2 - t1;
        double et = dif.count();
        printf("  ET-2 = %.3lf ms\n", et);
    }
    printf("  SAD = %.6lf\n", GetSAD());
}

int main(int argc, char* argv[])
{
    if (argc > 1)
        numThread = atoi(argv[1]);
    if (numThread <= 0)
        numThread = 1;
    ClearAll();
    InitArray();
    for (int i = 1; i <= 10; i++)
    {
        printf("Run = %d\n", i);
        Test();
    }
    return 0;
}

void foo(int N)                 //  thread function
{
    for (int i = 0; i < N; i++)  printf("%d", i);
}

int main()
{
    std::thread child(foo, 100);  //  parameter is 100
    child.join();            //  wait child to complete
}
