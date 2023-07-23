```c++
#define VK_CHECK(x)                                                 \
    do                                                              \
    {                                                               \
        VkResult err = x;                                           \
        if (err)                                                    \
        {                                                           \
            LOGE("Detected Vulkan error: {}", vkb::to_string(err)); \
            abort();                                                \
        }                                                           \
    } while (0)
```
