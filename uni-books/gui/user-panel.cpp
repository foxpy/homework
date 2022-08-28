#include "uni-books.hpp"

UserPanel::UserPanel(int x, int y, MainWindow *m): Fl_Widget(x, y, 700, 500) {
    main_window = m;
    box = new Fl_Box(x, y, 700, 500);
    table = new BooksTable(x, y, main_window);
    restore_table = new RestoreBooksTable(x, y, main_window);
    box->box(FL_UP_BOX);
    restore_books_button = new Fl_Button(x + 0, y + 460, 200, 40, "Restore books");
    restore_books_button->callback(restore_books_button_cb, main_window);
    go_back_button = new Fl_Button(x + 0, y + 460, 200, 40, "Go back");
    go_back_button->callback(go_back_button_cb, main_window);
    restore_book_button = new Fl_Button(x + 500, y + 460, 200, 40, "Restore book");
    restore_book_button->callback(restore_book_button_cb, main_window);
    new_book_button = new Fl_Button(x + 500, y + 460, 200, 40, "New book");
    new_book_button->callback(new_book_cb, main_window);
    delete_book_button = new Fl_Button(x + 300, y + 460, 200, 40, "Delete book");
    delete_book_button->callback(delete_book_cb, main_window);
}

UserPanel::~UserPanel() {
    delete box;
    delete table;
    delete restore_table;
    delete restore_books_button;
    delete restore_book_button;
    delete new_book_button;
    delete delete_book_button;
}

void UserPanel::draw() {}

void UserPanel::hide() {
    box->hide();
    table->hide();
    restore_table->hide();
    restore_books_button->hide();
    restore_book_button->hide();
    go_back_button->hide();
    new_book_button->hide();
    delete_book_button->hide();
}

void UserPanel::show() {
    box->show();
    table->show();
    restore_table->hide();
    restore_books_button->show();
    restore_book_button->hide();
    go_back_button->hide();
    new_book_button->show();
    delete_book_button->show();
}

BooksTable::BooksTable(int x, int y, MainWindow *m): Fl_Table(x, y, 700, 460) {
    main_window = m;
    books_count = 0;
    books = nullptr;
    end();
}

BooksTable::~BooksTable() {
    clear_books();
}

void BooksTable::DrawHeader(char const* s, int X, int Y, int W, int H) {
    fl_push_clip(X, Y, W, H);
    fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, row_header_color());
    fl_color(FL_BLACK);
    fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
    fl_pop_clip();
}

void BooksTable::DrawData(char const* s, int X, int Y, int W, int H) {
    fl_push_clip(X, Y, W, H);
    fl_color(FL_WHITE);
    fl_rectf(X, Y, W, H);
    fl_color(FL_GRAY0);
    fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
    fl_color(color());
    fl_rect(X, Y, W, H);
    fl_pop_clip();
}

void BooksTable::draw_cell(TableContext context, int ROW, int COL, int X, int Y, int W, int H) {
    switch (context) {
        case CONTEXT_STARTPAGE:
            fl_font(FL_HELVETICA, 16);
            return;
        case CONTEXT_COL_HEADER:
            char const* header_name;
            if (COL == 0) {
                header_name = "ISBN";
            } else if (COL == 1) {
                header_name = "Name";
            } else if (COL == 2) {
                header_name = "Author";
            } else if (COL == 3) {
                header_name = "Catalog";
            } else {
                header_name = "error";
            }
            DrawHeader(header_name, X, Y, W, H);
            return;
        case CONTEXT_CELL:
            char const* data;
            if (COL == 0) {
                data = books[ROW].isbn;
            } else if (COL == 1) {
                data = books[ROW].name;
            } else if (COL == 2) {
                data = books[ROW].author;
            } else if (COL == 3) {
                data = books[ROW].catalog;
            } else {
                data = "error";
            }
            DrawData(data, X, Y, W, H);
            return;
        default:
            return;
    }
}

void BooksTable::populate() {
    char* err;
    clear_books();
    ptrdiff_t num_books = database_get_books(main_window->database_handle, false, &books, &err);
    if (num_books < 0) {
        fl_message("Failed to load books: %s", err);
        free(err);
        return;
    } else {
        this->books_count = num_books;
        rows(num_books);
        row_header(0);
        row_height_all(30);
        row_resize(1);
        cols(4);
        col_header(1);
        col_width_all(200);
        col_resize(1);
    }
}

void BooksTable::clear_books() {
    if (books != nullptr) {
        for (size_t i = 0; i < books_count; ++i) {
            free(books[i].isbn);
            free(books[i].name);
            free(books[i].author);
            free(books[i].catalog);
        }
        free(books);
        books = nullptr;
    }
}

