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
    vector<vector<int> > levelOrder(TreeNode *root) {
        /*    vector<vector<int> > output;

        if (!root)
            return output;

        vector<TreeNode*> list;
        list.push_back(root);

        TreeNode *pLeftFirt = NULL, *tmp = NULL;

        if (root->left)
            pLeftFirt = root->left;
        else if (root->right)
            pLeftFirt = root->right;

        while(!list.empty())
        {
            vector<int> leveloutput;
            while (!list.empty() && list.front() != pLeftFirt)
            {
                tmp = list.front();
                list.erase(list.begin());

                if (!pLeftFirt)
                {
                    if (tmp->left)
                        pLeftFirt = tmp->left;
                    else if (tmp->right)
                        pLeftFirt = tmp->right;
                }

                if (tmp->left)
                    list.push_back(tmp->left);
                if (tmp->right)
                    list.push_back(tmp->right);

                leveloutput.push_back(tmp->val);
            }

            if (list.front()->left)
                pLeftFirt = list.front()->left;
            else if(list.front()->right)
                pLeftFirt = list.front()->right;
            else
                pLeftFirt = NULL;

            output.push_back(leveloutput);

        }
        return output;
        */

        vector< vector<int> > output;
        if(!root)
            return output;

        queue<TreeNode*> list;
        list.push_back(root);
        list.push(NULL);
        vector<int> level;
        TreeNode *tmp;

        while(!list.empty())
        {
            tmp = list.front();
            list.erase(list.begin());
            if (tmp)
            {
                level.push(tmp->val);
                if (tmp->left)
                    list.push(tmp->left);
                if (tmp->right)
                    list.push(tmp->right);
            }
            else
            {
                output.push_back(level);
                if (!list.empty()){
                    level.clear();
                    list.push(NULL);
                }

            }
        }
        return output;
    }
};
