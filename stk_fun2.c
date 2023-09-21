#include "monty.h"

/**
 * fetch_fun - Calls the required function.
 * @func: Pointer to the function that is about to be called. 
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @format: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void fetch_fun(op_func func, char *op, char *val, int ln, int format)
{
        stack_t *node;
        int flag;
        int i;

        flag = 1;
        if (strcmp(op, "push") == 0)
        {
                if (val != NULL && val[0] == '-')
                {
                        val = val + 1;
                        flag = -1;
                }
                if (val == NULL)
                        error_1(5, ln);
                for (i = 0; val[i] != '\0'; i++)
                {
                        if (isdigit(val[i]) == 0)
                                error_1(5, ln);
                }
                node = create_node(atoi(val) * flag);
                if (format == 0)
                        func(&node, ln);
                if (format == 1)
                        add_to_queue(&node, ln);
        }
        else
                func(&head, ln);
}

/**
 * rotl - Rotates the first node of the stack to the bottom.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @ln: Interger representing the line number of of the opcode.
 */
void rotl(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	tmp = *stack;
	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *stack;
	(*stack)->prev = tmp;
	*stack = (*stack)->next;
	(*stack)->prev->next = NULL;
	(*stack)->prev = NULL;
}



/**
 * sub_nodes - Adds the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: Interger representing the line number of of the opcode.
 */
void sub_nodes(stack_t **stack, unsigned int line_number)
{
	int sum;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)

		error_2(8, line_number, "sub");


	(*stack) = (*stack)->next;
	sum = (*stack)->n - (*stack)->prev->n;
	(*stack)->n = sum;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}


/**
 * div_nodes - Adds the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_number: Interger representing the line number of of the opcode.
 */
void div_nodes(stack_t **stack, unsigned int line_number)
{
	int sum;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		error_2(8, line_number, "div");

	if ((*stack)->n == 0)
		error_2(9, line_number);
	(*stack) = (*stack)->next;
	sum = (*stack)->n / (*stack)->prev->n;
	(*stack)->n = sum;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

