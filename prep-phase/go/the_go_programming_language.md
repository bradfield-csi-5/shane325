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
