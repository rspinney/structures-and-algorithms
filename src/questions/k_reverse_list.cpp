/*****************************************************************************/
/******************** Copyright (C) 2022, Richard Spinney. *******************/
/*****************************************************************************/
//                                                                           //
//    This program is free software: you can redistribute it and/or modify   //
//    it under the terms of the GNU General Public License as published by   //
//    the Free Software Foundation, either version 3 of the License, or      //
//    (at your option) any later version.                                    //
//                                                                           //
//    This program is distributed in the hope that it will be useful,        //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                           //
//                                                                           //
//    You should have received a copy of the GNU General Public License      //
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/*
Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.

k is a positive integer and is less than or equal to the length of the linked list. 
If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

e.g.
{1,2,3,4,5,6,7,8,9,10,11} with k = 3 becomes
{3,2,1,6,5,4,9,8,7,10,11}

You may not alter the values in the list's nodes, only nodes themselves may be changed.
*/
 
 #include <iostream>
 //list def
  struct ListNode {
    int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 

 //old solution
class Solution1 {
    int getLength(ListNode *ptr){
        int len = 0;
        while(ptr){
            len++;
            ptr = ptr -> next;
        }
        return len;
    }
    inline ListNode* reverseGroup(ListNode* head){
        ListNode* ptr = head;
        ListNode* nextptr = head->next;
        ListNode* prevptr = nullptr;
        while(ptr->next){
            nextptr = ptr->next;
            ptr->next = prevptr;
            prevptr= ptr;
            ptr=nextptr;
        }
        ptr->next =prevptr;
        return ptr;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        
        if((!head)||(!head->next))
            return head;
        ListNode* blockptr = head;
        ListNode* blockprevptr = nullptr;
        ListNode* last = head;
        bool inRange = true;
        while(inRange){
            //std::cout<<blockptr->val<<std::endl;
            ListNode *blocknext = blockptr;
            for (auto i=0;i<k;++i){ //this bit is inefficient
                if (blocknext){
                    last = blocknext;
                    blocknext = blocknext->next;
                }
                else{
                    inRange = false;
                    break;
                }
            }
            if (inRange){
                last->next = nullptr;
                ListNode* rev = reverseGroup(blockptr);
                //std::cout<<"sort "<<rev->val<<" "<<blockptr->val<<std::endl;
                if (blockprevptr)
                    blockprevptr->next=rev;
                else
                    head = rev;
                blockptr->next = blocknext;
                blockprevptr = blockptr;
               blockptr = blocknext;
            }

        }
        return head;
    }
};


//better solution

class Solution2 {
    int getLength(ListNode *ptr){
        int len = 0;
        while(ptr){
            len++;
            ptr = ptr -> next;
        }
        return len;
    }
    inline ListNode* reverseGroup(ListNode* head,int k){
        ListNode* ptr = head;
        ListNode* nextptr = head->next;
        ListNode* prevptr = nextptr; // k=1 edge case
        int c=1;
        while(c<k){
            nextptr = ptr->next;
            ptr->next = prevptr;
            prevptr= ptr;
            ptr=nextptr;
            ++c;
        }
        nextptr = ptr->next;
        head->next= nextptr;
        ptr->next =prevptr;
            
        return ptr;
    }
public:
   ListNode* reverseKGroup(ListNode* head, int k) {
        
        //do nothing cases
        if((!head)||(!head->next))
            return head;

        //use blockptr as pointer to heads of k-long blocks
        ListNode* blockptr = head;
        //pointer before the block
        ListNode* prevtail = nullptr;

        //how many groups of k to reverse    
        int len = getLength(head);
        int blocks = len/k;

        for (int j=0;j<blocks;++j){
            //reverses k nodes AND attaches remaining tail
            ListNode* rev = reverseGroup(blockptr,k);

            //attach block and tail to previous part of list
            if (j==0)//head case
                head = rev;
            else
                prevtail->next = rev;
            
            prevtail = blockptr;
            blockptr=blockptr->next;
        }
        return head;
    }
};

//best? solution - removes branches

class Solution {
    int getLength(ListNode *ptr){
        int len = 0;
        while(ptr){
            len++;
            ptr = ptr -> next;
        }
        return len;
    }
    inline ListNode* reverseGroup(ListNode* head,int k){
        ListNode* ptr = head;
        ListNode* nextptr = head->next;
        ListNode* prevptr = nextptr; // k=1 edge case
        int c=0;
        while(c<k){
            nextptr = ptr->next;
            ptr->next = prevptr;
            prevptr= ptr;
            ptr=nextptr;
            ++c;
        }
        head->next= nextptr;   //attach the rest of list to what is now end of k-block
        return prevptr; //return new - head of k-block
    }
public:
   ListNode* reverseKGroup(ListNode* head, int k) {
        
        int blocks = getLength(head)/k;
        ListNode* blockptr = head;       
        ListNode* prevtail = nullptr;
        for (int j=0;j<blocks;++j){     
            if (j)       
                prevtail->next = reverseGroup(blockptr,k);            
            else
                head = reverseGroup(blockptr,k);
            prevtail = blockptr;
            blockptr=blockptr->next;
        }
       return head;
       
    }

};

int main(){
    ListNode* head = new ListNode(1);
    ListNode* p = head;
    for (auto i=0;i<10;++i){
        ListNode* pp = new ListNode(i+2);
        p->next = pp;
        p=p->next;
    }
    Solution sol;
    ListNode *newhead = sol.reverseKGroup(head,5);
    p=newhead;
    while(p){
        std::cout<<p->val<<" ";
        p=p->next;
    }
    std::cout<<std::endl;
    return 0;
}