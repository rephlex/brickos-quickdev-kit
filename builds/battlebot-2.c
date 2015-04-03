//
//
// DESIGN SPECS:
//
// FAHRWERK LINKS:  MOTOR A
// FAHRWERK RECHTS: MOTOR C
//
// Active Light SENSOR AN PORTS 1 UND 3
// Touch Sensor AN PORT 2
//

#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dmotor.h>
#include <dsound.h>
#include <dsensor.h>
#include <string.h>


static const note_t devil[] = { 
  { PITCH_G4, QUARTER },
  { PITCH_END, 0 }
};


// ------------------------------------------------------------------------------------------------ SENSOR SETUP
// SETUP: AL links auf 1
#define LIGHTSENSL       SENSOR_1
// SETUP: AL rechts auf 3
#define LIGHTSENSR       SENSOR_3

// SETUP: TOUCH auf 2
#define TOUCHSENS       SENSOR_2

// ------------------------------------------------------------------------------------------------ FAHWERKSKONSTANTE
// flo / pascal 12
// mischa/felix 19
const signed int ms_per_deg = 19;

// flo/pascal 38
// mischa/felix 38
// Funktion zum ermitteln heißt debugLight
const signed int map_darkwarn = 38;



void wait(int duration);
void moveForward(int duration);
void moveBackward(int duration);
void moveStop();
void moveRotate(int deg);

void battle_BorderHitL();
void battle_BorderHitR();

void displayLaufschrift(char* from);
void debugLight();
void debugTouch();
void debugBeep();

int check_light_l();
int check_light_r();
int check_colission();




int main(int argc, char **argv) {

	//turn on accessory engine
	motor_b_dir(fwd);
	motor_b_speed (255);



	ds_active(&LIGHTSENSL);
	wait(100);
	ds_active(&LIGHTSENSR);

	srandom(LIGHT(LIGHTSENSL));

	while (1==1) {

		moveForward(0);
	
		if (check_light_l()) { battle_BorderHitL(); }
		if (check_light_r()) { battle_BorderHitR(); }
		if (check_colission()) { moveRotate(180); }

	}

	return 0;


}



void wait(int duration) {
	delay(duration*10);
}










void moveForward(int duration) {
	
	motor_a_dir(fwd);
	motor_c_dir(fwd);

	motor_a_speed (255);
	motor_c_speed (255);

	if (duration > 0) {
		delay(duration*10);
		motor_a_dir(brake);
		motor_c_dir(brake);
	}

}

void moveBackward(int duration) {
	

	motor_a_dir(rev);
	motor_c_dir(rev);

	motor_a_speed (255);
	motor_c_speed (255);

	if (duration > 0) {
		delay(duration*10);
		motor_a_dir(brake);
		motor_c_dir(brake);
	}

}

void moveStop() {

	motor_a_dir(brake);
	motor_c_dir(brake);

}

void moveRotate(int deg) {

	motor_a_dir(brake);
	motor_c_dir(brake);
	motor_a_speed (255);
	motor_c_speed (255);


	if (deg == 0) return;

	if (deg > 0) {
		motor_a_dir(fwd);
		motor_c_dir(rev);
	}
	if (deg < 0) {
		motor_a_dir(rev);
		motor_c_dir(fwd);
	}

	wait(deg*ms_per_deg);

}



void battle_BorderHitL() {

	moveStop();
	moveBackward(500);

	int i;
	i = 1000;		//stupid init value, must be
				//out of bounds for the while loop below

	while ((i < 120) || (i > 240)) {
		i = random();
	}

	moveRotate(i);
}



void battle_BorderHitR() {

	moveStop();
	moveBackward(500);

	int i;
	i = 1000;		//stupid init value, must be
				//out of bounds for the while loop below

	while ((i < -240) || (i > -120)) {
		i = 0-random();
	}

	moveRotate(i);
}




void displayLaufschrift(char* from) {

	char to[7];
	int i;

	for (i = 0; i < strlen(from)-6; i++) {
		strcpy (to, from+i);
		to[7] = '\0';
		cputs(to);
		delay(3000);
		cls();
	}


}



void debugLight() {

	int curval;

	lcd_unsigned(LIGHT(LIGHTSENSL));
	curval = LIGHT(LIGHTSENSL);
	if (curval <= map_darkwarn) {
		debugBeep();
	}

	wait(100);
	

}


void debugBeep() {
dsound_set_duration(40);

	dsound_play(devil);

}

int check_light_l() {
	return LIGHT(LIGHTSENSL) < map_darkwarn;
}
int check_light_r() {
	return LIGHT(LIGHTSENSR) < map_darkwarn;
}

int check_colission() {
	return !(      TOUCH(TOUCHSENS) < 1);
}



