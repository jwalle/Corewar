#include "corewar.h"

void	*get_next_proc(void)
{
	return (NULL);
}

void	*add_proc(t_proc *head, unsigned char *program_counter, int id)
{
	t_proc	*new;
	int		i;

	(void)head;
	i = 0;
	new = (t_proc *)malloc(sizeof(t_proc));
	if (!new)
		return(0); // TODO : HANDLE ERROR
	new->reg = (void *)malloc(sizeof(void *));
	while (i < REG_NUMBER)
	{
		new->reg[i] = (int)malloc(REG_SIZE + 1);		//(void* !?? uns_char*)
		// ft_bzero((char *)new->reg[i], REG_SIZE + 1);
		i++;
	}
	new->reg[0] = id;
	new->pc = program_counter;
	new->carry = 1;
	new->next = get_next_proc();
	return (new);
}