/**
 * Virual Machine implementation.
 *
 * This is a program that simulates the behavior of computer hardware
 */
package main

import (
    "fmt"
    "os"
)

func main() {
    // Define our memory array
    byteArray := []byte{0x00, 0x03, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x01, 0x00, 0xff}

    fmt.Println("Memory before:")
    fmt.Println(byteArray)
    fmt.Println()

    // Call our vm.
    vcpu(&byteArray)

    fmt.Println("Memory after:")
    fmt.Println(byteArray)
}

func vcpu(memory *[]byte) {
    // Define an array of registers.
    // Program counter and two general purpose registers (all initially set to zero).
    registers := []byte{0, 0, 0}

    // Set the pc value
    registers[0] = 8

    // Kick of the "fetch-decode-execute" cycle until we hit a `halt` or reach memory capacity.
    for registers[0] < 255 {
        // Fetch.
        pc := registers[0]
        value := (*memory)[pc]

        // Decode and execute.
        if value == 255 {
            break
        } else {
            switch value {
                case 1:
                load(memory, &registers, (*memory)[pc+1], (*memory)[pc+2])
                case 2:
                store(memory, &registers, (*memory)[pc+1], (*memory)[pc+2])
                case 3:
                add(memory, &registers, (*memory)[pc+1], (*memory)[pc+2])
                case 4:
                sub(memory, &registers, (*memory)[pc+1], (*memory)[pc+2])
                default:
                fmt.Println("No valid instruction found!\n")
            }
        }

        // Increment the program counter
        registers[0] = registers[0] + 3
    }
}

/**
 * Load value at given address (`data`) into register (`reg`)
 */
func load(memory *[]byte, r *[]byte, reg byte, data byte) {
    if data < 1 || data > 7 {
        fmt.Println("Load: Byte index is out of bounds!\n")
        os.Exit(1)
    } else if reg != 1 && reg != 2 {
        fmt.Println("Load: Invalid register index!\n")
        os.Exit(1)
    }

    (*r)[reg] = (*memory)[data]
}

/**
 * Store the value at given address (`reg`) into the location of address (`data`).
 */
func store(memory *[]byte, r *[]byte, reg byte, data byte) {
    if data < 0 || data > 7 {
        fmt.Println("Store: Byte index is out of bounds!\n")
        os.Exit(1)
    } else if reg != 1 && reg != 2 {
        fmt.Println("Store: Invalid register index!\n")
        os.Exit(1)
    }

    (*memory)[data] = (*r)[reg]
}

/**
 * Add the two reg values and store the result in r1
 */
func add(memory *[]byte, r *[]byte, r1 byte, r2 byte) {
    if (r1 != 1 && r1 != 2) || (r2 != 1 && r2 != 2) {
        fmt.Println("Add: Invalid register index!\n")
        os.Exit(1)
    }

    (*r)[r1] = (*r)[r1] + (*r)[r2]
}

/**
 * Subtract the two reg values and store the result in r1
 */
func sub(memory *[]byte, r *[]byte, r1 byte, r2 byte) {
    if (r1 != 1 && r1 != 2) || (r2 != 1 && r2 != 2) {
        fmt.Println("Sub: Invalid register index!\n")
        os.Exit(1)
    }

    (*r)[r1] = (*r)[r1] - (*r)[r2]
}
