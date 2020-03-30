#pragma once
#include <ostream>
#include "util/enum.hpp"

#define DISEASE_ENUM(DO) \
	DO(Acne) \
	DO(Allergy) \
	DO(Alzheimer) \
	DO(Anorexia) \
	DO(Asthma) \
	DO(Autism) \
	DO(Bedwetting) \
	DO(BipolarDisorder) \
	DO(BoneCancer) \
	DO(BrainCancer) \
	DO(BreastCancer) \
	DO(Cancer) \
	DO(Coronavirus) \
	DO(HeartFailure) \
	DO(Dehydration) \
	DO(Depression) \
	DO(Diarrhea) \
	DO(DownSyndrome) \
	DO(DrugAbuse) \
	DO(Dermatisis) \
	DO(Epilepsy) \
	DO(Flu) \
	DO(Gonorrhea) \
	DO(Headache) \
	DO(Deafness) \
	DO(Hemorrhage) \
	DO(Hepatisis) \
	DO(AIDS) \
	DO(HIV) \
	DO(Hyperglycemia) \
	DO(Hypertension) \
	DO(Infertility) \
	DO(Malaria) \
	DO(MemoryLoss) \
	DO(Migraine) \
	DO(NailBiting) \
	DO(NeckPain) \
	DO(Osteoporosis) \
	DO(OvarianCancer) \
	DO(PanicAttack) \
	DO(Phobia) \
	DO(Pneumonia) \
	DO(PretermBirth) \
	DO(Schizophrenia) \
	DO(SkinCancer) \
	DO(SkinRash) \
	DO(SleepDisorder) \
	DO(Syphilis) \
	DO(Tuberculosis) \
	DO(VaricoseVein)

enum Disease {
	DISEASE_ENUM(UTIL_MAKE_ENUM)
};

const char* const DiseaseNames[] = {
	DISEASE_ENUM(UTIL_ENUM_MAKE_STRING)
};

std::ostream& operator<< (std::ostream &o, Disease d);
