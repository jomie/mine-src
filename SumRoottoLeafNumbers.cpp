
//* Definition for binary tree

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int sumNumbers(TreeNode *root) {
        if (!root)
            return 0;
        if (!root->left && !root->right)
            return root->val;

        int numRoot = root->val;
        int numLeft = 0;
        int numRight = 0;

        if (root->left)
            numLeft = SumtoLeaf(root->left, numRoot);
        if (root->right)
            numRight = SumtoLeaf(root->right, numRoot);
        return numLeft + numRight;
    }

    int SumtoLeaf(TreeNode *node, int num)
    {
        if (NULL == node->right && NULL == node->left)
            return num*10 + node->val;

        if (node->right && node->left)
            return SumtoLeaf(node->right, num * 10 + node->val) +
                     SumtoLeaf(node->left, num* 10 + node->val);
        else if (node->right)
            return SumtoLeaf(node->right, num * 10 + node->val);
        else
            return SumtoLeaf(node->left, num* 10 + node->val);

    }
};
