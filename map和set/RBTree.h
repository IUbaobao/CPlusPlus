#pragma once 


#include <iostream>
#include <time.h>
#include <string>
namespace hdm
{
	enum Color
	{
		BLACK,	//��ɫ
		RED,	//��ɫ
	};

	template<class T>
	struct RBTreeNode
	{
		T _data;
		RBTreeNode<T>* _left;
		RBTreeNode<T>* _right;
		RBTreeNode<T>* _parent;
		Color _col;

		RBTreeNode(const T& data)
			:_data(data),_left(nullptr),_right(nullptr),_parent(nullptr),_col(RED)//Ĭ�ϸ��ڵ��ɫ
		{}
	};

	template<class T,class Ptr,class Ref>
	class _RBTreeIterator
	{
	public:
		typedef _RBTreeIterator<T, Ptr, Ref> Self;
		typedef _RBTreeIterator<T, T*, T&> iterator;

		typedef RBTreeNode<T> Node;
		_RBTreeIterator(Node* node):_node(node){}

		_RBTreeIterator(const iterator& it)
			:_node(it._node)
		{}


		Self operator++()
		{
			Node* cur = _node;
			if (cur->_right)//�����������������������������ڵ�
			{
				cur = cur->_right;
				while (cur->_left)
				{
					cur = cur->_left;
				}
				_node = cur;
			}
			else//û�������������Һ����Ǹ������ӵĽڵ�
			{
				Node* parent = cur->_parent;
				while (parent&&parent->_left != cur)
				{
					cur = parent;
					parent = cur->_parent;
				}
				_node = parent;
			}
			return *this;
		}

		Self operator--()
		{
			Node* cur = _node;
			if (cur->_left)//������������������������������ҽڵ�(���ʾ��������������ڵ�)
			{
				while (cur->_right)
				{
					cur = cur->_right;
				}
				_node = cur;
			}
			else//�Һ����Ǹ��׵��Һ��ӽڵ�
			{
				Node* parent = cur->_parent;
				while (parent && parent->_right != cur)
				{
					cur = parent;
					parent = cur->_parent;
				}
				_node = parent;
			}
			return *this;
		}


		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		bool operator==(const Self& it) const
		{
			return _node == it._node;
		}

		bool operator!=(const Self& it)const
		{
			return _node != it._node;
		}
	//private:
		Node* _node;
	};

	template<class K,class T,class KeyOfT>
	class RBTree
	{
	public:
		typedef RBTreeNode<T> Node;
		typedef _RBTreeIterator<T, T*, T&> iterator;
		typedef _RBTreeIterator<T, const T*, const T&> const_iterator;


		iterator begin()
		{
			Node* cur = _root;
			while (cur->_left)
			{
				cur = cur->_left;
			}
			return iterator(cur);
		}

		iterator end()
		{
			return iterator(nullptr);
		}

		const_iterator begin()const 
		{
			Node* cur = _root;
			while (cur->_left)
			{
				cur = cur->_left;
			}
			return const_iterator(cur);
		}
		const_iterator end()const 
		{
			return const_iterator(nullptr);
		}

		std::pair<iterator,bool> Insert(const T& data)
		{
			if (_root == nullptr)
			{
				_root = new Node(data);
				_root->_col = BLACK;
				return std::make_pair(iterator(_root), true);
			}

			Node* cur = _root;
			Node* parent = cur;//��¼cur�ĸ���
			while (cur)
			{
				if (KeyOfT()(cur->_data) > KeyOfT()(data))
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (KeyOfT()(cur->_data) < KeyOfT()(data))
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return std::make_pair(iterator(nullptr),false);//�����в����ظ��ڵ�
				}
			}

			//�ж�kv��parent�Ĺ�ϵ��ȷ��kv��λ��
			cur = new Node(data);
			Node* newnode = cur;
			if (KeyOfT()(parent->_data) > KeyOfT()(data))
			{
				parent->_left = cur;
			}
			else
			{
				parent->_right = cur;
			}
			cur->_parent = parent;

			//�ж��Ƿ���Ϻں�������
			while (parent && parent->_col == RED)
			{
				//�������
				//1.����ڵ���ڶ���Ϊ��
				//2.����ڵ㲻���ڻ��ߴ�����Ϊ�ڣ�����ڵ���parentͬ��
				//3.����ڵ㲻���ڻ��ߴ�����Ϊ�ڣ�����ڵ���parent��ͬ��
				//ע������Ҳ࣬ϸ��һ��6��
				Node* grandparent = parent->_parent;
				if (grandparent->_left == parent)//������������
				{
					//����ڵ�λ����parent��һ��
					Node* uncle = grandparent->_right;
					if (uncle && uncle->_col == RED)//���һ������ڵ���ڶ���Ϊ��
					{
						//ֱ�ӱ�ɫ����:parent��uncle��ڣ�grandparent���
						parent->_col = uncle->_col = BLACK;
						grandparent->_col = RED;

						//���ָ�grandparent�����Ҫ�������ϴ���
						cur = grandparent;
						parent = cur->_parent;
					}
					else//�����������uncle���Ǻ�ɫ���߲�����
					{
						//�����������
						//1.parent��curͬ��
						//2.parent��cur��ͬ��
						if (parent->_left == cur)//ͬ������
						{
							//��grandparent�ҵ���+��ɫ
							RotateR(grandparent);
							parent->_col = BLACK;
							grandparent->_col = RED;
						}
						else//��ͬ������
						{
							//������+��ɫ
							//��parent�������ٶ�grandparent�ҵ���
							RotateL(parent);
							RotateR(grandparent);
							cur->_col = BLACK;
							grandparent->_col = RED;
						}
						break;//��������滻��grandparent����ԭ���ڵ�λ�ò��䣬����Ӱ������
					}
				}
				else//������������--�������෴
				{
					Node* uncle = grandparent->_left;
					if (uncle&& uncle->_col == RED)
					{
						//��ɫ����
						grandparent->_col = RED;
						parent->_col = uncle->_col = BLACK;

						//���ϴ���
						cur = grandparent;
						parent = cur->_parent;
					}
					else
					{
						if (parent->_right == cur)//ͬ��
						{
							//����+��ɫ
							RotateL(grandparent);
							grandparent->_col = RED;
							parent->_col = BLACK;
						}
						else//��ͬ��
						{
							//������+��ɫ
							//��parent�ҵ���+��grandparent����+��ɫ
							RotateR(parent);
							RotateL(grandparent);
							grandparent->_col = RED;
							cur->_col = BLACK;
						}
						break;
					}
				}

			}//while end

