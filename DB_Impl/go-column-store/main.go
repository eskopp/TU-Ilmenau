package main

import (
	"ColumnStore/core"
	"ColumnStore/helper"
	"fmt"
	"math/rand"
	"sync"
	"time"
)

func RandomString(n int) string {
	var letters = []rune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")

	s := make([]rune, n)
	for i := range s {
		s[i] = letters[rand.Intn(len(letters))]
	}
	return string(s)
}
func main() {
	elements := []int{}
	for i := 800; i < 1000; i++ {
		elements = append(elements, i)
	}

	testSize := len(elements)

	output := false
	println("Start")
	start := time.Now()
	helper.MakeFiles(elements)
	duration := time.Since(start)
	fmt.Printf("Init done in %d milliseconds\n", duration.Milliseconds())
	/*rand.Seed(time.Now().UnixNano())
	runs := 10000000
	var count [30]int
	for i := 0; i < runs; i++ {
		e := core.Hash(RandomString(rand.Intn(98)+2), 30)
		count[e]++
	}

	for i := 0; i < len(count); i++ {
		fmt.Printf("%.3f\n", float64(count[i])/float64(runs))
	}*/
	var cs = new(core.ColumnStore)

	var atts = []core.AttrInfo{
		{Name: "id", Type: core.INT, Enc: core.NOCOMP},
		{Name: "Name", Type: core.STRING, Enc: core.NOCOMP},
	}

	cs.CreateRelation("students", atts)
	cs.CreateRelation("jobs", atts)

	//var parallelTimes [testSize][testSize]*time.Duration
	//var linearTimes [testSize][testSize]*time.Duration

	linearTimes := make([][]*time.Duration, testSize)
	parallelTimes := make([][]*time.Duration, testSize)
	for i := 0; i < len(parallelTimes); i++ {
		parallelTimes[i] = make([]*time.Duration, testSize)
		linearTimes[i] = make([]*time.Duration, testSize)
	}

	rStudents := core.Relation{}
	rJobs := core.Relation{}

	rResult := core.Relation{}

	var wg sync.WaitGroup
	var wg2 sync.WaitGroup
	wg.Add(testSize * testSize * 2)
	wg2.Add(1)

	calcTotal := time.Now()

	waiting := true
	go func(wait *bool) {
		lastWritten := ""
		counterOld := -1
		for *wait {
			counter := 0
			for i := 0; i < testSize; i++ {
				for j := 0; j < testSize; j++ {
					if linearTimes[i][j] != nil {
						counter++
					}
					if parallelTimes[i][j] != nil {
						counter++
					}
				}
			}
			if counterOld < counter {
				for i := 0; i < len(lastWritten); i++ {
					print("\b")
				}
				lastWritten = fmt.Sprintf("(%d/%d) %.2f%s", counter, testSize*testSize*2, (float64(counter)/float64(testSize*testSize*2))*100, "%")
				print(lastWritten)
			}
			counterOld = counter
		}
		wg2.Done()
		println()
	}(&waiting)

	for i := 0; i < testSize; i++ {
		for j := 0; j < testSize; j++ {
			go func(iConst int, jConst int) {
				sizeStudents := elements[iConst]
				sizeJobs := elements[jConst]
				tmp, _ := rStudents.Load(fmt.Sprintf("example/Benchmark_students_%d.csv", sizeStudents), ',')
				rStudents = tmp.(core.Relation)
				tmp, _ = rJobs.Load(fmt.Sprintf("example/Benchmark_jobs_%d.csv", sizeJobs), ',')
				rJobs = tmp.(core.Relation)

				go func(r1 core.Relationer, r2 core.Relationer) {
					startIntern := time.Now()
					rResult = cs.HashJoin(r1, core.AttrInfo{
						Name: "Studiengang",
						Type: 0,
						Enc:  0,
					}, r2, core.AttrInfo{
						Name: "Studiengang",
						Type: 0,
						Enc:  0,
					}, core.EQ).(core.Relation)
					durationIntern := time.Since(startIntern)

					if output {
						rResult.Print()
					}
					linearTimes[iConst][jConst] = &durationIntern
					wg.Done()
				}(rStudents, rJobs)
				go func(r1 core.Relationer, r2 core.Relationer) {
					startIntern := time.Now()
					rResult = cs.ParallelHashJoin(r1, core.AttrInfo{
						Name: "Studiengang",
						Type: 0,
						Enc:  0,
					}, r2, core.AttrInfo{
						Name: "Studiengang",
						Type: 0,
						Enc:  0,
					}, core.EQ).(core.Relation)
					durationIntern := time.Since(startIntern)

					if output {
						rResult.Print()
					}
					parallelTimes[iConst][jConst] = &durationIntern
					wg.Done()
				}(rStudents, rJobs)
			}(i, j)
		}
	}

	wg.Wait()
	waiting = false
	wg2.Wait()

	durationTotal := time.Since(calcTotal)
	fmt.Printf("Hashing-Benchmark completed in %.2f seconds\n", durationTotal.Seconds())

	for i := 0; i < len(parallelTimes); i++ {
		for j := 0; j < len(parallelTimes[i]); j++ {
			fmt.Printf("%d/%d: %d/%.3f\n", i, j, linearTimes[i][j].Milliseconds()-parallelTimes[i][j].Milliseconds(), float64(parallelTimes[i][j].Milliseconds())/float64(linearTimes[i][j].Milliseconds()))
		}
	}

	/*rs := core.Relation{}
	tmp, _ := rs.Load("exampleCSV.csv", ',')
	rs = tmp.(core.Relation)
	rs.Print()
	cs.Relations["students"] = rs

	rt := core.Relation{}
	tmp, _ = rs.Load("exampleCSV2.csv", ',')
	rt = tmp.(core.Relation)
	rt.Print()
	cs.Relations["jobs"] = rt

	rs = cs.ParallelHashJoin("students", core.AttrInfo{
		Name: "Studiengang",
		Type: 0,
		Enc:  0,
	}, "jobs", core.AttrInfo{
		Name: "Studiengang",
		Type: 0,
		Enc:  0,
	}, core.EQ).(core.Relation)
	rs.Print()

	rs = cs.HashJoin("students", core.AttrInfo{
		Name: "Studiengang",
		Type: 0,
		Enc:  0,
	}, "jobs", core.AttrInfo{
		Name: "Studiengang",
		Type: 0,
		Enc:  0,
	}, core.EQ).(core.Relation)
	rs.Print()

	rs = cs.NestedLoopJoin("students", core.AttrInfo{
		Name: "Studiengang",
		Type: 0,
		Enc:  0,
	}, "jobs", core.AttrInfo{
		Name: "Studiengang",
		Type: 0,
		Enc:  0,
	}, core.EQ).(core.Relation)
	rs.Print()

	/*rs.(core.Relation).CurrentKey = &core.AttrInfo{
		Name: "ID",
		Type: 0,
		Enc:  0,
	}

	rs.MakeIndex()*/
	println("End")
}
