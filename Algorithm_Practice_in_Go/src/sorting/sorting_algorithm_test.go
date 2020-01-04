package sorting

import (
	"algutil"
	"math/rand"
	"testing"
)

func generateRandomIntSlice(size int, max int, min int) []int {
	algutil.SetSeed()
	randomIntSlice := make([]int, size)
	for i := 0; i < size; i++ {
		randomIntSlice[i] = rand.Int()%(max-min+1) + min
	}

	return randomIntSlice
}
func TestInsertionSort(t *testing.T) {
	a := generateRandomIntSlice(100, 30, -40)
	InsertionSort(a)
	for i := 1; i < len(a); i++ {
		algutil.AssertTrue(t, a[i-1] <= a[i])
	}
}

func TestBubbleSort(t *testing.T) {
	a := generateRandomIntSlice(100, 30, -40)
	b := make([]int, len(a))
	copy(b, a)

	InsertionSort(b)
	BubbleSort(a)

	for i := 0; i < len(a); i++ {
		algutil.AssertTrue(t, a[i] == b[i])
	}
}

func TestMergeSort(t *testing.T) {
	for i := 1; i < 100; i++ {
		for size := 1; size < 18; size++ {
			a := generateRandomIntSlice(size, 30, -40)
			b := make([]int, len(a))
			copy(b, a)

			InsertionSort(b)
			MergeSort(a)

			for i := 0; i < len(a); i++ {
				algutil.AssertTrue(t, a[i] == b[i])
			}
		}
	}
}

func TestQuickSort(t *testing.T) {
	for i := 1; i < 100; i++ {
		for size := 1; size < 40; size++ {
			a := generateRandomIntSlice(size, 30, -40)
			b := make([]int, len(a))
			copy(b, a)

			InsertionSort(b)
			QuickSort(a)

			for j := 0; j < len(a); j++ {
				algutil.AssertTrue(t, a[j] == b[j])
			}
		}
	}
}

func TestRadixSort(t *testing.T) {
	for i := 1; i < 20; i++ {
		for size := 1; size < 15; size++ {
			a := generateRandomIntSlice(size, 66, -66)
			b := make([]int, len(a))
			copy(b, a)

			InsertionSort(b)
			RadixSort(a)

			for j := 0; j < len(a); j++ {
				algutil.AssertTrue(t, a[j] == b[j])
			}
		}
	}
}

func TestCountingSort(t *testing.T) {
	for i := 0; i < 20; i++ {
		for size := 1; size < 30; size++ {
			a := generateRandomIntSlice(size, 66, -66)
			b := make([]int, len(a))
			unsortedA := make([]int, len(a))
			copy(b, a)
			copy(unsortedA, a)

			InsertionSort(b)
			order := CountingSort(a)

			for j := 0; j < len(a); j++ {
				algutil.AssertTrue(t, a[j] == b[j])
			}

			for i, v := range order {
				algutil.AssertTrue(t, unsortedA[i] == a[v])
			}
		}
	}
}

func TestHeapSort(t *testing.T) {
	for i := 0; i < 20; i++ {
		for size := 1; size < 30; size++ {
			a := generateRandomIntSlice(size, 66, -66)
			b := make([]int, len(a))
			copy(b, a)

			InsertionSort(b)
			HeapSort(a)

			for j := 0; j < len(a); j++ {
				algutil.AssertTrue(t, a[j] == b[j])
			}
		}
	}
}

func TestBucketSort(t *testing.T) {
	for i := 0; i < 20; i++ {
		for size := 1; size < 30; size++ {
			min := -66
			max := 66
			a := generateRandomIntSlice(size, max, min)
			b := make([]int, len(a))
			copy(b, a)

			InsertionSort(b)
			BucketSort(a, max, min)

			for j := 0; j < len(a); j++ {
				algutil.AssertTrue(t, a[j] == b[j])
			}
		}
	}
}
