/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:21:27 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/17 12:59:04 by dmoraled         ###   ########.fr       */
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
t_list	*lst_min_value(t_list *lst, int threshold);
t_list	*parse_input(int argc, char **argv);

void	print_stack(t_list *a, t_list *b);

void	parallel_move(t_list **lsts[2], t_list *f, char tname, char fname);

void	fill_costs(t_list *to, t_list *from);

void	fill_targets(t_list *to, t_list *from, int (*l)(void *, void *));
t_list	*cheapest_target(t_list *b, t_list *allowed_start, int allowed_size);

void	sort_trivial(t_list **a, char name);
void	sort_small(t_list **a, t_list **b);
void	reverse_trivial(t_list **a, char name);

void	sort_complex_single(t_list **a, t_list **b);
void	sort_complex(t_list **a, t_list **b);

int		lst_item_less(void *a, void *b);
int		lst_item_more(void *a, void *b);
int		is_sorted(t_list *lst);

void	pb(t_list **a, t_list **b);
void	pa(t_list **a, t_list **b);
void	rs(t_list **lst, char stack);
void	rrs(t_list **lst, char stack);
void	rrr(t_list **a, t_list **b);
void	rr(t_list **a, t_list **b);
void	ss(t_list **lst, char stack);

#endif
