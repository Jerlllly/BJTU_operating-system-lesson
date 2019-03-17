.data #数据段声明
      msg: .string "Hello,world!\n"#要输出的字符串
      len=. -msg #字串长度
.text #代码段声明
.global _start #指定入口函数
 
_start:
      movl $len,%edx #参数三 字符长度
      movl $msg,%ecx #参数二 字符串指针
      movl $1,%ebx #参数一 文件描述符 stdout
      movl $4,%eax #系统调用号 sys_write ssize_t write(int fd, const void* buf, size_t count);
      int $0x80 #调用内核功能 是一条AT&T语法的中断指令，用于Linux的系统调用。
      
      #退出程序
      movl $0,%ebx #参数一：退出代码
      movl $1,%eax #系统调用号：sys_exit
      int $0x80#调用内核功能

