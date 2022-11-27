#ifndef ENV_UTILS_H
#define ENV_UTILS_H

#include <iostream>
//#include <sys/prctl.h>

class EnvUtils {
public:
    static void SetThreadAffinite(int aimCpu = 6, int anthorCpu = 5)
    {
        cpu_set_t mask;
        CPU_ZERO( &mask );
        CPU_SET(aimCpu, &mask );
        CPU_SET(anthorCpu, &mask );
    // 0 means current process
        if ( sched_setaffinity( 0, sizeof(mask), &mask ) == -1 ){
            //std::cout << "WARNING: Could not set CPU Affinity, continuing..." << std::endl; 
        } else {
           // std::cout << "Bind process #" << std::endl;
        }
    }
};

#endif