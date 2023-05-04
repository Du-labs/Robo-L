//V5.6 manjula......
//WORKING GOOD FOR ANGRY BIRD RED COLOR BOT...for vishweshwara museum exhibition
//written the function for seconds and minutes need to test it
//the motor will be forwarded till it detects wall
//working only for one digit  :ex:- WHEN,LIGHT,THEN,FORWARD,FOR,ONE,FOOT
//to be work on 2 digit and 3 digit number :ex:- WHEN,LIGHT,THEN,FORWARD,FOR,ONE,NINE,,TWO,FOOT
//bday program is working good
//low indication is working good
//rotations is changed to rotate
//different buzzing programe are working
//dance function is working

// utilities.c
/*Delay function to */
#include <VirtualWire.h>    // you must download and install the VirtualWire.h to your hardware/libraries folder
#undef int
#undef abs
#undef double
#undef float
#undef round

/* Basic Logical (BOOLEAN) #defines (use for BOOLEAN data types) */
#define FALSE  0
#define TRUE   (!FALSE)
#define HI     TRUE
#define LO     FALSE
#define YES    TRUE
#define NO     FALSE
#define ON     TRUE
#define OFF    FALSE
#define OPEN   TRUE
#define CLOSE  FALSE

#define WHEN 32
#define THEN 8
#define WAIT_FOR 48
#define FOR 24
#define OR 4
#define AND 1
#define NEXT 51
#define STOP 30
#define REPEAT 46
#define RETURN 43
#define GO 20
#define ELSE 17

#define WALL 52
#define NO_WALL 25
#define LIGHT 44
#define DARK 41
#define RAIN 28
#define TOUCH 49
#define SOUND 56

#define FORWARD 50
#define REVERSE 26
#define RIGHT 3
#define LEFT 6
#define BLINK_EYES 10
#define BUZZER 14
#define B_DAY 35
#define SECONDS 38
#define MINUTES 11
#define HOURS 22
#define ROTATE 19
#define FOOT 60
#define DEGREES 57
#define DANCE 34

#define ZERO 37
#define ONE 13
#define TWO 53
#define THREE 29
#define FOUR 55
#define FIVE 31
#define SIX 39
#define SEVEN 15
#define EIGHT 62
#define NINE 59
#define NO_COIN 63

#define MOTOR_FORWARD 0
#define MOTOR_REVERSE 1
#define MOTOR_LEFT    2
#define MOTOR_RIGHT   3
#define MOTOR_STOP    4
//-------------------------------------------------------------supermario---------------------------------------------------------------
#define NOTE_B05  31
#define NOTE_C15  33
#define NOTE_CS15 35
#define NOTE_D15  37
#define NOTE_DS15 39
#define NOTE_E15  41
#define NOTE_F15  44
#define NOTE_FS15 46
#define NOTE_G15  49
#define NOTE_GS15 52
#define NOTE_A15  55
#define NOTE_AS15 58
#define NOTE_B15  62
#define NOTE_C25  65
#define NOTE_CS25 69
#define NOTE_D25  73
#define NOTE_DS25 78
#define NOTE_E25  82
#define NOTE_F25  87
#define NOTE_FS25 93
#define NOTE_G25  98
#define NOTE_GS25 104
#define NOTE_A25  110
#define NOTE_AS25 117
#define NOTE_B25  123
#define NOTE_C35  131
#define NOTE_CS35 139
#define NOTE_D35  147
#define NOTE_DS35 156
#define NOTE_E35  165
#define NOTE_F35  175
#define NOTE_FS35 185
#define NOTE_G35  196
#define NOTE_GS35 208
#define NOTE_A35  220
#define NOTE_AS35 233
#define NOTE_B35  247
#define NOTE_C45  262
#define NOTE_CS45 277
#define NOTE_D45  294
#define NOTE_DS45 311
#define NOTE_E45  330
#define NOTE_F45  349
#define NOTE_FS45 370
#define NOTE_G45  392
#define NOTE_GS45 415
#define NOTE_A45  440
#define NOTE_AS45 466
#define NOTE_B45  494
#define NOTE_C55  523
#define NOTE_CS55 554
#define NOTE_D55  587
#define NOTE_DS55 622
#define NOTE_E55  659
#define NOTE_F55  698
#define NOTE_FS55 740
#define NOTE_G55  784
#define NOTE_GS55 831
#define NOTE_A55  880
#define NOTE_AS55 932
#define NOTE_B55  988
#define NOTE_C65 1047
#define NOTE_CS65 1109
#define NOTE_D65  1175
#define NOTE_DS65 1245
#define NOTE_E65  1319
#define NOTE_F65  1397
#define NOTE_FS65 1480
#define NOTE_G65  1568
#define NOTE_GS65 1661
#define NOTE_A65  1760
#define NOTE_AS65 1865
#define NOTE_B65  1976
#define NOTE_C75  2093
#define NOTE_CS75 2217
#define NOTE_D75  2349
#define NOTE_DS75 2489
#define NOTE_E75  2637
#define NOTE_F75  2794
#define NOTE_FS75 2960
#define NOTE_G75  3136
#define NOTE_GS75 3322
#define NOTE_A75  3520
#define NOTE_AS75 3729
#define NOTE_B75  3951
#define NOTE_C85  4186
#define NOTE_CS85 4435
#define NOTE_D85  4699
#define NOTE_DS85 4978
//--------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------melody------------------------------------------------------------

//       note, period, &  frequency.
#define  c1     3830    // 261 Hz
#define  d1    3400    // 294 Hz
#define  e1     3038    // 329 Hz
#define  f1     2864    // 349 Hz
#define  g1     2550    // 392 Hz
#define  a1     2272    // 440 Hz
#define  b1     2028    // 493 Hz
#define  C1     1912    // 523 Hz
// Define a special note, 'R', to represent a rest
#define  R1     0

//----------------------------------------------------------------------------------------------------------------------------------------
enum State { IDLE = 1, RX_DATA, EXEC_COMMAND};

const int TOUCH_Input = A0;
const int LIGHT_Input = A1;
const int LOW_BATTERY = A2;
const int RAIN_Input = A3;
const int side1_Input = A5;
const int side2_Input = A6;
const int SOUND_Input = A7;
const int WALL_Input = A4;
const int motor_1_A_Output = 10;
const int motor_1_B_Output  = 9;
const int motor_2_A_Output = 12;
const int motor_2_B_Output = 13;
const int BUZZER_Output = 3;
const int EYES1_Output = 4;
const int EYES2_Output = 5;

// Required reviewed variables
unsigned char i;
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;

// Need to review variables
char command_number, Historic_output, Current_output;
char Digit_Number = 0, Wait_for_flag = 0, wait_for_command_number = 0;
//unsigned int Numbers = 0;
unsigned int var;
char Status = 1; //Input_Status, commands_debug = 24;

unsigned char Rx_data[26] =
{
  /*  WHEN, LIGHT, THEN, LEFT, NO_COIN ,  NO_COIN,
    NO_COIN, NO_COIN, NO_COIN, NO_COIN,  NO_COIN, NO_COIN,
    NO_COIN, NO_COIN,  NO_COIN, NO_COIN,  NO_COIN, NO_COIN,
    NO_COIN, NO_COIN, NO_COIN, NO_COIN,  NO_COIN, NO_COIN,
    0xFF, 0xFF*/
  //WHEN, LIGHT, THEN, FORWARD, FOR, FOUR, FOOT, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, 0xFF, 0xFF
  WHEN, LIGHT, THEN, LEFT, FOR, NINE, SECONDS, NO_COIN, NO_COIN , NO_COIN , NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, 0xFF, 0xFF
  //WHEN, LIGHT, THEN, BLINK_EYES, FOR, ONE, ZERO, SECONDS, NO_COIN, NO_COIN,  NO_COIN, NO_COIN, NO_COIN, NO_COIN,  NO_COIN, NO_COIN,  NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN,  NO_COIN, NO_COIN, 0xFF, 0xFF
  // WHEN,LIGHT,THEN,FORWARD,FOR, FIVE,ROTATIONS,THEN, LEFT,NO_COIN,NO_COIN,NO_COIN,NO_COIN, NO_COIN,NO_COIN,NO_COIN,NO_COIN, NO_COIN,NO_COIN, NO_COIN, NO_COIN, NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  // WHEN,LIGHT,THEN,LEFT,NO_COIN, NO_COIN,NO_COIN,NO_COIN, NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN, NO_COIN,NO_COIN,NO_COIN,NO_COIN, NO_COIN,NO_COIN, NO_COIN, NO_COIN, NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //WHEN,LIGHT,THEN,RIGHT,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,
  //  WHEN,LIGHT, FORWARD, FOR, ONE, ZERO, SECONDS, THEN, BUZZ, THEN, WAITFOR, SOUND, STOP,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF, 0xFF
  //  FORWARD, WAITFOR, WALL, THEN, LEFT, WHEN, LIGHT, THEN, LEFT, FOR, TWO, SECONDS, THEN, BUZZ, WAITFOR, SOUND, THEN, STOP, RETURN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WHEN, NOWALL, THEN, REVERSE, FOR, ONE, ZERO, FOOT, AND, BUZZ, WAITFOR, WALL, THEN, STOP,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WHEN, SOUND, THEN, BUZZ, AND, REVERSE, FOR, ONE, ZERO, FOOT, THEN,BUZZ, BLINKEYES, AND, STOP,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WHEN, SOUND, THEN, REVERSE, FOR, SEVEN, FOOT, AND, STOP,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WAITFOR, EIGHT, HOURS, THEN, FORWARD,  FOR, FIVE, FOOT, THEN, LEFT, FOR, ONE, ZERO, FOOT, THEN, LEFT, FOR, TWO, FOOT, THEN, B’DAY, AND, BLINKEYES, AND, PANDADANCE,0xFF,0xFF
  //  WAITFOR, ONE, TWO, HOURS, THEN, BUZZ, WHEN, SOUND, THEN, STOP,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WHEN, DARK, THEN, FORWARD, FOR, FOUR, SECONDS, THEN, LEFT, FOR, TWO, SECONDS, THEN, BUZZ, BLINKEYES, AND, PANDADANCE,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WHEN, SOUND, THEN, BUZZ, AND, FORWARD, WAITFOR, SOUND, THEN, LEFT, WAITFOR, WALL, THEN, BLINKEYES, THEN, STOP,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WHEN, SOUND, WAITFOR, ONE,ZERO, SECONDS, THEN, BUZZ, FOR, ONE, SECONDS, THEN, STOP,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WAITFOR, TWO, ZERO, WALL, THEN, BUZZ, AND, BLINKEYES,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WHEN, SOUND, WAITFOR,ONE, ZERO, SECONDS, THEN, BUZZ, THEN, STOP, FORWARD, FOR, FIVE, FOOT, THEN, BUZZ, THEN, STOP,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  FORWARD, FOR, FIVE, FOOT, THEN, BUZZ, THEN, STOP,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WHEN, SOUND, FORWARD, WAITFOR, WALL, THEN, REVERSE, REPEAT,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WHEN, SOUND, FORWARD, FOR, FIVE, FOOT, THEN, LEFT, WAITFOR, WALL, THEN, STOP,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WHEN, SOUND, FORWARD,  WAITFOR, WALL, THEN, LEFT, FOR, THREE, SECONDS, BUZZ, FOR, TWO, SECONDS, WAITFOR, SOUND, THEN, RETURN, REPEAT,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WHEN, SOUND, FORWARD, FIVE, FOOTLEFT, FIVE, FOOT, LEFT, FIVE,FOOT, LEFT, FIVE, FOOT, THEN, STOP,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
  //  WHEN, SOUND, FORWARD, WHEN, WALL, ONE, TWO, FIVE, DEGREES, NEXT, FORWARD, AND, REPEAT,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,NO_COIN,0xFF,0xFF
};

