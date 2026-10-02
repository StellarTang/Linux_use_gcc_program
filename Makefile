# 基本的打印信息
$(info 这是一个Makefile的规则记录)
#`make`：默认执行第一个目标（这里是 all）

CC=gcc
CFLAGS=-Wall -Wextra -g -MMD -MP  # -MMD 生成依赖文件(.d)，-MP 处理缺失头文件情况


SRC_DIR = source
OBJ_DIR = build/object
TARGET = main

SRCS := $(wildcard $(SRC_DIR)/*.c)  # 获取当前目录下所有.c文件
# OBJS := $(SRCS:.c=.o)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
# 将 src/main.c 转换为 obj/main.d
DEPS = $(OBJS:.o=.d)
INCLUDE_DIR = ./include
CFLAGS += -I$(INCLUDE_DIR)



all: $(TARGET)

# main: test1.c test2.c
# 	gcc $^ -o $@
# $@ 当前目标的名字 即main
# $^ 当前目标的所有依赖文件	即%.c,test1.c test2.c
# $< 当前目标的第一个依赖文件即%.c,test1.c

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@	# 编译.c文件为.o文件

$(TARGET): $(OBJS)
	$(CC) $^ -o $@  # 链接所有.o

# 关键步骤：包含自动生成的依赖文件
# - 表示如果文件不存在也不报错（第一次编译时还没有 .d 文件）
-include $(DEPS)

.PHONY: clean all

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)


# 测试 :=
X := 100
Y := $(X)
X := 200
test1:
	@echo Y=$(Y)

M = 100
N = $(M)
M = 200
test2:
	@echo N=$(N)


# 下面两句效果一模一样()与{}，都是引用变量的值
test3:
	@echo $(CC)
	@echo ${CC}

test4:
	@echo "make变量: $(M)"
	@echo "传给shell的美元符号: $$HOME"

test5:
	#test for print something	

test6:
	@echo "test for print something"
	@pwd
	@which gcc
	@ls -lah

test7:
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"	
	@echo "DEPS: $(DEPS)"


# ```
# app: main.c
# 	gcc main.c -o app
# ```

# - `app: main.c` 的含义：**目标 app，依赖 main.c**
# - make 的核心逻辑：**比较目标和依赖的时间戳**
#   - 如果 `main.c` 的修改时间比 `app` 新 → 执行下面 `gcc` 命令重新编译
#   - 如果 `main.c` 没改动 → 不执行 gcc，直接跳过

