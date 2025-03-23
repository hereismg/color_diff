#!/usr/bin/env python3

import random
import string

def generate_random_string(length):
    # 定义生成字符串的字符集
    letters = string.ascii_lowercase
    # 使用random.choices从字符集中随机选择指定数量的字符，然后拼接成字符串
    random_string = ''.join(random.choices(letters, k=length))
    return random_string

# 指定要生成的字符串长度
# length_of_string = int(input("请输入字符串的长度: "))
length_of_string = 999999

# 生成并打印随机字符串
random_string = generate_random_string(length_of_string)
print(f"{random_string}")
