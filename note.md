animatediff stylize generate "D:\development\animatediff-cli-prompt-travel\stylize\2023-10-06T09-33-16-sample-majicmix realistic 麦橘写实_v2威力加强典藏版"

### git代理

1. git config --global http.proxy http://127.0.0.1:9991
2. git config --global https.proxy http://127.0.0.1:9991
### Animatediff

#### 网址

[guoyww/AnimateDiff: Official implementation of AnimateDiff. (github.com)](https://github.com/guoyww/AnimateDiff)

[s9roll7/animatediff-cli-prompt-travel: animatediff prompt travel (github.com)](https://github.com/s9roll7/animatediff-cli-prompt-travel)

#### 流程

```
cd animatediff-cli
venv\Scripts\activate.bat
.\venv\Scripts\Activate.ps1

# with this setup, it took about a minute to generate in my environment(RTX4090). VRAM usage was 6-7 GB
# width 256 / height 384 / length 128 frames / context 16 frames
animatediff generate -c config/prompts/prompt_travel.json -W 256 -H 384 -L 128 -C 16
# 5min / 9-10GB
animatediff generate -c config/prompts/prompt_travel.json -W 512 -H 768 -L 128 -C 16

# upscale using controlnet (tile, line anime, ip2p, ref)
# specify the directory of the frame generated in the above step
# default config path is 'frames_dir/../prompt.json'
# here, width=512 is specified, but even if the original size is 512, it is effective in increasing detail
animatediff tile-upscale PATH_TO_TARGET_FRAME_DIRECTORY -c config/prompts/prompt_travel.json -W 512

# upscale width to 768 (smoother than tile-upscale)
animatediff refine PATH_TO_TARGET_FRAME_DIRECTORY -W 768
# If generation takes an unusually long time, there is not enough vram.
# Give up large size or reduce the size of the context.
animatediff refine PATH_TO_TARGET_FRAME_DIRECTORY -W 1024 -C 6

# change lora and prompt to make minor changes to the video.
animatediff refine PATH_TO_TARGET_FRAME_DIRECTORY -c config/prompts/some_minor_changed.json
```

#### Video Sylization

```
cd animatediff-cli
venv\Scripts\activate.bat

# If you want to use the 'stylize' command, additional installation required
python -m pip install -e .[stylize]

# create config file from src video
animatediff stylize create-config YOUR_SRC_MOVIE_FILE.mp4

# Edit the config file by referring to the hint displayed in the log when the command finishes
# It is recommended to specify a short length for the test run

# generate(test run)
# 16 frames
animatediff stylize generate STYLYZE_DIR -L 16
# 16 frames from the 200th frame
animatediff stylize generate STYLYZE_DIR -L 16 -FO 200

# If generation takes an unusually long time, there is not enough vram.
# Give up large size or reduce the size of the context.

# generate
animatediff stylize generate STYLYZE_DIR
```

### blender

* SHIFT + MMB :  平移 
* MMB : 旋转 - 鼠标中键
* 小键盘 各种视图
* 数字7键 ：顶视图
* 数字1键 ： 正视图
* 数字3键 ： 右视图
* CTRL + ALT + Q ：四格试图
* 游标定位
  
  * Shift +RMB ：目视定位
  * 切换到编辑模式-点模式-选择一个点， 网格|吸附|游标到选中项
* SHIFT  + D : 复制物体
* ALT + LMB;  SHIFT +　ALT + LMB : 循环边 
* CTRL＋ALT＋LMB : 并排边 
* CTRL + SHIFT + LMB : 最短路径 
* G G : 滑移 
* CTRL + B ：倒角 
* SHIFT + CTRL + B ：点倒角 
* R R : 3D旋转 
* E ：挤出 
* ALT + E ：挤出二级菜单 
* CTRL + RMB ：挤出到光标 
* CTRL + R ：环切 
* F ：四点填充
* ALT + D ：调整顶点
* X：塌陷， 一个面坍缩为一个点
* / ：局部视图
* CTRL + J ：物体合并，
* CTRL + A ：应用物体变换
* F2：物体重命名，
* ALT +B：裁剪视图，
* m：新建集合
* CTRL + L ：关联材质等， 编辑模式，选择相连项
* Z ： 切换着色方式
*  ~ ： 切换视图
* ，：切换坐标系，
*  . ：切换基准点
* SHIFT + S：吸附
* i： 内插面
* A： 全选
* CTRL + i： 反选
* C： 刷选
* CTRL + : 扩展选区
* CTRL - ：收缩选区
* . ：居中显示
* SHIFT ：精细调节
* ALT + Z ：切换透视
* Q : 快捷键收藏夹
* CTRL + 1/ 2/3 : 添加1/2/3级别细分 ; 编辑视图，选点线面
* CTRL + P : 父子关系, 大纲中 SHIFT 拖动节点
* m: 新建集合
* CTRL + ALT + 0: 设置当前界面为摄像机界面
* ALT + G:清除位移
* 插件   [machin3io/MACHIN3tools: MACHIN3tools is a free, continuously evolving collection of blender tools and pie menus in a single customizable package. (github.com)](https://github.com/machin3io/MACHIN3tools)

### unity

* 平移 - 鼠标中间
* 旋转 - Alt + 鼠标左键
* 自由行走 - 鼠标右键 + wasd

python -m eval.interpolator_cli --pattern D:\development\stable-diffusion-webui\outputs\img2img-images\20230513214507 --model_path pretrained_models\film_net\Style\saved_model --times_to_interpolate 2

### Perceptual Model for Adaptive Local Shading and Refresh Rate

* When the displays spatial and temporal sampling frequency is lower than that of the displayed signal, we see aliasing artifacts which are a common occurrence in real-time graphics

* CAMOJAB: CONTENT-ADAPTIVE METRIC OF JUDDER, ALIASING AND BLUR

* our Adaptive Local Shading and Refresh Rate (ALSaRR) algorithm that uses our motion quality metric to determine the optimal distribution of shading rate and refresh rate under a given bandwidth constraint

* Real-time implementation. To reduce the performance overhead of our method, the quality predictions of CaMoJAB (Eq. (1)) are precomputed for every texture, mipmap level, and shading rate and stored as polynomials of the form:

* In comparison to Nvidia Adaptive Shading (NAS) [Yang et al. 2019], CaMoJAB is calibrated in physical units (pixels-per-degree, degreesper-second, cd/m2 ) and accounts for the display characteristics that affect motion quality perception, such as refresh rate, duty-cycle, and field-of-view. NAS may need to be recalibrated for a display of different size, brightness or pixel density than the one used by the authors. CaMoJAB has also been calibrated with several datasets, collected using psychophysical procedures, rather than tuned by the authors

### 直播间

[抖音直播电脑版_抖音直播网页版入口_抖音直播 (douyin.com)](https://live.douyin.com/590201259059)

### python

* 工程地址 D:\dev\pythonProject

* pyqt https://maicss.gitbook.io/pyqt-chinese-tutoral/pyqt6/introduction

* pyinstaller [pyinstaller用法 - 简书 (jianshu.com)](https://www.jianshu.com/p/5ca41c87628f)

### conda

conda remove -n  需要删除的环境名 --all

git clone https://github.com/AUTOMATIC1111/stable-diffusion-webui

conda create -n novelai python==3.10.6

conda activate novelai

```text
conda deactivate
```

https://link.zhihu.com/?target=https%3A//pytorch.org/get-started/locally/

conda install pytorch torchvision torchaudio pytorch-cuda=11.6 -c pytorch -c nvidia

python -m pip install -r requirements.txt

```
cd D:\dev\stable-diffusion-webui
conda activate novelai
python launch.py --lowvram
```

```
https://zhuanlan.zhihu.com/p/575353301
masterpiece, best quality,obliques , 1girl, magic, vivid, looking at viewer, from above, black hair, black eyes, floating, flowing dress, {{{{intricate red dress}}}}, hibiscus flowers, d:, cleavage

nsfw, lowres, bad anatomy, bad hands, text, error, missing fingers, extra digit, fewer digits, cropped, worst quality, low quality, normal quality, jpeg artifacts, signature, watermark, username, blurry,

随机种子 Seed 设为：815804347
```

### 网址

https://chat.openai.com/   美国代理 + 315876632@qq.com Kl@

ai绘图(midjourney) https://discord.com/channels/662267976984297473/1008571138361790464

ai视频(d-id) https://studio.d-id.com/

win11配置深度学习环境GPU https://zhuanlan.zhihu.com/p/460806048

### AI

[Civitai](https://civitai.com/)

[Danbooru 标签超市 (novelai.dev)](https://tags.novelai.dev/)

https://github.com/AUTOMATIC1111/stable-diffusion-webui

[NovelAI.Dev](https://novelai.dev/)

### 实用工具

* windows终端
* snipaste [截图工具] [Snipaste.exe](..\..\tools\Snipaste-2.8.5-Beta-x64\Snipaste.exe) 
* Typora [md笔记]
* WSL [linux环境]
* win + V [剪切板]
* XYplorer [文件浏览器]
* TreeSize [查看文件大小]
* Ghelper [翻墙]
* aria2 [下载]
* win +X [功能中心]
* 抓住窗口的标题栏并摇动它  [win 设置]
* potplayer [视频]
* everything [搜索]
* IrfanView [图片查看工具]
* Tabnine AI [[Visual Studio Code | Install Tabnine Autocomplete for VSCode](https://www.tabnine.com/install/vscode)]
* [Moo0 前端显示器 (免费) - 添加额外的有用的菜单到窗口](https://zhs.moo0.com/?top=https://zhs.moo0.com/software/WindowMenuPlus/)
* [FSCapture.exe](..\..\tools\FSCapture100\FSCapture.exe) bluman VPISCJULXUFGDDXYAUYF
* [marktext/marktext: 📝A simple and elegant markdown editor, available for Linux, macOS and Windows. (github.com)](https://github.com/marktext/marktext/tree/develop)
* D:\tools\spacesniffer_1_3_0_2 [查看文件大小]
* 网页视频下载：[cobalt](https://cobalt.tools/)

### 技巧

```js
var input = document.querySelector(".webcast-chatroom___textarea");
input.value = "求关注111"
var button = document.querySelector(".webcast-chatroom___send-btn");
button.click();


// 定义一个变量来存储定时器的标识符
var timer;
// 使用setInterval函数创建一个定时器，每隔500毫秒执行一次console.log函数
timer = setInterval(function(){
  console.log("Hello World");
}, 500);

async function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

function fireKeyEvent(element, evtType, keyChar) {
  element.focus();
  var KeyboardEventInit = {key:keyChar, code:"", location:0, repeat:false, isComposing:false};
  var evtObj = new KeyboardEvent(evtType, KeyboardEventInit);
  element.dispatchEvent(evtObj);
}

var timer;
var i = 0;
timer = setInterval(async function(){
    i++;
    var input = document.querySelector(".webcast-chatroom___textarea");
    input.value = "求关注求关注求关注求关注求关注求关注" + i
    fireKeyEvent(input, "keydown", "Enter");
    await sleep(1000);
    var button = document.querySelector(".webcast-chatroom___send-btn");
    button.click();
}, 5000);

var i = 0;
i++;
var input = document.querySelector(".webcast-chatroom___textarea");
input.value = "求关注求关注求关注求关注求关注求关注" + i
var button = document.querySelector(".webcast-chatroom___send-btn");
button.click();
```

### ffmpeg

```
ffmpeg -y -r 30.0 -i %5d.png -c:v libx264 -vf fps=30.0 -pix_fmt yuv420p -crf 17 -preset veryfast video.mp4
ffmpeg -i output.mp4 -r 30 -f image2 %03d.png
```

### Edge TTS && whisper

D:\development\Edge-tts

```
edge-tts.exe --voice zh-TW-HsiaoChenNeural --f .\output\output.txt --write-media .\output\output{AudioCount}.mp3 2>nul
whisper xx.mp4 --model medium --language Chinese
```

### Unity学习

[通用渲染管线资源 | Universal RP | 12.1.1 (unity3d.com)](https://docs.unity3d.com/cn/Packages/com.unity.render-pipelines.universal@12.1/manual/universalrp-asset.html)

| 属性                   | 描述                                                                                                                                                                                                                                                   |
| -------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **SRP Batcher**      | 选中此复选框可启用 SRP Batcher。如果有许多不同材质使用相同的着色器，这将非常有用。SRP Batcher 是一个内部循环，可以在不影响 GPU 性能的情况下加速 CPU 渲染。使用 SRP Batcher 时，它将替代 SRP 渲染代码内部循环。                                                                                                                    |
| **Dynamic Batching** | 启用 [Dynamic Batching](https://docs.unity3d.com/Manual/DrawCallBatching.html) 可以使渲染管线自动批处理一系列共享相同材质的小动态对象。这对于不支持 GPU 实例化的平台和图形 API 非常有用。如果目标硬件确实支持 GPU 实例化，请禁用 **Dynamic Batching**。可以在运行时更改此设置。                                                      |
| **Store Actions**    | 定义 Unity 是丢弃还是存储 DrawObjects 通道的渲染目标。选择 **Store** 选项可显著增加移动端和基于瓦片的 GPU 上的内存带宽。 <br>**Auto**：Unity 默认使用 **Discard** 选项，如果检测到任何注入的通道，则回退到 **Store** 选项。 <br>**Discard**：Unity 会丢弃以后不重用的渲染通道的渲染目标（较低的内存带宽）。 <br>**Store**：Unity 存储每个通道的所有渲染目标（更高的内存带宽）。 |

**Use Adaptive Performance**

[通用渲染管线中的渲染 | Universal RP | 12.1.1 (unity3d.com)](https://docs.unity3d.com/cn/Packages/com.unity.render-pipelines.universal@12.1/manual/rendering-in-universalrp.html)

![](assets/2023-07-09-21-11-10-image.png)

[通用渲染器 | Universal RP | 12.1.1 (unity3d.com)](https://docs.unity3d.com/cn/Packages/com.unity.render-pipelines.universal@12.1/manual/urp-universal-renderer.html)

![](assets/2023-07-09-21-19-33-image.png)

![](assets/2023-07-09-21-22-22-image.png)

[Unity - Scripting API: Rendering.ScriptableRenderContext.BeginRenderPass (unity3d.com)](https://docs.unity3d.com/ScriptReference/Rendering.ScriptableRenderContext.BeginRenderPass.html)

![](assets/2023-07-09-21-38-53-image.png)

[URP 中的延迟渲染路径 | Universal RP | 12.1.1 (unity3d.com)](https://docs.unity3d.com/cn/Packages/com.unity.render-pipelines.universal@12.1/manual/rendering/deferred-rendering-path.html)

![](assets/2023-07-09-21-38-37-image.png)

```

```

### switch

[WebFG (atlas44.s3-us-west-2.amazonaws.com)](https://atlas44.s3-us-west-2.amazonaws.com/web-fusee-launcher/index.html)

### 3D Gaussian Spaltting

源码：https://github.com/graphdeco-inria/gaussian-splatting 

教程：[GitHub - jonstephens85/gaussian-splatting-Windows: 3D Gaussian Splatting for Real-Time Radiance Field Rendering - Detailed Windows Install & Usage Instructions](https://github.com/jonstephens85/gaussian-splatting-Windows)

视频教程：[Getting Started With 3D Gaussian Splatting for Windows (Beginner Tutorial) (youtube.com)](https://www.youtube.com/watch?v=UXtuigy_wYc)

```
1.ffmpeg -i {path to video} -qscale:v 1 -qmin 1 -vf fps={frame extraction rate} %04d.jpg

2.<location>/input
<location>
|---input
    |---<image 0>
    |---<image 1>
    |---...
    
3.python convert.py -s <location> [--resize] #If not resizing, ImageMagick is not needed

4.activate gaussian_splatting

5.python train.py -s <path to COLMAP or NeRF Synthetic dataset>

6../<SIBR install dir>/bin/SIBR_gaussianViewer_app -m <path to trained model>
```

![image-20240518161407171](./assets/image-20240518161407171.png)

拍摄：[XV3DGS-UEPlugin/Media/CaptureDOC_CN.md at main · xverse-engine/XV3DGS-UEPlugin · GitHub](https://github.com/xverse-engine/XV3DGS-UEPlugin/blob/main/Media/CaptureDOC_CN.md)

colmap:[Tutorial — COLMAP 3.9-dev documentation](https://colmap.github.io/tutorial.html)

### 飞书chatGPT

[ConnectAI-E/feishu-openai: 🎒 飞书 ×（GPT-4 + GPT-4V + DALL·E-3 + Whisper）= 飞一般的工作体验 🚀 语音对话、角色扮演、多话题讨论、图片创作、表格分析、文档导出 🚀 (github.com)](https://github.com/ConnectAI-E/feishu-openai?tab=readme-ov-file#详细配置步骤)



## 设计模式

设计模式是软件开发中用于解决常见设计问题的一套可复用解决方案。它们提供了编写灵活、可维护和可扩展代码的最佳实践。设计模式主要分为三大类：创建型模式、结构型模式和行为型模式。

### 创建型模式

创建型模式主要关注对象的创建过程，使系统独立于对象的创建方式。常见的创建型模式有：

1. **单例模式（Singleton Pattern）**：
   确保一个类只有一个实例，并提供一个全局访问点。
   ```cpp
   class Singleton {
   public:
       static Singleton& getInstance() {
           static Singleton instance;
           return instance;
       }
   private:
       Singleton() {}
       Singleton(const Singleton&) = delete;
       Singleton& operator=(const Singleton&) = delete;
   };
   ```

2. **工厂方法模式（Factory Method Pattern）**：
   定义一个用于创建对象的接口，让子类决定实例化哪一个类。
   ```cpp
   class Product {
   public:
       virtual void use() = 0;
   };
   
   class ConcreteProductA : public Product {
   public:
       void use() override { /* implementation */ }
   };
   
   class ConcreteProductB : public Product {
   public:
       void use() override { /* implementation */ }
   };
   
   class Factory {
   public:
       virtual Product* createProduct() = 0;
   };
   
   class FactoryA : public Factory {
   public:
       Product* createProduct() override {
           return new ConcreteProductA();
       }
   };
   
   class FactoryB : public Factory {
   public:
       Product* createProduct() override {
           return new ConcreteProductB();
       }
   };
   ```

3. **抽象工厂模式（Abstract Factory Pattern）**：
   提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。
   ```cpp
   class AbstractProductA {
   public:
       virtual void doSomething() = 0;
   };
   
   class AbstractProductB {
   public:
       virtual void doSomethingElse() = 0;
   };
   
   class ConcreteProductA1 : public AbstractProductA {
   public:
       void doSomething() override { /* implementation */ }
   };
   
   class ConcreteProductA2 : public AbstractProductA {
   public:
       void doSomething() override { /* implementation */ }
   };
   
   class ConcreteProductB1 : public AbstractProductB {
   public:
       void doSomethingElse() override { /* implementation */ }
   };
   
   class ConcreteProductB2 : public AbstractProductB {
   public:
       void doSomethingElse() override { /* implementation */ }
   };
   
   class AbstractFactory {
   public:
       virtual AbstractProductA* createProductA() = 0;
       virtual AbstractProductB* createProductB() = 0;
   };
   
   class ConcreteFactory1 : public AbstractFactory {
   public:
       AbstractProductA* createProductA() override {
           return new ConcreteProductA1();
       }
       AbstractProductB* createProductB() override {
           return new ConcreteProductB1();
       }
   };
   
   class ConcreteFactory2 : public AbstractFactory {
   public:
       AbstractProductA* createProductA() override {
           return new ConcreteProductA2();
       }
       AbstractProductB* createProductB() override {
           return new ConcreteProductB2();
       }
   };
   ```

### 结构型模式
结构型模式主要关注类和对象的组合，帮助确保系统的一部分可以独立变化。常见的结构型模式有：

1. **适配器模式（Adapter Pattern）**：
   将一个类的接口转换成客户希望的另外一个接口，使得原本由于接口不兼容而不能一起工作的类可以一起工作。
   ```cpp
   class Target {
   public:
       virtual void request() = 0;
   };
   
   class Adaptee {
   public:
       void specificRequest() { /* implementation */ }
   };
   
   class Adapter : public Target {
   private:
       Adaptee* adaptee;
   public:
       Adapter(Adaptee* a) : adaptee(a) {}
       void request() override {
           adaptee->specificRequest();
       }
   };
   ```

2. **装饰者模式（Decorator Pattern）**：
   动态地给对象添加一些额外的职责，就增加功能来说，装饰者模式相比生成子类更为灵活。
   ```cpp
   class Component {
   public:
       virtual void operation() = 0;
   };
   
   class ConcreteComponent : public Component {
   public:
       void operation() override { /* implementation */ }
   };
   
   class Decorator : public Component {
   protected:
       Component* component;
   public:
       Decorator(Component* c) : component(c) {}
       void operation() override {
           component->operation();
       }
   };
   
   class ConcreteDecoratorA : public Decorator {
   public:
       ConcreteDecoratorA(Component* c) : Decorator(c) {}
       void operation() override {
           Decorator::operation();
           // Additional behavior
       }
   };
   
   class ConcreteDecoratorB : public Decorator {
   public:
       ConcreteDecoratorB(Component* c) : Decorator(c) {}
       void operation() override {
           Decorator::operation();
           // Additional behavior
       }
   };
   ```

### 行为型模式
行为型模式主要关注对象之间的通信和职责分配。常见的行为型模式有：

1. **观察者模式（Observer Pattern）**：
   定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。
   ```cpp
   class Observer {
   public:
       virtual void update() = 0;
   };
   
   class ConcreteObserver : public Observer {
   public:
       void update() override { /* implementation */ }
   };
   
   class Subject {
   private:
       std::list<Observer*> observers;
   public:
       void attach(Observer* o) {
           observers.push_back(o);
       }
       void detach(Observer* o) {
           observers.remove(o);
       }
       void notify() {
           for (Observer* o : observers) {
               o->update();
           }
       }
   };
   ```

2. **策略模式（Strategy Pattern）**：
   定义一系列算法，把它们一个个封装起来，并且使它们可互相替换。
   ```cpp
   class Strategy {
   public:
       virtual void algorithmInterface() = 0;
   };
   
   class ConcreteStrategyA : public Strategy {
   public:
       void algorithmInterface() override { /* implementation */ }
   };
   
   class ConcreteStrategyB : public Strategy {
   public:
       void algorithmInterface() override { /* implementation */ }
   };
   
   class Context {
   private:
       Strategy* strategy;
   public:
       void setStrategy(Strategy* s) {
           strategy = s;
       }
       void executeStrategy() {
           strategy->algorithmInterface();
       }
   };
   ```

这些设计模式在软件开发中广泛使用，帮助开发者编写更加灵活、可维护的代码。通过理解和应用这些模式，可以更好地设计和实现复杂的软件系统。

## 面试准备

职位描述
1、负责跨平台框架的图形渲染引擎设计和研发；
2、参与自研跨平台（Android、iOS、嵌入式全平台）UI Framework开发和技术攻坚；
3、负责技术选型和调研，提出专业合理的方案建议，并推动技术驱动产生更多业务价值；
4、持续推动UI Framework在面向多端多平台场景下的开发体验的提升。
职位要求
1、大学本科及以上学历，计算机相关专业；
2、精通C++开发，3年以上的C++开发经验优先；
3、熟悉图形学原理，有较好的算法基础；
4、熟悉skia，nanovg，agg等2D图形库中的一种；
5、熟悉OpenGL/Vulkan/Metal/OpenGL ES中一种，了解相关规范、熟悉Shader编程优先；
6、有较强的语言表达、沟通能力和分析、解决问题的能力。

字节 Flow 团队的渲染引擎主要用于将网页内容呈现给用户，并实现各种交互效果，其具体功能包括：

1. 解析网页语言：渲染引擎需要解析 HTML、CSS 和 JavaScript 等网页语言，将其转化为可理解的格式。

2. 构建 DOM 树和 Render 树：解析完网页语言后，渲染引擎会构建 DOM 树（Document Object Model，文档对象模型）和 Render 树，前者描述了网页的结构，后者则用于确定页面的布局和样式。

3. 布局和绘制：根据 Render 树的信息，渲染引擎会计算页面的布局，确定各个元素的位置和大小，并将其绘制到屏幕上。

4. 处理用户交互：渲染引擎还需要处理用户的交互，例如鼠标点击、滚动、触摸等，根据用户的操作更新页面的显示内容。

总的来说，字节 Flow 团队的渲染引擎的作用是将网页内容转化为用户可以看到和交互的界面，为用户提供更好的浏览体验。



字节渲染引擎可能会考察以下方面的知识：

1. 计算机图形学：包括图形渲染的基本原理、光照模型、纹理映射、阴影等。

2. 渲染引擎架构：了解渲染引擎的整体架构，如渲染管道、顶点处理、片段处理等。

3. 编程语言：掌握相关的编程语言，如 C++、Python 等。

4. 数学知识：如线性代数、向量计算、矩阵变换等，这些在图形渲染中经常用到。

5. 性能优化：了解如何优化渲染引擎的性能，如减少三角形数量、使用合适的纹理格式等。

6. 图形 API：熟悉常见的图形 API，如 OpenGL、Vulkan 等。

7. 实时渲染：如果涉及实时渲染，还需要了解相关的技术和算法，如帧率控制、动态阴影等。

8. 材质和纹理：理解材质和纹理的概念，以及如何在渲染中使用它们。

9. 灯光和阴影：掌握灯光和阴影的计算方法，以及如何实现不同类型的阴影效果。

10. 特效和后期处理：了解一些常见的特效，如粒子系统、景深、抗锯齿等，以及后期处理的相关技术。

具体的考试内容可能会根据岗位要求和公司的技术栈有所不同。建议你在准备考试时，根据具体的岗位要求有针对性地进行学习和复习。

字节 Flow 团队渲染引擎架构师的考核可能会涵盖以下几个方面：

1. 计算机图形学基础知识：包括图形管线、几何变换、光照模型、纹理映射、着色器编程等。

2. 渲染算法和技术：例如实时渲染算法、离线渲染算法、阴影生成算法、抗锯齿技术、全局光照算法等。

3. 数据结构和算法：常见的数据结构（如链表、树、图等）和算法（如排序、搜索、动态规划等），以及在渲染引擎中的应用。

4. 编程语言和工具：熟练掌握 C++、Python 等编程语言，熟悉相关的开发工具和库。

5. 图形 API 知识：如 OpenGL、DirectX 等图形 API 的使用和理解。

6. 性能优化：能够分析和优化渲染引擎的性能，包括内存管理、CPU 和 GPU 利用率的提升等。

7. 软件工程知识：包括软件架构设计、代码规范、版本控制、团队协作等方面的能力。

8. 问题解决能力：通过实际的技术难题和案例，考察候选人分析和解决复杂问题的能力。

9. 对新技术的关注和学习能力：了解行业内最新的渲染技术发展趋势，具备快速学习和应用新技术的能力。

需要注意的是，具体的考核内容可能会根据团队的特定需求和项目特点有所不同。





【候选人可准备方面】：思考并梳理总结工作、多深究技术要点、多关注系统设计要点，数据结构和算法要针对性准备；资深候选人需要准备项目设计&工程能力等。

【面试准备】1、我们的技术面试会涉及到算法、数据结构和系统设计，面试前需要你做的准备具体如下：- 提前温习软件工程的核心概念，例如: 如何从一个需求落实到一个系统设计，如何衡量两个不同设计的好坏，如何在各种限制下（人员、时间、资源等）选择其中更合适的设计，以及提升该设计的可拓展性等。- 在白板上练习算法题目，写出清晰、简洁、bug free的代码,，并衡量时间和空间复杂度以及可能存在的副作用。- 我们鼓励即时跟面试官沟通你的想法，一个好的解法往往是思维逻辑的展现，所以与面试官沟通思考的过程是非常重要的，这样在沟通的过程中你也能拿到更多关于问题本身的信息。- 尝试用不同的方法，思路或数据结构去解决同一个问题，并且衡量不同解法之间的优劣。- 我们需要是可执行的代码，而不是伪代码。- 我们需要你能掌握面试岗位对应的技术领域相关知识。2、以下是准备面试的资料/网站，包括但不限于：- 《Cracking the Coding Interview》- https://leetcode.com/- http://highscalability.com/ 







**以下是一些可能在字节渲染引擎面试中出现的问题：**

1. 请简述渲染引擎的主要工作流程。

2. 谈谈你对图形渲染管线的理解，包括各个阶段的主要任务。

   应用阶段 (Application Stage) : 场景管理, 动画与物理计算, 用户输入处理,准备绘制指令

   几何阶段 (Geometry Stage): 顶点着色器, 曲面细分,几何着色器

   光栅化阶段 (Rasterization Stage): 图元转换为片元, 片元属性插值

   片元阶段 (Fragment Stage):片元着色器,深度和模板测试 

   后处理阶段 (Post-Processing Stage):**屏幕空间效果**：如HDR、色调映射、景深、运动模糊、抗锯齿等,**合成和混合**：将多个渲染结果合成一个最终的图像

3. 常见的图形 API 有哪些？它们各自的特点是什么？

   OpenGL\DirectX12\Vulkan\Metal

4. 如何优化渲染引擎的性能？举例说明一些方法。

   1. **减少绘制调用（Draw Calls）**批处理（Batching）\实例化（Instancing）
   2. **使用高效的资源管理 **纹理压缩\着色器缓存\延迟加载
   3. **优化几何处理** 简化网格\视锥体剔除（Frustum Culling）\细节层次（Level of Detail, LOD）
   4. **优化光照计算** 延迟渲染（Deferred Rendering）\预计算光照光照贴图\使用光照缓存
   5. **利用并行处理 **多线程渲染\命令缓冲区
   6. **优化内存访问** 减少内存访问和提高内存访问效率是优化的关键 \缓存友好数据结构\减少状态切换\合并多个网格数据，减少绘制调用和状态切换
   7. **使用硬件特性** 硬件加速 硬件光照、硬件曲面细分\GPU 计算（GPGPU）

5. 解释一下顶点缓冲和索引缓冲的作用。

   **存储顶点数据**：顶点缓冲用于存储一个或多个顶点的属性信息，如位置、法线、颜色、纹理坐标等。每个顶点通常包含多个属性，每个属性占用一定的内存空间

   **存储索引数据**：索引缓冲用于存储顶点的索引。索引是顶点在顶点缓冲区中的位置。通过索引缓冲，可以重复使用顶点缓冲区中的顶点，避免冗余数据。

6. 什么是纹理映射？在渲染中有什么重要性？

   纹理映射（Texture Mapping）是一种计算机图形学技术，通过将二维图像（纹理）贴附到三维模型的表面上，使模型表面显示出更多的细节和颜色，从而增加视觉真实感。

   纹理\UV 坐标\纹理单元

7. 描述一下光照模型的基本概念和常见类型。

   光照模型（Lighting Model）是用于模拟物体表面光照效果的数学模型，在计算机图形学中起着至关重要的作用。光照模型的基本概念涉及光源、表面材质和视点的相互作用，从而决定物体的最终颜色和亮度。常见的光照模型包括：朗伯光照模型（Lambertian Lighting Model）、冯氏光照模型（Phong Lighting Model）和布林-冯光照模型（Blinn-Phong Lighting Model）等。

   **光源（Light Source）\材质（Material）\视点（Viewer or Camera）\法向量（Normal Vector）**

   1. 朗伯光照模型 (Lambertian Lighting Model) 不考虑镜面反射，仅模拟漫反射 
      $$
      I_{diffuse}=I_{light}⋅k_d⋅max(0,N⋅L)
      $$
      

   2. 冯氏光照模型 (Phong Lighting Model)  包含环境光、漫反射光和镜面反射光的计算
      $$
      I=I_{ambient}+I_{diffuse}+I_{specular}
      $$
      

   3. 布林-冯光照模型 (Blinn-Phong Lighting Model)
      $$
      I_{specular} = I_{light}⋅k_s⋅max(0,N⋅H)^n
      $$
      

8. 说一说你对实时渲染和离线渲染的区别与联系的理解。

9. 如何处理渲染中的深度测试和剔除？

10. 讲一讲在渲染复杂场景时，如何进行场景管理和优化。

    **场景管理：**

    层次包围体（Bounding Volume Hierarchy, BVH）：

    四叉树（Quadtree）和八叉树（Octree）：

    网格细分（Spatial Grid Subdivision）：

    可见性判定（Visibility Determination）：

    **优化：**

    细节层次（Level of Detail, LOD）

    纹理压缩（Texture Compression）

    实例化渲染（Instancing Rendering）

    延迟渲染（Deferred Rendering）

    光照贴图（Lightmapping）

11. **举例说明一些常见的渲染特效及其实现原理。**

    1. 环境光遮蔽 (Ambient Occlusion, AO)
    2. 景深 (Depth of Field, DoF)
    3.  运动模糊 (Motion Blur)
    4. 镜面反射 (Specular Reflection)
    5. 体积光效 (Volumetric Lighting)

12. 对渲染引擎中的资源管理有什么看法？

    1. 资源管理的重要性
       性能优化：通过有效管理资源，可以减少不必要的加载和卸载操作，从而提高渲染性能和帧率。
       内存管理：控制内存使用，防止内存泄漏和内存碎片，确保渲染引擎在长时间运行后依然稳定。
       加载速度：提高资源加载和释放的效率，减少加载时间，提升用户体验。
       可扩展性：支持大规模场景和多种资源类型的管理，适应不同的应用场景和硬件环境。
    2. 资源管理的主要策略
       1. 资源池（Resource Pooling）
       2. 引用计数（Reference Counting）
       3. 资源缓存（Resource Caching）
       4. 懒加载（Lazy Loading）
       5. 资源预加载（Resource Preloading）
       6. 资源压缩和解压（Resource Compression and Decompression）

13. 如何解决渲染过程中的帧率不稳定问题？

    通过综合运用**优化渲染管线、细节层次管理、资源管理、光照模型选择、剔除技术、动态调整渲染负载、多线程和异步计算等方法**，可以显著提高渲染引擎的性能，解决帧率不稳定问题。关键是根据具体的应用场景和性能瓶颈，灵活选择和组合这些技术，持续进行性能监测和调优

14. 介绍一下你所了解的现代渲染引擎的新特性或技术趋势。

    1.  实时光线追踪 (Real-time Ray Tracing) 光线追踪硬件加速\混合渲染管线\DXR（DirectX Raytracing）和Vulkan Ray Tracing微软和Khronos Group分别在DirectX和Vulkan中引入了光线追踪支持，提供标准化的API接口
    2. 路径追踪 (Path Tracing) 全局光照模拟\降噪技术NVIDIA OptiX\实时路径追踪
    3. 物理渲染 (Physically Based Rendering, PBR) 物理材质模型\标准化材质\**环境光照贴图（IBL）**：使用环境光照贴图实现基于图像的全局光照，增加场景的真实感
    4. 虚拟现实 (Virtual Reality, VR) 和增强现实 (Augmented Reality, AR)
    5. 云渲染 (Cloud Rendering) 分布式渲染\即服务模型（Rendering as a Service, RaaS）：提供渲染即服务，使得用户无需高性能本地硬件即可进行复杂的渲染任务\实时流媒体渲染：通过云端渲染和流媒体技术，实现高质量图像的实时传输和显示
    6. 神经网络渲染 (Neural Rendering)  深度学习技术\AI驱动的降噪和超分辨率\神经光场（Neural Radiance Fields, NeRF）

15. 面对渲染中的一些技术挑战，你会如何去解决和应对？



1. **空间数据结构与算法：如八叉树、KD 树等，用于加速场景的空间划分和查询，以提高渲染效率。**

2. 几何处理算法：包括三角形网格简化、曲面细分、曲线拟合等，用于优化模型的几何表示和处理。

3. **可见性判断算法：例如视锥裁剪、遮挡剔除等，减少不必要的渲染计算。**

4. 纹理映射算法：如纹理压缩、纹理过滤等，以提高纹理的存储和显示效果。

5. **光照计算算法：包括光线追踪、辐射度算法、全局光照近似算法等，实现真实的光照效果。**

6. **阴影生成算法：如阴影映射、体积阴影等，增强场景的真实感。**

7. 并行计算算法：利用多核 CPU 或 GPU 进行并行处理，加速渲染过程。

8. **图像后处理算法：像抗锯齿、景深模拟、运动模糊等，提升最终图像的质量。**



一般来说基本上中等难度算法，偶尔会考hard，除了我发给你的codetop上接入字节leetcode上的hot100也是字节比较钟爱考察的，类似**接雨水，N皇后之类的hard题，**算法并不是考察的全部，主要看解题思路，面试官风格不同考察也不同


