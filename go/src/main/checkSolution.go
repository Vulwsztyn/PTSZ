package main

import "fmt"

func CheckSolution(solution Solution,instance Instance) (result bool) {
	result = true
	tasks := make([]int,instance.size+1)
	for _,m := range solution.machines {
		for _,t := range m {
			tasks[t.Id]++
		}
	}
	for i := 1;i<=instance.size;i++{
		if tasks[i] == 0 {
			fmt.Println("Nie ma zadania ",i)
			result = false
		}
		if tasks[i] > 1 {
			fmt.Println("Zadanie ",i, "jest wielokrotnie")
			result = false
		}
	}
	return
}