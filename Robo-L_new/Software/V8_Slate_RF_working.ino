// V8_RNC_17_NOV_2017 - Slate transmiting data 24 times succesfully. (Need to check state machine for completeness of transitions)

#include <VirtualWire.h>  // you must download and install the VirtualWire.h to your hardware/libraries folder
#undef int
#undef abs
#undef double
#undef float
#undef round
/*    Rev 1.0   13 - April - 2017    RC
  ;    Values of scanned holes are displayed on screen as zeros and ones.
  ;    Rev 2.0   14 - April - 2017    RC
  ;    Values are displayed with checksum.
  ;    Rev 2.0   20 - April - 2017    RC
  ;    Added all commands in header file
  ;    Rev 5.0   01 - Oct - 2017    RC
  ;    Succesfully reading the data from holes and displaying on com port
  ;    Rev 6.0   04 - OCT - 2017    RC
  ;    Work on fixing the problem on reading data from holes
  ;    Rev 7.0   12 - NOV - 2017    RC
  ;    Working code for slate reading commands with veeresh help
  ;    Rev 8.0   12 - NOV - 2017    RC
  ;    Converting raw data of 18 bytes in to commands.
  ---------------------------------------------------------------------------*/

// GLOBALS Used, reviewed variables
unsigned char       Ref_IR, Start_IR, End_IR, Save_Button_1, Save_Button_2, Save_Button_3, Save_Button_4, Message_Sent;
unsigned char       TX_Ready_data[24], Current_Temp_Command[3000]; //This will hold command each time as it is computed
enum State          {IDLE = 1, START_SCAN, SEND_MESSAGE, DISPLAY_ERROR, SAVE_PROGRAM};
unsigned char Final_Commands[18];
const unsigned char MASK_ARRAY[8] = {128, 64, 32, 16, 8, 4, 2, 1};
unsigned char Tx_Index = 0;
unsigned char Cm_Index = 0;
unsigned char Bit_Index = 0;

//--------------------------------------------------------------------------------------------------------------
// Need to check these variables.

unsigned char Error_in_row_1, Error_in_row_2, Error_in_row_3, Error_in_row_4, Commands, Rules_to_check, Error_Status;
unsigned char Status = 1, i, NO_ERROR = 0, Next_Reading = 0;
unsigned char INVALID_COMMAND;
//--------------------------------------------------------------------------------------------------------------
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
/* Bit masks - used to test/set/clear specific bit positions */
#define BIT0   0x0001
#define BIT1   0x0002
#define BIT2   0x0004
#define BIT3   0x0008
#define BIT4   0x0010
#define BIT5   0x0020
#define BIT6   0x0040
#define BIT7   0x0080
#define BIT8   0x0100
//KEY WORDS
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
//INPUTS
#define WALL 52
#define NO_WALL 25
#define LIGHT 44
#define DARK 41
#define RAIN 28
#define TOUCH 49
#define SOUND 56
//OUTPUTS
#define FORWARD 50
#define REVERSE 26
#define RIGHT 6
#define LEFT 3
#define BLINK_EYES 10
#define BUZZ 14
#define B_DAY 35
#define SECONDS 38
#define MINUTES 11
#define HOURS 22
#define ROTATIONS 19
#define FOOT 60
#define DEGREES 57
#define DANCE 34
//NUMBERS
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
// Define IRs for white slate
#define Ref_IR_Read   A0
#define Start_IR_Read A10
#define End_IR_Read   A9
#define IR_1          A1
#define IR_2          A2
#define IR_3          A3
#define IR_4          A4
#define IR_5          A5
#define IR_6          A6
#define IR_7          A7
#define IR_8          A8
#define Vcontrol      18
#define Save_Button_1_Read      5
#define Save_Button_2_Read      4
#define Save_Button_3_Read      3
#define Save_Button_4_Read      2

#define LED_1_1_Green      6
#define LED_2_1_Green      7
#define LED_3_1_Green      8
#define LED_4_1_Green      9

unsigned char TEST_Ready_data[30] = {WHEN,   WALL,   THEN,   FORWARD, NO_COIN, NO_COIN,
                                     NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN,
                                     NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN,
                                     NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN, NO_COIN,
                                     0xFF, 0xFF
                                    };
void setup() {

  //------------------------------------------ For Virtual wire-----------------
  // Initialise the IO and ISR
  vw_set_ptt_inverted(true); // Required for RF Link module
  vw_setup(2000);                 // Bits per sec
  vw_set_tx_pin(12);                // pin 3 is used as the transmit data out into the TX Link module, change this as per your needs
  //-----------------------------------------------------------------------------

  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(A7, INPUT_PULLUP);
  pinMode(A8, INPUT_PULLUP);
  pinMode(A9, INPUT_PULLUP);
  pinMode(A10, INPUT_PULLUP);
  pinMode(18, OUTPUT); //IR TX ENABLE
  pinMode(20, OUTPUT); //IR TX ENABLE

  digitalWrite(18, HIGH); // IR Tx Enable
  Status = IDLE;
  // put your setup code here, to run once:
  Serial.begin(9600);                                                          // initialize serial:
  Serial.println("RESTART");
  Serial.flush();

} // SETUP End

