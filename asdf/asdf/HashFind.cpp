// A C program to show implementation of LRU cache
#include <stdio.h>
#include <stdlib.h>

// 구조체 정의 가장 먼저 하고
typedef struct QNode {
	struct QNode* prev, * next; // 더블 링크드 리스트
	unsigned pageNumber; // 노드에 페이지 넘버 저장
} QNode;

// A Queue (A FIFO collection of Queue Nodes)
typedef struct Queue {
	unsigned count; // Number of filled frames
	unsigned numberOfFrames; // total number of frames
	QNode* front, * rear;
} Queue;

// A hash (Collection of pointers to Queue Nodes)
typedef struct Hash {
	int capacity; // how many pages can be there
	QNode** array; // an array of queue nodes
} Hash;

// A utility function to create a new Queue Node. The queue Node
// will store the given 'pageNumber'
// 노드 생성 함수 먼저 만들어서 만듭니다.
QNode* NewQNode(unsigned pageNumber)
{
	// Allocate memory and assign 'pageNumber'
	QNode* temp = (QNode*)malloc(sizeof(QNode));
	if (temp)
	{
		temp->pageNumber = pageNumber;

		// Initialize prev and next as nullptr

		temp->prev = temp->next = nullptr;
	}

	return temp;
}

// 2. 큐 생성
// The queue can have at most 'numberOfFrames' nodes
Queue* CreateQueue(int numberOfFrames)
{
	Queue* queue = (Queue*)malloc(sizeof(Queue));

	// The queue is empty
	if (queue)
	{
		queue->count = 0;
		queue->front = queue->rear = nullptr;

		// Number of frames that can be stored in memory
		queue->numberOfFrames = numberOfFrames;
	}

	return queue;
}

// 1.해시 생성. 노드 배열
Hash* CreateHash(int capacity)
{
	// Allocate memory for hash
	Hash* hash = (Hash*)malloc(sizeof(Hash));
	if (hash)
	{
		hash->capacity = capacity;

		// Create an array of pointers for refering queue nodes
		hash->array = (QNode**)malloc(hash->capacity * sizeof(QNode*));

		// Initialize all hash entries as empty
		for (int i = 0; i < hash->capacity; ++i)
		{
			hash->array[i] = nullptr;
		}
	}

	return hash;
}

// A function to check if there is slot available in memory
int AreAllFramesFull(Queue* queue)
{
	return queue->count == queue->numberOfFrames;
}

// A utility function to check if queue is empty
int IsQueueEmpty(Queue* queue)
{
	return queue->rear == nullptr;
}

// A utility function to delete a frame from queue
void DeQueue(Queue* queue)
{
	if (IsQueueEmpty(queue))
		return;

	// If this is the only node in list, then change front
	if (queue->front == queue->rear)
		queue->front = nullptr;

	// Change rear and remove the previous rear
	QNode* temp = queue->rear;
	queue->rear = queue->rear->prev;

	if (queue->rear)
		queue->rear->next = nullptr;

	free(temp);

	// decrement the number of full frames by 1
	queue->count--;
}

// A function to add a page with given 'pageNumber' to both queue
// and hash
void Enqueue(Queue* queue, Hash* hash, unsigned pageNumber)
{
	// If all frames are full, remove the page at the rear
	if (AreAllFramesFull(queue)) {
		// remove page from hash
		hash->array[queue->rear->pageNumber] = nullptr;
		DeQueue(queue);
	}

	// Create a new node with given page number,
	// And add the new node to the front of queue
	QNode* temp = NewQNode(pageNumber);
	temp->next = queue->front;

	// If queue is empty, change both front and rear pointers
	if (IsQueueEmpty(queue))
		queue->rear = queue->front = temp;
	else // Else change the front
	{
		queue->front->prev = temp;
		queue->front = temp;
	}

	// Add page entry to hash also
	hash->array[pageNumber] = temp;

	// increment number of full frames
	queue->count++;
}

// This function is called when a page with given 'pageNumber' is referenced
// from cache (or memory). There are two cases:
// 1. Frame is not there in memory, we bring it in memory and add to the front
// of queue
// 2. Frame is there in memory, we move the frame to front of queue
void ReferencePage(Queue* queue, Hash* hash, unsigned pageNumber)
{
	// 해시 테이블에 있는가?
	QNode* reqPage = hash->array[pageNumber];

	// 없다면 새로 넣는다.
	if (reqPage == nullptr)
		Enqueue(queue, hash, pageNumber);

	// 참조 페이지가 첫번째가 아니라면
	else if (reqPage != queue->front) {

		// 첫번째 노드로 등록하자.        
		reqPage->prev->next = reqPage->next;
		if (reqPage->next)
			reqPage->next->prev = reqPage->prev;

		// If the requested page is rear, then change rear
		// as this node will be moved to front
		if (reqPage == queue->rear) {
			queue->rear = reqPage->prev;
			queue->rear->next = nullptr;
		}

		// Put the requested page before current front
		reqPage->next = queue->front;
		reqPage->prev = nullptr;

		// Change prev of current front
		reqPage->next->prev = reqPage;

		// Change front to the requested page
		queue->front = reqPage;
	}
}

void Show(Queue* q)
{
	// Let us print cache frames after the above referenced pages
	QNode* reqPage = q->front;

	while (reqPage != nullptr)
	{
		printf("%d ", reqPage->pageNumber);

		reqPage = reqPage->next;
	}
}

// Driver program to test above functions
int main()
{
	// 4 pages 의 캐시를 만들어 보자.
	Queue* q = CreateQueue(4);

	// 페이지 넘버  10 개
	// referenced are numbered from 0 to 9
	Hash* hash = CreateHash(10);

	int input = 0;
	while (1)
	{
		scanf_s("\t %d", &input);

		if (input < 0 || input > 9)
		{
			printf("wrong page number, input 0 ~ 9\n");
			continue;
		}

		ReferencePage(q, hash, input);
		Show(q);
	}

	return 0;
}
