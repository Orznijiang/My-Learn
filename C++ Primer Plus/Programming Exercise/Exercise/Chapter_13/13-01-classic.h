#pragma once
#include "13-01-cd.h"

class Classic : public Cd {
private:
	char mainWork[50];
public:
	Classic(const char* s1, const char* s2, const char* s3, int n, double x);
	Classic(const Classic&);
	Classic();
	virtual ~Classic();
	virtual void Report() const override;
	Classic& operator=(const Classic&);
};