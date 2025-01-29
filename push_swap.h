/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:21:27 by dmoraled          #+#    #+#             */
/*   Updated: 2025/01/29 11:22:49 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include "libft/libft.h"

typedef struct s_item
{
	// t_list *target;
	int	value;
	int	index;
}	t_item;

void	lst_item_free(void *content);
int		lst_item_less(void *a_content, void *b_content);
t_list	*parse_input(int argc, char **argv);

void	sort_trivial(t_list **a);
void	sort_complex(t_list **a, t_list **b);

void	pb(t_list **a, t_list **b);
void	pa(t_list **a, t_list **b);
void	rs(t_list **lst, char stack);
void	rrs(t_list **lst, char stack);
void	ss(t_list **lst, char stack);

#endif
