#include "bookService.h"

using namespace std;

BookService::BookService(shared_ptr<BookRepository> repo, 
            shared_ptr<CacheManager> cache)
    : repo_(repo), cache_(cache) {}

optional<json> BookService::getBook(int id) {
    auto cached = cache_->get("book:" + to_string(id));
    if (cached) {
        return json::parse(*cached);
    }

    auto book_opt = repo_->getById(id);
    if (!book_opt) {
        return nullopt; 
    }

    json book_json = {
        {"id", book_opt->id},
        {"title", book_opt->title},
        {"author", book_opt->author},
        {"year", book_opt->year},
        {"genre", book_opt->genre}
    };

    cache_->set("book:" + to_string(id), book_json.dump());

    return book_json;
}

