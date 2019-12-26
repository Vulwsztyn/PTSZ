package main

import (
	"math/rand"
)

func Mutate(solution Solution) Solution {
	machineNum := int(rand.Float64()*4)
	tasks := solution.machines[machineNum]
	if rand.Float64()>0.5 {
		taskNum := int(rand.Float64()*float64(len(tasks)-1))
		solution.machines[machineNum][taskNum],solution.machines[machineNum][taskNum+1] = tasks[taskNum+1],tasks[taskNum]
		//fmt.Println(machineNum,taskNum)
	} else {
		secondMachine := int(rand.Float64()*3)
		if secondMachine >= machineNum {
			secondMachine++
			if secondMachine >= machinesCount {
				secondMachine=0
			}
		}
		taskNum := int(rand.Float64()*float64(len(tasks)))
		solution.machines[secondMachine]=SortByDeadline(append(solution.machines[secondMachine],solution.machines[machineNum][taskNum]))
		solution.machines[machineNum] = append(solution.machines[machineNum][:taskNum], solution.machines[machineNum][taskNum+1:]...)
		//fmt.Println(machineNum,taskNum,secondMachine)
	}
	return solution
}