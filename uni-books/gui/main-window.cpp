#include "uni-books.hpp"

static void close_database_handle(db** database) {
    if (*database != nullptr) {
        database_close(*database);
        *database = nullptr;
    }
}

MainWindow::MainWindow(int w, int h, char const* t): Fl_Double_Window(w, h, t) {
    database_handle = nullptr;
    menu_bar = new Fl_Menu_Bar(0, 0, w, 25);
    menu_bar->add("&File/&New", "^n", menu_file_new_cb, this);
    menu_bar->add("&File/&Open", "^o", menu_file_open_cb, this);
    menu_bar->add("&File/&Close", "^w", menu_file_close_cb, this);
    menu_bar->add("&File/&Quit", "^q", menu_file_quit_cb, this);
    menu_bar->add("&Help/&About", "^/", menu_help_about_cb, this);
    login_widget = new LoginWidget(200, 200, this);
    login_widget->hide();
    admin_panel = new AdminPanel(50, 50, this);
    admin_panel->hide();
    user_panel = new UserPanel(50, 50, this);
    user_panel->hide();
}

MainWindow::~MainWindow() {
    delete menu_bar;
    delete login_widget;
    delete admin_panel;
    delete user_panel;
    close_database_handle(&database_handle);
}

void menu_file_new_cb(Fl_Widget*, void* m) {
    auto* main_window = reinterpret_cast<MainWindow*>(m);
    Fl_Native_File_Chooser file_chooser;
    file_chooser.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
    file_chooser.preset_file("library.db");
    if (file_chooser.show() != 0) {
        return;
    }
    char const* picked = file_chooser.filename();
    char const* admin_password;
    ask_for_password:
    admin_password = fl_input("Admin password");
    if (admin_password == nullptr) {
        return;
    }
    if (strlen(admin_password) < 8) {
        fl_message("Admin password should have at least 8 characters");
        goto ask_for_password;
    }
    char* err;
    if (!database_new(picked, &err, admin_password)) {
        fl_message("%s", err);
    } else {
        fl_message("Created database %s", picked);
    }
    main_window->database_handle = database_open(picked, &err);
    if (main_window->database_handle == nullptr) {
        fl_message("Failed to open database: %s", err);
        free(err);
    }
    main_window->login_widget->show();
}

void menu_file_open_cb(Fl_Widget* w, void* m) {
    auto* main_window = reinterpret_cast<MainWindow*>(m);
    menu_file_close_cb(w, m);
    Fl_Native_File_Chooser file_chooser;
    file_chooser.type(Fl_Native_File_Chooser::BROWSE_FILE);
    if (file_chooser.show() != 0) {
        return;
    }
    char const* picked = file_chooser.filename();
    char* err;
    main_window->database_handle = database_open(picked, &err);
    if (main_window->database_handle == nullptr) {
        fl_message("Failed to open database: %s", err);
        free(err);
    }
    main_window->login_widget->username_input->value("");
    main_window->login_widget->password_input->value("");
    main_window->login_widget->show();
}

void menu_file_close_cb(Fl_Widget*, void* m) {
    auto* main_window = reinterpret_cast<MainWindow*>(m);
    close_database_handle(&main_window->database_handle);
    main_window->login_widget->hide();
    main_window->admin_panel->hide();
    main_window->user_panel->hide();
}

void menu_file_quit_cb(Fl_Widget* w, void* m) {
    menu_file_close_cb(w, m);
    exit(EXIT_SUCCESS);
}

void menu_help_about_cb(Fl_Widget*, void*) {
    fl_message("There is no help");
}
