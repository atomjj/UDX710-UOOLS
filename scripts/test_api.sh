#!/bin/bash
# HTTP API 测试脚本
# 用法: ./test_api.sh [host:port]

HOST=${1:-"localhost:8080"}
BASE_URL="http://$HOST"

echo "=========================================="
echo "HTTP API 测试脚本"
echo "目标: $BASE_URL"
echo "=========================================="

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

pass=0
fail=0

test_api() {
    local method=$1
    local endpoint=$2
    local data=$3
    local desc=$4
    
    echo -n "测试: $desc ... "
    
    if [ "$method" = "GET" ]; then
        response=$(curl -s -w "\n%{http_code}" "$BASE_URL$endpoint")
    else
        response=$(curl -s -w "\n%{http_code}" -X $method -H "Content-Type: application/json" -d "$data" "$BASE_URL$endpoint")
    fi
    
    http_code=$(echo "$response" | tail -n1)
    
    if [ "$http_code" = "200" ]; then
        echo -e "${GREEN}PASS${NC} (HTTP $http_code)"
        ((pass++))
    else
        echo -e "${RED}FAIL${NC} (HTTP $http_code)"
        ((fail++))
    fi
}

# 系统信息
test_api "GET" "/api/info" "" "获取系统信息"

# 流量统计
test_api "GET" "/api/get/Total" "" "获取流量统计"
test_api "GET" "/api/get/set" "" "获取流量配置"

# 系统时间
test_api "GET" "/api/get/time" "" "获取系统时间"

# 定时重启
test_api "GET" "/api/get/first-reboot" "" "获取定时重启配置"

# 充电控制
test_api "GET" "/api/charge/config" "" "获取充电配置"

# 频段信息
test_api "GET" "/api/bands" "" "获取频段状态"
test_api "GET" "/api/current_band" "" "获取当前频段"
test_api "GET" "/api/cells" "" "获取小区信息"

# 短信
test_api "GET" "/api/sms" "" "获取短信列表"
test_api "GET" "/api/sms/sent" "" "获取发送记录"
test_api "GET" "/api/sms/config" "" "获取短信配置"
test_api "GET" "/api/sms/webhook" "" "获取Webhook配置"
test_api "GET" "/api/sms/fix" "" "获取短信修复状态"

# OTA更新
test_api "GET" "/api/update/version" "" "获取版本信息"

echo ""
echo "=========================================="
echo "测试完成: ${GREEN}$pass 通过${NC}, ${RED}$fail 失败${NC}"
echo "=========================================="

exit $fail
