#pragma once

class Plorg
{
private:
	const static int MAX = 20;
	char name[MAX];
	int ci;
public:
	Plorg(const char* name = "Plorga", int ci = 50);
	void setCI(int ci);
	void report() const;
};