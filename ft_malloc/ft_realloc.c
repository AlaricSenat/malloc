/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat </var/spool/mail/asenat>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 19:54:38 by asenat            #+#    #+#             */
/*   Updated: 2018/08/07 22:25:02 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc/ft_malloc.h"

#include "ft_malloc/algorithm.h"
#include "utils/utils.h"
#include "libft/memory/memory.h"

static void	*free_and_malloc(void *ptr, size_t size)
{
	ft_free(ptr);
	return (ft_malloc(size));
}

static int is_next_enough(const t_block_location *locations,
		size_t size)
{
	t_block*	next;
	size_t		total_size;

	next = (t_block*)((char*)locations->loc +
			round_size(locations->type, locations->loc->size));
	if (!is_in_free_list(next, g_areas[locations->type].free_blocks))
		return (0);
	total_size = round_size(locations->type,
				locations->loc->size + next->size);
	return (total_size == size || total_size
			>= round_size(locations->type, size + sizeof(t_block) + 1));
}

static void	*resize_with_next(t_block_location *locations,
		size_t size)
{
	t_block 	*next;
	t_block 	*new_next;
	t_block		*curr;
	size_t		r_size;
	size_t		size_needed;

	r_size = round_size(locations->type, size);
	curr = locations->loc;
	next = (t_block*)((char*)locations->loc +
			round_size(locations->type, locations->loc->size));
	size_needed = r_size - round_size(locations->type, curr->size);
 	curr->size = size;
	if (size_needed < next->size)
	{
		new_next = (t_block*)((char*)next + size_needed);
		new_next->next_free = next->next_free;
		new_next->size = next->size - size_needed;
		next->next_free = new_next;	
	}
	if (locations->prev_free)
		locations->prev_free->next_free = next->next_free;
	else
		g_areas[locations->type].free_blocks->next_free = next->next_free;  
	return (locations->loc);
}

void	*ft_realloc(void *ptr, size_t size)
{
	t_block_location locations;

	if (!size)
		return (NULL);
	ft_bzero(&locations, sizeof(locations));
	if (!search_address(ptr, &locations))
		return (ft_malloc(size));
	if (locations.type != get_block_type(locations.loc->size - sizeof(t_block)))
		return (free_and_malloc(ptr, size));
	size += sizeof(t_block);
	if (round_size(locations.type, locations.loc->size) >= size)
	{
		locations.loc->size = size;
		return (locations.loc);
	}
	else if (is_next_enough(&locations, round_size(locations.type, size)))
		return (resize_with_next(&locations, size));
	return (free_and_malloc(ptr, size - sizeof(t_block)));
}
