package core

import "strconv"

func typeCheck(datatype DataTypes, word string) DataTypes {
	//Returns the "most specialized" datatype possible of given string
	if datatype == INT {
		if isInt(word) {
			return INT
		}
		datatype = FLOAT
	}
	if datatype == FLOAT {
		if isFloat(word) {
			return FLOAT
		}
	}
	return STRING
}

func isInt(s string) bool {
	if s == "-" {
		return false
	}
	for i := 0; i < len(s); i++ {
		if i == 0 && s[i] == 45 {
			continue
		}
		if !(s[i] >= 48 && s[i] <= 57) {
			return false
		}
	}
	return true
}
func isFloat(s string) bool {
	if s == "-" {
		return false
	}
	floatingPointDiscovered := false
	for i := 0; i < len(s); i++ {
		if i == 0 && s[i] == 45 {
			continue
		}
		if s[i] == 46 {
			if floatingPointDiscovered {
				return false
			}
			floatingPointDiscovered = true
			continue
		}
		if !(s[i] >= 48 && s[i] <= 57) {
			return false
		}
	}
	return true
}

func compare(dt DataTypes, cp Comparison, val1 string, val2 string) bool {
	switch dt {
	case INT:
		v1, _ := strconv.Atoi(val1)
		v2, _ := strconv.Atoi(val2)
		switch cp {
		case EQ:
			return v1 == v2
		case GT:
			return v1 > v2
		case LT:
			return v1 < v2
		case LE:
			return v1 <= v2
		case GE:
			return v1 >= v2
		case NEQ:
			return v1 != v2
		}
		return false
	case FLOAT:
		v1, _ := strconv.ParseFloat(val1, 64)
		v2, _ := strconv.ParseFloat(val2, 64)
		switch cp {
		case EQ:
			return v1 == v2
		case GT:
			return v1 > v2
		case LT:
			return v1 < v2
		case LE:
			return v1 <= v2
		case GE:
			return v1 >= v2
		case NEQ:
			return v1 != v2
		}
		return false
	case STRING:
		v1 := val1
		v2 := val2
		switch cp {
		case EQ:
			return v1 == v2
		case GT:
			return v1 > v2
		case LT:
			return v1 < v2
		case LE:
			return v1 <= v2
		case GE:
			return v1 >= v2
		case NEQ:
			return v1 != v2
		}
		return false
	}
	return false
}

func (r Relation) GetRawData() interface{} {
	return r.Data
}

func (r Relation) Size() int {
	return len(r.Data)
}

func (cs *ColumnStore) CreateRelation(tabName string, sig []AttrInfo) Relationer {
	// initialize a new map when no one exists
	if cs.Relations == nil {
		cs.Relations = make(map[string]Relationer)
	}

	// create an appropriate number of columns and asign the signatures
	rs := Relation{
		Name:   tabName,
		Header: sig,
		Data:   []Tuple{},
		Map:    nil,
	}

	// save and return the relation
	cs.Relations[tabName] = &rs
	return &rs
}
