//
//
// DESIGN SPECS:
//
// FAHRWERK LINKS:  MOTOR A
// FAHRWERK RECHTS: MOTOR C
//
//

#include <conio.h>
#include <unistd.h>
#include <dmotor.h>
#include <dsound.h>
#include <dsensor.h>
#include <string.h>





// ------------------------------------------------------------------------------------------------ SENSOR SETUP
// FLO/PASCAL SETUP: AL auf 2
#define LIGHTSENS       SENSOR_2
#define DARK_THRESH     0x40
#define BRIGHT_THRESH   0x48


// ------------------------------------------------------------------------------------------------ FAHWERKSKONSTANTE
// flo / pascal 17
// mischa/felix 15
const signed int ms_per_deg = 17;




void engineTest();
void wait(int duration);
void moveForward(int duration);
void moveBackward(int duration);
void moveStop();
void moveRotate(int deg);
void displayLaufschrift(char* from);
void debugLight();
static wakeup_t bright_found(wakeup_t data);
static wakeup_t dark_found(wakeup_t data);




int main(int argc, char **argv) {

while (1==1) { moveForward(0); }

}



void engineTest() {

		moveForward(5000);

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
	motor_a_dir(brake);
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
	int divisor = 100;
	char value[5];
	char lastdigit = 0;
	int i;
	char temp = 0;

	value[4] = 0;
	cls();

	for(i = 0;i < 4;i++)
	{
		//value[i] = ((LIGHT(LIGHTSENS)-((divisor+10)*lastdigit) / divisor)) + 0x30;
		temp = LIGHT(LIGHTSENS) / (divisor * 10);
		temp *= (divisor * 10);
				
		value[i] = (LIGHT(LIGHTSENS)-temp) / divisor;
		divisor /= 10;	
	}

	cputs(value);

}




static wakeup_t dark_found(wakeup_t data) {
	return LIGHT(LIGHTSENS)<(unsigned short)data;
}
static wakeup_t bright_found(wakeup_t data) {
	return LIGHT(LIGHTSENS)>(unsigned short)data;
}

