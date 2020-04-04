#pragma once
#include <ostream>

enum Disease {
	Asthma,
	Cancer,
	Diarrhea,
	Flu,
	Headache,
	Hepatisis,
	NeckPain,
};

const char* const DiseaseNames[] = {
	"Asthma",
	"Cancer",
	"Diarrhea",
	"Flu",
	"Headache",
	"Hepatisis",
	"NeckPain",
};

std::ostream& operator<< (std::ostream &o, Disease d);
