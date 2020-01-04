package main

import (
	"fmt"
)

func main() {
	a := make([]int, 6)
	for i := 0; i < 6; i++ {
		a[i] = i
	}

	b := append(a[:2], a[3:]...)

	fmt.Print(b)

}
