# include "rt.h"

int	main(int argc, char **argv)
{
	t_env	*e;
	
	if (argc != 2)
		ft_error("usage : ./RT file.xml\n", NULL);
	e = env_init(argv[1]);
	loop(e);
	return (0);
}