void setup() {
  pinMode(TOUCH_Input , INPUT_PULLUP);
  pinMode(LIGHT_Input , INPUT_PULLUP);
  pinMode(LOW_BATTERY , INPUT_PULLUP);
  pinMode(RAIN_Input , INPUT_PULLUP);
  pinMode(side1_Input , INPUT_PULLUP);
  pinMode(side2_Input , INPUT_PULLUP);
  pinMode( SOUND_Input , INPUT_PULLUP);
  pinMode(WALL_Input , INPUT_PULLUP);
  pinMode(motor_1_A_Output , OUTPUT);
  pinMode(motor_1_B_Output , OUTPUT);
  pinMode(motor_2_A_Output , OUTPUT);
  pinMode(motor_2_B_Output , OUTPUT);
  pinMode(BUZZER_Output , OUTPUT);
  pinMode(EYES1_Output , OUTPUT);
  pinMode(EYES2_Output , OUTPUT);
  Serial.begin(9600);
  Serial.println("ROBOLBOT");
  vw_set_ptt_inverted(true);    // Required for RX Link Module
  vw_setup(2000);                   // Bits per sec
  vw_set_rx_pin(11);           // We will be receiving on pin 4 i.e the RX pin from the module connects to this pin.
  vw_rx_start();                      // Start the receiver
}
//--------------------------------------------low_battery_programe---------------------------------------------------------------------------------------

void low_battery()  {   // void low_battery
  float lvw = 3;  // low voltage warning value
  float c_volt = 0;

  // read the input on analog pin 1
  int sensorValue = analogRead(LOW_BATTERY);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
  c_volt = sensorValue * (5.0 / 1023.0);

  // if voltage is equal to or less than cut-off level, alarm and strobe
  if ( c_volt <= lvw) {
    lv_cutoff();   // low voltage function call
  }
  // ensure buzzer and led is off
  else {
    digitalWrite(BUZZER_Output, 0);
  }
}

void lv_cutoff() {
  // fade out from max to min in increments of 20
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 20) {
    digitalWrite(BUZZER_Output, fadeValue);
    delay(30);
  }
}

void beep(long interval) {
  static long previousBeep = 0;

  unsigned long currentMillis = millis();

  if (currentMillis - previousBeep > interval) {
    // save the last time you blinked the LED
    previousBeep = currentMillis;
    analogWrite(BUZZER_Output, 100);
    delay(100);
    analogWrite(BUZZER_Output, 0);

}
//-------------------------------------------------------end_of_low_battery_program-------------------------------------------------------
//--------------------------------------------------------------------------------BUZZ_ONE program  PLAYINGMELODY---------------------------------------------------------------------------------------

// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[],
//  which sets each note's relative length (higher #, longer note)
unsigned char melody1[14 ] = {  C1,  b1,  g1,  C1,  b1,   e1,  R1,  C1,  c1,  g1, a1, C1};
unsigned char beats1[14]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 };
unsigned char MAX_COUNT = sizeof(melody1) / 2; // Melody length, for looping.

// Set overall tempo
long tempo1 = 10000;
// Set length of pause between notes
unsigned int pause = 1000;
// Loop variable to increase Rest length
unsigned char rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
unsigned int tone_1 = 0;
unsigned int beat1 = 0;
long duration1  = 0;

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone1() {
  long elapsed_time = 0;
  if (tone_1 > 0) { // if this isn't a Rest beat, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration1) {

      digitalWrite(BUZZER_Output, HIGH);
      delayMicroseconds(tone_1 / 2);

      // DOWN
      digitalWrite(BUZZER_Output, LOW);
      delayMicroseconds(tone_1 / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_1);
    }
  }
  else { // Rest beat; loop times delay
    for (unsigned int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration1);
    }
  }
}

// LET THE WILD RUMPUS BEGIN =============================
void play_melody()
{
  // Set up a counter to pull from melody[] and beats[]
  for (unsigned int i = 0; i < MAX_COUNT; i++) {
    tone_1 = melody1[i];
    beat1 = beats1[i];

    duration1 = beat1 * tempo1; // Set up timing

    playTone1();            //calling function to play the tone
    playTone1();
    playTone1();
    playTone1();
    playTone1();
    // A pause between notes...
    delayMicroseconds(pause);
  }
}
//-------------------------------------------------------------------------end of playing melodyprogram----------------------------------------------------------------------------------------
//---------------------------------------------------------------------------alaram_tone-----------------------------------------------------------------------------------------------------
void buzz(unsigned char time)
{
  analogWrite(BUZZER_Output, 170);
  delay(time);
  analogWrite(BUZZER_Output, 0);
  delay(time);
}

void play_alaram()              //alaram will snooze for every 50ms
{
  buzz(50);
  buzz(50);                     //calling the function every time untill the alaram is stopped
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);
  buzz(50);

}
//-----------------------------------------------------------------------------------end of alaram tone---------------------------------------------------------------------------------------
//----------------------------------------------------STARWARS TONE------------------------------------------------------------------------

const int c3 = 261;
const int d3 = 294;
const int e3 = 329;
const int f3 = 349;
const int g3 = 391;
const int gS3 = 415;
const int a3 = 440;
const int aS3 = 455;
const int b3 = 466;
const int cH3 = 523;
const int cSH3 = 554;
const int dH3 = 587;
const int dSH3 = 622;
const int eH3 = 659;
const int fH3 = 698;
const int fSH3 = 740;
const int gH3 = 784;
const int gSH3 = 830;
const int aH3 = 880;
int counter3 = 0;

void beep3(int note3, int duration3)
{
  //Play tone on buzzerPin
  tone(BUZZER_Output, note3, duration3);
  //Stop tone on buzzerPin
  //Increment counter
  counter3++;
}
void firstSection()
{
  beep3(a3, 500);
  beep3(a3, 500);
  beep3(a3, 500);
  beep3(f3, 350);
  beep3(cH3, 150);
  beep3(a3, 500);
  beep3(f3, 350);
  beep3(cH3, 150);
  beep3(a3, 650);

  delay(500);

  beep3(eH3, 500);
  beep3(eH3, 500);
  beep3(eH3, 500);
  beep3(fH3, 350);
  beep3(cH3, 150);
  beep3(gS3, 500);
  beep3(f3, 350);
  beep3(cH3, 150);
  beep3(a3, 650);

  delay(500);
}

void secondSection()
{
  beep3(aH3, 500);
  beep3(a3, 300);
  beep3(a3, 150);
  beep3(aH3, 500);
  beep3(gSH3, 325);
  beep3(gH3, 175);
  beep3(fSH3, 125);
  beep3(fH3, 125);
  beep3(fSH3, 250);

  delay(325);

  beep3(aS3, 250);
  beep3(dSH3, 500);
  beep3(dH3, 325);
  beep3(cSH3, 175);
  beep3(cH3, 125);
  beep3(b3, 125);
  beep3(cH3, 250);

  delay(350);
}
void play_starwar()
{
  //Play first section
  firstSection();

  //Play second section
  secondSection();

  //Variant 1
  beep3(f3, 250);
  beep3(gS3, 500);
  beep3(f3, 350);
  beep3(a3, 125);
  beep3(cH3, 500);
  beep3(a3, 375);
  beep3(cH3, 125);
  beep3(eH3, 650);

  delay(500);

  //Repeat second section
  secondSection();

  //Variant 2
  beep3(f3, 250);
  beep3(gS3, 500);
  beep3(f3, 375);
  beep3(cH3, 125);
  beep3(a3, 500);
  beep3(f3, 375);
  beep3(cH3, 125);
  beep3(a3, 650);

  delay(650);
}
//------------------------------------------------------------------END OF STARWAR TONE--------------------------------------------------------
//-----------------------------------program for twinkle twinkle four--------------------------------------------------------------------

