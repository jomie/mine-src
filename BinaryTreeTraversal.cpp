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
今天又犯了个大错误，乍看这道题又轻视它了，以为不用递归也是很简单的事情。事实上，不使用递归增加了几个级数的难度啊。
不使用额外空间，我现在还是觉得不可能做到的，或许会有某些天才以后做出来吧，应该是两个思路吧：
1. 最简单应该是使用两个栈作为额外空间。感觉好浪费哦。哎呀，又感觉自己怎么那么小气啊，一点空间都不舍得，呵呵。
2. 使用额外标识，可以知道是发生了递归了，还是新进入一个node。这个好像跟回溯法差不多，但是想想还是有很大区别的。
到处上网逛了逛，好像网上的也都是这两个思路。
还是使用两个栈比较简单，下面就用递归和用两个栈实现以下吧：
 
非常简单的递归：
[cpp] view plaincopyprint?在CODE上查看代码片派生到我的代码片
void postRecurse(TreeNode *node,vector<int> &onePath)  
    {  
        if(node == nullptr) return;  
        postRecurse(node->left, onePath);  
        postRecurse(node->right, onePath);  
        onePath.push_back(node->val);  
    }  
 
非简单的非递归：
[cpp] view plaincopyprint?在CODE上查看代码片派生到我的代码片
vector<int> postorderTraversal(TreeNode *root) {  
        vector<int> postPath;   
        postPath = postIter(root);  
        reverse(postPath.begin(), postPath.end());  
        return postPath;  
    }  
[cpp] view plaincopyprint?在CODE上查看代码片派生到我的代码片
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

代码优雅还是最重要的，最后代码我觉得还算优雅吧，不过也参考了一下别人的代码，改进一点自己的。
最近一直在研究算法，连我的本行图形学都有荒废了，不过不要紧吧。图形学基础打的非常好了，不会那么容易丢的。先练好算法，以便研究更深奥的图形学。
虽然感觉最近功力提升了，但是还是觉得功力不到家啊，这道题琢磨了我很长时间，要努力提升！

2014-1-10更新：
上面的非递归算法，需要对后序遍历的顺序非常熟悉，然后才能逆序访问，最后反转输出结果，虽然很适合这道题，因为题目要求保存结果，但是我们也可以正常顺序非递归访问。
程序如下：
[cpp] view plaincopyprint?在CODE上查看代码片派生到我的代码片
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
这样访问就会破坏了原树的结构，我们可以增加两个标志，就不会破坏原树结构了。
[cpp] view plaincopyprint?在CODE上查看代码片派生到我的代码片
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

这两个标志设计也非常巧妙的，安排不好，结果就会不正确。
非递归遍历树总结：
1 前序遍历不需要增加标志
2 中序遍历需要增加一个标志
3 后序就需要增加两个标志
难度也是一个比一个难。

[cpp] view plaincopyprint?在CODE上查看代码片派生到我的代码片
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

[cpp] view plaincopyprint?在CODE上查看代码片派生到我的代码片
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
