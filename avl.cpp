#include "avl.h"

/*
 * ��ȡ���ĸ߶�
 */
template <class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree)
{
    if (tree != NULL)
        return tree->height;

    return 0;
}

template <class T>
int AVLTree<T>::height()
{
    return height(mRoot);
}

/*
 * �Ƚ�����ֵ�Ĵ�С
 */
template <class T>
int AVLTree<T>::max(int a, int b)
{
    return a>b ? a : b;
}

/*
 * LL�������Ӧ�����(����ת)��
 *
 * ����ֵ����ת��ĸ��ڵ�
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2)
{
    AVLTreeNode<T>* k1;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max( height(k2->left), height(k2->right)) + 1;
    k1->height = max( height(k1->left), k2->height) + 1;

    return k1;
}


/*
 * RR�����Ҷ�Ӧ�����(�ҵ���ת)��
 *
 * ����ֵ����ת��ĸ��ڵ�
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1)
{
    AVLTreeNode<T>* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max( height(k1->left), height(k1->right)) + 1;
    k2->height = max( height(k2->right), k1->height) + 1;

    return k2;
}

/*
 * LR�����Ҷ�Ӧ�����(��˫��ת)��
 *
 * ����ֵ����ת��ĸ��ڵ�
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3)
{
    k3->left = rightRightRotation(k3->left);

    return leftLeftRotation(k3);
}


/*
 * RL�������Ӧ�����(��˫��ת)��
 *
 * ����ֵ����ת��ĸ��ڵ�
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1)
{
    k1->right = leftLeftRotation(k1->right);

    return rightRightRotation(k1);
}


/*
 * �������뵽AVL���У������ظ��ڵ�
 *
 * ����˵����
 *     tree AVL���ĸ����
 *     key ����Ľ��ļ�ֵ
 * ����ֵ��
 *     ���ڵ�
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key)
{
    if (tree == NULL)
    {
        // �½��ڵ�
        tree = new AVLTreeNode<T>(key, NULL, NULL);
        if (tree==NULL)
        {
            cout << "ERROR: create avltree node failed!" << endl;
            return NULL;
        }
    }
    else if (key < tree->key) // Ӧ�ý�key���뵽"tree��������"�����
    {
        tree->left = insert(tree->left, key);
        // ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height(tree->left) - height(tree->right) == 2)
        {
            if (key < tree->left->key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
    else if (key > tree->key) // Ӧ�ý�key���뵽"tree��������"�����
    {
        tree->right = insert(tree->right, key);
        // ����ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height(tree->right) - height(tree->left) == 2)
        {
            if (key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }
    else //key == tree->key)
    {
        cout << "���ʧ�ܣ������������ͬ�Ľڵ㣡" << endl;
    }

    tree->height = max( height(tree->left), height(tree->right)) + 1;

    return tree;
}

template <class T>
void AVLTree<T>::insert(T key)
{
    insert(mRoot, key);
}
/*
 * ɾ�����(z)�����ظ��ڵ�
 *
 * ����˵����
 *     tree AVL���ĸ����
 *     z ��ɾ���Ľ��
 * ����ֵ��
 *     ���ڵ�
 */
template <class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z)
{
    // ��Ϊ�� ���� û��Ҫɾ���Ľڵ㣬ֱ�ӷ���NULL��
    if (tree==NULL || z==NULL)
        return NULL;

    if (z->key < tree->key)        // ��ɾ���Ľڵ���"tree��������"��
    {
        tree->left = remove(tree->left, z);
        // ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height(tree->right) - height(tree->left) == 2)
        {
            AVLTreeNode<T> *r =  tree->right;
            if (height(r->left) > height(r->right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
    else if (z->key > tree->key)// ��ɾ���Ľڵ���"tree��������"��
    {
        tree->right = remove(tree->right, z);
        // ɾ���ڵ����AVL��ʧȥƽ�⣬�������Ӧ�ĵ��ڡ�
        if (height(tree->left) - height(tree->right) == 2)
        {
            AVLTreeNode<T> *l =  tree->left;
            if (height(l->right) > height(l->left))
                tree = leftRightRotation(tree);
            else
                tree = leftLeftRotation(tree);
        }
    }
    else    // tree�Ƕ�ӦҪɾ���Ľڵ㡣
    {
        // tree�����Һ��Ӷ��ǿ�
        if ((tree->left!=NULL) && (tree->right!=NULL))
        {
            if (height(tree->left) > height(tree->right))
            {
                // ���tree�����������������ߣ�
                // ��(01)�ҳ�tree���������е����ڵ�
                //   (02)�������ڵ��ֵ��ֵ��tree��
                //   (03)ɾ�������ڵ㡣
                // ����������"tree�������������ڵ�"��"tree"������
                // �������ַ�ʽ�ĺô��ǣ�ɾ��"tree�������������ڵ�"֮��AVL����Ȼ��ƽ��ġ�
                AVLTreeNode<T>* max = maximum(tree->left);
                tree->key = max->key;
                tree->left = remove(tree->left, max);
            }
            else
            {
                // ���tree��������������������(��������ȣ�������������������1)
                // ��(01)�ҳ�tree���������е���С�ڵ�
                //   (02)������С�ڵ��ֵ��ֵ��tree��
                //   (03)ɾ������С�ڵ㡣
                // ����������"tree������������С�ڵ�"��"tree"������
                // �������ַ�ʽ�ĺô��ǣ�ɾ��"tree������������С�ڵ�"֮��AVL����Ȼ��ƽ��ġ�
                AVLTreeNode<T>* min = maximum(tree->right);
                tree->key = min->key;
                tree->right = remove(tree->right, min);
            }
        }
        else
        {
            AVLTreeNode<T>* tmp = tree;
            tree = (tree->left!=NULL) ? tree->left : tree->right;
            delete tmp;
        }
    }

    return tree;
}

template <class T>
void AVLTree<T>::remove(T key)
{
    AVLTreeNode<T>* z;

    if ((z = search(mRoot, key)) != NULL)
        mRoot = remove(mRoot, z);
}
