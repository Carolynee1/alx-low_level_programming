#include "lists.h"

/**
 * free_listint_safe - frees a linked list
 * @h: pointer to the first node in the linked list
 *
 * Return:the size of the list that was free’d
 */
size_t free_listint_safe(listint_t **h)
{
size_t len = 0;
int dif;
listint_t *tem;

if (!h || !*h)
return (0);

while (*h)
{
dif = *h - (*h)->next;
if (dif > 0)
{
tem = (*h)->next;
free(*h);
*h = tem;
len++;
}
else
{
free(*h);
*h = NULL;
len++;
break;
}
}

*h = NULL;

return (len);
}
