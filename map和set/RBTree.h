#pragma once 


#include <iostream>
#include <time.h>
#include <string>
#include <assert.h>
namespace hdm
{
	enum Color
	{
		BLACK,	//黑色
		RED,	//红色
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
			:_data(data),_left(nullptr),_right(nullptr),_parent(nullptr),_col(RED)//默认给节点红色
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
			if (cur->_right)//如果存在右子树，则找右子树最左节点(本质就是右子树的最小节点)
			{
				cur = cur->_right;
				while (cur->_left)
				{
					cur = cur->_left;
				}
				_node = cur;
			}
			else//没有右子树，就找孩子是父亲左孩子的节点
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
			if (_node == _header)//如果迭代器的位置是end,那么--之后就是最大值
			{
				Node* cur = _header->_parent;
				while (cur->_right)
				{
					cur = cur->_right;
				}
				_node = cur;
			}
			else//正常节点的情况
			{
				Node* cur = _node;
				if (cur->_left)//如果存在左子树，就找左子树的最右节点(本质就是左子树的最大节点)
				{
					cur = cur->_left;
					while (cur->_right)
					{
						cur = cur->_right;
					}
					_node = cur;
				}
				else//找孩子是父亲的右孩子节点
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
			Node* parent = cur;//记录cur的父亲
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
					return std::make_pair(iterator(cur, _header),false);//不允许插入重复节点
				}
			}

			//判断kv和parent的关系，确定kv的位置
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

			//判断是否符合黑红树规则
			while (parent!=_header && parent->_col == RED)
			{
				//三种情况
				//1.叔叔节点存在而且为空
				//2.叔叔节点不存在或者存在且为黑，插入节点与parent同侧
				//3.叔叔节点不存在或者存在且为黑，插入节点与parent不同侧
				//注意分左右侧，细分一共6种
				Node* grandparent = parent->_parent;
				if (grandparent->_left == parent)//在左子树处理
				{
					//叔叔节点位置在parent另一侧
					Node* uncle = grandparent->_right;
					if (uncle && uncle->_col == RED)//情况一：叔叔节点存在而且为红
					{
						//直接变色处理:parent和uncle变黑，grandparent变红
						parent->_col = uncle->_col = BLACK;
						grandparent->_col = RED;

						//这种改grandparent的情况要继续往上处理
						cur = grandparent;
						parent = cur->_parent;
					}
					else//这种情况就是uncle不是红色或者不存在
					{
						//分两种情况：
						//1.parent和cur同侧
						//2.parent和cur不同侧
						if (parent->_left == cur)//同侧的情况
						{
							//对grandparent右单旋+变色
							RotateR(grandparent);
							parent->_col = BLACK;
							grandparent->_col = RED;
						}
						else//不同侧的情况
						{
							//左右旋+变色
							//对parent左单旋，再对grandparent右单旋
							RotateL(parent);
							RotateR(grandparent);
							cur->_col = BLACK;
							grandparent->_col = RED;
						}
						break;//这种情况替换了grandparent但是原来黑的位置不变，不会影响其他
					}
				}
				else//在右子树处理--跟上面相反
				{
					Node* uncle = grandparent->_left;
					if (uncle&& uncle->_col == RED)
					{
						//变色处理
						grandparent->_col = RED;
						parent->_col = uncle->_col = BLACK;

						//向上处理
						cur = grandparent;
						parent = cur->_parent;
					}
					else
					{
						if (parent->_right == cur)//同侧
						{
							//左单旋+变色
							RotateL(grandparent);
							grandparent->_col = RED;
							parent->_col = BLACK;
						}
						else//不同侧
						{
							//右左旋+变色
							//对parent右单旋+对grandparent左单旋+变色
							RotateR(parent);
							RotateL(grandparent);
							grandparent->_col = RED;
							cur->_col = BLACK;
						}
						break;
					}
				}

			}//while end

			_header->_parent->_col = BLACK;//保证根节点是黑色
			update_header();//更新虚拟头节点的孩子指向
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
			if (_header->_parent == nullptr)//空树也是红黑树
				return true;
			if (_header->_parent->_col != BLACK)
			{
				std::cout << "违反了红黑树性质二：根节点必须为黑色" << std::endl;
				return false;
			}
			//获取任意一个节点的黑色节点
			size_t blackCount = 0;
			Node* cur = _header->_parent;
			while (cur)
			{
				if (cur->_col == BLACK)
					blackCount++;
				cur = cur->_left;
			}
			// 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
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
		void update_header()//创建虚拟头节点与_root连接or更新虚拟头节点的指向
		{
			Node* root = _header->_parent;
			//找最小节点
			Node* left_min = root;
			while (left_min->_left)
			{
				left_min = left_min->_left;
			}
			//找最大节点
			Node* right_max = root;
			while (right_max->_right)
			{
				right_max = right_max->_right;
			}
			//hander的左孩子连接最小节点,右孩子连最大节点
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
		void RotateL(Node* parent)//左单旋
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			Node* pparent = parent->_parent;

			//连接
			parent->_right = subRL;
			if (subRL)
				subRL->_parent = parent;

			subR->_left = parent;
			parent->_parent = subR;
			subR->_parent = pparent;
			if (pparent == _header)
			{
				//那么subR就是新的根节点
				_header->_parent = subR;
			}
			else
			{
				//判断subR在pparent的那一侧
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

		void RotateR(Node* parent)//右单旋
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			Node* pparent = parent->_parent;

			//连接
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
				//判断位于那一侧
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
			//走到null之后，判断k和black是否相等
			if (root == nullptr)
			{
				if (k != blackCount)
				{
					std::cout << "违反性质四：每条路径中黑色节点的个数必须相同" << std::endl;
					return false;
				}
				return true;
			}
			// 统计黑色节点的个数
			if (root->_col == BLACK)
				k++;
			// 检测当前节点与其双亲是否都为红色
			Node* parent = root->_parent;
			if (parent && parent->_col == RED && root->_col == RED)
			{
				std::cout << "违反性质三：不能存在连在一起的红色节点" << std::endl;
				return false;
			}

			return IsValidRBTree(root->_left, blackCount, k) &&
				IsValidRBTree(root->_right, blackCount, k);
		}

	private:
		Node* _header = nullptr;//哨兵位头节点
		size_t _size = 0;// 红黑树中有效节点的个数
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
	//		//std::string s("测试");
	//		//s += std::to_string(i);
	//		t.Insert(std::make_pair(x,x));
	//		//cout << t.IsBalance() << endl;
	//	}

	//	t.InorderTree();

	//	std::cout << t.IsValidRBTree() << std::endl;
	//}
}
