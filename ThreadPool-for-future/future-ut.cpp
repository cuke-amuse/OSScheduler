#include <iostream>
#include <vector>
#include <chrono>

#include <gtest/gtest.h>
#include "ThreadPool.h"

class ThreadFunc {
public :
    int ThreeDul(int x) {
        return x * factor_;
    };
    void SetFactor(int x)
    {
        factor_ = x;
    }
private:
    int factor_{3};
};

int  Mul (int x) 
{
      return x + x;
};

TEST(ThreadPool, lambda)
{
    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 3; ++i) {
        results.emplace_back(
            pool.enqueue([i] () -> int {
                std::cout << "hello " << i << "/run at thread: " << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i*i;
            })
        );
    }

   // std::vector<int> res = {std::future<int>(0) ,std::future<int>(1) ,std::future<int>(2) ,std::future<int>(3)};
   // EXPECT_EQ(results, res);
}

TEST(ThreadPool, Global)
{
    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue(Mul, i)
        );
    }

   // std::vector<int> res = {std::future<int>(0) ,std::future<int>(1) ,std::future<int>(2) ,std::future<int>(3)};
   // EXPECT_EQ(results, res);
}

TEST(ThreadPool, ClassMember)
{
    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    ThreadFunc funT;
     funT.SetFactor(5);
     for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue(&ThreadFunc::ThreeDul, &funT, i)
        );
    }

   // std::vector<int> res = {std::future<int>(0) ,std::future<int>(1) ,std::future<int>(2) ,std::future<int>(3)};
   // EXPECT_EQ(results, res);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}