### Binary Representations of Data

Here are my answers to some of the prework for this class.

#### 1.1 Simple conversion
- `0x9`
- `0x88`
- `0xf7`

#### 1.2 CSS colors
- Our answer is a power of two.
- Each of our 3 bytes can represent 8 bits each to give a total of 24 bits.
- 2^24 is 16,777,216.

#### 1.3 Say hello to hellohex
- We would expect 34 hexadecimal characters (17 bytes x 2).

The first 5 bytes converted to binary are:
- `0b01101000`
- `0b01100101`
- `0b01101100`
- `0b01101100`
- `0b01101111`

#### 2.1 Integers basic conversion

- `0b100`
- `0b1000001`
- `0b1101001`
- `0b11111111`

- `2`
- `3`
- `108`
- `85`

#### 2.2 Unsigned binary addition
```
11111111
00001101
--------
00001100 (12)
```

- We have demonstrated integer overflow.

#### 2.3 Two's complement conversion
- `0b01111111`
- `0b10000000`
- `0b11111111`
- `0b00000001`
- `0b11110010`

- `-125`
- `-60`

#### 2.4 Addition of two's complement signed integers
```
01111111 (127)
10000000 (-128)
--------
11111111 (-1)
```

- To negate a number in two's complement you just flip the bits and add one.
- To substract you negate the second argument then add it to the first.
- -128 is the most signifigant bit in an 8 bit two's complement number.

#### 2.5 Advanced: Integer overflow detection
- We need a way to detect overflow in two's complement (based solely on bit patterns).
- The way we do that is we look at the _carry out_ value (is there an extra bit carried out after our arithmetic?) and we look at the _carry in_ value (did we carry in a bit to the most significant place?) and we `XOR` them.
- The operation to determine integer overflow for two's compliment is `XOR(carry_in, carry_out)`.
- As a reminder, `XOR` returns true if the number of true values is odd.

**XOR example**
| A | B | A XOR B |
|---|---|---------|
| 0 | 0 | 0       |
| 0 | 1 | 1       |
| 1 | 0 | 1       |
| 1 | 1 | 0       |

#### 3 Byte ordering
- For the decimal number 123:
- `123` is big endian ordering.
- `321` is little endian ordering.
- Ordering, typically, doesn't impact the individual bit order because the smallest unit of data that we retrieve from RAM is a byte (8 bits).
- But if we have a _multi-byte_ value, we need to decide whether the highest order bytes should come first (big endian) or last (little endian).

#### 3.1 It's over 9000!
- Converting the value `9001` to binary we can see that it's encoded as big endian in our file.

#### 3.2 TCP
- Uses big endian byte ordering, like most network protocols.
- Sequence number: 1142846312
- Ack number: 4025655458
- Source port: 44800
- Destination port: 48134

#### 3.3 Bonus: Byte ordering and integer encoding in bitmaps
- `BM` format.
- Width: 24.
- Height: 48.
- Bitmap image data starts at `0x8a`.
- All white and all red.

#### 4 IEEE Floating Point
- A format used to represent numbers ranging from the unimaginably subatomic to well beyond astronomical.
- It borrows extensively from the idea of scientific notation.
- Floating point is scientific notation in base 2.

#### 4.1 Deconstruction
- Sign: 0
- Exponent: 10000100
- Mantissa: 01010100000000000000000
- Value: 42.5

- The smallest change is achieved by flipping the least significant bit of the mantessa to 1.

- As the size of the number increases, the precision decreases. We lose precision with higher numbers.

#### 5.1 Snowman
- 3 bytes total.

#### 5.2 Hello again hellohex
- `hello`.
- This file is UTF-8 encoded.

#### 5.3 Bonus: Ding ding ding!
- `man ascii` to find the value of the bell character (7 or 0x07).
- `echo '070707' | xxd -r -p`.
