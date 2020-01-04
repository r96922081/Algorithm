package alg

import (
	"ds/priorityqueue"
	"ds/tree"
)

func inorderGenCode(node *tree.BinaryTreeNode, code string, output *[]*HuffmanCodeOutput) {
	leaf := true
	if node.Left != nil {
		inorderGenCode(node.Left, code+"0", output)
		leaf = false
	}
	if node.Right != nil {
		inorderGenCode(node.Right, code+"1", output)
		leaf = false
	}

	if leaf {
		o := new(HuffmanCodeOutput)
		o.code = code
		o.Value = node.Value
		*output = append(*output, o)
	}
}

type HuffmanCodeInput struct {
	count int
	Value interface{}
}

type HuffmanCodeOutput struct {
	code  string
	Value interface{}
}

func GenHuffmanCode(input []*HuffmanCodeInput) []*HuffmanCodeOutput {
	output := make([]*HuffmanCodeOutput, len(input))

	biggerThanFunc := func(v1 interface{}, v2 interface{}) bool {
		return v1.(*HuffmanCodeInput).count < v2.(*HuffmanCodeInput).count
	}
	q := priorityqueue.New(biggerThanFunc)

	for _, v := range input {
		huffnode := new(HuffmanCodeInput)
		huffnode.count = v.count
		huffnode.Value = new(tree.BinaryTreeNode)
		huffnode.Value.(*tree.BinaryTreeNode).Value = v.Value
		q.Insert(huffnode)
	}

	for true {
		n1 := q.ExtractMax()
		if q.Empty() {
			output := make([]*HuffmanCodeOutput, 0)
			inorderGenCode(n1.(*HuffmanCodeInput).Value.(*tree.BinaryTreeNode), "", &output)
			return output
		}
		n2 := q.ExtractMax()
		n3 := new(HuffmanCodeInput)
		n3.count = n1.(*HuffmanCodeInput).count + n2.(*HuffmanCodeInput).count
		binaryNode := new(tree.BinaryTreeNode)
		binaryNode.Left = n1.(*HuffmanCodeInput).Value.(*tree.BinaryTreeNode)
		binaryNode.Right = n2.(*HuffmanCodeInput).Value.(*tree.BinaryTreeNode)
		n3.Value = binaryNode

		q.Insert(n3)
	}

	return output
}
