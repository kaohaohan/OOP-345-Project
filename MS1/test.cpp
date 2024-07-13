#include "Utilities.h"
#include <iostream>
#include <string>

int main() {
  // 设置分隔符
  seneca::Utilities::setDelimiter(',');

  // 创建一个 Utilities 对象
  seneca::Utilities util;

  // 示例字符串
  std::string testStr =
      "apple,orange,banana,kiwi,strawberry,yellow watermellon";
  size_t next_pos = 0;
  bool more = true;

  // 提取第一个 token（item name）
  std::string token1 = util.extractToken(testStr, next_pos, more);
  std::cout << "Token 1: " << token1 << std::endl;
  std::cout << "Field width: " << util.getFieldWidth() << std::endl;

  // 提取第二个 token（serial number）
  std::string token2 = util.extractToken(testStr, next_pos, more);
  std::cout << "Token 2: " << token2 << std::endl;
  std::cout << "Field width: " << util.getFieldWidth() << std::endl;

  // 提取第三个 token（quantity）
  std::string token3 = util.extractToken(testStr, next_pos, more);
  std::cout << "Token 3: " << token3 << std::endl;
  std::cout << "Field width: " << util.getFieldWidth() << std::endl;

  // 提取第四个 token（description）
  std::string token4 = util.extractToken(testStr, next_pos, more);
  std::cout << "Token 4: " << token4 << std::endl;
  std::cout << "Field width: " << util.getFieldWidth() << std::endl;

  std::string token5 = util.extractToken(testStr, next_pos, more);
  std::cout << "Token 5: " << token5 << std::endl;
  std::cout << "Field width: " << util.getFieldWidth() << std::endl;

  std::string token6 = util.extractToken(testStr, next_pos, more);
  std::cout << "Token 6: " << token6 << std::endl;
  std::cout << "Field width: " << util.getFieldWidth() << std::endl;

  // 检查是否还有更多的 token
  std::cout << "More tokens: " << (more ? "true" : "false") << std::endl;

  return 0;
}