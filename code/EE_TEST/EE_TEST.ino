// =========================================================================
// Arduino UNO General Instruments SP0256-AL2 Shield Project
// https://github.com/MarkD833/Arduino-SP0256-Shield
//
// Simple EEPROM vocabulary test sketch
//
// =========================================================================
// Uses the EEPROM_SPI_WE library - find it via library manager
// =========================================================================

#include <stdio.h>
#include <SPI.h>
#include <EEPROM_SPI_WE.h>

// maximum number of chars in received text string
#define MAXCHARS    128

// the 74HCT595 shift registers are selected using pin D10 on the UNO
#define SP0256_SPI_SS 10

// the 25LC256 EEPROM is selected using pin D9 on the UNO
#define EEPROM_SPI_SS 9

// SP0256-AL2 load request (input) is on pin A0 on the UNO
#define SP_LOAD_REQ  A0

// SP0256-AL2 write pulse (output) is on pin A1 on the UNO
#define SP_WRITE  A1

// the 74HCT595 shift registers are selected using pin D10 on the UNO
#define SP0256_SPI_SS 10

#define MAXALLO   64

const char table[ MAXALLO ][4] = {
  {"PA1"},  {"PA2"},  {"PA3"},  {"PA4"},  {"PA5"},  {"OY\0"}, {"AY\0"}, {"EH\0"},
  {"KK3"},  {"PP\0"}, {"JH\0"}, {"NN1"},  {"IH\0"}, {"TT2"},  {"RR1"},  {"AX\0"},
  {"MM\0"}, {"TT1"},  {"DH1"},  {"IY\0"}, {"EY\0"}, {"DD1"},  {"UW1"},  {"AO\0"},
  {"AA\0"}, {"YY2"},  {"AE\0"}, {"HH1"},  {"BB1"},  {"TH\0"}, {"UH\0"}, {"UW2"},
  {"AW\0"}, {"DD2"},  {"GG3"},  {"VV\0"}, {"GG1"},  {"SH\0"}, {"ZH\0"}, {"RR2"},
  {"FF\0"}, {"KK2"},  {"KK1"},  {"ZZ\0"}, {"NG\0"}, {"LL\0"}, {"WW\0"}, {"XR\0"},
  {"WH\0"}, {"YY1"},  {"CH\0"}, {"ER1"},  {"ER2"},  {"OW\0"}, {"DH2"},  {"SS\0"},
  {"NN2"},  {"HH2"},  {"OR\0"}, {"AR\0"}, {"YR\0"}, {"GG2"},  {"EL\0"}, {"BB2"}
};

EEPROM_SPI_WE myEE = EEPROM_SPI_WE( EEPROM_SPI_SS );

char rxCharBuff[ MAXCHARS ];

void setup() {
  Serial.begin( 9600 );
  Serial.println(F("\n\n========================================================="));
  Serial.println(F("Arduino UNO General Instruments SP0256-AL2 Shield Project"));
  Serial.println(F("  [ https://github.com/MarkD833/Arduino-SP0256-Shield ]\n"));
  Serial.println(F("      SP0256-AL2 EEPROM Vocabulary Test Sketch V1.0"));
  Serial.println(F("\n========================================================="));

  // congifure the SPI SS pin for the external EEPROM
  pinMode( EEPROM_SPI_SS, OUTPUT );
  digitalWrite( EEPROM_SPI_SS, HIGH );

  // configure the SPI SS pin for the shift registers
  pinMode( SP0256_SPI_SS, OUTPUT );
  digitalWrite( SP0256_SPI_SS, HIGH );

  // configure the write strobe pin to the SP0256-AL2 chip
  pinMode( SP_WRITE, OUTPUT );
  digitalWrite( SP_WRITE, HIGH );

  // configure the LOAD request pin from the SP0256-AL2 chip
  pinMode( SP_LOAD_REQ, INPUT );

  SPI.begin();

  // shuts the SP0256 up if it was speaking
  spSpeak( 0 );

  // initialise the external EEPROM interface
  if(myEE.init()){
    Serial.println("25LC256 EEPROM connected");
    myEE.setPageSize(EEPROM_PAGE_SIZE_64);
  }
  else{
    Serial.println("EEPROM does not respond");
    while(1);
  }

  Serial.print(F("Version string from EEPROM is: "));
  spEEVersion();
  
  Serial.println(F("\n\nEnter 1 or more vocabulary index numbers separated by a space."));
  Serial.println(F("To say the word OK, the index number is 3506 in the current vocaulary."));
}

void loop() {
  char * tok;
  uint16_t vocabIndex;

  // process any serial commands received
  waitForUserInput();

  if ( strlen( rxCharBuff ) > 0 ) {

    tok = strtok( rxCharBuff, " " );
    while ( tok != 0 ) {
      // get the index number
      vocabIndex = atoi( tok );

      Serial.println( vocabIndex );
      spEESpeak( vocabIndex );

      // now wait for the word/phrase to be output
      while ( digitalRead( SP_LOAD_REQ ) == HIGH );

      // and find the next index number
      tok = strtok( 0, " " );
    }

    // finished speaking so wait for the last allophone to complete    
    while ( digitalRead( SP_LOAD_REQ ) == HIGH );
    spSpeak( 0 );
    Serial.println( " -- done -- " );
  }
}

