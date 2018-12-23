# pic16f18346_uart_ledarray

### Specification
UART Baudrate 19200bps

### Input

| pin | description |
|---|---|
| 1 | GND |
| 2 | DC 5-9V |
| 3 | UART TX |
| 4 | UART RX |

### Output


### Command

| index | description |
|---|---|
| 0-1 | version |
| 2-3 | body size |
| 4-13 | body |

#### version 01

* 0
    * off
* 1
    * on

// 010A0100000000
// 010A1000000000
// 010A0100000000
// 010A0010000000
// 010A0001000000
// 010A0000100000
// 010A0000010000
// 010A0000001000
// 010A0000000100
// 010A0000000010
// 010A0000000001
// 010A1111111111