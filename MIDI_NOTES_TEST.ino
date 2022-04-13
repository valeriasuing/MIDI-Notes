//Demo for sending MIDI Notes Messages 
//Followed this tutorial: https://ask.video/article/audio-hardware/how-to-build-a-simple-diy-usb-midi-controller-using-teensy
//Bounce, fallingEdge and risingEdge were new concepts introduced by this tutorial 

#include <Bounce.h>

//number of push buttons for MIDI keyboard 
const int KEYBOARD_BUTTONS = 12;

//MIDI channel 
const int MIDI_CHAN = 1;

const int DEBOUNCE_TIME = 5;


//Bounce Object (deals with contact chatter) 
Bounce buttons[KEYBOARD_BUTTONS] = 
{
  Bounce (2, DEBOUNCE_TIME),
  Bounce (3, DEBOUNCE_TIME),
  Bounce (4, DEBOUNCE_TIME),
  Bounce (5, DEBOUNCE_TIME),
  Bounce (6, DEBOUNCE_TIME),
  Bounce (7, DEBOUNCE_TIME),
  Bounce (8, DEBOUNCE_TIME),
  Bounce (9, DEBOUNCE_TIME),
  Bounce (10, DEBOUNCE_TIME),
  Bounce (11, DEBOUNCE_TIME),
  Bounce (12, DEBOUNCE_TIME),
  Bounce (13, DEBOUNCE_TIME),
};

//Array that stores the exact note each button will need
  const int MIDI_NOTE_NUMS[KEYBOARD_BUTTONS] = {60,61,62,63,64,65,66,67,68,69,70,71};
//velocity 
  const int MIDI_NOTE_VELS[KEYBOARD_BUTTONS] = {110,110,110,110,110,110,110,110,110,110,110,110};
  

void setup() {
  //setting keyboard buttons as inputs with pullup resistors
  for (int i = 0; i < KEYBOARD_BUTTONS + 1; i++)
  {
    pinMode (i, INPUT_PULLUP);
  }

}

void loop() {
  //update buttons, no delays
  for (int i = 0; i < KEYBOARD_BUTTONS + 1; i++)
  {
    buttons[i].update();
  }

  //check status of buttons 
  for (int i = 0; i < KEYBOARD_BUTTONS; i++)
  {
    //Falling Edge - falling = high (not pressed - voltage from pullup resistor) to low (pressed - button connects pin to ground) 
    if (buttons[i].fallingEdge())
    {
      //send MIDI note
      usbMIDI.sendNoteOn(MIDI_NOTE_NUMS[i], 110, MIDI_CHAN);
    }
    //Rising = low (pressed) to high (not pressed)
    else if (buttons[i].risingEdge()) 
    {
       //send MIDI note OFF
      usbMIDI.sendNoteOff (MIDI_NOTE_NUMS[i], 110, MIDI_CHAN);
    }
  }

  //MIDI controllers should discard incoming MIDI messages 
  while (usbMIDI.read()){
    //ignore incoming messages
  }
 }
