/*
* 代码思路：创建一个连续内存块，进行连贯、大量、随机的有意义访问，要保证整块内存尽可能全部放入cache。当
* 内存被整块放入cache中时，访问速度会明显加快，直到有一个时间跳跃点，消耗时间增多，则这个跳跃点的存储容* 量大小即为cache大小
*/
 
#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
 
#define KB(x) ((size_t)(x) << 10)
 
//using namespace std;
 
int main()
{
    // 需要测试的数组的大小
    std::vector<size_t> sizes_KB;
    for (int i = 1; i < 18; i++) {
        sizes_KB.push_back(1 << i);
    }
    std::random_device rd;
    // 伪随机数算法，计算更快，占用内存更少
    std::mt19937 gen(rd());
 
    for (size_t size : sizes_KB) {
        // 离散均匀分布类
        std::uniform_int_distribution<> dis(0, KB(size) - 1);
        // 创建连续内存块
        std::vector<char> memory(KB(size));
        // 在内存中填入内容
        std::fill(memory.begin(), memory.end(), 1);
        
        int dummy = 0;
        
        // 在内存上进行大量的随机访问并计时
        clock_t begin = clock();
        // 1<<25：将1左移25位，进行大量随机访问
        for (int i = 0; i < (1 << 25); ++i) {
            dummy += memory[dis(gen)];
        }
        clock_t end = clock();
        
        // 输出
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        std::cout << size << " KB, " << elapsed_secs << "secs, dummy:" << dummy << std::endl;
    }
}
