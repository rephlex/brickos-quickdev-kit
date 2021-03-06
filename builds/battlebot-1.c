//
//
// DESIGN SPECS:
//
// FAHRWERK LINKS:  MOTOR A
// FAHRWERK RECHTS: MOTOR C
//
// Active Light SENSOR AN PORT 2
//

#include <conio.h>
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
// FLO/PASCAL SETUP: AL auf 2
#define LIGHTSENS       SENSOR_2

// ------------------------------------------------------------------------------------------------ FAHWERKSKONSTANTE
// flo / pascal 15
// mischa/felix 15
const signed int ms_per_deg = 15;

// flo/pascal 37
// mischa/felix 40
// Funktion zum ermitteln heißt debugLight
const signed int map_darkwarn = 40;



void wait(int duration);
void moveForward(int duration);
void moveBackward(int duration);
void moveStop();
void moveRotate(int deg);

void battle_BorderHit();

void displayLaufschrift(char* from);
void debugLight();
void debugBeep();

static wakeup_t border_found(wakeup_t data);



int main(int argc, char **argv) {

	ds_active(&LIGHTSENS);
	srandom(LIGHT(LIGHTSENS));

while (1==1) {
	moveForward(0);

	wait_event(border_found,map_darkwarn);

	battle_BorderHit();

}

	return 0;

//engineTest();
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



void battle_BorderHit() {

	moveStop();
	moveBackward(1000);

	int i; int j;
	i = 1000; j=1000;	//stupid init values, must be
				//out of bounds for the while loop below

	while ((j < 120) || (j > 240)) {
		i = random();
		j = (unsigned int)i;
	}


	//linksrum
	// 120 bis 240
	//rechtsrum
	// -120 bis -240

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

	lcd_unsigned(LIGHT(LIGHTSENS));
	curval = LIGHT(LIGHTSENS);
	if (curval <= map_darkwarn) {
		debugBeep();
	}

	wait(100);
	

}


void debugBeep() {
dsound_set_duration(40);

	dsound_play(devil);

}

static wakeup_t border_found(wakeup_t data) {
	return LIGHT(LIGHTSENS) < (unsigned short)data;
}




