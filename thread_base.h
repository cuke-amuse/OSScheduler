#ifndef THREAD_BASE_H
#define THREAD_BASE_H

#include <thread>
#include <atomic>
#include <vector>
#include <functional>
#include <sys/prctl.h>
#include <algorithm>
#include <chrono>
#include <iostream>

class ThreadBase {
public:
    //const std::string defaultName = "ThreadBase";
    explicit ThreadBase(const std::string& name = "ThreadBase")
    : threadName_(name),
      maxWork_(50) {
        prctl(PR_SET_NAME, "threadbase");
        Start();   //  ??
    }
    ~ThreadBase() {
        stop_ = true;
        if (worker_.joinable()) {
            worker_.join();
        }
    }
    void Start()
    {
        //worker_ = std::thread(&ThreadBase::Worker, this);
        ThreadSwitchTest();
    }
    static ThreadBase& Instance()
    {
        static ThreadBase tb;
        return tb;
    }
    void Worker(int sleepTime = 20)
    {
        while(!stop_) {
            for (const auto work : workGroup_) {
                work();
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            }
        }
    }
    bool SetWork(std::function<void()>& func)
    {
        if (workGroup_.size() > maxWork_) {
            return false;
        }
        workGroup_.push_back(func);
        return true;
    }

    void RemoveWork(std::function<void()>& func)
    {
        std::vector<std::function<void()>>::iterator it;
        //it = std::find(workGroup_.begin(), workGroup_.end(), func);
        if (it != workGroup_.end()) {
            workGroup_.erase(it);
        }
    }

    void Print(int num)
    {
        //int num = 0;
        while (!stopT_) {
            //printf("schedule %d\n", num);
            num++;
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }

    void ThreadSwitchTest()
    {
        for (int i = 0; i < 83; ++i) {
            threadG_.push_back(std::thread(&ThreadBase::Print, this, i));
        }
    }
private:
    std::atomic<bool> stop_{false};
    std::vector<std::function<void()>> workGroup_;
    std::thread worker_;
    std::string threadName_;
    int maxWork_;
    bool stopT_{false};
    std::vector<std::thread> threadG_;
};

#endif