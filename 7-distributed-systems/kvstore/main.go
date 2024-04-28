package main

const FILEPATH = "kvstore.json"

func main() {
    store := newKvStore(FILEPATH)
    store.Run()
}
