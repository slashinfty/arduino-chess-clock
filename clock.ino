#include <TM1637.h>

int minus5 = 2;
int minus1 = 3;
int enter = 4;
int plus1 = 5;
int plus5 = 6
int player2 = 7;
int player1 = 8;
int CLK2 = 9;
int DIO2 = 10;
int CLK1 = 11;
int DIO1 = 12;

TM1637 TM1(CLK1, DIO1);
TM1637 TM2(CLK2, DIO2);

int turn = 0;
int set = 0;
unsigned long p1time = 600000;
unsigned long p2time = 600000;
unsigned long p1bonus = 0;
unsigned long p2bonus = 0;
unsigned long timeStart = 0;
unsigned long turnStart = 0;

void display(TM1637 tm, unsigned long ms, bool point = true) {
	int sec = ms / 1000;
	if (point) {
		tm.point(1);
		int min = sec / 60;
		if (min != 0) {
			tm.display(1, min % 10);
			tm.display(0, min / 10 % 10);
		}
		tm.display(2, sec / 10 % 10);
	}
	else {
		if (sec / 10 % 10 != 0) {
			tm.display(2, sec / 10 % 10);
		}
	}
	tm.display(3, sec % 10);
}

void adjust(int opt, unsigned long val) {
	switch (opt) {
		case 0:
			p1time += val * 60000;
			display(TM1, p1time);
			break;
		case 1:
			p1time += val * 1000;
			display(TM1, p1time);
			break;
		case 2:
			p2time += val * 60000;
			display(TM2, p2time);
			break;
		case 3:
			p2time += val * 1000;
			display(TM2, p2time);
			break;
		case 4:
			p1bonus += val * 1000;
			display(TM1, p1bonus, false);
			break;
		case 5:
			p2bonus += val * 1000;
			display(TM2, p2bonus, false);
			break;
	}
}

void turn(int player) {
	
}

void setup() {
	TM1.init();
	TM1.set(2);
	display(TM1, p1time);
	TM2.init();
	TM2.set(2);
	display(TM2, p2time);

	pinMode(minus5, INPUT);
	pinMode(minus1, INPUT);
	pinMode(enter, INPUT);
	pinMode(plus1, INPUT);
	pinMode(plus5, INPUT);
	pinMode(player1, INPUT);
	pinMode(player2, INPUT);
}

void loop() {
	if (turn == 0) {
		if (digitalRead(plus5) == HIGH) {
			adjust(set, 5);
		}
		else if (digitalRead(plus1) == HIGH) {
			adjust(set, 1);
		}
		else if (digitalRead(minus1) == HIGH) {
			adjust(set, -1);		
		}
		else if (digitalRead(minus5) == HIGH) {
			adjust(set, -5);
		}
		else if (digitalRead(enter) == HIGH) {
			set = (set + 1) % 6;
			if (set == 4) {
				display(TM1, p1bonus, false);
				display(TM2, p2bonus, false);
			}
			else if (set == 0) {
				display(TM1, p1time);
				display(TM2, p2time);
			}
		}
		else if (digitalRead(player1) == HIGH) {
			if (set >= 3) {
				display(TM1, p1time);
				display(TM2, p2time);
			}
			turn = 2;
			timeStart = p2time;
			turnStart = millis();
		}
		else if (digitalRead(player2) == HIGH) {
			if (set >= 3) {
				display(TM1, p1time);
				display(TM2, p2time);
			}
			turn = 1;
			timeStart = p1time;
			turnStart = millis();
		}
	delay(100);
	}
	else {
		while (p1time > 0 && p2time > 0) {
			unsigned long now = millis();
			unsigned long timeSpent = now - turnStart;
			if (turn == 1) {
				p1time = (timeSpent > timeStart) ? 0 : timeStart - timeSpent;
				display(TM1, p1time);
				if (digitalRead(player1) == HIGH) {
					p1time += p1bonus;
					turn = 2;
					timeStart = p2time;
					turnStart = millis();
				}
			}
			else {
				p2time = (timeSpent > timeStart) ? 0 : timeStart - timeSpent;
				display(TM2, p2time);
				if (digitalRead(player2) == HIGH) {
					p2time += p2bonus;
					turn = 1;
					timeStart = p1time;
					turnStart = millis();
				}
			}
		}
		exit(0);
	}
}
