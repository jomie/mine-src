Given a binary tree, return the postorder traversal of its nodes' values.
For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [3,2,1].
Note: Recursive solution is trivial, could you do it iteratively?
�����ַ��˸������է����������������ˣ���Ϊ���õݹ�Ҳ�Ǻܼ򵥵����顣��ʵ�ϣ���ʹ�õݹ������˼����������ѶȰ���
��ʹ�ö���ռ䣬�����ڻ��Ǿ��ò����������ģ��������ĳЩ����Ժ��������ɣ�Ӧ��������˼·�ɣ�
1. ���Ӧ����ʹ������ջ��Ϊ����ռ䡣�о����˷�Ŷ����ѽ���ָо��Լ���ô��ôС������һ��ռ䶼����ã��Ǻǡ�
2. ʹ�ö����ʶ������֪���Ƿ����˵ݹ��ˣ������½���һ��node�������������ݷ���࣬�������뻹���кܴ�����ġ�
�����������˹䣬�������ϵ�Ҳ����������˼·��
����ʹ������ջ�Ƚϼ򵥣�������õݹ��������ջʵ�����°ɣ�
 
�ǳ��򵥵ĵݹ飺
[cpp] view plaincopyprint?��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ
void postRecurse(TreeNode *node,vector<int> &onePath)  
    {  
        if(node == nullptr) return;  
        postRecurse(node->left, onePath);  
        postRecurse(node->right, onePath);  
        onePath.push_back(node->val);  
    }  
 
�Ǽ򵥵ķǵݹ飺
[cpp] view plaincopyprint?��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ
vector<int> postorderTraversal(TreeNode *root) {  
        vector<int> postPath;   
        postPath = postIter(root);  
        reverse(postPath.begin(), postPath.end());  
        return postPath;  
    }  
[cpp] view plaincopyprint?��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ
vector<int> postIter(TreeNode *node)   
    {  
        vector<int> output;  
        if (!node) return output;  
        vector<TreeNode *> vt;  
        vt.push_back(node);  
        while (!vt.empty())   
        {  
            TreeNode *cur = vt.back();  
            output.push_back(cur->val);  
            vt.pop_back();  
            if (cur->left)  
                vt.push_back(cur->left);  
            if (cur->right)  
                vt.push_back(cur->right);  
        }  
        return output;  
    }  

�������Ż�������Ҫ�ģ��������Ҿ��û������Űɣ�����Ҳ�ο���һ�±��˵Ĵ��룬�Ľ�һ���Լ��ġ�
���һֱ���о��㷨�����ҵı���ͼ��ѧ���лķ��ˣ�������Ҫ���ɡ�ͼ��ѧ������ķǳ����ˣ�������ô���׶��ġ��������㷨���Ա��о�����µ�ͼ��ѧ��
��Ȼ�о�������������ˣ����ǻ��Ǿ��ù��������Ұ����������ĥ���Һܳ�ʱ�䣬ҪŬ��������

2014-1-10���£�
����ķǵݹ��㷨����Ҫ�Ժ��������˳��ǳ���Ϥ��Ȼ�����������ʣ����ת����������Ȼ���ʺ�����⣬��Ϊ��ĿҪ�󱣴�������������Ҳ��������˳��ǵݹ���ʡ�
�������£�
[cpp] view plaincopyprint?��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ
vector<int> postorderTraversal(TreeNode *root)   
    {  
        vector<int> rs;  
        if (!root) return rs;  
  
        stack<TreeNode *> stk;  
        stk.push(root);  
  
        while (!stk.empty())  
        {  
            while (stk.top()->left) stk.push(stk.top()->left);  
            if (stk.top()->right) stk.push(stk.top()->right);  
            else   
            {  
                TreeNode *t = stk.top();  
                stk.pop();  
                rs.push_back(t->val);  
                if (!stk.empty())  
                {  
                    if (stk.top()->left == t) stk.top()->left = NULL;  
                    else stk.top()->right = NULL;  
                }  
            }  
        }  
        return rs;  
    }  
�������ʾͻ��ƻ���ԭ���Ľṹ�����ǿ�������������־���Ͳ����ƻ�ԭ���ṹ�ˡ�
[cpp] view plaincopyprint?��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ
vector<int> postorderTraversal(TreeNode *root)   
    {  
        vector<int> rs;  
        if (!root) return rs;  
  
        stack<TreeNode *> stk;  
        stk.push(root);  
        bool lflag = false;  
        bool rflag = false;  
  
        while (!stk.empty())  
        {  
            while (!lflag && stk.top()->left) stk.push(stk.top()->left);  
            if (!rflag && stk.top()->right)  
            {  
                stk.push(stk.top()->right);  
                lflag = false;  
            }  
            else   
            {  
                TreeNode *t = stk.top();  
                stk.pop();  
                rs.push_back(t->val);  
                lflag = true;  
                if (!stk.empty() && stk.top()->right == t) rflag = true;  
                else rflag = false;  
            }  
        }  
        return rs;  
    }  

��������־���Ҳ�ǳ�����ģ����Ų��ã�����ͻ᲻��ȷ��
�ǵݹ�������ܽ᣺
1 ǰ���������Ҫ���ӱ�־
2 ���������Ҫ����һ����־
3 �������Ҫ����������־
�Ѷ�Ҳ��һ����һ���ѡ�

[cpp] view plaincopyprint?��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ
//2014-2-19_1 update  
    vector<int> postorderTraversal(TreeNode *root)   
    {  
        vector<int> rs;  
        if (!root) return rs;  
        stack<TreeNode *> stk;  
        stk.push(root);  
        TreeNode *pre = nullptr;  
        while (!stk.empty())  
        {  
            if ((!pre || pre->left == stk.top() || pre->right == stk.top())   
                && stk.top()->left)  
            {  
                pre = stk.top();  
                stk.push(stk.top()->left);  
            }  
            else if (((!stk.top()->left && pre != stk.top()->right)  
                || pre == stk.top()->left) && stk.top()->right)  
            {  
                pre = stk.top();  
                stk.push(stk.top()->right);  
            }  
            else  
            {  
                pre = stk.top();  
                stk.pop();  
                rs.push_back(pre->val);  
            }  
        }  
        return rs;  
    }  

[cpp] view plaincopyprint?��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ
//2014-2-19_2 update  
    vector<int> postorderTraversal(TreeNode *root)   
    {  
        vector<int> rs;  
        if (!root) return rs;  
        stack<TreeNode *> stk;  
        stk.push(root);  
        while (!stk.empty())  
        {  
            TreeNode *t = stk.top();  
            stk.pop();  
            rs.push_back(t->val);  
            if (t->left) stk.push(t->left);  
            if (t->right) stk.push(t->right);  
        }  
        reverse(rs.begin(), rs.end());  
        return rs;  
    }  
