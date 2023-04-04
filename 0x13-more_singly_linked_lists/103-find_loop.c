#include "lists.h"

/**
 * find_listint_loop - finds the loop in a linked list
 * @head: linked list to search for
 *
 * Return: The address of the node where the loop starts, or NULL
 */
listint_t *find_listint_loop(listint_t *head)
{
listint_t *weak = head;
listint_t *tough = head;

if (!head)
return (NULL);

while (weak && tough && tough->next)
{
tough = tough->next->next;
weak = weak->next;
if (tough == weak)
{
weak = head;
while (slow != tough)
{
weak = weak->next;
tough = tough->next;
}
return (tough);
}
}

return (NULL);
}