int length4 = 15; // the number of notes

//twinkle twinkle little star
unsigned char notes4[50] = "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc "; // a space represents a rest
unsigned char beats4[20] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
unsigned int tempo4 = 300;

void playTone4(unsigned int tone4, unsigned int duration4) {
  for (long i = 0; i < duration4 * 1000L; i += tone4 * 2) {
    digitalWrite(BUZZER_Output, HIGH);
    delayMicroseconds(tone4);
    digitalWrite(BUZZER_Output, LOW);
    delayMicroseconds(tone4);
  }
}

void playNote4(unsigned char note4, unsigned int duration4) {
  char names4[10] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones4[10] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names4[i] == note4) {
      playTone4(tones4[i], duration4);
    }
  }
}
void playtwinkle ()
{
  for (unsigned int i = 0; i < length4; i++) {          //based on the tempo specified it will play the tone
    if (notes4[i] == ' ') {
      delay(beats4[i] * tempo4); // rest
    }
    else
    {
      playNote4(notes4[i], beats4[i] * tempo4);
    }

    // pause between notes
    delay(tempo4 / 2);
  }
}
//----------------------------------------------------------end of twinkle program---------------------------------------------------------
//------------------------------------------------------------superMario-------------------------------------------------------------------
unsigned int melody5[100] = {
  NOTE_E75, NOTE_E75, 0, NOTE_E75,
  0, NOTE_C75, NOTE_E75, 0,
  NOTE_G75, 0, 0,  0,
  NOTE_G65, 0, 0, 0,

  NOTE_C75, 0, 0, NOTE_G65,
  0, 0, NOTE_E65, 0,
  0, NOTE_A65, 0, NOTE_B65,
  0, NOTE_AS65, NOTE_A65, 0,

  NOTE_G65, NOTE_E75, NOTE_G75,
  NOTE_A75, 0, NOTE_F75, NOTE_G75,
  0, NOTE_E75, 0, NOTE_C75,
  NOTE_D75, NOTE_B65, 0, 0,

  NOTE_C75, 0, 0, NOTE_G65,
  0, 0, NOTE_E65, 0,
  0, NOTE_A65, 0, NOTE_B65,
  0, NOTE_AS65, NOTE_A65, 0,

  NOTE_G65, NOTE_E75, NOTE_G75,
  NOTE_A75, 0, NOTE_F75, NOTE_G75,
  0, NOTE_E75, 0, NOTE_C75,
  NOTE_D75, NOTE_B65, 0, 0
};
//Mario main them tempo
unsigned int tempo5[100] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
unsigned int underworld_melody5[100] = {
  NOTE_C45, NOTE_C55, NOTE_A35, NOTE_A45,
  NOTE_AS35, NOTE_AS45, 0,
  0,
  NOTE_C45, NOTE_C55, NOTE_A35, NOTE_A45,
  NOTE_AS35, NOTE_AS45, 0,
  0,
  NOTE_F35, NOTE_F45, NOTE_D35, NOTE_D45,
  NOTE_DS35, NOTE_DS45, 0,
  0,
  NOTE_F35, NOTE_F45, NOTE_D35, NOTE_D45,
  NOTE_DS35, NOTE_DS45, 0,
  0, NOTE_DS45, NOTE_CS45, NOTE_D45,
  NOTE_CS45, NOTE_DS45,
  NOTE_DS45, NOTE_GS35,
  NOTE_G35, NOTE_CS45,
  NOTE_C45, NOTE_FS45, NOTE_F45, NOTE_E35, NOTE_AS45, NOTE_A45,
  NOTE_GS45, NOTE_DS45, NOTE_B35,
  NOTE_AS35, NOTE_A35, NOTE_GS35,
  0, 0, 0
};
//Underwolrd tempo
unsigned int underworld_tempo5[100] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};


unsigned int song5 = 0;

