#include "13-03-dma.h"
#include <iostream>

int main03() {
	using std::cout;
	using std::endl;

	ABC* abcs[5];

	baseDMA shirt("Portabelly", 8);
	abcs[0] = &shirt;
	lacksDMA ballon("red", "Blimpo", 4);
	abcs[1] = &ballon;
	hasDMA map("Mercator", "Buffalo Keys", 5);
	abcs[2] = &map;

	lacksDMA ballon2(ballon);
	abcs[3] = &ballon2;

	hasDMA map2;
	map2 = map;
	abcs[4] = &map2;

	for (int i = 0; i < 5; i++) {
		abcs[i]->View();
	}

	return 0;
}