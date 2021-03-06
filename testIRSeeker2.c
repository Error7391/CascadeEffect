#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S2,     colorR,         sensorNone)
#pragma config(Sensor, S3,     irSeekerL,      sensorI2CCustom)
#pragma config(Sensor, S4,     irSeekerR,      sensorI2CCustom)
#pragma config(Motor,  motorA,          hook,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorR,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    liftLow,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    liftHigh,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    shoulder,             tServoStandard)
#pragma config(Servo,  srvo_S1_C2_4,    elbow,                tServoStandard)
#pragma config(Servo,  srvo_S1_C2_5,    collector,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_6,    trapDoor,             tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * hitechnic-irseeker-v2.h provides an API for the HiTechnic IR Seeker V2.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 4.10 AND HIGHER

 * Xander Soldaat (xander_at_botbench.com)
 * Dick Swan
 * Gus Jansson
 * 04 October 2012
 * version 0.1
 */

#include "hitechnic-irseeker-v2.h"

// main task
task main ()
{
  displayCenteredTextLine(0, "HiTechnic");
  displayCenteredBigTextLine(1, "IR Seekr");
  displayCenteredTextLine(3, "Test 1");
  displayCenteredTextLine(5, "Press enter to");
  displayCenteredTextLine(6, "switch between");
  displayCenteredTextLine(7, "600 and 1200 Hz");
  sleep(2000);

  // Create struct to hold sensor data
  tHTIRS2 irSeeker_L;
  tHTIRS2 irSeeker_R;

  // Initialise and configure struct and port
  initSensor(&irSeeker_L, S3);
  initSensor(&irSeeker_R, S4);

  while(true)
  {
    // You can switch between the two different DSP modes by pressing the
    // orange enter button

    playSound(soundBeepBeep);
    while(bSoundActive)
    {}
    eraseDisplay();

    // display the current DSP mode
    //if (irSeeker.mode == DSP_1200)
    //  displayTextLine(0, "    DC 1200");
    //else
    //  displayTextLine(0, "    DC  600");

    while (true)
    {
      if (getXbuttonValue(xButtonEnter))
      {
        // "Enter" button has been pressed. Need to switch mode

        //irSeeker.mode = (irSeeker.mode == DSP_1200) ?  DSP_600 : DSP_1200;
        while(getXbuttonValue(xButtonEnter))
        {
          sleep(1);
        }
        break;
      }

      // Read the sensor data.
      readSensor(&irSeeker_L);
      readSensor(&irSeeker_R);
      //displayTextLine(1, "D:%4d %4d 3%d", irSeeker_L.acDirection, irSeeker_R.acDirection, irSeeker.enhDirection, irSeeker.enhStrength);
      displayTextLine(1, "D:%4d %4d 3%d 3%d", irSeeker_L.acDirection, irSeeker_R.acDirection, irSeeker_L.enhDirection, irSeeker_R.enhDirection);
      displayTextLine(2, "0:%d %d", irSeeker_L.acValues[0], irSeeker_R.acValues[0]);
      displayTextLine(3, "0:%d %d", irSeeker_L.acValues[1], irSeeker_R.acValues[1]);
      displayTextLine(4, "0:%d %d", irSeeker_L.acValues[2], irSeeker_R.acValues[2]);
      displayTextLine(5, "0:%d %d", irSeeker_L.acValues[3], irSeeker_R.acValues[3]);
      displayTextLine(6, "0:%d %d", irSeeker_L.acValues[4], irSeeker_R.acValues[4]);


 		}
  }
}
