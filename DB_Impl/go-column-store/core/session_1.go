package core

import (
	"bufio"
	"errors"
	"os"
)

func (cs *ColumnStore) GetRelation(relationName string) (Relationer, error) {
	var rs = cs.Relations[relationName]
	if rs == nil {
		return nil, errors.New("no relation named " + relationName + " exists")
	}
	return rs, nil
}

func (r Relation) Load(csvFile string, separator rune) (Relationer, error) {
	//Initialisieren des csv-Files und Scanner
	data, err := os.Open(csvFile)
	if err != nil {
		return nil, err
	}
	fileScanner := bufio.NewScanner(data)
	r.Header = []AttrInfo{}
	r.Data = []Tuple{}
	fileScanner.Split(bufio.ScanRunes)
	s := ""
	//Initialisieren Ende
	//Beginn einlesen
	for fileScanner.Scan() { //Read the first line, one letter at a time
		if fileScanner.Text() == string(separator) { //end of single argument name
			r.Header = append(r.Header, AttrInfo{
				Name: s,
				Type: INT,
				Enc:  NOCOMP,
			})
			s = ""
			continue
		}
		if fileScanner.Text() == string('\n') { //End of argument line
			r.Header = append(r.Header, AttrInfo{
				Name: s,
				Type: INT,
				Enc:  NOCOMP,
			})
			s = ""
			break
		}
		if fileScanner.Text() == string('\r') { //Windows ends lines with \r \n
			continue
		}
		s += fileScanner.Text()
	}

	currentTuple := Tuple{
		header:  &r.Header,
		entries: &[]interface{}{},
	}
	s = ""
	for fileScanner.Scan() { //read the set
		if fileScanner.Text() == string(separator) {
			*currentTuple.entries = append(*currentTuple.entries, s)
			r.Header[len(*currentTuple.entries)-1].Type = typeCheck(r.Header[len(*currentTuple.entries)-1].Type, s)
			s = ""
			continue
		}
		if fileScanner.Text() == string('\n') {
			*currentTuple.entries = append(*currentTuple.entries, s)
			r.Header[len(*currentTuple.entries)-1].Type = typeCheck(r.Header[len(*currentTuple.entries)-1].Type, s)
			s = ""
			r.Data = append(r.Data, currentTuple)
			currentTuple = Tuple{
				header:  &r.Header,
				entries: &[]interface{}{},
			}
			continue
		}
		if fileScanner.Text() == string('\r') {
			continue
		}
		s += fileScanner.Text()
	}
	//Adds the final entry

	*currentTuple.entries = append(*currentTuple.entries, s)
	r.Header[len(*currentTuple.entries)-1].Type = typeCheck(r.Header[len(*currentTuple.entries)-1].Type, s)
	s = ""
	r.Data = append(r.Data, currentTuple)

	r.Name = data.Name()
	err = data.Close()
	if err != nil {
		return nil, err
	}
	return r, nil
}

func (r Relation) Print() {
	var length []int
	for i := 0; i < len(r.Header); i++ {
		length = append(length, len(r.Header[i].Name))
	}
	for i := 0; i < len(r.Data); i++ {
		for j := 0; j < len(*r.Data[i].entries); j++ {
			length[j] = max(length[j], len((*r.Data[i].entries)[j].(string)))
		}
	}

	for i := 0; i < len(r.Header); i++ {
		if i != 0 {
			print("│")
		}
		print(r.Header[i].Name)
		for j := len(r.Header[i].Name); j < length[i]; j++ {
			print(" ")
		}
	}
	println()

	for i := 0; i < len(length); i++ {
		if i != 0 {
			print("┼")
		}
		for j := 0; j < length[i]; j++ {
			print("─")
		}
	}
	println()

	for i := 0; i < len(r.Data); i++ {
		for j := 0; j < len(*r.Data[i].entries); j++ {
			if j != 0 {
				print("│")
			}
			print((*r.Data[i].entries)[j].(string))
			for k := len((*r.Data[i].entries)[j].(string)); k < length[j]; k++ {
				print(" ")
			}
		}
		println()
	}
	println()
}

func (r Relation) Select(colName AttrInfo, comp Comparison, compVal interface{}) Relationer {
	index := -1
	for i := 0; i < len(r.Header); i++ {
		if r.Header[i].Name == colName.Name {
			index = i
			break
		}
	}

	ret := Relation{
		Name:   r.Name,
		Header: r.Header,
		Data:   []Tuple{},
		Map:    nil,
	}

	for i := 0; i < len(r.Data); i++ {
		if compare(r.Header[index].Type, comp, (*r.Data[i].entries)[index].(string), compVal.(string)) {
			ret.Data = append(ret.Data, r.Data[i])
		}
	}
	return ret
}

func max(a int, b int) int {
	if a < b {
		return b
	}
	return a
}
