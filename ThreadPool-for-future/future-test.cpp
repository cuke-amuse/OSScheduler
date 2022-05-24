#include <iostream>
#include <vector>
#include <chrono>

#include "ThreadPool.h"

class ThreadFunc {
public :
    int threeDul(int x) {
        return x * 3;
    };
};

int  mul (int x) {
  // std::cout << "calc:" << x << std::endl;
  //return x + y;
  return x + x;
}

int main()
{
    ThreadPool pool(4);
    std::vector< std::future<int> > results;
#if 0
    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i] () -> int {
                std::cout << "hello " << i << "/run at thread: " << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i*i;
            })
        );
    }
#endif
    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue(mul, i)
        );
    }
 
 ThreadFunc funT;

     for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue(&ThreadFunc::threeDul, &funT, i)
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
    
    return 0;
}
