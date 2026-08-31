#pragma once
#include "../db/bookRepository.h"
#include "../cache/cacheManager.h"
#include <nlohmann/json.hpp>
#include <memory>

using json = nlohmann::json;

class BookService {
public:
    BookService(std::shared_ptr<BookRepository> repo, 
                std::shared_ptr<CacheManager> cache);

    std::optional<json> getBook(int id);

private:
    std::shared_ptr<BookRepository> repo_;
    std::shared_ptr<CacheManager> cache_;
};