void sing5(unsigned int s) {
  // iterate over the notes of the melody:
  song5 = s;
  if (song5 == 2) {
    Serial.println(" 'Underworld Theme'");
    unsigned int size = sizeof(underworld_melody5) / sizeof( unsigned int);
    for (unsigned int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      unsigned int noteDuration = 1000 / underworld_tempo5[thisNote];

      buzz(BUZZER_Output, underworld_melody5[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      unsigned int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(BUZZER_Output, 0, noteDuration);

    }

  } else {

    Serial.println(" 'Mario Theme'");
    unsigned int size = sizeof(melody5) / sizeof(unsigned int);
    for (unsigned int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      unsigned int noteDuration = 1000 / tempo5[thisNote];

      buzz(BUZZER_Output, melody5[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      unsigned int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(BUZZER_Output, 0, noteDuration);

    }
  }
}
void buzz(unsigned int targetPin, long frequency, long length5) {
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length5 / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(BUZZER_Output, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(BUZZER_Output, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
}
void playsupermario()
{
  //sing the tunes
  sing5(1);
  sing5(1);
  sing5(2);
}

//-----------------------------------------------------------------------------------function for dance-------------------------------------------------------------------
void F_DANCE()
{
  digitalWrite(BUZZER_Output, HIGH);      //motor will move forward and reverse and buzzer will make sound
  Motor(1, 0, MOTOR_FORWARD);
  Motor(2, 0, MOTOR_FORWARD);
  wheel(16, 16);
  Motor(1, 0, MOTOR_FORWARD);
  Motor(2, 0, MOTOR_REVERSE);
  wheel(32, 32);
  /* digitalWrite(motor_1_A_Output, HIGH);
    digitalWrite(motor_1_B_Output, LOW);
    digitalWrite(motor_2_A_Output, LOW);
    digitalWrite(motor_2_B_Output, LOW);*/
  digitalWrite(EYES1_Output, LOW);
  digitalWrite(EYES2_Output, LOW);
  // digitalWrite(BUZZER_Output, HIGH);
  Motor(2, 0, MOTOR_REVERSE);
  Motor(1, 0, MOTOR_REVERSE);
  wheel(16, 16);
  Motor(2, 0, MOTOR_FORWARD);
  Motor(1, 0, MOTOR_REVERSE);
  wheel(32, 32);

}


/*Rotate, blink EYES_Output and music for 5 seconds*/
//--------------------------------------------------------------------------end of dance program------------------------------------------------------------------------
//---------------------------------------------------------------------------function for bday program-------------------------------------------------------------------

int length = 28; // the number of notes
char notes[] = "GGAGcB GGAGdc GGxecBA yyecdc";
int beats[] = { 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8, 8, 8, 16, 1, 2, 2, 8, 8, 8, 16 };
int tempo = 150;
void playTone(unsigned int tone, unsigned int duration)
{
  for (long i = 0; i < duration * 1000L; i += tone * 2)
  {
    digitalWrite(BUZZER_Output, HIGH);
    delayMicroseconds(tone);
    digitalWrite(BUZZER_Output, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration)
{
  char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',
                  'c', 'd', 'e', 'f', 'g', 'a', 'b',
                  'x', 'y'
                 };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,
                  956,  834,  765,  593,  468,  346,  224,
                  655 , 715
                };
  int SPEE = 5;
  // play the tone corresponding to the note name
  for (unsigned int i = 0; i < 17; i++)
  {
    if (names[i] == note)
    {
      int newduration = duration / SPEE;
      playTone(tones[i], newduration);
    }
  }
}

void F_Birthday_Buz()
{
  for (unsigned int i = 0; i < length; i++)           //based on the length specified the birthday tone will be played
  {
    if (notes[i] == ' ')
    {
      delay(beats[i] * tempo); // rest
    } else
    {
      playNote(notes[i], beats[i] * tempo);
    }
    // pause between notes
    delay(tempo);
  }
  // play the tone corresponding to the note name
}

//---------------------------------------------------------------------------end of bday program---------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop()
{

  low_battery();    //low_battery function calling
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  switch (Status)                                   // STATE MACHINE
  {
    //------------------------------------------------- IDLE ------------------------------------------------
    case  IDLE :
      // Recieve message, Read all sensor data, If program exists, go to EXEC_COMMAND else wait till Rx
      // Check if Data Rxd and once cycle of execution completed.

      //-----------------------------From Virtual wire-------------------
       // check to see if anything has been received
      {
        unsigned int i;
        // Message with a good checksum received.

        for (i = 0; i < buflen; i++)
        {
          Serial.print(buf[i]);            // the received data is stored in buffer
          Rx_data[i] = buf[i];
          Serial.print("-");
        }
        Serial.println("");
      }
      Status = EXEC_COMMAND;
      command_number = 0;
      break;
    //------------------------------------------------- RX_DATA ------------------------------------------------
    case  RX_DATA :
      // Recieve message, Check for checksum, Go to display error state if error, if not go to next task here.
      // Store task, Go to EXEC_COMMAND

      Status = EXEC_COMMAND;
      // command_number = 0;
      break;
    //------------------------------------------------- EXEC_COMMAND ------------------------------------------------
    case  EXEC_COMMAND :
      Serial.println("EXECUTE_COMMAND");
      // Execute commands in loop/one time based one the commands on slate.
      // Periodically check for recieve data and jump to RX_DATA if Rx buffer triggers
      Execute_24_commands();        // calling the function where it will check for al the 24 commands
      // Go to IDLE to execute next command and
      Historic_output = FALSE;
      Current_output = FALSE; // Clearing flags before going to next execution freshly*/
      Status = IDLE;
      break;
  }
}
// Loopend ------------------------------------------------- End of state machine ------------------------------------------------



unsigned int value2, value3;
unsigned int dataa1 = 0;
unsigned  int F_NUMBERS(unsigned int Number)
{
  Serial.println("function of numbers");
  dataa1 = Number;
  command_number++;
  if (Rx_data[command_number] == ONE || TWO || THREE || FOUR || FIVE || SIX || SEVEN || EIGHT || NINE || ZERO)
  {
    Serial.println("ifloop1");
    switch (Rx_data[command_number])
    {
      case ONE:                                   //based the command number the following cases will be select and inside it the function F_NUM1 will be called
        dataa1 = F_Num1(1);
        break;
      case TWO:
        dataa1 = F_Num1(2) ;
        break;
      case THREE:
        dataa1 = F_Num1(3) ;
        break;
      case FOUR:
        dataa1 = F_Num1(4) ;
        break;
      case FIVE:
        dataa1 = F_Num1(5) ;
        break;
      case SIX:
        dataa1 = F_Num1(6) ;
        break;
      case SEVEN:
        dataa1 = F_Num1(7) ;
        break;
      case EIGHT:
        dataa1 = F_Num1(8) ;
        break;
      case NINE:
        dataa1 = F_Num1(9) ;
        break;
      case ZERO:
        dataa1 = F_Num1(0) ;
        break;
    }
  }

  command_number++;
  if (Rx_data[command_number] == ONE || TWO || THREE || FOUR || FIVE || SIX || SEVEN || EIGHT || NINE || ZERO)
  {
    Serial.println("if loop2");
    switch (Rx_data[command_number])
    {
      case ONE:
        dataa1 = F_Num2(1);        //based the command number the following cases will be select and inside it the function F_NUM1 will be called
        break;
      case TWO:
        dataa1 = F_Num2(2) ;
        break;
      case THREE:
        dataa1 = F_Num2(3) ;
        break;
      case FOUR:
        dataa1 = F_Num2(4) ;
        break;
      case FIVE:
        dataa1 = F_Num2(5) ;
        break;
      case SIX:
        dataa1 = F_Num2(6) ;
        break;
      case SEVEN:
        dataa1 = F_Num2(7) ;
        break;
      case EIGHT:
        dataa1 = F_Num2(8) ;
        break;
      case NINE:
        dataa1 = F_Num2(9) ;
        break;
      case ZERO:
        dataa1 = F_Num2(0) ;
        break;
    }
    Serial.println("dataa1");
    Serial.println(dataa1);
  }
  command_number--;
  command_number--;
  return dataa1;
}
//---------------------------------------------------------------------function for number 1 & 2----------------------------------------------------

int F_Num1(unsigned int Num1)
{
  value2 = dataa1 * 10 + Num1;
  Serial.println("value2");           //for loop 1 value 2 will be calculated based on the number passed
  Serial.println(value2);
  return value2;

}
int F_Num2(unsigned int Num2)
{
  value3 = dataa1 * 10 + Num2;           //for loop 1 value 2 will be calculated based on the number passed
  Serial.println("value3");
  Serial.println(value3);
  return value3;

}


//---------------------------------------------------------------------end of fun number 1 & 2----------------------------------------------------

//------------------------------------------------------------END OF FUNCTION FOR NMBERS------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------
char fun_wall()
{
  char wal = digitalRead(WALL_Input);
  return wal;
}

//----------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------function of foot-------------------------------------------------------------------------------------------------
void F_foot( int var)
{
  Serial.println("executing foot function");
  Serial.println("var");
  Serial.println(var);
  unsigned int k = 0;
  command_number--;
  Serial.println("Rx_data[command_number] at the start of foot");
  Serial.println("Rx_data[command_number]");
  Serial.println(Rx_data[command_number]);

  if (Rx_data[command_number] == ONE || TWO || THREE || FOUR || FIVE || SIX || SEVEN || EIGHT || NINE || ZERO)
  {
    command_number--;
    if (Rx_data[command_number] == FOR)
    {
      command_number--;
      if (Rx_data[command_number] == FORWARD || REVERSE || LEFT || RIGHT)
      {
        switch (Rx_data[command_number])
        {

          case FORWARD:                                  //Upto the variable number sent the motor will move in forward direction for foot           
            if (Historic_output == TRUE)
            {
              Serial.println("var");
              Serial.println(var);
              for (k = 0; k < var; k++)
              {
                Serial.println("executing FORWARDINGing operation");
                Motor(1, 0, MOTOR_FORWARD);
                Motor(2, 0, MOTOR_FORWARD);
                wheel(8, 8);
                Serial.println("k");
                Serial.println(k);
              }
            }
            else
            {
              Motor(1, 0, MOTOR_STOP);
              Motor(2, 0, MOTOR_STOP);
            }
            break;

          case REVERSE:                                           //Upto the variable number sent the motor will move in reverse direction for seconds
            if (Historic_output == TRUE)
            {
              for (k = 0; k < var; k++)
              {
                Serial.println("executing reversing operation");
                Motor(1, 0, MOTOR_REVERSE);
                Motor(2, 0, MOTOR_REVERSE);
                wheel(8, 8);
              }
            }
            else
            {
              Motor(1, 0, MOTOR_STOP);
              Motor(2, 0, MOTOR_STOP);
            }
            break;

          case LEFT:                                     //Upto the variable number sent the motor will move to left for foot
            if (Historic_output == TRUE)
            {
              Motor(2, 0, MOTOR_LEFT);
              Motor(1, 0, MOTOR_LEFT);

              for (k = 0; k < var; k++)
              {
                Motor(1, 0, MOTOR_FORWARD);
                Motor(2, 0, MOTOR_FORWARD);
                wheel(8, 8);
              }
            }
            else
            {
              Motor(1, 0, MOTOR_STOP);
              Motor(2, 0, MOTOR_STOP);
            }

            break;

          case RIGHT:                                         //Upto the variable number sent the motor will move to RIGHT for foot
            if (Historic_output == TRUE)
            {
              Motor(1, 0, MOTOR_RIGHT);
              Motor(2, 0, MOTOR_RIGHT);
              for (k = 0; k < var; k++)
              {
                Motor(1, 0, MOTOR_FORWARD);
                Motor(2, 0, MOTOR_FORWARD);
                wheel(8, 8);
              }
            }
            else
            {
              Motor(1, 0, MOTOR_STOP);
              Motor(2, 0, MOTOR_STOP);
            }
            break;
        }
        command_number++;
      }
      command_number++;
    }
    command_number++;
  }
  Serial.println("Rx_data[command_number] at the end of foot function");
  Serial.println("Rx_data[command_number]");
  Serial.println(Rx_data[command_number]);
}
/*   if (Rx_data[command_number] == ONE || TWO || THREE || FOUR || FIVE || SIX || SEVEN || EIGHT || NINE || ZERO)
   {
     command_number--;
     if (Rx_data[command_number] == FOR)
     {
       command_number--;
       if (Rx_data[command_number] == FORWARD || REVERSE || LEFT || RIGHT)
       {
         switch (Rx_data[command_number])
         {
           case FORWARD:
             Motor(1, 0, MOTOR_FORWARD);
             Motor(2, 0, MOTOR_FORWARD);
             k = 0;
             for (k = 0; k << var; k++)
             {
               wheel(8, 8);
             }
             break;
           case REVERSE:
             Motor(1, 0, MOTOR_REVERSE);
             Motor(2, 0, MOTOR_REVERSE);
             k = 0;
             for (k = 0; k << var; k++)
             {
               wheel(8, 8);
             }
             break;
           case LEFT:
             Motor(1, 0, MOTOR_FORWARD);
             Motor(2, 0, MOTOR_FORWARD);
             k = 0;
             for (k = 0; k << var; k++)
             {
               wheel(8, 8);
             }
             break;
           case RIGHT:
             Motor(1, 0, MOTOR_FORWARD);
             Motor(2, 0, MOTOR_FORWARD);
             k = 0;
             for (k = 0; k << var; k++)
             {
               wheel(8, 8);
             }
             break;
         }
         command_number++;
       }
       // command_number++;
     }
     if (Rx_data[command_number] == ONE || TWO || THREE || FOUR || FIVE || SIX || SEVEN || EIGHT || NINE || ZERO)
     {
       command_number--;
       if (Rx_data[command_number] == FOR)
       {
         command_number--;
         if (Rx_data[command_number] == FORWARD || REVERSE || LEFT || RIGHT)
         {
           switch (Rx_data[command_number])
           {
             case FORWARD:
               Motor(1, 0, MOTOR_FORWARD);
               Motor(2, 0, MOTOR_FORWARD);
               k = 0;
               for (k = 0; k << var; k++)
               {
                 wheel(8, 8);
               }
               break;

             case REVERSE:
               Motor(1, 0, MOTOR_REVERSE);
               Motor(2, 0, MOTOR_REVERSE);
               k = 0;
               for (k = 0; k << var; k++)
               {
                 wheel(8, 8);
               }
               break;
             case LEFT:
               Motor(1, 0, MOTOR_FORWARD);
               Motor(2, 0, MOTOR_FORWARD);
               k = 0;
               for (k = 0; k << var; k++)
               {
                 wheel(8, 8);
               }
               break;
             case RIGHT:
               Motor(1, 0, MOTOR_FORWARD);
               Motor(2, 0, MOTOR_FORWARD);
               k = 0;
               for (k = 0; k << var; k++)
               {
                 wheel(8, 8);
               }
               break;
           }
           command_number++;
         }
         command_number++;
       }
       command_number++;
     }
   }
   command_number++;
  }
  command_number++;
  Serial.println("Rx_data[command_number] at the end of foot function");
  Serial.println("Rx_data[command_number]");
  Serial.println(Rx_data[command_number]);*/
//------------------------------------------------------------------function of seconds--------------------------------------------------------------------------------------
void f_function_seconds(int var)
{
  unsigned int n;
  command_number--;
  Serial.println("Rx_data[command_number] at the start of foot");
  Serial.println("Rx_data[command_number]");
  Serial.println(Rx_data[command_number]);
  if (Rx_data[command_number] == ONE || TWO || THREE || FOUR || FIVE || SIX || SEVEN || EIGHT || NINE || ZERO)
  {
    command_number--;
    if (Rx_data[command_number] == FOR)
    {
      command_number--;
      if (Rx_data[command_number] == FORWARD || REVERSE || LEFT || RIGHT || BUZZER || BLINK_EYES)
      {
        switch (Rx_data[command_number])
        {

          case FORWARD:
            if (Historic_output == TRUE)            //Upto the variable number sent the motor will move in forward direction for seconds
            {                                      
              for (n = 0; n < var; n++)
              {
                Serial.println("var");
                Serial.println(var);

                Motor(1, 0, MOTOR_FORWARD);
                Motor(2, 0, MOTOR_FORWARD);
                delay(950);               //will remain for 950 ms and the motor will stop 
              }
            }
            else
            {
              Motor(1, 0, MOTOR_STOP);
              Motor(2, 0, MOTOR_STOP);
            }
            break;

          case REVERSE:
            if (Historic_output == TRUE)          //Upto the variable number sent the motor will move in reverse direction for seconds
            {
              for (n = 0; n < var; n++)
              {
                Motor(1, 0, MOTOR_REVERSE);
                Motor(2, 0, MOTOR_REVERSE);
                delay(950);                // will remain for 950 ms and the motor will stop 
              }
            }
            else
            {
              Motor(1, 0, MOTOR_STOP);
              Motor(2, 0, MOTOR_STOP);
            }
            break;

          case LEFT:
            if (Historic_output == TRUE)          //Upto the variable number sent the motor will move in LEFT direction for seconds
            {
              Motor(2, 0, MOTOR_LEFT);
              Motor(1, 0, MOTOR_LEFT);
              for (n = 0; n < var; n++)
              {
                Motor(1, 0, MOTOR_FORWARD);
                Motor(2, 0, MOTOR_FORWARD);
                delay(950);                       //will remain for 950 ms and the motor will stop 
              }
            }
            else
            {
              Motor(1, 0, MOTOR_STOP);
              Motor(2, 0, MOTOR_STOP);
            }
            break;

          case RIGHT:
            if (Historic_output == TRUE)        //Upto the variable number sent the motor will move in RIGHT direction for seconds
            {
              Motor(1, 0, MOTOR_RIGHT);
              Motor(2, 0, MOTOR_RIGHT);
              for (n = 0; n < var; n++)
              {
                Motor(1, 0, MOTOR_FORWARD);
                Motor(2, 0, MOTOR_FORWARD);
                delay(950);                   //will remain for 950 ms and the motor will stop 
              }
            }
            else
            {
              Motor(1, 0, MOTOR_STOP);
              Motor(2, 0, MOTOR_STOP);
            }
            break;

          case BLINK_EYES:                            //Upto the variable number sent the eyes will starts blinking for seconds
            if (Historic_output == TRUE)
            {
              for (n = 0; n < var; n++)
              {
                digitalWrite(EYES1_Output, LOW );
                digitalWrite(EYES2_Output, LOW);
                delay(475);           // Delay in milliseconds
                digitalWrite(EYES1_Output, HIGH);
                digitalWrite(EYES2_Output, HIGH);
                delay(475);
              }
            }
            else
            {
              digitalWrite(EYES1_Output, HIGH);
              digitalWrite(EYES2_Output, HIGH);
            }
            break;
          case BUZZER:                              //Upto the variable number sent the buzzer starts to make sound for seconds
            if (Historic_output == TRUE)
            {
              for (n = 0; n < var; n++)
              {
                digitalWrite(BUZZER_Output, HIGH );
                delay(950);
              }
            }
            else
            {
              digitalWrite(BUZZER_Output, LOW );
            }
            break;
        }
        command_number++;
      }
      command_number++;
    }
    command_number++;
  }
}
//----------------------------------------------------------------------------------END OF SECONDS PROGRAM---------------------------------------------------------------------------+
//----------------------------------------------------------------------------funtion for MINUTES-----------------------------------------------------------------------------------
void f_function_minutes(int var)
{
  unsigned int m;
  command_number--;
  Serial.println("Rx_data[command_number] at the start of minutes");
  Serial.println("Rx_data[command_number]");
  Serial.println(Rx_data[command_number]);
  if (Rx_data[command_number] == ONE || TWO || THREE || FOUR || FIVE || SIX || SEVEN || EIGHT || NINE || ZERO)
  {
    command_number--;
    if (Rx_data[command_number] == FOR)
    {
      command_number--;
      if (Rx_data[command_number] == FORWARD || REVERSE || LEFT || RIGHT || BUZZER || BLINK_EYES)
      {
        switch (Rx_data[command_number])
        {

          case FORWARD:                                     //Upto the variable number sent the motor will move in forward direction for minutes
            if (Historic_output == TRUE)
            {
              for (m = 0; m < var; m++)
              {
                Serial.println("var");
                Serial.println(var);

                Motor(1, 0, MOTOR_FORWARD);
                Motor(2, 0, MOTOR_FORWARD);
                delay(60000);
              }
            }
            else
            {
              Motor(1, 0, MOTOR_STOP);
              Motor(2, 0, MOTOR_STOP);
            }
            break;

          case REVERSE:                       //Upto the variable number sent the motor will move in reverse direction for minutes
            if (Historic_output == TRUE)
            {
              for (m = 0; m < var; m++)
              {
                Motor(1, 0, MOTOR_REVERSE);
                Motor(2, 0, MOTOR_REVERSE);
                delay(60000);
              }
            }
            else
            {
              Motor(1, 0, MOTOR_STOP);
              Motor(2, 0, MOTOR_STOP);
            }
            break;

          case LEFT:                          //Upto the variable number sent the motor will move to LEFT for minutes
            if (Historic_output == TRUE)
            {
               Serial.println("var");
                Serial.println(var);

              Motor(2, 0, MOTOR_LEFT);
              Motor(1, 0, MOTOR_LEFT);
              for (m = 0; m < var; m++)
              {
                Motor(1, 0, MOTOR_FORWARD);
                Motor(2, 0, MOTOR_FORWARD);
                delay(60000);
              }
            }
            else
            {
              Motor(1, 0, MOTOR_STOP);
              Motor(2, 0, MOTOR_STOP);
            }
            break;

          case RIGHT:                                   //Upto the variable number sent the motor will move to RIGHT for minutes
            if (Historic_output == TRUE)
            {
              Motor(1, 0, MOTOR_RIGHT);
              Motor(2, 0, MOTOR_RIGHT);
              for (m = 0; m < var; m++)
              {
                Motor(1, 0, MOTOR_FORWARD);
                Motor(2, 0, MOTOR_FORWARD);
                delay(60000);
              }
            }
            else
            {
              Motor(1, 0, MOTOR_STOP);
              Motor(2, 0, MOTOR_STOP);
            }
            break;

          case BLINK_EYES:                                    //Upto the variable number sent the motor will BLINK eyes for minutes
            if (Historic_output == TRUE)
            {
              for (m = 0; m < var; m++)
              {
                unsigned int e;
                for (e = 0; e < 60; e++);
                {
                  digitalWrite(EYES1_Output, LOW );
                  digitalWrite(EYES2_Output, LOW);
                  delay(200);           // Delay in milliseconds
                  digitalWrite(EYES1_Output, HIGH);
                  digitalWrite(EYES2_Output, HIGH);
                  delay(60000);
                }
              }
            }
            else
            {
              digitalWrite(EYES1_Output, HIGH);
              digitalWrite(EYES2_Output, HIGH);
            }
            break;
          case BUZZER:                                  //Upto the variable number sent the motor will BUZZ for minutes
            if (Historic_output == TRUE)
            {
              for (m = 0; m < var; m++)
              {
                unsigned int f;
                for (f = 0; f < 60; f++);
                {
                  digitalWrite(BUZZER_Output, HIGH );
                  delay(60000);
                }
              }
            }
            else
            {
              digitalWrite(BUZZER_Output, LOW );
            }
            break;
        }
        command_number++;
      }
      command_number++;
    }
    command_number++;
  }
}

//------------------------------------------------------------------------------end function for MINUTES-------------------------------------------------------------------------------
//--------------------------------------------------------------end of foot function-----------------------------------------------------------------------------------------
void Motor(char motor_number, char delay_sec, char action) // Motor number, Delay, fwd/rev (0/1)
{
  if (motor_number == 1)
  {
    if (delay_sec == 0)
    {
      if (action == MOTOR_FORWARD)          // Forward
      {
        digitalWrite(motor_1_A_Output, HIGH);    // Motor-1 runs forward.
        digitalWrite(motor_1_B_Output, LOW);    // Motor-1 runs
      }
      else if (action == MOTOR_REVERSE)  // Reverse
      {
        digitalWrite(motor_1_A_Output, LOW);
        digitalWrite(motor_1_B_Output, HIGH);
      }
      else if (action == MOTOR_LEFT)          // Left
      {
        digitalWrite(motor_1_A_Output, LOW);
        digitalWrite(motor_1_B_Output, HIGH);
        wheel(4, 4);  // To turn left.
        digitalWrite(motor_1_A_Output, HIGH);
        digitalWrite(motor_1_B_Output, LOW);
        wheel(6, 6);
      }
      else if (action == MOTOR_RIGHT)          // Right
      {
        digitalWrite(motor_1_A_Output, HIGH);
        digitalWrite(motor_1_B_Output, LOW);
      }
      else if (action == MOTOR_STOP)
      {
        digitalWrite(motor_1_A_Output, LOW);   // Stop
        digitalWrite(motor_1_B_Output, LOW);
      }
      else
      {

      }
    }
  }
  if (motor_number == 2)
  {
    if (delay_sec == 0)
    {
      if (action == MOTOR_FORWARD)          // Forward
      {
        digitalWrite(motor_2_A_Output, HIGH);    // Motor-1 runs forward.
        digitalWrite(motor_2_B_Output, LOW);    // Motor-1 runs
      }
      else if (action == MOTOR_REVERSE)  // Reverse
      {
        digitalWrite(motor_2_A_Output, LOW);
        digitalWrite(motor_2_B_Output, HIGH);
      }
      else if (action == MOTOR_LEFT)          // Left
      {
        digitalWrite(motor_2_A_Output, HIGH);
        digitalWrite(motor_2_B_Output, LOW);
      }
      else if (action == MOTOR_RIGHT)          // Right
      {
        digitalWrite(motor_2_A_Output, LOW);
        digitalWrite(motor_2_B_Output, HIGH);
        wheel(5, 5);  // To turn Right.
        digitalWrite(motor_2_A_Output, HIGH);
        digitalWrite(motor_2_B_Output, LOW);
        wheel(6, 6);
      }
      else if (action == MOTOR_STOP)        //stop
      {
        digitalWrite(motor_2_A_Output, LOW);
        digitalWrite(motor_2_B_Output, LOW);
      }
      else
      {

      }
    }
  }
}

//-----------------------------------------------------------------------------FUNCTION FOR STOP-------------------------------------------------------------
void F_STOP()
{
  Motor(1, 0, MOTOR_STOP);        //to stop motor,buzzer will be stoped and both eyes will be high
  Motor(2, 0, MOTOR_STOP);
  digitalWrite(BUZZER_Output, LOW);
  digitalWrite(EYES1_Output, HIGH);
  digitalWrite(EYES2_Output, HIGH);
}

//--------------------------------------------------------------------------END OF STOP FUNCTION-----------------------------------------------------------------

//----------------------------------------------------------------------------------wheel ir program-------------------------------------------------------------------------------------------
void wheel(unsigned int right, unsigned int left)
{
  //to read right ir
  unsigned  int counter_right = 0, counter_left = 0, historic_right = 0, historic_left = 0;
  Serial.println("historic_right");
  Serial.println(historic_right);
  Serial.println("historic_left");
  Serial.println(historic_left);
  unsigned int i, current_right, current_left;
abc:
  current_right = digitalRead(A5);
  Serial.println("current_right");
  Serial.println(current_right);
  if (current_right != historic_right)
  {
    counter_right++;
    Serial.println("counter_right");
    Serial.println(counter_right);
    historic_right = current_right;
  }
  char curren_left = analogRead(A6);
  if (curren_left <= 500)
  {
    current_left = LOW;
  }
  else
  {
    current_left = HIGH;
  }
  Serial.println("current_left");
  Serial.println(current_left);
  if (current_left != historic_left )
  {
    counter_left++;
    Serial.println("counter_left");
    Serial.println(counter_left);
    current_left = historic_left;
  }
  if (right != counter_right && left  != counter_left)
  {
    goto abc;
  }
  // else
  //{
  //counter_right = 0;
  //counter_left = 0;
  //}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------function for rotate-----------------------------------------------------------------------------------------------------
void rotate_left()
{
  Motor(1, 0, MOTOR_FORWARD); //motor 1 will move forward and motor 2 will go reverse to rotate left
  Motor(2, 0, MOTOR_REVERSE);
  wheel(24, 24);
}
void rotate_right()         //motor 2 will move forward and motor 1 will go reverse to rotate left
{
  Motor(2, 0, MOTOR_FORWARD);
  Motor(1, 0, MOTOR_REVERSE);
  wheel(24, 24);
}
void rotate_both()            //combination of right and left rotation
{
  Motor(1, 0, MOTOR_FORWARD);     
  Motor(2, 0, MOTOR_REVERSE);

  wheel(16, 16);
  Motor(1, 0, MOTOR_REVERSE);
  Motor(2, 0, MOTOR_FORWARD);

  wheel(16, 16);
}
//-------------------------------------------------------------------------end of rotate function-----------------------------------------------------------------------------------

void Elapse_Time(unsigned int Number_to_action)            // Call this function to elapse the time in seconds
{
  F_delay(100);  /* Elapse number of seconds as in input parameter*/
}
void  Elapse_Length(unsigned int Numbers_to_action)
{

}
void Elapse_Angle(unsigned int Number_to_action)               // Call this function to elapse number of degrees
{

}
char Read_INPUT(char input_sensor)                // Call this function to get all sensor status
{
  int  return_val = 0;

  // Return TRUE if input pointed command returns TRUE else FALSE
  // Eg: WHEN NO_WALL shall return TRUE if there is no obstacle
  //       WHEN WALL shall return FALSE if there is no obstacle
  switch (input_sensor)
  {
    case  WALL:                                             
      return_val = digitalRead(WALL_Input);  //value returned by IR sensor is true the wall is present
      Serial.print("WALL:  ");
      Serial.println(return_val);
      return return_val;
      break;
    case  NO_WALL:
      return_val = !digitalRead(WALL_Input); // value returned from IR sensor is false the wall is not present
      Serial.print("NO_WALL:  ");
      Serial.println(return_val);
      return return_val;
      break;
    case  LIGHT:                                  //light is detected by LDR then it will  return true condition 
      return_val = digitalRead(LIGHT_Input);
      return_val;
      Serial.print("LIGHT:  " );
      Serial.println(return_val);
      return return_val;
      break;
    case  DARK:
      return_val = !digitalRead(LIGHT_Input);           //returning false condition i.e., light is not detected
      Serial.print("DARK:  ");
      Serial.println(return_val);
      return return_val;
      break;
    case  RAIN:
      return_val = digitalRead(RAIN_Input);                 //will read the value by RAIN SENSoR
      Serial.print("RAIN:  ");
      Serial.println(return_val);
      return return_val;
      break;
    case  TOUCH:
      return_val = digitalRead(TOUCH_Input);          //this will read the touch sensor output once the touch is detected it will return the value
      Serial.println("TOUCH");
      Serial.println(return_val);
      return return_val;
      break;
    case  SOUND:
      return_val = digitalRead(SOUND_Input);        //sound value is detected by the sound sensor
      Serial.println("SOUND");
      Serial.println(return_val);
      break;
  }
}
char Write_OUTPUT(char output_actuator)           // Call this function to get all output actuated
{
  // Check if the wait_for command is on
  // Wait untill the flag Historic_output is set to TRUE indicating that the WAIT_FOR condition is met else restart from where the WAIT_FOR command started.
  if (Wait_for_flag  == TRUE && Historic_output == FALSE)
  {
    command_number = wait_for_command_number;
  }

  // Return TRUE if input pointed command returns TRUE else FALSE
  // Eg: WHEN NO_WALL shall return TRUE if there is no obstacle
  //     WHEN WALL shall return FALSE if there is no obstacle
  // This set of outputs contain only final output set (SECONDS, FOOT and DEGREES are taken care as part of loopins)

  //Digit_Number = 0; // Clear this flag to make sure the numbers computed on
  // input/outputs are cleared before executing next task
  switch (output_actuator)
  {
      int wall;
    case FORWARD:

      if (Historic_output == TRUE)                          ////motor will go forward only when next command is not FOR or else it will stop
      {                                                     
        Serial.println("motor FORWARD on");                
        Serial.println("Rx_data[command_number]");
        Serial.println(Rx_data[command_number]);
        command_number++;
        if (Rx_data[command_number] != FOR) // == NO_COIN || WHEN)      
        {                                                             
          wall = fun_wall();                              
          while (wall != 1)                            
          {
            Motor(1, 0, MOTOR_FORWARD);
            Motor(2, 0, MOTOR_FORWARD);
            wall = fun_wall();                       //this function will be continously checking if the wall is present or not
          }
          Motor(1, 0, MOTOR_STOP);
          Motor(2, 0, MOTOR_STOP);
        }
        else
        {
          command_number--;
        }
      }
      else
      {
        Motor(1, 0, MOTOR_STOP);
        Motor(2, 0, MOTOR_STOP);
        Serial.println("motor FORWARD OFF");            
      }
      break;

    case REVERSE:
      if (Historic_output == TRUE)
      {
        command_number++;
        if (Rx_data[command_number] != FOR) // if (Rx_data[command_number] == NO_COIN)
        {
          Motor(1, 0, MOTOR_REVERSE);
          Motor(2, 0, MOTOR_REVERSE);           //motor will go reverse only when next command is not FOR or else it will stop 
          wheel(200, 200);
        }
        else
        {
          command_number--;
        }
      }
      else
      {
        Motor(1, 0, MOTOR_STOP);
        Motor(2, 0, MOTOR_STOP);
      }
      break;

    case  RIGHT :
      if (Historic_output == TRUE)              //motor will turn right only when next command is not FOR or else it will stop
      {
        command_number++;
        if (Rx_data[command_number] != FOR) // if (Rx_data[command_number] == NO_COIN)
        {
          Motor(1, 0, MOTOR_RIGHT);
          Motor(2, 0, MOTOR_RIGHT);
          Serial.println("motor right");

          wall = fun_wall();              //this function will be continously checking if the wall is present or not
          Serial.println("wall");
          Serial.println(wall);
          while (wall != 1)
          {
            Serial.println("motor forward");
            Motor(1, 0, MOTOR_FORWARD);
            Motor(2, 0, MOTOR_FORWARD);
            wall = fun_wall();             //this function will be continously checking if the wall is present or not
          }
          Serial.println("motor off");
          Motor(1, 0, MOTOR_STOP);
          Motor(2, 0, MOTOR_STOP);
        }
        else
        {
          command_number--;
        }
      }
      else
      {
        Motor(2, 0, MOTOR_STOP);
        Motor(1, 0, MOTOR_STOP);
      }
      break;

    case  LEFT :                            //motor will turn right only when next command is not FOR or else it will stop
      if (Historic_output == TRUE)
      {
        command_number++;
        if (Rx_data[command_number] != FOR) //if (Rx_data[command_number] == NO_COIN)
        {
          Motor(2, 0, MOTOR_LEFT);
          Motor(1, 0,  MOTOR_LEFT);

          char wall = fun_wall();            //this function will be continously checking if the wall is present or not
          while (wall != 1)
          {
            Motor(1, 0, MOTOR_FORWARD);
            Motor(2, 0, MOTOR_FORWARD);
            wall = fun_wall();               //this function will be continously checking if the wall is present or not
          }
          Motor(1, 0, MOTOR_STOP);
          Motor(2, 0, MOTOR_STOP);
        }

        else
        {
          command_number--;
        }
      }
      else
      {
        Motor(1, 0, MOTOR_STOP);
        Motor(2, 0, MOTOR_STOP);
      }
      break;

    case  BLINK_EYES :
      Serial.print("Historic_output at blink: ");     // blink the eyes for defined time period.
      Serial.println(Historic_output);
      if (Historic_output == TRUE)
      {
        Serial.println("blink eyes on");
        digitalWrite(EYES1_Output, LOW );             //blinking the eyes for every 100ms
        digitalWrite(EYES2_Output, LOW);
        F_delay(100);           // Delay in milliseconds
        digitalWrite(EYES1_Output, HIGH);
        digitalWrite(EYES2_Output, HIGH);
        F_delay(100);
      }
      else
      {
        digitalWrite(EYES1_Output, HIGH);               //if light has not detected then it will not blink
        digitalWrite(EYES2_Output, HIGH);
        Serial.println("blink eyes off");
      }
      break;

    case  BUZZER :
      Serial.print("Historic_output at buzz: ");    //this is for checking which sound is to be done ny buzzer
      Serial.println(Historic_output);

      if (Historic_output == TRUE)
      {
        command_number++;
        switch (Rx_data[command_number])        //will check for the cases
        {
          case ONE:
            play_melody();                //to play song
            break;
          case TWO:
            play_alaram();                //this case is for alaram tone,will enter into the function
            break;
          case THREE:
            play_starwar();               //play starwar tone
            break;
          case FOUR:
            playtwinkle ();              //play rhymes
            break;
          case FIVE:
            //playsupermario();
            break;
          default:
            digitalWrite(BUZZER_Output, HIGH);
            Serial.println("BUZZER_ON");
        }
      }
      else
      {
        digitalWrite(BUZZER_Output, LOW);
        Serial.println("BUZZER_OFF");
      }
      break;

    case  ROTATE :            //•	Rotations one wheel should forward and another should reverse
      if (Historic_output == TRUE)
      {
        command_number++;
        switch (Rx_data[command_number])
        {
          case LEFT:
            rotate_left();        //entering into the function to rotate left
            break;
          case RIGHT:
            rotate_right();        //entering into the function to rotate left
            break;
          default:
            rotate_both();         //entering into the function to rotate on both sides
            break;
        }
      }
      else
      {
        Motor(1, 0, MOTOR_STOP);
        Motor(2, 0, MOTOR_STOP);
      }
      break;

    case  B_DAY :
      if (Historic_output == TRUE)            
      {
        F_Birthday_Buz();           //enter into the function to play the birthday tone
      }
      else
      {
        digitalWrite(BUZZER_Output, LOW);
        Motor(1, 0, MOTOR_STOP);          //motor will stop
        Motor(2, 0, MOTOR_STOP);
      }
      break;

    case  DANCE:
      if (Historic_output == TRUE)
      {
        F_DANCE();
      }
      else
      {
        digitalWrite(BUZZER_Output, LOW);
        digitalWrite(EYES1_Output, HIGH);
        digitalWrite(EYES2_Output, HIGH);
        Motor(1, 0, MOTOR_STOP);
        Motor(2, 0, MOTOR_STOP);
      }
      break;
  }
}

/*void F_FOR()                                      // Call this function to process FOR keyword as a set
  {
  char Number_to_action;
  /* Extract numbers and perform action*/
/* SECONDS,MINUTES,HOURS,ROTATIONS,FOOT,DEGREES*/
/* if (Rx_data[command_number] != SECONDS   ||
     Rx_data[command_number] != MINUTES   ||
     Rx_data[command_number] != HOURS     ||
     //Rx_data[command_number] != ROTATIONS ||
     Rx_data[command_number] != FOOT      ||
     Rx_data[command_number] != DEGREES   )
  {
   /*Extract first byte*/
/* Number_to_action = Rx_data[command_number] << 7; // Take MSD
  }
  /* Check for next command eighter a number or keyword*/
/* if (Rx_data[command_number + 1] != SECONDS   ||
     Rx_data[command_number] != MINUTES   ||
     Rx_data[command_number] != HOURS     ||
     //Rx_data[command_number] != ROTATIONS ||
     Rx_data[command_number] != FOOT      ||
     Rx_data[command_number] != DEGREES   )
  {
   /*Extract first byte*/
/* command_number++;
  Serial.println(command_number);
  Number_to_action = Number_to_action || Rx_data[command_number];  // Take LSD and add to MSDigit
  }
  /* Call functions with different keywords*/
/* switch (Rx_data[command_number])
  {
   case  SECONDS :
     Elapse_Time(Number_to_action);            // Call this function to elapse the time in seconds
     break;

   case  MINUTES :
     Elapse_Time(Number_to_action * 60);      // Call this function to elapse the time in seconds
     break;

   case  HOURS :
     Elapse_Time(Number_to_action * 60 * 60);    // Call this function to elapse the time in seconds
     break;

   /*case  ROTATIONS :
     Elapse_Rotations(Number_to_action);              // Call this function to elapse number of rotations
     break;*/

/*case  FOOT :
  Elapse_Length(Number_to_action);              // Call this function to elapse number of foots
  break;

  case  DEGREES :
  Elapse_Angle(Number_to_action);              // Call this function to elapse number of degrees
  break;
  }
  }*/
/*void F_STOP()
  {
  if (Historic_output == TRUE)
  {
    Serial.println("STOP");
  }
  else
  {
    Serial.println("NO STOP");
  }
  // Set all outputs to FALSE
  }*/

/*void F_NUMBERS(char input_number)
  {
  if (Digit_Number == 0)
  { // Fresh digit, MSD
    Numbers = input_number;
  }

  else if (Digit_Number == 1)                       // Mid digit
  {
    Numbers = (Numbers * 10) + input_number;      // Scanner scans first value as MSD, hence multiply previous number with 10 to shift to tens
  }

  else if (Digit_Number == 2)                       // Last digit LSD
  {
    Numbers = (Numbers * 10) + input_number;    // Scanner scans first value as MSD, hence multiply previous number with 10 to shift to tens
  }
  Digit_Number++;                                   // To know what digit it shall be taken for multiplication factor
  }*/






void F_delay(unsigned int delay_value)
{
  unsigned int i;
  for (i = 0; i < delay_value; i++);
}

char Execute_24_commands()
{
  for (i = 0; i <= 23; i++)   //contains all 24 coin commands
  {
    switch (Rx_data[command_number])
    {

      /* KEY WORDS*/
      case  WHEN :
        Serial.println("Rx_data[command_number]");
        Serial.println(Rx_data[command_number]);
        command_number++;
        Historic_output = FALSE;
        Current_output = FALSE; // Clearing flags before going to next inputs/commands
        //Input_Status = Process_input(Rx_data[command_number]);                // Process full set of input commands untill finds
        // keyword or output and increment command pointer
        Serial.println("WHEN");
        Serial.println("Rx_data[command_number]");
        Serial.println(Rx_data[command_number]);
        break;

      case THEN:                                  //Then is a keyword which should come after inputs and before outputs.
        command_number++;
        Serial.println("Rx_data[command_number]");
        Serial.println(Rx_data[command_number]);
        Serial.println("THEN");
        break;

      case WAIT_FOR:
        //1: WAIT_FOR key word used with numerical values succeeded with seconds (Input crtiteria)
        //2: WAIT_FOR keyword can also be used with multiple input conditions with logical OR/AND expressions.
        //3: WAIT_FOR keyword can have maximum of 2 logical operands. Eg: WAIT_FOR WALL AND SOUND_Input AND LIGHT_Input
        //4: command_Number after this function execution returns updated command number which will be pointing to next command
        //5: WAIT_FOR can only be with inputs. but not to merge with output commands (WAIT_FOR 10 Seconds)
        /*Set a flag for wait_for to TRUE to know that we are in WAIT-FOR condition either in input or output*/
        /*If WAIT_FOR is with inputs then wait*/
        /*If WAIT_FOR is with outputs then wait*/
        Wait_for_flag = TRUE;
        wait_for_command_number = command_number;
        command_number++;                                              // Got to next command with flag set to true and clear once the action have been taken.
        //              F_WAIT_FOR();                                                         // Call function for WAIT_FOR command set execution
        break;

      case FOR:
        Serial.println("FOR");
        /* FOR keyword can only be used as an OUTPUT condition*/
        /* Eg: WHEN LIGHT_Input THEN LED1-ON FOR 99 SECONDS*/
        /* Maximum number of digit that can be programmed is only 999*/
        /* FOR can have SECONDS,MINUTES,HOURS,ROTATIONS,FOOT,DEGREES after numbers */
        /* FOR command is implicitly taken care in program, hence just increment the command number*/
        command_number++;
        break;

      case OR:
        /* Maximum number of OR used is limited to one
           OR can be used in only input commands like WHEN LIGHT_Input OR SOUND_Input THENBUZZER_Output1
           When OR command enountered, Historical value ORed with current value of output
        */
        command_number++;                                             // Get next input and assign to current output
        Current_output = Read_INPUT(Rx_data[command_number]);
        Historic_output = Historic_output || Current_output;
        command_number++;                                             // Go to next command
        break;

      case AND:
        /* Maximum number of OR used is limited to one
           OR can be used in only input commands like WHEN LIGHT_Input OR SOUND_Input THENBUZZER_Output1
           When OR command enountered, Historical value ORed with current value of output
        */
        command_number++;                                             // Get next input and assign to current output
        Current_output = Read_INPUT(Rx_data[command_number]);
        Historic_output = Historic_output && Current_output;
        command_number++;                                             // Go to next command
        break;

      case NEXT:
        command_number++;
        Historic_output = FALSE;
        Current_output = FALSE; // Clearing flags before going to next execution freshly
        break;

      case GO:
        command_number++;
        break;

      case ELSE:
        command_number++;
        break;

      case STOP:
        /*Stop all actuators, set Historic and current values to FALSE */
        Historic_output = FALSE;
        Current_output = FALSE; // Clearing flags before going to next execution freshly
        F_STOP(); // calling stop function
        command_number++;
        break;

      case REPEAT:
        command_number = 0;
        Execute_24_commands();
        /*If REPEAT exists at the end of commands then execute the task repeatedly, inputs shall be processed every time*/
        /*If not REPEAT then task shall execute only once and then stop*/
        /* Good Eg: Task_1 Task_2 REPEAT */
        /*Bad Eg: Task_1 REPEAT Task_2 (Task_2 never executes)*/
        /*Reset command number to 24*/
        //commands_debug = 24;
        break;

      // KEYWORDS
      //-----------------------------------------------------------------------------------------------------------------------
      /* INPUTS*/

      case WALL:
        /*This case used for simple WALL sensor read as input*/
        /*Can be used in WHEN WALL THEN LED1-ON*/
        /*The current value will be stored in historic output to check next command is AND or OR*/
        /*For now, we will use only one AND or OR as logical operand*/
        //printf("WALL_Input\t");
        Historic_output = Read_INPUT(WALL);                                  // Get value of WALL sensor
        command_number++;                                                    //
        break;

      case NO_WALL:
        Historic_output = Read_INPUT(NO_WALL);          //calling the function 
        command_number++;
        break;

      case LIGHT:
        Historic_output =Read_INPUT(LIGHT);                   //will get the value of light sensor and incremented to next command
        Serial.print("Historic_output at LIGHT: ");
        Serial.println(Historic_output);
        command_number++;
        Serial.println("Rx_data[command_number]");
        Serial.println(Rx_data[command_number]);
        break;
      case DARK:
        Historic_output = Read_INPUT(DARK);               //will get the value of light sensor 
        command_number++;
        break;

      case RAIN:
        Historic_output = Read_INPUT(RAIN);               //will get the value of rain sensor
        command_number++;
        break;

      case TOUCH:
        Historic_output = Read_INPUT(TOUCH);                //will get the value of TOUCH sensor
        command_number++;
        break;

      case SOUND:                                               //will get the value of SOUND sensor
        Historic_output = Read_INPUT(SOUND);
        command_number++;
        break;

      // INPUTS
      //---------------------------------------------------------------------------------------------------------------------------
      /* OUTPUTS*/

      case FORWARD:
        Serial.print("Historic_output at FORWARD: ");
        Serial.println(Historic_output);
        /*This case used for simple WALL sensor read as input*/
        /*Can be used in WHEN WALL THEN LED1-ON*/
        /*The current value will be stored in historic output to check next command is AND or OR*/
        /*For now, we will use only one AND or OR as logical operand*/
        Write_OUTPUT(FORWARD);
        command_number++;
        Serial.println("Rx_data[command_number]");
        Serial.println(Rx_data[command_number]);
        break;

      case REVERSE:
        Write_OUTPUT(REVERSE);        //based on the condition inside the function the motor will work and it will move on to next command
        command_number++;
        break;

      case RIGHT:                     //based on the condition inside the function the motor will work and it will move on to next command
        Write_OUTPUT(RIGHT);
        command_number++;
        break;

      case LEFT:                      //based on the condition inside the function the motor will work and it will move on to next command

        f_function_seconds(var)(LEFT);
        command_number++;
        break;

      case BLINK_EYES:                //based on the condition inside the function the eyes will blink and it will move on to next command
        Write_OUTPUT(BLINK_EYES);
        command_number++;
        break;

      case BUZZER:                //different types of buzzer sounds are available 
        Write_OUTPUT(BUZZER);
        command_number++;
        break;

      case B_DAY:
        Write_OUTPUT(B_DAY);     //enter into the function to Execute birthday tone
        command_number++;
        break;

      case DANCE:             //perform dance operation by moving bot front and back, blinking eyes and producing a music through buzzer.
        Write_OUTPUT (DANCE);
        command_number++;
        break;

      case ROTATE:
        Write_OUTPUT (ROTATE);  // Send Numbers calculated before
        command_number++;
        break;

      // OUTPUTS
      //---------------------------------------------------------------------------------------------------------------------------
      /* NO_COIN*/

      case NO_COIN:
        command_number++;
        Serial.println("Rx_data[command_number]");
        Serial.println(Rx_data[command_number]);
        break;

      // NO COIN

      /*NUMBERS*/
      /*Store number in Numbers variable*/
      /*Variable Numbers will be holding the value till it uses somewhere as an action and the scope of that value ends there*/
      /*Combine numbers untill 3 numbers in numbers representing word 0 to 999 */
      /*Clear Numbers variable once the action on this number is completed*/
      /*Set Number_Flag to TRUE when command encountered number in series to aid next command action*/
      /*Number can be used only in outputs, WHEN LIGHT_Input THEN FORWARD 10 SECONDS*/
      case ONE:
        var = F_NUMBERS(1);  //calling the function
        //this is a number to indicate for how many times the output command should perform its task.
        command_number++;
        //              printf("%d",Numbers);
        Serial.println("Rx_data[command_number]");
        Serial.println(Rx_data[command_number]);
        break;

      case TWO:             //this is a number to indicate for how many times the output command should perform its task.
        var = F_NUMBERS(2);
        command_number++;
        //              printf("%d",Numbers);
        break;

      case THREE:         //this is a number to indicate for how many times the output command should perform its task.
        var = F_NUMBERS(3);
        command_number++;
        //              printf("%d",Numbers);
        break;

      case FOUR:      //this is a number to indicate for how many times the output command should perform its task.
        var = F_NUMBERS(4);
        command_number++;
        break;

      case FIVE:      //this is a number to indicate for how many times the output command should perform its task.
        var = F_NUMBERS(5);
        command_number++;
        Serial.println("Rx_data[command_number]");
        Serial.println(Rx_data[command_number]);
        break;

      case SIX:         //this is a number to indicate for how many times the output command should perform its task.

        var = F_NUMBERS(6);
        command_number++;
        break;

      case SEVEN:         //this is a number to indicate for how many times the output command should perform its task.
        var = F_NUMBERS(7);
        break;

      case EIGHT:         //this is a number to indicate for how many times the output command should perform its task.

        var = F_NUMBERS(8);
        command_number++;
        Serial.println("Rx_data[command_number]");
        Serial.println(Rx_data[command_number]);
        break;

      case NINE:      //this is a number to indicate for how many times the output command should perform its task.
        var = F_NUMBERS(9);
        command_number++;
        break;

      case ZERO:          //this is a number to indicate for how many times the output command should perform its task.

        var = F_NUMBERS(0);
        command_number++;
        break;
      /*NUMBERS*/

      case SECONDS:
        /*Sense if the control is in Input or output session*/
        /*Call delay in seconds*/
        /*Eg: WHEN 5 SECONDS THENBUZZER_Output/ WHEN LIGHT_Input THENBUZZER_Output 50 SECONDS*/
        // Elapse_Time(Numbers);  // Send Numbers calculated before
        f_function_seconds(var);
        command_number++;
        break;

      case MINUTES:
       f_function_minutes(var); //Elapse_Time(Numbers * 60);  // Send Numbers calculated before multipleid by 60 for seonds conversion
        command_number++;
        break;

      case HOURS:
        //Elapse_Time(Numbers * 60 * 60);  // Send Numbers calculated before multipleid by 60*60 for seonds conversion
        command_number++;
        break;

      /* case ROTATE:
         Elapse_Rotations(Numbers);  // Send Numbers calculated before
         command_number++;
         break;*/

      case FOOT:
        // Elapse_Length(Numbers);  // Send Numbers calculated before
        F_foot(var);
        command_number++;
        break;

      case DEGREES:
        //        Elapse_Angle(Numbers);  // Send Numbers calculated before
        command_number++;
        break;

        //case DANCE:
        //F_DANCE();
        //command_number++;
        //break;
        // case  DISPLAY_ERROR :
        // Display error if battery low
        // Display error if sensors/outputs are not working
        // Checksum error
        // Go to IDLE
        break;

    } // Switch end for commands execution
  }
}
