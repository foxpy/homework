#include <numeric>
#include <cstring>
#include <iostream>
#include <vector>

class BookCounter;
class Book {
private:
    unsigned long id;
    char author[20]{};
    unsigned year;
    unsigned count;
public:
    friend BookCounter;
    Book(unsigned long id, const char* author, unsigned year, unsigned count): id(id), year(year), count(count) {
        strncpy(this->author, author, 20);
    }
};

class BookCounter {
public:
    template<typename Iter>
    static unsigned count_books(Iter first, Iter last) {
        return std::accumulate(first, last, 0, op);
    }
private:
    static unsigned op(unsigned count, const Book& book) {
        return count + ((book.year >= 2007 && book.year <= 2016 && strcmp(book.author, "Robert") == 0) ? book.count : 0);
    }
};

int main() {
    std::vector<Book> books;
    books.emplace_back(1, "Robert", 2012, 3);
    books.emplace_back(2, "Robert", 2003, 2);
    books.emplace_back(3, "Straustrup", 2017, 1);
    books.emplace_back(4, "Richie", 1995, 1);
    books.emplace_back(5, "Robert", 2015, 4);
    std::cout << BookCounter::count_books(books.cbegin(), books.cend()) << std::endl;
}
