/*
 * Copyright (c) 1993 by David I. Bell
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
 * Stand-alone shell for system maintainance for Linux.
 * This program should NOT be built using shared libraries.
 *
 * 1.1.1, 	hacked to re-allow cmd line invocation of script file
 *		Pat Adamo, padamo@unix.asb.com
 */

#include "sash.h"

#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>

static const char enoent_msg[] = "Bad command or file name";
static const char unkerr_msg[] = "Unknown error!";

extern int intflag;

extern void do_test();

typedef struct {
	char	name[10];
	char	usage[30];
	void	(*func)();
	int	minargs;
	int	maxargs;
} CMDTAB;


CMDTAB	cmdtab[] = {
	"cat",		"filename ...",
	do_cat,		2,	MAXARGS,

	"cd",		"[dirname]",
	do_cd,		1,	2,

	"chgrp",	"gid filename ...",
	do_chgrp,	3,	MAXARGS,

	"chmod",	"mode filename ...",
	do_chmod,	3,	MAXARGS,

	"chown",	"uid filename ...",
	do_chown,	3,	MAXARGS,

	"cmp",		"filename1 filename2",
	do_cmp,		3,	3,

	"cp",		"srcname ... destname",
	do_cp,		3,	MAXARGS,

	"date",		"date [MMDDhhmm[YYYY]]",
	do_date,	1,	2,

	"df",		"[file-system]",
	do_df,		1,	2,

	"echo",		"[args] ...",
	do_echo,	1,	MAXARGS,

	"exec",		"filename [args]",
	do_exec,	2,	MAXARGS,

	"exit",		"",
	do_exit,	1,	1,

	"free",		"",
	do_free,	1,	1,

	"help",		"",
	do_help,	1,	MAXARGS,

	"hexdump",	"[-s pos] filename",
	do_hexdump,	1,	4,

	"hostname",	"[hostname]",
	do_hostname,	1,	2,

	"kill",		"[-sig] pid ...",
	do_kill,	2,	MAXARGS,

	"ln",		"[-s] srcname ... destname",
	do_ln,		3,	MAXARGS,

	"ls",		"[-lidC] filename ...",
	do_ls,		1,	MAXARGS,

	"mkdir",	"dirname ...",
	do_mkdir,	2,	MAXARGS,

	"mknod",	"filename type major minor",
	do_mknod,	5,	5,

	"more",		"filename ...",
	do_more,	2,	MAXARGS,

	"mount",	"[-t type] devname dirname",
	do_mount,	3,	MAXARGS,

	"mv",		"srcname ... destname",
	do_mv,		3,	MAXARGS,

	"pid",		"",
	do_pid,		1,	1,

	"printenv",	"[name]",
	do_printenv,	1,	2,

	"ps",		"",
	do_ps,		1,	MAXARGS,

	"pwd",		"",
	do_pwd,		1,	1,

	"quit",		"",
	do_exit,	1,	1,

	"rm",		"filename ...",
	do_rm,		2,	MAXARGS,

	"rmdir",	"dirname ...",
	do_rmdir,	2,	MAXARGS,

	"setenv",	"name value",
	do_setenv,	3,	3,

	"sleep",	"seconds",
	do_sleep,	1,	2,

	"source",	"filename",
	do_source,	2,	2,

	"sync",		"",
	do_sync,	1,	1,

	"touch",	"filename ...",
	do_touch,	2,	MAXARGS,

	"umask",	"[mask]",
	do_umask,	1,	2,

	"umount",	"filename",
	do_umount,	2,	2,

	0,		0,			0,
	0,		0
};


typedef struct {
	char	*name;
	char	*value;
} ALIAS;


static	ALIAS	*aliastable;
static	int	aliascount;

static	FILE	*sourcefiles[MAXSOURCE];
static	int	sourcecount;

volatile static	BOOL	intcrlf = TRUE;


