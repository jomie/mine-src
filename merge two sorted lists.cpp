/**
  Definition for singly-linked list.
  */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (!l1 && !l2)
            return NULL;

        if (l1 && ! l2)
            return l1;
        else if (!l1 && l2)
            return l2;

        ListNode *p1 = l1;
        ListNode *p2 = l2;

        ListNode *result = NULL;
        ListNode *p3 = result;

        if (p1->val <= p2->val)
        {
            p3 = p1;
            p1 = p1->next;
            p3->next = NULL;
        }

        while (p1 && p2)
        {
            if (p1 == p2){
                p3->next = p1;
                break;
            } else if (p1->val <= p2->val){
                p3->next = p1;
                p1 = p1->next;

            } else {
                p3->next = p2;
                p2 = p2->next;

            }
            p3 = p3->next;
        }

        if (p1 == p2)
            return result;
        else if(p1) {
            p3->next = p1;
        } else
            p3->next = p2;

        return result;

    }
};
