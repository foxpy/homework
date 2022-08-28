#include "uni-books.hpp"

LoginWidget::LoginWidget(int x, int y, MainWindow* m): Fl_Widget(x, y, 400, 200) {
    main_window = m;
    box = new Fl_Box(x, y, 400, 200);
    box->box(FL_UP_BOX);
    label = new Fl_Box(x+20, y+20, 360, 20, "Log in");
    username_input = new Fl_Input(x+80, y+40, 300, 40, "Username");
    password_input = new Fl_Secret_Input(x+80, y+100, 300, 40, "Password");
    authorize_button = new Fl_Button(x+150, y+150, 100, 40, "Authorize");
    authorize_button->callback(authorize_cb, this);
}

LoginWidget::~LoginWidget() {
    delete box;
    delete label;
    delete username_input;
    delete password_input;
    delete authorize_button;
}

void LoginWidget::draw() {}

void LoginWidget::hide() {
    box->hide();
    label->hide();
    username_input->hide();
    password_input->hide();
    authorize_button->hide();
}

void LoginWidget::show() {
    box->show();
    label->show();
    username_input->show();
    password_input->show();
    authorize_button->show();
}

void authorize_cb(Fl_Widget*, void* l) {
    auto login_widget = reinterpret_cast<LoginWidget*>(l);
    char const* username = login_widget->username_input->value();
    char const* password = login_widget->password_input->value();
    if (strlen(username) > 0 && strlen(password) > 0) {
        char* err = nullptr;
        db_user_type type = database_check_credentials(
                login_widget->main_window->database_handle, username, password, &err);
        if (type == DATABASE_UNAUTHORIZED) {
            fl_message("Failed to authorize: %s", err);
            free(err);
        } else {
            login_widget->hide();
            if (type == DATABASE_ADMIN) {
                fl_message("Successfully authorized as admin");
                login_widget->main_window->admin_panel->show();
                login_widget->main_window->admin_panel->table->populate();
            } else {
                fl_message("Successfully authorized as user");
                login_widget->main_window->user_panel->show();
                login_widget->main_window->user_panel->table->populate();
            }
        }
    }
}
