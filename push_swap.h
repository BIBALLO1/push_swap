/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:21:27 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/01 13:31:25 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include "libft/libft.h"

# define DIRECTION_UP 0
# define DIRECTION_DOWN 1

typedef struct s_item
{
	t_list	*target;
	int		value;
	int		index;
	int		cost;
	char	direction;
	char	target_dir;
}	t_item;

void	lst_item_free(void *content);
int		lst_item_less(void *a_content, void *b_content);
t_list	*parse_input(int argc, char **argv);

void	print_stack(t_list *a, t_list *b);

void	sort_trivial(t_list **a, char name);
void	sort_small(t_list **a, t_list **b);
void	reverse_trivial(t_list **a, char name);

void	sort_complex_single(t_list **a, t_list **b);
void	sort_complex(t_list **a, t_list **b);

void	pb(t_list **a, t_list **b);
void	pa(t_list **a, t_list **b);
void	rs(t_list **lst, char stack);
void	rrs(t_list **lst, char stack);
void	rrr(t_list **a, t_list **b);
void	rr(t_list **a, t_list **b);
void	ss(t_list **lst, char stack);

#endif
