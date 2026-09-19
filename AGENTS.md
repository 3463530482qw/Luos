# 工作规范
项目位置：D:\MemorySea
库位置:D:\Luos
llvm-ucrt-mingw编译器及部分第三方库:D:\mingw64
vulakn位置:C:\vulkan

变量命名采用纯小写,应当避免大写.多个单词可用下划线链接.格式 单词_单词

跨模块变量定义到vmain,vmode

wiall用于#include标准头文件,第三方库,自定义大类,除了wiall其它地方静止#include标准头文件,第三方库等

->,**写法如无必要应该进行避免,如 this->变量名 视为低质量代码

无论函数和类型应当做到一个函数一个文件,文件名同函数.除了强关联的函数如load(加载) batch_load(批量加载)外视为不合格交付.

此库为单头文件库，不要写如#ifndef,#pragma once等类似的头文件保护

单文件推荐长度不超过200到300行,100行内为最佳.

工作记录和报告写在.vscode/work_cache.txt,写完之后记得清理,最好在500行以内.

如果犯错了可以在本文件内进行添加记录保证不会再犯.

记录:批量替换标识符要按整词或带分隔符匹配.曾用 substring 把 lable 换成 label,连 "available" 里的 lable 一起改掉,
污染了 include 路径(availabel),事后才手工修回.

记录:阁下说"装配进 X"这类话,指的是库内自己接(成员持借用指针、router 把任务推进 private_run,再由 run 执行),
不是让应用从外部装钩子.曾把 window_vulkan 的引擎改成一律按参数传、又给窗口加了一层 bind_frame 钩子,
两样都不是阁下的意思,都撤了.拿不准先问一句,别自行设计新接口.

记录:不要乱加中文 api.新写的类不要加中文别名 —— 既不要 `using 中文名 = 类型名;`,
也不要 `中文/可用/…` 目录、中文成员别名.标准里那两行中文接口本库按阁下早先的要求就没启用
(见 work_cache 二十七).库里既有的中文目录(窗口配置信息/创建信息/时间等历史文件)保持原样,
别顺手补、也别顺手删.曾给新写的两个配置类加了中文别名与中文目录,被阁下指出后清掉.

记录:片段改完要回读整段核对格式.曾用带换行的 old_string 做替换,把 depth/main.hpp 的
"class Vulkan_depth {" 与下一行 "public:" 粘成一行(换行被吃掉),文件看着是乱的;同一处还顺手多写了
`class Vulkan;`(Vulkan 由 luos/main.hpp 在 window 之前定义,line_render 与 depth 直接用 `Vulkan**` 就行),
两处都被阁下指出.前向声明只写真正需要的,别写成多余的一堆.

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