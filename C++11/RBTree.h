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

	template<class K,class V>
	struct RBTreeNode
	{
		std::pair<K, V> _kv;
		RBTreeNode<K, V>* _left;
		RBTreeNode<K, V>* _right;
		RBTreeNode<K, V>* _parent;
		Color _col;

		RBTreeNode(const std::pair<K,V>& kv)
			:_kv(kv),_left(nullptr),_right(nullptr),_parent(nullptr),_col(RED)//Ĭ�ϸ��ڵ��ɫ
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
			Node* parent = cur;//��¼cur�ĸ���
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
					return false;//�����в����ظ��ڵ�
				}
			}

			//�ж�kv��parent�Ĺ�ϵ��ȷ��kv��λ��
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
			if (_root == nullptr)//����Ҳ�Ǻ����
				return true;
			if (_root->_col != BLACK)
			{
				cout << "Υ���˺�������ʶ������ڵ����Ϊ��ɫ" << endl;
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
			//�ߵ�null֮���ж�k��black�Ƿ����
			if (root == nullptr)
			{
				if (k != blackCount)
				{
					cout << "Υ�������ģ�ÿ��·���к�ɫ�ڵ�ĸ���������ͬ" << endl;
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
				cout << "Υ�������������ܴ�������һ��ĺ�ɫ�ڵ�" << endl;
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
			std::string s("����");
			s += std::to_string(i);
			t.Insert(std::make_pair(x,s));
			//cout << t.IsBalance() << endl;
		}

		t.InorderTree();

		std::cout << t.IsValidRBTree() << std::endl;
	}
}
