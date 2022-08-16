<a name="title"></a>
# 通用操作库

[项目链接](#https://github.com/2128cz/UE_PortableLibrary)

&nbsp;

**目录**
> 1. [文件结构](#file)
>> [物品管理组件函数列表](#ItemManagementComponent)  
>> [逻辑收发集成组件使用](#TriggerTransceiverIntegraionComponent)
> 1. [如何使用]（#HowToUse）
> 1. [更新](#update)
> 1. [已知错误](#knowbug)
> 1. [如何解决报错](#error)

点击[超链接](#file)即可跳转到其标题位置哦

缓慢更新中。。。

&nbsp;

-----

<a name="file"></a>
## 文件结构

> <code>GeneralPlugLibrary</code> *通用插件库*  
>> <code>[ItemManagementComponent](#ItemManagementComponent)</code> 物品管理组件 ✔
>>> 动态物品管理，静态物品管理，多形体碰撞管理，指令框选管理，物品条目布尔操作等  
>>>  &nbsp;
>>>  
>> <code>TimeStopComponent</code> 时停组件 🕑  
>>> 用于不同的时停策略，和引擎暂停类似，可以在确保全局物理正确的情况下排除任意对象制造时间膨胀，近似时停。  
>>>  &nbsp;  
>>>  
>> <code>VectorTrackingComponent</code> 角色矢量追踪 🕑  
>>> 检测角色运动轨迹，并在各个阶段产生回调事件，但与移动组件自带的到达跳跃顶点的稍微有点不同。  
>>>  可以检测运动矢量是否由重力主导，检测运动矢量沿重力平面翻转。
>>>  &nbsp;  
>>>  
>> <code>RandomNoiseExtractionSeparation</code> 抖动矢量追踪 🕑
>>> 用于手柄角速度传感器复用输入，通过信号抖动与否来区分是否正在使用传感器输入，将手柄的挥舞动作作为事件输出，比如上下左右挥动，但考虑到性能问题，可能做不了更复杂的动作，比如画圆，画三角等；  
>>> 复用输入是指这条信号通道（2d向量）上同时有多个输入设备，比如鼠标，手柄摇杆，手柄角速度传感器，键盘方向键等，将传感器信号与其他所有信号区分开就是它的工作了；
>>> 一般只是用来区分摇杆，鼠标和角速度，其中鼠标的输入较大时，对输出影响也较大，。
>>>  &nbsp;
>>>
>> <code>AnimationPhysicsEffectorComponent</code> 动画驱动物理现象 🕑
>>> 可以代替物理模拟引擎完成在固定运动对象与模拟运动对象交互时的运动解算，并模拟弹性，柔性运动，使得元素运动更“视觉合理”； 
>>> 但此运动模拟仅在二维方向上有效，且需要使用Damage服务来触发动画，需要在一定程度上修改已有代码才能够正常运行，除此之外其他事件比如平台转移则已经存在方法解决。
>>>  &nbsp;  
>>>  
>> <code>[TriggerTransceiverIntegraionComponent](#TriggerTransceiverIntegraionComponent)</code> 逻辑收发集成组件 ❗
>>> 使用逻辑类似PLC指令表，可以使用LD,LDI,OUT,INV,AND,ANI,OR,ORI,ANB,ORB,XOR,NOR,END,NOE这些基础指令与其他触发器组成指令结构，
>>> 支持带有同类组件，触发器类，触发接口的方式设定指令，
>>> 基于plc指令的特性可以完成一系列的与或非，块与或非，基本大概也许我想可以囊括所有常用指令，关于如何编写PLC指令可以自行在网上搜索。  
>>> 为了避免发生无限循环，由指令表产生的输出不会通过设置指令触发其他指令表的计算，而是偷偷赋值。  
>>> 如果有必要进行多表协同计算，那么可以开启“针对无限循环优化”，这会将触发指令转到task上，等待全局同步结束后再一起计算，相应的，这会大幅提高响应时间。
>>>  &nbsp;  
>>>  
>> <code>DebugPrintTool</code> 调试信息绘制工具 🕑  
>>> 扩展调试绘制信息，可以绘制扭转箭头，绘制变换矩阵，绘制简单视锥，绘制虚线，绘制抛物线。  
>>>  &nbsp;  
>>>

&nbsp;

-----

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
>> <code>nope</code>
>>  &nbsp;  
>>  

之所以用数字做名字是因为函数有点多，名称不好区分，在搜索函数时可以直接用数字找到函数，还挺方便的。  

🔼[回到顶部](#title)

&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;

<a name="TriggerTransceiverIntegraionComponent"></a>
### 逻辑收发集成组件使用

Add this component where you want to use it, and the rest of the operations can be set directly from the details panel

* How to use  
直接添加到组件列表中，并点击该组件进入组件细节面板，在组件细节面板中找到
<code>接收与逻辑</code>
，在该折叠标题下可以看到当前默认的逻辑状态和逻辑流程；  
默认逻辑为真，逻辑流程为空，这代表此组件现在仅作为
<code>触发器信号</code>
使用，如果在此组件列表中存在其他触发器组件，那么此组件会自动绑定到此触发器，否则需要额外使用逻辑来使用
<code>触发信号</code>
；  

* How to use Logical flow sheet  
A logical flow sheet uses an
<code>instruction + target</code>
structure, where the target can be empty and the component automatically fills in itself as the target；    
&nbsp;

* Order List

| Order | instruction                                                                                                                          | Target            | Description                                                                                                  |
|-------|--------------------------------------------------------------------------------------------------------------------------------------|-------------------|--------------------------------------------------------------------------------------------------------------|
| LD    | Load the target logic and connect it directly to the bus                                                                             | necessary / self  | The LD can be used anywhere to create a new bus,All the instructions after that are on this new bus          |
| LDI   | Same as the LD instruction, but inverts the Load logic                                                                               | necessary / self  | Same as the LD                                                                                               |
| OUT   | Output the result of the current process or instruction block                                                                        | necessary / self  | The output does not indicate the end of the program, and you can still do other things after that            |
| INV   | inverts pointer logic                                                                                                                | ignore            | pointer logic mean The logic on a pointer when a program pointer runs from top to bottom to the current line |
| AND   | The output is true only if both the target logic and the pointer logic are true, otherwise any two are false and the output is false | necessary / self  |                                                                                                              |
| ANI   | Same as the AND instruction, but inverts the Target logic                                                                            | necessary / self  |                                                                                                              |
| ANB   | If there are more than one bus, this instruction will AND the existing pointer logic to the last instruction of the root bus         | ignore            |                                                                                                              |
| OR    | If either of the target logic or pointer logic is true, the output is true                                                           | necessary / self  |                                                                                                              |
| ORI   | Same as the OR instruction, but inverts the Target logic                                                                             | necessary / self  |                                                                                                              |
| ORB   | If there are more than one bus, this instruction will OR the existing pointer logic to the last instruction of the root bus          | ignore            |                                                                                                              |
| XOR   | Xor with the target logic                                                                                                            | necessary / self  |                                                                                                              |
| NOR   | Nor with the target logic                                                                                                            | necessary / self  |                                                                                                              |
| END   | Normally, you don't need to use this instruction, it's automatically added to the end of the program                                 | ignore            |                                                                                                              |
| NOE   | Empty command, ignore the target here                                                                                                | ignore            |                                                                                                              |

使用英文只是为了表格的格式好看(身心愉悦)  
如果英文有错误或有误区的地方，请务必告知于我。  
Please let me know if there are any grammatical errors or misunderstandings in the English instructions.

* 程序报错


&nbsp;


<a name="HowToUse"></a>
## 如何使用



🔼[回到顶部](#title)

&nbsp;

-----

<a name="update"></a>
## 更新

欸嘿，还没动笔呢

&nbsp;

<a name="knowbug"></a>
## 已知错误


&nbsp;

<a name="error"></a>
## 解决报错

* 如果直接移植报错与类相关，可能是由于类名没有改为合适的项目， 可以在<code>class <code>your project name</code>_API UItemManagementComponent : public UActorComponent</code>的<code>your project name</code>处填入自己工程的名字，如果还是不对可以自己新建文件一个看看名字？  

* 如果发现文件已经从图标变为文本，说明已经丢失了c++类，不过不要着急打开确认，此时打开的话找不到的目标就会成为既定事实，你可以等待重新编译完成并通过后，再检查文件目标是否恢复，一般此时文件目标会恢复；
不过如果编译时发现函数目标从组件应有的命名变为<code>LIVE CODE</code>开头的命名；或是发现调用时根本找不到函数，这时通常指向已经偏离，无法使用通常手段进行恢复，不过此类事件发生的几率较小，不需要太过担心。

* 如果编译时发现一直提示一个固定的错误，怎么也改不掉，错误行也不变，可以在编译文件目录下试着找找是否存在<code>.history</code>文件，清空里面的内容即可。

* 如果委托绑定提示签名不对，可以尝试直接产生事件。