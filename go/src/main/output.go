package main

import (
	"os"
	"strconv"
	"time"
)

func createOutputFile(name string, solution Solution) {
	f, err := os.Create("./Solucje/"+name)
	if err != nil {
		return
	}
	_, err = f.WriteString(solution.stringForFile())
	if err != nil {
		return
	}

	err = f.Close()
	if err != nil {
		return
	}
}

func createResultsFile(results []int) {
	s := ""
	for _,r := range results{
		s+=strconv.Itoa(r)+"\n"
	}
	currentTime := time.Now()
	f, err := os.Create("./Wyniki"+currentTime.Format("2006-01-02-15-04-05")+".txt")
	_, err = f.WriteString(s)
	if err != nil {
		return
	}
	err = f.Close()
	if err != nil {
		return
	}
}