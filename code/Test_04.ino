// =========================================================================
// Arduino UNO General Instruments SP0256-AL2 Shield
// Simple speech demo using the VOCAB.HEX file programmed into the 25LC256.
// =========================================================================
// Uses the EEPROM_SPI_WE library - find it via library manager
// =========================================================================

#include <stdio.h>
#include <SPI.h>
#include <EEPROM_SPI_WE.h>

#define EEREAD_CMD  0x03	// 25LC256 READ command
#define EEWRITE_CMD 0x02	// 25LC256 WRITE command
#define EEWREN_CMD  0x06	// 25LC256 WRITE ENABLE command
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

EEPROM_SPI_WE myEE = EEPROM_SPI_WE( EEPROM_SPI_SS );

char rxCharBuff[ MAXCHARS ];

void setup() {
  Serial.begin( 9600 );
  Serial.println(F("\n\nGeneral Instruments SP0256-AL2 Test Program #4"));
  Serial.println(F("=============================================="));

  Serial.println(F("Type in an index number for the word or phrase stored in the EEPROM"));
  Serial.println(F("More than one number can be entered separated by a space."));
  Serial.println(F("\nAlso accepts Intel-Hex records to program the on-board 25LC256."));
  Serial.println(F("NOTE: Leave the baud rate at 9600 as there's no handshaking on the Intel-HEX upload.\n"));

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
  delay( 100 );
}

void loop() {
  char * tok;
  uint16_t phrase;

  // process any serial commands received
  waitForUserInput();

  if ( rxCharBuff[ 0 ] == ':' ) {
    // it's a line of Intel-Hex data so take care of it
    Serial.print( decodeIntelHex() );
  }
  else
  {
    if ( strlen( rxCharBuff ) > 0 ) {
      // split the string using a SPACE as the delimiter
      tok = strtok( rxCharBuff, " " );
      while ( tok != 0 ) {
        // get the index number for the phrase or word to say
        phrase = atoi( tok );
  
        Serial.println( phrase );
        spEESpeak( phrase );

        // now wait for the sound to be output
        while ( digitalRead( SP_LOAD_REQ ) == HIGH );
  
        tok = strtok( 0, " " );
      }
      // finished speaking so wait for the last allophone to complete    
      while ( digitalRead( SP_LOAD_REQ ) == HIGH );
      spSpeak( 0 );
      Serial.print( " -- done -- " );
    }
  }
  Serial.println();
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
  uint16_t msbAddr = 0;
  uint16_t phraseAddr = 0;
  uint8_t  i = 0;
  uint8_t  j = 0;

  uint8_t  allo = 0;
  
  // calculate the address in the look up table where message pointer is 
  // it is simply 2x the index number as the LUT holds 16-bit addresses
  lutAddr = ( indx << 1 );

  Serial.print(F("Lookup table address = "));
  Serial.println( lutAddr , HEX );

  lsbAddr = myEE.read( lutAddr++ );
  msbAddr = myEE.read( lutAddr );
  phraseAddr = ( msbAddr << 8 ) | lsbAddr;

  Serial.print(F("Phrase start address = "));
  Serial.println( phraseAddr , HEX );

  do {
    allo = myEE.read( phraseAddr++ );
    
    if ( allo != 0xFF ) {
      Serial.print( allo, HEX );
      Serial.print( " = " );
      Serial.println( table[allo] );

      spSpeak( allo );

      // now wait for the sound to be output
      while ( digitalRead( SP_LOAD_REQ ) == HIGH );
    }
  } while ( allo != 0xFF );
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

// =========================================================================
// decodeASCIIHexChar - convert ASCII HEX digit to binary
// =========================================================================
int16_t decodeASCIIHexChar( char ch ) {
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    else if (ch >= 'a' && ch <= 'f')
        return 10 + ch - 'a';
    else if (ch >= 'A' && ch <= 'F')
        return 10 + ch - 'A';
    else
        return -1;
}

// =========================================================================
// decodeIntelHex - decode 1 line of Intel-Hex data held in rxCharBuff[]
// =========================================================================
int8_t decodeIntelHex() {
  uint8_t  byteCount = 0;
  uint8_t  checksum = 0;
  uint8_t  tByte = 0;
  uint8_t  buffIndx = 1;
  uint16_t startAddress = 0;

  // byte count
  byteCount = decodeASCIIHexChar( rxCharBuff[buffIndx++] );
  byteCount = ( byteCount << 4 ) + decodeASCIIHexChar( rxCharBuff[buffIndx++] );
  checksum = byteCount;

  // simple sanity check - knowing byte count means we know how many chars there should be
  if ( strlen( rxCharBuff ) < ( 10 + ( byteCount << 1 ))) {
    Serial.println(F("ERR: Corrupted iHex record."));
    return 1;
  }

  // start address
  tByte = decodeASCIIHexChar( rxCharBuff[buffIndx++] );
  tByte = ( tByte << 4 ) + decodeASCIIHexChar( rxCharBuff[buffIndx++] );
  checksum = checksum + tByte;
  startAddress = tByte;
  tByte = decodeASCIIHexChar( rxCharBuff[buffIndx++] );
  tByte = ( tByte << 4 ) + decodeASCIIHexChar( rxCharBuff[buffIndx++] );
  checksum = checksum + tByte;
  startAddress = ( startAddress << 8 ) + tByte;

  // record type - either 00 (Data) or EOF (01)
  tByte = decodeASCIIHexChar( rxCharBuff[buffIndx++] );
  tByte = ( tByte << 4 ) + decodeASCIIHexChar( rxCharBuff[buffIndx++] );
  checksum = checksum + tByte;

  // if record type is 00 (Data) then carry on extracting the bytes
  if ( tByte == 0 ) {
    // enable EEPROM continuous writes
    myEE.continuousPutEnable( startAddress );

    for (uint8_t i=0; i<byteCount; i++) {
      tByte = decodeASCIIHexChar( rxCharBuff[buffIndx++] );
      tByte = ( tByte << 4 ) + decodeASCIIHexChar( rxCharBuff[buffIndx++] );
      checksum = checksum + tByte;

      // write out the byte
      myEE.continuousPut( tByte );
    }
    // done
    myEE.continuousPutDisable();
  }

  // now add in the checksum
  tByte = decodeASCIIHexChar( rxCharBuff[buffIndx++] );
  tByte = ( tByte << 4 ) + decodeASCIIHexChar( rxCharBuff[buffIndx++] );
  checksum = checksum + tByte;

  // if the checksum is ZERO, then we've got a valid record
  if ( checksum == 0 ) return 0;

  return -1;
}