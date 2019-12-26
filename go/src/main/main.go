package main

import (
	"fmt"
	"math/rand"
	"sort"
	"time"
)

func main() {
	//realRun()
	//listowy()
	test()
}

func test() {
	indexNumbers := []string{
		"132290",
		"132324",
		"132289",
		"132234",
		"132311",
		"132235",
		"132275",
		"132332",
		"132202",
		"132205",
		"132217",
		"132250",
		"132322",
		"132212",
		"116753",
		"132264",
		"132078",
	}
	instanceSizes := []string{
		"50",
		"100",
		"150",
		"200",
		"250",
		"300",
		"350",
		"400",
		"450",
		"500",
	}
	results := make([]int, len(instanceSizes)*len(indexNumbers))
	ri := 0
	for _, ind := range indexNumbers {
		for _, num := range instanceSizes {
			fmt.Println(ind + "_" + num)
			inst := LoadFile("./Instancje/in" + ind + "_" + num + ".txt")
			start := time.Now()
			sol := Listowy(inst)
			//fmt.Println(sol)
			//fmt.Print(sol.stringOfIds())
			population := make([]Solution, 500)
			generation := 0
			for i := 0; i < 100; i++ {
				population[i] = Mutate(sol.deepCopy())
				population[i].CalculateFitness()

				CheckSolution(population[i], inst)
				if i == 74 {
					sol.Nop()
				}
				if !CheckSolution(population[i], inst) {
					break
				}
			}
			for {
				//fmt.Println(generation)
				generation++
				for i := 100; i < 500; i++ {
					index := int(rand.Float64() * 100)
					population[i] = Mutate(population[index].deepCopy())
					population[i].CalculateFitness()
					if !CheckSolution(population[i], inst) {
						break
					}
				}
				sort.SliceStable(population, func(i, j int) bool {
					return population[i].fitness < population[j].fitness
				})
				if time.Since(start).Microseconds() > microsecondsLimit {
					break
				}
			}
			//sort.SliceStable(population, func(i, j int) bool {
			//	return population[i].fitness < population[j].fitness
			//})
			//fmt.Println(time.Since(start).Microseconds())
			//for i := 0; i < 100; i++ {
			//	fmt.Println(population[i].CalculateFitness())
			//}
			createOutputFile("out"+ind+"_"+num+".txt", population[0])
			results[ri] = population[0].fitness
			ri++
			//fmt.Println(population[0].stringOfIds())
			//fmt.Println(sol.CalculateFitness())
			//fmt.Println(generation)
			//fmt.Println(CalculateFitness(sol2))
		}
	}
	createResultsFile(results)
	fmt.Println("RESULTS:")
	for _,r := range results {
		fmt.Println(r)
	}
}

func realRun() {
	indexNumbers := []string{"132290",
		"132324",
		"132289",
		"132234",
		"132311",
		"132235",
		"132275",
		"132332",
		"132202",
		"132205",
		"132217",
		"132250",
		"132322",
		"132212",
		"116753",
		"132264",
		"132078"}
	instanceSizes := []string{"50", "100", "150", "200", "250", "300", "350", "400", "450", "500"}
	for _, ind := range indexNumbers {
		for _, num := range instanceSizes {
			inst := LoadFile("./Instancje/in" + ind + "_" + num + ".txt")
			start := time.Now()
			sol := Listowy(inst)
			sol.Nop()
			fmt.Println(time.Since(start).Microseconds())

			//fmt.Println(CalculateFitness(sol))
		}
	}
}

func listowy() {
	indexNumbers := []string{"132290",
		"132324",
		"132289",
		"132234",
		"132311",
		"132235",
		"132275",
		"132332",
		"132202",
		"132205",
		"132217",
		"132250",
		"132322",
		"132212",
		"116753",
		"132264",
		"132078"}
	instanceSizes := []string{"50", "100", "150", "200", "250", "300", "350", "400", "450", "500"}
	for _, ind := range indexNumbers {
		for _, num := range instanceSizes {
			inst := LoadFile("./Instancje/in" + ind + "_" + num + ".txt")
			start := time.Now()
			sol := Listowy(inst)
			sol.Nop()
			fmt.Println(time.Since(start).Microseconds())

			//fmt.Println(CalculateFitness(sol))
		}
	}
}
