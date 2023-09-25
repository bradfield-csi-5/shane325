package main

import (
    "encoding/binary"
    "fmt"
    "net"
    "os"
    "strings"
)

const (
    SERVER_HOST = "8.8.8.8"
    SERVER_PORT = "53"
    SERVER_TYPE = "udp"
)

type DNSHeader struct {
    ID          uint16
    FLAGS       uint16
    QDCOUNT     uint16
    ANCOUNT     uint16
    NSCOUNT     uint16
    ARCOUNT     uint16
}

type DNSQuestion struct {
    QNAME       []byte
    QTYPE       uint16
    QCLASS      uint16
}

type DNSResourceRecord struct {
    
}


func main() {
    domain := os.Args[1]

    // Create a socket and bind to a port
    connection, err := net.Dial(SERVER_TYPE, SERVER_HOST+":"+SERVER_PORT)
    if err != nil {
        panic(err)
    }

    // Encode and send a query message
    var header DNSHeader
    header.ID = 8888
    header.FLAGS = 0x0100
    header.QDCOUNT = 1

    headerBuf := new(bytes.Buffer)
    binary.Write(headerBuf, binary.BigEndian, header)

    var question DNSQuestion
    var encodedDomain []byte
    labels := strings.Split(domain, ".")
    for _, label := range labels {
        encodedDomain = append(encodedDomain, byte(len(label))
        encodedDomain = append(encodedDomain, label...)
    }
    encodedDomain = append(encodedDomain, 0)
    question.QNAME = encodedDomain
    question.QTYPE = 1
    question.QCLASS = 1

    questionBuf := new(bytes.Buffer)
    binary.Write(questionBuf, binary.BigEndian, question)

    query := append(header, questions...)
    
    // Send data bytes using the `Write` function over our established connection
    _, err = connection.Write(query)
    if err != nil {
        fmt.Println("Error reading:", err.Error())
    }

    // Read data bytes using the `Read` function over our established connection

    // Decode a response message


    defer connection.Close()
}
