package main

import "sort"

func SortByDeadline(tasks []Task) []Task {
	sort.SliceStable(tasks, func(i, j int) bool {
		return tasks[i].Deadline < tasks[j].Deadline
	})
	return tasks
}

func Listowy(instance Instance) (solution Solution) {
	instance.tasks=SortByDeadline(instance.tasks)
	var machineBusyUntil [machinesCount]int
	for _, t := range instance.tasks {
		chosenMachine := 0
		minTime := machineBusyUntil[chosenMachine]
		for j := 1; j < machinesCount; j++ {
			if machineBusyUntil[j] < minTime {
				minTime = machineBusyUntil[j]
				chosenMachine = j
			}
		}
		solution.machines[chosenMachine] = append(solution.machines[chosenMachine], t)
		machineBusyUntil[chosenMachine] = MaxInt(machineBusyUntil[chosenMachine], t.Start) + t.Duration
	}
	return
}
