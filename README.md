<a name="title"></a>
# 通用操作库

[项目链接](#https://github.com/2128cz/UE_PortableLibrary)  

文件分为<code>Private</code>和<code>Public</code>两个文件夹；  
其中<code>Private</code>保存.cpp文件，<code>Public</code>保存.h文件，将这些文件夹直接合并到自己工程中即可使用。  

&nbsp;

**目录**
> 1. [文件结构](#file)
>> [物品管理组件函数列表](ItemManagementComponent)
> 1. [更新](#update)
> 1. [已知错误](#knowbug)
> 1. [解决报错](#error)

点击[超链接](#file)即可跳转到其标题位置哦

&nbsp;

<a name="file"></a>
## 文件结构

在<code>Private</code>和<code>Public</code>下都有同名的文件夹，每组同名文件夹内都是代表含有同一个功能的全部组件集合。  

> <code>GeneralPlugLibrary</code> *通用插件库*  
>> <code>[ItemManagementComponent](#ItemManagementComponent)</code> 物品管理组件 💬  
>>> 管理物品，完成背包，多形体碰撞，框选命令，布尔选择等  
>>>  &nbsp;  
>>>  
>> <code>SimpleTraceComponent</code> 简易射线追踪 🕑  
>>> 翻越检测，多形体测量等方法  
>>>  &nbsp;  
>>>  
>> <code>TimeStopComponent</code> 时停组件 🕑  
>>> 用于不同的时停策略，和引擎暂停类似，可以在确保全局物理正确的情况下排除任意对象制造时停。  
>>>  &nbsp;  
>>>  
>> <code>VectorTrackingComponent</code> 矢量追踪 🕑  
>>> 检测角色运动轨迹，并在各个阶段产生回调事件，但与移动组件自带的到达跳跃顶点的稍微有点不同。  
>>>  可以检测运动矢量是否由重力主导，检测运动矢量沿重力平面翻转。
>>>  &nbsp;  
>>>  
>> <code>AnimationPhysicsEffectorComponent</code> 动画驱动物理现象 🕑  
>>> 模拟弹性，柔性运动解算，驱动被动场景元素与主动运动元素交互时“视觉合理”的运动解算；由于仅使用交互距离，弹性趋势等一维浮点参数计算，不能替代真实物理解算。  
>>>  比如可以用在踩踏的活动平台，可以跟随踩踏者的重量，与支点距离来计算旋转与偏移幅度，并根据运动惯性施加弹跳等现象。
>>>  &nbsp;  
>>>  
>> <code>TriggerTransceiverIntegraionComponent</code> 逻辑收发集成组件 🕑  
>>> 类似PLC指令表，可以使用LD,LDI,OUT,INV,AND,ANI,OR,ORI,ANB,ORB,XOR,NOR,END,NOE这些基础指令与其他触发器组成指令结构，
>>> 支持带有同类组件，触发器类，触发接口的方式设定指令，
>>> 基于plc指令的特性可以完成一系列的与或非，块与或非，基本大概也许可以囊括所有常用指令，关于如何编写PLC指令可以直接在网上搜。  
>>>  &nbsp;  
>>>  
>> <code>DebugPrintTool</code> 调试信息绘制工具 🕑  
>>> 扩展调试绘制信息，可以绘制扭转箭头，绘制变换矩阵，绘制简单视锥，绘制虚线，绘制抛物线。  
>>>  &nbsp;  
>>>  
>> ItemManagementComponentNode.txt 
>>> [ItemManagementComponent](#ItemManagementComponent)的所有节点，全选复制到蓝图中即可。  
>>>  &nbsp;  
>>>  

&nbsp;

<a name="ItemManagementComponent"></a>
### 物品管理组件函数列表

因为这个组件属于函数库性质的操作，所以这里将所有可调用的函数列举出来，便于调用。  

> <code>TESTFUNC</code> 测试事件，可重载无返回值  
> <code>1_InstanceContainer</code> *1号实例容器*  
>  
>  设计用于纯实例对象加入或移除，依赖于运行中的实例;  
>  如果某实例在这之后被销毁，那么将会自动清理废引用，并产生一个发生销毁事件  
>> <code>bool V1_AddActorByInst(AActor* ActorInstance)</code> 向容器1添加一个实例  
>>  &nbsp;  
>> <code>bool V1_RemoveActorByInst(AActor* ActorInstance)</code> 在容器1中移除一个对象实例  
>>  &nbsp;  
>> <code>TArray<AActor*> V1_GetActorInst()</code> 获取容器集合  
>>  &nbsp;  
>> <code>void V1_CleanActorInst()</code> 清空容器  
>>  &nbsp;  
>> <code>OnV1DestructionArrive</code> 容器1内发生融毁事件时  
>> 定义句柄在`.h`文件的开头处，现在调用会崩溃，所以还没用。
>>  &nbsp;  
>  
> <code>2_ClassContainer</code> *2号类容器*  
>  
>  存储类对象，最好在存储后进行移除，否则有可能造成多次加入  
>  在添加时勾选“添加时移除实例”即可。针对有可能使用索引回调的控件事件，提供了按索引更新的函数
>> <code>bool V2_AddAClassByInst(AActor* ActorInstance, bool AndDestroy)</code> 对象类容器2按实例添加  
>>  &nbsp;  
>> <code>bool V2_RemoveAClassByInst(AActor* ActorInstance)</code> 对象类容器2按实例移除  
>>  &nbsp;  
>> <code>void V2_AddAClassByClass(UClass* ActorClass, int32 Number)</code> 对象类容器2按类增加  
>>  &nbsp;  
>> <code>void V2_RemoveAClassByClass(UClass* ActorClass, int32 Number)</code> 对象类容器2按类减少  
>>  &nbsp;  
>> <code>void V2_SetAClassByClass(UClass* ActorClass, int32 Number, bool SetNumber)</code> 对象类容器2按类设置  
>>  &nbsp;  
>> <code>void V2_AddAClassByIndex(int32 Index, int32 Number)</code> 对象类容器2按索引增加  
>>  &nbsp;  
>> <code>void V2_RemoveAClassByIndex(int32 Index, int32 Number)</code> 对象类容器2按索引减少  
>>  &nbsp;  
>> <code>void V2_SetAClassByIndex(int32 Index, int32 Number, bool SetNumber)</code> 对象类容器2按索引设置  
>>  &nbsp;  
>> <code>bool V2_GetAClassByInst(AActor* ActorClass, int32& Number)</code> 按实例获取对象类容器2内容  
>>  &nbsp;  
>> <code>bool V2_GetAClassByClass(UClass* ActorClass, int32& Number)</code> 按类获取对象类容器2内容  
>>  &nbsp;  
>> <code>bool V2_GetAClassByIndex(int32 Index, UClass*& ActorClass, int32& Number)</code> 按索引获取对象类容器2内容  
>>  &nbsp;  
>  
> <code>3_SingleContainer</code> 3号独有容器  
>  
>  只存储一个对象，但可以用于有多形体碰撞的情况  
>  通过勾选“当插槽为空时添加”选项，限制加入的对象，并且在移除时，可以只针对插槽内的对象，也就是说可以和插槽1放置在一起使用。  
>> <code>void V3_AddSingleInst(AActor* ActorClass, bool Focus)</code> 添加实例到独有容器3
>>  &nbsp;  
>> <code>void V3_RemoveSingleInst(AActor* Actor)</code> 移除独有容器3的实例
>>  &nbsp;  
>> <code>void V3_CleanSingleInst()</code> 清空独有容器3
>>  &nbsp;  
>> <code>bool V3_GetSingleInst(AActor*& Actor)</code> 获取独有容器3的实例
>>  &nbsp;  
>>  
> <code>4_BooleanContainer</code> 4号布尔容器  
>  
>  一次性存储多个对象，可以用于玩家框选时的操作  
>  并且针对框选，框选组布尔，编组等操作封装了特有函数，其主要操作功能和插槽1基本类似。  
>>  &nbsp;  
>> <code>bool V4_AddActorInst(AActor* Actor)</code> 按实例添加到布尔容器4
>>  &nbsp;  
>> <code>bool V4_RemoveActorInst(AActor* Actor)</code> 按实例移除布尔容器4
>>  &nbsp;  
>> <code>bool V4_AddActorInstArray(TArray<AActor*> Actors)</code> 按实例组添加布尔容器4
>>  &nbsp;  
>> <code>bool V4_RemoveActorInstArray(TArray<AActor*> Actors)</code> 按实例组移除布尔容器4
>>  &nbsp;  
>> <code>bool V4_SetActorInstArray(TArray<AActor*> Actors)</code> 替换布尔容器4
>>  &nbsp;  
>> <code>bool V4_FuncIntersection(TArray<AActor*> Actors, bool AndKeepSave, TSet<AActor*>& Output)</code> 交集操作布尔容器4
>>  &nbsp;  
>> <code>bool V4_FuncUnion(TArray<AActor*> Actors, bool AndKeepSave, TSet<AActor*>& Output)</code> 并集操作布尔容器4
>>  &nbsp;  
>> <code>bool V4_FuncDifference(TArray<AActor*> Actors, bool AndKeepSave, TSet<AActor*>& Output)</code> 差集操作布尔容器4
>>  &nbsp;  
>> <code>TArray<AActor*> V4_GetActorArray()</code> 获取对象组布尔容器4
>>  &nbsp;  
>> <code>bool V4_CleanContainer()</code> 清空布尔容器4
>>  &nbsp;  
>> <code>bool V4_FuncIsArrayForTransfer(TArray<AActor*> Actors, float Threshold, TArray<AActor*>& ValidTrans, TArray<AActor*>& OtherTrans)</code> 校验输入是为传送布尔容器4
>>  &nbsp;  
>> <code>bool V4_FuncIsActorForTransfer(AActor* Actor)</code> 校验传送对象布尔容器4
>>  &nbsp;  
>> <code>OnV4DestructionArrive</code>容器4内发生融毁事件时
>>  &nbsp;  
>> <code>OnV4ChangeArrayMore</code>容器4内发生内容变更时_增加组
>>  &nbsp;  
>> <code>OnV4ChangeArrayLess</code>容器4内发生内容变更时_减少组
>>  &nbsp;  
>>  
> <code>5_ImmediatelyContainer</code> 5号即时容器  
>  
>  用于检测时多对象内容发生变更的对象，并产生相应事件；  
>  此插槽可以用来保存对象，但并不固定，且没有清理计划，不建议从此处获取持久引用。  
>  主要功能和插槽4类似；独立使用时可以用分发器获取物品变动。  
>  如需和插槽4配合使用，可以使用特别封装的传送函数，将减少移动物品引用时变更分发器事件的发生；  
>  更新时如果需要忽略浏览的高亮事件作用于已选择的对象（指插槽4中的内容），勾选忽略选项即可。  
>  当前版本的传送后回收功能受插槽4的自动清理功能限制，会在不自动清理时不检查传送内容，导致回收站保持内容，本意是可以通过不清理来执行多次运算。  
>>  &nbsp;  
>> <code>void V5_UpdataSizer(TArray<AActor*> TargetActors, bool IgoneVes4, TArray<AActor*>& ExcrActors, TArray<AActor*>& MissActor)</code> 更新对象组筛选器即时容器5  
>>  &nbsp;  
>> <code>TArray<AActor*> V5_OnTransmit()</code> 传送即时容器5
>>  &nbsp;  
>> <code>void V5_Clean()</code> 清除即时容器5
>>  &nbsp;  
>> <code>TArray<AActor*> V5_GetActors()</code> 获取即时容器5
>>  &nbsp;  
>> <code>bool V5_RecoveryTransferData()</code> 取消传送即时容器5
>>  &nbsp;  
>> <code>OnV5ChangeArrayMore</code>容器5内发生内容变更时_增加组
>>  &nbsp;  
>> <code>OnV5ChangeArrayLess</code>容器5内发生内容变更时_减少组
>>  &nbsp;  
>>  
> <code>5_ImmediatelyContainer</code> 框选行为示例  
> 
>> <code></code>
>>  &nbsp;  
>>  

之所以用数字做名字是因为函数有点多，名称不好区分（记不住🙄），在搜索函数时可以直接用数字找到函数，还挺方便的。  

🔼[回到顶部](#title)

&nbsp;

<a name="update"></a>
## 更新

物品管理组件移植完毕，基本能实现功能

&nbsp;

<a name="knowbug"></a>
## 已知错误

1号实例库的实例销毁后处理事件不能正常工作。  

&nbsp;

<a name="error"></a>
## 解决报错

如果直接移植报错与类相关，可能是由于类名没有改为合适的项目， 可以在<code>class <code>your project name</code>_API UItemManagementComponent : public UActorComponent</code>的<code>your project name</code>处填入自己工程的名字，如果还是不对可以自己新建文件一个看看名字？  

如果编译时发现函数目标从组件应有的命名变为<code>LIVE CODE</code>开头的命名；或是发现调用时根本找不到函数，请立即重启并从引擎编译，确保可以看到c++内容时再打开文件；如果发现文件已经从图标变为文本，说明文件已经丢失了c++类，此时可以在编译完后打开并手动恢复先前的状态；想要预防这类事件，需要避免在引擎未开启时对源文件的改动，对脏文件保存也不行，可以等待引擎编译完成后再进行保存。  

如果编译时发现一直提示一个固定的错误，怎么也改不掉，错误行也不变，可以在编译文件目录下试着找找是否存在<code>.history</code>文件，清空里面的内容即可。

如果委托绑定提示签名不对，可以尝试直接产生事件。