#include "config.h"
#include "db/dbPool.h"
#include "db/bookRepository.h"
#include "cache/cacheManager.h"
#include "service/bookService.h"

#include <crow.h>
#include <memory>
#include <iostream>

using namespace std;

int main() {
    Config config;
    if (!config.load("config.json")) {
        return 1;
    }

    string conn_str = 
        "host=" + config.db.host + 
        " port=" + to_string(config.db.port) + 
        " dbname=" + config.db.dbname + 
        " user=" + config.db.user + 
        " password=" + config.db.password;

    auto db_pool = make_shared<DbPool>(conn_str, 10);
    auto book_repo = make_shared<BookRepository>(db_pool);

    auto cache = make_shared<CacheManager>(
        config.cache.host, 
        config.cache.port, 
        config.cache.ttl_seconds
    );

    shared_ptr<BookService> book_service = make_shared<BookService>(book_repo, cache);

    crow::SimpleApp app;

    CROW_ROUTE(app, "/book/<int>")
    ([book_service](int book_id) {
        auto result = book_service->getBook(book_id);
        if (result) {
            return crow::response(200, result->dump());
        } else {
            return crow::response(404, "{\"error\": \"Book not found\"}");
        }
    });

    cout << "Start" << endl;

    app.port(config.server.port)
       .concurrency(config.server.threads)
       .run();

    return 0;
}