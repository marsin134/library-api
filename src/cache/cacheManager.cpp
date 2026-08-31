#include "cacheManager.h"

using namespace std;

CacheManager::CacheManager(const string& host, int port, int ttl_seconds)
    : ttl_seconds_(ttl_seconds) {
    redis_ = make_unique<sw::redis::Redis>("tcp://" + host + ":" + to_string(port));
}


void CacheManager::set(const string &key, const string &value) {
        redis_->setex(key, ttl_seconds_, value);
}

optional<string> CacheManager::get(const string &key) try {
    auto val = redis_->get(key);
    if (val) return *val;
        return nullopt;
    } catch (...) {
        return nullopt;
}
