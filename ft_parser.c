#include "minishell.h"

// 기능: lexer에 존재하는 pipe 개수, 리턴: pipe 개수(int)
static int	get_pipe_count(void)
{
	t_lexer	*tmp;
	int		cnt;

	cnt = 0;
	tmp = g_uni.lexer_list;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}

// 기능: parser 생성 및 초기화, 리턴: t_parser
t_parser	*new_parser(void)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser) * 1);
	parser->start = NULL;
	parser->end = NULL;
	parser->fd_in = 0;
	parser->fd_out = 1;
	parser->next = NULL;
	parser->pipe[0] = 0;
	parser->pipe[1] = 0;
	parser->pid = 0;
	return (parser);
}

// 기능: parser_list에 parser 추가, 리턴: void
void	add_parser(t_parser *parser)
{
	t_parser	*temp;

	if (g_uni.parser_list == NULL)
		g_uni.parser_list = parser;
	else
	{
		temp = g_uni.parser_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = parser;
	}
}

// 기능: lexer를 pipe기준으로 나누어 parser에 저장, 리턴: void
void	ft_parser(void)
{
	t_lexer		*cur_lexer;
	t_parser	*parser;
	int			parser_cnt;
	int			i;

	cur_lexer = g_uni.lexer_list;
	if (cur_lexer == 0)
		return ;
	i = 0;
	parser_cnt = get_pipe_count() + 1;
	while (++i <= parser_cnt)
	{
		parser = new_parser();
		parser->start = cur_lexer;
		if (i == parser_cnt)
			while (cur_lexer->next != NULL)
				cur_lexer = cur_lexer->next;
		else
			while (cur_lexer->next->type != PIPE)
				cur_lexer = cur_lexer->next;
		parser->end = cur_lexer->next;
		if (i != parser_cnt)
			cur_lexer = cur_lexer->next->next; // pipe위치에서 한 번 이동
		add_parser(parser);
	}
}

// 기능: 저장된 parser_list 출력, 리턴: void
void	view_parser_list(void)
{
	t_parser	*viewer;
	t_lexer		*start;
	t_lexer		*end;

	viewer = g_uni.parser_list;
	while (viewer != NULL)
	{
		start = viewer->start;
		end = viewer->end;
		while (start != end)
		{
			printf("%s %d %d\n", start->str, start->type, start->quote);
			start = start->next;
		}
		printf("%s %d %d\n", end->str, end->type, end->quote);
		viewer = viewer->next;
		printf("\n");
	}
}
