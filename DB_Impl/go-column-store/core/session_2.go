package core

func (cs *ColumnStore) NestedLoopJoin(leftRelation string, leftCol AttrInfo, rightRelation string, rightCol AttrInfo, comp Comparison) Relationer {
	left := cs.Relations[leftRelation].(Relation)
	right := cs.Relations[rightRelation].(Relation)

	leftIndex := -1
	for i := 0; i < len(left.Header); i++ {
		if left.Header[i].Name == leftCol.Name {
			leftIndex = i
			break
		}
	}
	rightIndex := -1
	for i := 0; i < len(right.Header); i++ {
		if right.Header[i].Name == rightCol.Name {
			rightIndex = i
			break
		}
	}

	ret := Relation{
		Name:   "Result",
		Header: append(left.Header, right.Header...),
		Data:   []Tuple{},
		Map:    nil,
	}

	for i := 0; i < len(left.Data); i++ {
		for j := 0; j < len(right.Data); j++ {
			if compare(left.Header[leftIndex].Type, comp, (*left.Data[i].entries)[leftIndex].(string), (*right.Data[j].entries)[rightIndex].(string)) {
				tmp := append(*left.Data[i].entries, *right.Data[j].entries...)
				add := Tuple{
					header:  &ret.Header,
					entries: &tmp,
				}
				ret.Data = append(ret.Data, add)
			}
		}
	}

	return ret
}

func Hash(s string, size int) int {
	ret := 0
	for _, i := range s {
		ret += int(i)
	}
	return ret % size
}

func (cs *ColumnStore) HashJoin(leftRelation Relationer, leftCol AttrInfo, rightRelation Relationer, rightCol AttrInfo, comp Comparison) Relationer {
	left := leftRelation.(Relation)
	right := rightRelation.(Relation)

	leftIndex := -1
	for i := 0; i < len(left.Header); i++ {
		if left.Header[i].Name == leftCol.Name {
			leftIndex = i
		}
	}
	rightIndex := -1
	for i := 0; i < len(right.Header); i++ {
		if right.Header[i].Name == rightCol.Name {
			rightIndex = i
		}
	}

	leftIsHash := false
	hashRel := right
	loopRel := left
	hashIndex := rightIndex
	loopIndex := leftIndex

	if left.Size() < right.Size() {
		leftIsHash = true
		hashRel = left
		loopRel = right
		hashIndex = leftIndex
		loopIndex = rightIndex
	}

	var hashTable [HashTableSize][]int

	for i := 0; i < hashRel.Size(); i++ {
		hashVal := Hash((*hashRel.Data[i].entries)[hashIndex].(string), HashTableSize)
		hashTable[hashVal] = append(hashTable[hashVal], i)
	}

	ret := Relation{
		Name:   "Result",
		Header: append(left.Header, right.Header...),
		Data:   []Tuple{},
		Map:    nil,
	}

	for i := 0; i < loopRel.Size(); i++ {
		hashVal := Hash((*loopRel.Data[i].entries)[loopIndex].(string), HashTableSize)
		for j := 0; j < len(hashTable[hashVal]); j++ {
			if compare(loopRel.Header[loopIndex].Type, comp, (*loopRel.Data[i].entries)[loopIndex].(string), (*hashRel.Data[hashTable[hashVal][j]].entries)[hashIndex].(string)) {
				temp := append(*loopRel.Data[i].entries, *hashRel.Data[hashTable[hashVal][j]].entries...)
				if leftIsHash {
					temp = append(*hashRel.Data[hashTable[hashVal][j]].entries, *loopRel.Data[i].entries...)
				}
				add := Tuple{
					header:  &ret.Header,
					entries: &temp,
				}
				ret.Data = append(ret.Data, add)
			}
		}
	}

	return ret
}
