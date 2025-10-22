# 🧩 Python 字符串常用函数上手指南（给 C++ 开发者）

Python 的字符串（`str`）提供了大量实用方法，但常用的其实只有十几个。  
这份速查表帮你快速上手，尤其适合有 C++ 背景的开发者。

---

## 🧩 一、拆分与拼接

| 函数 | 作用 | 示例 | 类比 |
|------|------|------|------|
| `split(sep=None)` | 按分隔符拆分成列表 | `"a b c".split()` → `['a', 'b', 'c']` | 类似 `stringstream` |
| `join(iterable)` | 把可迭代对象拼接成字符串 | `" ".join(['a', 'b', 'c'])` → `'a b c'` | 类似手写循环 `+=` |
| `strip()` | 去掉首尾空白符 | `"  hi  ".strip()` → `'hi'` | `trim()`（C++里自己写的） |
| `replace(old, new)` | 替换子串 | `"foo bar".replace("foo", "baz")` → `'baz bar'` | `std::string::replace` |

---

## 🔠 二、查找与判断

| 函数 | 作用 | 示例 | 类比 |
|------|------|------|------|
| `startswith(prefix)` | 判断是否以某字符串开头 | `"apple".startswith("a")` → `True` | `r.find(...) == 0` |
| `endswith(suffix)` | 判断是否以某字符串结尾 | `"main.cpp".endswith(".cpp")` → `True` | 手动比较尾部 |
| `find(sub)` | 返回子串位置，找不到返回 `-1` | `"hello".find("l")` → `2` | `std::string::find` |
| `count(sub)` | 子串出现次数 | `"banana".count("a")` → `3` | 无直接等价（需循环） |
| `in` | 判断是否包含子串 | `'cat' in 'concatenate'` → `True` | `find != npos` |

---

## 🔤 三、大小写处理

| 函数 | 作用 | 示例 |
|------|------|------|
| `lower()` | 全部转小写 | `"HeLLo".lower()` → `'hello'` |
| `upper()` | 全部转大写 | `"HeLLo".upper()` → `'HELLO'` |
| `capitalize()` | 首字母大写 | `"apple".capitalize()` → `'Apple'` |
| `title()` | 每个单词首字母大写 | `"hello world".title()` → `'Hello World'` |

---

## 🔧 四、字符串检查（返回布尔值）

| 函数 | 作用 | 示例 |
|------|------|------|
| `isalpha()` | 是否全为字母 | `'abc'.isalpha()` → `True` |
| `isdigit()` | 是否全为数字 | `'123'.isdigit()` → `True` |
| `isalnum()` | 是否全为字母或数字 | `'a1'.isalnum()` → `True` |
| `isspace()` | 是否全为空白符 | `'  '.isspace()` → `True` |

---

## 🪄 五、一些常见的小技巧

| 用法 | 说明 | 示例 |
|------|------|------|
| `len(s)` | 字符串长度 | `len("abc")` → `3` |
| `s[i:j]` | 切片（取子串） | `"abcdef"[1:4]` → `'bcd'` |
| `s[::-1]` | 反转字符串 | `"abc"[::-1]` → `'cba'` |
| `f"{x}..."` | f-string 格式化 | `f"Result: {x}"` | 替代 `std::cout` 拼接 |

---

## 🧠 六、学习建议（C++ → Python）

1. **先掌握**：`split()`、`join()`、`startswith()`、`strip()`、`replace()`  
2. **多在交互式解释器实验**  
   ```python
   >>> s = "  hello world  "
   >>> s.strip().split()
   ['hello', 'world']
   ```
3. **做一些练习：**
   - 统计文件中以 `a` 开头的单词；
   - 把字符串中所有单词反过来；
   - 判断输入是否为回文。

---

## 💡 Bonus: Python vs C++ 对照表（部分）

| Python | C++ |
|--------|-----|
| `find()` | `std::string::find()` |
| `replace()` | `std::replace()` 或手动循环 |
| `split()` | `std::stringstream` |
| `join()` | 手动拼接字符串 |
| `startswith()` / `endswith()` | 比较前后子串 |
| `strip()` | 无直接等价（需自己写） |
