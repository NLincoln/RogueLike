#pragma once
#include <vector>
#include "Common.h"

template <typename T>
class Node
{
	using NodeType = Node<T>;
	T m_Data;
	std::vector<NodeType*> m_Children;

public:
	T GetData()
	{
		return m_Data;
	}

	void SetData(T Data)
	{
		m_Data = Data;
	}

	NodeType* operator[](uint index)
	{
		return m_Children[index];
	}

	std::vector<NodeType*> GetAllChildren()
	{
		return m_Children;
	}

	void AddChild(NodeType* Child)
	{
		m_Children.push_back(Child);
	}

	Node() {}
	~Node()
	{
		for (auto Node : m_Children)
		{
			delete Node;
			Node = nullptr;
		}
	}
};

