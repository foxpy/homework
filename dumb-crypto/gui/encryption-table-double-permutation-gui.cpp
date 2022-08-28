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
    Fl_Int_Input* h1;
    Fl_Int_Input* h2;
    Fl_Int_Input* h3;
    Fl_Int_Input* h4;
    Fl_Int_Input* v1;
    Fl_Int_Input* v2;
    Fl_Int_Input* v3;
    Fl_Int_Input* v4;
};

void run(Fl_Widget*, void* dat) {
    auto* run_data = reinterpret_cast<struct run_data *>(dat);
    char const* input = run_data->input->value();
    size_t horizontal_permutation[4];
    horizontal_permutation[0] = std::atoi(run_data->h1->value()) - 1;
    horizontal_permutation[1] = std::atoi(run_data->h2->value()) - 1;
    horizontal_permutation[2] = std::atoi(run_data->h3->value()) - 1;
    horizontal_permutation[3] = std::atoi(run_data->h4->value()) - 1;
    size_t vertical_permutation[4];
    vertical_permutation[0] = std::atoi(run_data->v1->value()) - 1;
    vertical_permutation[1] = std::atoi(run_data->v2->value()) - 1;
    vertical_permutation[2] = std::atoi(run_data->v3->value()) - 1;
    vertical_permutation[3] = std::atoi(run_data->v4->value()) - 1;
    if (run_data->check_button->value() == 0) {
        char* encrypted = encryption_table_double_permutation_encrypt(
                input, 4, horizontal_permutation, 4, vertical_permutation);
        if (encrypted == nullptr) {
            return;
        }
        run_data->output->value(encrypted);
        free(encrypted);
    } else {
        char* decrypted = encryption_table_double_permutation_decrypt(
                input, 4, horizontal_permutation, 4, vertical_permutation);
        if (decrypted == nullptr) {
            return;
        }
        run_data->output->value(decrypted);
        free(decrypted);
    }
}

int main(int argc, char *argv[]) {
    auto* w = new Fl_Window(800, 300, "Encryption Table Double Permutation GUI");
    run_data run_data{
            new Fl_Input(80, 10, 660, 40, "Ввод:"),
            new Fl_Output(80, 70, 660, 40, "Вывод:"),
            new Fl_Check_Button(20, 120, 160, 20, "Расшифровать"),
            new Fl_Int_Input(240, 120, 40, 20, "X:"),
            new Fl_Int_Input(280, 120, 40, 20),
            new Fl_Int_Input(320, 120, 40, 20),
            new Fl_Int_Input(360, 120, 40, 20),
            new Fl_Int_Input(420, 120, 40, 20, "Y:"),
            new Fl_Int_Input(460, 120, 40, 20),
            new Fl_Int_Input(500, 120, 40, 20),
            new Fl_Int_Input(540, 120, 40, 20),
    };
    auto* run_button = new Fl_Button(680, 250, 100, 30, "Запустить");
    run_button->callback(run, &run_data);
    w->end();
    w->show(argc, argv);
    return Fl::run();
}
