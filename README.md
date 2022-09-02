<a name="title"></a>
# 通用操作库  

[](#https://github.com/2128cz/UE_PortableLibrary)

**使用须知**  
仅包含源码，使用前需要自行生成反射和插件项目结构。  



&nbsp;

**目录**
> 1. [文件结构](#file)
> 1. [物品管理组件函数列表](#ItemManagementComponent)  
> 1. [逻辑收发集成组件使用](#TriggerTransceiverIntegraionComponent)  
> 1. [任务系统](#NiagaraSample)
> 1. [更新](#update)
> 1. [如何解决报错](#error)

点击[超链接](#file)即可跳转到其标题位置哦

更新中。。。

&nbsp;

<a name="file"></a>
# 文件结构  

**源码目录**  

> <code>Plugins</code>插件根目录
> &nbsp;
>> <code>GeneralPlugLibrary</code> **通用插件库** 插件文件
>>> <code>[ItemManagementComponent](#ItemManagementComponent)</code> 物品管理组件 ✔
>>>> 动态物品管理，静态物品管理，多形体碰撞管理，指令框选管理，物品条目布尔操作等  
>>>>  &nbsp;
>>>>
>>> <code>AnimationPhysicsEffectorComponent</code> 动画驱动物理现象 🕑
>>>> 可以代替物理模拟引擎完成在固定运动对象与模拟运动对象交互时的运动解算，并模拟弹性，柔性运动，使得元素运动更“视觉合理”； 
>>>> 但此运动模拟仅在二维方向上有效，且需要使用Damage服务来触发动画，需要在一定程度上修改已有代码才能够正常运行，除此之外其他事件比如平台转移则已经存在方法解决。
>>>>  &nbsp;  
>>>>  
>>> <code>[TriggerTransceiverIntegraionComponent](#TriggerTransceiverIntegraionComponent)</code> 逻辑收发集成组件 ❗
>>>> 使用逻辑类似PLC指令表，可以使用LD,LDI,OUT,INV,AND,ANI,OR,ORI,ANB,ORB,XOR,NOR,END,NOE这些基础指令与其他触发器组成指令结构，
>>>> 支持带有同类组件，触发器类，触发接口的方式设定指令，
>>>> 基于plc指令的特性可以完成一系列的与或非，块与或非，基本大概也许我想可以囊括所有常用指令，关于如何编写PLC指令可以自行在网上搜索。
>>>>  &nbsp;
>>>>
>>> <code>[CameraManagementPlug](#CameraManagementPlug)</code> 摄像机运动管理 ❗
>>>> 包含一个可以独立运动的摄像机，和多种运动数据重载体积。  
>>>>  &nbsp;
>>>>
> &nbsp;
>>  <code>[MissionSystems](#MissionSystems)</code>**任务系统** 插件文件 ❗
>>> 独特的资产系统，因为和库文件不是一类所以并没有作为一个插件下的两个模块进行创建。  
>>>  &nbsp;
>>>
> 
&nbsp;

-----

<a name="ItemManagementComponent"></a>
## 物品管理组件函数列表  

&nbsp;

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

&nbsp;

### 如何使用

&nbsp;

你可以通过这张图片看到全部函数的列表，也可以在上方的函数列表来获取更多详细信息

<img src="https://github.com/2128cz/UE_PortableLibrary/blob/main/Resources/IMCAllBPFuncList.png?raw=true" />

其他功能并没有什么很不得了的地方，此组件的主要功能是用来代替常规的框选操作，完成框选的函数全部来自于4号和5号容器  
框选的节点看起来像这样：

<img src="https://github.com/2128cz/UE_PortableLibrary/blob/main/Resources/IMCBPShow1.png?raw=true" />
<img src="https://github.com/2128cz/UE_PortableLibrary/blob/main/Resources/IMCBPShow2.png?raw=true" />

其中左侧输入来自<code>Receive Draw HUD</code>，但无需担心重复调用，左上角的宏仅用作后续的选框绘制，而接入鼠标按键的目的是在合适的时机进行绘制并共享局部变量。  

    需要注意的是，在现在的插件中的程序很可能与图片中展示的节点有所不同；
    比如我取消了对 布尔容器4 的自动清理选项，因为一般情况下对此进行操作显得毫无意义；  

以上节点使用少量的功能即可完成框选功能，此时你可以在<code>布尔容器4</code>中找到所有已框选的对象，而<code>即时容器5</code>的作用是可以在框选中对框选下的对象进行浏览；
如果此时使用调试，或是用高亮显示的方式来进行查看，会发现框选的对象向释放后框选对象进行转变时会额外产生一次事件，为了消除这个事件，需要用到<code>即时容器5</code>的传送功能，
作为传送的对象可以在转移到<code>布尔容器4</code>时避免产生事件，同时彻底清除遗留在<code>即时容器5</code>的引用，就像这样：

<img src="https://github.com/2128cz/UE_PortableLibrary/blob/main/Resources/IMCEm1.png?raw=true" />

这之后就可以进行类似这样的操作了：

<img src="https://github.com/2128cz/UE_PortableLibrary/blob/main/Resources/IMCSelect.png?raw=true" />

以上节点示例可以在文件中找到，仅提供思路，
像快捷键编组之类的功能之后再说吧。

&nbsp;

🔼[回到顶部](#title)

&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;

<a name="TriggerTransceiverIntegraionComponent"></a>
## 逻辑收发集成组件使用

你也可以直接查看[编写指令时需要注意的事项](#ToWriteCommandYouNeedKnow)  

Add this component where you want to use it, and the rest of the operations can be set directly from the details panel

* How to use  
直接添加到组件列表中，并点击该组件进入组件细节面板，在组件细节面板中找到
<code>接收与逻辑</code>
，在该折叠标题下可以看到当前默认的逻辑状态和逻辑流程；  
默认自身逻辑为真，逻辑流程为空，这代表此组件现在仅作为
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

| Order | instruction                                                                                                                          | Target            | Description                                                                                                   |
|-------|--------------------------------------------------------------------------------------------------------------------------------------|-------------------|---------------------------------------------------------------------------------------------------------------|
| LD    | Load the target logic and connect it directly to the bus                                                                             | necessary / self  | The LD can be used anywhere to create a new bus,All the instructions after that are on this new bus           |
| LDI   | Same as the LD instruction, but inverts the Load logic                                                                               | necessary / self  | Same as the LD                                                                                                |
| OUT   | Output the result of the current process or instruction block                                                                        | necessary / self  | The output does not indicate the end of the program, and you can still do other things after that             |
| INV   | inverts pointer logic                                                                                                                | ignore            | pointer logic mean The logic on a pointer when a program pointer runs from top to bottom to the current line  |
| AND   | The output is true only if both the target logic and the pointer logic are true, otherwise any two are false and the output is false | necessary / self  |                                                                                                               |
| ANI   | Same as the AND instruction, but inverts the Target logic                                                                            | necessary / self  |                                                                                                               |
| ANB   | If there are more than one bus, this instruction will AND the existing pointer logic to the last instruction of the root bus         | ignore            |                                                                                                               |
| OR    | If either of the target logic or pointer logic is true, the output is true                                                           | necessary / self  |                                                                                                               |
| ORI   | Same as the OR instruction, but inverts the Target logic                                                                             | necessary / self  |                                                                                                               |
| ORB   | If there are more than one bus, this instruction will OR the existing pointer logic to the last instruction of the root bus          | ignore            |                                                                                                               |
| XOR   | Xor with the target logic                                                                                                            | necessary / self  | Just like a conditional inverse fetch, you can invert pointer logic when your target is true                  |
| NOR   | Nor with the target logic                                                                                                            | necessary / self  | Contrary to XOR                                                                                               |
| END   | Normally, you don't need to use this instruction, it's automatically added to the end of the program                                 | ignore            | Manually added to a program forces the pointer to stop running                                                |
| NOE   | Empty command, ignore the target here                                                                                                | ignore            |                                                                                                               |

* 此逻辑指令来源于PLC指令，原理也基本一致，我认为直接查看PLC指令原理可以更好的学习；  
* 此逻辑表程序指令几乎在任何情况下都能使用，只有极少部分情况下会产生报错，程序的错误不会产生任何不利的影响，也不会影响其他程序运行（指不会崩溃）；  
* 指令的目标可以空置，带有<code>self</code>标记的指令将会在没有目标时使用自身作为目标；  
* 如果你的使用场景含有：可能存在的循环引用、被多个逻辑表指向的逻辑表之类多个输入多输出的结构，那么这时应该开启“针对无限循环优化”，
你不需要将所有表格都开启优化选项，其他引用这张表的逻辑表会自动同步这项功能；  
* 无限循环优化将赋值事件延后，并在全局等待触发，避免在一个时刻内产生大量的往复调用，这个时间默认为500ms；
而这段时间内如果还有其他赋值事件，则会按或运算。

&nbsp;  

<a name="ToWriteCommandYouNeedKnow"></a>
### 编写指令时需要注意的事项：

&nbsp;

* 不明确的赋值顺序，目标不能作为公共变量使用

| Order | Target  |
|-------|---------|
| LD    |         |
| OUT   | Target1 |
| ...   |         |
| LD    | Target1 |
| ANB   |         |
| OUT   |         |

这样写指令结构并无错误，所以不会报错，
但一个目标同时作为输入和输出进行操作时，为了规范取值方向，计算时的逻辑取值统一使用计算前的数值，不论当前状态如何；

&nbsp;

* 无用的逻辑，可以使用<code>NOE</code>或<code>END</code>作为装饰命令被忽略

| Order | Target  | ==> | Order | Target  |
|-------|---------|-----|-------|---------|
| LD    |         |     |       |         |
| OR    | Target1 |     |       |         |
| LD    | Target2 |     | LD    | Target2 |
| AND   | Target2 |     |       |         | 
| AND   | Target3 |     | AND   | Target3 |
| LD    | Target4 |     | LD    | Target4 |
| ANB   |         |     | ANB   |         |
| OUT   |         |     | OUT   |         |
| END   | Target4 |     | END   |         |
| LD    | Target5 |     |       |         |
| OUT   | Target1 |     |       |         |

**左边的指令等价于右边的指令**  
当然就算写成左边表格的样式也没什么不对的，这点代码数量对性能影响微乎其微；

&nbsp;

* 创建一个锁存器

创建6个已经包含逻辑组件的<code>Actor</code>并放置在场景中，分别取名为
<code>R_Target</code><code>S_Target</code><code>Logic1_Target</code><code>Logic2_Target</code><code>Q_Target1</code><code>Q_Target2</code>
（当然不改名字也行）  
在这两个<code>Logic_Target</code>中分别写入逻辑：

| Order | Target    |     | Order | Target    |
|-------|-----------|-----|-------|-----------|
| LD    | R_Target  |     | LD    | S_Target  |
| OR    | Q_Target2 |     | OR    | Q_Target1 |
| INV   |           |     | INV   |           |
| OUT   | Q_Target1 |     | OUT   | Q_Target2 |

需要注意的是，这个操作由于并没有循环引用，是比较安全的操作；

&nbsp;

* 避免利用循环引用制作触发器，寄存器，定时器

在上面的制作锁存器中，根据逻辑触发原理，想要更好的运行，你可以将<code>R_Target</code>中写一个取反的逻辑表用来设置<code>S_Target</code>的值保持反相，
而如果想要额外的逻辑时，可以选择重载一个基于此组件的类，并移除掉父类的<code>BeginPlay</code>和<code>Tick</code>节点，父类会因此失去定时基础触发基础，
这样你就获得一个和普通组件无异的逻辑表组件了。  
不过这样对于其他逻辑表来说并不公平，所以我推荐你可以重载以下函数：<code>逻辑状态取值</code>、<code>逻辑状态更新</code>、<code>指令表计算</code>，
以及事件<code>逻辑表触发更新</code>、<code>逻辑状态赋值</code>。  

&nbsp;


* 在运行中销毁逻辑表组件  

运行中的逻辑表如果仅销毁组件，或是连同继承者也一同销毁时，会导致其他逻辑表产生运行错误，此时会默认忽略错误继续执行，而错误的取值会为假；  
并会产生一个错误事件，以供运行中调用，

&nbsp;

🔼[回到顶部](#title)

&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;

<a name="CameraManagementPlug"></a>
## 摄像机运动管理器

摄像机运动管理器内容
1. [摄像机运行流程](#CamerasFlow)
1. [摄像机重载器](#CameraReloader)



<a name="CamerasFlow"></a>
### 摄像机运行流程  

摄像机运动管理需要多个组件相互配合才能运行，我将这些组件分为了几种类型：　　

* 摄像机目标类
* 跟随视图管理组件
* 追踪目标登记组件
* 视图重载器体积

对于各个想要运行的摄像机与体积重载器来说，有优先级和相关性两个等级约束；  
* 优先级将允许高优先的摄像机视图优先使用；  
* 相关性则允许同一个场景下有多个视图规则，且不同相关性的规则互不干扰；

摄像机对象的基本运行说需要配合`跟随视图管理组件`，放置在被控制的角色身上，即可将视图自动转移到目标摄像机上；  
但想要让摄像机能够被指定，需要先让摄像机指向角色，并在开始时请求角色控制；  
此时如果有多个摄像同时请求控制，则会按照相关性下的优先级进行排除，同一优先级下距离最近的摄像机将被启用。  

同时你也可以在任何任何地方使用<code>Get Player Camera Manager</code>来获取指定角色索引下的相机管理器，这会返回当前角色上的管理插件。  

摄像机的更多运行模式需要配合摄像机参数重载体积，

&nbsp;  

<a name="CameraReloader"></a>
### 摄像机重载器

管理器中自带几种基础的重载器：  

| 类型        | 权重  | 优先级 | 说明                                                                                                                                        |
|-----------|-----|-----|-------------------------------------------------------------------------------------------------------------------------------------------|
| 静态场景焦点    | 0.5 | 5   | 放置在场景中，不允许移动，通常情况下都应该优先考虑静态场景焦点;<br/>本身并无约束方法，但会提供一个权重焦点，在用户设定的权重下将按比例将摄像机向体积偏移。                                                          |
| 动态对象焦点    | 0.5 | 8   | 放置在场景中，本身不允许移动，但允许将指定目标的优先级作为自身优先级加入到焦点计算中;<br/>对突发事件，需要注意的动画事件等有独特的焦点转移方法;<br/>本身并无约束方法，也不会提供新的摄像机吸附，优先级也十分低，但如果遇到指定类的对象时，则会将对象的优先级赋予自己。 |
| 路径专注焦点    | 1   | 3   | 放置在场景中，不允许移动，如有时应当优先考虑此体积焦点，具有一个样条驱动的路径，摄像机进入时几乎由样条曲线约束。                                   |
| 状态重载体积    | N/A | 4   | 放置在场景中，原则上允许移动，仅重设参数，方法类似进出`PostProcessVolume`时的后处理效果。                                                                                    |
| 摄像机强制重载体积 | N/A | 3   | 放置在场景中，原则上允许移动；可以将角色视图强制重载到新的视图中，这通常使用在需要将视角切换到一个具体物体上时;<br/>也可以选择使用序列编辑器来作为新视图驱动，当序列播放完毕，或是定时结束时，将返还视图目标，除非这个视图目标指定了角色。                  |

* 重载器的范围可以为0，这是安全的操作。
* 路径重载器有两个模式，默认为最近流向坐标查找，可以切换为流向距离映射（流向是指摄像机在进入时，主要的运动方向，设定这个可以便于查找一个合理的最近样条点进行驱动）；
最近流向查找将通过指定的流向轴将最近的样条驱动点进行二次映射，找到一个垂直于流向轴的驱动点；  
而流向距离映射则可以按摄像机在体积内运行的距离映射到样条上，这样可以无视样条设定是否合理，解决一些特殊镜头约束要求。

&nbsp;

#### 重载摄像机重载器

继承重载体积只需要重载`关注点计算`函数即可，这个函数的作用是计算一个约束摄像机的关注点，输出时需要指定输出的空间

* 世界空间：输出基于世界原点
* 重载绝对空间：输出基于重载器根组件原点
* 重载相对空间：输出基于重载器重载体积原点
* 角色空间：输出基于角色世界空间
* 摄像机绝对空间：输出基于摄像机世界空间
* 摄像机相对空间：输出基于摄像机局部空间

默认为`世界空间`，使用错误的空间类型时，摄像机可能会产生错误的移位，抖动；  

重载重载器时可以自由设定自身的优先级，相关性等参数，由于重载器自身默认关闭了`tick`执行，所以需要自行开启；  
你可以重载体积碰撞事件，并调用其父项的方法来继承并扩展这个功能；  
但我更推荐使用`摄像机重载开始`和`摄像机重载结束`事件来实现，因为直接重载父方法并不能继承其原始的分支流程。

#### 摄像机专注于区域

重载器`静态场景焦点`已经实现了一个基础的专注于区域的流程，但这个会因为摄像机内部的混合权重而淡化效果，所以如果想要实现锁定摄像机在一个区域的效果，
可以将摄像机的混合权重设为0，让重载器焦点作为摄像机的主导元素，而不是角色；

但为了能够更方便的完成这一流程，重载器可以直接输出期望的混合权重到摄像机，当这个重载器为唯一正在启用的重载器时，这个`混合权重`将直接控制`摄像机混合权重`，
此时想要脱离控制，只有在重载器中返回`关注点有效`设为否，或是因为距离太远，受到`最大容许偏移`影响而拉回视图；  
因为`最大容许偏移`而拉回视图时可能会明显感觉到动画过度不自然，所以应当使用更为合理的运动路径。




&nbsp;

🔼[回到顶部](#title)

&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;

<a name="MissionSystems"></a>
## 任务系统
 
任务系统结构

任务系统用于管理世界时间线上的事件和任务，使用时间序列化任务节点，可以满足任务流程可视化的需求；  
任务系统和普通的对象类似，也可以通过继承来获取任务模板，并在任务大纲中使用纵向流程图进行流程控制。

1. [创建任务](#creatSystem)
2. [模板系统](#ReuseSystem)
3. [任务与蓝图](#MissionSystemAndBP)

&nbsp;

<a name="creatSystem"></a>
### 创建任务
。

&nbsp;

<a name="ReuseSystem"></a>
### 模板系统
。

&nbsp;

<a name="MissionSystemAndBP"></a>
### 任务与蓝图
。

&nbsp;

🔼[回到顶部](#title)

&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;

-----

<a name="update"></a>
## 更新

* 优化了逻辑表的读取操作，现在读取时不论双方是否已经完成运算，都会选择更稳定的值。
* 优化了逻辑表的更新行为，现在不会进入“逻辑死区”了。
* 优化了逻辑表的运算，默认情况下会使用响应更快速的渐稳触发，而不是同步触发。

&nbsp;

**代办事项**

* 逻辑收发集成组件 =>  蓝图已验证，等待性能验证。
* 等待蓝图功能检验通过。

&nbsp;

<a name="error"></a>
## 解决报错

* 如果直接移植报错与类相关，可能是由于类名没有改为合适的项目；  
可以在<code>class <code>your project name</code>_API U<code>your file name</code> : public U<code>your base class</code></code>中填入相应的名字;   
不过现在已经改为了插件形式了，应该不会有这样的错误了。  

&nbsp;  
* 如果发现文件已经从图标变为文本；  
说明已经丢失了c++类，不过不要着急打开确认，此时打开的话找不到的目标就会成为既定事实，你可以等待重新编译完成并通过后，再检查文件目标是否恢复，一般此时文件目标会恢复；  
没能自动恢复的话，就只能考虑手动重新写一遍了；  
不过如果编译时发现函数目标从组件应有的命名变为<code>LIVE CODE</code>开头的命名；或是发现调用时根本找不到函数，这时通常指向已经偏离，无法使用通常手段进行恢复，不过此类事件发生的几率较小，不需要太过担心。  

&nbsp;  
* 如果编译时发现一直提示一个固定的错误，怎么也改不掉，错误行也不变；  
可以在编译文件目录下试着找找是否存在<code>.history</code>文件，清空里面的内容即可。

&nbsp;  
* 组件存在分发器句柄，但不允许绑定，提示签名错误；  
可以直接使用添加事件解决，可能是因为已经在头文件中定义了句柄事件，所以不能绑定。  

&nbsp;
* 