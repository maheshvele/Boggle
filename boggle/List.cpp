#include<stdio.h>
#include "types.h"
#include "List.h"

void ListInit(LinkedList *head)
{
	head->next = head;
	head->prev = head;
}

void ListInsertTail(LinkedList *head, LinkedList *entry)
{
	if (!entry)
		return;

	entry->prev = head->prev;
	entry->next = head;

	(head->prev)->next = entry;
	head->prev = entry;
}

LinkedList *ListFirst(LinkedList *head)
{
	if (head->next == head)
		return NULL;
	return head->next;
}

LinkedList *ListTail(LinkedList *head)
{
	if (head->prev == head)
		return NULL;
	return head->prev;
}

LinkedList *ListNext(LinkedList *head, LinkedList *entry)
{
	if (head->next == head)
		return NULL;
	if (entry == NULL)
		return NULL;
	if (entry->next == head)
		return NULL;
	else
		return (entry->next);
}

int32_t ListGetCnt(LinkedList *head)
{
	int32_t cnt = 0;
	LinkedList *temp = ListFirst(head);

	while (temp)
	{
		cnt++;
		temp = ListNext(head, temp);
	}

	return cnt;
}

LinkedList *ListRemoveHead(LinkedList *head)
{
	LinkedList *temp = ListFirst(head);

	if (temp)
	{
		head->next = temp->next;
		(temp->next)->prev = head;
	}

	return temp;
}

LinkedList *ListRemoveTail(LinkedList *head)
{
	LinkedList *temp = ListTail(head);
	
	if (temp)
	{
		head->prev = temp->prev;
		(temp->prev)->next = head;
	}
	return temp;
}

