#pragma config(Sensor, S2,     light,          sensorLightActive)
#pragma config(Motor,  motorB,          rightMotor,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          leftMotor,     tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "steering.h"

task main() {
	//writeDebugStreamLine("Starting NXT");
	//steer(left);

//Kp = 10                               ! Initialize our three variables
//offset = 45
//Tp = 50
//Loop forever
//   LightValue = read light sensor     ! what is the current light reading?
//   error = LightValue - offset        ! calculate the error by subtracting the offset
//   Turn = Kp * error                  ! the "P term", how much we want to change the motors' power
//   powerA = Tp + Turn                 ! the power level for the A motor
//   powerC = Tp - Turn                 ! the power level for the C motor
//   MOTOR A direction=forward power=powerA ! issue the command with the new power level in a MOTOR block
//   MOTOR C direction=forward power=powerC ! same for the other motor but using the other power level
//end loop forever                      ! done with this loop, go back to the beginning and do it again

	int kp = 10;
	int offset = 45;
	int tp = 100;

	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;

	while (1) {
		int lightval = SensorValue(light);
		int error = lightval - offset;
		int turn = kp * error;

		int powerB = tp + turn;
		int powerC = tp - turn;

		motor[motorB] = powerB;
		motor[motorC] = powerC;
	}
}
