#pragma once 


#include <iostream>
#include <time.h>
#include <string>
#include <assert.h>
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

		RBTreeNode(const T& data=T())
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
		_RBTreeIterator(Node* node,Node* header):_node(node),_header(header){}

		_RBTreeIterator(const iterator& it)
			:_node(it._node),_header(it._header)
		{}


		Self operator++()
		{
			Node* cur = _node;
			if (cur->_right)//�����������������������������ڵ�(���ʾ�������������С�ڵ�)
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
				while (parent!=_header&&parent->_left != cur)
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
			if (_node == _header)//�����������λ����end,��ô--֮��������ֵ
			{
				Node* cur = _header->_parent;
				while (cur->_right)
				{
					cur = cur->_right;
				}
				_node = cur;
			}
			else//�����ڵ�����
			{
				Node* cur = _node;
				if (cur->_left)//������������������������������ҽڵ�(���ʾ��������������ڵ�)
				{
					cur = cur->_left;
					while (cur->_right)
					{
						cur = cur->_right;
					}
					_node = cur;
				}
				else//�Һ����Ǹ��׵��Һ��ӽڵ�
				{
					Node* parent = cur->_parent;
					while (parent != _header && parent->_right != cur)
					{
						cur = parent;
						parent = cur->_parent;
					}
					_node = parent;
				}
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
		Node* _header;
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
			Node* cur = _header->_parent;
			while (cur->_left)
			{
				cur = cur->_left;
			}
			return iterator(cur, _header);
		}

		iterator end()
		{
			return iterator(_header, _header);
		}

		const_iterator begin()const 
		{
			Node* cur = _header->_parent;
			while (cur->_left)
			{
				cur = cur->_left;
			}
			return const_iterator(cur, _header);
		}
		const_iterator end()const 
		{
			return const_iterator(_header, _header);
		}

		std::pair<iterator,bool> Insert(const T& data)
		{
			if (_header == nullptr)
			{
				_header = new Node();
				Node* root = new Node(data);
				root->_parent = _header;
				_header->_parent = root;
				_header->_left = _header->_right = root;
				_header->_col = BLACK;
				++_size;
				return std::make_pair(iterator(_header->_parent, _header), true);
			}

			Node* cur = _header->_parent;
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
					return std::make_pair(iterator(cur, _header),false);//����������ظ��ڵ�
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
			while (parent!=_header && parent->_col == RED)
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

			_header->_parent->_col = BLACK;//��֤���ڵ��Ǻ�ɫ
			update_header();//��������ͷ�ڵ�ĺ���ָ��
			++_size;
			return std::make_pair(iterator(newnode, _header),true);
		}//Insert end

		size_t size()const
		{
			return _size;
		}
		iterator Find(const K& x)
		{
			Node* cur = _header->_parent;
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
					return iterator(cur,_header);
				}
			}
			return iterator(cur, _header);
		}
		void InorderTree()
		{
			InorderTree(_header->_parent);
		}
		bool IsValidRBTree()
		{
			if (_header->_parent == nullptr)//����Ҳ�Ǻ����
				return true;
			if (_header->_parent->_col != BLACK)
			{
				std::cout << "Υ���˺�������ʶ������ڵ����Ϊ��ɫ" << std::endl;
				return false;
			}
			//��ȡ����һ���ڵ�ĺ�ɫ�ڵ�
			size_t blackCount = 0;
			Node* cur = _header->_parent;
			while (cur)
			{
				if (cur->_col == BLACK)
					blackCount++;
				cur = cur->_left;
			}
			// ����Ƿ��������������ʣ�k������¼·���к�ɫ�ڵ�ĸ���
			size_t k = 0;
			return IsValidRBTree(_header->_parent, blackCount, k);
		}


		void clear()
		{
			Node* cur = _header->_parent;
			clear(cur);
			_size = 0;
			delete _header;
		}

		bool empty()
		{
			return _size == 0;
		}
	private:
		void clear(Node* root)
		{
			if (root == nullptr)
				return;
			clear(root->_left);
			clear(root->_right);
			//--_size;
			delete root;
		}
		void update_header()//��������ͷ�ڵ���_root����or��������ͷ�ڵ��ָ��
		{
			Node* root = _header->_parent;
			//����С�ڵ�
			Node* left_min = root;
			while (left_min->_left)
			{
				left_min = left_min->_left;
			}
			//�����ڵ�
			Node* right_max = root;
			while (right_max->_right)
			{
				right_max = right_max->_right;
			}
			//hander������������С�ڵ�,�Һ��������ڵ�
			_header->_left = left_min;
			_header->_right = right_max;
		}

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
			if (pparent == _header)
			{
				//��ôsubR�����µĸ��ڵ�
				_header->_parent = subR;
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
			if (pparent == _header)
			{
				_header->_parent = subL;
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
		Node* _header = nullptr;//�ڱ�λͷ�ڵ�
		size_t _size = 0;// ���������Ч�ڵ�ĸ���
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
