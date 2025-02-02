/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoraled <dmoraled@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:59:17 by dmoraled          #+#    #+#             */
/*   Updated: 2025/02/02 18:17:46 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	move_top(t_list **lst, int pos, char dir, char name)
{
	int	size;

	size = ft_lstsize(*lst);
	if (dir == DIRECTION_UP)
	{
		while (pos > 0)
		{
			rs(lst, name);
			--pos;
		}
	}
	else
	{
		while (pos < size)
		{
			rrs(lst, name);
			++pos;
		}
	}
}

void	parallel_move_top(t_list **lsts[2], char dir, int pos[2], char names[2])
{
	int	sizes[2];

	sizes[0] = ft_lstsize(*lsts[0]);
	sizes[1] = ft_lstsize(*lsts[1]);
	if (dir == DIRECTION_UP)
	{
		while (pos[0] > 0 && pos[1] > 0)
		{
			rr(lsts[0], lsts[1]);
			--pos[0];
			--pos[1];
		}
	}
	else
	{
		while (pos[0] < sizes[0] && pos[1] < sizes[1])
		{
			rrr(lsts[0], lsts[1]);
			++pos[0];
			++pos[1];
		}
	}
	move_top(lsts[0], pos[0], dir, names[0]);
	move_top(lsts[1], pos[1], dir, names[1]);
}

void	parallel_move(t_list **lsts[2], t_list *f, char tname, char fname)
{
	char	fdir;
	int		fpos;
	int		tpos;

	fdir = ((t_item *)(f->content))->direction;
	fpos = ft_lstsize(*lsts[0]) - ft_lstsize(f);
	tpos = ft_lstsize(*lsts[1]) - ft_lstsize(((t_item *)(f->content))->target);
	if (fdir == ((t_item *)(f->content))->target_dir)
	{
		parallel_move_top(
			(t_list **[]){lsts[0], lsts[1]},
			fdir,
			(int []){fpos, tpos},
			(char []){fname, tname});
	}
	else
	{
		move_top(lsts[0], fpos, fdir, fname);
		move_top(lsts[1], tpos, !fdir, tname);
	}
}
