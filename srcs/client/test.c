
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_LEN 512

typedef struct			s_circular
{
	int					head;
	int					tail;
	int					len;
	char				buf[MAX_INPUT_LEN + 3];
}						t_circular;

void	circular_push(t_circular *circ, char *received, int size)
{
	while (size)
	{
		circ->buf[circ->tail] = *received++;
		circ->tail = (circ->tail + 1) % MAX_INPUT_LEN;
		size--;
	}
}

bool	search_for_crlf(char *buf, int head, int size)  //(t_circular *circ, int size)
{
	while (size)
	{
		if (buf[head] == 0xd && buf[head + 1] == 0xa)
			return (true);
		head = (head + 1) % MAX_INPUT_LEN;
		size--;
	}
	return (false);
}

void extract_and_update(t_circular *circ, char *final)
{
	int count;

	count = 0;
	while (count < circ->len)
	{
		if (circ->buf[circ->head] == 0xd && circ->buf[circ->head + 1] == 0xa)
		{
			circ->head = (circ->head + 1) % MAX_INPUT_LEN;
			circ->head = (circ->head + 1) % MAX_INPUT_LEN;
			circ->len = (count + 2);
			break ;
		}
		final[count] = circ->buf[circ->head];
		circ->head = (circ->head + 1) % MAX_INPUT_LEN;
		count++;
	}
	final[count] = '\0';
}

int main(void)
{
	int			count= 0;
	t_circular	circ;

	char	buf[MAX_INPUT_LEN + 3] = {0};
	char	command[] = "TEST_A\r\nTEST_B\r\nTEST_C\r\n";

	memset(&circ, 0x0, sizeof(t_circular));
	circ.len = strlen(command);
	circular_push(&circ, command, strlen(command));
	while (search_for_crlf(circ.buf, circ.head, circ.len) == true)
	{
		if (count > 5)
			break ;
		extract_and_update(&circ, buf);

		printf("-> %s\n", buf);

		count++;
	}

	return (0);
}