void loop() {

  switch (Status)                         // STATE MACHINE
  {
    //----------------------------------------------------------------- IDLE -----------------------------------------------------------------
    case  IDLE : {
        // Read all sensor values and load to buffer
        // Jump to START_SCAN if Start_IR changed status from CLOSE to OPEN
        // Jump to SAVE_PROGRAM if Save_Button Pressed and scanned program is different than the one in EEPROM

        Enable_Slider_Tx_IRs();               // Enable Slider to read
        Read_Ref_Start_End_IRs();             // Read all IRs
        Read_Save_Buttons();                  // Read 4 save buttons
        // Save_Button_pressed();                // Check if save buttons pressed?
        // Check for change in Start_IR to check scanning bar started sliding.
        while (Start_IR == CLOSE && End_IR == OPEN)         // Wait for read condition for initial setup. Slider is at start position
        {
          Read_Ref_Start_End_IRs();             // Read all IRs
          Status  = START_SCAN;
          Message_Sent = 0;                     // For fresh message to be sent.
        }
        break;

      } // IDLE state ends
    //----------------------------------------------------------------- START_SCAN -----------------------------------------------------------------
    case  START_SCAN : {
        Serial.print("START_SCAN:");
        /*Scan all holes/ convert them in to commands/ Check validity/ keep commands ready to send*/
        Scan_holes(); // Get final 24 commands in TX_Ready_data array of 24 elements.
        print_data();
        Status  = SEND_MESSAGE; // Temporary setting
        break;
      } // Start_Scan ends

    //----------------------------------------------------------------- SEND_MESSAGE -----------------------------------------------------------------
    case  SEND_MESSAGE :
      Serial.print("SEND_MESSAGE");
      // Send message if no errors else change status to DISPLAY_ERROR
      // Check_Errors(); // Need to fix
      digitalWrite(LED_1_1_Green, HIGH);
      digitalWrite(LED_2_1_Green, HIGH);
      digitalWrite(LED_3_1_Green, HIGH);
      digitalWrite(LED_4_1_Green, HIGH);

      Call_virtual_wire();       // Send message 24 times which is ready to be sent in buffer and set a Message_Sent flag to HIGH
      digitalWrite(LED_1_1_Green, LOW);
      digitalWrite(LED_2_1_Green, LOW);
      digitalWrite(LED_3_1_Green, LOW);
      digitalWrite(LED_4_1_Green, LOW);
      Status  = IDLE;
      /* Error_Status = Check_Errors();

        if (Error_Status == NO_ERROR)
        {
         Status = SEND_MESSAGE;
        }
        else
        {
         Status = DISPLAY_ERROR;
        } */ // Include later.
      // Display GREEN in all 4 rows
      break;

    //----------------------------------------------------------------- DISPLAY_ERROR -----------------------------------------------------------------
    case  DISPLAY_ERROR :
      Serial.println("DISPLAY_ERROR\n");
      /* Display error as per the error message (Error_row_1,  Error_row_2, Error_row_3, Error_row_4) and small buzzer
      */
      // #Error Error_Buzzer(Error_Status);  // Beep tone to indicate invalid commands.
      // #Error Error_LEDs(Error_Status);    // All LEDs to RED to indicate invalied commands.
      Error_Status = NO_ERROR;     // Clear error for next readings
      Status = IDLE;      // Jump to IDLE State
      break;

    //----------------------------------------------------------------- SAVE_PROGRAM -----------------------------------------------------------------
    case  SAVE_PROGRAM :

      //  Serial.println("SAVE_PROGRAM\n");
      // Save program in temp_memory if no Save_Button pressed
      // Save program in Button_1_memory if Save_Button_1 pressed
      // Save program in Button_2_memory if Save_Button_2 pressed
      // Save program in Button_3_memory if Save_Button_3 pressed
      // Save program in Button_4_memory if Save_Button_4 pressed

      break;
  }
  //----------------------------------------------------------------- END OF STATE MACHINE---------------------------------------------------------------
  // #ifdef TEST_DEV
  // #endif
} // LOOP End


