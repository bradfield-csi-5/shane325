package main

import (
    "fmt"
    "golang.org/x/sys/unix"
)

func main() {
    // Create a socket
    socketFD, err := unix.Socket(unix.AF_INET, unix.SOCK_STREAM, unix.IPPROTO_IP)
    if err != nil {
        panic(err)
    }
    defer unix.Close(socketFD)

    // Bind an address to our socket
    serverAddr := &unix.SockaddrInet4{
        Port: 8080,
        Addr: [4]byte{127, 0, 0, 1},
    }
    err = unix.Bind(socketFD, serverAddr)
    if err != nil {
        panic(err)
    }
    fmt.Printf("Server: Bound to addr: %d, port: %d\n", serverAddr.Addr, serverAddr.Port)

    // Listen on our socket
    err = unix.Listen(socketFD, 100)
    if err != nil {
        panic(err)
    }

    // Accept a connection on our socket
    acceptedSocketFD, _, err := unix.Accept(socketFD)
    if err != nil {
        panic(err)
    }
    defer unix.Close(acceptedSocketFD)

    // Receive a message
    msg := make([]byte, 8000)
    msgSize, _, err := unix.Recvfrom(acceptedSocketFD, msg, 0)

    fmt.Printf("%d\n", msgSize)
    str := string(msg)
    fmt.Println(str)
}
