package main

import (
    "fmt"
)

func main() {
	input := []int{1,20,11,6,12,0}
	fmt.Println(part2(input))
}

func testPart1() {
	tcases := []struct{ input []int; want int }{
		{ input: []int{0,3,6}, want: 436 },
		{ input: []int{1,3,2}, want: 1 },
		{ input: []int{2,1,3}, want: 10 },
		{ input: []int{1,2,3}, want: 27 },
		{ input: []int{2,3,1}, want: 78 },
		{ input: []int{3,2,1}, want: 438 },
		{ input: []int{3,1,2}, want: 1836 },
	}
	allPassed := true
	for _, tc := range tcases {
		have := part1(tc.input)
		if tc.want != have {
			fmt.Printf("FAIL:\n  want: %v\n  have: %v\n", tc.want, have)
			allPassed = false
		}
	}
	if allPassed {
		fmt.Println("All tests passed!")
	}
}

func testPart2() {
	tcases := []struct{ input []int; want int }{
		{ input: []int{0,3,6}, want: 175594 },
		{ input: []int{1,3,2}, want: 2578 },
		{ input: []int{2,1,3}, want: 3544142 },
		{ input: []int{1,2,3}, want: 261214 },
		{ input: []int{2,3,1}, want: 6895259 },
		{ input: []int{3,2,1}, want: 18 },
		{ input: []int{3,1,2}, want: 362 },
	}
	allPassed := true
	for _, tc := range tcases {
		have := part2(tc.input)
		if tc.want != have {
			fmt.Printf("FAIL:\n  want: %v\n  have: %v\n", tc.want, have)
			allPassed = false
		}
	}
	if allPassed {
		fmt.Println("All tests passed!")
	}
}

func part1(start []int) int {
	return memoryGame(start, 2020)
}

func part2(start []int) int {
	return memoryGame(start, 30_000_000)
}

func memoryGame(start []int, finalTurn int) int {
	said := make(map[int]int)
	for turn:=0; turn<len(start)-1; turn++ {
		said[start[turn]] = turn
		// fmt.Println(start[turn]) // debug
	}
	prev := start[len(start)-1]
	for turn:=len(start); turn<finalTurn; turn++ {
		lastSaid, isRepeat := said[prev]
		said[prev] = turn - 1
		// fmt.Println(prev) // debug
		if isRepeat {
			prev = turn - 1 - lastSaid
		} else {
			prev = 0
		}
	}
	return prev
}
