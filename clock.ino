#include <TM1637.h>

int CLK1 = 9;
int DIO1 = 10;
int CLK2 = 11;
int DIO2 = 12;

TM1637 tm1(CLK1, DIO1);
TM1637 tm2(CLK2, DIO2);

void setup() {
	tm1.init();
	tm1.set(2);
	tm2.init();
	tm2.set(2);
}

void loop() {

}

void display(TM1637 tm, long ms, bool point = true) {
	int sec = ms / 1000;
	if (point) {
		tm.point(1);
		int min = sec / 60;
		if (min != 0) {
			tm.display(1, min % 10);
			tm.display(0, min / 10 % 10);
		}
		tm.display(2, sec / 10 % 10);
	else {
		if (sec / 10 % 10 != 0) {
			tm.display(2, sec / 10 % 10);
		}
	}
	tm.display(3, sec % 10);
}
