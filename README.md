<a name="title"></a>
# 通用操作库  

[](#https://github.com/2128cz/UE_PortableLibrary)

&nbsp;

**目录**
> 1. [文件结构](#file)
>> [物品管理组件函数列表](#ItemManagementComponent)  
>> [逻辑收发集成组件使用](#TriggerTransceiverIntegraionComponent)
> 2. [更新](#update)
> 1. [如何解决报错](#error)

点击[超链接](#file)即可跳转到其标题位置哦

更新中。。。

&nbsp;

<a name="file"></a>
## 文件结构

> ## 源码目录
> <code>GeneralPlugLibrary</code> *通用插件库*  
>> <code>[ItemManagementComponent](#ItemManagementComponent)</code> 物品管理组件 ✔
>>> 动态物品管理，静态物品管理，多形体碰撞管理，指令框选管理，物品条目布尔操作等  
>>>  &nbsp;
>>>   
>> <code>RandomNoiseExtractionSeparation</code> 抖动矢量追踪 🕑
>>> 用于手柄角速度传感器复用输入，通过信号抖动与否来区分是否正在使用传感器输入，将手柄的挥舞动作作为事件输出，比如上下左右挥动，但考虑到性能问题，可能做不了更复杂的动作，比如画圆，画三角等；  
>>> 复用输入是指这条信号通道（2d向量）上同时有多个输入设备，比如鼠标，手柄摇杆，手柄角速度传感器，键盘方向键等，将传感器信号与其他所有信号区分开就是它的工作了；
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
>>>  &nbsp;  
>>>  
>> <code>DebugPrintTool</code> 调试信息绘制工具 🕑  
>>> 扩展调试绘制信息，可以绘制扭转箭头，绘制变换矩阵，绘制简单视锥，绘制虚线，绘制抛物线。  
>>>  &nbsp;  
>>>
>>  <code>[NiagaraSample](#NiagaraSample)</code>粒子系统示例 ❗
>>> 一些流体模拟系统。  
>>>  &nbsp;
>>>
> 
&nbsp;

-----

<a name="ItemManagementComponent"></a>
### 物品管理组件函数列表  

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

#### 如何使用

&nbsp;

你可以通过这张图片看到全部函数的列表，也可以在上方的函数列表来获取更多详细信息

<img src="https://github.com/2128cz/UE_PortableLibrary/blob/main/Resources/IMCAllBPFuncList.png?raw=true" />

其他功能并没有什么很不得了的地方，此组件的主要功能是用来代替常规的框选操作，完成框选的函数全部来自于4号和5号容器  
框选的节点看起来像这样：

<img src="https://github.com/2128cz/UE_PortableLibrary/blob/main/Resources/IMCBPShow1.png?raw=true" />
<img src="https://github.com/2128cz/UE_PortableLibrary/blob/main/Resources/IMCBPShow2.png?raw=true" />

其中左侧输入来自<code>Receive Draw HUD</code>，但无需担心重复调用，左上角的宏仅用作后续的选框绘制，而接入鼠标按键的目的是在合适的时机进行绘制并共享局部变量。  
需要注意的是，在现在的插件中的程序很可能与图片中展示的节点有所不同，比如我取消了对<code>布尔容器4</code>的自动清理选项，因为一般情况下对此进行操作显得毫无意义；  
以上节点使用少量的功能即可完成框选功能，此时你可以在<code>布尔容器4</code>中找到所有已框选的对象，而<code>即时容器5</code>的作用是可以在框选中对框选下的对象进行浏览；
如果此时使用调试，或是用高亮显示的方式来进行查看，会发现框选的对象向释放后框选对象进行转变时会额外产生一次事件，为了消除这个事件，需要用到<code>即时容器5</code>的传送功能，
作为传送的对象可以在转移到<code>布尔容器4</code>时避免产生事件，同时彻底清除遗留在<code>即时容器5</code>的引用，就像这样：

<img src="https://github.com/2128cz/UE_PortableLibrary/blob/main/Resources/IMCEm1.png?raw=true" />

这之后就可以进行类似这样的操作了：

<img src="https://github.com/2128cz/UE_PortableLibrary/blob/main/Resources/IMCSelect.png?raw=true" />

以上节点示例可以在文件中找到，仅提供思路。

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

* 此逻辑表程序指令几乎在任何情况下都能使用，只有极少部分情况下会产生报错，程序的错误不会产生任何不利的影响，也不会影响其他程序运行；  
* 指令的目标可以空置，带有<code>self</code>标记的指令将会在没有目标时使用自身作为目标；  
* 如果你的使用场景含有：可能存在的循环引用、被多个逻辑表指向的逻辑表之类多个输入多输出的结构，那么这时应该开启“针对无限循环优化”，你不需要将所有表格都开启优化选项，其他引用这张表的逻辑表会自动同步这项功能；  
无限循环优化将赋值事件延后，并在全局等待触发，避免在一个时刻内产生大量的往复调用，这个时间默认为500ms；
而这段时间内如果还有其他赋值事件，则会全部记录，并按指定（与，或，最后时刻）运算，这是因为如果需要条件逻辑可以使用取指令，而不是赋值指令。  

&nbsp;  

#### 编写指令时需要注意的事项：

1. 不明确的赋值顺序，目标不能作为公共变量使用

| Order | Target  |
|-------|---------|
| LD    |         |
| OUT   | Target1 |
| ...   |         |
| LD    | Target1 |
| ANB   |         |
| OUT   |         |

这样写指令结构并无错误，所以不会报错，但如果当前组件模式是<code>优化循环引用模式</code>，第二个<code>LD command</code>读取的就是没有被<code>OUT command</code>赋值的状态；  
相反，如果<code>未开启优化循环引用模式</code>，第二个<code>LD command</code>读取的就是<code>OUT command</code>赋值后的状态；  

&nbsp;

2. 关于优化循环引用模式  

考虑到运行中途如果检测到循环引用后导致<code>优化循环引用模式</code>的变更会很突兀，所以如果用户使用转义程序动态添加程序后，
需要手动顺序调用<code>初始化逻辑表</code><code>检查指令循环引用</code>这两个函数，并检查指定深度的循环引用  

    如果没有额外定义，那么组件默认只检查1个深度的循环引用，它的本质就是广度优先的树状递归，
    深度不能太大，以免检查的太频繁反而被引擎断言；

    当然更简单的方式是将父类的 BeginPlay 用作初始化使用，
    父类函数其实可以在子类的任何地方进行调用，也可以调用多个父类函数，作为用户检测方案也是一个不错的选择。

当然如果不需要组件运算的实时性的话，可以直接将<code>检查指令循环引用</code>替换成<code>开启优化循环引用模式</code>。

&nbsp;

3. 无用的逻辑，可以使用<code>NOE</code>或<code>END</code>作为装饰命令被忽略

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

左边的指令等价于右边的指令

虽然逻辑表的运算开销很小，但我不建议在表格里出现冗长的无效命令并不是因为效率问题，而是可阅读性；  
当然就算写成左边表格的样式也没什么不对的，这点代码数量对性能影响微乎其微，只有当你的单个组件的代码数量接近8,000行时才应该注意性能问题；  
无效的原因是<code>Block command</code>是从自己往上找最近的一个<code>LD command</code>进行合并，就像编程语言中的括号一样一层一层包裹起来的，
而此处的<code>ANB command</code>只对应最后一个<code>LD command</code>，将其与第二个<code>LD command</code>后的程序进行块与，
从而达到<code>Target2</code><code>AND</code><code>Target3</code><code>AND</code><code>Target4</code>然后输出的结果。  

可能还有一些没能想到的情况，但是不要紧，逻辑表的原理十分简单，无论是自己动手修改，或是使用其他逻辑代替都是完全没有问题的；  
所用到的知识应该与PLC的编程指令一样，我就不过多赘述了。

&nbsp;

4. 尽量避免利用循环引用制作触发器，寄存器，定时器，同时也注意逻辑死区  

如果可以的话，可以选择重载一个基于此组件的类，并移除掉父类的<code>BeginPlay</code>和<code>Tick</code>节点，这样父类会失去定时基础触发基础；  
只要保持子类的逻辑表内容干净，一般其他引用到此的逻辑表不会无故开启<code>优化循环引用模式</code>。  
再利用<code>布尔变量:逻辑状态</code>获取外部更改到此处的状态，理论上你可以继续扩展你的功能！

##### 如何创建一个锁存器：  

创建6个已经包含逻辑组件的<code>Actor</code>并放置在场景中，分别命名为
<code>R_Target</code><code>S_Target</code><code>Logic1_Target</code><code>Logic2_Target</code><code>Q_Target1</code><code>Q_Target2</code>
在这两个<code>Logic_Target</code>中分别写入逻辑：

| Order | Target    |     | Order | Target    |
|-------|-----------|-----|-------|-----------|
| LD    | R_Target  |     | LD    | S_Target  |
| OR    | Q_Target2 |     | OR    | Q_Target1 |
| INV   |           |     | INV   |           |
| OUT   | Q_Target1 |     | OUT   | Q_Target2 |

需要注意的是，这个操作由于并没有循环引用，是比较安全的操作，不过由于需要额外的触发更新逻辑，所以可能需要<code>开启优化循环引用模式</code>；  
否则这样的逻辑一般就只能运行一次了，这种外部无论如何都无法触发更新的状态，我称呼为逻辑死区。

| Order | Target        |     | Order | Target          |
|-------|---------------|-----|-------|-----------------|
| LD    | R_Target      |     | LD    | S_Target        |
| OR    | Q_Target2     |     | OR    | Q_Target1       |
| INV   |               |     | INV   |                 |
| OUT   | Q_Target1     |     | OUT   | Q_Target2       |
| NOE   | Logic2_Target |     | NOE   | Logic1_Target   |

你可以在表中添加装饰指令来强制表<code>开启优化循环引用模式</code>，这样无论如何都不会进入逻辑死区。  
装饰指令虽然会被忽略执行，但目标依然会作为引用进行计数，所以可以帮助我们脱离逻辑死区。

🔼[回到顶部](#title)

&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;  
&nbsp;

<a name="NiagaraSample"></a>
### 逻辑收发集成组件使用


🔼[回到顶部](#title)





-----

<a name="update"></a>
## 更新

变成插件乐（  

(0/1) 节点示例

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