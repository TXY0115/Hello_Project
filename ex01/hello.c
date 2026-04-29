#include <stdio.h>

int main() {
    char str[100]; // 准备一个能装100个字符的“篮子”
    
    printf("请输入一些内容: ");
    
    // 使用 scanf 获取键盘输入。 %s 代表字符串
    scanf("%s", str);
    
    // 把刚才输入的文字再打印出来
    printf("你刚才输入的是: %s\n", str);
    
    return 0;
}
