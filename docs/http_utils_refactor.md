# HTTP工具库改造总结

## 概述

本次改造创建了`src/lib/http_utils.h`工具库，统一封装HTTP响应处理，提高代码可读性和可维护性。

## 改造文件清单

| 文件 | 改造内容 |
|------|----------|
| `src/lib/http_utils.h` | 新建HTTP工具库 |
| `src/Makefile` | 添加`-Ilib`包含路径 |
| `src/system/reboot.c` | 3个handler改造 |
| `src/system/traffic.c` | 3个handler改造 |
| `src/system/advanced.c` | 6个handler改造 |
| `src/system/charge.c` | 3个handler改造 |
| `src/handlers/handlers.c` | ~25个handler改造 |
| `src/handlers/http_server.c` | 移除重复函数 |
| `src/handlers/handlers.h` | 移除旧函数声明 |

## HTTP工具库宏定义

### CORS响应头
```c
#define HTTP_CORS_HEADERS \
    "Content-Type: application/json\r\n" \
    "Access-Control-Allow-Origin: *\r\n"
```

### 方法检查宏
```c
HTTP_CHECK_GET(c, hm)    // GET方法检查 + OPTIONS处理
HTTP_CHECK_POST(c, hm)   // POST方法检查 + OPTIONS处理
HTTP_CHECK_DELETE(c, hm) // DELETE方法检查 + OPTIONS处理
HTTP_CHECK_ANY(c, hm)    // 仅OPTIONS处理，不检查方法
```

### 响应宏
```c
HTTP_OK(c, json)         // 200 OK响应
HTTP_ERROR(c, code, msg) // 错误响应
HTTP_SUCCESS(c, msg)     // 成功响应
HTTP_JSON(c, code, json) // 带状态码的JSON响应
```

## mongoose内置JSON函数

替代手动JSON解析，使用mongoose内置函数：

```c
// 获取字符串 (需要free)
char *str = mg_json_get_str(hm->body, "$.key");

// 获取数值
double val;
mg_json_get_num(hm->body, "$.key", &val);

// 获取布尔值
int bval;
mg_json_get_bool(hm->body, "$.enabled", &bval);
```

## 改造前后对比

### 改造前
```c
void handle_example(struct mg_connection *c, struct mg_http_message *hm) {
    if (hm->method.len == 7 && memcmp(hm->method.buf, "OPTIONS", 7) == 0) {
        mg_http_reply(c, 200, "Access-Control-Allow-Origin: *\r\n"
                              "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
                              "Access-Control-Allow-Headers: Content-Type\r\n", "");
        return;
    }
    // ... 业务逻辑
    mg_http_reply(c, 200,
        "Content-Type: application/json\r\n"
        "Access-Control-Allow-Origin: *\r\n",
        "%s", json);
}
```

### 改造后
```c
void handle_example(struct mg_connection *c, struct mg_http_message *hm) {
    HTTP_CHECK_GET(c, hm);
    // ... 业务逻辑
    HTTP_OK(c, json);
}
```

## 移除的冗余代码

- `check_method()` 函数 (handlers.c)
- `send_json_response()` 函数 (http_server.c)
- `send_error_response()` 函数 (http_server.c)

## 编译

```bash
cd src
make clean
make
```
