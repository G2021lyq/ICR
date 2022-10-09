# 最终的目标名 app
targetse = se
targetcl = cl
# 搜索当前项目目录下的源文件
srcse=$(wildcard server.c ./src_se/*.c)
srccl=$(wildcard client.c ./src_cl/*.c)
# 将文件的后缀替换掉 .c -> .o
objse=$(patsubst %.c, %.o, $(srcse))
objcl=$(patsubst %.c, %.o, $(srccl))
# 头文件目录
include=./include

# 第一条规则
.PHONY: all
all: $(targetse) $(targetcl) user.dat

# 依赖中都是 xx.o yy.o zz.o
# gcc命令执行的是链接操作
$(targetse): $(objse)
	gcc $^ -o $@
$(targetcl): $(objcl)
	gcc $^ -o $@
user.dat:
	touch user.dat

# 模式匹配规则
# 执行汇编操作, 前两步: 预处理, 编译是自动完成
%.o:%.c
	gcc $< -c -I $(include) -o $@

.PHONY:clean
clean:
	-rm $(objse) $(targetse) -f
	-rm $(objcl) $(targetcl) -f
	-rm user.dat
        
       