static	void	catchint();
static	void	catchquit();
static	void	catchchild();
static	void	readfile();
static	void	command();
static	void	runcmd();
static	void	showprompt();
static	BOOL	trybuiltin();
static	BOOL	command_in_path();
static	ALIAS	*findalias();

extern char ** environ;

char	buf[CMDLEN];
int exit_code = 0;

int main(int argc, char *argv[])
	int	argc;
	char	**argv;
	char	*env[];
{
	struct sigaction act;
	char	*cp;
	int dofile = 0;

	if ((argc > 1) && !strcmp(argv[1], "-c")) {
		/* We are that fancy a shell */
		buf[0] = '\0';
		for (dofile = 2; dofile < argc; dofile++) {
			strncat(buf, argv[dofile], sizeof(buf));
			if (dofile + 1 < argc)
				strncat(buf, " ", sizeof(buf));
		}
		command(buf, FALSE);
		exit(exit_code);
	}

	if ((argc > 1) && strcmp(argv[1], "-t"))
		{
		dofile++;
		printf("Shell invoked to run file: %s\n",argv[1]);
		}
	else
		printf("\nSash command shell (OpenADK edition)\n");
	fflush(stdout);

	signal(SIGINT, catchint);
	signal(SIGQUIT, catchquit);

	memset(&act, 0, sizeof(act));
	act.sa_handler = catchchild;
	act.sa_flags = SA_RESTART;
	sigaction(SIGCHLD, &act, NULL);

	if (getenv("PATH") == NULL)
		putenv("PATH=/bin:/usr/bin:/sbin:/usr/sbin");

	readfile(dofile ? argv[1] : NULL);
	exit(exit_code);
}


/*
 * Read commands from the specified file.
 * A null name pointer indicates to read from stdin.
 */
static void
readfile(name)
	char	*name;
{
	FILE	*fp;
	int	cc;
	BOOL	ttyflag;
	char	*ptr;

	if (sourcecount >= MAXSOURCE) {
		fprintf(stderr, "Too many source files\n");
		return;
	}

	fp = stdin;
	if (name) {
		fp = fopen(name, "r");
		if (fp == NULL) {
			perror(name);
			return;
		}
	}
	sourcefiles[sourcecount++] = fp;

	ttyflag = isatty(fileno(fp));

	while (TRUE) {
		fflush(stdout);
		if (fp == stdin) //using terminal, so show prompt
			showprompt();

		if (intflag && !ttyflag && (fp != stdin)) {
			fclose(fp);
			sourcecount--;
			return;
		}

		if (fgets(buf, CMDLEN - 1, fp) == NULL) {
			if (ferror(fp) && (errno == EINTR)) {
				clearerr(fp);
				continue;
			}
			break;
		}

		cc = strlen(buf);

		while ((cc > 0) && isspace(buf[cc - 1]))
			cc--;
		buf[cc] = '\0';
		/* remove leading spaces and look for a '#' */
		ptr = &buf[0];
		while (*ptr == ' ') {
			ptr++;
		}
		if (*ptr != '#') {
			if (fp != stdin) {
				//taking commands from file - echo
				printf("Command: %s\n",buf);
			} //end if (fp != stdin)

			command(buf, fp == stdin);
		}
	}



	if (ferror(fp)) {
		perror("Reading command line");
		if (fp == stdin)
			exit(1);
	}

	clearerr(fp);
	if (fp != stdin) {
		fclose(fp);
		printf("Execution Finished, Exiting\n");
	}

	sourcecount--;
}


/*
 * Parse and execute one null-terminated command line string.
 * This breaks the command line up into words, checks to see if the
 * command is an alias, and expands wildcards.
 */
