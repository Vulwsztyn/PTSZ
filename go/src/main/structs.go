package main

import (
	"strconv"
)

const machinesCount = 4

const microsecondsLimit = 9 * 1e6

type Solution struct {
	machines [machinesCount][]Task
	fitness  int
}

func (this Solution) deepCopy() (result Solution) {
	for i, m := range this.machines {
		result.machines[i] = make([]Task, len(m))
		copy(result.machines[i], m)
	}
	return
}

func (this Solution) stringForFile() string {
	return strconv.Itoa(this.fitness) + "\n" + this.stringOfIds()
}

func (this Solution) stringOfIds() (result string) {
	for _, m := range this.machines {
		for _, t := range m {
			result += strconv.Itoa(t.Id) + " "
		}
		result += "\n"
	}
	return
}
func (this Solution) Nop() {}

type Instance struct {
	tasks []Task
	size  int
}

type Task struct {
	Id       int
	Start    int
	Duration int
	Deadline int
}
