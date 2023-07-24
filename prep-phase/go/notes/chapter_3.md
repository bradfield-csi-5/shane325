[Home](https://github.com/bradfield-csi-5/shane325/blob/main/prep-phase/go/notes/the_go_programming_language.md)

### 3. Basic Data Types
Go's types fall into four categories: _basic types_, _aggregate types_, _reference types_, and _interface types_. This chaper focuses on basic types. They are numbers, strings, and booleans.

#### 3.1 Integers
- Go has 4 distinct sizes for both signed, and unsigned integers: `int8`, `int16`, `int32`, and `int64`. With corresponding sizes for `unint` values.
- The type `rune` is a synonym for `int32` and indicated that a value is a Unicode code point.
- The range of `int8` is -128 to 127, whereas the range og `uint8` is 0 to 255.
- We tend to use signed `int` form even for quantaties that can't be negative.
- The built in `len` function returns a signed `int`.

- Arithemtic operations must have operands of the same type:

```go
var apples int32 = 1
var oranges int16 = 2
var compote int = apples + oranges  // compile error
```

- To fix this error we could do:

```go
var compote = int(apples) + int(oranges)    // "3"
```

- A conversion that narrows a big integer into a smaller one, or a conversion from integer to floating-point or vice versa, may change the value or lose precision.

#### 3.2 Floating-Point Numbers
- Go provides two sizes of floating-point numbers, `float32` and `float64`.
- The limits of floating-point numbers can be found in the [math](https://pkg.go.dev/math) package. `math.MaxFloat32`, `math.MaxFloat64`, etc.
- Floating-point numbers can be written literally using decimals like this: `const e = 2.71828`.
- Digits may be omitted before the decimal point (`.123`) or after it (`134.`).

#### 3.3 Complex Numbers
- Go provides two sized of complex numbers, `complex64` and `complex128`, whose components are `float32` and `float64` respectively.
- The built-in function `complex` creates a complex number from its real and imaginary components, and the built-in `real` and `imag` functions extract those components.

#### 3.4 Booleans
- A value of type `bool`, or `boolean`, has only two possible values, `true` and `false`.
- `!true` is `false` and `(!true==false)==true`.
- We always simplify redundant boolean expressions like `x==true` to `x`.

#### 3.5 Strings
- A string is an *immutable* sequence of bytes.
- The built in `len` function returns the number of bytes (not runes) in a string, and the index operation `s[i]` retrieves the _i-th_ byte of a string `s`, where `0 <= i < len(s)`.

```go
s := "hello, world"
fmt.Println(len(s))             // "12"
fmt.Println(s[0], s[7])         // "104 119" ('h' and 'w')

c := s[len(s)]                  // panic: index out of range

// The substing operator s[i:j] yields a new string consisting of the bytes of the original string.
fmt.Println(s[0:5])             // "hello"
fmt.Println(s[:5])              // "hello"
fmt.Println(s[7:])              // "world"
fmt.Println(s[:])               // "hello, world"

// The + operator makes a new string by concatenating two strings.
fmt.Println("goodbye" + s[5:])  // "goodbye, world"
```

#### 3.5.1 String Literals
- A string value can be written as a _string literal_, a sequence of bytes enclosed in double quotes.
- With a string literal (double quotes), _escape sequences_ that begin with a backslash `\` can be used.
- A _raw string literal_ is written using backquotes (or backticks) instead of double quotes.
- Within a raw string literal no escape sequences are processed and it can work across multiple new lines. Regex expressions and HTML templating are good usages of raw string literals.

#### 3.5.2 Unicode
- The Unicode standards collects all of the worlds writing systems and assigns each one a standard number called a _Unicode code point_ or, in Go terminology, a _rune_.
- We use the data type `int32` to store a single _rune_.

#### 3.5.3 UTF-8
- UTF-8 is a variable length encoding of Unicode code points as bytes.
- Go source files are always encoded in UTF-8, and UTF-8 is the preferred encoding for text strings manipulated by Go programs.
- The [unicode](https://pkg.go.dev/unicode) package provides functions for working with individual runes.

#### 3.5.4 Strings and Byte Slices
- Four packages are important for manipulating strings: `bytes`, `strings`, `strconv`, and `unicode`.
- Because strings are immutable, building up strings incrementally can involve a lot of allocation and copying. It's more efficient to use the `bytes.Buffer` type.
- A strings contains an array of bytes that, once created, is immutable, By contrast, the elements of a byte slice can be freely modified.
- Strings can be converted to byte slices, and back again:

```go
s := "abc"
b := []byte(s)
s2 := string(b)
```

The `bytes` package provides the `Buffer` type for efficient manipulation of byte slices. A `Buffer` starts out empty but grows as data of types like `string`, `byte`, and `[]byte` are written to it.

#### 3.5.5 Conversions between Strings and Numbers
- We can also convert between numeric values and their string representations.
- One option is to use `fmt.Sprintf`; another is to use the function `strconv.Itoa` ("integer to ASCII"):

```go
x := 123
y := fmt.Sprintf("%d", x)
fmt.Println(y, strconv.Itoa(x)) // "123 123"
```

#### 3.6 Constants
- Constants are expressions whose values is known to the compiler and whose evaluation is guaranteed to occur at compile time, not at run time.
- The underlying type of every constant is `boolean`, `string`, or `number`.

```go
// When we declare a list of constant we can ommit the right-hand side.
// This tells the compiler to  reuse the  previous value
const (
    a = 1
    b
    c = 2
    d
)
fmt.Println(a, b, c, d) // "1 1 2 2"
```

- This isn't very useful if the right-hand side always evaluates to the same thing. But what if it could vary? This brings us to `iota`.

#### 3.6.1 The Constant Generator iota
- _the constant generator iota_ is used to generate a sequence of related values without spelling out each one explicitly.
- In a `const` declaration, the value of `iota` begins at zero and increments by one for each item in the sequence.
- Types of this kind are often called `enumerations`, or `enums` for short.

```go
type Weekday int

const (
    Sunday Weekday = iota
    Monday
    Tuesday
    Wednesday
    Thursday
    Friday
    Saturday
)
```

#### 3.6.2 Untyped Constants
- Many constants are not committed to a particular type.
- The compiled represents these uncommitted constants which much greater numeric precision than values of basic types, and arithmetic on them is more precise than machine arithmetic.
- There are six flavors of these uncommitted constants called _untyped_ boolean, untyped integer, untyped rune, untyped floating-point, untyped complex, and untyped string.

**We've now covered the basic data types of Go.**
