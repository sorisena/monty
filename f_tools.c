#include "monty.h"

/**
 * add_to_stack - Adds a node to the stack.
 * @new_node: Pointer to the new node.
 * @ln: Interger representing the line number of of the opcode.
 */
void add_to_stack(stack_t **new_node, __attribute__((unused))unsigned int ln)
{
        stack_t *tmp;

        if (new_node == NULL || *new_node == NULL)
                exit(EXIT_FAILURE);
        if (head == NULL)
        {
                head = *new_node;
                return;
        }
        tmp = head;
        head = *new_node;
        head->next = tmp;
        tmp->prev = head;
}


/**
 * r_file - reads a file
 * @fd: pointer to file descriptor
 * Return: void
 */

void r_file(FILE *fd)
{
	int line_number, format = 0;
	char *buffer = NULL;
	size_t len = 0;

	for (line_number = 1; getline(&buffer, &len, fd) != -1; line_number++)
	{
		format = parse_line(buffer, line_number, format);
	}
	free(buffer);
}

/**
 * pop_top - Adds a node to the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: Interger representing the line number of of the opcode.
 */
void pop_top(stack_t **stack, unsigned int line_number)
{
        stack_t *tmp;

        if (stack == NULL || *stack == NULL)
                error_2(7, line_number);

        tmp = *stack;
        *stack = tmp->next;
        if (*stack != NULL)
                (*stack)->prev = NULL;
        free(tmp);
}


/**
 * find_func - find the appropriate function for the opcode
 * @opcode: opcode
 * @value: argument of opcode
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * @ln: line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void find_func(char *opcode, char *value, int ln, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", add_to_stack},
		{"pall", display_stack},
		{"pint", out_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", display_char},
		{"pstr", display_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			fetch_fun(func_list[i].f, opcode, value, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		error_1(3, ln, opcode);
}

/**
 * swap_nodes - Swaps the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: Interger representing the line number of of the opcode.
 */
void swap_nodes(stack_t **stack, unsigned int line_number)
{
        stack_t *tmp;

        if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
                error_2(8, line_number, "swap");
        tmp = (*stack)->next;
        (*stack)->next = tmp->next;
        if (tmp->next != NULL)
                tmp->next->prev = *stack;
        tmp->next = *stack;
        (*stack)->prev = tmp;
        tmp->prev = NULL;
        *stack = tmp;
}

