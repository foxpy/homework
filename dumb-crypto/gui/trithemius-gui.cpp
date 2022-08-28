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
    Fl_Input* key;
};

void run(Fl_Widget*, void* dat) {
    auto* run_data = reinterpret_cast<struct run_data *>(dat);
    char const* input = run_data->input->value();
    char const* key = run_data->key->value();
    if (run_data->check_button->value() == 0) {
        char *encrypted = trithemius_cipher_encrypt(input, 8, 4, key);
        if (encrypted == nullptr) {
            return;
        }
        run_data->output->value(encrypted);
        free(encrypted);
    } else {
        char* decrypted = trithemius_cipher_decrypt(input, 8, 4, key);
        if (decrypted == nullptr) {
            return;
        }
        run_data->output->value(decrypted);
        free(decrypted);
    }
}

int main(int argc, char *argv[]) {
    auto* w = new Fl_Window(800, 300, "Trithemius GUI");
    run_data run_data{
            new Fl_Input(80, 10, 660, 40, "Ввод:"),
            new Fl_Output(80, 70, 660, 40, "Вывод:"),
            new Fl_Check_Button(20, 120, 160, 20, "Расшифровать"),
            new Fl_Input(240, 120, 200, 20, "Ключ:")
    };
    auto* run_button = new Fl_Button(680, 250, 100, 30, "Запустить");
    run_button->callback(run, &run_data);
    w->end();
    w->show(argc, argv);
    return Fl::run();
}
