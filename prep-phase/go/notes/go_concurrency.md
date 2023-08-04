## Concurrency in Go

- A big selling point of Go is that it supports concurrency.
- It's worth noting that concurrency is not the same as parallelism.
- Concurrency is about breaking up a program into independently executing tasks that _could_ run at the same time and still give the right result at the end.

- The following example is a syncronous program. There is no concurrency here:

```go
package main

import (
    "fmt"
    "time"
)

func main() {
    count("sheep")
    count("fish")
}

func count(thing string) {
    for i := 1; true; i++ {
        fmt.Println(i, thing)
        time.Sleep(time.Millisecond * 500)
    }
}
```

- In the above program, the `count("fish")` line will never be reached because `count` has an infinite loop. It'll just count sheep forever and never get to the fish.
- If we put the keyword `go` in front of the call to `count("fish")` it will run it in the background and carry on with the rest of the function execution. We have created a **goroutine**.
- Our `main` function is also a `goroutine`.
- If we add `go `before both calls to `count`, effectively kicking off two `goroutines`, nothing happens. This is because our `main` function finishes execution and terminates the program before our `goroutines` could do anything.
- To fix this, we can use a `wait group`.

```go
import "sync"

func main() {
    var wg sync.WaitGroup
    wg.Add(1)

    go func() {
        count("sheep")
        wg.Done()
    }()

    wg.Wait()
}
```

- A wait group is nothing crazy, it's just a counter that keeps track of how many `goroutines` have been created.
- `wg.Wait()` will halt execution until the number of go routines still running is zero.
- Thats how to create a goroutine. Really simple but not massively useful so far. What we need next are `channels`.

- A channel is a way for goroutines to communicate with each other. What if we wanted our `count` function to communicate back to the `main` go routine.
- A channel is like a (typed) pipe, where you can send a message and receive a message. Sending and receiving across channels is a blocking operation.

```go
package main

import (
    "fmt"
    "time"
)

func main() {
    c := make(chan string)
    go count("sheep", c)

    msg := <- c
    fmt.Println(msg)
}

func count(thing string, c chan string) {
    for i := 1; i <= 5; i++ {
        c <- thing
        time.Sleep(time.Millisecond * 500)
    }
}
```

- The above program will output _sheep_ just once.
- This blocking nature of channels allows us to use them to syncronize go routines.
- What if we wanted to receive more that one _sheep_. We can place our `msg` variable inside a `for` loop but the channel sender (`count`) will have to close the channel when it's done sending.
- Or we can put our receiver in a `for range` loop and the loop will terminate when the channel is closed (we don't have to manually check).

```go
for msg := range c {
    fmt.Println(msg)
}

// count()...
close(c)
```

- There's also a common pattern called `worker pools`. This is where you have a queue of things to be done and a worker is pulling things off the queue.
