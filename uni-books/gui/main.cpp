#include "uni-books.hpp"

int main() {
    MainWindow main_window(800, 600, "Library");
    main_window.end();
    main_window.show();
    return Fl::run();
}
