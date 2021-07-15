#gcc -g3 -Wall -Werror -Wextra -fsanitize=address *.c ./*/*.c  -o minishell && ./minishell
gcc -g3 -Wall -Werror -Wextra *.c ./*/*.c  -o minishell && ./minishell
