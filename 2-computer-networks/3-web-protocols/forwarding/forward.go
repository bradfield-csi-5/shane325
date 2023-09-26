package main

import (
    "fmt"
    "log"
    "golang.org/x/sys/unix"
)

func main() {
    // Create a socket
    socketFD, err := unix.Socket(unix.AF_INET, unix.SOCK_STREAM, unix.IPPROTO_IP)
    if err != nil {
        log.Fatal("Create: ", err)
    }
    defer unix.Close(socketFD)

    // Bind an address to our socket
    serverAddr := &unix.SockaddrInet4{
        Port: 8081,
        Addr: [4]byte{127, 0, 0, 1},
    }
    err = unix.Bind(socketFD, serverAddr)
    if err != nil {
        log.Fatal("Bind: ", err)
    }
    fmt.Printf("Server: Bound to addr: %d, port: %d\n", serverAddr.Addr, serverAddr.Port)

    // Listen on our socket
    err = unix.Listen(socketFD, 100)
    if err != nil {
        log.Fatal("Listen: ", err)
    }

    // Accept a connection on our socket
    acceptedSocketFD, _, err := unix.Accept(socketFD)
    if err != nil {
        log.Fatal("Accept: ", err)
    }
    defer unix.Close(acceptedSocketFD)

    // Receive a message
    msg := make([]byte, 100)
    _, _, err = unix.Recvfrom(acceptedSocketFD, msg, 0)
    if err != nil {
        log.Fatal("Recvfrom: ", err)
    }

    // str := string(msg)
    // fmt.Println(str)

    // Forward the message
    forwardServerAddr := &unix.SockaddrInet4{
        Port: 8082,
        Addr: [4]byte{127, 0, 0, 1},
    }
    err = unix.Sendmsg(acceptedSocketFD, msg, nil, forwardServerAddr, unix.MSG_DONTWAIT)
    if err != nil {
        log.Fatal("Sendmsg: ", err)
    }
}