static void
command(cmd, do_history)
	int do_history;
	char	*cmd;
{
	ALIAS	*alias;
	char	**argv;
	int	argc;
	int 	bg;
	char   *c;

	char last_exit_code[10];

	sprintf(last_exit_code, "%d", exit_code);

	intflag = FALSE;
	exit_code = 0;

	freechunks();

	while (isblank(*cmd))
		cmd++;

	if (do_history) {
		int i;
		static char *history[HISTORY_SIZE];

		if (*cmd == '!') {
			if (cmd[1] == '!')
				i = 0;
			else {
				i = atoi(cmd+1) - 1;
				if (i < 0 || i >= HISTORY_SIZE) {
					printf("%s: Out of range\n", cmd);
					return;
				}
			}
			if (history[i] == NULL) {
				printf("%s: Null entry\n", cmd);
				return;
			}
			strcpy(cmd, history[i]);
		} else if (*cmd == 'h' && cmd[1] == '\0') {
			for (i=0; i<HISTORY_SIZE; i++) {
				if (history[i] != NULL)
					printf("%2d: %s\n", i+1, history[i]);
			}
			return;
		} else if (*cmd != '\0') {
			if (history[HISTORY_SIZE-1] != NULL)
				free(history[HISTORY_SIZE-1]);
			for (i=HISTORY_SIZE-1; i>0; i--)
				history[i] = history[i-1];
			history[0] = strdup(cmd);
		}
	}
	if (c = strchr(cmd, '&')) {
		*c = '\0';
		bg = 1;
	} else
		bg = 0;

	/* Set the last exit code */
	setenv("?", last_exit_code, 1);

	if ((cmd = expandenvvar(cmd)) == NULL)
		return;

	if ((*cmd == '\0') || !makeargs(cmd, &argc, &argv))
		return;

	/*
	 * Search for the command in the alias table.
	 * If it is found, then replace the command name with
	 * the alias, and append any other arguments to it.
	 */
	alias = findalias(argv[0]);
	if (alias) {
		cmd = buf;
		strcpy(cmd, alias->value);

		while (--argc > 0) {
			strcat(cmd, " ");
			strcat(cmd, *++argv);
		}

		if (!makeargs(cmd, &argc, &argv))
			return;
	}

	/*
	 * BASH-style variable setting
	 */
	if (argc == 1) {
		c = index(argv[0], '=');
		if (c > argv[0]) {
			*c++ = '\0';
			setenv(argv[0], c, 1);
			return;
		}
	}

	/*
	 * Now look for the command in the builtin table, and execute
	 * the command if found.
	 */
	if (!strcmp(argv[0], "builtin")) {
		--argc;
		++argv;
		if (!*argv || !trybuiltin(argc, argv))
			fprintf(stderr, "%s: %s\n", argv[-1], enoent_msg);
		return;
	} else if (!command_in_path(argv[0]) && trybuiltin(argc, argv))
		return;

	/*
	 * Not found, run the program along the PATH list.
	 */
	runcmd(cmd, bg, argc, argv);
}


/*
 * return true if we find this command in our
 * path.
 */
static BOOL
command_in_path(char *cmd)
{
	struct stat	stat_buf;

	if (strchr(cmd, '/') == 0) {
		char	* path;
		static char	path_copy[PATHLEN];

		/* Search path for binary */
		for (path = getenv("PATH"); path && *path; ) {
			char * p2;

			strcpy(path_copy, path);
			if (p2 = strchr(path_copy, ':')) {
				*p2 = '\0';
			}

			if (strlen(path_copy))
				strcat(path_copy, "/");
			strcat(path_copy, cmd);

			if (!stat(path_copy, &stat_buf) && (stat_buf.st_mode & 0111))
				return(TRUE);

			p2 = strchr(path, ':');
			if (p2)
				path = p2 + 1;
			else
				path = 0;
		}
	} else if (!stat(cmd, &stat_buf) && (stat_buf.st_mode & 0111))
		return(TRUE);
	return(FALSE);
}


/*
 * Try to execute a built-in command.
 * Returns TRUE if the command is a built in, whether or not the
 * command succeeds.  Returns FALSE if this is not a built-in command.
 */
