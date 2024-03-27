package main

type ScanIterator struct {
    values []Value
    idx int
    err error
}

func (s *ScanIterator) Next() bool {
    if s.idx < len(s.values) {
        s.idx++
        return true
    }
    return false
}

func (s *ScanIterator) Error() error {
    return s.err
}

func (s *ScanIterator) Key() []byte {
    if s.idx < len(s.values) {
        return s.values[s.idx].key
    }
    return nil
}

func (s *ScanIterator) Value() []byte {
    if s.idx < len(s.values) {
        return s.values[s.idx].value
    }
    return nil
}

func newScanIterator(values []Value) Iterator {
    return &ScanIterator{
        values: values,
        idx: -1,
        err: nil,
    }
}
