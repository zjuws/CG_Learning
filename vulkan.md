# Ch3-5 命令缓冲区[](https://easyvulkan.github.io/Ch3-5%20%E5%91%BD%E4%BB%A4%E7%BC%93%E5%86%B2%E5%8C%BA.html#ch3-5 "Permalink to this heading")

命令缓冲区（VkCommandBuffer）用于录制命令，而命令池（VkCommandPool）用于分配命令缓冲区。  
命令缓冲区并不代表命令池中大小和位置确定的某块区域，它是根据录制的命令内容动态变化的，由命令池管理，命令池本身也是动态大小的。  
在多线程中录制命令缓冲区时，必须给每个线程一个不同的命令池（而不是从同一个命令池中为每个线程分配不同的命令缓冲区），以避免访问冲突。

## Command Buffer[](https://easyvulkan.github.io/Ch3-5%20%E5%91%BD%E4%BB%A4%E7%BC%93%E5%86%B2%E5%8C%BA.html#command-buffer "Permalink to this heading")

命令缓冲区有两个级别：一级命令缓冲区和二级命令缓冲区。  
一级命令缓冲区可以被直接提交给队列。  
二级命令缓冲区必须从一级命令缓冲区执行，跟函数调用不太一样，二级命令缓冲区在开始录制时需指定继承信息（包含渲染通道在内的一些上下文参数），并非录制完以后可以被任何一级缓冲区调用。  
对于有多个子通道的渲染通道，通过在主线程中录制一级命令缓冲区，另一线程中将某个子通道中的命令录制在二级命令缓冲区中，可能可以在一定程度上缩减CPU一侧的执行时间。

### 命令缓冲区的生命周期[](https://easyvulkan.github.io/Ch3-5%20%E5%91%BD%E4%BB%A4%E7%BC%93%E5%86%B2%E5%8C%BA.html#id1 "Permalink to this heading")

![_images/ch3-5-1.png](https://easyvulkan.github.io/_images/ch3-5-1.png) ![_images/ch3-5-2.png](https://easyvulkan.github.io/_images/ch3-5-2.png)

- 如图所示，提交命令缓冲区之后、命令执行完之前的状态为待决状态（提一下以强调）。
    
- 若命令缓冲区中涉及到的Vulkan对象被销毁，则命令缓冲区从录制或可执行状态进入无效状态。
    
- 对于可反复录制（从指定了VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT的命令池中分配）且每次录制完只提交一次（开始录制时指定VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT）的命令缓冲区，执行完以后可以手动将其重置，但通常不需要这么干，重新录制命令缓冲区时会将其自动重置到初始化状态（然后紧跟着进入录制状态）。
    # Ch3-5 命令缓冲区[](https://easyvulkan.github.io/Ch3-5%20%E5%91%BD%E4%BB%A4%E7%BC%93%E5%86%B2%E5%8C%BA.html#ch3-5 "Permalink to this heading")

命令缓冲区（VkCommandBuffer）用于录制命令，而命令池（VkCommandPool）用于分配命令缓冲区。  
命令缓冲区并不代表命令池中大小和位置确定的某块区域，它是根据录制的命令内容动态变化的，由命令池管理，命令池本身也是动态大小的。  
在多线程中录制命令缓冲区时，必须给每个线程一个不同的命令池（而不是从同一个命令池中为每个线程分配不同的命令缓冲区），以避免访问冲突。

## Command Buffer[](https://easyvulkan.github.io/Ch3-5%20%E5%91%BD%E4%BB%A4%E7%BC%93%E5%86%B2%E5%8C%BA.html#command-buffer "Permalink to this heading")

命令缓冲区有两个级别：一级命令缓冲区和二级命令缓冲区。  
一级命令缓冲区可以被直接提交给队列。  
二级命令缓冲区必须从一级命令缓冲区执行，跟函数调用不太一样，二级命令缓冲区在开始录制时需指定继承信息（包含渲染通道在内的一些上下文参数），并非录制完以后可以被任何一级缓冲区调用。  
对于有多个子通道的渲染通道，通过在主线程中录制一级命令缓冲区，另一线程中将某个子通道中的命令录制在二级命令缓冲区中，可能可以在一定程度上缩减CPU一侧的执行时间。

### 命令缓冲区的生命周期[](https://easyvulkan.github.io/Ch3-5%20%E5%91%BD%E4%BB%A4%E7%BC%93%E5%86%B2%E5%8C%BA.html#id1 "Permalink to this heading")

![_images/ch3-5-1.png](https://easyvulkan.github.io/_images/ch3-5-1.png) ![_images/ch3-5-2.png](https://easyvulkan.github.io/_images/ch3-5-2.png)

- 如图所示，提交命令缓冲区之后、命令执行完之前的状态为待决状态（提一下以强调）。
    
- 若命令缓冲区中涉及到的Vulkan对象被销毁，则命令缓冲区从录制或可执行状态进入无效状态。
    
- 对于可反复录制（从指定了VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT的命令池中分配）且每次录制完只提交一次（开始录制时指定VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT）的命令缓冲区，执行完以后可以手动将其重置，但通常不需要这么干，重新录制命令缓冲区时会将其自动重置到初始化状态（然后紧跟着进入录制状态）。
    

Note

对于某些早期的Vulkan实现，提交命令缓冲区时必须附带一个栅栏（哪怕你用了其他同步手段比如信号量），才能使命令缓冲区在执行结束后从待决状态回到可执行状态或进入无效状态。这在标准中没有规定，可能是bug。

关于分配、释放、重置命令缓冲区的相应函数，见后文关于命令池的说明。

Note

对于某些早期的Vulkan实现，提交命令缓冲区时必须附带一个栅栏（哪怕你用了其他同步手段比如信号量），才能使命令缓冲区在执行结束后从待决状态回到可执行状态或进入无效状态。这在标准中没有规定，可能是bug。

关于分配、释放、重置命令缓冲区的相应函数，见后文关于命令池的说明。
