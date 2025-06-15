#include "FunctionDeclManager.h"
#include <spdlog/spdlog.h>

FunctionDeclManager& FunctionDeclManager::getInstance() {
  static FunctionDeclManager instance;
  return instance;
}

void FunctionDeclManager::addFunctionDecl(clang::FunctionDecl* funcDecl) {
  if (!funcDecl) {
    spdlog::warn("Attempted to add null FunctionDecl pointer");
    return;
  }
  
  std::lock_guard<std::mutex> lock(mutex_);
  functionDecls.push_back(funcDecl);
  
  spdlog::debug("Added function: {} (total: {})", 
                funcDecl->getNameAsString(), 
                functionDecls.size());
}

const std::vector<clang::FunctionDecl*>& FunctionDeclManager::getFunctionDecls() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return functionDecls;
}

size_t FunctionDeclManager::size() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return functionDecls.size();
}

void FunctionDeclManager::clear() {
  std::lock_guard<std::mutex> lock(mutex_);
  functionDecls.clear();
  spdlog::info("Cleared all function declarations");
}

bool FunctionDeclManager::empty() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return functionDecls.empty();
}
