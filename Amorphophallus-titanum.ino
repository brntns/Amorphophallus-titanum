// ┌─┐┌┬┐┌─┐┬─┐┌─┐┬ ┬┌─┐┌─┐┬ ┬┌─┐┬  ┬  ┬ ┬┌─┐  ┌┬┐┬┌┬┐┌─┐┌┐┌┬ ┬┌┬┐
// ├─┤││││ │├┬┘├─┘├─┤│ │├─┘├─┤├─┤│  │  │ │└─┐   │ │ │ ├─┤││││ ││││
// ┴ ┴┴ ┴└─┘┴└─┴  ┴ ┴└─┘┴  ┴ ┴┴ ┴┴─┘┴─┘└─┘└─┘   ┴ ┴ ┴ ┴ ┴┘└┘└─┘┴ ┴
//
//         BEAT               AMBIENT
//      ____1____            ____5____       
//     / ___2___ \          / ___6___ \
//    / / __3__ \ \        / / __7__ \ \
//   / / / _4_ \ \ \      / / / _8_ \ \ \
//  / / / / . \ \ \ \    / / / / . \ \ \ \
//  \ \ \ \___/ / / /    \ \ \ \___/ / / /
//   \ \ \_____/ / /      \ \ \_____/ / /
//    \ \_______/ /        \ \_______/ /
//     \_________/          \_________/

//MIDI
const int keys =         [  5,  4,  3,  2,  6,  7,  8,  9];
const int states =       [  0,  0,  0,  0,  0,  0,  0,  0];
const int playing =      [  0,  0,  0,  0,  0,  0,  0,  0];
const int tones =        [ 83,106, 67, 71,  0,  0,  0,  0];

// PLAY
const int tetris =       [ 64, 59, 60, 62, 60, 59, 57, 57, 60, 64, 62, 60, 71, 60, 62, 64, 60, 57, 57];
const int tetris_delay = [100, 50, 50,100, 50, 50,100, 50, 50,100, 50, 50,150, 50,100,100,100,100,200];

// MODES
// 1: ON/OFF 
// 2: ON, OFF
// 3: PLAY
int  debug = 1;
int mode = 1;

void setup(){
    if (mode == 1) {
    	Serial.begin(9600);// LOGING
    }
    Serial1.begin(31250);// MIDI
    // SET KEYS
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
void  play(){
  for (byte i = 0; i < sizeof(tetris); i++) {
    playMIDINote(1, tetris[i], 100);
    delay(tetris_delay[i]);
    playMIDINote(1, tetris[i], 0);
  } 
}
void loop(){
  if(mode == 1){
  	piano():
  }
  if(mode == 2){
  	synth();
  }
  if(mode == 3){
    play();
  }
}

void playMIDINote(byte channel, byte note, byte velocity)
{
    //MIDI CHANNELS 1-16 ARE REALLY 0-15
    byte noteOnStatus=0x90 + (channel-1);  
    //SEND MIDI
    Serial1.write(noteOnStatus);
    Serial1.write(note);
    Serial1.write(velocity);
}
