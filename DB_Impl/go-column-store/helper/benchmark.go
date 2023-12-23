package helper

import (
	"fmt"
	"io"
	"math/rand"
	"os"
	"sync"
	"time"
)

var wg sync.WaitGroup

func MakeFiles(elements []int) {

	os.RemoveAll("example")
	os.Mkdir("example", 0755)

	rand.Seed(time.Now().UnixNano())
	Init()
	wg.Add(len(elements) * 2)
	for i := 0; i < len(elements); i++ {
		go generatePair(elements[i])
	}
	wg.Wait()
}

func generatePair(size int) {
	go WriteToFileStudents(size)
	go WriteToFileJobs(size)
}

// WriteToFileStudents will print any string of text to a file safely by
// checking for errors and syncing at the end.
func WriteToFileStudents(size int) error {
	defer wg.Done()
	filename := fmt.Sprintf("example/Benchmark_students_%d.csv", size)
	data := generateStudentRelation(size)
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	_, err = io.WriteString(file, data)
	if err != nil {
		return err
	}
	return file.Sync()
}

func generateStudentRelation(amount int) string {
	firstName := append(FirstNamesF, FirstNamesM...)
	ret := "ID,Vorname,Nachname,Alter,Studiengang\n"

	for i := 0; i < amount; i++ {
		ID := i
		vorname := firstName[rand.Intn(len(firstName))]
		nachname := LastNames[rand.Intn(len(LastNames))]
		alter := rand.Intn(50) + 20
		studiengang := Subject[rand.Intn(len(Subject))]

		if i != 0 {
			ret += "\n"
		}

		ret += fmt.Sprintf("%d,%s,%s,%d,%s", ID, vorname, nachname, alter, studiengang)
	}
	return ret
}

func WriteToFileJobs(size int) error {
	defer wg.Done()
	filename := fmt.Sprintf("example/Benchmark_jobs_%d.csv", size)
	data := generateJobRelation(size)
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	_, err = io.WriteString(file, data)
	if err != nil {
		return err
	}
	return file.Sync()
}

func generateJobRelation(amount int) string {
	ret := "ID,Gehalt,Studiengang\n"
	for i := 0; i < amount; i++ {
		ID := i
		salary := rand.Intn(600) + 200
		studiengang := Subject[rand.Intn(len(Subject))]

		if i != 0 {
			ret += "\n"
		}

		ret += fmt.Sprintf("%d,%d€,%s", ID, salary, studiengang)
	}
	return ret
}
