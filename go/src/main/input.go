package main

import (
	"bufio"
	"os"
	"strconv"
	"strings"
)

func split(t []string) (res []int) {
	for _, i := range t {
		j, err := strconv.Atoi(i)
		if err != nil {
			panic(err)
		}
		res = append(res, j)
	}
	return res
}

func LoadFile(input string) Instance {
	instanceFile, _ := os.Open(input)
	scanner := bufio.NewScanner(instanceFile)
	scanner.Scan()
	d, _ := strconv.Atoi(strings.Fields(scanner.Text())[0])
	var res [][]int
	for scanner.Scan() {
		res = append(res, split(strings.Fields(scanner.Text())))
	}
	tasks := makeTasks(d, res)
	return Instance{tasks,d}
}
func newTask(id int, duration int, start int, deadline int) Task {
	this := Task{}
	this.Id = id
	this.Start = start
	this.Duration = duration
	this.Deadline = deadline
	return this
}

func makeTasks(size int, input [][]int) (tasks []Task) {
	tasks = make([]Task, size)
	for i, task := range input {
		tasks[i] = newTask(i+1, task[0], task[1], task[2])
	}
	return
}
