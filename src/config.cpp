#include "config.h"
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

bool Config::load(const string &configFilePath) {
    try {
        ifstream file(configFilePath);
        if (!file.is_open()) {
            cerr << "Failed to open config file: " << configFilePath << endl;
            return false;
        }

        json data;
            file >> data;

            server.port = data["server"]["port"];
            server.threads = data["server"]["threads"];

            db.host = data["database"]["host"];
            db.port = data["database"]["port"];
            db.dbname = data["database"]["dbname"];
            db.user = data["database"]["user"];
            db.password = data["database"]["password"];
            db.connectionPoolSize = data["database"]["connection_pool_size"];

            cache.host = data["cache"]["host"];
            cache.port = data["cache"]["port"];
            cache.ttlSeconds = data["cache"]["ttl_seconds"];


    } catch (const exception &e) {
        cerr << "Error loading config file: " << e.what() << endl;
        return false;
    }

    return true;
}