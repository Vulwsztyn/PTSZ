package main

import "math"

func Naiwny(instance Instance) (solution Solution) {
	current := 0
	i := 0
	limit := int(math.Ceil(float64(instance.size) / 4.0))
	for _, t := range instance.tasks {
		solution.machines[current] = append(solution.machines[current], t)
		i++
		if i >= limit {
			i = 0
			current++
		}
	}
	return
}
