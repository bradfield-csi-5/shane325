package main

import (
	"go/ast"
	"go/parser"
	"go/token"
	"log"
	"strconv"
)

// Given an expression containing only int types, evaluate
// the expression and return the result.
func Evaluate(expr ast.Expr) (int, error) {
	switch n := expr.(type) {
	case *ast.ParenExpr:
		evalX, _ := Evaluate(n.X)
		return evalX, nil
	case *ast.BinaryExpr:
		evalX, _ := Evaluate(n.X)
		evalY, _ := Evaluate(n.Y)
		return calc(evalX, evalY, n.Op)
	case *ast.BasicLit:
		return strconv.Atoi(n.Value)
	default:
		return 0, nil
	}
}

func calc(x int, y int, o token.Token) (int, error) {
	result := 0
	switch (o.String()) {
	case "-":
		result += x - y
	case "+":
		result += x + y
	case "*":
		result += x * y
	}
	return result, nil
}

func main() {
	expr, err := parser.ParseExpr("2 * (3 - 4)")
	if err != nil {
		log.Fatal(err)
	}
	fset := token.NewFileSet()
	err = ast.Print(fset, expr)
	if err != nil {
		log.Fatal(err)
	}
}
