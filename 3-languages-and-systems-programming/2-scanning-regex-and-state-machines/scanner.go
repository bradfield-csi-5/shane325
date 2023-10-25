package main

import (
    "fmt"
    "log"
    "os"
    "strings"
)

type Token struct {
    Type  string
    Lexeme  string
}

func main() {
    if (len(os.Args) > 2) {
        log.Fatal("Too many cmd line arguments.")
    }

    source := os.Args[1]
    lexemes := strings.Split(source, " ")
    tokens := []Token{}

    for i := 0; i < len(lexemes); i++ {
        lexeme := lexemes[i]
        switch lexeme {
            case "AND":
                tokens = append(tokens, Token{ "AND", lexeme })
            case "OR":
                tokens = append(tokens, Token{ "OR", lexeme })
            case "NOT":
                tokens = append(tokens, Token{ "NOT", lexeme })
            default:
                tokens = append(tokens, Token{ "STRING", lexeme })
        }
    }

    fmt.Println(tokens)
}
