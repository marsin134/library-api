#pragma once
#include <sw/redis++/redis++.h>
#include <string>
#include <optional>

class CacheManager {
public:
    CacheManager(const std::string& host, int port, int ttl_seconds);

    void set(const std::string& key, const std::string& value);

    std::optional<std::string> get(const std::string& key);

private:
    std::unique_ptr<sw::redis::Redis> redis_;
    int ttl_seconds_;
};