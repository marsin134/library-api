#include <string>

struct DBConfig {
    std::string host;
    int port;
    std::string dbname;
    std::string user;
    std::string password;
    int connectionPoolSize;
};

struct CacheConfig {
    std::string host;
    int port;
    int ttlSeconds;
};

struct ServerConfig {
    int port;
    int threads;
};

class Config {
    public:
        ServerConfig server;
        DBConfig db;
        CacheConfig cache;

    private:
        bool load(const std::string &filename);
};

