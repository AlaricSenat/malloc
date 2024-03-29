/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:00:20 by asenat            #+#    #+#             */
/*   Updated: 2018/09/07 15:25:44 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_H
# define ALGORITHM_H

# include "ft_malloc/malloc_data.h"

t_block	*do_malloc(t_block_type type, size_t size);
t_block	*alloc_block(t_block_type type, t_block **it, size_t size);
t_block	*resize_block(t_block *block, size_t size);

int		search_in_area(t_area *area,
		const char *adr, t_block_location *result);
int		search_in_areas(const void *adr, t_block_location *result);

void	defrag_around_and_free(t_block_location *location);
int		search_address(const void *ptr, t_block_location *ret);
void	free_location(t_block_location *locations);

#endif
