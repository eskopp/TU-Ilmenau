package core

import "sync"

func (r Relation) MakeIndex(info AttrInfo) {
	index := -1
	for i := 0; i < len(r.Header); i++ {
		if r.Header[i].Name == info.Name {
			index = i
			break
		}
	}
	r.Map = make(map[string][]int)
	for i := 0; i < r.Size(); i++ {
		key := (*r.Data[i].entries)[index].(string)
		r.Map[key] = append(r.Map[key], i)
	}
}

func (r Relation) IndexScan(info AttrInfo, key string) Relationer {
	r.MakeIndex(info)

	ret := Relation{
		Name:   r.Name,
		Header: r.Header,
		Data:   []Tuple{},
		Map:    nil,
	}

	if r.Map[key] != nil {
		for i := 0; i < len(r.Map[key]); i++ {
			ret.Data = append(ret.Data, r.Data[r.Map[key][i]])
		}
	}

	return &ret
}

func (r Relation) IndexNestedLoop(r2 Relationer, info AttrInfo) Relationer {
	rel := r2.(*Relation)
	relIndex := -1
	for i := 0; i < len(rel.Header); i++ {
		if rel.Header[i].Name == info.Name {
			relIndex = i
			break
		}
	}

	ret := Relation{
		Name:   "Result",
		Header: append(r.Header, rel.Header...),
		Data:   []Tuple{},
		Map:    nil,
	}

	for i := 0; i < rel.Size(); i++ {
		key := (*rel.Data[i].entries)[relIndex].(string)
		if r.Map[key] != nil {
			for j := 0; j < len(r.Map[key]); j++ {
				tmp := append(*r.Data[r.Map[key][j]].entries, *rel.Data[i].entries...)
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

func (cs *ColumnStore) ParallelHashJoin(leftRelation Relationer, leftCol AttrInfo, rightRelation Relationer, rightCol AttrInfo, comp Comparison) Relationer {
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

	results := make([][]Tuple, loopRel.Size())
	wg := new(sync.WaitGroup)
	wg.Add(loopRel.Size())
	for i := 0; i < loopRel.Size(); i++ {
		results = append(results, []Tuple{})
		go func(iConst int, wg *sync.WaitGroup) {
			hashVal := Hash((*loopRel.Data[iConst].entries)[loopIndex].(string), HashTableSize)
			var res []Tuple
			for j := 0; j < len(hashTable[hashVal]); j++ {
				if compare(loopRel.Header[loopIndex].Type, comp, (*loopRel.Data[iConst].entries)[loopIndex].(string), (*hashRel.Data[hashTable[hashVal][j]].entries)[hashIndex].(string)) {
					temp := append(*loopRel.Data[iConst].entries, *hashRel.Data[hashTable[hashVal][j]].entries...)
					if leftIsHash {
						temp = append(*hashRel.Data[hashTable[hashVal][j]].entries, *loopRel.Data[iConst].entries...)
					}
					res = append(res, Tuple{
						header:  &ret.Header,
						entries: &temp,
					})
				}
			}
			results[iConst] = res
			wg.Done()
		}(i, wg)
	}

	var retData []Tuple
	wg.Wait()
	for i := 0; i < len(results); i++ {
		for j := 0; j < len((results)[i]); j++ {
			retData = append(retData, (results)[i][j])
		}
	}
	ret.Data = retData
	return ret
}
