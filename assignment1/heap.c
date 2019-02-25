/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Module for creating and manipulating min heap containing data   *
 * of type float                                                   *
 *                                                                 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2018 *
 * by Renjie Meng         renjiem@student.unmimelb.edu.au          *
 * 2018/03/25 23:38                                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"

/* * * * * * 
 * FUNCTION DEFINITIONS
 */ 


/*
 *Function: heap_swap
 *------------------------------
 * Swap two element in the array
 * @param: h1-->Heap_Item_t 1
 *         h2-->Heap_Item_t 2
 * return: none
 */
void 
heap_swap(Heap_Item_t *h1, Heap_Item_t *h2){
    Heap_Item_t temp;
    // Initialize temp to store information
    temp = *h1;
    *h1 = *h2;
    *h2 = temp;
}

/*
 *Function: siftup
 *------------------------------
 * Sift the Heap_Item_t up to the right position
 * @param: h--> heap
 *         i--> index of Heap_Item_t
 * return: none
 */
void 
siftup(Heap_t *h, int i){
    int parent;
    if (i == 0){
        // it is the root, STOP!!!
        return;
    }else if (i>=h->max_size){
        // INVALID ACTION!! WARNING!!
        printf("WARNING: Index Out Of Range!");
    }else {
        parent = (i-1)/2;
        if (h->heap[parent].key>h->heap[i].key){
            // if it is smaller than its parent, replace its parent
            heap_swap(&(h->heap[parent]), &(h->heap[i]));
            // recursively compare until find the right position
            siftup(h, parent);
        }
    }
}

/*
 *Function: min_child
 *------------------------------
 * find the smaller child's index
 * @param: h--> heap
 *         i--> index of Heap_Item_t
 * return: smaller child's index or NOCHILD
 */
int 
min_child(Heap_t *h, int i){
    // Initialize two children
    int left_child = 2*i+1;
    int right_child = left_child+1;

    if (left_child>=h->curr_size){
        // children index out of range, which mean no child
        return NOCHILD;
    }else if (left_child<h->curr_size&&right_child>=h->curr_size){
        // Have only one child
        return left_child;
    }else if (right_child<h->curr_size){
        // Have two children, return the smaller one
        if (h->heap[right_child].key>h->heap[left_child].key){
            return left_child;
        }else{
            return right_child;
        }
    }
    // Error --> no child
    return NOCHILD;
}

/*
 *Function: siftdown
 *------------------------------
 * Sift the Heap_Item_t down to the right position
 * @param: h--> heap
 *         i--> index of Heap_Item_t
 * return: none
 */
void 
siftdown(Heap_t *h, int i){
    int min_child_index = min_child(h, i);
    if ((min_child_index == NOCHILD) ||\
     (h->heap[i].key<=h->heap[min_child_index].key)){
         // if it has no children or smaller than it min child
         // we are at right position now. 
         // STOP!!!
        return;
    }else{
        // it smaller than its min children
        // replace min child
        heap_swap(&(h->heap[i]), &(h->heap[min_child_index]));
        // recursively finding downside
        siftdown(h, min_child_index);
    }
}

/*
 *Function: new_heap
 *------------------------------
 * Create a new heap and allocte max_size memory space - 
 * - for the array inside it
 * @param: max_size --> the size of array of Heap_Item
 * return: a allocated Heap_t* with max_size of array of Heap_Item
 */
Heap_t 
*new_heap(int max_size){
    Heap_t *new;
    new = (Heap_t*)malloc(sizeof(*new));
    new->heap = (Heap_Item_t*)malloc(sizeof(*(new->heap))*max_size);
    new->curr_size = 0;
    new->max_size = max_size;
    return new;
}

/*
 *Function: heap_insert
 *------------------------------
 * insert a new Heap_Item to min heap
 * @param: h--> heap
 *         key --> float number
 *         data --> int number
 * return: none
 */
void 
heap_insert(Heap_t *h, float key, int data){
    // check if ther is enough memory space
    if (h->curr_size == h->max_size){
        h->max_size*=2;
        h->heap = realloc(h->heap, sizeof(*(h->heap))*h->max_size);
    }
    // add new Item to the last position
    h->heap[h->curr_size].key = key;
    h->heap[h->curr_size].data = data;
    // find its position
    siftup(h, h->curr_size);
    // Increment current size
    h->curr_size++;
}

/*
 *Function: heap_remove_min
 *------------------------------
 * Remove the HeapItem with min key 
 * then swap last HeapItem to first position
 * to find new min of the heap.
 * @param: h--> heap
 * return: the data with minimum key
 */
