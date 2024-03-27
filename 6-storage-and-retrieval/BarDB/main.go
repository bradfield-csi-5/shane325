package main

import (
    "encoding/csv"
    "fmt"
    "io"
    "log"
    "os"
)

func main() {

    // Open file so that we can grab some test data
    f, err := os.Open("./movies.csv")
    if err != nil {
        log.Fatal(err)
    }
    // Close the file at the end of the program
    defer f.Close()
    // Read csv values using csv.Reader
    csvReader := csv.NewReader(f)
    // Skip the csv header row
    _, err = csvReader.Read()
    if (err != nil) {
        log.Fatal(err)
    }

    // Instantiate a new database
    barDB := newDatabase()

    // Populate our new database with movie data
    for {
        movieRecord, err := csvReader.Read()
        if err == io.EOF {
            break
        }

        err = barDB.Put([]byte(movieRecord[0]), []byte(movieRecord[1]))
        if err != nil {
            log.Fatal(err)
        }
    }

    barDB.Put([]byte("52"), []byte("Adams Family"))
    barDB.Delete([]byte("24"))
    barDB.Put([]byte("14"), []byte("Godfather"))

    scan, err := barDB.RangeScan([]byte("10"), []byte("20"))

    for scan.Next() {
        fmt.Printf("key: %s, value: %s.\n", scan.Key(), scan.Value())
    }
}
