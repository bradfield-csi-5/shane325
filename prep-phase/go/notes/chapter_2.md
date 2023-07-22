[Home](https://github.com/bradfield-csi-5/shane325/blob/main/prep-phase/go/notes/the_go_programming_language.md)

### 2. Program Structure
This chapter goes into more detail about the basic structural elements of a Go program.

#### 2.1 Names
- A name begins with a letter or an underscore and may have any number of additional letters, digits, and underscores.
- Case matters.
- If the name begins with an upper-case letter, it is exported, which means this it is visible and accessible outside of its own package.
- Package names are always in lower case.

#### 2.2 Declarations
- There are four major kinds of declarations: `var`, `const`, `type`, and `func`.

#### 2.3 Variables
- A `var` declaration creates a variable of a specific type.
- If the type is ommited, is it determined by the initializer expression.
- If the initializer expression is omitted, the initial value is the _zero value_ for the type, which is `0` for numbers, `false` for booleans, `""` for strings, and `nil` for interfaces and reference types (slice, pointer, map, channel, function).

#### 2.3.1 Short Variable Declarations
- Because of their brevity, short variable declarations are used to declare and initilize the majority of local variables.

```go
i := 100                    // an int
var boiling float64 = 100   // a float64
name := "shane"             // a string
```

#### 2.3.2 Pointers
- A _pointer_ value is the _address_ of a variable.
- With a pointer, we can read or update the value of a variable _indirectly_, without using or even knowing the name of the variable, if indeed it has a name.
- If we have a variable `var x int`, the expression `&x` yields the address of `x`. This is a pointer to an integer variable (`*int`). If this value (`&x`) is called `p`, we say "p points to x", or "p contains the address of x".
- The variable to which p points is written `*p`. The expression `*p` yields the value of that variable (`x`).

```go
x := 1
p := &x         // p, of type *int, points to x
fmt.Println(*p) // "1"
*p = 2
fmt.Println(x)  // "2"
```

- Each component of a variable of aggregate type - a field of a struct or an element of an array - is also a variable and thus has an address too.

```go
var p = f()

func f() *int {
    v := 1
    return &v
}
```

- each call of `f` returns a distinct value.

```go
fmt.Println(f() == f())     // "false"
```

#### 2.3.3 The `new` Function
- Another way to create a variable is to use the built in `new` function.
- The expression `new(t)` creates an _unnamed variable_ of type T, initializes it to the zero value of type T, and returns its address, which is a value of type `*T`.

```go
p := new(int)
fmt.Println(*p)     // "0"
fmt.Println(p)      // Prints the address of the variable
*p = 2
fmt.Println(*p)     // "2"
```

#### 2.3.4 Lifetime of Variables
- The lifetime of a package level variable is the entire execution of the program.
- Local variables have dynamic lifetimes: the variable lives on until it becomes unreachable, at which point its storage may be recycled.

#### 2.4 Assignments
```go
x = 1                       // named variable
*p = true                   // indirect variable
person.name                 // struct field
count[x] = count[x] * scale // array of slice or may element
```

- Each of the arithmetic and bitwise operators has a corresponding _assignment operator_ so we can do:

```go
count[x] *= scale
```

- We can increment and decrement with `++` and `--`.

#### 2.4.1 Tuple Assignment
- _tuple assignment_ allows several variables to be assigned at once.

    ```go
x, y = y, x
a[i], a[j] = a[j], a[i] // swap values
    ```

- All of the right hand side expressions are evaluated before any of the variables are updated.

```go
// Computing the nth Fibonacci number iteratively
func fib(n int) int {
    x, y := 0, 1
    for i := 0; i < n; i++ {
        x, y = y, x+y
    }
    return x
}
```

- Some expressions produce several values (such as a function call with multiple results).

```go
f, err = os.Open("foo.txt")     // function call returns two values
```

#### 2.4.2 Assignability
- An assignment, explicit or implicit, is always legal if the left-hand side (the variable) and the right-hand side (the value) have the same type.

#### 2.5 Type Declarations
- A type decalaration defines a new _named_ type that has the same underlying type as an existing type.
- `type _name_ _underlying-type_`.

```go
type Celsius float64
type Fahrenheit float64
```

- We just defined two names types. The underlying types are `float64`.
- For every type T, there is a corresponding conversion operation T(x) that converts the value x to type T.
- A conversion of one type to another is allowed if both have the same underlying type.

#### 2.6 Packages and Files
- Packages in Go server the same purposes as libraries or modules in other languages.
- In Go, a simple rule governs which identifiers are exported and which are not: exported identifiers start with an upper-case letter.
- Each file starts with a package delcaration that defines the package name: `package tempconv`.
- Package level names like types and constants declared in one file of a package are visible to all the other files of the package, as if the source code were all in a single file.

#### 2.6.1 Imports
```go
package main

import (
    "fmt"
    "os"
    "gopl.io/ch2/tempconv"  // import path
)

func main() {
    f := tempconv.Fahrenheit(100.14)    // Calling a method from our imported package
}
```

#### 2.6.2 Package Initialization
- Package initialization starts by initializing package-level variables in the order in which they are declared, except that dependencies are resolved first.
- One package is initialized at a time, in the order of imports in the program, dependencies first.
- A package `p` importing `q` can be sure that `q` is fully initialized before `p`'s initialization begins.
- We also have an `init` function that can pre-compute before our main program runs.

#### 2.7 Scope
- Don't confuse scopr with liftime.
- The scope of a declaration is a region of the program text; it is a compile-time property.
- The lifetime of a variable is the range of time during execution when the variable can be referred to by other parts of the program; it is a run-time property.
- A declarations lexical block determines its scope.
