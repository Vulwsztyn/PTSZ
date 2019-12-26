package main

func(solution *Solution) CalculateFitness() (fitness int){
	for _,machine := range solution.machines {
		lastEnded := 0
		for _,t := range machine {
			timeStarted := MaxInt(t.Start, lastEnded)
			lastEnded = timeStarted + t.Duration
			delay := lastEnded - t.Deadline
			fitness+=MaxInt(delay,0)
		}
	}
	solution.fitness = fitness
	return
}