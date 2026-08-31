#include "bookRepository.h"

using namespace std;

BookRepository::BookRepository(shared_ptr<DbPool> pool) : pool_(pool) {}

optional<Book> BookRepository::getById(int id) {
    try {
        auto conn = pool_->getConnection();
        pqxx::work txn(*conn);

        pqxx::result result = txn.exec_params(
            "SELECT id, title, author, year, genre FROM books WHERE id = $1",
            id
        );

        if (result.empty()) {
            return nullopt;
        }

        const auto& row = result[0];
        Book book{
            row["id"].as<int>(),
            row["title"].as<string>(),
            row["author"].as<string>(),
            row["year"].as<int>(),
            row["genre"].as<string>()
        };

        return book;
    } catch (const exception& e) {
        cerr << "Error fetching book by ID: " << e.what() << endl;
        return nullopt;
    }
}   