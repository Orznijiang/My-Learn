#pragma once
#include <iostream>

class ABC {
private:
	char* label;
	int rating;
public:
	ABC(const char* l = "null", int r = 0);
	ABC(const ABC& rs);
	virtual ~ABC() { delete[] label; }
	virtual void View() const;
	ABC& operator=(const ABC& rs);
};

class baseDMA : public ABC{
private:
public:
	baseDMA(const char* l = "null", int r = 0);
	baseDMA(const baseDMA& rs);
	void View() const override;
};

class lacksDMA :public ABC {
private:
	enum { COL_LEN = 40 };
	char color[COL_LEN];
public:
	lacksDMA(const char* c = "blank", const char* l = "null", int r = 0);
	lacksDMA(const char* c, const baseDMA& rs);
	void View() const override;
};

class hasDMA :public ABC {
private:
	char* style;
public:
	hasDMA(const char* s = "none", const char* l = "null", int r = 0);
	hasDMA(const char* s, const baseDMA& rs);
	hasDMA(const hasDMA& hs);
	~hasDMA();
	hasDMA& operator=(const hasDMA& rs);
	void View() const override;
};