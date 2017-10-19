/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 17:43:54 by curquiza          #+#    #+#             */
/*   Updated: 2017/08/20 17:43:55 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_check_err_cd(char *path, t_shell *shell)
{
	struct stat		info;

	if (!path)
		return (-1);
	errno = 0;
	if (stat(path, &info) == -1)
	{
		if (errno == 13)
			ft_put_cd_errmsg(shell->name, path, "permission denied");
		else
			ft_put_cd_errmsg(shell->name, path, "no such file or directory");
		return (-1);
	}
	if (!S_ISDIR(info.st_mode))
	{
		ft_put_cd_errmsg(shell->name, path, "not a directory");
		return (-1);
	}
	if (access(path, X_OK) == -1)
	{
		ft_put_cd_errmsg(shell->name, path, "permission denied");
		return (-1);
	}
	return (0);
}

int		ft_go_to_dir(t_shell *shell, char *path)
{
	char	*pwd;

	if (ft_check_err_cd(path, shell) == -1)
		return (CMD_FAILURE);
	pwd = getcwd(NULL, MAXPATHLEN);
	if (pwd)
		ft_chg_varval_or_add(&shell->var_env, "OLDPWD", pwd);
	if (chdir(path) == -1)
	{
		ft_put_errmsg(shell->name, "cd", "chdir error");
		ft_strdel(&pwd);
		return (CMD_FAILURE);
	}
	ft_strdel(&pwd);
	pwd = getcwd(NULL, MAXPATHLEN);
	if (pwd)
		ft_chg_varval_or_add(&shell->var_env, "PWD", pwd);
	ft_strdel(&pwd);
	return (CMD_SUCCESS);
}

int		ft_go_to_home(t_shell *shell)
{
	int		ret;
	char	*path;

	if (!(path = ft_get_varvalue(shell->var_env, "HOME")))
	{
		ft_put_errmsg(shell->name, "cd", "HOME not set");
		return (CMD_FAILURE);
	}
	path = ft_strdup(path);
	ret = ft_go_to_dir(shell, path);
	ft_strdel(&path);
	return (ret);
}

int		ft_go_to_oldpwd(t_shell *shell)
{
	int		ret;
	char	*path;

	if (!(path = ft_get_varvalue(shell->var_env, "OLDPWD")))
	{
		ft_put_errmsg(shell->name, "cd", "OLDPWD not set");
		return (CMD_FAILURE);
	}
	path = ft_strdup(path);
	ret = ft_go_to_dir(shell, path);
	ft_strdel(&path);
	return (ret);
}

int		ft_builtin_cd(t_ast *ast)
{
	char	*flags;
	char	flag_error;
	char	**arg;
	int		ret;

	ret = CMD_SUCCESS;
	flags = ft_get_flags(ast->argtab + 1);
	if ((flag_error = ft_check_illegal_flags(flags, "LP")) != 0)
	{
		ft_put_usage("cd", flag_error, "LP");
		ft_strdel(&flags);
		return (CMD_FAILURE);
	}
	arg = ft_get_arg(ast->argtab + 1, flag_error);
	if (arg && !arg[0])
		ret = ft_go_to_home(ast->shell);
	else if (arg && !ft_strcmp(arg[0], "-"))
		ret = ft_go_to_oldpwd(ast->shell);
	else if (arg && arg[0])
		ret = ft_go_to_dir(ast->shell, arg[0]);
	ft_strdel(&flags);
	return (ret);
}
