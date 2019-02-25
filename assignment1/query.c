/* ... */

#include <stdio.h>
#include "heap.h"
#include "query.h"
#include "list.h"

# define EndOfDocList 999
# define TRUE 1
// see Assignment spec: 'Task 1: Array-based accumulation approach'
void print_array_results(Index *index, int n_results, int n_documents) {
	float documents_array[n_documents];
	for (int i=0; i<n_documents; i++){
		documents_array[i] = 0.0;
	}

	Document * doc;
	Node* node;
	for (int i=0; i<index->num_terms;i++){
		node = index->doclists[i]->head;
		while (node != NULL){
			doc = node->data;
			node = node->next;
			documents_array[doc->id] += doc->score;
		}
	}

	Heap_t *min_heap;
	min_heap = new_heap(n_results);
	// there are enough document to iterate
	if (n_documents>=n_results){
		for (int i=0; i<n_results; i++){
			heap_insert(min_heap, documents_array[i], i);
		}

		for (int i=n_results+1; i<n_documents; i++){
			if (documents_array[i]>min_heap->heap[0].key){
				heap_remove_min(min_heap);
				heap_insert(min_heap, documents_array[i], i);
			}
		}
	}else{// not enough document
		for (int i=0; i<n_documents; i++){
			heap_insert(min_heap, documents_array[i], i);
		}
	}
	de_queue_descending(min_heap);
	free_heap(min_heap);
}

// see Assignment spec: 'Task 2: Priority queue-based multi-way merge approach'
void print_merge_results(Index *index, int n_results) {
	// Initialization
	Heap_t *n_terms_heap;
	DocHeap_t *DocHeap;
	DocHeap_Item_t min_id_doc;
	Document* Doc;
	DocHeap = new_DocHeap(index->num_terms);
	n_terms_heap = new_heap(n_results);
	int id;
	float score;
	Node * next_node;

	// insert first document of each query term into DocHeap
	for (int i=0; i<index->num_terms; i++){
		// Since its the first doc in each doclist it could not be none so append without checking
		Doc = index->doclists[i]->head->data;
		DocHeap_insert(DocHeap, Doc->score, Doc->id, index->doclists[i]->head);// associate with a ptr to the doc itself
	}

	// merge first n_result doc id
	for (int i=0; i<n_results; i++){
		// Initialization
		min_id_doc = DocHeap->DocHeap[0];
		id = min_id_doc.id;
		score = 0.0;
		// Accumulate score for each doc id
		while(id == min_id_doc.id){
			score+=min_id_doc.score;
			// update DocHeap
			DocHeap_remove_min(DocHeap);
			// if the doclist does not reach end, append in.
			next_node = min_id_doc.queryPtr;
			next_node = next_node->next;
			if (next_node!=NULL){
				Doc = next_node->data;
				DocHeap_insert(DocHeap, Doc->score, Doc->id, next_node);
			}
			// update the min id doc
			if (DocHeap->curr_size!=0){
				min_id_doc = DocHeap->DocHeap[0];
			}else{
				break;
			}
		}
		// update top k heap
		heap_insert(n_terms_heap, score, id);
	}

	//merge and use top k selection for the rest of doclists
	// This while loop is not good but it will stop if we check all the doclists
	while(TRUE){
		// update the min id doc and initialize
			if (DocHeap->curr_size!=0){
				min_id_doc = DocHeap->DocHeap[0];
				id = min_id_doc.id;
				score = 0.0;
			}else{
				break;
			}
		// Accumulate score for each doc id
		while(id == min_id_doc.id){
			score+=min_id_doc.score;
			// update DocHeap
			DocHeap_remove_min(DocHeap);
			// if the doclist does not reach end, append in.
			next_node = min_id_doc.queryPtr;
			next_node = next_node->next;
			if (next_node!=NULL){
				Doc = next_node->data;
				DocHeap_insert(DocHeap, Doc->score, Doc->id, next_node);
			}
			// update the min id doc
			if (DocHeap->curr_size!=0){
				min_id_doc = DocHeap->DocHeap[0];
			}else{
				break;
			}
		}
		// update top k heap
		if (n_terms_heap->heap[0].key < score){
			heap_remove_min(n_terms_heap);
			heap_insert(n_terms_heap, score, id);
		}
	}

	// display && free
	de_queue_descending(n_terms_heap);
	free_heap(n_terms_heap);
	free_DocHeap(DocHeap);
}
