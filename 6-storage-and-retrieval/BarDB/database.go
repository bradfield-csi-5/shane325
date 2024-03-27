package main

import (
    "bytes"
    "errors"
    "fmt"
)

type Database struct {
    values []Value
    idx int
}

type Value struct {
    key []byte
    value []byte
}

func (db *Database) Get(key []byte) ([]byte, error) {
    for i := 0; i < len(db.values); i++ {
        if bytes.Equal(key, db.values[i].key) {
            return db.values[i].value, nil
        }
    }

    return []byte{}, errors.New("no key found")
}

func (db *Database) Has(key []byte) bool {
    for i := 0; i < len(db.values); i++ {
        if bytes.Equal(key, db.values[i].key) {
            return true
        }
    }
    return false
}

func (db *Database) Put(key, value []byte) error {
    // First try to find the key
    for i := 0; i < len(db.values); i++ {
        if bytes.Equal(key, db.values[i].key) {
            db.values[i].value = value
            return nil
        }
    }

    // If we get here, the key does not exist yet
    db.values = append(db.values, Value{key, value})
    return nil
}

func (db *Database) Delete(key []byte) error {
    for i := 0; i < len(db.values); i++ {
        if bytes.Equal(key, db.values[i].key) {
            db.values = append(db.values[:i], db.values[i+1:]...)
            return nil
        }
    }
    return errors.New("no key found")
}

func (db *Database) RangeScan(start, limit []byte) (Iterator, error) {
    startIdx := -1
    limitIdx := -1

    for i := 0; i < len(db.values); i++ {
        if bytes.Equal(start, db.values[i].key) {
            startIdx = i
        } else if bytes.Equal(limit, db.values[i].key) {
            limitIdx = i
        }
    }

    if startIdx == -1 || limitIdx == -1 {
        return nil, errors.New("Couldn't find index")
    }

    newScanIterator := newScanIterator(db.values[startIdx:limitIdx+1])
    return newScanIterator, nil
}

func (db *Database) Print() {
    for i := 0; i < len(db.values); i++ {
        fmt.Printf("key: %s, value: %s.\n", db.values[i].key, db.values[i].value)
    }
}

func newDatabase() DB {
    return &Database{
        values: []Value{},
        idx: -1,
    }
}
