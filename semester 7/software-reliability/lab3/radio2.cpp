#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

class RadiostationRenamer;
class Radiostation {
public:
    Radiostation(char const* name, double frequency): frequency(frequency) { strncpy(this->name, name, 60); }
    friend RadiostationRenamer;
    friend std::ostream& operator<< (std::ostream&, const Radiostation&);
private:
    char name[60]{}; double frequency;
};

std::ostream& operator<< (std::ostream& o, const Radiostation& r) {
    o << r.name << ": " << r.frequency;
    return o;
}

static bool double_cmp(double a, double b) {
    const double eps = 1e-9;
    return fabs(a - b) < eps;
}

class RadiostationRenamer {
public:
    template<typename Iter>
    static void rename(Iter first, Iter last, char const* name, double frequency) {
        for (; first < last; ++first) {
            if (double_cmp(first->frequency, frequency)) {
                strncpy(first->name, name, 60);
            }
        }
    }
};

int main() {
    std::vector<Radiostation> radiostations;
    radiostations.emplace_back("Станция 1", 10);
    radiostations.emplace_back("Станция 2", 15);
    radiostations.emplace_back("Погода", 25);
    radiostations.emplace_back("Вести ФМ", 35);
    radiostations.emplace_back("Европа Плюс", 40);
    radiostations.emplace_back("Эхо Москвы", 45);
    std::cout << radiostations[3] << std::endl;
    RadiostationRenamer::rename(radiostations.begin(), radiostations.end(), "Новости", 35);
    std::cout << radiostations[3] << std::endl;
}
