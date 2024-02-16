# Arduino UNO General Instruments SP0256-AL2 Shield
After playing with the National Semiconductor Digitalker IC, I got to remembering about another speech chip from my younger days. Way back when I owned a [NASCOM-2](https://en.wikipedia.org/wiki/Nascom) Z80 based machine, I also had a speech interface built around a GI SP0256-AL2 device that I hooked up to it. This is my spin on using the SP0256-AL2 chip with a modern-ish Arduino UNO board.

## Description

The aim of this project is to create a shield for an Arduino UNO to bring to life a General Instruments SP0256-AL2 speech IC and to additionall have some non-volatile storage to hold some [allophones](https://en.wikipedia.org/wiki/Allophone) for pre-defined words and phrases.

## Design

In order to speak a word (or phrase), the SP0256-AL2 needs to be passes a stream of allophones that when strung together sound like a word. The SP0256-AL2 has 64 allophones. The required allophone is presented on the pins A1..A8. In this design, A7 & A8 are grounded so only 6 bits are used from the shift register.

Once the required allophone has been presented, the ALD (Address Load) pin is pulsed low briefly. This loads the allophone into the SP0256-AL2 and starts the sound generation process.

The SP0256-AL2 sets the LRQ (Load Request) pin low when it is ready for the next allophone.

### Interface

I've chosen to use the SPI interface of the ATMEGA328P on the UNO and a single 74HCT595 serial-in / parallel-out shift register to transfer the allophone to the SP0256-AL2 chip.

I'm using the SPI signals MOSI and SCK from the ICSP header on the UNO rather than D11 and D13 in the hope that this board can also be used with an Arduino MEGA2560 as well. The SPI signals on the Arduino MEGA2560 board are on completely different pins, but they are also present on the ICSP header in the same physical location as on the UNO.

The SPI SS signal is routed to the D10 pin on the UNO, the Address Load is routed to the A1 pin on the UNO and the Load Request is routed to pin A0 on the UNO.

### Power

Unlike the Digitalker chip, the SP0256-AL2 runs from 5V which is sourced from the UNO board. 

### Audio

The audio circuitry is lifted directly from the SP0256-AL2 datasheet.

# Assembly

Start with the discrete components - there are a few resistors and capacitors which should be easy to hand solder. Then add the various IC sockets and the header pins.

When you've installed all the basic components, and before fitting any chips, check that you have 5V on the VCC pins of the SP0256-AL2, 74HCT595 and 25LC256.

Install the SP0256-AL2, 74HCT595 and the 25LC256 EEPROM. 

# Speaking the first words

I've created a simple test sketch that you can use to send any of the allophones. It's in the code folder and called Test_03. You can type in either the allophone number (0-63) or the allophone name. Multiple allophones can be generated - simply put a space between each allophone.
 As a start, the allophones for the word "hello" are:
 
> PA2 HH1 EH LL OW PA3

or

> 1 27 7 45 53 2

Note that the SP0256-AL2 needs a silence allophone at the end of a sequence otherwise it continues to output the last sound it made.

# Further information

Have a look in the datasheets folder for information on the SP0256-AL2 chip and its companion, the CTS256. The SP0256-AL2 datasheet details the allophones as well as examples of their use in english words.

# Bored with trying to work out the required allophones yet?

I discovered a [software implementation of the CTS256 chip](https://github.com/GmEsoft/SP0256_CTS256A-AL2). The CTS256 chip is used to convertt plain ASCII character words into the required allophones that the SP0256-AL2 uses. The software can be compiled using the free version of Visual Studio. Once compiled, you can use the CTS256 simulator to produce the required allophones like this:
`
> CTS256A-AL2.exe hello
CTS256A-AL2(tm) Emulator - v0.0.6-alpha

 PA2 HH1 EH LL OW PA3

Conversion complete.
`
## Version History

* 0.1
    * Initial Release

## License

This project is licensed under the GNU General Public License v3.0 - see the LICENSE.md file for details
