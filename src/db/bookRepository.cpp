#include "bookRepository.h"

std::optional<Book> BookRepository::getById(int id) {
    try {
        auto conn = pool_->getConnection();
        pqxx::work txn(*conn);

        pqxx::result result = txn.exec_params(
            "SELECT id, title, author, year, genre FROM books WHERE id = $1",
            id
        );

        if (result.empty()) {
            return std::nullopt;
        }

        const auto& row = result[0];
        Book book{
            row["id"].as<int>(),
            row["title"].as<std::string>(),
            row["author"].as<std::string>(),
            row["year"].as<int>(),
            row["genre"].as<std::string>()
        };

        return book;
    } catch (const std::exception& e) {
        std::cerr << "Error fetching book by ID: " << e.what() << std::endl;
        return std::nullopt;
    }
}   