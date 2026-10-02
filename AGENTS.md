# 工作规范
此文件内容不该被修改

项目位置：D:\MemorySea
库位置:D:\Luos
llvm-ucrt-mingw编译器及部分第三方库:D:\mingw64
vulakn位置:C:\vulkan
工作内容和冗余文件放在 work\

变量命名采用纯小写,应当避免大写.多个单词可用下划线链接.格式 单词_单词

跨模块变量定义到vmain,vmode

wiall用于#include标准头文件,第三方库,自定义大类,除了wiall其它地方静止#include标准头文件,第三方库等

->,**写法如无必要应该进行避免,如 this->变量名 视为低质量代码

无论函数和类型应当做到一个函数一个文件,文件名同函数.除了强关联的函数如load(加载) batch_load(批量加载)外视为不合格交付.

此库为单头文件库，不要写如#ifndef,#pragma once等类似的头文件保护

单文件推荐长度不超过200到300行,100行内为最佳.

工作记录和报告写在.vscode/work_cache.txt,写完之后记得清理,最好在400行以内.你需要先去阅读work_cache.txt内的内容

类的提前声明是静止事项

禁止写无意义备注,禁止备注单独存在,禁止多行备注

禁止添加中文或其它语言的api

先问具体问题,后认真分析，然后写工作清单，最后挂载执行清单事项

# 类标准定义
include "english/parameters/数据结构体或子类名/main.hpp"
namespace Gnik_luos {
    class 类型名 {
        public:
            #include"english/available/variable.inl"
            #include"中文/接口/变量.inl"
        public:
            #include"english/available/function.inl"
            #include"中文/接口/函数.inl"
        private:
            #include"english/available/internal/variable.inl"
            #include"english/available/internal/function.inl"
        public:
            构建函数();
            析构函数();
    };
    using 中文类型名 = 类型名;
}
#include "main.inl" //构建析构函数实现
#include "english/method/public/接口函数实现"
#include "english/method/internal/内部函数实现"

注:此结构为完整结构,可以进行省略,但额外添加视为错误.需要向前申明的地方写在具体的位置不要写在原类型定义的一堆#include里面