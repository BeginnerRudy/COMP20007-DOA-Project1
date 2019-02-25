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
    float key;
    int data;
}Heap_Item_t;

// Array based min heap structure
// max_size records heap's allocated memory space
// curr_size records #Heap items stored in min heap currently   
typedef struct{
    Heap_Item_t *heap;
    int max_size;
    int curr_size;
}Heap_t;

// Store key, data ({float, int}) information
typedef struct{
    float score;
    int id;
    void* queryPtr;
}DocHeap_Item_t;

// Array based min heap structure
// max_size records heap's allocated memory space
// curr_size records #Heap items stored in min heap currently
typedef struct{
    DocHeap_Item_t *DocHeap;
    int max_size;
    int curr_size;
}DocHeap_t;

/* * * * *
 * FUNCTION PROTOTYPES
 */

/*--------------------------------------------------------*/

/*
 *Function: heap_swap
 *------------------------------
 * Swap two element in the array
 * @param: h1-->Heap_Item_t 1
 *         h2-->Heap_Item_t 2
 * return: none
 */
void heap_swap(Heap_Item_t *h1, Heap_Item_t *h2);

/*
 *Function: siftup
 *------------------------------
 * Sift the Heap_Item_t up to the right position
 * @param: h--> heap
 *         i--> index of Heap_Item_t
 * return: none
 */
void siftup(Heap_t *h, int i);

/*
 *Function: siftdown
 *------------------------------
 * Sift the Heap_Item_t down to the right position
 * @param: h--> heap
 *         i--> index of Heap_Item_t
 * return: none
 */
void siftdown(Heap_t *h, int i);

/*
 *Function: min_child
 *------------------------------
 * find the smaller child's index
 * @param: h--> heap
 *         i--> index of Heap_Item_t
 * return: smaller child's index or NOCHILD
 */
int min_child(Heap_t *h, int i);

/*
 *Function: new_heap
 *------------------------------
 * Create a new heap and allocte max_size memory space - 
 * - for the array inside it
 * @param: max_size --> the size of array of Heap_Item
 * return: a allocated Heap_t* with max_size of array of Heap_Item
 */
Heap_t *new_heap(int max_size);

/*
 *Function: heap_insert
 *------------------------------
 * insert a new Heap_Item to min heap
 * @param: h--> heap
 *         key --> float number
 *         data --> int number
 * return: none
 */
void heap_insert(Heap_t *h, float key, int data);

/*
 *Function: heap_remove_min
 *------------------------------
 * Remove the HeapItem with min key 
 * then swap last HeapItem to first position
 * to find new min of the heap.
 * @param: h--> heap
 * return: the data with minimum key
 */
int heap_remove_min(Heap_t *h);

/*
 *Function: heap_peek_min
 *------------------------------
 * find the data with min key
 * @param: h--> heap
 * return: data with min key
 */
int heap_peek_min(Heap_t *h);

/*
 *Function: heap_peek_key
 *------------------------------
 * find min key
 * @param: h--> heap
 * return: min key
 */
float heap_peek_key(Heap_t *h);

/*
 *Function: free_heap
 *------------------------------
 * free all pointers in heap
 * @param: h--> heap
 * return: none
 */
void free_heap(Heap_t *h);  

/*
 *Function: de_queue
 *------------------------------
 * print out all the data,key pair in ascending order.
 * @param: h--> heap
 * return: none
 */
void 
de_queue_descending(Heap_t *h);

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
DocHeap_insert(DocHeap_t *h, float score, int id, void* queryPtr);

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