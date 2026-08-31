#pragma once
#include "dbPool.h"
#include <pqxx/pqxx>
#include <optional>
#include <string>
#include <iostream>

struct Book {
    int id;
    std::string title;
    std::string author;
    int year;
    std::string genre;
};

class BookRepository {
public:
    explicit BookRepository(std::shared_ptr<DbPool> pool) : pool_(pool) {}

    std::optional<Book> getById(int id) {}

private:
    std::shared_ptr<DbPool> pool_;
};