## 基于EasyX的打地鼠小游戏

---

### 程序介绍

#### 界面

1. 游戏主界面：

   - 开始游戏、设置和退出游戏

2. 游戏设置界面：

    - 音量调节：可以通过滑动条调节音量；

   - 难度选择：可以选择简单、普通和困难三种难度；

   - 分辨率选择：可以选择不同的屏幕分辨率；

   - 返回主界面：返回主界面。

3. 游戏界面：

    - 显示当前关卡、剩余时间和当前得分。

   - 地鼠随机出现，玩家需要点击地鼠得分。

   - 返回按钮，点击返回主界面。

#### 模块

1. 主模块：程序入口，负责初始化资源、启动主界面。

2. 窗口模块：负责各个界面的绘制和用户交互处理。

3. 游戏模块：负责游戏逻辑的实现，包括地鼠生成、点击检测、得分计算等。

4. 资源模块：负责图片、音效等资源的加载和管理。

5. 音效模块：负责音效的播放和管理。

---

### 项目结构

`include`：头文件目录

`src`：源码目录

`lib`：引用的库目录

`res`：图片和音乐资源的目录

`build`：编译目录

---

### 构建

#### 使用 CLion

本项目是用 **CLion** 写的，可以通过 **CLion** 打开。直接点击右上角的绿色箭头运行即可。

#### 使用 CMake

以下命令在项目文件夹下运行，因此先进入项目文件夹`cd whack-a-mole`。

然后再运行：
``` bash
cmake -B build
cmake --build build
```
编译好后的 **exe** 文件在 `build/Debug/Whack_a_Mole.exe` ，将其复制到 `build/` 目录下：

```bash
cp build/Debug/Whack_a_Mole.exe build/
```

然后运行该程序即可。

---

### 参考文档

[EasyX 介绍](https://docs.easyx.cn/zh-cn/intro)

[EasyX 基本概念](https://docs.easyx.cn/zh-cn/concepts)

[EasyX 函数说明](https://docs.easyx.cn/zh-cn/reference)

---

### 项目源码

[GitHub - mcdudu233/Whack-a-Mole: 基于easyx库的打地鼠游戏](https://github.com/mcdudu233/Whack-a-Mole)

[dudu233 / Whack a Mole · GitLab](https://gitlab.dorm.mcso.top/dudu233/whack-a-mole)

---
