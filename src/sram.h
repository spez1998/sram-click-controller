// SRAM.h -- class to control SRAM Click Boards
// Created by Sujit Malde, 2021

#ifndef SRAM_h
#define SRAM_h

#include <string>
#include <SPI.h>
#include "sram_opcodes.h"
#include "flip_click_defs.h"

#define EDIO      0x3B
#define EQIO      0x38
#define RDMR      0x05
#define READ      0x03
#define RSTIO     0xFF
#define WRITE     0x02
#define WRMR      0x01

#define BYTE_MODE 0x00
#define PAGE_MODE 0xC0
#define SEQ_MODE  0x40

class SRAM
{
    public:
        int board_cs; // Board CS line number
        int board_led; // Board corresponding LED line number
        SRAM(int usr_socket_choice);
        void WriteBoardLED();
        void ClearBoardLED();
        uint8_t GetBoardMode();
        void SetBoardMode(uint8_t mode);
        void CheckBoardMode(uint8_t board_cs, uint8_t target_mode);
        uint8_t ReadByte(unsigned int adr);
        void WriteByte(unsigned int adr, char write_data);
        void WriteCheckerboard ();
};

#endif
