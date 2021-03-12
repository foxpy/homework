package main

import(
	"math/big"
	"os"
	"fmt"
)

func help() {
	fmt.Println("Usage:", os.Args[0], "A", "B")
	os.Exit(1)
}

func gcd(a, b *big.Int) {
	if a.Cmp(b) == 1 {
		a, b = b, a
	}
	Ri_2 := new(big.Int)
	Ri_1 := new(big.Int)
	Ri := new(big.Int)
	Qi := new(big.Int)
	Ri_2.Set(b)
	Ri_1.Set(a)
	zero := big.NewInt(0)
	for {
		Qi, Ri = Qi.DivMod(Ri_2, Ri_1, Ri)
		if Ri.Cmp(zero) == 0 {
			fmt.Printf("GCD(%v, %v) = %v\n", a, b, Ri_1)
			break
		}
		Ri_2.Set(Ri_1)
		Ri_1.Set(Ri)
	}
}

func main() {
	if len(os.Args) != 3 {
		help()
	} else {
		a := new(big.Int)
		_, resultA := a.SetString(os.Args[1], 10)
		b := new(big.Int)
		_, resultB := b.SetString(os.Args[2], 10)
		if !resultA || !resultB {
			help()
		} else {
			gcd(a, b)
		}
	}
}
