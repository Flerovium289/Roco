# C++模拟洛克王国

### 文件结构说明

`src`：通用基础文件

- `Pet.h`/`Pet.cpp`：宠物基础信息，包括六项能力面板、种族值、属性、天赋等

- `AbnormalState.h`/`AbnormalState.cpp`：异常状态类及其作用效果函数

- `CombatInfo.h`/`CombatInfo.cpp`：战斗类信息，包括强化等级、战斗标记（双损，禁疗等）

- `SkillEffect.h`/`SkillEffect.cpp`：技能效果类

- `Skill.h`/`Skill.cpp`：技能类，包括技能基本信息及其作用效果函数

- `WeatherEnvironment.h`/`WeatherEnvironment.cpp`：天气/环境类

- `CombatPet.h`/`CombatPet.cpp`：单只宠物的所有战斗信息

- `Player.h`/`Player.cpp`：玩家信息类，包括当前出战宠物下标、出战宠物信息等

- `Administrator.h/Administrator.cpp`：全局裁判类

  层级关系如下图：

<img src="D:\Programs\CFiles\Roco\文件结构.png" alt="文件结构" style="zoom:22%;" />

   

`PetInfo`：具体宠物信息

​	命名格式：宠物编号+宠物名称拼音

- `6HuoShen.h/6HuoShen.cpp`：火神具体信息

`SkillsInfo`：具体技能信息

- `BasicSkill.h`/`BasicSkill.cpp`：通用技能信息

### 对战逻辑

#### Step 0 基本框架

- `Administrator`：裁判，负责技能最终效果的判定

- `Player`：玩家
  - `CombatInfo`：当前出战宠物的作战信息，指向六只宠物中的某一只
  - `CombatInfo[6]`：背包里所有六只宠物的作战信息

- `WeatherEnvironment`：场上的天气/环境

  

<img src="D:\Programs\CFiles\Roco\对战逻辑0.png" alt="对战逻辑0" style="zoom:22%;" />



#### Step 1 玩家向裁判发送本回合技能速度，裁判综合各因素判定先手度

- 异常状态的影响
- 天气/环境的影响

<img src="D:\Programs\CFiles\Roco\对战逻辑1.png" alt="对战逻辑1" style="zoom:22%;" />



#### Step 2 先手玩家把技能效果封装成多个skill_effect，传给Administrator的消息队列

- 假设Player 1 先手

<img src="D:\Programs\CFiles\Roco\对战逻辑2.png" alt="对战逻辑2" style="zoom:22%;" />



#### Step 3 裁判邀请对手、天气环境对原技能效果进行调整，得到最终效果

- 裁判令消息队列队首元素出列
- 对手、天气环境对队首元素进行调整

<img src="D:\Programs\CFiles\Roco\对战逻辑3.png" alt="对战逻辑3" style="zoom:22%;" />

#### Step 4 裁判令技能效果作用对象应用技能效果

- 重复Step 3、 Step 4直至消息队列为空
- 若执行过程中Player 2出战宠物阵亡，则结算完本技能效果，之后不再结算其他多段技能效果

<img src="D:\Programs\CFiles\Roco\对战逻辑4.png" alt="对战逻辑4" style="zoom:22%;" />

#### Step 5 先手玩家结算多段技能剩余段数

- 流程同上

#### Step 6 先手玩家结算异常状态效果和天气环境效果

- 流程同上

#### Step 7 后手玩家结算本回合效果

- 重复Step 1到Step 6
