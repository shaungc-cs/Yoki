# UT Generation Module

这个模块为将来的单元测试生成功能预留空间。函数声明的收集和管理现在已集成到YokiConfig中。

## 功能概述

### 函数声明管理

函数声明现在通过YokiConfig单例类进行管理，这样保持了整个系统的一致性和简洁性。

#### 特性

- **集成化管理**: 与其他配置信息一起统一管理
- **简单API**: 提供添加、获取、清空等基本操作
- **一致性**: 遵循项目的单例模式设计

#### 使用示例

```cpp
#include "config/YokiConfig.h"

// 获取配置实例
auto& config = YokiConfig::getInstance();

// 添加函数声明（通常在AST访问器中完成）
config.addFunctionDecl(functionDeclPtr);

// 获取所有收集到的函数声明
const auto& functions = config.getAllFunctionDecls();

// 获取函数数量
size_t count = config.getFunctionDeclCount();

// 清空所有函数声明
config.clearFunctionDecls();
```

### AST访问器集成

参考`YokiUTGenerationASTViositor`类，它展示了如何在遍历AST时收集函数声明：

```cpp
bool YokiUTGenerationASTViositor::VisitFunctionDecl(FunctionDecl *node) {
  if (!node->hasBody()) {
    return true; // 跳过没有函数体的声明
  }
  
  // 将函数声明添加到YokiConfig中
  YokiConfig::getInstance().addFunctionDecl(node);
  return true;
}
```

## 集成指南

1. 在AST遍历过程中，通过YokiConfig收集函数声明
2. 在`VisitFunctionDecl`等方法中调用`YokiConfig::getInstance().addFunctionDecl()`
3. 使用`YokiConfig::getInstance().getAllFunctionDecls()`获取收集到的函数声明
4. 根据收集到的函数声明生成单元测试代码

## 迁移说明

原来的`FunctionDeclManager`类已被弃用，其功能已集成到`YokiConfig`中：

- `FunctionDeclManager::getInstance().addFunctionDecl()` → `YokiConfig::getInstance().addFunctionDecl()`
- `FunctionDeclManager::getInstance().getFunctionDecls()` → `YokiConfig::getInstance().getAllFunctionDecls()`
- `FunctionDeclManager::getInstance().size()` → `YokiConfig::getInstance().getFunctionDeclCount()`
- `FunctionDeclManager::getInstance().clear()` → `YokiConfig::getInstance().clearFunctionDecls()`

- 函数声明指针的生命周期由Clang AST管理，不要手动释放
- 在多线程环境中使用时，所有操作都是线程安全的
- 建议在每次新的编译单元处理开始时调用`clear()`清空之前的数据
