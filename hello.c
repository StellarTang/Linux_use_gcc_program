#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


typedef struct onedirectional_linked_list
{
	int data;
	struct onedirectional_linked_list *next;
} node_t;

node_t * create_node(int data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

void addTail(node_t *head, int data)
{
	node_t *new_node = create_node(data);
	node_t *current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_node;
}

void addHead(node_t **head, int data)
{
	node_t *new_node = create_node(data);
	new_node->next = *head;
	*head = new_node;
}

void changeData(node_t *head, int old_data, int new_data)
{
	node_t *current = head;
	while (current != NULL)
	{
		if (current->data == old_data)
		{
			current->data = new_data;
			return;
		}
		current = current->next;
	}
}

void deleteNode(node_t **head, int data)
{
	node_t *current = *head;
	node_t *prev = NULL;

	while (current != NULL && current->data != data)
	{
		prev = current;
		current = current->next;
	}

	if (current == NULL) // Data not found
		return;

	if (prev == NULL) // Deleting the head node
	{
		*head = current->next;
	}
	else
	{
		prev->next = current->next;
	}

	free(current);
}


void free_list(node_t **head)
{
	node_t *current = *head;
	while (current != NULL)
	{
		node_t *temp = current;
		current = current->next;
		free(temp);
	}
	*head = NULL;
}

void print_list(node_t *head)
{
	node_t *current = head;
	while (current != NULL)
	{
		printf("%d -> ", current->data);
		current = current->next;
	}
	printf("NULL\n");
}


void test_onedirectional_linked_list()
{
	node_t *head = NULL;
	print_list(head);
	addHead(&head, 1);
	print_list(head);
	
	addTail(head, 2);
	print_list(head);
	addTail(head, 3);
	print_list(head);
	addHead(&head, 4);
	print_list(head);


	changeData(head, 2, 5);
	print_list(head);

	deleteNode(&head, 3);
	print_list(head);

	free_list(&head);
	print_list(head); // This will print "NULL" since the list has been freed
}



typedef struct bidirectional_linked_list
{
	int data;
	struct bidirectional_linked_list *next;
	struct bidirectional_linked_list *prev;
} node_bi_t;

node_bi_t * create_node_bi(int data)
{
	node_bi_t *new_node = (node_bi_t *)malloc(sizeof(node_bi_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}


void addTail_bi(node_bi_t *head, int data)
{
	node_bi_t *new_node = create_node_bi(data);
	node_bi_t *current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_node;
	new_node->prev = current;
}


void addHead_bi(node_bi_t **head, int data)
{
	node_bi_t *new_node = create_node_bi(data);
	new_node->next = *head;
	if (*head != NULL)
	{
		(*head)->prev = new_node;
	}
	*head = new_node;
}

void changeData_bi(node_bi_t *head, int old_data, int new_data)
{
	node_bi_t *current = head;
	while (current != NULL)
	{
		if (current->data == old_data)
		{
			current->data = new_data;
			return;
		}
		current = current->next;
	}
}

void deleteNode_bi(node_bi_t **head, int data)
{
	node_bi_t *current = *head;

	while (current != NULL && current->data != data)
	{
		current = current->next;
	}

	if (current == NULL) // Data not found
		return;

	if (current->prev != NULL) // Not the head node
	{
		current->prev->next = current->next;
	}
	else // Deleting the head node
	{
		*head = current->next;
	}

	if (current->next != NULL) // Not the tail node
	{
		current->next->prev = current->prev;
	}

	free(current);
}

void print_list_bi(node_bi_t *head)
{
	node_bi_t *current = head;
	while (current != NULL)
	{
		printf("%d <-> ", current->data);
		current = current->next;
	}
	printf("NULL\n");
}

void test_bidirectional_linked_list()
{
	node_bi_t *head = NULL;
	print_list_bi(head);
	addHead_bi(&head, 1);
	print_list_bi(head);
	
	addTail_bi(head, 2);
	print_list_bi(head);
	addTail_bi(head, 3);
	print_list_bi(head);
	addHead_bi(&head, 4);
	print_list_bi(head);

	changeData_bi(head, 2, 5);
	print_list_bi(head);
}






int main(void)
{
	printf("Hello world !\n");

	for(int i = 0; i < 5; i++)
    	{
        	printf("count = %d\n", i);
    	}

	test_onedirectional_linked_list();
	test_bidirectional_linked_list();

	return 0;
}



