#pragma once
#include <string>
#include <cstddef>
#include <fstream>
#include <iterator>
#include <vector>

enum StorageClass: unsigned char {
	PatientClass,
	DoctorClass,
};

enum Severity: unsigned char {
	LowSeverity,
	MediumSeverity,
	HighSeverity,
	ExtremeSeverity,
};

struct Patient {
	char name[32];
	unsigned age;
	char disease[32];
	Severity severity;
};

struct Filesystem {
	Filesystem(const std::string &path);
	template<class Container> void read(std::back_insert_iterator<Container> inserter) {
		file.seekp(0);
		file.read(reinterpret_cast<char*>(&entries), sizeof(entries));
		Patient patient;
		for (std::size_t i = 0; i < entries; ++i) {
			file.read(reinterpret_cast<char*>(&patient), sizeof(patient));
			std::fill_n(inserter, 1, patient);
		}
	}
	template<class InputIter> void write(InputIter begin, InputIter end) {
		entries = std::distance(begin, end);
		file.seekp(0);
		file.write(reinterpret_cast<char*>(&entries), sizeof(entries));
		for (; begin != end; ++begin) {
			Patient patient = *begin;
			file.write(reinterpret_cast<char*>(&patient), sizeof(patient));
		}
	}
private:
	void open_and_create_if_not_exists(const std::string &path);
	std::fstream file;
	std::size_t entries;
};

struct Tui {
	Tui(std::vector<Patient> *patients);
	void run();
private:
	std::vector<Patient> *patients;
};
