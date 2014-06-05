/**
 * Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void reorderList(ListNode *head) {
        if (!head)
            return;

        stack<ListNode*> st;

        ListNode* p = head;
        while(p)
        {
            st.push(p);
            p = p->next;
        }

        ListNode* alter = head;
        p = st.top();
        st.pop();

        while (p != alter && p != alter->next )
        {
            p->next = alter->next;
            alter->next = p;
            alter = p->next;

            p = st.top();
            st.pop();
        }

        alter->next = NULL;
    }
};
