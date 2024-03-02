// =========================================================================
// Arduino UNO General Instruments SP0256-AL2 Shield Project
// https://github.com/MarkD833/Arduino-SP0256-Shield
//
// Simple allophone test sketch
//

#include <stdio.h>
#include <SPI.h>

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

char rxCharBuff[ MAXCHARS ];

void setup() {
  Serial.begin( 9600 );
  Serial.println(F("\n\n========================================================="));
  Serial.println(F("Arduino UNO General Instruments SP0256-AL2 Shield Project"));
  Serial.println(F("  [ https://github.com/MarkD833/Arduino-SP0256-Shield ]\n"));
  Serial.println(F("          SP0256-AL2 Allophone Test Sketch V1.0"));
  Serial.println(F("\n========================================================="));

  Serial.println(F("\nNOTE: Leave the baud rate at 9600 as there's no handshaking on the Intel-HEX upload.\n"));

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

  Serial.println(F("Enter 1 or more allophones separated by a space."));
  Serial.println(F("For example, to say the word OK, enter the allophones:"));
  Serial.println(F("pa2 ow pa3 kk1 ey pa3"));
}

void loop() {
  char * tok;
  uint16_t allophone;

  // process any serial commands received
  waitForUserInput();

  if ( strlen( rxCharBuff ) > 0 ) {
    // convert the whole use input to upper case
    for ( int x=0; x<strlen( rxCharBuff ); x++ ) {
      rxCharBuff[ x ] = toupper( rxCharBuff[ x ] );
    }

    tok = strtok( rxCharBuff, " " );
    while ( tok != 0 ) {
      // if 1st char is A..Z then allophone has been typed
      if ( isalpha( tok[0] ) ) {
        // could be an allophone - so look it up
        allophone = lookup( tok );

        // did we find it?
        if ( allophone != -1 ) {
          Serial.println( allophone );
          spSpeak( allophone );          
        }
        else
        {
          // didn't recognise the allophine the user entered
          Serial.print(F("Unknown allophone: "));
          Serial.println( tok );
        }
      }
      else
      {
        // direct allophone number so just say it
        allophone = atoi( tok );

        if ( allophone < 64 ) {
          Serial.println( allophone );
          spSpeak( allophone );
        }
        else
        {
          Serial.println(F("Allophone number must be less than 64."));
        }
      }
      // now wait for the sound to be output
      while ( digitalRead( SP_LOAD_REQ ) == HIGH );

      tok = strtok( 0, " " );
    }
    // finished speaking so wait for the last allophone to complete    
    while ( digitalRead( SP_LOAD_REQ ) == HIGH );
    spSpeak( 0 );
    Serial.println( " -- done -- " );
  }

}

// =========================================================================
// lookup - lookup the allophone and return its number
// =========================================================================
int lookup( char * allo ) {
  for ( int x=0; x<MAXALLO; x++ ) {
    if ( strncmp( allo, table[x], 4 ) == 0 ) return x;
  }
  return -1;
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
