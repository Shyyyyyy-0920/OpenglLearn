# 递归将本文件夹下所有的cpp放到DUNCS中
file(GLOB_RECURSE WRAPPER ./ *.cpp)

# 将FUNCS中所有cpp编译为FUNCS这个lib库
add_library(wrapper ${WRAPPER})