			_root->_col = BLACK;//��֤���ڵ��Ǻ�ɫ
			return std::make_pair(iterator(newnode),true);
		}//Insert end

		Node* Find(const K& x)
		{
			Node* cur = _root;
			while (cur)
			{
				if (KeyOfT()(cur->_data) > KeyOfT()(x))
				{
					cur = cur->_left;
				}
				else if (KeyOfT()(cur->_data) < KeyOfT()(x))
				{
					cur = cur->_right;
				}
				else
				{
					return cur;
				}
			}
			return cur;
		}
		void InorderTree()
		{
			InorderTree(_root);
		}
		bool IsValidRBTree()
		{
			if (_root == nullptr)//����Ҳ�Ǻ����
				return true;
			if (_root->_col != BLACK)
			{
				std::cout << "Υ���˺�������ʶ������ڵ����Ϊ��ɫ" << std::endl;
				return false;
			}
			//��ȡ����һ���ڵ�ĺ�ɫ�ڵ�
			size_t blackCount = 0;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_col == BLACK)
					blackCount++;
				cur = cur->_left;
			}
			// ����Ƿ��������������ʣ�k������¼·���к�ɫ�ڵ�ĸ���
			size_t k = 0;
			return IsValidRBTree(_root, blackCount, k);
		}
	private:
		void InorderTree(Node* root)
		{
			if (root == nullptr)
				return;
			InorderTree(root->_left);
			std::cout << root->_kv.first<<":"<<root->_kv.second << " ";
			InorderTree(root->_right);
		}
		void RotateL(Node* parent)//����
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			Node* pparent = parent->_parent;

			//����
			parent->_right = subRL;
			if (subRL)
				subRL->_parent = parent;

			subR->_left = parent;
			parent->_parent = subR;
			subR->_parent = pparent;
			if (pparent == nullptr)
			{
				//��ôsubR�����µĸ��ڵ�
				_root = subR;
				_root->_parent = nullptr;
			}
			else
			{
				//�ж�subR��pparent����һ��
				if (KeyOfT()(pparent->_data) > KeyOfT()(subR->_data) )
				{
					pparent->_left = subR;
				}
				else
				{
					pparent->_right = subR;
				}
			}
		}

		void RotateR(Node* parent)//�ҵ���
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			Node* pparent = parent->_parent;

			//����
			parent->_left = subLR;
			if (subLR)
				subLR->_parent = parent;
			parent->_parent = subL;
			subL->_right = parent;
			subL->_parent = pparent;
			if (pparent == nullptr)
			{
				_root = subL;
				_root->_parent = nullptr;
			}
			else
			{
				//�ж�λ����һ��
				if (KeyOfT()(pparent->_data) > KeyOfT()(subL->_data))
				{
					pparent->_left = subL;
				}
				else
				{
					pparent->_right = subL;
				}
			}
		}


		bool IsValidRBTree(Node* root, size_t blackCount, size_t k)
		{
			//�ߵ�null֮���ж�k��black�Ƿ����
			if (root == nullptr)
			{
				if (k != blackCount)
				{
					std::cout << "Υ�������ģ�ÿ��·���к�ɫ�ڵ�ĸ���������ͬ" << std::endl;
					return false;
				}
				return true;
			}
			// ͳ�ƺ�ɫ�ڵ�ĸ���
			if (root->_col == BLACK)
				k++;
			// ��⵱ǰ�ڵ�����˫���Ƿ�Ϊ��ɫ
			Node* parent = root->_parent;
			if (parent && parent->_col == RED && root->_col == RED)
			{
				std::cout << "Υ�������������ܴ�������һ��ĺ�ɫ�ڵ�" << std::endl;
				return false;
			}

			return IsValidRBTree(root->_left, blackCount, k) &&
				IsValidRBTree(root->_right, blackCount, k);
		}

	private:
		Node* _root = nullptr;
	};


	//void RBTreeTest1()
	//{
	//	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	//	//	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//	//	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	//	RBTree<int,int> t;
	//	for (auto e : a)
	//	{
	//		t.Insert(std::make_pair(e,e));
	//	}
	//	t.InorderTree();
	//}

	//void RBTreeTest2()
	//{
	//	srand(time(0));
	//	const size_t N = 10000;
	//	RBTree<int,string> t;
	//	for (size_t i = 0; i < N; ++i)
	//	{
	//		size_t x = rand();
	//		//std::string s("����");
	//		//s += std::to_string(i);
	//		t.Insert(std::make_pair(x,x));
	//		//cout << t.IsBalance() << endl;
	//	}

	//	t.InorderTree();

	//	std::cout << t.IsValidRBTree() << std::endl;
	//}
}
