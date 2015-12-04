/*
CITY RUSH - CUSTOM MIDI CONTROLLER
Developed by Ícaro Ferre
Last modified on 06/11/2015 - 01:43PM

Version: 1.0

4 knobs + 4 pads + 3 switches + 6 leds

 */

#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int knobs_jitter_amount = 7;
int controller_midi_channel = 10;

//Knob 1
int knob1 = A0;
int knob1_new = 0;
int knob1_old = 0;
int knob1_midi = 0;

//Knob 2
int knob2 = A1;
int knob2_new = 0;
int knob2_old = 0;
int knob2_midi = 0;

//Knob 3
int knob3 = A2;
int knob3_new = 0;
int knob3_old = 0;
int knob3_midi = 0;

//Knob 4
int knob4 = A3;
int knob4_new = 0;
int knob4_old = 0;
int knob4_midi = 0;

//Button 1
const int button1 = 4;
int button1_new = LOW;
int button1_old = LOW;


//Button 2
const int button2 = 7;
int button2_new = LOW;
int button2_old = LOW;


//Button 3
const int button3 = 12;
int button3_new = LOW;
int button3_old = LOW;


//Button 4
const  int button4 = 8;
int button4_new = LOW;
int button4_old = LOW;

//Switch 1
const  int switch1 = 9;
int switch1_new = LOW;
int switch1_old = LOW;

//LED 1
const int led1 = 3;
int led1_pwm = 0;

//LED 2
const int led2 = 6;
int led2_pwm = 0;


//LED 3
const int led3 = 5;
int led3_pwm = 0;



void HandleControlChange (byte channel, byte number, byte value) {
  if (channel == 14) {
    if (number == 1) {
      led1_pwm = value * 2;
      analogWrite(led1, led1_pwm);

    }
    if (number == 2) {
      led2_pwm = value * 2;
      analogWrite(led2, led2_pwm);
    }
    if (number == 3) {
      led3_pwm = value * 2;
      analogWrite(led3, led3_pwm);

    }
  }

}


void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  MIDI.setHandleControlChange (HandleControlChange);



}

void loop() {

  MIDI.read();

  // KNOB 1
  knob1_new = analogRead(knob1);
  if ((abs(knob1_new - knob1_old) > knobs_jitter_amount)) {
    knob1_midi = map(knob1_new, 1023, 0, 0, 127);
    MIDI.sendControlChange(1, knob1_midi, controller_midi_channel);
    //led1_pwm = knob1_midi*2;
    //analogWrite(led1, led1_pwm);
    knob1_old = knob1_new;
  }

  // KNOB 2
  knob2_new = analogRead(knob2);
  if ((abs(knob2_new - knob2_old) > knobs_jitter_amount)) {
    knob2_midi = map(knob2_new, 1023, 0, 0, 127);
    MIDI.sendControlChange(2, knob2_midi, controller_midi_channel);
    //led2_pwm = knob2_midi*2;
    //analogWrite(led2, led2_pwm);
    knob2_old = knob2_new;
  }

  // KNOB 3
  knob3_new = analogRead(knob3);
  if ((abs(knob3_new - knob3_old) > knobs_jitter_amount)) {
    knob3_midi = map(knob3_new, 1023, 0, 0, 127);
    MIDI.sendControlChange(3, knob3_midi, controller_midi_channel);
    knob3_old = knob3_new;
  }

  // KNOB 4
  knob4_new = analogRead(knob4);
  if ((abs(knob4_new - knob4_old) > knobs_jitter_amount)) {
    knob4_midi = map(knob4_new, 1023, 0, 0, 127);
    MIDI.sendControlChange(4, knob4_midi, controller_midi_channel);
    knob4_old = knob4_new;
  }

  // BUTTON 1
  button1_new = digitalRead(button1);
  if (button1_new != button1_old) {
    if (button1_new == HIGH) {
      MIDI.sendNoteOn(60, 127, controller_midi_channel);
    }
    if (button1_new == LOW) {
      MIDI.sendNoteOn(60, 0, controller_midi_channel);
    }
    button1_old = button1_new;
  }

  // BUTTON 2
  button2_new = digitalRead(button2);
  if (button2_new != button2_old) {
    if (button2_new == HIGH) {
      MIDI.sendNoteOn(61, 127, controller_midi_channel);
    }
    if (button2_new == LOW) {
      MIDI.sendNoteOn(61, 0, controller_midi_channel);
    }
    button2_old = button2_new;
  }

  // BUTTON 3
  button3_new = digitalRead(button3);
  if (button3_new != button3_old) {
    if (button3_new == HIGH) {
      MIDI.sendNoteOn(62, 127, controller_midi_channel);
    }
    if (button3_new == LOW) {
      MIDI.sendNoteOn(62, 0, controller_midi_channel);
    }
    button3_old = button3_new;
  }


  // BUTTON 4
  button4_new = digitalRead(button4);
  if (button4_new != button4_old) {
    if (button4_new == HIGH) {
      MIDI.sendNoteOn(63, 127, controller_midi_channel);
    }
    if (button4_new == LOW) {
      MIDI.sendNoteOn(63, 0, controller_midi_channel);
    }
    button4_old = button4_new;
  }

  
  // SWITCH 1
  switch1_new = digitalRead(switch1);
  if (switch1_new != switch1_old) {
    if (switch1_new == HIGH) {
      MIDI.sendControlChange(10, 127, controller_midi_channel);
    }
    if (switch1_new == LOW) {
      MIDI.sendControlChange(10, 0, controller_midi_channel);
    }
    switch1_old = switch1_new;
  }





}
