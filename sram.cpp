#include "sram.h"

// Default constructor for SRAM object
// User chooses a socket, class attributes
// and relevant Arduino pins are enabled 
// accordingly.
SRAM::SRAM (int(usr_socket_choice))
{
    switch(usr_socket_choice)
    {
    case 'A':
        board_cs = A_CS;
        board_led = LED_A;
        break;
    case 'B':
        board_cs = B_CS;
        board_led = LED_B;
        break;
    case 'C':
        board_cs = C_CS;
        board_led = LED_C;
        break;
    case 'D':
        board_cs = D_CS;
        board_led = LED_D;
        break;
    }
    pinMode(board_cs, OUTPUT);
    pinMode(board_led, OUTPUT);
}

// Turn on LED corresponding to chosen board
void SRAM::WriteBoardLED ()
{
    digitalWrite(board_led, HIGH);
}

// Turn off LED corresponding to chosen board

void SRAM::ClearBoardLED ()
{
    digitalWrite(board_led, LOW);
}

// Write a single byte to the SRAM
// Parameters:
// - adr --> the address to write to
// - write_data --> data to write
void SRAM::WriteByte (unsigned int adr, char write_data)
{
    SetBoardMode(BYTE_MODE);
    adr &= 0x00FFFFFF; // Convert address to 24 bits
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    WriteBoardLED();
    digitalWrite(board_cs, LOW);
    SPI.transfer(WRITE);
    SPI.transfer((uint8_t) (adr >> 16));
    SPI.transfer((uint8_t) (adr >> 8));
    SPI.transfer((uint8_t) adr);
    SPI.transfer(write_data);
    digitalWrite(board_cs, HIGH);
    ClearBoardLED();
    SPI.endTransaction();
}

// Read a single byte from the SRAM
// Parameters:
// - adr --> the address to read from
// Returns:
// - read_data --> data read from device
uint8_t SRAM::ReadByte (unsigned int adr)
{
    SetBoardMode(BYTE_MODE);
    uint8_t read_data;
    adr &= 0x00FFFFFF; // Convert address to 24 bits
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    WriteBoardLED();
    digitalWrite(board_cs, LOW);
    SPI.transfer(READ);
    SPI.transfer((uint8_t) (adr >> 16));
    SPI.transfer((uint8_t) (adr >> 8));
    SPI.transfer((uint8_t) adr);
    read_data = SPI.transfer(0xFF); // Dummy
    digitalWrite(board_cs, HIGH);
    ClearBoardLED();
    SPI.endTransaction();
    return read_data;
}

// Set the mode register of the SRAM
// Parameters:
// - mode --> the target mode to set
void SRAM::SetBoardMode (uint8_t mode)
{
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    WriteBoardLED();
    digitalWrite(board_cs, LOW);
    SPI.transfer(WRMR);
    SPI.transfer(mode);
    digitalWrite(board_cs, HIGH);
    ClearBoardLED();
    SPI.endTransaction();
}

// Get the current board mode of the SRAM
// Returns:
// - current_mode --> the value of the mode register
uint8_t SRAM::GetBoardMode()
{
    uint8_t current_mode;
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    WriteBoardLED();
    digitalWrite(board_cs, LOW);
    SPI.transfer(RDMR);
    current_mode = SPI.transfer(0xFF); // Dummy
    digitalWrite(board_cs, HIGH);
    ClearBoardLED();
    SPI.endTransaction();
    return current_mode;
}

// Write alternating 1s and 0s to every bit of device memory
void SRAM::WriteCheckerboard()
{
    SetBoardMode(SEQ_MODE);
    unsigned int adr = 0 & 0x00FFFFFF;
    uint8_t checkerbyte = 170;
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    WriteBoardLED();
    digitalWrite(board_cs, LOW);
    SPI.transfer(WRITE);
    SPI.transfer((uint8_t) (adr >> 16));
    SPI.transfer((uint8_t) (adr >> 8));
    SPI.transfer((uint8_t) adr);
    for (int i=0; i<125000; i++)
    {
        SPI.transfer(checkerbyte);
    }
    digitalWrite(board_cs, HIGH);
    ClearBoardLED();
    SPI.endTransaction();
}
