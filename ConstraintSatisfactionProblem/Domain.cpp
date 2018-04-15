#include "stdafx.h"
#include "Domain.h"


Domain::Domain() {
}

Domain::Domain(int size) {
	setDomainSize(size);
	domain = new int[domainSize];

	//fill the domain by values (1...domainSize)
	for (int i = 0; i < domainSize; i++) {
		domain[i] = i + 1;
	}

}



Domain::~Domain() {
}

void Domain::setDomainSize(int size) {
	domainSize = size;
}

void Domain::setDomain(int * domain) {
}

int *Domain::getDomain() {
	return domain;
}

void Domain::upgradeDomain(int i, int value) {
	domain[i] = value;
}

bool Domain::domainNotEmpty() {
	bool isNotEmpty = false;
	for (int i = 0; i < domainSize; i++) {
		if (domain[i] != 0) {
			isNotEmpty = true;
		}
	}
	return isNotEmpty;
}

void Domain::showDomain() {
	cout << "[";
	for (int i = 0; i < domainSize - 1; i++) {
		cout << domain[i] << ",  ";
	}
	cout << domain[domainSize - 1] << "]" << endl;
}
