package main

import (
    "bufio"
    "errors"
    "encoding/json"
    "fmt"
    "io/ioutil"
    "log"
    "os"
    "os/exec"
    "os/signal"
    "slices"
    "strings"
    "syscall"
)

// Constant values
const CLI_NAME = "kv-store"

// Describes our Key Value Store
type KvStore struct {
    filePath string
    commands []string
    cliName string
}

// Returns a new instance of our key value store
func newKvStore(filePath string) KvStore {
    commands := []string{
        "help",
        "clear",
        "print",
    }

    return KvStore{
        filePath: filePath,
        commands: commands,
        cliName: CLI_NAME,
    }
}

// Run the program
func (kv *KvStore) Run() {
    reader := bufio.NewScanner(os.Stdin)
    c := make(chan os.Signal, 2)

    signal.Notify(c, os.Interrupt, syscall.SIGTERM)
    go func() {
        <-c
        fmt.Println()
        fmt.Println("Exiting...")
        os.Exit(1)
    }()

    kv.printPrompt()
    for reader.Scan() {
        text := cleanInput(reader.Text())
        if strings.EqualFold("exit", text) {
            fmt.Println("Exiting...")
            os.Exit(1)
        } else {
            kv.handleCmd(text)
        }
        kv.printPrompt()
    }
    fmt.Println()
}

// Print a prompt
func (kv *KvStore) printPrompt() {
    fmt.Print(kv.cliName, "> ")
}

// Handle unknown command
func printUnknown(text string) {
    fmt.Println(text, ": command not found")
}

// Print the help text
func (kv *KvStore) displayHelp() {
    fmt.Printf(
        "Welcome to %v! These are the available commands: \n",
        kv.cliName,
    )
    fmt.Println("help      - Show available commands")
    fmt.Println("clear     - Clear the terminal screen")
    fmt.Println("print     - Prints the database to stdout")
    fmt.Println("exit      - Closes your connection to", kv.cliName)
}

// Print the database content
func (kv *KvStore) printDatabase() {
    jsonData, err := kv.readData()
    if err != nil {
        log.Panic(err)
    }
    fmt.Println("KVStore: Key ---> Value")
    fmt.Println("-----------------------")
    for key, val := range jsonData {
        fmt.Printf("%s\t\t ---> %s \n", key, val)
    }
}

// Clear the screen
func (kv *KvStore) clearScreen() {
    cmd := exec.Command("clear")
    cmd.Stdout = os.Stdout
    cmd.Run()
}

// Handle invalid command
func handleInvalidCmd(text string) {
    defer printUnknown(text)
}

// Handle command
func (kv *KvStore) handleCmd(text string) {
    if slices.Contains(kv.commands, text) {
        switch text {
        case "help":
            kv.displayHelp()
            return
        case "clear":
            kv.clearScreen()
            return
        case "print":
            kv.printDatabase()
            return
        }
    }

    inputs := strings.Fields(text)
    if len(inputs) != 2 {
        handleInvalidCmd(text)
        return
    }
    op := inputs[0]
    param := inputs[1]
    if strings.Compare(op, "get") != 0 && strings.Compare(op, "set") != 0 {
        handleInvalidCmd(text)
    } else if op == "get" {
        val, err := kv.get(param)
        if err != nil {
            fmt.Printf("No value found for key: %v \n", param)
            return
        }
        fmt.Printf("%s \n", val)
    } else if op == "set" {
        kvPair, err := parsePair(param)
        if err != nil {
            fmt.Printf("Invalid key value pair. Must be key=value. \n")
            return
        }
        key := kvPair[0]
        value := kvPair[1]
        kv.set(key, value)
    }
}

// Clean input from Stdin
func cleanInput(text string) string {
    output := strings.TrimSpace(text)
    output = strings.ToLower(output)
    return output
}

// Get method
func (kv *KvStore) get(text string) (string, error) {
    mapData, err := kv.readData()
    if err != nil {
        return "", err
    }

    for key, value := range mapData {
        if strings.Compare(key, text) == 0 {
            return value, nil
        }
    }

    return "", errors.New("Key not found")
}

// Set method
func (kv *KvStore) set(key, value string) {
    mapData, err := kv.readData()
    if err != nil {
        log.Panic(err)
    }

    mapData[key] = value
    err = kv.writeData(mapData)
    if err != nil {
        log.Panic(err)
    }
}

// Accepts a string like `foo=baz` and returns a
// key value pair like `["foo", "baz"]`
func parsePair(text string) ([]string, error) {
    if !strings.Contains(text, "=") {
        return []string{}, errors.New("Invalid key value pair")
    }
    return strings.Split(text, "="), nil
}

// Reads json data and returns it as a map
func (kv *KvStore) readData() (map[string]string, error) {
    byteValue, err := ioutil.ReadFile("./" + kv.filePath)
    var result map[string]string
    if err != nil {
        return result, errors.New("Error reading json file")
    }

    err = json.Unmarshal(byteValue, &result)
    if err != nil {
        return result, errors.New("Error unmarshaling json")
    }

    return result, nil
}

// Writes map to json
func (kv *KvStore) writeData(data map[string]string) error {
    f, err := os.Create(kv.filePath)
    if err != nil {
        return errors.New("Error calling create on file")
    }
    defer f.Close()

    jsonData, err := json.Marshal(data)
    if err != nil {
        return errors.New("Error marshaling json")
    }

    f.Write(jsonData)
    return nil
}