int
heap_remove_min(Heap_t *h){
    assert(h!=NULL);
    if (h->curr_size==0){
        // empty heap
        return -1; 
    }
    if (h->curr_size==1){ 
        // single heap
        h->curr_size--;
        return h->heap[0].data;
    }
    int min = h->heap[0].data;
    heap_swap(&(h->heap[0]), &(h->heap[h->curr_size -1]));
    h->curr_size--;//remove old min out from our heap
    siftdown(h, 0);
    return min;
}

/*
 *Function: heap_peek_min
 *------------------------------
 * find the data with min key
 * @param: h--> heap
 * return: data with min key
 */
int 
heap_peek_min(Heap_t *h){
    return h->heap[0].data;
}

/*
 *Function: heap_peek_key
 *------------------------------
 * find min key
 * @param: h--> heap
 * return: min key
 */
float 
heap_peek_key(Heap_t *h){
    return h->heap[0].key;
}

/*
 *Function: free_heap
 *------------------------------
 * free all pointers in heap
 * @param: h--> heap
 * return: none
 */
void 
free_heap(Heap_t *h){
    assert(h!=NULL);
    free(h->heap);
    h->heap = NULL;
    free(h);
    h = NULL;
}  

/*
 *Function: de_queue
 *------------------------------
 * print out all the data,key pair in ascending order.
 * @param: h--> heap
 * return: none
 */
void 
de_queue_descending(Heap_t *h){
    assert(h!=NULL);
    // if there no items in the heap print WARNING message
    if (h->curr_size==0){
        printf("EMPTY HEAP!!!!\n");
        return;
    }
    // print out the values in ascending order
    Heap_Item_t descending_order_array[h->curr_size];
    int count = 0;
    int size = h->curr_size;
    while (h->curr_size>0){
        descending_order_array[count].key = h->heap[0].key;
        descending_order_array[count++].data = h->heap[0].data; 
        heap_remove_min(h); 
    }
    // print out
    for (int i=size-1; i>=0; i--){
        printf("%6d %.6f\n", descending_order_array[i].data, descending_order_array[i].key);
    }
}  


/*
 *Function: DocHeap_swap
 *------------------------------
 * Swap two element in the array
 * @param: h1-->DocHeap_Item_t 1
 *         h2-->DocHeap_Item_t 2
 * return: none
 */
void 
DocHeap_swap(DocHeap_Item_t *h1, DocHeap_Item_t *h2){
    DocHeap_Item_t temp;
    // Initialize temp to store information
    temp = *h1;
    *h1 = *h2;
    *h2 = temp;
}

/*
 *Function: DocHeap_siftup
 *------------------------------
 * Sift the DocHeap_Item_t up to the right position
 * @param: h--> DocHeap
 *         i--> index of DocHeap_Item_t
 * return: none
 */
void 
DocHeap_siftup(DocHeap_t *h, int i){
    int parent;
    if (i == 0){
        // it is the root, STOP!!!
        return;
    }else if (i>=h->max_size){
        // INVALID ACTION!! WARNING!!
        printf("WARNING: Index Out Of Range!");
    }else {
        parent = (i-1)/2;
        if (h->DocHeap[parent].id>h->DocHeap[i].id){
            // if it is smaller than its parent, replace its parent
            DocHeap_swap(&(h->DocHeap[parent]), &(h->DocHeap[i]));
            // recursively compare until find the right position
            DocHeap_siftup(h, parent);
        }
    }
}

/*
 *Function: DocHeap_min_child
 *------------------------------
 * find the smaller child's index
 * @param: h--> DocHeap
 *         i--> index of DocHeap_Item_t
 * return: smaller child's index or NOCHILD
 */
int 
DocHeap_min_child(DocHeap_t *h, int i){
    // Initialize two children
    int left_child = 2*i+1;
    int right_child = left_child+1;

    if (left_child>=h->curr_size){
        // children index out of range, which mean no child
        return NOCHILD;
    }else if (left_child<h->curr_size&&right_child>=h->curr_size){
        // Have only one child
        return left_child;
    }else if (right_child<h->curr_size){
        // Have two children, return the smaller one
        if (h->DocHeap[right_child].id>h->DocHeap[left_child].id){
            return left_child;
        }else{
            return right_child;
        }
    }
    // Error --> no child
    return NOCHILD;
}

/*
 *Function: DocHeap_siftdown
 *------------------------------
 * Sift the DocHeap_Item_t down to the right position
 * @param: h--> DocHeap
 *         i--> index of DocHeap_Item_t
 * return: none
 */
