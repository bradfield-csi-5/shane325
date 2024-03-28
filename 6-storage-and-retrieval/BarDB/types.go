package main

type DB interface {
    // Get gets the value for the given key. Returns an error if the
    // DB does not contain the key.
    Get(key []byte) (value []byte, err error)

    // Has returns true if the DB contains the key.
    Has(key []byte) (ret bool)

    // Put sets the value for the given key. It overwrites any previous value
    // for that key; a DB is not a multi-map.
    Put(key, value []byte) (err error)

    // Delete deletes the value for the given key.
    Delete(key []byte) (err error)

    // RangeScan returns an Iterator for scanning through all
    // key-value pairs in a given range, ordered by key ascending.
    RangeScan(start, limit []byte) (iter Iterator, err error)

    // Print prints the key value pairs
    Print()

    // Order the key value pairs by key
    Order()

    // Seed the database with test data
    Seed(file string) (err error)
}

type Iterator interface {
    // Next moves the iterator to the next key/value pair.
    // It returns false if the iterator is exhausted.
    Next() bool

    // Error returns any accumulated error. Exhausting all the key/value pairs
    // is not considered to be an error.
    Error() error

    // Key returns the key of the current key/value pair, or nil if done.
    Key() []byte

    // Value returns the value of the current key/value pair, or nil if done.
    Value() []byte
}
