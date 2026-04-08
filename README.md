# XLedger

> 一个基于 Qt 的桌面记账应用

![Qt](https://img.shields.io/badge/Qt-6.11-brightgreen.svg) ![CMake](https://img.shields.io/badge/CMake-3.16+-orange.svg) ![License](https://img.shields.io/badge/License-MIT-green.svg)




## 功能

- [x] 添加、编辑、删除账单
- [x] 分类管理（添加和删除分类和标签）
- [x] 账单数据过滤
- [ ] 导出账单到excel表格(未完成) 
---

## 截图

![主界面](assets/2026-04-08_13-51.png)

---

## 依赖

- **Qt 6.11+** (Widgets)
- **CMake 3.16+**
- 可选库：
  - SQLite (内置 Qt 支持)

---

## 安装与构建

### 1. 克隆仓库

```bash
git clone https://github.com/xiangxun/XLedger.git
cd XLedger
```
### 2. 执行构建
```bash
mkdir build
cd build
cmake ..
make
```