// =========================================================================
// spSpeak - writes a single allophone to the SP0256-AL2 chip
// =========================================================================
void spSpeak( uint8_t alloNumber )
{
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite( SP0256_SPI_SS, LOW );
  SPI.transfer( alloNumber );
  digitalWrite( SP0256_SPI_SS, HIGH );
  SPI.endTransaction();
  
  digitalWrite( SP_WRITE, LOW );
  delay( 1 );
  digitalWrite( SP_WRITE, HIGH );
}

// =========================================================================
// spEESpeak - writes a stored sequence of allophones from the 25LC256
//             EEPROM to the SP0256-AL2 chip
// =========================================================================
void spEESpeak( uint16_t indx ) {
  uint16_t lutAddr = 0;
  uint16_t lsbAddr = 0;
  uint16_t alloAddr = 0;
  uint8_t  i = 0;
  uint8_t  j = 0;

  uint8_t  allo = 0;
  
  // calculate the address in the look up table where message pointer is 
  lutAddr = indx << 1;
/*   
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  digitalWrite( EEPROM_SPI_SS, LOW );
  SPI.transfer( EEREAD_CMD );
  SPI.transfer16( lutAddr );

  lsbAddr = SPI.transfer( 0 );
  alloAddr = SPI.transfer( 0 );
  alloAddr = ( alloAddr << 8 ) | lsbAddr;
  
  digitalWrite( EEPROM_SPI_SS, HIGH );
*/
  Serial.print(F("message start = "));
  Serial.println( lutAddr , HEX );
/*  
  // alloAddr now holds the address in the EEPROM where the sequence of allophones starts
  // read out the allophones starting at that address until 0xFF is found (i.e. end of sequence)
  digitalWrite( EEPROM_SPI_SS, LOW );
  SPI.transfer( EEREAD_CMD );
  SPI.transfer16( alloAddr );
  do {
    rxCharBuff[ i ] = SPI.transfer( 0 );
    Serial.println( rxCharBuff[i], HEX );
    if ( rxCharBuff[ i ] == -1 ) break;
    i++;
  } while ( i < MAXCHARS );
  digitalWrite( EEPROM_SPI_SS, HIGH );

  SPI.endTransaction();
*/
  lsbAddr = myEE.read( lutAddr++ );
  alloAddr = myEE.read( lutAddr );
  alloAddr = ( alloAddr << 8 ) | lsbAddr;

  do {
    allo = myEE.read( alloAddr++ );
    if ( allo != 0xFF ) {
      Serial.println( table[ allo ] );
      spSpeak( allo );

      // now wait for the sound to be output
      while ( digitalRead( SP_LOAD_REQ ) == HIGH );
    }
  } while ( allo != 0xFF );
/*
  for (j=0; j<i; j++) {
    spSpeak( rxCharBuff[j] );
    // now wait for the sound to be output
    while ( digitalRead( SP_LOAD_REQ ) == HIGH );
  }
  Serial.println( i, HEX );
*/
}

// =========================================================================
// spEEVersion - prints the vocabulary version string from the EEPROM
// =========================================================================
void spEEVersion( void ) {
  uint16_t lsbAddr = 0;
  uint16_t verAddr = 0;
  char ch;
  
  uint8_t  allo = 0;

  // get the address where the version string is stored in the EEPROM
  // EEPROM locations 0x0000 and 0x0001 hold the pointer
  lsbAddr = myEE.read( 0 );
  verAddr = myEE.read( 1 );
  verAddr = ( verAddr << 8 ) | lsbAddr;

  ch = myEE.read( verAddr++ );
  while ( ch != 0 ) {
    Serial.print( ch );
    ch = myEE.read( verAddr++ );
  }
}

// =========================================================================
// isPrintableChar - Returns TRUE if character is 0..9 or A..Z
// =========================================================================
bool isPrintableChar( char ch ) {
  if ( (ch>='0') || (ch<='9') ) return true;
  if ( (ch>='A') || (ch<='Z') ) return true;
  if ( (ch>='a') || (ch<='z') ) return true;

  return false;
}

// =========================================================================
// waitForUserInput - Wait for the user to type something collecting chars
//                    until ENTER pressed
// =========================================================================
void waitForUserInput() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  bool newData = false;

  memset(rxCharBuff, 0, MAXCHARS );
  
  while ( newData == false ) {
    if (Serial.available() > 0) {
      rc = Serial.read();

      if (rc != endMarker) {
        if ( isPrintableChar( rc ) == true ) {
          rxCharBuff[ndx++] = rc;
          if (ndx >= MAXCHARS) ndx = MAXCHARS - 1;
        }
      }
      else {
        if ( ndx > 0 ) {
          rxCharBuff[ndx] = '\0';
          ndx = 0;
          newData = true;
        }
      }
    }
  }
}
