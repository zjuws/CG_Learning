### Perceptual Model for Adaptive Local Shading and Refresh Rate

* When the displays spatial and temporal sampling frequency is lower than that of the displayed signal, we see aliasing artifacts which are a common occurrence in real-time graphics

* CAMOJAB: CONTENT-ADAPTIVE METRIC OF JUDDER, ALIASING AND BLUR
*  our Adaptive Local Shading and Refresh Rate (ALSaRR) algorithm that uses our motion quality metric to determine the optimal distribution of shading rate and refresh rate under a given bandwidth constraint
* Real-time implementation. To reduce the performance overhead of our method, the quality predictions of CaMoJAB (Eq. (1)) are precomputed for every texture, mipmap level, and shading rate and stored as polynomials of the form:
* In comparison to Nvidia Adaptive Shading (NAS) [Yang et al. 2019], CaMoJAB is calibrated in physical units (pixels-per-degree, degreesper-second, cd/m2 ) and accounts for the display characteristics that affect motion quality perception, such as refresh rate, duty-cycle, and field-of-view. NAS may need to be recalibrated for a display of different size, brightness or pixel density than the one used by the authors. CaMoJAB has also been calibrated with several datasets, collected using psychophysical procedures, rather than tuned by the authors



### 直播间

[抖音直播电脑版_抖音直播网页版入口_抖音直播 (douyin.com)](https://live.douyin.com/590201259059)



### GAMES104

![image-20220521115204624](C:\Users\ws\AppData\Roaming\Typora\typora-user-images\image-20220521115204624.png)



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
* snipaste [截图工具]
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



- copy contents of *C:\Program Files\WindowsApps\CanonicalGroupLimited.UbuntuonWindows_1604.2017.922.0_x64__79rhkp1fndgsc* to another directory (I copied to *C:\Ubuntu*); Windows Explorer didn't let me browse this directory so I used Total Commander (Run As Administrator) to access it and copy
- start ubuntu.exe from the new location and it should install
- use ubuntu.exe from the new location going forward to start up bash etc.

![image-20220612111321584](C:\Users\ws\AppData\Roaming\Typora\typora-user-images\image-20220612111321584.png)

https://github.com/microsoft/WSL/issues/2577