/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:21:27 by dmoraled          #+#    #+#             */
/*   Updated: 2024/12/10 09:13:41 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include "libft/libft.h"

typedef struct s_item
{
	int	value;
	int	index;
}	t_item;

void	lst_item_free(void *content);
t_list	*parse_input(int argc, char **argv);

void	pb(t_list **a, t_list **b);
void	pa(t_list **a, t_list **b);
void	rs(t_list **lst);

#endif
