#ifndef ratelimiter_hpp
#define ratelimiter_hpp
#include "listas.hpp"

class RateLimiter{

private:
    listas timestamps;
    long long T;
    int L;
    void purgeExpired(long long timestamp);

public:
    RateLimiter(long long window, int limit);
    bool allow(long long timestamp);
    void printState() const;
    int size() const;
};
#endif