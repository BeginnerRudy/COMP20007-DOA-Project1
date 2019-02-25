/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Module for creating and manipulating min heap containing data   *
 * of type float                                                   *
 *                                                                 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2018 *
 * by Renjie Meng         renjiem@student.unmimelb.edu.au          *
 * 2018/03/25 23:38                                                *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// indicates parent in the heap does not have children
# define NOCHILD -1 

// Store key, data ({float, int}) information
typedef struct{
    float score;
    int id;
}DocHeap_Item_t;

// Array based min heap structure
// max_size records heap's allocated memory space
// curr_size records #Heap items stored in min heap currently
typedef struct{
    DocHeap_Item_t *DocHeap;
    int max_size;
    int curr_size;
}DocHeap_t;

/*
 *Function: DocHeap_swap
 *------------------------------
 * Swap two element in the array
 * @param: h1-->DocHeap_Item_t 1
 *         h2-->DocHeap_Item_t 2
 * return: none
 */
void 
DocHeap_swap(DocHeap_Item_t *h1, DocHeap_Item_t *h2);
/*
 *Function: DocHeap_siftup
 *------------------------------
 * Sift the DocHeap_Item_t up to the right position
 * @param: h--> DocHeap
 *         i--> index of DocHeap_Item_t
 * return: none
 */
void 
DocHeap_siftup(DocHeap_t *h, int i);


/*
 *Function: DocHeap_min_child
 *------------------------------
 * find the smaller child's index
 * @param: h--> DocHeap
 *         i--> index of DocHeap_Item_t
 * return: smaller child's index or NOCHILD
 */
int 
DocHeap_min_child(DocHeap_t *h, int i);

/*
 *Function: DocHeap_siftdown
 *------------------------------
 * Sift the DocHeap_Item_t down to the right position
 * @param: h--> DocHeap
 *         i--> index of DocHeap_Item_t
 * return: none
 */
void 
DocHeap_siftdown(DocHeap_t *h, int i);

/*
 *Function: new_DocHeap
 *------------------------------
 * Create a new heap and allocte max_size memory space - 
 * - for the array inside it
 * @param: max_size --> the size of array of Heap_Item
 * return: a allocated DocHeap_t* with max_size of array of DocHeap_Item
 */
DocHeap_t 
*new_DocHeap(int max_size);

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
DocHeap_insert(DocHeap_t *h, float score, int id);

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
DocHeap_remove_min(DocHeap_t *h);

/*
 *Function: DocHeap_peek_min
 *------------------------------
 * find the score with min id
 * @param: h--> heap
 * return: score with min id
 */
int 
DocHeap_peek_min(DocHeap_t *h);

/*
 *Function: DocHeap_peek_id
 *------------------------------
 * find min id
 * @param: h--> DocHeap
 * return: min id
 */
float 
DocHeap_peek_key(DocHeap_t *h);

/*
 *Function: free_DocHeap
 *------------------------------
 * free all pointers in DocHeap
 * @param: h--> DocHeap
 * return: none
 */
void 
free_DocHeap(DocHeap_t *h);

/*
 *Function: DocHeap_de_queue_descending
 *------------------------------
 * print out all the id, score pair in ascending order.
 * @param: h--> DocHeap
 * return: none
 */
void 
DocHeap_de_queue_descending(DocHeap_t *h);