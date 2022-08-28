#include <cstdlib>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Check_Button.H>

extern "C" {
#include "crypto.h"
}

struct run_data {
    Fl_Input* input;
    Fl_Output* output;
    Fl_Check_Button* check_button;
    Fl_Int_Input* x;
    Fl_Int_Input* y;
    Fl_Input* key;
};

void run(Fl_Widget*, void* dat) {
    auto* run_data = reinterpret_cast<struct run_data *>(dat);
    char const* input = run_data->input->value();
    size_t x = std::atoi(run_data->x->value());
    size_t y = std::atoi(run_data->y->value());
    char const* key = run_data->key->value();
    if (run_data->check_button->value() == 0) {
        char *encrypted = playfair_cipher_encrypt(input, x, y, key);
        if (encrypted == nullptr) {
            return;
        }
        run_data->output->value(encrypted);
        free(encrypted);
    } else {
        char* decrypted = playfair_cipher_decrypt(input, x, y, key);
        if (decrypted == nullptr) {
            return;
        }
        run_data->output->value(decrypted);
        free(decrypted);
    }
}

int main(int argc, char *argv[]) {
    auto* w = new Fl_Window(800, 300, "Playfair GUI");
    run_data run_data{
            new Fl_Input(80, 10, 660, 40, "Ввод:"),
            new Fl_Output(80, 70, 660, 40, "Вывод:"),
            new Fl_Check_Button(20, 120, 160, 20, "Расшифровать"),
            new Fl_Int_Input(240, 120, 40, 20, "x:"),
            new Fl_Int_Input(300, 120, 40, 20, "y:"),
            new Fl_Input(400, 120, 200, 20, "Ключ:")
    };
    auto* run_button = new Fl_Button(680, 250, 100, 30, "Запустить");
    run_button->callback(run, &run_data);
    w->end();
    w->show(argc, argv);
    return Fl::run();
}
