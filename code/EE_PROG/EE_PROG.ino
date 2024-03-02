// =========================================================================
// Arduino UNO General Instruments SP0256-AL2 Shield Project
// https://github.com/MarkD833/Arduino-SP0256-Shield
//
// Onboard 25LC256 EEPROM programming sketch.
//
// =========================================================================
// Uses the EEPROM_SPI_WE library - find it via library manager
// =========================================================================

#include <stdio.h>
#include <SPI.h>
#include <EEPROM_SPI_WE.h>

// maximum number of chars in received text string
#define MAXCHARS    128

// the 25LC256 EEPROM is selected using pin D9 on the UNO
#define EEPROM_SPI_SS 9

// SP0256-AL2 write pulse (output) is on pin A1 on the UNO
#define SP_WRITE  A1

// the 74HCT595 shift registers are selected using pin D10 on the UNO
#define SP0256_SPI_SS 10

EEPROM_SPI_WE myEE = EEPROM_SPI_WE( EEPROM_SPI_SS );

char rxCharBuff[ MAXCHARS ];
uint8_t loadErrors = 0;

void setup() {
  Serial.begin( 9600 );
  Serial.println(F("\n\n========================================================="));
  Serial.println(F("Arduino UNO General Instruments SP0256-AL2 Shield Project"));
  Serial.println(F("  [ https://github.com/MarkD833/Arduino-SP0256-Shield ]\n"));
  Serial.println(F("          SP0256-AL2 25LC256 Programmer V1.0"));
  Serial.println(F("\n========================================================="));

  Serial.println(F("\nNOTE: Leave the baud rate at 9600 as there's no handshaking on the Intel-HEX upload.\n"));

  // congifure the SPI SS pin for the external EEPROM
  pinMode( EEPROM_SPI_SS, OUTPUT );
  digitalWrite( EEPROM_SPI_SS, HIGH );

  SPI.begin();

  // shuts the SP0256 up if it was speaking
  spSpeak( 0 );

  // initialise the external EEPROM interface
  if(myEE.init()){
    Serial.println("EEPROM connected");
    myEE.setPageSize(EEPROM_PAGE_SIZE_64);
  }
  else{
    Serial.println("EEPROM does not respond");
    while(1);
  }  
  delay( 100 );
  Serial.println(F("Waiting for Intel-HEX records."));
}

void loop() {
  char * tok;
  uint16_t phrase;

  // process any serial commands received
  waitForUserInput();

  if ( rxCharBuff[ 0 ] == ':' ) {
    // it's a line of Intel-Hex data so take care of it
    decodeIntelHex();
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
// and write it to the external EEPROM.
// =========================================================================
void decodeIntelHex() {
  uint8_t  byteCount = 0;
  uint8_t  checksum = 0;
  uint8_t  tByte = 0;
  uint8_t  buffIndx = 1;
  uint16_t startAddress = 0;
  uint8_t  endOfFile = 0;
  
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

  Serial.print( startAddress, HEX );

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
  else if ( tByte == 1 ) {
    // end of file record
    endOfFile = 1;
  }
  
  // now add in the checksum
  tByte = decodeASCIIHexChar( rxCharBuff[buffIndx++] );
  tByte = ( tByte << 4 ) + decodeASCIIHexChar( rxCharBuff[buffIndx++] );
  checksum = checksum + tByte;

  // if the checksum is ZERO, then we've got a valid record
  if ( checksum == 0 ) {
    // valid record
    Serial.println(F(" - Ok"));
  }
  else {
    // invalid record - checksum failed
    Serial.println(F(" - Checksum fail"));
    loadErrors++;
  }

  if ( endOfFile == 1 ) {
    delay( 1000 );
    if ( loadErrors == 0 ) {
      Serial.println(F("LOAD COMPLETE - NO ERRORS."));
    } else {
      Serial.println(F("LOAD FAILED - ERRORS DETECTED."));
      // reset the error count ready for next attempt
      loadErrors = 0;
    }
  }
}
