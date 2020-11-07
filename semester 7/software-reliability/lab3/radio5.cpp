#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

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
        auto num_words = std::count(&rad.name[0], &rad.name[60], ' ') + 1;
        return num_words >= 2 && num_words <= 4;
    }
};

int main() {
    std::vector<Radiostation> radiostations;
    radiostations.emplace_back("VCPR", 120.5);
    radiostations.emplace_back("Wave 103", 122.5); // k
    radiostations.emplace_back("Espantoso", 124.5);
    radiostations.emplace_back("K-chat", 126.5);
    radiostations.emplace_back("V-rock", 128.5);
    radiostations.emplace_back("electro choc", 130.5); // k
    radiostations.emplace_back("INDEP- ENDENCE FM", 132.5); // k
    radiostations.emplace_back("SELF ACTUALIZATION FM", 134.5); // k
    radiostations.emplace_back("Liberty Rock Radio", 136.5); // k
    radiostations.emplace_back("We Know The Truth WKTT TALK RADIO", 138.5);
    auto num_stations = RadiostationCounter::count_radiostations(radiostations.cbegin(), radiostations.cend());
    std::cout << num_stations << std::endl;
}
