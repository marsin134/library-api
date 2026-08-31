#pragma once
#include <pqxx/pqxx>
#include <memory>
#include <string>
#include <mutex>
#include <queue>
#include <iostream>

class DbPool {
private:
    std::string conn_string_;
    int pool_size_;
    std::queue<std::shared_ptr<pqxx::connection>> pool_;
    std::mutex mutex_;
    std::condition_variable cv_;

public:
    DbPool(const std::string&connection_string, int pool_size = 10) 
        : conn_string_(connection_string), pool_size_(pool_size) {}

    std::shared_ptr<pqxx::connection> getConnection() {}

    void releaseConnection(std::shared_ptr<pqxx::connection> conn) {}
};