/* TASKS
  1 Display values in array - DONE
  2 Check values are displayed from Scan_holes function. - DONE
  3 Place them in proper array of 24 values + checksum.  - DONE
  4 Implement 10 time readings and taking average using SIMULATE #defines - DONE
  5 Define each coin's data - DONE
  6 Define different possible errors, not a command, Sytax error in task etc DONE
  7 Check on Rules and set errors for different row.
  8 Make state machine working with all possible combinations
  9 Determine complete set of errors in error function, combine all errors bitwise.
  10
  Tasks in hardware
  1. Remove SIMULATE and fix all errors
  2. Assign port numbers for all IR wrapper functions
*/
/*------------------Informations---------------------------
  IR LEDs : 9
  All array starts from zero
  24 bytes and 2 bytes of checksum at the end formatted for data commands to send
  ------------------Flow------------------------------------
  Read 144 bit values
  Create a matrix
  Derive values
  State machine
*/
/* Valid coins

  KEY WORDS
  LSB
  0 0 0   WHEN
  0 0 1   32
  0 0 0   THEN
  1 0 0   8
  0 0 0   WAIT-FOR
  0 1 1   48
  0 0 0   FOR
  1 1 0   24
  0 0 1   OR
  0 0 0   4
  1 0 0   AND
  0 0 0   1
  1 1 0   NEXT
  0 1 1   51
  0 1 1   STOP
  1 1 0   30
  0 1 1   REPEAT
  1 0 1   46
  1 1 0   RETURN
  1 0 1   43
  0 0 1   GO
  0 1 0   20
  1 0 0   ELSE
  0 1 0   17
  INPUTS
  0 0 1   WALL
  0 1 1   52
  1 0 0   NO WALL
  1 1 0   25
  0 0 1   LIGHT
  1 0 1   44
  1 0 0   DARK
  1 0 1   41
  0 0 1   RAIN
  1 1 0   28
  1 0 0   TOUCH
  0 1 1   49
  0 0 0   SOUND
  1 1 1   56
  OUTPUTS
  0 1 0   FORWARD
  0 1 1   50
  0 1 0   REVERSE
  1 1 0   26
  0 1 1   RIGHT
  0 0 0   6
  1 1 0   LEFT
  0 0 0   3
  0 1 0   BLINK EYES
  1 0 0   10
  0 1 1   BUZZ
  1 0 0   14
  1 1 0   B'DAY
  0 0 1   35
  0 1 1   SECONDS
  0 0 1   38
  1 1 0   MINUTES
  1 0 0   11
  0 1 1   HOURS
  0 1 0   22
  1 1 0   ROTATIONS
  0 1 0   19
  0 0 1   FOOT
  1 1 1   60
  1 0 0   DEGREES
  1 1 1   57
  0 1 0   DANCE
  0 0 1   34
  NUMBERS
  1 0 1   0z
  0 0 1   37
  1 0 1   1
  1 0 0   13
  1 0 1   2
  0 1 1   53
  1 0 1   3
  1 1 0   29
  1 1 1   4
  0 1 1   55
  1 1 1   5
  1 1 0   31
  1 1 1   6
  0 0 1   39
  1 1 1   7
  1 0 0   15
  0 1 1   8
  1 1 1   62
  1 1 0   9
  1 1 1   59
  1   1   1       NO COIN
  1   1   1       63
*/

//-----------------------------------------------------------------------------------------------------------
/* To read End IR sensor using Arduino*/
char F_End_IR()
{
  char End_IR;
  // End_IR = digitalRead();
  return End_IR;
}
//-----------------------------------------------------------------------------------------------------------
/* To read Start IR sensor using Arduino*/
char F_Start_IR()
{
  char Start_IR = CLOSE;
  // Start_IR = digitalRead();
  return Start_IR;
}
//-----------------------------------------------------------------------------------------------------------
/* To read button_1 sensor using Arduino*/
char F_Save_Button_1(void)
{
  char Save_Button_1 = TRUE;
  // End_IR = digitalRead();
  return Save_Button_1;
}
//-----------------------------------------------------------------------------------------------------------
/* To read button_2 sensor using Arduino*/
char F_Save_Button_2(void)
{
  char Save_Button_2 = TRUE;
  // End_IR = digitalRead();
  return Save_Button_2;
}
//-----------------------------------------------------------------------------------------------------------
/* To read button_3 sensor using Arduino*/
char F_Save_Button_3(void)
{
  char Save_Button_3 = TRUE;
  // End_IR = digitalRead();
  return Save_Button_3;
}
//-----------------------------------------------------------------------------------------------------------
/* To read button_4 sensor using Arduino*/
char F_Save_Button_4(void)
{
  char Save_Button_4 = TRUE;
  // End_IR = digitalRead();
  return Save_Button_4;
}

