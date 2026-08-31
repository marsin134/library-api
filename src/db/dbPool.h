#pragma once
#include <pqxx/pqxx>
#include <memory>
#include <string>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <iostream>

class DbPool {
private:
    std::string conn_string_;
    int pool_size_;
    std::queue<std::shared_ptr<pqxx::connection>> pool_;
    std::mutex mutex_;
    std::condition_variable cv_;

public:
    DbPool(const std::string&connection_string, int pool_size = 10);

    std::shared_ptr<pqxx::connection> getConnection();

    void releaseConnection(std::shared_ptr<pqxx::connection> conn);
};