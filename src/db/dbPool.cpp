#include "dbPool.h"

using namespace std;

DbPool::DbPool(const string &connection_string, int pool_size = 5) : conn_string_(connection_string), pool_size_(pool_size)  {
    for (int i = 0; i < pool_size_; ++i) {
            try {
                auto conn = make_shared<pqxx::connection>(conn_string_);
                pool_.push(conn);
            } catch (const exception& e) {
                cerr << "DB Connection error: " << e.what() << endl;
            }
    }
}

shared_ptr<pqxx::connection> DbPool::getConnection() {
        unique_lock<mutex> lock(mutex_);
        cv_.wait(lock, [this] { return !pool_.empty(); });
        auto conn = pool_.front();
        pool_.pop();
        return conn;
}

void DbPool::releaseConnection(std::shared_ptr<pqxx::connection> conn) {
        std::lock_guard<std::mutex> lock(mutex_);
        pool_.push(conn);
        cv_.notify_one();
}