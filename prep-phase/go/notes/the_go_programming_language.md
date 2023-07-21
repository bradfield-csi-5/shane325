## The Go Programming Language
Go was conceived in 2007 at Google. The goals of the language and it's tools were to be expressive, efficient in both compilation and execution, and effective in writing reliable and robust programs

### 1. Tutorial
This chapter is a tour of the basic components of Go.

#### 1.1 Hello, World
- `C` is one of the most direct influences on `Go`.

```go
package main

import "fmt"

func main() {
    fmt.Println("Hello, World")
}
```
- The Go toolchain is accessed via a single command called `go` that has a number of subcommands.
```bash
$ go run helloworld.go    # Compile, link, and run a go program
$ go build helloworld.go  # Compile a go program
```
- For a full list of subcommands see the [official Go documentation](https://pkg.go.dev/cmd/go).

#### 1.2 Command-Line Arguments
- The [os package](https://pkg.go.dev/os) lets us interact with the host operating system.
- Command line variables come from `os.Args`.
- `os.Args[0]` is the name of the command itself and the following elements are the command line options passed in.
- `os.Args[1:]` will get you just the command line arguments.

```go
package main

import (
    "os"
    "fmt"
)

func main() {
    var s, sep string
    for i:= 1; i < len(os.Args); i++ {
        s += sep + os.Args[i]
        sep = " "
    }
    fmt.Println(s)
}
```

- The `for` loop is the only loop statement in Go.
- You can also use `for` to iterate over a `range` of values:

```go
package main

import (
    "os"
    "fmt"
)

func main() {
    s, sep := "", ""
    for _, arg := range os.Args[1:] {
        s += sep + arg
        sep = " "
    }
    fmt.Println(s)
}
```

- The underscore tells Go that we don't want to use this value.
- There are multiple ways we can declare a variable:

```go
s := ""
var s string
var s string = ""
var s = ""
```

- In practice, you should use one of the first two methods of declaring variables. It's worth noting that the first, shorthand method, only works inside of functions. It does not work at the package-level.

#### 1.3 Finding Duplicate Lines
- This version of a program called `dup` prints each line that appears more than once in the standard input.
- It introduces the `if` statement, the `map` data type, and the `bufio` package.

```go
// Dup 1
package main

import (
    "bufio"
    "fmt"
    "os"
)

func main() {
    counts := make(map[string]int)
    input := bufio.NewScanner(os.Stdin)
    for input.Scan() {
        counts[input.Text()]++
    }

    for line, n := range counts {
        if n > 1 {
            fmt.Printf("%d\t%s\n", n, line)
        }
    }
}
```

- The built in function `make` creates a new empty map; it has other uses too.
- A `map` holds a set of key/value pairs and provides constant time operations.
- The [bufio](https://pkg.go.dev/bufio) package helps make input and output efficient and convenient.
- `fmt.Printf` has over a dozen conversion similar to `%d` (called verbs) which formats an integer using decimal notation.
- See [Go Formatting Verbs](https://www.w3schools.com/go/go_formatting_verbs.php) for a complete list.

#### 1.4 Animated Gifs
- This section introduces the following new concepts, but does not go into too much detail about them:
    - `const` declarations.
    - `struct types`.
    - `composite literals` which are a compact notation for instantiating any of Go's composite types from a sequence of element values.

#### 1.5 Fetching a URL
- Go provides a collection of packages grouped under `net`, that make it easy to send and receive information throught the Internet.

```go
// Fetch prints the contents found at each specified URL.
package main

import (
    "fmt"
    "io.ioutil"
    "net/http"
    "os"
)

func main() {
    for _, url := range os.Args[1:] {
        resp, err := http.Get(url)
        if err != nil {
            fmt.Fprintf(os.Stderr, "fetch: %v\n", err)
            os.Exit(1)
        }
        b, err := ioutil.ReadAll(resp.Body)
        resp.Body.Close()
        if err != nil {
            fmt.Fprintf(os.Stderr, "fetch: reading %s: %v\n", url, err)
            os.Exit(1)
        }
        fmt.Printf("%s", b)
    }
}
```

- Here we see functions from two new packages, `net/http` and `io/ioutil`.
- `http.Get` makes an http request and returns the result is a response struct called `resp`.
- The `Body` field of `resp` contains the server response as a readable stream.
- `ioutil.ReadAll` reads the entire response; the result is stored in `b`. Then, the `Body` steam is closed to avoid leaking resources.

#### 1.6 Fetching URLs Concurrently
- `Go` has support for concurrent programming.

```go
// Fetchall fetches URLs in parallel and reports their times and sizes.
package main

import (
    "fmt"
    "io"
    "io/ioutil"
    "net/http"
    "os"
    "time"
)

func main() {
    start := time.Now()
    ch := make(chan string)
    for _, url := range os.Args[1:] {
        go fetch(url, ch) // Start a goroutine
    }
    for range os.Args(1:) {
        fmt.Println(<-ch) // Receive from channel ch
    }
    fmt.Printf("%.2fs elapsed\n", time.Since(start).Seconds())
}

func fetch(url string, ch chan<- string) {
    start := time.Now()
    resp, err := http.Get(url)
    if err != nil {
        ch <- fmt.Sprint(err) // Send to channel
        return
    }

    nbytes, err := io.Copy(ioutil.Discard, resp.Body)
    resp.Body.Close() // Don't leak resources
    if err != nil {
        ch <- fmt.Sprintf("while reading %s: %v", url, err)
        return
    }
    secs := time.Since(start).Seconds()
    ch <- fmt.Sprintf("%.2fs %7d %s", secs, nbytes, url)
}
```

- A `goroutine` is a concurrent function execution.
- A `channel` is a communication mechanism that allows one `goroutine` to pass values of a specified type to another `goroutine`.
- The function `main` runs in a `goroutine` and the `go` statement creates additional `goroutines`.
- The `main` function creates a channel of strings using `make`.
- The `io.Copy` function reads the body response and discards it by writing to the `ioutil.Discard` output stream.

#### 1.7 A Web Server

```go
// Server1 is a minimal "echo" server.
package main

import (
    "fmt"
    "log"
    "net/http"
)

func main() {
    http.HandleFunc("/", handler) // each request calls handler
    log.Fatal(http.ListenAndServe("localhost:8000", nil))
}

// Handler echoes the Path component of the requested URL.
func handler(w http.ResponseWriter, r *http.Request) {
    fmt.Fprintf(w, "URL.Path = %q\n", r.URL.Path)
}
```

- This program is short because library functions do most of the work.

#### 1.8 Loose Ends
- We covered the two foundational control flow statments, `if` and `for`, but not the `switch` statement.

```go
switch coinflip() {
    case "heads":
        heads++
    case "tails":
        tails++
    default
        fmt.Println("landed on edge!")
}
```

- Switch cases **do not** fall through from one the next as in C-like languages.
- The `break` and `continue` statements modify the flow of control.
- Other loose ends that we will learn more about in detail are:
    - Named types.
    - Pointers.
    - Methods and interfaces.
    - Packages.
    - Comments
