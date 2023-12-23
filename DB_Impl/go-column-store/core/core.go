package core

// TODO: Session 1 - Implement the Relationer and ColumnStorer interface by
// using the given structs. Implement the methods in the core_impl.go file.
// Implement Load, Scan, Select, Print, GetRawData, CreateRelation and GetRelation.

// TODO: Session 2 - Implement HashJoin and Aggregate

// TODO: Session 3 - Parallelization and Acceleration

/*
	The comparison operators for filter operators.
*/
type Comparison string

const (
	EQ  Comparison = "=="
	NEQ Comparison = "!="
	LT  Comparison = "<"
	GT  Comparison = ">"
	LE  Comparison = "<="
	GE  Comparison = ">="
)

const HashTableSize = 10000

/*
	The supported compression types of the Column Store.
*/
type Compression int

const (
	NOCOMP Compression = iota
	RLE
	DICT
	FOR
)

/*
	The supported data types of the Column Store.
*/
type DataTypes int

const (
	INT DataTypes = iota
	FLOAT
	STRING
)

/*
	The AttrInfo structure stores metainformation about a column, e.g., the name, type and encryption used in a column.
*/
type AttrInfo struct {
	Name string
	Type DataTypes
	Enc  Compression
}

/*
	The column structure stores the actual data of a column in a relation.
*/
type Column struct {
	Signature AttrInfo
	Data      interface{}
}

/*
	The actual structure for a Relation. It contains the name of the relation and a collection
	of the columns.
*/
type Relation struct {
	Name   string
	Header []AttrInfo
	Data   []Tuple
	Map    map[string][]int
}

type Tuple struct {
	header  *[]AttrInfo
	entries *[]interface{}
}

/*
	The Relationer interface defines an interface for operations that can be executed on a Relation.
	These methods implements in- and output and query operators.
*/
type Relationer interface {
	/*
		Loads a .csv file into a relation. The name of the relation corresponds to the name of the given file.
		A given seperator is used to delimit the columns.
	*/
	Load(csvFile string, separator rune) (Relationer, error)
	//Scan(colList []AttrInfo) Relationer
	Select(col AttrInfo, comp Comparison, compVal interface{}) Relationer
	Print()
	GetRawData() interface{}
	Size() int
	//MakeIndex()
	//IndexScan(string) Relationer
	//IndexNestedLoop(relation *Relationer) Relationer
}

/*
	ColumnStore is the main structure that contains a map of relations with their names as key.
*/
type ColumnStore struct {
	Relations map[string]Relationer
}

/*
	ColumnStorer is the main interface in order to create relations with given name and attributes and
	to get a relation by name.
*/
type ColumnStorer interface {
	/*
		Creates a new relation with given name and a signature list of the columns.
	*/
	CreateRelation(tabName string, sig []AttrInfo) Relationer

	/*
		Returns a relation by name.
	*/
	GetRelation(relName string) Relationer

	MakeIndex(relName string)
	IndexScan(relName string, colList []AttrInfo)
}
