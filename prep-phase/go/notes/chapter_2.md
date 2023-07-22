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

#### 2.4 Assignments

#### 2.4.1 Tuple Assignment

#### 2.4.2 Assignability

#### 2.5 Type Declarations

#### 2.6 Packages and Files

#### 2.6.1 Imports

#### 2.6.2 Package Initialization

#### 2.7 Scope
