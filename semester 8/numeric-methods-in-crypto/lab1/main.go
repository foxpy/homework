package main

import(
	"os"
	"fmt"
	"math/big"
)

func factorize(number *big.Int) {
	zero := new(big.Int)
	zero.SetUint64(0)
	one := new(big.Int)
	one.SetUint64(1)
	two := new(big.Int)
	two.SetUint64(2)

	count := new(big.Int)
	count.SetUint64(0)
	factor := new(big.Int)
	factor.SetUint64(0)
	size := new(big.Int)
	size.SetUint64(2)
	x := new(big.Int)
	x.SetUint64(2)
	x_fixed := new(big.Int)
	x_fixed.SetUint64(2)
	loop := new(big.Int)
	loop.SetUint64(1)

	if number.Cmp(one) == 0 {
		return
	}

	for {
		count.Set(size)
		for {
			x.Mul(x, x).Add(x, one).Mod(x, number)
			factor.Sub(x, x_fixed).Abs(factor).GCD(nil, nil, factor, number)
			count.Sub(count, one)
			if count.Cmp(zero) == 0 || factor.Cmp(one) != 0 {
				break
			}
		}
		size.Mul(size, two)
		x_fixed.Set(x)
		loop.Add(loop, one)
		if factor.Cmp(one) != 0 {
			break
		}
	}
	fmt.Print(" ", factor)
	number.Div(number, factor)
	factorize(number)
}

func main() {
	n := new(big.Int)
	if len(os.Args) != 2 {
		fmt.Println("Usage:", os.Args[0], "NUMBER")
		os.Exit(1)
	} else {
		_, s := n.SetString(os.Args[1], 10)
		if !s {
			fmt.Println(os.Args[1], "does not look like integer")
		} else {
			fmt.Print(n, ":")
			factorize(n)
			fmt.Println()
		}
	}
}