//-----------------------------------------------------------------------------------------------------------
/* To read each row IR sensor using Arduino*/
char F_Read_IR_Row_1()
{
  char Read_IR_Row_1 = 0;
  // End_IR = digitalRead();
#ifdef Test_Bit_1
  Read_IR_Row_1 = 1;
#endif
  return Read_IR_Row_1;

}
//-----------------------------------------------------------------------------------------------------------
/* To read each row IR sensor using Arduino*/
char F_Read_IR_Row_2()
{
  char Read_IR_Row_2 = 0;
  // End_IR = digitalRead();
#ifdef Test_Bit_1
  Read_IR_Row_2 = 1;
#endif
  return Read_IR_Row_2;
}
//-----------------------------------------------------------------------------------------------------------
/* To read each row IR sensor using Arduino*/
char F_Read_IR_Row_3()
{
  char Read_IR_Row_3 = 0;
  // End_IR = digitalRead();
#ifdef Test_Bit_1
  Read_IR_Row_3 = 1;
#endif
  return Read_IR_Row_3;
}
//-----------------------------------------------------------------------------------------------------------
/* To read each row IR sensor using Arduino*/
char F_Read_IR_Row_4()
{
  char Read_IR_Row_4 = 0;
  // End_IR = digitalRead();
#ifdef Test_Bit_1
  Read_IR_Row_4 = 1;
#endif
  return Read_IR_Row_4;
}
//-----------------------------------------------------------------------------------------------------------
/* To read each row IR sensor using Arduino*/
char F_Read_IR_Row_5()
{
  char Read_IR_Row_5 = 0;
  // End_IR = digitalRead();
#ifdef Test_Bit_1
  Read_IR_Row_5 = 1;
#endif
  return Read_IR_Row_5;
}
//-----------------------------------------------------------------------------------------------------------
/* To read each row IR sensor using Arduino*/
char F_Read_IR_Row_6()
{
  char Read_IR_Row_6 = 0;
  // End_IR = digitalRead();
#ifdef Test_Bit_1
  Read_IR_Row_6 = 1;
#endif
  return Read_IR_Row_6;
}
//-----------------------------------------------------------------------------------------------------------
/* To read each row IR sensor using Arduino*/
char F_Read_IR_Row_7()
{
  char Read_IR_Row_7 = 0;
  // End_IR = digitalRead();
#ifdef Test_Bit_1
  Read_IR_Row_7 = 1;
#endif
  return Read_IR_Row_7;
}
//-----------------------------------------------------------------------------------------------------------
/* To read each row IR sensor using Arduino*/
char F_Read_IR_Row_8()
{
  char Read_IR_Row_8 = 0;
  // End_IR = digitalRead();
#ifdef Test_Bit_1
  Read_IR_Row_8 = 1;
#endif
  return Read_IR_Row_8;
}
//-----------------------------------------------------------------------------------------------------------
/* To read each row IR sensor using Arduino*/
char F_Read_IR_Ref()
{
  char Read_IR_Ref = OPEN;
  // End_IR = digitalRead();
  return Read_IR_Ref;
}

/* #Errror char Error_Buzzer(Error_Status)  // Beep tone to indicate invalid commands.
  {
  if (Error_Status == INVALID_COMMAND)
  {
    Serial.print("BUZZ for 10 seconds");    // Buzz for long time and stop.
  }
  }*/

/* #Errror char  Error_LEDs(Error_Status)   // All LEDs to RED to indicate invalied commands.
  {
  if (Error_Status == SYNTAX_ERROR)
  {
    Serial.print("LEDs to RED light for 3 blinks and stop");    // LEDs blink with red and stop.
  }

  }*/