void new_book_cb(Fl_Widget*, void* m) {
    char isbn[81];
    char bookname[81];
    char author[81];
    char catalog[81];
    auto main_window = reinterpret_cast<MainWindow *>(m);
    char const *input_text;
    {
        input_text = fl_input("ISBN code");
        if (input_text == nullptr) {
            return;
        } else if (strlen(input_text) > 80) {
            fl_message("ISBN code too long!");
            return;
        }
        strcpy(isbn, input_text);
        input_text = fl_input("Book name");
        if (input_text == nullptr) {
            return;
        } else if (strlen(input_text) > 80) {
            fl_message("Book name too long!");
            return;
        }
        strcpy(bookname, input_text);
        input_text = fl_input("Book author");
        if (input_text == nullptr) {
            return;
        } else if (strlen(input_text) > 80) {
            fl_message("Book author too long!");
            return;
        }
        strcpy(author, input_text);
        input_text = fl_input("Catalog name");
        if (input_text == nullptr) {
            return;
        } else if (strlen(input_text) > 80) {
            fl_message("Catalog name too long!");
            return;
        }
        strcpy(catalog, input_text);
    }
    {
        char* err;
        if (!database_add_book(main_window->database_handle, isbn, bookname, author, catalog, &err)) {
            fl_message("Failed to add book %s: %s", bookname, err);
            free(err);
        }
    }
    main_window->user_panel->table->populate();
}

void delete_book_cb(Fl_Widget*, void* m) {
    auto main_window = reinterpret_cast<MainWindow*>(m);
    char const* bookname = fl_input("Book name to delete");
    if (bookname == nullptr) {
        return;
    } else {
        char* err;
        if (!database_delete_book(main_window->database_handle, bookname, &err)) {
            fl_message("Failed to delete book %s: %s", bookname, err);
            free(err);
        }
        main_window->user_panel->table->populate();
    }
}

RestoreBooksTable::RestoreBooksTable(int x, int y, MainWindow *m): Fl_Table(x, y, 700, 460) {
    main_window = m;
    books_count = 0;
    books = nullptr;
    end();
}

RestoreBooksTable::~RestoreBooksTable() {
    clear_books();
}

void RestoreBooksTable::DrawHeader(char const* s, int X, int Y, int W, int H) {
    fl_push_clip(X, Y, W, H);
    fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, row_header_color());
    fl_color(FL_BLACK);
    fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
    fl_pop_clip();
}

void RestoreBooksTable::DrawData(char const* s, int X, int Y, int W, int H) {
    fl_push_clip(X, Y, W, H);
    fl_color(FL_WHITE);
    fl_rectf(X, Y, W, H);
    fl_color(FL_GRAY0);
    fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
    fl_color(color());
    fl_rect(X, Y, W, H);
    fl_pop_clip();
}

void RestoreBooksTable::draw_cell(TableContext context, int ROW, int COL, int X, int Y, int W, int H) {
    switch (context) {
        case CONTEXT_STARTPAGE:
            fl_font(FL_HELVETICA, 16);
            return;
        case CONTEXT_COL_HEADER:
            char const* header_name;
            if (COL == 0) {
                header_name = "ISBN";
            } else if (COL == 1) {
                header_name = "Name";
            } else if (COL == 2) {
                header_name = "Author";
            } else if (COL == 3) {
                header_name = "Catalog";
            } else {
                header_name = "error";
            }
            DrawHeader(header_name, X, Y, W, H);
            return;
        case CONTEXT_CELL:
            char const* data;
            if (COL == 0) {
                data = books[ROW].isbn;
            } else if (COL == 1) {
                data = books[ROW].name;
            } else if (COL == 2) {
                data = books[ROW].author;
            } else if (COL == 3) {
                data = books[ROW].catalog;
            } else {
                data = "error";
            }
            DrawData(data, X, Y, W, H);
            return;
        default:
            return;
    }
}

void RestoreBooksTable::populate() {
    char* err;
    clear_books();
    ptrdiff_t num_books = database_get_books(main_window->database_handle, true, &books, &err);
    if (num_books < 0) {
        fl_message("Failed to load books: %s", err);
        free(err);
        return;
    } else {
        this->books_count = num_books;
        rows(num_books);
        row_header(0);
        row_height_all(30);
        row_resize(1);
        cols(4);
        col_header(1);
        col_width_all(200);
        col_resize(1);
    }
}

void RestoreBooksTable::clear_books() {
    if (books != nullptr) {
        for (size_t i = 0; i < books_count; ++i) {
            free(books[i].isbn);
            free(books[i].name);
            free(books[i].author);
            free(books[i].catalog);
        }
        free(books);
        books = nullptr;
    }
}

void restore_books_button_cb(Fl_Widget*, void* m) {
    auto main_window = reinterpret_cast<MainWindow*>(m);
    main_window->user_panel->table->hide();
    main_window->user_panel->restore_books_button->hide();
    main_window->user_panel->delete_book_button->hide();
    main_window->user_panel->new_book_button->hide();
    main_window->user_panel->restore_table->show();
    main_window->user_panel->restore_table->populate();
    main_window->user_panel->go_back_button->show();
    main_window->user_panel->restore_book_button->show();
}

void go_back_button_cb(Fl_Widget*, void* m) {
    auto main_window = reinterpret_cast<MainWindow*>(m);
    main_window->user_panel->show();
    main_window->user_panel->table->populate();
}

void restore_book_button_cb(Fl_Widget*, void* m) {
    auto main_window = reinterpret_cast<MainWindow*>(m);
    char const* bookname = fl_input("Book name to restore");
    if (bookname == nullptr) {
        return;
    } else {
        char* err;
        if (!database_restore_book(main_window->database_handle, bookname, &err)) {
            fl_message("Failed to restore book %s: %s", bookname, err);
            free(err);
        }
        main_window->user_panel->restore_table->populate();
    }
}
