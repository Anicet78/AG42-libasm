#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_list
{
	char *data;
	struct s_list *next;
} t_list;

// Mandatory
extern size_t	ft_strlen(const char *s);
extern char*	ft_strcpy(char *dest, const char *src);
extern int		ft_strcmp(const char *s1, const char *s2);
extern ssize_t	ft_write(int fd, const void *buf, size_t count);
extern ssize_t	ft_read(int fd, void *buf, size_t count);
extern char*	ft_strdup(const char *s);
extern void*	ft_calloc(size_t nmemb, size_t size);

// Bonus
extern int			ft_atoi_base(char *str, char *base);
extern void			ft_list_push_front(t_list **begin_list, void *data);
extern unsigned int	ft_list_size(t_list *begin_list);
extern void			ft_list_sort(t_list **begin_list, int (*cmp)());
extern void			ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
extern void			*ft_simd_memchr(const void *s, int c, size_t n);

void void_data(void *data) {
	(void)data;
	return ;
}

void free_data(void *data) {
	free(data);
	return ;
}

int main(int ac, char **av) {
	bool debug = false;

	if (ac > 1 && strcmp(av[1], "debug") == 0)
		debug = true;

	int count;

	// !MANDATORY

	printf("==== MANDATORY ====\n");

	// * strlen
	count = 0;
	char	*strlen1 = "";
	char	*strlen2 = "salut";
	if (strlen(strlen1) == ft_strlen(strlen1))
		count++;
	if (strlen(strlen2) == ft_strlen(strlen2))
		count++;
	if (count == 2)
		printf("strlen:        OK!\n");
	else
		printf("strlen:        Error:%d/2\n", count);

	// * strcpy
	char	strcpy_src1[] = "salut";
	char	strcpy_dest1[6];
	char	strcpy_dest2[6];
	char*	strcpy_og = strcpy(strcpy_dest1, strcpy_src1);
	char*	strcpy_me = ft_strcpy(strcpy_dest2, strcpy_src1);
	if (debug) printf("------------\nSTRCPY:\nOG: %s | %p | %p\nME: %s | %p | %p\n------------\n", strcpy_dest1, strcpy_dest1, strcpy_og, strcpy_dest2, strcpy_dest2, strcpy_me);
	if (strcmp(strcpy_dest1, strcpy_dest2) == 0 && strcpy_dest2 == strcpy_me)
		printf("strcpy:        OK!\n");
	else
		printf("strcpy:        Error\n");

	// * strcmp
	count = 0;
	char	*strcmp_src1 = "salut";
	char	*strcmp_src2 = "salutt";
	int		strcmp_og = strcmp(strcmp_src1, strcmp_src2);
	int		strcmp_me = ft_strcmp(strcmp_src1, strcmp_src2);
	if (debug) printf("------------\nSTRCMP:\nOG: %d\nME: %d\n------------\n", strcmp_og, strcmp_me);
	if (strcmp(strcmp_src1, strcmp_src2) == ft_strcmp(strcmp_src1, strcmp_src2))
		count++;
	if (strcmp(strcmp_src2, strcmp_src1) == ft_strcmp(strcmp_src2, strcmp_src1))
		count++;
	if (strcmp(strcmp_src1, strcmp_src1) == ft_strcmp(strcmp_src1, strcmp_src1))
		count++;
	if (count == 3)
		printf("strcmp:        OK!\n");
	else
		printf("strcmp:        Error\n");

	// * write
	count = 0;
	int write_fd = debug ? STDOUT_FILENO : open("/dev/null", O_WRONLY);
	if (debug) {
		printf("------------\nFT_WRITE:\n");
		fflush(stdout);
	}
	ssize_t write_og = write(write_fd, "OG: TEST\n", 9);
	ssize_t write_me = ft_write(write_fd, "ME: TEST\n", 9);
	if (write_og == write_me)
		count++;
	write_fd = open("/dev/null", O_RDONLY);
	write_og = write(write_fd, "------------\nFT_WRITE:\nOG: TEST", 31);
	int write_og_errno = errno;
	write_me = ft_write(write_fd, "\nME: TEST\n", 10);
	int write_me_errno = errno;
	if (write_og == write_me && write_og_errno == write_me_errno)
		count++;
	if (count == 2)
		printf("write:         OK!\n");
	else
		printf("write:         Error\n");

	// * read
	count = 0;
	char read_dest1[50];
	char read_dest2[50];
	int read_fd = open("/etc/ssh/ssh_host_ed25519_key.pub", O_RDONLY);
	ssize_t read_og = read(read_fd, read_dest1, 50);
	read_dest1[50] = 0;
	lseek(read_fd, 0, SEEK_SET);
	ssize_t read_me = ft_read(read_fd, read_dest2, 50);
	read_dest2[50] = 0;
	if (strncmp(read_dest1, read_dest2, 50) == 0 && read_og == read_me)
		count++;
	if (debug) printf("------------\nREAD:\nOG: %s\nME: %s\n------------\n", read_dest1, read_dest2);
	read_fd = open("/unknown", O_WRONLY);
	read_og = read(read_fd, read_dest1, 50);
	int read_og_errno = errno;
	read_me = ft_read(read_fd, read_dest2, 50);
	int read_me_errno = errno;
	if (read_og == read_me && read_og_errno == read_me_errno)
		count++;
	if (count == 2)
		printf("read:          OK!\n");
	else
		printf("read:          Error\n");

	// * strdup
	char	strdup1[] = "salut";
	char	*strdup_og = strdup(strdup1);
	char	*strdup_me = ft_strdup(strdup1);
	if (debug) printf("------------\nSTRDUP:\nOG: %s\nME: %s\n------------\n", strdup_og, strdup_me);
	if (strcmp(strdup_og, strdup_me) == 0)
		printf("strdup:        OK!\n");
	else
		printf("strdup:        Error\n");
	free(strdup_og);
	free(strdup_me);

	// * calloc
	int i = 0;
	char	*calloc_og = calloc(5, sizeof(char));
	char	*calloc_me = ft_calloc(5, sizeof(char));
	if (debug) {
		printf("------------\nCALLOC:\n");
		printf("OG: ");
		while (i < 5)
			printf("%d ", calloc_og[i++]);
		printf("\nME: ");
		i = 0;
		while (i < 5)
			printf("%d ", calloc_me[i++]);
		printf("\n------------\n");
	}
	void* fail_calloc_og = calloc(LONG_MAX, sizeof(int));
	void* fail_calloc_me = ft_calloc(LONG_MAX, sizeof(int));
	if (memcmp(calloc_og, calloc_me, 5) == 0 && fail_calloc_og == fail_calloc_me)
		printf("calloc:        OK!\n");
	else
		printf("calloc:        Error\n");
	free(calloc_og);
	free(calloc_me);

	// !BONUS

	printf("\n======= BONUS =======\n");

	// * ft_atoi_base
	count = 0;
	if (ft_atoi_base("2a", "0123456789abcdef") == 42)
		count++;
	if (ft_atoi_base("2a", " 0123456789abcdef") == 0)
		count++;
	if (ft_atoi_base("2a", "0123456789 abcdef") == 0)
		count++;
	if (ft_atoi_base("2a", "0123456789abcdef ") == 0)
		count++;
	if (ft_atoi_base("2a", "01234567+89abcdef") == 0)
		count++;
	if (ft_atoi_base("2a", "0123456789abcdef-") == 0)
		count++;
	if (ft_atoi_base("2a", "01f23456789abcdef") == 0)
		count++;
	if (ft_atoi_base("2a", "\b0123456789abcdef") == 0)
		count++;
	if (ft_atoi_base("29", "0") == 0)
		count++;
	if (ft_atoi_base("29", "") == 0)
		count++;
	if (ft_atoi_base("2a", "0123456789") == 2)
		count++;
	if (ft_atoi_base("29", "0123456789") == 29)
		count++;
	if (ft_atoi_base("      \b    +29", "0123456789") == 29)
		count++;
	if (ft_atoi_base("      \b    -29", "0123456789") == -29)
		count++;
	if (ft_atoi_base(" -2a", "0123456789abcdef") == -42)
		count++;
	if (ft_atoi_base("", "0123456789") == 0)
		count++;
	if (ft_atoi_base("-", "0123456789") == 0)
		count++;
	if (ft_atoi_base("b", "0123456789") == 0)
		count++;
	if (count == 18)
		printf("atoi_base:        OK!\n");
	else
		printf("atoi_base:        Error\n");

	// * LIST_PUSH_FRONT
	t_list* lst = NULL;
	ft_list_push_front(&lst, "a");
	ft_list_push_front(&lst, "b");
	ft_list_push_front(&lst->next, "c");
	if (lst && *(char *)(lst->data) == 'b'
		&& lst->next && *(char *)(lst->next->data) == 'c'
		&& lst->next->next && *(char *)(lst->next->next->data) == 'a')
		printf("list_push_front:  OK!\n");
	else
		printf("list_push_front:  Error\n");

	// * LIST_SIZE
	if (ft_list_size(NULL) == 0 && ft_list_size(lst) == 3)
		printf("list_size:        OK!\n");
	else
		printf("list_size:        Error\n");

	// * LIST_SORT
	count = 0;
	ft_list_push_front(&lst, "9");
	ft_list_push_front(&lst, "x");
	ft_list_push_front(&lst, "b");
	ft_list_sort(&lst, &ft_strcmp);
	if (*(char *)(lst->data) == '9'
		&& *(char *)(lst->next->data) == 'a'
		&& *(char *)(lst->next->next->data) == 'b'
		&& *(char *)(lst->next->next->next->data) == 'b'
		&& *(char *)(lst->next->next->next->next->data) == 'c'
		&& *(char *)(lst->next->next->next->next->next->data) == 'x')
		count++;
	ft_list_sort(NULL, &ft_strcmp);
	t_list* lst2 = NULL;
	ft_list_sort(&lst2, NULL);
	ft_list_sort(&lst2, &ft_strcmp);
	ft_list_push_front(&lst2, "");
	ft_list_sort(&lst2, &ft_strcmp);
	ft_list_push_front(&lst2, "TEST");
	ft_list_sort(&lst2, &ft_strcmp);
	if (ft_strcmp(lst2->data, lst2->next->data) <= 0)
		count++;
	if (count == 2)
		printf("list_sort:        OK!\n");
	else
		printf("list_sort:        Error\n");
	free(lst2->next);
	free(lst2);

	// * LIST_REMOVE_IF
	count = 0;
	ft_list_remove_if(&lst, "b", &ft_strcmp, NULL);
	if (*(char *)(lst->data) == '9'
		&& *(char *)(lst->next->data) == 'a'
		&& *(char *)(lst->next->next->data) == 'c'
		&& *(char *)(lst->next->next->next->data) == 'x')
		count++;
	ft_list_remove_if(NULL, "", &ft_strcmp, &void_data);
	ft_list_remove_if(&lst, "", &ft_strcmp, &void_data);
	ft_list_remove_if(&lst, "", &ft_strcmp, &void_data);
	ft_list_remove_if(&lst, "a", &ft_strcmp, &void_data);
	ft_list_remove_if(&lst, "x", &ft_strcmp, &void_data);
	ft_list_remove_if(&lst, "TEST", &ft_strcmp, &free_data);
	ft_list_push_front(&lst, ft_strdup("TEST"));
	ft_list_remove_if(&lst, "TEST", &ft_strcmp, &free_data);
	if (ft_list_size(lst) == 2)
		count++;
	ft_list_remove_if(&lst, "9", &ft_strcmp, &void_data);
	ft_list_remove_if(&lst, "c", &ft_strcmp, &void_data);
	if (ft_list_size(lst) == 0)
		count++;
	if (count == 3)
		printf("list_remove_if:   OK!\n");
	else
		printf("list_remove_if:   Error\n");

	// * SIMD_MEMCHR
	count = 0;
	const char memchr_str[] = "o-pifosngoaqwertyjukjmn zs\bdtyjmnvghjkiuytdcghjkluytf\b";
	if (memchr(memchr_str, '\b', 54) == ft_simd_memchr(memchr_str, '\b', 54))
		count++;
	if (memchr(memchr_str, '\t', 54) == ft_simd_memchr(memchr_str, '\t', 54))
		count++;
	if (memchr(memchr_str, '\b', 0) == ft_simd_memchr(memchr_str, '\b', 0))
		count++;
	if (memchr(memchr_str, 'o', 0) == ft_simd_memchr(memchr_str, 'o', 0))
		count++;
	if (memchr(memchr_str, 'o', 1) == ft_simd_memchr(memchr_str, 'o', 1))
		count++;
	if (memchr(memchr_str, 's', 15) == ft_simd_memchr(memchr_str, 's', 15))
		count++;
	if (memchr(memchr_str, 's', 17) == ft_simd_memchr(memchr_str, 's', 17))
		count++;
	if (memchr(memchr_str, '\0', 54) == ft_simd_memchr(memchr_str, '\0', 54))
		count++;
	if (memchr(memchr_str, '\0', 55) == ft_simd_memchr(memchr_str, '\0', 55))
		count++;
	if (count == 9)
		printf("simd_memchr:      OK!\n");
	else
		printf("simd_memchr:      Error\n");

	return (0);
}
