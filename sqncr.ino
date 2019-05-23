const int keys = [5,4,3,2,6,7,8,9];
const int states = [0,0,0,0,0,0,0];
const int playing = [0,0,0,0,0,0,0];
const int tones = [83,106,67,71,0,0,0,0];

// MODES
// 1: ON/OFF 
// 2: ON, OFF
int  debug = 1;
int mode = 1;

void setup(){
    if (mode == 1) {
    	Serial.begin(9600);// Logging
    }
    Serial1.begin(31250);// MIDI
    // Set Keys
    for (byte i = 0; i < sizeof(keys); i++) {
    	pinMode(keys[i], INPUT);
    }
}

void synth(){
	for (byte i = 0; i < sizeof(states); i++) {
		if (state[i] == HIGH && playing[i] == 1) {
	      	playing[i] = 0;
	      	playMIDINote(1,tones[i], 0);
	      	if (debug == 1) {
	      		Serial.print(0);
	  		}	
	    }
	    if (state[i] == HIGH && playing[i] == 0) {
	      	playing[i] = 1;
	      	playMIDINote(1,tones[i], 100);
	      	if (debug == 1) {
	      		Serial.print(0);
	  		}	
	    }
    } 
}

void  piano(){
	for (byte i = 0; i < sizeof(states); i++) {
    state[i] = digitalRead(keys[i]);
    if (state[i] == HIGH && playing[i] == 0) {
      	playing[i] = 1;
      	playMIDINote(1,tones[i], 100);
      	if (debug == 1) {
      		Serial.print(1);
  		}	
    } else if(state[] == LOW && playing[i] == 1) {
      	playing[i] = 0;
      	playMIDINote(1, tones[i], 0);
     	if (debug == 1) {
      		Serial.print(0);
  		}
    }
  } 
}
void loop(){
  if(mode == 1){
  	piano():
  }
  if(mode == 2){
  	synth();
  }
}

void playMIDINote(byte channel, byte note, byte velocity)
{
    //MIDI channels 1-16 are really 0-15
    byte noteOnStatus=0x90 + (channel-1);  
    //Send MIDI
    Serial1.write(noteOnStatus);
    Serial1.write(note);
    Serial1.write(velocity);
}