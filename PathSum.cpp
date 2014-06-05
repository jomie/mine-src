/**
  Definition for binary tree
   */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        if (NULL == root)
            return false;
        if (!root->left && !root->right && root->val == sum)
            return true;
        else
            return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
    vector<vector<int> > pathSum(TreeNode *root, int sum) {
        vector<vector<int> > result;
        vector<int> tmp;

        if (!root)
            return result;
        pathSumII(root, result, tmp, sum);
        return result;
    }
    void pathSumII(TreeNode *root, vector<vector<int> > &result, vector<int> &tmp, int sum)
    {
        tmp.push_back(root->val);
        if (!root->left && !root->right && sum == root->val)
        {
            result.push_back(tmp);
            return;
        }

        if (root->left)
        {
            pathSumII(root->left, result, tmp, sum - root->val);
        }
        if (root->right)
        {
            pathSumII(root->right, result, tmp, sum - root->val);
        }
        tmp.pop_back();
    }
};
