#include "13-04-port.h"

int main04() {
	Port port1("a", "b", 3);
	Port port2(port1);
	Port port3;
	port3 = port2;
	port3 += 2;
	port3 -= 1;
	VintagePort vp1("a", "b", 3, "n", 1);
	VintagePort vp2(vp1);
	VintagePort vp3;
	vp3 = vp1;
	vp2 += 2;
	vp3 += 3;
	vp1 -= 1;
	
	port1.Show();
	port2.Show();
	port3.Show();
	cout << vp1 << vp2 << vp3;

	return 0;
}