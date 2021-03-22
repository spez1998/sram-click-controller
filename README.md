# sram-click-controller
A class to control MikroE's [SRAM Click](https://www.mikroe.com/sram-click) boards. The target device is the [ARM Flip & Click](https://www.mikroe.com/flip-n-click-sam3x) microcontroller, although any ARM-based microcontroller with MikroBUS support will work with edits to the header files.

## Prerequisites
- Flip & Click board
- SRAM Click board
- Arduino IDE

## Usage
An example .ino file is provided to illustrate code usage.

First, create an instance of the SRAM class:

```c++
SRAM sram_inst(usr_socket_choice);
```
### Parameters:

|                           |                                                             |     |
| ------------------------- | ----------------------------------------------------------- | --- |
| usr_socket_choice, *char* | Letter of MikroBUS socket that target board is plugged into |
| ---                       | ---                                                         | --- |

The ```sram_inst``` object is now assigned to a board at the socket specified.

### Attributes:

|                  |                                        |     |
| ---------------- | -------------------------------------- | --- |
| board_cs, *int*  | Pin number of target socket CS pin     |
| board_led, *int* | Pin number of corresponding socket LED |
| ---              | ---                                    | --- |

### Methods:
|     |     |  |
| --- | --- ||
| WriteBoardLED(); | Turn on target board's socket LED  |
| ClearBoardLED(); | Turn off target board's socket LED |
| WriteByte(*adr, write_data*); | Write *write_data* target device at memory location *adr*  |
| ReadByte(*adr*); | Read from address *adr* of target device |
| GetBoardMode(); | Return current mode of target device |
| SetBoardMode(*mode*); | Set target device to *mode* |
| WriteCheckerboard(); | Write alternating 1s and 0s throughout target device memory |
| ----------------------------- | ----- |  |

```c++
WriteBoardLED();
```
No parameters, returns nothing.

```c++
ClearBoardLED();
```
No parameters, returns nothing.

```c++
WriteByte(adr, write_data);
```
Parameters:
- **unsigned int** *adr*: address to write to
- **char** *write_data*: byte to write

Returns nothing.

```c++
ReadByte(adr);
```
Parameters:
- **unsigned int** *adr*: address to read from
  
Returns:
- **uint8_t** *read_data*: byte at *adr*

```c++
GetBoardMode();
```
No parameters.

Returns:
- **uint8_t** *current_mode*: contents of device mode register

```c++
SetBoardMode(mode);
```
Parameters:
- **uint8_t** *mode*: byte to write to device mode register
  
Returns nothing.

```c++
WriteCheckerboard();
```
No parameters, returns nothing.

## Notes about device operation
The Flip & Click microcontroller communicates with each SRAM Click via a shared SPI bus. Calling SPI-related functions in the Arduino IDE will write to this shared bus. To transfer the SPI data to a desired board, the chip select (CS) line of that specific board must be brought low (and then high again when the transaction ends). Each time the CS line is brought high from a low state, the device is powered off, and its mode register is reset. Therefore, before each SPI transaction, the mode register of the board's SRAM chip is asserted.