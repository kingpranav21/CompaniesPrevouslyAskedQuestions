
// You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

// Merge all the linked-lists into one sorted linked-list and return it.

 

// Example 1:

// Input: lists = [[1,4,5],[1,3,4],[2,6]]
// Output: [1,1,2,3,4,4,5,6]
// Explanation: The linked-lists are:
// [
//   1->4->5,
//   1->3->4,
//   2->6
// ]
// merging them into one sorted linked list:
// 1->1->2->3->4->4->5->6
// Example 2:

// Input: lists = []
// Output: []
// Example 3:

// Input: lists = [[]]
// Output: []
 

// Constraints:

// k == lists.length
// 0 <= k <= 104
// 0 <= lists[i].length <= 500
// -104 <= lists[i][j] <= 104
// lists[i] is sorted in ascending order.
// The sum of lists[i].length will not exceed 104.


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    //Approach - 1 using array TC : O(nlogn), SC: O(n)
    // ListNode* mergeKLists(vector<ListNode*>& lists) {
    //     vector<int>arr;
    //     for(ListNode* list : lists){
    //         ListNode* temp = list;
    //         while(temp){
    //             arr.push_back(temp->val);
    //             temp = temp->next;
    //         }
    //     }

    //     sort(begin(arr),end(arr));
    //     ListNode* dummy = new ListNode(0);
    //     ListNode* curr = dummy;
    //     for(int i=0;i<arr.size();i++){
    //         curr->next = new ListNode(arr[i]);
    //         curr = curr->next;
    //     }
    //     return dummy->next;
    // }

    //Approach - 2 merge list one by one Tc- O(n*k) , Sc- O(1)
    // ListNode* mergeKLists(vector<ListNode*>&lists){
    //     if(lists.empty())return {};
    //     ListNode* l1 = lists[0];
    //     for(int i=1;i<lists.size();i++){
    //         ListNode* l2 = lists[i];
    //         l1 = merge(l1,l2);
    //     }
    //     return l1;
    // }
    // ListNode* merge(ListNode* l1, ListNode* l2){
    //     ListNode* dummy = new ListNode(0);
    //     ListNode* curr = dummy;

    //     while(l1!=NULL  && l2!=NULL){
    //         if(l1->val<=l2->val){
    //             curr->next = l1;
    //             l1=l1->next;
    //         }else{
    //             curr->next = l2;
    //             l2=l2->next;
    //         }
    //         curr = curr->next;
    //     }
    //     if(l1!=NULL){
    //         curr->next = l1;
    //     }
    //     if(l2!=NULL){
    //         curr->next = l2;
    //     }
    //     return dummy->next;
    // }

    //Approach - 3 using priority queue T.C->N(logk), SC->O(k)
    //Where k is the total number of lists and n is the total number of nodes across k lists.

    ListNode* mergeKLists(vector<ListNode*>& lists){
        //so we will store on the basis of the value and then sort it
        priority_queue<pair<int,ListNode*>, vector<pair<int,ListNode*>>, greater<pair<int, ListNode*>>>min_heap;
        for(ListNode* list: lists){
            if(list)min_heap.push({list->val, list});
        }
        ListNode* dummy = new ListNode(-1);
        ListNode* curr = dummy;
        while(!min_heap.empty()){
            pair<int,ListNode*>temp = min_heap.top();
            min_heap.pop();
            curr->next = temp.second;
            if(temp.second->next){
                min_heap.push({temp.second->next->val, temp.second->next});
            }
            curr=curr->next;
        }
        return dummy->next;
    }

    //Approach - 4 divide and conquer , merge 0 to mid then mid + 1 to end
};