static BOOL
trybuiltin(argc, argv)
	int	argc;
	char	**argv;
{
	CMDTAB	*cmdptr;
	int	oac;
	int	newargc;
	int	matches;
	int	i;
	char	*newargv[MAXARGS];
	char	*nametable[MAXARGS];

	cmdptr = cmdtab - 1;
	do {
		cmdptr++;
		if (cmdptr->name[0] == 0)
			return FALSE;

	} while (strcmp(argv[0], cmdptr->name));

	/*
	 * Give a usage string if the number of arguments is too large
	 * or too small.
	 */
	if ((argc < cmdptr->minargs) || (argc > cmdptr->maxargs)) {
		fprintf(stderr, "usage: %s %s\n",
			cmdptr->name, cmdptr->usage);
		fflush(stderr);

		return TRUE;
	}

	/*
	 * Now for each command argument, see if it is a wildcard, and if
	 * so, replace the argument with the list of matching filenames.
	 */
	newargv[0] = argv[0];
	newargc = 1;
	oac = 0;

	while (++oac < argc) {
		if (argv[oac][0] == '"' || argv[oac][0] == '\'') {
			argv[oac]++;
			matches = 0;
		}
		else {
			matches = expandwildcards(argv[oac], MAXARGS, nametable);
			if (matches < 0)
				return TRUE;
		}

		if ((newargc + matches) >= MAXARGS) {
			fprintf(stderr, "Too many arguments\n");
			return TRUE;
		}

		if (matches == 0)
			newargv[newargc++] = argv[oac];

		for (i = 0; i < matches; i++)
			newargv[newargc++] = nametable[i];
	}

	(*cmdptr->func)(newargc, newargv);

	return TRUE;
}

/*
 * Execute the specified command.
 */
static void
runcmd(cmd, bg, argc, argv)
	char	*cmd;
	int	bg;
	int	argc;
	char	**argv;
{
	register char *	cp;
	int		pid;
	int		status;
	int oac;
	int newargc;
	int matches;
	int i;
	char	*newargv[MAXARGS];
	char	*nametable[MAXARGS];
	struct sigaction act;

	newargv[0] = argv[0];

	/*
	 * Now for each command argument, see if it is a wildcard, and if
	 * so, replace the argument with the list of matching filenames.
	 */
	newargc = 1;
	oac = 0;

	while (++oac < argc) {
		if (argv[oac][0] == '"' || argv[oac][0] == '\'') {
			argv[oac]++;
			matches = 0;
		}
		else {
			matches = expandwildcards(argv[oac], MAXARGS, nametable);
			if (matches < 0)
				return;
		}

		if ((newargc + matches) >= MAXARGS) {
			fprintf(stderr, "Too many arguments\n");
			return;
		}

		if (matches == 0)
			newargv[newargc++] = argv[oac];

		for (i = 0; i < matches; i++)
			newargv[newargc++] = nametable[i];
	}

	newargv[newargc] = 0;

	if (!bg)
		signal(SIGCHLD, SIG_DFL);

	/*
	 * Do the fork and exec ourselves.
	 * If this fails with ENOEXEC, then run the
	 * shell anyway since it might be a shell script.
	 */
	if (!(pid = vfork())) {
		int	ci;
		char	errbuf[50];

		/*
		 * We are the child, so run the program.
		 * First close any extra file descriptors we have opened.
		 * be sure not to modify any globals after the vfork !
		 */

		for (ci = 0; ci < sourcecount; ci++)
			if (sourcefiles[ci] != stdin)
				close(fileno(sourcefiles[ci]));

		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);

		execvp(newargv[0], newargv);

		ci = errno;
		write(2, newargv[0], strlen(newargv[0]));
		write(2, ": ", 2);
		if (ci == ENOENT)
			write(2, enoent_msg, sizeof(enoent_msg) - 1);
		else if (strerror_r(ci, errbuf, sizeof(errbuf)))
			write(2, unkerr_msg, sizeof(unkerr_msg) - 1);
		else
			write(2, errbuf, strlen(errbuf));
		write(2, "\n", 1);

		_exit(ci == ENOENT ? 127 : 126);
	}

	if (pid < 0) {
		memset(&act, 0, sizeof(act));
		act.sa_handler = catchchild;
		act.sa_flags = SA_RESTART;
		sigaction(SIGCHLD, &act, NULL);

		perror("vfork failed");
		return;
	}

	if (bg) {
		printf("[%d]\n", pid);
		return;
	}

	if (pid) {
		int cpid;
		status = 0;
		intcrlf = FALSE;

		for (;;) {
			cpid = wait4(pid, &status, 0, 0);
			if ((cpid < 0) && (errno == EINTR))
				continue;
			if (cpid < 0)
				break;
			if (cpid != pid) {
				fprintf(stderr, "sh %d: child %d died\n", getpid(), cpid);
				continue;
			}
		}

		act.sa_handler = catchchild;
		memset(&act.sa_mask, 0, sizeof(act.sa_mask));
		act.sa_flags = SA_RESTART;
		sigaction(SIGCHLD, &act, NULL);

		intcrlf = TRUE;

		if (WIFEXITED(status)) {
			if (WEXITSTATUS(status) == 0)
				return;
			exit_code = WEXITSTATUS(status);
		} else
			exit_code = 1;

		return;
	}

	perror(argv[0]);
	exit(1);
}

