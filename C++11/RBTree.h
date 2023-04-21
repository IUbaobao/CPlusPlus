#pragma once 


#include <iostream>
#include <time.h>
#include <string>
namespace hdm
{
	enum Color
	{
		BLACK,	//黑色
		RED,	//红色
	};

	template<class K,class V>
	struct RBTreeNode
	{
		std::pair<K, V> _kv;
		RBTreeNode<K, V>* _left;
		RBTreeNode<K, V>* _right;
		RBTreeNode<K, V>* _parent;
		Color _col;

		RBTreeNode(const std::pair<K,V>& kv)
			:_kv(kv),_left(nullptr),_right(nullptr),_parent(nullptr),_col(RED)//默认给节点红色
		{}
	};

	template<class K,class V>
	class RBTree
	{
	public:
		typedef RBTreeNode<K,V> Node;
		bool Insert(const std::pair<K, V>& kv)
		{
			if (_root == nullptr)
			{
				_root = new Node(kv);
				_root->_col = BLACK;
				return true;
			}

			Node* cur = _root;
			Node* parent = cur;//记录cur的父亲
			while (cur)
			{
				if (cur->_kv.first > kv.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_kv.first < kv.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false;//不运行插入重复节点
				}
			}

			//判断kv和parent的关系，确定kv的位置
			cur = new Node(kv);
			if (parent->_kv.first > kv.first)
			{
				parent->_left = cur;
			}
			else
			{
				parent->_right = cur;
			}
			cur->_parent = parent;

			//判断是否符合黑红树规则
			while (parent && parent->_col == RED)
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

			_root->_col = BLACK;//保证根节点是黑色
			return true;
		}//Insert end

		Node* Find(const K& x)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_kv.first > x)
				{
					cur = cur->_left;
				}
				else if (cur->_kv.first < x)
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
			if (_root == nullptr)//空树也是红黑树
				return true;
			if (_root->_col != BLACK)
			{
				cout << "违反了红黑树性质二：根节点必须为黑色" << endl;
				return false;
			}
			//获取任意一个节点的黑色节点
			size_t blackCount = 0;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_col == BLACK)
					blackCount++;
				cur = cur->_left;
			}
			// 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
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
			if (pparent == nullptr)
			{
				//那么subR就是新的根节点
				_root = subR;
				_root->_parent = nullptr;
			}
			else
			{
				//判断subR在pparent的那一侧
				if (pparent->_kv.first > subR->_kv.first)
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
			if (pparent == nullptr)
			{
				_root = subL;
				_root->_parent = nullptr;
			}
			else
			{
				//判断位于那一侧
				if (pparent->_kv.first > subL->_kv.first)
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
					cout << "违反性质四：每条路径中黑色节点的个数必须相同" << endl;
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
				cout << "违反性质三：不能存在连在一起的红色节点" << endl;
				return false;
			}

			return IsValidRBTree(root->_left, blackCount, k) &&
				IsValidRBTree(root->_right, blackCount, k);
		}

	private:
		Node* _root = nullptr;
	};


	void RBTreeTest1()
	{
		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
		//	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
		//	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
		RBTree<int,int> t;
		for (auto e : a)
		{
			t.Insert(std::make_pair(e,e));
		}
		t.InorderTree();
	}

	void RBTreeTest2()
	{
		srand(time(0));
		const size_t N = 10000;
		RBTree<int,string> t;
		for (size_t i = 0; i < N; ++i)
		{
			size_t x = rand();
			std::string s("测试");
			s += std::to_string(i);
			t.Insert(std::make_pair(x,s));
			//cout << t.IsBalance() << endl;
		}

		t.InorderTree();

		std::cout << t.IsValidRBTree() << std::endl;
	}
}
