
// * Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {

        vector<int> output;
        if (!root)
            return output;

       stack<TreeNode*> st;
        st.push_back(root);

        TreeNode *pre = NULL;
        TreeNode *p = NULL;
        while(!st.empty())
        {
            p = st.top();
            if ((!p->left && !p->right) ||
                (pre &&( pre == p->left || pre == p->right)))
            {
                output.push_back(p->val);
                st.pop();
                pre = p;
            }
            else{

                if (p->right)
                    st.push(p->right);
                if (p->left)
                    st.push(p->left);
            }
        }
        return output;
    }


    void post(TreeNode *root, vector<int> &postbuf)
    {

        //        vector<int> postbuf;
        //        post(root, postbuf);
        //        return postbuf;
        if(!root)
            return;

        if(root->left)
            post(root->left, postbuf);
        if (root->right)
            post(root->right, postbuf);
        postbuf.push_back(root->val);
    }

    vector<int> frontorderTraversal(TreeNode *root)
    {
        vector<int> output;
        if (!root)
            return output;

        stack<TreeNode*> st;
        TreeNode *tmp = NULL;

        st.push(root);

        while(!st.empty()){
            tmp = st.top();
            st.pop();
            output.push_back(tmp->val);

            if(tmp->right)
                st.push(tmp->right);
            if(tmp->left)
                st.push(tmp->left);
        }

        return output;
    }

    vector<int> midorderTraversal(TreeNode *root)
    {
        //        vector<int> output;
        //        if (!root)
        //            return output;
        //
        //        stack<TreeNode *> st;
        //        TreeNode *tmp = root;
        //
        ////        st.push(root);
        //
        //        while(tmp || !st.empty())
        //        {
        //            while (tmp){
        //
        //                st.push(tmp);
        //                tmp->left;
        //            }
        //
        //            if (!st.empty())
        //            {
        //                tmp = st.top();
        //                st.pop();
        //                output.push_back(tmp->v)
        //            }
        //        }
        //        return output;

        vector<int> output;
        if (!root)
            return output;

        stack<TreeNode *> st;
        TreeNode *tmp;

        st.push(root);

        while(!st.empty())
        {

            while (st.top()->left)
                st.push(st.top()->left);

            tmp = st.top();
            st.pop();

            output.push_back(tmp->val);

            if (tmp->right)
            {
                push
                    }
        }
        return output;
    }

};
