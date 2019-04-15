/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfielder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 22:34:50 by gfielder          #+#    #+#             */
/*   Updated: 2019/04/15 15:51:28 by gfielder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_unit_tester_args		*failsafe_args_recover;


static void		init_args(t_unit_tester_args *args, char *pattern,
					int from, int to, t_unit_tester_func f)
{
	args->pattern = pattern;
	args->from = from;
	args->to = to;
	args->current = from;
	args->num_fails = 0;
	args->num_run = 0;
	args->run = f;
	//Back up stdout
	args->fd_stdout_dup = dup(fileno(stdout));
}

static void		unit_testing(int argc, char **argv)
{
	t_unit_tester_args		args;
	failsafe_args_recover = &args;
	int from, to;

	if (argc > 1)
	{
		if (DEBUG) printf("argv[1] = \"%s\"\n", argv[1]);
		if (!(argv[1][0] >= '0' && argv[1][0] <= '9'))
		{
			//Search pattern
			if (DEBUG) printf("Searching tests with pattern: \"%s\"\n", argv[1]);
			init_args(&args, argv[1], 0, 2147483647, run_search_tests);
			run_search_tests(&args);
		}
		else
		{
			from = atoi(argv[1]);
			if (argc > 2)
				to = atoi(argv[2]);
			else
				to = 2147483647;
			if (DEBUG) printf("Running tests on range [%i, %i]\n", from, to);
			init_args(&args, NULL, from, to, run_test_range);
			run_test_range(&args);
		}
	}
	else
	{
		//No arguments. Run all tests
		if (DEBUG) printf("Running All Tests...\n");
		from = 0;
		to = 2147483647;
		init_args(&args, NULL, from, to, run_test_range);
		run_test_range(&args);
	}
}

int main(int argc, char **argv)
{
	unit_testing(argc, argv);
	return (0);
}
