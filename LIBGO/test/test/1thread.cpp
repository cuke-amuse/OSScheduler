#include <vector>
#include <boost/thread.hpp>
#include <boost/progress.hpp>

#include "coroutine.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "../libgo/scheduler/processer.h"

using namespace std;

std::atomic_int g_value{0};
static const int co_count = 1000000;
static const int switch_per_co = 10;
    std::vector<int> src(100000000, 2);
    std::vector<int> dst(100000000, 0 );
volatile int64_t start;
void f1()
{
   // std::copy(src.begin(), src.end(), dst);
   start = co::Processer::NowMicrosecond();
   dst.clear();
   dst = src;
   //NowMicrosecond()
   // for (int i = 0; i < switch_per_co; ++i) {
        printf("current task: %d/%d, cost : %ld\n", g_Scheduler.GetCurrentTaskID(), g_Scheduler.GetCurrentTaskYieldCount(), 
        co::Processer::NowMicrosecond() - start);  
        g_value++;  

        //co_yield;
   // }
}

    std::vector<int> src2(1000000, 3);
    std::vector<int> dst2(1000000, 0 );
void f2()
{
   // std::copy(src.begin(), src.end(), dst);
   start = co::Processer::NowMicrosecond();
   dst.clear();
   dst2 = src2;
   //NowMicrosecond()
   // for (int i = 0; i < switch_per_co; ++i) {
        printf("2current task: %d/%d, cost : %ld\n", g_Scheduler.GetCurrentTaskID(), g_Scheduler.GetCurrentTaskYieldCount(), 
        co::Processer::NowMicrosecond() - start);  
        g_value++;  

        //co_yield;
   // }
}

int main()
{
    //g_Scheduler.GetOptions().debug = dbg_all;
    //g_Scheduler.GetOptions().stack_size = 2048;

    for (int i = 0; i < co_count/2; ++i) {
        go f1;
    }

    for (int i = 0; i < co_count/2; ++i) {
        go f2;
    }

    printf("go task cnt: %d\n", g_Scheduler.TaskCount());     
    
    { 
        boost::progress_timer pt;
        while (!g_Scheduler.IsEmpty()) {
            g_Scheduler.Start(2, 2);  
        }
        printf("main thread, run %d coroutines, %d times switch. cost ", co_count, co_count * switch_per_co);
    }
    printf("%d\nend\n", (int)g_value);
    return 0;
}

