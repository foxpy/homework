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
	fmt.Printf("Ri_2=0, Ri_1=0, Qi=0, Ri=%v\n", a)
	fmt.Printf("Ri_2=0, Ri_1=0, Qi=0, Ri=%v\n", b)
	Ri_2 := new(big.Int)
	Ri_1 := new(big.Int)
	Ri := new(big.Int)
	Qi := new(big.Int)
	Ri_2.Set(b)
	Ri_1.Set(a)
	zero := big.NewInt(0)
	for {
		Qi, Ri = Qi.DivMod(Ri_2, Ri_1, Ri)
		fmt.Printf("Ri_2=%v, Ri_1=%v, Qi=%v, Ri=%v\n", Ri_2, Ri_1, Qi, Ri)
		if Ri.Cmp(zero) == 0 {
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
