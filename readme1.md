# CS144-Sponge TCP协议栈实现

## 项目简介

这是斯坦福大学CS144计算机网络课程的TCP协议栈实现项目，代号"Sponge"。本项目通过C++从零开始实现一个功能完整的TCP协议栈，帮助学习者深入理解TCP协议的核心机制。

## 项目结构

```
├── libsponge/              # 核心库
│   ├── byte_stream.*       # 字节流实现
│   ├── stream_reassembler.*# 流重组器
│   ├── tcp_receiver.*      # TCP接收器
│   ├── wrapping_integers.* # 序列号处理
│   ├── tcp_helpers/        # TCP辅助工具
│   └── util/              # 基础工具类
├── apps/                   # 应用程序
│   └── webget.cc          # HTTP客户端工具
├── tests/                  # 测试文件
├── writeups/              # 实验报告模板
└── etc/                   # 构建配置
```

## 核心组件

### 1. ByteStream (字节流)
- 提供有序字节流的读写接口
- 支持容量限制和流结束标记
- 作为其他组件的基础数据结构

### 2. StreamReassembler (流重组器)
- 处理乱序、重复、重叠的数据包
- 实现滑动窗口机制
- 支持累积确认策略

### 3. TCPReceiver (TCP接收器)
- 集成流重组器功能
- 处理TCP序列号和确认号
- 计算接收窗口大小

## 实验内容

- **Lab 0**: 环境搭建，实现HTTP客户端
- **Lab 1**: 实现StreamReassembler
- **Lab 2**: 实现TCPReceiver
- **Lab 3**: 实现TCPSender (待完成)
- **Lab 4**: 实现TCPConnection (待完成)

## 构建和测试

### 构建项目
```bash
mkdir build
cd build
cmake ..
make
```

### 运行测试
```bash
# 运行所有测试
make check

# 运行特定实验的测试
make check_lab0
make check_lab1
make check_lab2
```

### 运行应用程序
```bash
# 使用webget工具
./apps/webget stanford.edu /class/cs144
```

## 开发环境

- **编译器**: GCC 7+ 或 Clang 6+
- **构建系统**: CMake 2.8.5+
- **操作系统**: Linux (推荐Ubuntu 18.04+)

## 代码规范

项目使用以下工具确保代码质量：
- `clang-format`: 代码格式化
- `clang-tidy`: 静态代码分析
- `cppcheck`: 额外的静态检查

## 学习目标

通过完成本项目，你将深入理解：
- TCP协议的核心机制（序列号、确认、窗口）
- 网络编程中的实际挑战（乱序、重复、丢包处理）
- C++系统编程和面向对象设计
- 软件测试和质量保证

## 参考资料

- [CS144课程网站](https://cs144.github.io/)
- [TCP/IP详解](https://www.amazon.com/TCP-Illustrated-Volume-Implementation/dp/0201633469)
- [RFC 793 - TCP协议规范](https://tools.ietf.org/html/rfc793)

## 许可证

本项目仅用于教育目的，请遵守学术诚信政策。