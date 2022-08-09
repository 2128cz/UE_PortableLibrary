# 通用操作库
-----

文件分为<code>Private</code>和<code>Public</code>两个文件夹；

其中<code>Private</code>保存.cpp文件，<code>Public</code>保存.h文件，将这些文件夹直接合并到自己工程中即可使用。

-----

## 更新
当前属于测试版本V0.2B，但也可使用，移植了1号实例容器总计4个可调用基本操作方法，不过销毁后处理事件还未能正常工作。

下一步移植2号实例类库，总计11个操作方法。

进度5% - 4/31个文件 - 1/37个目标

-----

## 文件
在<code>Private</code>和<code>Public</code>下都有同名的文件夹，每组同名文件夹内都是代表含有同一个功能的全部组件集合。

> <code>GeneralPlugLibrary</code> 通用插件库
>> <code>ItemManagementComponent</code> 物品管理组件
>>> <code>1_InstanceContainer</code> 实例容器，顺序1，只存放有效实例，当实例销毁时，容器也一同更新。



-----

## 报错

如果直接移植报错与类相关，可能是由于API没有改为合适的项目， 可以在<code>class <code>your project name</code>_API UItemManagementComponent : public UActorComponent</code>的<code>your project name</code>处填入自己工程的名字，如果还是不对可以自己新建文件一个看看名字？

如果编译时发现函数目标从组件应有的命名变为<code>LIVE CODE</code>开头的命名；或是发现调用时根本找不到函数，请立即重启并从引擎编译，确保可以看到c++内容时再打开文件；如果发现文件已经从图标变为文本，说明文件已经丢失了c++类，此时可以在编译完后打开并手动恢复先前的状态；想要预防这类事件，需要避免在引擎未开启时对源文件的改动，对脏文件保存也不行，可以等待引擎编译完成后再进行保存。
