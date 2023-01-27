/*
 * main.c
 *
 *  Created on: 2023年1月27日
 *      Author: arisery
 */

#include "main.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

int ARRAY_NUM = 16;
int LINE_ROW = 4;
char game_is_over = 0;
typedef enum
    {
    NO_DIR,
    UP = 8,
    DOWN = 2,
    LEFT = 4,
    RIGHT = 6,
    MID = 5,
    } DIRECTION;
int get_random_empty(int *array, int n);
DIRECTION get_dir();
void game_handle(int *array, char dir);
void left_handle(int *array);
void matix_rotation(int *array, int line_row);
void matix_up_down(int *array, int line_row);
void matix_left_right(int *array, int line_row);
int main(int argc, char *argv[])
    {
    char direction = NO_DIR;
    int *num_array;
    int rand_num = 0;
    if (argc != 1)
	{
	LINE_ROW = atoi(argv[1]);
	ARRAY_NUM = LINE_ROW * LINE_ROW;

	}
    else{
	printf_s("input the number of row\r\n");
	scanf_s("%d",&LINE_ROW);
	ARRAY_NUM = LINE_ROW * LINE_ROW;
    }
    printf_s("argc is %d\r\n", argc);
    for (int x = 0; x < argc; x++)
	{
	printf_s("argv[%d] is %s \r\n", x, argv[x]);
	}
    printf_s("ARRAY_NUM is %d,\t LINE_ROW is %d\r\n", ARRAY_NUM, LINE_ROW);

    if (ARRAY_NUM == 0)
	{
	printf_s("wrong param,quit...\r\n");
	game_is_over = 1;
	}
    else
	{
	printf_s("note:\r\n press q to quit game\r\n");
	printf_s("/******  w  ******/\tUP\r\n");
	printf_s("/***  a  *********/\tLEFT\r\n");
	printf_s("/*********  d  ***/\tRIGHT\r\n");
	printf_s("/******  s  ******/\tDOWN\r\n");

	num_array = malloc(ARRAY_NUM * sizeof(int));
	memset(num_array, 0, ARRAY_NUM * sizeof(int));
	printf_s("2048 GAME START!!!\r\n");
	}
    srand(time(NULL));
    srand(rand());
    rand_num = rand();
    while (1)
	{
	if (game_is_over == 1)
	    {
	    break;
	    }
	rand_num = get_random_empty(num_array, ARRAY_NUM);
	if (rand_num != -1)
	    {
	    num_array[rand_num] = 2;
	    }
	else
	    {
	    break;
	    }
	for (int i = 1; i <= ARRAY_NUM; i++)
	    {
	    printf_s("%6d\t", num_array[i - 1]);
	    if ((i % LINE_ROW) == 0)
		{
		for (int x = 1; x < 4; x++)
		    printf_s("\r\n");
		}
	    }

	printf_s(
		"/************************************************************/\r\n");
	printf_s("new number position is (%d,%d)\r\n",
		(rand_num % LINE_ROW) + 1, (rand_num / LINE_ROW) + 1);
	direction = get_dir();
	game_handle(num_array, direction);

	}
    printf_s("\r\n");
    printf_s("Game is over!\r\n");
    }

/*
 * @brief	找出数组0-n中为0的元素,随机返回其中一个元素的序列
 * @param	数组的指针
 * @param	数组的个数
 * @retval  返回数组为0的序列号
 */
int get_random_empty(int *array, int n)
    {
    int num = rand() % n, flag = 0;
    for (int i = 0; i < n; i++)
	{
	if (array[i] == 0)
	    {
	    flag = 1;
	    }
	}
    if (flag == 0)
	{
	return -1;
	}
    while (array[num] != 0)
	{
	num = rand() % n;
	}
    return num;
    }
/*brief 获取滑动方向
 * param NULL
 * retval 方向
 */
