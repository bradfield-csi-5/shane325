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

#### 2.3.3 The `new` Function

#### 2.3.4 Lifetime of Variables

#### 2.4 Assignments

#### 2.4.1 Tuple Assignment

#### 2.4.2 Assignability

#### 2.5 Type Declarations

#### 2.6 Packages and Files

#### 2.6.1 Imports

#### 2.6.2 Package Initialization

#### 2.7 Scope
