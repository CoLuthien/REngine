# Invader

it's gonna be quite awesome game engine

for compile time reflection, see example/main.cpp



## Requirements

For Arch Linux

```sh
sudo pacman -S vulkan-devel
sudo pacman -S shaderc
```

For Linux Mint

```sh 
wget -qO - http://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-focal.list http://packages.lunarg.com/vulkan/lunarg-vulkan-focal.list
sudo apt update
sudo apt install vulkan-sdk
```

unlike vulkan tutorials, glfw and glm is not required.