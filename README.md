# 通用操作库
-----

文件分为<code>Private</code>和<code>Public</code>两个文件夹；

其中<code>Private</code>保存.cpp文件，<code>Public</code>保存.h文件，将这些文件夹直接合并到自己工程中即可使用。

-----

## 更新
当前属于测试版本V0.2B，但也可使用，移植了1号实例容器总计4个可调用基本操作方法，不过销毁后处理事件还未能正常工作。

下一步移植2号实例类库，总计11个操作方法。

进度13% - 4/31

-----

## 文件
在<code>Private</code>和<code>Public</code>下都有同名的文件夹，每组同名文件夹内都是代表含有同一个功能的全部组件集合。

> <code>GeneralPlugLibrary</code> 通用插件库
>> <code>ItemManagementComponent</code> 物品管理组件
>>> <code></code>



-----

## 报错

如果直接移植报错与类相关，可能是由于API没有改为合适的项目， 可以在<code>class <code>your project name</code>_API UItemManagementComponent : public UActorComponent</code>的<code>your project name</code>处填入自己工程的名字，如果还是不对可以自己新建一个看看名字？

如果编译时发现函数目标从组件应有的命名变为<code>LIVE CODE</code>开头的命名，重启即可后重编译即可。
