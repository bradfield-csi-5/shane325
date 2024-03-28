package main

import (
    "bytes"
    "testing"
)

func TestPut(t *testing.T) {
    barDB := newDatabase()

    err := barDB.Put([]byte("hello"), []byte("world"))

    if err != nil {
        t.Errorf("Error putting data.")
    }
}

func TestDB(t *testing.T) {
    barDB := newDatabase()
    err := barDB.Seed("movies.csv")
    if err != nil {
        t.Errorf("Seed failed.")
    }

    err = barDB.Put([]byte("52"), []byte("Adams Family"))
    if err != nil {
        t.Errorf("Put failed")
    }

    err = barDB.Delete([]byte("15"))
    if err != nil {
        t.Errorf("Delete failed")
    }

    scan, err := barDB.RangeScan([]byte("10"), []byte("20"))
    if err != nil {
        t.Errorf("Scan failed")
    }

    scan.Next()
    scan.Next()
    scan.Next()

    if bytes.Equal(scan.Key(), []byte("12")) != true {
        t.Errorf("Scan Next failed.")
    }
}
