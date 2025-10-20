# Retro-Go 固件详细介绍

## 项目概述

Retro-Go 是一个专为基于 ESP32 的设备设计的复古游戏固件，支持在 ODROID-GO 和 MRGC-G32 等设备上运行。该项目包含一个启动器和多个经过高度优化的应用程序，这些应用在减少 CPU、内存和闪存需求的同时保持了良好的兼容性。

## 支持的系统

- **任天堂**: NES, SNES (运行较慢), Gameboy, Gameboy Color, Game & Watch
- **世嘉**: SG-1000, Master System, Mega Drive / Genesis, Game Gear
- **Coleco**: Colecovision
- **NEC**: PC Engine
- **Atari**: Lynx
- **其他**: DOOM (包括 MOD)

## 核心特性

1. **游戏内菜单**: 提供便捷的游戏设置选项
2. **收藏夹和最近游玩**: 方便管理喜爱的游戏
3. **GB 调色板和实时时钟(RTC)**: 支持自定义调色板和时间调整
4. **NES 调色板和 PAL ROM**: 支持多种 NES 游戏格式
5. **缩放和滤镜选项**: 提供多种画面显示选项
6. **性能优化**: 更好的性能和兼容性
7. **加速模式**: 支持涡轮加速和快进功能
8. **可定制启动器**: 支持主题和个性化设置
9. **封面艺术和存档预览**: 支持游戏封面和存档预览
10. **多存档槽**: 每个游戏支持多个存档槽
11. **WiFi 文件管理器**: 可通过 WiFi 管理游戏文件
12. **ZIP 文件支持**: 支持 ZIP 格式的游戏文件

## 硬件支持

Retro-Go 官方支持以下设备：
- ODROID-GO
- MRGC-G32 (GBC)

同时也支持其他 ESP32 设备的移植版本，包括项目中包含的 Katarina 目标设备。

## 技术架构

### 项目结构
```
retro-go-esp32s3/
├── launcher/           # 启动器应用
├── retro-core/         # 核心模拟器(包含 NES, PCE, G&W, Lynx, SMS/GG/COL)
├── gwenesis/           # Genesis/Megadrive 模拟器
├── prboom-go/          # DOOM 引擎
├── fmsx/               # MSX 模拟器
├── components/         # 核心组件
├── themes/             # 主题文件
├── tools/              # 构建工具
└── assets/             # 资源文件
```

### 构建系统
Retro-Go 使用自定义的构建工具 [rg_tool.py](file:///e%3A/Learning/My_toy/gameboy/katarina_gameboy/Firmware/retro-go-esp32s3/rg_tool.py) 来管理多应用项目，该工具是对 ESP-IDF 的 [idf.py](file:///e%3A/Learning/My_toy/gameboy/katarina_gameboy/Firmware/retro-go-esp32s3/retro-core/retro-core.c#L74-L74) 工具的封装。

支持的 ESP-IDF 版本为 4.4 到 5.3，推荐使用 4.4.8 版本。

### 目标平台
项目支持多种 ESP32 目标设备，包括:
- ODROID-GO (官方支持)
- MRGC-G32 (官方支持)
- Katarina (自定义目标)
- 以及其他社区支持的设备

## 安装方法

### 对于 ODROID-GO:
1. 从发布页面下载 `retro-go_1.x_odroid-go.fw` 文件
2. 将文件复制到 SD 卡的 `/odroid/firmware` 目录
3. 按住 B 键开机进入固件更新模式
4. 在文件列表中选择 retro-go 并刷入

### 对于 MRGC-G32:
1. 从发布页面下载 `retro-go_1.x_mrgc-g32.fw` 文件
2. 将文件复制到 SD 卡的 `/espgbc/firmware` 目录
3. 按住 MENU 键(音量旋钮)开机
4. 在文件列表中选择 retro-go 并刷入

### 通用 ESP32 设备:
1. 构建 .img 文件
2. 使用 esptool.py 刷入固件: `esptool.py write_flash --flash_size detect 0x0 retro-go_*.img`

## 使用说明

### 游戏封面
游戏封面应放置在 SD 卡根目录的 `romart` 文件夹中。支持两种命名方式:
1. 基于文件名: `/romart/nes/Super Mario.png`
2. 基于 CRC32: `/romart/nes/A/ABCDE123.png`

### BIOS 文件
部分模拟器支持 BIOS 文件，应按以下方式放置:
- GB: `/retro-go/bios/gb_bios.bin`
- GBC: `/retro-go/bios/gbc_bios.bin`
- FDS: `/retro-go/bios/fds_bios.bin`
- MSX: 在 `/retro-go/bios/msx/` 文件夹中放置相应 ROM 文件

### WiFi 功能
要使用 WiFi 功能，需要在 `/retro-go/config/` 目录创建 [wifi.json](file:///e%3A/Learning/My_toy/gameboy/katarina_gameboy/Firmware/retro-go-esp32s3/components/retro-go/targets/sdl2/wifi.json) 配置文件，可定义最多 4 个网络。

### 外部 DAC (耳机)
支持 ODROID-GO 的外部 DAC 模组，可在菜单中切换音频输出到外部 DAC。

## 开发相关信息

### 构建 Retro-Go
1. 安装 ESP-IDF (版本 4.4-5.3)
2. 克隆项目代码
3. 应用必要的补丁 (sdcard-fix, panic-hook)
4. 使用 [rg_tool.py](file:///e%3A/Learning/My_toy/gameboy/katarina_gameboy/Firmware/retro-go-esp32s3/rg_tool.py) 构建固件:
   ```bash
   python rg_tool.py build-fw
   ```

### 目标设备移植
项目支持移植到新的 ESP32 设备，需要配置目标设备的硬件参数，包括:
- 显示屏配置
- 输入按键映射
- 存储配置
- 音频配置
- 电池检测配置

项目中的 Katarina 目标就是一个自定义移植的例子。

## 版权和许可

项目整体采用 GPLv2 许可证，但包含以下例外组件:
- fmsx/components/fmsx (MSX 模拟器，自定义非商业许可)
- handy-go/components/handy (Lynx 模拟器，zlib 许可证)

## 致谢

项目基于多个开源项目:
- Go-Play 固件 (NES/GBC/SMS 模拟器和基础库)
- pelle7's go-emu (启动器设计灵感)
- HuExpress 和 pelle7 的移植 (PCE-GO)
- libretro-handy (Lynx 模拟器)
- Snes9x 2005 (SNES 模拟器)
- PrBoom 2.5.0 (DOOM 引擎)
- Gwenesis (Genesis 模拟器)
- lcd-game-emulator (Game & Watch 模拟器)
- fMSX (MSX 模拟器)
- lodepng (PNG 支持)

以及社区贡献者和硬件支持厂商的大力支持。