DIRECTION get_dir()
    {
    char dir = NO_DIR;
    while (dir == NO_DIR)
	{
	printf_s("input you direction\r\n");
	 scanf ("%c", &dir);
	//dir = getchar();
	//getchar();
	if (dir == 'w')
	    dir = UP;
	else if (dir == 's')
	    dir = DOWN;
	else if (dir == 'a')
	    dir = LEFT;
	else if (dir == 'd')
	    dir = RIGHT;
	else if (dir == 'q')
	    game_is_over = 1;
	else
	    {
	    dir = NO_DIR;
	    printf_s("/********please input again*********/\r\n");
	    }
	}
    switch (dir)
	{
    case UP:
	printf_s("your direction is UP \r\n");
	break;
    case DOWN:
	printf_s("your direction is DOWN \r\n");
	break;
    case LEFT:
	printf_s("your direction is LEFT \r\n");
	break;
    case RIGHT:
	printf_s("your direction is RIGHT \r\n");
	break;
	}

    return dir;
    }

void game_handle(int *array, char dir)
    {
    switch (dir)
	{
    case UP:

	matix_rotation(array, LINE_ROW);
	left_handle(array);
	matix_rotation(array, LINE_ROW);
	break;
    case DOWN:
	matix_up_down(array, LINE_ROW);
	matix_rotation(array, LINE_ROW);
	left_handle(array);

	matix_rotation(array, LINE_ROW);
	matix_up_down(array, LINE_ROW);
	break;
    case LEFT:
	left_handle(array);
	break;
    case RIGHT:
	matix_left_right(array, LINE_ROW);
	left_handle(array);
	matix_left_right(array, LINE_ROW);

	break;

	}

    }

void left_handle(int *array)
    {
    for (int y = 1; y <= LINE_ROW; y++)
	{

	for (int x = 1; x <= (LINE_ROW - 1); x++)
	    {
	    if (array[(y - 1) * LINE_ROW + (x - 1)] != 0)
		{
		for (int i = x; i <= (LINE_ROW - 1); i++)
		    {

		    if (array[(y - 1) * LINE_ROW + i]
			    == array[(y - 1) * LINE_ROW + (x - 1)])
			{
			array[(y - 1) * LINE_ROW + (x - 1)] *= 2;
			array[(y - 1) * LINE_ROW + i] = 0;
			break;
			}
		    if (array[(y - 1) * LINE_ROW + i] != 0)
			{
			break;
			}
		    }
		}
	    }
	for (int i = 1; i <= (LINE_ROW - 1); i++)
	    {
	    for (int x = 1; x <= (LINE_ROW - 1); x++)
		{
		if (array[(y - 1) * LINE_ROW + (x - 1)] == 0)
		    {
		    array[(y - 1) * LINE_ROW + (x - 1)] = array[(y - 1)
			    * LINE_ROW + x];
		    array[(y - 1) * LINE_ROW + x] = 0;
		    }
		}
	    }
	}
    }

void matix_rotation(int *array, int line_row)
    {
    for (int y = 1; y <= line_row; y++)
	{
	int temp;
	for (int x = y + 1; x <= line_row; x++)
	    {
	    temp = array[(y - 1) * line_row + (x - 1)];
	    array[(y - 1) * line_row + (x - 1)] = array[(x - 1) * line_row
		    + (y - 1)];
	    array[(x - 1) * line_row + (y - 1)] = temp;
	    }
	}

    }
void matix_up_down(int *array, int line_row)
    {
    for (int y = 1; y <= (int) (line_row / 2); y++)
	{
	int temp;
	for (int x = 1; x <= line_row; x++)
	    {
	    temp = array[(y - 1) * line_row + (x - 1)];
	    array[(y - 1) * line_row + (x - 1)] = array[(line_row - y)
		    * line_row + (x - 1)];
	    array[(line_row - y) * line_row + (x - 1)] = temp;
	    }
	}
    }

void matix_left_right(int *array, int line_row)
    {
    for (int y = 1; y <= line_row; y++)
	{
	int temp;
	for (int x = 1; x <= (int) (line_row / 2); x++)
	    {
	    temp = array[(y - 1) * line_row + (x - 1)];
	    array[(y - 1) * line_row + (x - 1)] = array[(y - 1) * line_row
		    + (line_row - x)];
	    array[(y - 1) * line_row + (line_row - x)] = temp;
	    }
	}
    }