void 
DocHeap_siftdown(DocHeap_t *h, int i){
    int min_child_index = DocHeap_min_child(h, i);
    if ((min_child_index == NOCHILD) ||\
     (h->DocHeap[i].id<=h->DocHeap[min_child_index].id)){
         // if it has no children or smaller than it min child
         // we are at right position now. 
         // STOP!!!
        return;
    }else{
        // it smaller than its min children
        // replace min child
        DocHeap_swap(&(h->DocHeap[i]), &(h->DocHeap[min_child_index]));
        // recursively finding downside
        DocHeap_siftdown(h, min_child_index);
    }
}

/*
 *Function: new_DocHeap
 *------------------------------
 * Create a new heap and allocte max_size memory space - 
 * - for the array inside it
 * @param: max_size --> the size of array of Heap_Item
 * return: a allocated DocHeap_t* with max_size of array of DocHeap_Item
 */
DocHeap_t 
*new_DocHeap(int max_size){
    DocHeap_t *new;
    new = (DocHeap_t*)malloc(sizeof(*new));
    new->DocHeap = (DocHeap_Item_t*)malloc(sizeof(*(new->DocHeap))*max_size);
    new->curr_size = 0;
    new->max_size = max_size;
    return new;
}

/*
 *Function: DocHeap_insert
 *------------------------------
 * insert a new DocHeap_Item to min heap
 * @param: h--> DocHeap
 *         score --> float number
 *         id --> int number
 * return: none
 */
void 
DocHeap_insert(DocHeap_t *h, float score, int id, void* queryPtr){
    // check if ther is enough memory space
    if (h->curr_size == h->max_size){
        h->max_size*=2;
        h->DocHeap = realloc(h->DocHeap, sizeof(*(h->DocHeap))*h->max_size);
    }
    // add new Item to the last position
    h->DocHeap[h->curr_size].score = score;
    h->DocHeap[h->curr_size].id = id;
     h->DocHeap[h->curr_size].queryPtr = queryPtr;
    // find its position
    DocHeap_siftup(h, h->curr_size);
    // Increment current size
    h->curr_size++;
}

/*
 *Function: DocHeap_remove_min
 *------------------------------
 * Remove the DocHeapItem with min key 
 * then swap last DocHeapItem to first position
 * to find new min of the DocHeap.
 * @param: h--> DocHeap
 * return: the score with minimum id
 */
int
DocHeap_remove_min(DocHeap_t *h){
    assert(h!=NULL);
    if (h->curr_size==0){
        // empty heap
        return -1; 
    }
    if (h->curr_size==1){ 
        // single heap
        h->curr_size--;
        return h->DocHeap[0].score;
    }
    int min = h->DocHeap[0].score;
    DocHeap_swap(&(h->DocHeap[0]), &(h->DocHeap[h->curr_size -1]));
    h->curr_size--;//remove old min out from our heap
    DocHeap_siftdown(h, 0);
    return min;
}

/*
 *Function: DocHeap_peek_min
 *------------------------------
 * find the score with min id
 * @param: h--> heap
 * return: score with min id
 */
int 
DocHeap_peek_min(DocHeap_t *h){
    return h->DocHeap[0].score;
}

/*
 *Function: DocHeap_peek_id
 *------------------------------
 * find min id
 * @param: h--> DocHeap
 * return: min id
 */
float 
DocHeap_peek_key(DocHeap_t *h){
    return h->DocHeap[0].id;
}

/*
 *Function: free_DocHeap
 *------------------------------
 * free all pointers in DocHeap
 * @param: h--> DocHeap
 * return: none
 */
void 
free_DocHeap(DocHeap_t *h){
    assert(h!=NULL);
    free(h->DocHeap);
    h->DocHeap = NULL;
    free(h);
    h = NULL;
}  



/*
 *Function: DocHeap_de_queue_descending
 *------------------------------
 * print out all the id, score pair in ascending order.
 * @param: h--> DocHeap
 * return: none
 */
void 
DocHeap_de_queue_descending(DocHeap_t *h){
    assert(h!=NULL);
    // if there no items in the heap print WARNING message
    if (h->curr_size==0){
        printf("EMPTY HEAP!!!!\n");
        return;
    }
    // print out the values in ascending order
    DocHeap_Item_t descending_order_array[h->curr_size];
    int count = 0;
    int size = h->curr_size;
    while (h->curr_size>0){
        descending_order_array[count].id = h->DocHeap[0].id;
        descending_order_array[count++].score = h->DocHeap[0].score; 
        DocHeap_remove_min(h); 
    }
    // print out
    for (int i=0; i<size; i++){
        printf("%6d %.6f\n", descending_order_array[i].id, descending_order_array[i].score);
    }
} 
