[Home](https://github.com/bradfield-csi-5/shane325/blob/main/prep-phase/go/notes/the_go_programming_language.md)

### 4. Composite Types
In this chapter, we'll take a look at four composite types - arrays, slices, maps, and structs.

#### 4.1 Arrays
- An array is a fixed length sequence of zero or more elements of a particular type.
- Because of their fixed length, arrays are rarely used directly in Go.
- `Slices`, which can grow and shrink, are much more versatile, but to understand slices we must understand arrays first.

```go
var a [3]int                // array of 3 integers (all initially set to zero)
fmt.Println(a[0])           // print the first element
fmt.Println(a[len(a)-1])    // print the last element, a[2]

// print the indices and elements
for i, v := range a {
    fmt.Printf("%d %d\n", i, v)
}

// print the elements only
for _, v := range a {
    fmt.Printf("%d\n", v)
}
```

- We can use an _array literal_ to initialize an array with a list of values.

```go
var q [3]int = [3]int{1, 2, 3}
var r [3]int = [3]int{1, 2}
fmt.Println(r[2])   // "0"

// If an elipsis "..." appears in place of the array length, the length is determined by the number of initializers
q := [...]int{1, 2, 3}
fmt.Printf("%T\n", q)   // "[3]int"
```

- The size of an array is part of its type, so `[3]int` and `[4]int` are different types. The size must be a constant expressions.
- Arrays are passed by value, not reference.
- Using a pointer to an array is efficiant and allows the called function to mutate the caller's variable, but arrays are still inherently inflexible because of their fixed size.
- Arrays are seldom used as function parameters or results, instead, we use slices.

#### 4.2 Slices
- Slices represent variable length sequences whose elements all have the same type.
- The slice type is written `[]T`, where the elements have type T; it looks like an array without the size.
- Arrays and slices are intimately connected. A slice is a lightweight data structure that gives access to a subsequence (or perhaps all) of the elements of an array, which is known as the slice's underlying array.
- A slice has 3 components, a pointer, a length, and a capacity.
- The pointer points to the first element of the slice (which may not be the first element of the array), the length gives the size of the slice and the capacity gives the number of elements between the start of the slice and the end of the underlying array. The length cannot exceed the capacity.
- Multiple slices can share the same underlying array and may refer to overlapping parts of that array.

```go
months := [...]string{1: "January",/*...*/, 12: "December"} // Create an array for months of the year
Q2 := months[4:7]       // Create a slice
summer := months[6:9]   // Create a slice
fmt.Println(Q2)         // ["April" "May", "June"]
fmt.Println(summer)     // ["June", "July", "August"]
```

- Slicing beyond `cap(s)` causes a panic, but slicing beyond `len(s)` extends the slice so the result may be longer than the original.
- The built-in function `make` creates a slice of a specified element type, length and capacity. The capacity argument may be ommitted, in which case the capacity equals length.
- Under the hood, `make` creates an unnamed array variable and returns a slice of it.

```go
make([]T, len)
make([]T, len, cap)
```

#### 4.2.1 The append Function
- The built-in `append` function appends items to slice.

```go
var runes []rune
for _, r := range "Hello, World" {
    runes = append(runes, r)
}
fmt.Printf("%q\n", runes)   // "['H', 'e', 'l', 'l', 'o', ','...]"
```

#### 4.2.2 In-Place Slice Technique
- There are a few other example of slice techniques in the textbook.

#### 4.3 Maps
- In Go, a _map_ is a reference to a hash table, and a map type is written `map[K]V`, where `K` and `V` are the types of its keys and values.
- The build in function `make` can be used to create a map:

```go
ages := make(map[string]int)    // Creates a map with string keys and int values
// We can also use a _map literal_ to create a new map populated with some initial data
ages := map[string]int{
    "alice": 14,
    "charlie": 47,
}
// An alternative expression for a new empty map is
ages := map[string]int{}
```

#### 4.4 Structs
- A struct is an aggregate data type that groups together zero or more named values of arbitrary types as a single entity.
- Each value is called a field.

```go
type Employee struct {
    ID          int
    Name        string
    Address     string
    DoB         time.Time
    Position    string
    Salary      int
    ManagerID   int
}

var dilbert Employee
// Fields are accessed with dot notation
dilbert.Salary -= 5000
// Also works with a pointer to a struct
var employeeOfTheMonth *Employee = &dilbert
employeeOfTheMonth.Position += " (proactive team player)"
```

#### 4.4.1 Struct Literals
- A value of struct type can be written using a _struct literal_ that specifies values for its fields.

```go
type Point struct{ X, Y int }
p := Point{1, 2}
```

- More often, a second form of _struct literals_ is used.

```go
anim := gif.GIF{LoopCount: nframes}
```

- If a field is ommitted, it is set to the zero value for its type. Because names are provided, the order of fields doesn't matter.

#### 4.4.2 Comparing Structs
- If all the fields of struct are comparable, the struct itself is comparable.
- Comparable struct types, like other comparable types, may be used as the key type of a map.

#### 4.4.3 Struct Embedding and Anonymous Fields
- Structs can be embedded as fields in other structs.
- Go lets us declare a field with a type but no name; such fields are called _anonymous fields_.

```go
type Circle struct {
    Point
    Radius int
}

type Wheel struct {
    Circle
    Spokes int
}
```

#### 4.5 JSON
- This section gives an overview of the most important parts of the _encoding/json_ package.
- Convering a Go data structure to JSON is called _marshalling_. Marshalling is done by `json.Marshal`.
- The inverse of _marshalling_, decoding JSON and populating a Go data structure, is called _unmarshalling_, and it is done by `json.Unmarshal`.

#### 4.6 Text and HTML Templates
