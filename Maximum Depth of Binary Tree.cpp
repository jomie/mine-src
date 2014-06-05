/**
 * Definition for binary tree  */
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    int maxDepth(TreeNode *root) {
        if(root == NULL)return 0;
            int res = INT_MIN;
            postorderTrav(root, res);
            return res;
    }
    int postorderTrav(TreeNode *root, int& res)
       {//返回值：root作为端点的path的最大值
           int left = 0, right = 0;
           if(root->left)left = postorderTrav(root->left, res);
           if(root->right)right = postorderTrav(root->right, res);
           int res_this = max(max(left+root->val, right+root->val), root->val);
           int tmp = max(res_this, left + right + root->val);
           if(tmp > res)
               res = tmp;
           return res_this;
       }


    bool isSameTree(TreeNode *p, TreeNode *q) {
        if (NULL == q && p == NULL)
            return true;
        if (!q || !p)
            return false;
        return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }

    bool hasPathSum(TreeNode *root, int sum) {

    }
};
