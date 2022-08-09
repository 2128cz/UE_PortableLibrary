<a name="title"></a>
# 通用操作库

文件分为<code>Private</code>和<code>Public</code>两个文件夹；

其中<code>Private</code>保存.cpp文件，<code>Public</code>保存.h文件，将这些文件夹直接合并到自己工程中即可使用。

&nbsp;

**小目录**
> 1. [文件结构](#file)
>>  [物品管理组件代码解释](ItemManagementComponent)  
> 1. [更新](#update)
> 1. [已知错误](#knowbug)
> 1. [解决报错](#error)

&nbsp;

<a name="file"></a>
## 文件结构

在<code>Private</code>和<code>Public</code>下都有同名的文件夹，每组同名文件夹内都是代表含有同一个功能的全部组件集合。

> <code>GeneralPlugLibrary</code> *通用插件库*  
>> <code>[ItemManagementComponent](#ItemManagementComponent)</code> 物品管理组件 (Wait)  
>>> 用于管理物品，完成背包，多形体碰撞，框选，布尔选择等  
>>>  &nbsp;
>>>  
>> <code>SimpleTraceComponent</code> 简易射线追踪 (shelve)  
>>> 用于翻越检测，多形体测量等方法  
>>>  &nbsp;
>>>  
>> <code>TimeStopComponent</code> 时停组件 (shelve)  
>>> 用于不同的时停策略，暂停游戏，仅暂停部分物理，排除部分对象暂停物理，和引擎暂停类似。  
>>>  &nbsp;
>>>  
>> <code>VectorTrackingComponent</code> 角色矢量追踪 (shelve)  
>>> 用于检测角色运动轨迹，并在各个阶段产生回调事件。  
>>>  &nbsp;
>>>  

&nbsp;

<a name="ItemManagementComponent"></a>
### 物品管理组件代码解释
> <code>1_InstanceContainer</code> *1号实例容器*  
>> 只存放有效实例，当实例销毁时，容器也一同更新。  
>>  &nbsp;
>>  
> <code>2_ClassContainer</code> *2号类容器*
>> 保存每个物品（类）的数量（值）。  
>>  &nbsp;
>>  
> <code>3_SingleContainer</code> 3号独有容器
>> 捕捉唯一的一个对象，凑数用的。  
>>  &nbsp;
>>  
> <code>4_BooleanContainer</code> 4号布尔容器
>> 可以用在框选事件后，直接进行布尔运算。  
>>  &nbsp;
>>  
> <code>5_ImmediatelyContainer</code> 5号即时容器
>> 用来作为回收站和筛选器。  
>>  &nbsp;
>>  
> <code>6_MapContainer</code> 6号映射容器
>> 好像就是一个单纯的映射？等我回忆一下吧……  
>>  &nbsp;
>>  

之所以用数字做名字是因为函数有点多，名称不好区分，在搜索函数时也可以直接用数字找到函数，还挺方便的。

&nbsp;

<a name="update"></a>
## 更新

当前属于测试版本V0.2B，但也可使用，从蓝图中移植了1号实例容器总计4个可调用基本操作方法，不过销毁后处理事件还未能正常工作。  
下一步移植2号实例类库，总计11个操作方法。  
进度5% - 4/31个文件 - 1/37个目标  

&nbsp;

<a name="knowbug"></a>
## 已知错误

1号实例库的实例销毁后处理事件不能正常工作。  

&nbsp;

<a name="error"></a>
## 解决报错

如果直接移植报错与类相关，可能是由于类名没有改为合适的项目， 可以在<code>class <code>your project name</code>_API UItemManagementComponent : public UActorComponent</code>的<code>your project name</code>处填入自己工程的名字，如果还是不对可以自己新建文件一个看看名字？  

如果编译时发现函数目标从组件应有的命名变为<code>LIVE CODE</code>开头的命名；或是发现调用时根本找不到函数，请立即重启并从引擎编译，确保可以看到c++内容时再打开文件；如果发现文件已经从图标变为文本，说明文件已经丢失了c++类，此时可以在编译完后打开并手动恢复先前的状态；想要预防这类事件，需要避免在引擎未开启时对源文件的改动，对脏文件保存也不行，可以等待引擎编译完成后再进行保存。  
