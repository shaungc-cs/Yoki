#ifndef FUNCTION_DECL_MANAGER_H
#define FUNCTION_DECL_MANAGER_H

#include <clang/AST/Decl.h>
#include <vector>
#include <mutex>

/**
 * FunctionDeclManager - 单例类，用于管理所有收集到的函数声明
 * 
 * 该类使用单例模式，提供线程安全的方式来存储和访问
 * 在AST遍历过程中收集到的所有FunctionDecl指针
 */
class FunctionDeclManager {
public:
  // 获取单例实例
  static FunctionDeclManager& getInstance();
  
  // 删除拷贝构造函数和赋值操作符
  FunctionDeclManager(const FunctionDeclManager&) = delete;
  FunctionDeclManager& operator=(const FunctionDeclManager&) = delete;

  // 添加函数声明
  void addFunctionDecl(clang::FunctionDecl* funcDecl);
  
  // 获取所有函数声明
  const std::vector<clang::FunctionDecl*>& getFunctionDecls() const;
  
  // 获取函数声明数量
  size_t size() const;
  
  // 清空所有函数声明
  void clear();
  
  // 检查是否为空
  bool empty() const;

private:
  // 私有构造函数
  FunctionDeclManager() = default;
  ~FunctionDeclManager() = default;
  
  // 存储函数声明的容器
  std::vector<clang::FunctionDecl*> functionDecls;
  
  // 互斥锁，保证线程安全
  mutable std::mutex mutex_;
};

#endif // FUNCTION_DECL_MANAGER_H
