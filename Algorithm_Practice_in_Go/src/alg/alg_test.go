package alg

import (
	"algutil"
	"math/rand"
	"testing"
)

func TestHuffmanCode1(t *testing.T) {
	input1 := make([]*HuffmanCodeInput, 0)
	a := new(HuffmanCodeInput)
	a.count = 45
	a.Value = 'a'
	input1 = append(input1, a)
	input1[0] = a
	b := new(HuffmanCodeInput)
	b.count = 13
	b.Value = 'b'
	input1 = append(input1, b)
	c := new(HuffmanCodeInput)
	c.count = 12
	c.Value = 'c'
	input1 = append(input1, c)
	d := new(HuffmanCodeInput)
	d.count = 16
	d.Value = 'd'
	input1 = append(input1, d)
	e := new(HuffmanCodeInput)
	e.count = 9
	e.Value = 'e'
	input1 = append(input1, e)
	f := new(HuffmanCodeInput)
	f.count = 5
	f.Value = 'f'
	input1 = append(input1, f)

	output := GenHuffmanCode(input1)

	//answer a = 0, c = 100, b = 101, f = 1100, e = 1101, d = 111
	for i, v1 := range output {
		for j, v2 := range output {
			v1Count := 0
			v2Count := 0
			for _, v3 := range input1 {
				if v3.Value == v1.Value {
					v1Count = v3.count
				} else if v3.Value == v2.Value {
					v2Count = v3.count
				}
			}
			if i != j {
				if v1Count > v2Count {
					algutil.AssertTrue(t, len(v1.code) <= len(v2.code))
				} else if v2Count > v1Count {
					algutil.AssertTrue(t, len(v2.code) <= len(v1.code))
				}

				if len(v1.code) <= len(v2.code) {
					algutil.AssertTrue(t, v1.code != v2.code[:len(v1.code)])
				} else {
					algutil.AssertTrue(t, v2.code != v1.code[:len(v2.code)])
				}

			}
		}
	}
}

func TestHuffmanCode2(t *testing.T) {
	for ti := 0; ti < 100; ti++ {
		input := make([]*HuffmanCodeInput, 0)
		for i := 0; i < 26; i++ {
			a := new(HuffmanCodeInput)
			a.count = rand.Int() % 20
			a.Value = 'a' + i
			input = append(input, a)
		}

		output := GenHuffmanCode(input)

		for i, v1 := range output {
			for j, v2 := range output {
				v1Count := 0
				v2Count := 0
				for _, v3 := range input {
					if v3.Value == v1.Value {
						v1Count = v3.count
					} else if v3.Value == v2.Value {
						v2Count = v3.count
					}
				}
				if i != j {
					if v1Count > v2Count {
						algutil.AssertTrue(t, len(v1.code) <= len(v2.code))
					} else if v2Count > v1Count {
						algutil.AssertTrue(t, len(v2.code) <= len(v1.code))
					}

					if len(v1.code) <= len(v2.code) {
						algutil.AssertTrue(t, v1.code != v2.code[:len(v1.code)])
					} else {
						algutil.AssertTrue(t, v2.code != v1.code[:len(v2.code)])
					}

				}
			}
		}
	}
}
