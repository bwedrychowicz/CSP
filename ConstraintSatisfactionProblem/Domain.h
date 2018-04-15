#pragma once
#include <iostream>
#include <string>

using namespace std;

class Domain {
public:

	int *domain;
	int domainSize;

	Domain();
	Domain(int size);
	~Domain();

	void setDomainSize(int size);
	void setDomain(int *domain);
	int *getDomain();
	void upgradeDomain(int i, int value);

	bool domainNotEmpty();
	void showDomain();

};

