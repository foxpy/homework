#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <random>

class RadiostationCounter;
class Radiostation {
public:
    Radiostation(char const* name, double frequency): frequency(frequency) { strncpy(this->name, name, 60); }
    friend RadiostationCounter;
private:
    char name[60]{}; double frequency;
};

class RadiostationCounter {
public:
    template<typename Iter>
    static unsigned count_radiostations(Iter first, Iter last) {
        return std::count_if(first, last, is_valuable);
    }
private:
    static bool is_valuable(const Radiostation &rad) {
        return strstr(rad.name, "музыка") != nullptr;
    }
};

int main() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<> dis(80, 120.0);
    std::vector<Radiostation> radiostations;
    radiostations.emplace_back("Своя музыка", dis(gen));
    radiostations.emplace_back("Радио Звезда", dis(gen));
    radiostations.emplace_back("Вести FM", dis(gen));
    radiostations.emplace_back("музыка 107", dis(gen));
    radiostations.emplace_back("радио ENERGY", dis(gen));
    radiostations.emplace_back("Радио музыкальное", dis(gen));
    auto num_stations = RadiostationCounter::count_radiostations(radiostations.cbegin(), radiostations.cend());
    std::cout << num_stations << std::endl;
}
