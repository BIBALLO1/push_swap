/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:35:38 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/04 12:39:11 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

void	print_lst_vert(t_list *lst)
{
	while (lst)
	{
		ft_printf("%i\n", ((t_item *)lst->content)->index);
		lst = lst->next;
	}
}

int	main(int argc, char **argv)
{
	t_list	*lst;

	lst = parse_input(argc, argv);
	if (!lst)
		return (1);
	print_lst_vert(lst);
	ft_lstclear(&lst, lst_item_free);
}
