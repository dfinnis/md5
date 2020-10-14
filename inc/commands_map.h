
#ifndef COMMANDS_MAP_H
# define COMMANDS_MAP_H

# include "commands.h"

const static struct {
	const char	*cmd;
	void		(*func)(char *);
} g_cmd_func_map[] = {
	{ "md5", md5 },
	{ "sha224", sha224 },
	{ "sha256", sha256 },
	{ "sha384", sha384 },
	{ "sha512", sha512 },
	{ "sha512224", sha512224 },
	{ "sha512256", sha512256 },
};

#endif
