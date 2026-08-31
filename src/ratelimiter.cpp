#include "ratelimiter.hpp"
#include <iostream>

RateLimiter::RateLimiter(long long window, int limit){

    T = window;
    L = limit;
}

void RateLimiter::purgeExpired(long long timestamp){

    int oldest;

    while (!timestamps.isEmpty()){

        oldest = timestamps.front();

        if (timestamp - oldest >= T){
            timestamps.dequeue(oldest);
        }

        else{
            break;
        }
    }
}

bool RateLimiter::allow(long long timestamp){

    purgeExpired(timestamp);

    if (timestamps.size() >= L){
        return false;
    }

    timestamps.enqueue(static_cast<int>(timestamp));
    return true;
}

int RateLimiter::size() const{
    return timestamps.size();
}

void RateLimiter::printState() const{
    std::cout << "Timestamps actuales: ";
    timestamps.print();
}
