typedef struct LinkedList{

	struct LinkedList *next;
	struct LinkedList *prev;
}LinkedList;

void ListInit(LinkedList *head);
void ListInsertTail(LinkedList *head, LinkedList *entry);
LinkedList *ListFirst(LinkedList *head);
LinkedList *ListTail(LinkedList *head);
LinkedList *ListNext(LinkedList *head, LinkedList *entry);
int32_t ListGetCnt(LinkedList *head);
LinkedList *ListRemoveHead(LinkedList *head);
LinkedList *ListRemoveTail(LinkedList *head);
