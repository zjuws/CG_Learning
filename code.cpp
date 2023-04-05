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


bool enable_extension(const char *                              required_ext_name,
                      const std::vector<VkExtensionProperties> &available_exts,
                      std::vector<const char *> &               enabled_extensions)
{
	for (auto &avail_ext_it : available_exts)
	{
		if (strcmp(avail_ext_it.extensionName, required_ext_name) == 0)
		{
			auto it = std::find_if(enabled_extensions.begin(), enabled_extensions.end(),
			                       [required_ext_name](const char *enabled_ext_name) {
				                       return strcmp(enabled_ext_name, required_ext_name) == 0;
			                       });
			if (it != enabled_extensions.end())
			{
				// Extension is already enabled
			}
			else
			{
				LOGI("Extension {} found, enabling it", required_ext_name);
				enabled_extensions.emplace_back(required_ext_name);
			}
			return true;
		}
	}

	LOGI("Extension {} not found", required_ext_name);
	return false;
}


AddExtension(const std::unordered_map<const char *, bool> &required_extensions)
{
    	uint32_t instance_extension_count;
	VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_count, nullptr));

	std::vector<VkExtensionProperties> available_instance_extensions(instance_extension_count);
	VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &instance_extension_count, available_instance_extensions.data()));

    auto extension_error = false;
	for (auto extension : required_extensions)
	{
		auto extension_name        = extension.first;
		auto extension_is_optional = extension.second;
		if (!enable_extension(extension_name, available_instance_extensions, enabled_extensions))
		{
			if (extension_is_optional)
			{
				LOGW("Optional instance extension {} not available, some features may be disabled", extension_name);
			}
			else
			{
				LOGE("Required instance extension {} not available, cannot run", extension_name);
				extension_error = true;
			}
			extension_error = extension_error || !extension_is_optional;
		}
	}

	VkInstanceCreateInfo instance_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};

	instance_info.pApplicationInfo = &app_info;

	instance_info.enabledExtensionCount   = to_u32(enabled_extensions.size());
	instance_info.ppEnabledExtensionNames = enabled_extensions.data();

	instance_info.enabledLayerCount   = to_u32(requested_validation_layers.size());
	instance_info.ppEnabledLayerNames = requested_validation_layers.data();
	// Create the Vulkan instance
	VkResult result = vkCreateInstance(&instance_info, nullptr, &handle);

	if (result != VK_SUCCESS)
	{
		throw VulkanException(result, "Could not create Vulkan instance");
	}
}


template <typename T>
T &request_extension_features(VkStructureType type)
{
    // We cannot request extension features if the physical device properties 2 instance extension isnt enabled
    if (!instance.is_enabled(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME))
    {
        throw std::runtime_error("Couldn't request feature from device as " + std::string(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME) + " isn't enabled!");
    }

    // If the type already exists in the map, return a casted pointer to get the extension feature struct
    auto extension_features_it = extension_features.find(type);
    if (extension_features_it != extension_features.end())
    {
        return *static_cast<T *>(extension_features_it->second.get());
    }

    // Get the extension feature
    VkPhysicalDeviceFeatures2KHR physical_device_features{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR};
    T                            extension{type};
    physical_device_features.pNext = &extension;
    vkGetPhysicalDeviceFeatures2KHR(handle, &physical_device_features);

    // Insert the extension feature into the extension feature map so its ownership is held
    extension_features.insert({type, std::make_shared<T>(extension)});

    // Pull out the dereferenced void pointer, we can assume its type based on the template
    auto *extension_ptr = static_cast<T *>(extension_features.find(type)->second.get());

    // If an extension feature has already been requested, we shift the linked list down by one
    // Making this current extension the new base pointer
    if (last_requested_extension_feature)
    {
        extension_ptr->pNext = last_requested_extension_feature;
    }
    last_requested_extension_feature = extension_ptr;

    return *extension_ptr;
}

void RequestGpuFeatures()
{
	// Querying valid physical devices on the machine
	uint32_t physical_device_count{0};
	VK_CHECK(vkEnumeratePhysicalDevices(handle, &physical_device_count, nullptr));

	if (physical_device_count < 1)
	{
		throw std::runtime_error("Couldn't find a physical device that supports Vulkan.");
	}

	std::vector<VkPhysicalDevice> physical_devices;
	physical_devices.resize(physical_device_count);
	VK_CHECK(vkEnumeratePhysicalDevices(handle, &physical_device_count, physical_devices.data()));

	// Create gpus wrapper objects from the VkPhysicalDevice's
	for (auto &physical_device : physical_devices)
	{
		gpus.push_back(std::make_unique<PhysicalDevice>(*this, physical_device));
	}



    auto &requested_extension_features = gpu.request_extension_features<VkPhysicalDeviceFragmentShadingRateFeaturesKHR>(
    VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_FEATURES_KHR);
	requested_extension_features.attachmentFragmentShadingRate = VK_TRUE;
	requested_extension_features.pipelineFragmentShadingRate   = VK_TRUE;
	requested_extension_features.primitiveFragmentShadingRate  = VK_FALSE;
}

