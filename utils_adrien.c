#include "ft.h"


t_list	*ft_doubletab_to_list(char **tab)
{
	t_list *head;
	t_list *new;

	if (!tab || !*tab)
		return (NULL);
	head = NULL;
	while (*tab)
	{
		new = ft_lstnew(*tab);
		ft_lstadd_back(&head, new);
		tab++;
	}
	return (head);
}

void	ft_print_str_list(t_list *head)
{
	t_list *tmp;

	tmp = head;
	while (tmp->next)
	{
		printf("%s -->\n", tmp->content);
		tmp = tmp->next;
	}
	printf("NULL||\n");

}

void	ft_free_lst(t_list *head)
{
	t_list *tmp;
	int i;


	if (!head)
		return;
	tmp = head;
	i = 0;
	while (tmp)
	{
		head = tmp->next;
		free(tmp);
		tmp = head;
		i++;
	}
	printf("node deleted = %d\n", i);
}