//------------------------------------------------------------ SCAN HOLES -----------------------------------------------
char Scan_holes()
{
  unsigned char Bit_0, Bit_1, Bit_2, Bit_3, Bit_4, Bit_5, Bit_6, Bit_7,  bathi = 0;
  unsigned int index1 = 0, index = 0;
  unsigned char Current_Command = 0;
  unsigned int Zero_Counter = 0;
  unsigned int Command_Counter = 0;
#define MAX_ZERO_LIMITS 2

  Serial.println("In_Scan_Holes");
  Ref_IR     = digitalRead(Ref_IR_Read);    // Read all IR sensors on slate
  Start_IR   = digitalRead(Start_IR_Read);
  End_IR     = digitalRead(End_IR_Read);
  Serial.flush();
  // To Read all raw holes
  Serial.println("Start_Scan_Now");
  index = 0;
  while (End_IR == OPEN)  // Check if the slider is not yet come at end position Scanner is at hole position. // Make an error if column > 17
  { // Column while loop
    End_IR = digitalRead(End_IR_Read);
    Bit_0 = digitalRead(IR_1);
    Bit_1 = digitalRead(IR_2);
    Bit_2 = digitalRead(IR_3);
    Bit_3 = digitalRead(IR_4);
    Bit_4 = digitalRead(IR_5);
    Bit_5 = digitalRead(IR_6);
    Bit_6 = digitalRead(IR_7);
    Bit_7 = digitalRead(IR_8);
    Current_Temp_Command[index] = (128 * Bit_0) + (64 * Bit_1) + (32 * Bit_2) + (16 * Bit_3) + (8 * Bit_4) + (4 * Bit_5) + (2 * Bit_6) + (1 * Bit_7);
    Serial.println(Current_Temp_Command[index]);
    index++;
    End_IR     = digitalRead(End_IR_Read);
  }
  Serial.println("Filter_Starts");
  index1 = 0;
  // Clear array.
  for (Command_Counter = 0; Command_Counter < 25; Command_Counter++)//check for 24 commands //
  {
    Final_Commands[Command_Counter] = 0;
  }
  Command_Counter = 0;

  while (index1 < index) // Check full array.
  {
    if (Current_Temp_Command[index1] != 0 && Zero_Counter == 0) // These are numbers
    {
      Zero_Counter = 0;                                 // Clear zero counter for next set
      if (bathi == 1)                                   // Increment command counter once only
      {
        bathi = 0;
        Command_Counter++;//increment commandcounter//
      if (Final_Commands[Command_Counter] < Current_Temp_Command[index1])
      {
        Final_Commands[Command_Counter] = Current_Temp_Command[index1];
      }
    }
    else if (Current_Temp_Command[index1] == 0 && Current_Temp_Command[index1 + 1] != 0)               // Take out these zeros
    {
      Zero_Counter = 0;
      bathi = 1;
    }
    else  if (Current_Temp_Command[index1] == 0)
    {
      Zero_Counter++;
    }
    index1++;
  } // While end

  //  Command_Counter = 0;
  //  First_Command_Started = FALSE;
  for (index1 = 0; index1 <= 18; index1++)
  {
    Final_Commands[index1] = Final_Commands[index1 + 1];
    Serial.println(Final_Commands[index1]);
  }
  Serial.println("Converting data");
  /* Initialize all TX data read */
  for (Tx_Index = 0; Tx_Index < 24; Tx_Index++)
  {
    TX_Ready_data[Tx_Index] = 0;
  }

  Tx_Index = 0;
  // Get TX_Ready_data as final data to send
  for (Bit_Index = 0; Bit_Index < 7; )
  {
    for (Cm_Index = 0; Cm_Index < 18; )
    {
      if (Final_Commands [Cm_Index] & MASK_ARRAY [Bit_Index])
      {
        TX_Ready_data[Tx_Index] |= 0x01;
      }

      if (Final_Commands [Cm_Index + 1] & MASK_ARRAY [Bit_Index])
      {
        TX_Ready_data[Tx_Index] |= 0x02;
      }
      if (Final_Commands [Cm_Index + 2] & MASK_ARRAY [Bit_Index])
      {
        TX_Ready_data[Tx_Index] |= 0x04;
      }
      if (Final_Commands [Cm_Index] & MASK_ARRAY [Bit_Index + 1])
      {
        TX_Ready_data[Tx_Index] |= 0x08;
      }
      if (Final_Commands [Cm_Index + 1] & MASK_ARRAY [Bit_Index + 1])
      {
        TX_Ready_data[Tx_Index] |= 0x10;
      }
      if (Final_Commands [Cm_Index + 2] & MASK_ARRAY [Bit_Index + 1])
      {
        TX_Ready_data[Tx_Index] |= 0x20;
      }
      Tx_Index++;
      Cm_Index = Cm_Index + 3;
    }
    Cm_Index = 0;
    Bit_Index = Bit_Index + 2;
  }
  for (Tx_Index = 0; Tx_Index < 24; Tx_Index++)
  {
    Serial.println(TX_Ready_data[Tx_Index]);
  }
}

//------------------------------------------------------------ Read_Ref_Start_End_IRs -----------------------------------
int Read_Ref_Start_End_IRs()
{
  Ref_IR = digitalRead(Ref_IR_Read);    // Read all IR sensors on slate
  Start_IR = digitalRead(Start_IR_Read);
  End_IR = digitalRead(End_IR_Read);
}
//------------------------------------------------------------ print_data -----------------------------------------------
int print_data()
{
  int index1;
  for (Tx_Index = 0; Tx_Index < 24; Tx_Index++)
  {
    // Serial.println(TX_Ready_data[Tx_Index]);
  }
  // Display Commands

  for (index1 = 0; index1 <= 23; index1++)
  {
    switch (TX_Ready_data[index1])
    {
      case    WHEN:
        Serial.print("WHEN-");
        break;
      case    THEN:
        Serial.print("THEN-");
        break;
      case    WAIT_FOR:
        Serial.print("WAIT_FOR-");
        break;
      case    FOR:
        Serial.print("FOR-");
        break;
      case    OR:
        Serial.print("OR-");
        break;
      case    AND:
        Serial.print("AND-");
        break;
      case    NEXT:
        Serial.print("NEXT-");
        break;
      case    STOP:
        Serial.print("STOP-");
        break;
      case    REPEAT:
        Serial.print("REPEAT-");
        break;
      case    RETURN:
        Serial.print("RETURN-");
        break;
      case    GO:
        Serial.print("GO-");
        break;
      case    ELSE:
        Serial.print("ELSE-");
        break;
      case    WALL:
        Serial.print("WALL-");
        break;
      case    NO_WALL:
        Serial.print("NO_WALL-");
        break;
      case    LIGHT:
        Serial.print("LIGHT-");
        break;
      case    DARK:
        Serial.print("DARK-");
        break;
      case    RAIN:
        Serial.print("RAIN-");
        break;
      case    TOUCH:
        Serial.print("TOUCH-");
        break;
      case    SOUND:
        Serial.print("SOUND-");
        break;
      case    FORWARD:
        Serial.print("FORWARD-");
        break;
      case    REVERSE:
        Serial.print("REVERSE-");
        break;
      case    RIGHT:
        Serial.print("RIGHT-");
        break;
      case    LEFT:
        Serial.print("LEFT-");
        break;
      case    BLINK_EYES:
        Serial.print("BLINK_EYES-");
        break;
      case    BUZZ:
        Serial.print("BUZZ-");
        break;
      case    B_DAY:
        Serial.print("B_DAY-");
        break;
      case    SECONDS:
        Serial.print("SECONDS-");
        break;
      case    MINUTES:
        Serial.print("MINUTES-");
        break;
      case    HOURS:
        Serial.print("HOURS-");
        break;
      case    ROTATIONS:
        Serial.print("ROTATIONS-");
        break;
      case    FOOT:
        Serial.print("FOOT-");
        break;
      case    DEGREES:
        Serial.print("DEGREES-");
        break;
      case    DANCE:
        Serial.print("DANCE-");
        break;
      case    ZERO:
        Serial.print("ZERO-");
        break;
      case    ONE:
        Serial.print("ONE-");
        break;
      case    TWO:
        Serial.print("TWO-");
        break;
      case    THREE:
        Serial.print("THREE-");
        break;
      case    FOUR:
        Serial.print("FOUR-");
        break;
      case    FIVE:
        Serial.print("FIVE-");
        break;
      case    SIX:
        Serial.print("SIX-");
        break;
      case    SEVEN:
        Serial.print("SEVEN-");
        break;
      case    EIGHT:
        Serial.print("EIGHT-");
        break;
      case    NINE:
        Serial.print("NINE-");
        break;
      case    NO_COIN:
        Serial.print("NO_COIN-");
        break;
    }
  }
}

char Enable_Slider_Tx_IRs()
{
  digitalWrite(Vcontrol, HIGH);         // Enable Control input to IR Tx
}

char Read_Save_Buttons()
{
  Save_Button_1 = digitalRead(Save_Button_1_Read);
  Save_Button_2 = digitalRead(Save_Button_2_Read);
  Save_Button_3 = digitalRead(Save_Button_3_Read);
  Save_Button_4 = digitalRead(Save_Button_4_Read);
}

char Save_Button_pressed()                // Check if save buttons pressed?
{
  // Check if any save buttons pressed, then jump to save program.
  if (Save_Button_1 || Save_Button_2 || Save_Button_3 || Save_Button_4)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//------------------------------------------------------------ Call_virtual_wire -----------------------------------------------
char Call_virtual_wire()
{
  char loop1 = 0;
  // Send data for 24 times and then stop
  Serial.println("Commanding Rora!!");
  while (loop1 != 24)
  {
    loop1++;
    vw_send((uint8_t *)TX_Ready_data, strlen(TX_Ready_data));
    vw_wait_tx();                                          // Wait for message to finish
    delay(200);
    Serial.flush();
    Serial.println(loop1);
  }
}

//------------------------------------------------------------ Check_Errors-----------------------------------------------------
char Check_Errors()
{
  // 1 : No error/good commands
  // 2 : Invalid command/Invalid number of commands
  // 3 : Syntax error of tasks/commands are not in good sequence.

  unsigned char
  Valid_Array[50] = {32, 8, 48, 24, 4, 1, 51, 30, 46, 43, 20, 17,           //KEYWORDS
                     52, 25, 44, 41, 28, 49, 56,                            //INPUTS
                     50, 26, 6, 3, 10, 14, 35, 38, 11, 22, 19, 60, 57, 34,  //OUTPUTS
                     37, 13, 53, 29, 55, 31, 39, 15, 62, 59, 63             //UTILITIES
                    },
                    commands, Master_commands, Valid_commands_Count = 0, i, j, Current_Command, Next_Command, Valid_Array_index, Rules_index, Error, Check_Errors_return;

  unsigned char   Rules_Array[44][20] =
  {
    // KEYWORDS
    {WALL, NO_WALL, LIGHT, DARK, RAIN, TOUCH, SOUND, NO_COIN                                                                     }, // 0: WHEN
    {FORWARD, REVERSE, RIGHT, LEFT, BLINK_EYES, BUZZ, B_DAY, WAIT_FOR, STOP, REPEAT, RETURN, GO, DANCE, NO_COIN                        }, // 1: THEN
    {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, WALL, NO_WALL, LIGHT, DARK, RAIN, TOUCH, SOUND, NO_COIN   },// 2: WAIT_FOR
    {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, NO_COIN                                                   },// 3: FOR
    {WALL, NO_WALL, LIGHT, DARK, RAIN, TOUCH, SOUND, NO_COIN                                                                     }, // 4: OR
    {WALL, NO_WALL, LIGHT, DARK, RAIN, TOUCH, SOUND, NO_COIN                                                                     }, // 5: AND
    {WHEN, FORWARD, REVERSE, RIGHT, LEFT, BLINK_EYES, BUZZ, B_DAY, WAIT_FOR, STOP, REPEAT, RETURN, DANCE, NO_COIN                     }, // 6: NEXT
    {THEN, NO_COIN                                                                                                         },// 7: STOP
    {THEN, NO_COIN                                                                                                         },// 8: REPEAT
    {THEN, NO_COIN                                                                                                         },// 9: RETURN
    {FORWARD, REVERSE, RIGHT, LEFT, NO_COIN                                                                                   }, // 10: GO
    {FORWARD, REVERSE, RIGHT, LEFT, BLINK_EYES, BUZZ, B_DAY, WAIT_FOR, STOP, REPEAT, RETURN, GO, DANCE, NO_COIN                        }, // 11: ELSE
    //INPUTS
    {THEN, AND, OR, FOR, NO_COIN},                                                                                           // 12: WALL
    {THEN, AND, OR, FOR, NO_COIN},                                                                                           // 13: NO_WALL
    {THEN, AND, OR, FOR, NO_COIN},                                                                                           // 14: LIGHT
    {THEN, AND, OR, FOR, NO_COIN},                                                                                           // 15: DARK
    {THEN, AND, OR, FOR, NO_COIN},                                                                                           // 16: RAIN
    {THEN, AND, OR, FOR, NO_COIN},                                                                                           // 17: TOUCH
    {THEN, AND, OR, FOR, NO_COIN},                                                                                           // 18: SOUND
    //OUTPUTS
    {NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN, NO_COIN},                                                                  // 19: FORWARD
    {NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN, NO_COIN},                                                                  // 20: REVERSE
    {NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN, NO_COIN},                                                                  // 21: RIGHT
    {NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN, NO_COIN},                                                                  // 22: LEFT
    {NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN, NO_COIN},                                                                  // 23: BLINK_EYES
    {NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN, NO_COIN},                                                                  // 24: BUZZ
    {NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN, NO_COIN},                                                                  // 25: B_DAY
    {NEXT, ELSE, THEN, STOP, REPEAT, RETURN, NO_COIN     },                                                                  // 26: SECONDS
    {NEXT, ELSE, THEN, STOP, REPEAT, RETURN, NO_COIN     },                                                                  // 27: MINUTES
    {NEXT, ELSE, THEN, STOP, REPEAT, RETURN, NO_COIN     },                                                                  // 28: HOURS
    {NEXT, ELSE, THEN, STOP, REPEAT, RETURN, NO_COIN     },                                                                  // 29: ROTATIONS
    {NEXT, ELSE, THEN, STOP, REPEAT, RETURN, NO_COIN     },                                                                  // 30: FOOT
    {NEXT, ELSE, THEN, STOP, REPEAT, RETURN, NO_COIN     },                                                                  // 31: DEGREES
    {NEXT, ELSE, THEN, STOP, REPEAT, RETURN, FOR, NO_COIN },                                                                 // 32: DANCE
    //UTILITIES:
    {SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, NO_COIN},           // 33: ZERO
    {SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, NO_COIN},           // 34: ONE
    {SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, NO_COIN},           // 35: TWO
    {SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, NO_COIN},           // 36: THREE
    {SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, NO_COIN},           // 37: FOUR
    {SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, NO_COIN},           // 38: FIVE
    {SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, NO_COIN},           // 39: SIX
    {SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, NO_COIN},           // 40: SEVEN
    {SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, NO_COIN},           // 41: EIGHT
    {SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, NO_COIN},           // 42: NINE
    {NO_COIN}                                                                                                                // 43: NO_COIN
  };

  /* RULES for commands
    KEYWORDS:
    WHEN     : WALL,NO_WALL,LIGHT,DARK,RAIN,TOUCH,SOUND
    THEN     : FORWARD,REVERSE,RIGHT,LEFT,BLINK_EYES,BUZZ,B_DAY,WAIT_FOR,STOP,REPEAT,RETURN,GO,DANCE
    WAIT_FOR : ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, WALL, NO_WALL, LIGHT, DARK, RAIN, TOUCH, SOUND
    FOR      : ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
    OR       : WALL,NO_WALL,LIGHT,DARK,RAIN,TOUCH,SOUND
    AND      : WALL,NO_WALL,LIGHT,DARK,RAIN,TOUCH,SOUND
    NEXT     : WHEN, FORWARD,REVERSE,RIGHT,LEFT,BLINK_EYES,BUZZ,B_DAY,WAIT_FOR,STOP,REPEAT,RETURN,DANCE
    STOP     : THEN
    REPEAT   : THEN
    RETURN   : THEN
    GO       : FORWARD,REVERSE,RIGHT,LEFT
    ELSE     : FORWARD,REVERSE,RIGHT,LEFT,BLINK_EYES,BUZZ,B_DAY,WAIT_FOR,STOP,REPEAT,RETURN,GO,DANCE

    INPUTS:
    WALL    :THEN, AND, OR, FOR
    NO_WALL :THEN, AND, OR, FOR
    LIGHT   :THEN, AND, OR, FOR
    DARK    :THEN, AND, OR, FOR
    RAIN    :THEN, AND, OR, FOR
    TOUCH   :THEN, AND, OR, FOR
    SOUND   :THEN, AND, OR, FOR

    OUTPUTS:
    FORWARD    :NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN,
    REVERSE    :NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN,
    RIGHT      :NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN,
    LEFT       :NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN,
    BLINK_EYES :NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN,
    BUZZ       :NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN,
    B_DAY      :NEXT, FOR, ELSE, THEN, STOP, REPEAT, RETURN,
    SECONDS    :NEXT, ELSE, THEN, STOP, REPEAT, RETURN,
    MINUTES    :NEXT, ELSE, THEN, STOP, REPEAT, RETURN,
    HOURS      :NEXT, ELSE, THEN, STOP, REPEAT, RETURN,
    ROTATIONS  :NEXT, ELSE, THEN, STOP, REPEAT, RETURN,
    FOOT       :NEXT, ELSE, THEN, STOP, REPEAT, RETURN,
    DEGREES    :NEXT, ELSE, THEN, STOP, REPEAT, RETURN,
    DANCE      :NEXT, ELSE, THEN, STOP, REPEAT, RETURN,FOR,

    UTILITIES
    ZERO  : SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
    ONE   : SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
    TWO   : SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
    THREE : SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
    FOUR  : SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
    FIVE  : SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
    SIX   : SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
    SEVEN : SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
    EIGHT : SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
    NINE  : SECONDS, MINUTES, HOURS, FOOT, DEGREES, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
  */
  { // Check for valid command or not
    for (commands = 0; commands < 24; commands++)                                   // Check if commands are valid.
    {
      for (Master_commands = 0; Master_commands < 46; Master_commands++)          // Valid commands form master list.
      {
        if (TX_Ready_data[commands] == Valid_Array[Master_commands])               // Check each commands if they are good to send.
        {
          Valid_commands_Count++;
        }
      }
    }
    if (Valid_commands_Count != 24)                                                 // Check if all the commands are valid ones.
    {
      Check_Errors_return = INVALID_COMMAND;  // Send error to enable further actions.
    }
  }

  {
    // Check for rules and reply row number which has error.
    Error_in_row_1 = 0;                                       // Holds error in row value 0 = No error, else Error
    Error_in_row_2 = 0;
    Error_in_row_3 = 0;
    Error_in_row_4 = 0;
    Commands = 0;

    for (Commands = 0; Commands < 24; Commands++)                                                     // Parse thru all commands list
    {
      Current_Command = TX_Ready_data[Commands];                                  // Get current command
      Next_Command    = TX_Ready_data[Commands + 1];                              // Get next command

      for (Valid_Array_index = 0; Valid_Array_index < 50; Valid_Array_index++) // To get the index to be checked in 2D array
      {
        if (TX_Ready_data[Commands] == Valid_Array[Valid_Array_index])          // Parse command in full set of commands in valid array
        {
          Rules_to_check = Valid_Array_index;                              // Now we got index to be passed on 2D array first index
        }
      }

      for (Rules_index = 0; Rules_index < 20; Rules_index++) // Parse Current command with next command
      {
        if (TX_Ready_data[Next_Command] != Rules_Array[Rules_to_check][Rules_index]) // Check next commands for WHEN
        {
          Error = 1;
        }
      }

      if (Error)                                              // Set corresponding row error and clear error for next parse
      {
        if (Commands >= 0 && Commands <= 5)
        {
          Error_in_row_1 = TRUE;
          Serial.println("Error_in_row_1");
        }
        else if (Commands >= 6 && Commands <= 11)        {
          Error_in_row_2 = TRUE;
          Serial.println("Error_in_row_2");
        }
        else if (Commands >= 12 && Commands <= 17)
        {
          Error_in_row_3 = TRUE;
          Serial.println("Error_in_row_3");
        }
        else
        {
          Serial.println("Error_in_row_4");
        }
      }
      Error = 0;

    }
    Check_Errors_return = Error_in_row_1 & Error_in_row_2 & Error_in_row_3 & Error_in_row_4;
  }
  return Check_Errors_return;  // Return final
}



