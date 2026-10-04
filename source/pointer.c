#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "pointer.h"

void test_arr()
{
    /*数组定义时初始化，未初始化完全的均为0*/
    int arr[10] = {0, 1, 2, 3, 4, 5};

    /*数组定义时未初始化，变量随机*/
    int arr_b[10];

    int *pointer = arr;
    int len = sizeof(arr) / sizeof(arr[0]);
    /*注意 指针退化成数组了*/
    int len_test = sizeof(pointer) / sizeof(arr[0]);

    printf("len of arr = %d\n", len);
    printf("len_test of arr = %d\n", len_test);

    for (int i = 0; i < len; i++)
    {
        printf("arr[%d] = %d\t\t\t", i, arr[i]);
        printf("*(arr + %d) = %d\n", i, *(pointer + i));
    }

    pointer = arr_b;
    for (int i = 0; i < len; i++)
    {
        printf("arr_b[%d] = %d\t\t\t", i, arr_b[i]);
        printf("*(arr_b + %d) = %d\n", i, *(pointer + i));
    }
}

void test_pointer_arr()
{
    int arr_a[5] = {0, 1, 2};
    int arr_b[5] = {5, 10, 30};

    /*int *pointer[10] = int* pointer[10]*/
    int *pointer[10] = {arr_a, arr_b};

    int len = sizeof(pointer) / sizeof(pointer[0]);
    int len_arr_a = sizeof(arr_a) / sizeof(arr_a[0]);
    int len_arr_b = sizeof(arr_b) / sizeof(arr_b[0]);

    printf("len_arr_a = %d\n", len_arr_a);
    printf("len_arr_b = %d\n", len_arr_b);

    for (int i = 0; i < len; i++)
    {
        if(pointer[i] == arr_a || pointer[i] == arr_b)
        {
            for (int j = 0; j < len_arr_a; j++)
            {
                printf("*(pointer[i] + j) = %d\t", *(pointer[i] + j));
            }
        }
        printf("pointer = %x\n", pointer[i]);
    }
}


void test_arr_pointer()
{
    int arr[5][10] = {0};

    int total_len = sizeof(arr) / sizeof(arr[0][0]);
    printf("sizeof(arr) = %d\n", total_len);

    int colum = sizeof(arr[0]) / sizeof(arr[0][0]);
    int row = total_len / colum;
    printf("row = %d\n", row);
    printf("colum = %d\n", colum);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < colum; j++)
        {
            arr[i][j] = i * 10 + j;
            // printf("arr[%d][%d] = %d\n", i, j,arr[i][j]);
        }
    }


    int (*arr_pointer)[10];
    /*数组指针就是一个指针，大小在32位cpu=4字节，64位上是8字节*/
    printf("sizeof(arr_pointer) = %d\n", sizeof(arr_pointer));


    /*- `arr`：退化成**第 0 行地址** `int (*)[3]`
    - `&arr`：**整个二维数组的地址** `int (*)[2][3]`
    - 两者**起始内存数字相同**，但是指针运算时，`+1` 的步长完全不同。*/
    arr_pointer = arr;
    printf("arr_pointer = %x\n", arr_pointer);
    printf("arr = %x\n", arr);
    printf("arr+1 = %x\n", arr+1);
    printf("&arr = %x\n", &arr);
    printf("&arr +1 = %x\n", &arr+1);

    /*⚠️ **数组只要参与运算（做 +j / 赋值），
    数组名就会自动退化，变成数组首元素指针 `int *`**
    `*(arr_pointer+i)` 本来是 `int[3]`，遇到 `+j` → 
    退化成 `int*`，指向当前行第 0 个 int。*/
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < colum; j++)
        {
            printf("*(*(arr_pointer + %d)+%d) = %d\n", i, j, *(*(arr_pointer + i)+j));
            printf("arr[%d][%d] = %d\n", i, j, arr_pointer[i][j]);
        }
    }
}

static int value_for_function_get_value = 100;
int function_get_value(int * value)
{
    return *value;
}

int (*function_pointer)(int * );

void test_function_pointer()
{
    function_pointer = function_get_value; 
    /*函数指针，调用可以(*p)(), 也可以p()*/
    int static_value = (*function_get_value)(&value_for_function_get_value);
    printf("static_value = %d\n", static_value);

    value_for_function_get_value = 200;
    static_value = function_get_value(&value_for_function_get_value);
    printf("static_value = %d\n", static_value);
}



/*#
：：：：：指针退化：：：：：：
> 
> 退化的原因**不是赋值**，不是 “类型不一致才退化”
> **退化规则（C 标准）：**
> 数组名在**表达式中**，除下面 3 种特例，全部自动转为指向首元素的指针：

1. `sizeof(数组名)` 👉 不退化！取整个数组字节大小
2. `&数组名`        👉 不退化！取**整个数组的地址**
3. 数组初始化 `char s[]="abc"` 这种初始化列表场景

👉 只要不是上面 3 种，只要数组名放在表达式里（赋值右边、函数传参、加减运算），都会退化。

**退化和两边类型是否匹配没关系！**
哪怕你写错类型，退化照样发生，只是编译报警告：*/
void test_one_dementional_pointer_degrade()
{
    int test_a[10] = {1, 2, 3, 4, 5};

    int *p1 = test_a;
    printf("pointer test_a = %x\n", p1);
    printf("pointer test_a = %x\n", p1 + 1);

    int *p2 = &test_a;
    printf("pointer &test_a = %x\n", p2);
    printf("pointer &test_a = %x\n", p2 + 1);
}

void test_two_dementional_pointer_degrade()
{
    int test_a[10][100] = {
        {1, 2, 3, 4, 5}

    };

    // int *p1 = test_a;
    // printf("pointer test_a = %x\n", p1);
    // printf("pointer test_a = %x\n", p1 + 1);

    // int *p2 = &test_a;
    // printf("pointer &test_a = %x\n", p2);
    // printf("pointer &test_a = %x\n", p2 + 1);

    int (*p1)[100] = test_a;
    int (*p3)[100] = test_a + 1;
    // printf("pointer test_a = %x\n", p1);
    // printf("pointer test_a = %x\n", p1 + 1);
    printf("pointer test_a = %x\n", test_a);
    printf("pointer test_a = %x\n", test_a + 1);
    printf(" test_a = %d\n", (void *)p3 - (void *)p1);

    // printf("pointer &test_a = %x\n", p2);
    // printf("pointer &test_a = %x\n", p2 + 1);
    printf("pointer test_a = %x\n", &test_a);
    printf("pointer test_a = %x\n", &test_a + 1);
    printf(" test_a = %d\n",(void *) (&test_a + 1) - (void *)&test_a);

}
