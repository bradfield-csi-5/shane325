package main

import (
    "fmt"
    "log"
)

func main() {
    // Instantiate a new database
    barDB := newDatabase()

    // Seed the database
    err := barDB.Seed("movies.csv")
    if err != nil {
        log.Fatal(err)
    }


    barDB.Put([]byte("52"), []byte("Adams Family"))
    barDB.Delete([]byte("24"))
    barDB.Put([]byte("14"), []byte("Godfather"))

    scan, err := barDB.RangeScan([]byte("10"), []byte("20"))

    for scan.Next() {
        fmt.Printf("key: %s, value: %s.\n", scan.Key(), scan.Value())
    }

    barDB.Put([]byte("140"), []byte("Finding Nemo"))
    barDB.Put([]byte("99"), []byte("Shrek"))
    barDB.Put([]byte("75"), []byte("Gladiator"))

    // barDB.Print()
}
