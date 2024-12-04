/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:35:38 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/04 11:13:09 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	lst_less(t_list *a, t_list *b)
{
	return (*(int *)(a->content) < *(int *)(b->content));
}

int	lst_is_sorted(t_list *lst, int (*less)(t_list *, t_list *))
{
	if (!lst)
		return (1);
	while (lst->next)
	{
		if (!less(lst, lst->next))
			return (0);
		lst = lst->next;
	}
	return (1);
}

void	lst_bubble(t_list *lst, int (*less)(t_list *, t_list *))
{
	t_list	*l;
	void	*tmp;

	if (!lst)
		return ;
	while (1)
	{
		if (lst_is_sorted(lst, less))
			return ;
		l = lst;
		while (l->next)
		{
			if (!less(l, l->next))
			{
				tmp = l->next->content;
				l->next->content = l->content;
				l->content = tmp;
			}
			l = l->next;
		}
	}
}

void	lst_print(void *content)
{
	ft_printf("%i ", *(int *)content);
}

int	main(int argc, char **argv)
{
	t_list	*lst;
	int		*n;

	lst = 0;
	n = 0;
	if (argc <= 1)
	{
		ft_printf("no args : (\n");
		return (1);
	}
	while (argc > 1)
	{
		n = ft_calloc(1, sizeof(int));
		if (!n)
			return (1);
		*n = ft_atoi(argv[argc - 1]);
		ft_lstadd_front(&lst, ft_lstnew(n));
		--argc;
	}
	ft_printf("original: ");
	ft_lstiter(lst, lst_print);
	ft_printf("\nsorted: ");
	lst_bubble(lst, lst_less);
	ft_lstiter(lst, lst_print);
	ft_lstclear(&lst, free);
}