void
do_help(argc, argv)
	int	argc;
	char	**argv;
{
	CMDTAB	*cmdptr;

	for (cmdptr = cmdtab; cmdptr->name && cmdptr->name[0]; cmdptr++)
		printf("%-10s %s\n", cmdptr->name, cmdptr->usage);
}

/*
 * Look up an alias name, and return a pointer to it.
 * Returns NULL if the name does not exist.
 */
static ALIAS *
findalias(name)
	char	*name;
{
	ALIAS	*alias;
	int	count;

	count = aliascount;
	for (alias = aliastable; count-- > 0; alias++) {
		if (strcmp(name, alias->name) == 0)
			return alias;
	}

	return NULL;
}


void
do_source(argc, argv)
	int	argc;
	char	**argv;
{
	readfile(argv[1]);
}

void
do_pid(argc, argv)
	int	argc;
	char	**argv;
{
	printf("%d\n", getpid());
}

void
do_exec(argc, argv)
	int	argc;
	char	**argv;
{
	while (--sourcecount >= 0) {
		if (sourcefiles[sourcecount] != stdin)
			fclose(sourcefiles[sourcecount]);
	}

	argv[argc] = NULL;
	execvp(argv[1], &argv[1]);

	perror(argv[1]);
	exit(1);
}

/*
 * Display the prompt string.
 */
static void
showprompt()
{
	char	*cp;
	char buf[60];

	if ((cp = getenv("PS1")) != NULL) {
		printf("%s", cp);
	}
	else {
		*buf = '\0';
		getcwd(buf, sizeof(buf) - 1);
		printf("%s> ", buf);
	}
	fflush(stdout);
}


static void
catchint()
{
	signal(SIGINT, catchint);

	intflag = TRUE;

	if (intcrlf)
		write(STDOUT, "\n", 1);
}


static void
catchquit()
{
	signal(SIGQUIT, catchquit);

	intflag = TRUE;

	if (intcrlf)
		write(STDOUT, "\n", 1);
}

static void
catchchild()
{
	char buf[40];
	pid_t pid;
	int status;

	pid = wait4(-1, &status, WUNTRACED, 0);
	if (WIFSTOPPED(status))
		sprintf(buf, "sh %d: Child %d stopped\n", getpid(), pid);
	else
		sprintf(buf, "sh %d: Child %d died\n", getpid(), pid);

	if (intcrlf)
		write(STDOUT, "\n", 1);

	write(STDOUT, buf, strlen(buf));
}

/* END CODE */
