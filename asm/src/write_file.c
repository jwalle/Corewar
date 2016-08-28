/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/05 06:50:23 by rhoffsch          #+#    #+#             */
/*   Updated: 2016/08/05 06:50:25 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static void		write_bytecodes(t_env *e, int fd)
{
	t_int	*octets;
	t_ins	*ptr;

	ptr = e->ins;
	while (ptr != NULL)
	{
		octets = ptr->done;
		while (octets != NULL)
		{
			write(fd, &(octets->octet[0]), 1);
			octets = octets->next;
		}
		ptr = ptr->next;
	}
}

static void		write_header(t_env *e, int fd)
{
	unsigned int	magic[1];
	unsigned int	prog_size[1];
	unsigned int	tmp;

	magic[0] = e->head.magic;
	tmp = ((char*)magic)[3];
	((char*)magic)[3] = ((char*)magic)[0];
	((char*)magic)[0] = tmp;
	tmp = ((char*)magic)[2];
	((char*)magic)[2] = ((char*)magic)[1];
	((char*)magic)[1] = tmp;
	e->head.magic = magic[0];
	prog_size[0] = e->head.prog_size;
	tmp = ((char*)prog_size)[3];
	((char*)prog_size)[3] = ((char*)prog_size)[0];
	((char*)prog_size)[0] = tmp;
	tmp = ((char*)prog_size)[2];
	((char*)prog_size)[2] = ((char*)prog_size)[1];
	((char*)prog_size)[1] = tmp;
	e->head.prog_size = prog_size[0];
	write(fd, &(e->head), sizeof(t_header));
}

void			write_file(t_env *e, char *filename)
{
	int		fd;
	char	*output;

	fd = ft_strlen(filename);
	if (filename == NULL || fd < 3 \
		|| filename[fd - 2] != '.' || filename[fd - 1] != 's')
		ft_exit("Data corrupt.", DATA_CORRUPT);
	filename[fd - 2] = 0;
	output = ft_strjoin(filename, ".cor");
	ft_putendl(output);
	if ((fd = open(output, O_CREAT | O_WRONLY | O_EXCL, 0666)) == -1)
		ft_exit("Open failed.\n\t-> Output file already exist?", OPENFAIL);
	write_header(e, fd);
	write_bytecodes(e, fd);
	close(fd);
	ft_putstr("\nOutput file: ");
	ft_putendl(output);
}
