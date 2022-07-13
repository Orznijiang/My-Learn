#pragma once
#include "13-02-cd-dynamic.h"

class Classic_dynamic : public Cd_dynamic {
private:
	char *mainWork;
public:
	Classic_dynamic(const char* s1, const char* s2, const char* s3, int n, double x);
	Classic_dynamic(const Classic_dynamic&);
	Classic_dynamic();
	virtual ~Classic_dynamic();
	virtual void Report() const override;
	Classic_dynamic& operator=(const Classic_dynamic&);
};