#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

PASSED=0
FAILED=0
TOTAL=0

run_test() {
    local test_name="$1"
    shift
    local expected="$1"
    shift
    local args=("$@")
    
    TOTAL=$((TOTAL + 1))
    
    local actual=$(../../build/task1 "${args[@]}" 2>&1)
    
    if [ "$actual" == "$expected" ]; then
        echo -e "${GREEN}✓${NC} $test_name"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗${NC} $test_name"
        echo -e "  Expected: ${YELLOW}${expected}${NC}"
        echo -e "  Got:      ${RED}${actual}${NC}"
        FAILED=$((FAILED + 1))
    fi
}

if [ ! -f "../../build/task1" ]; then
    echo -e "${RED}Error: ../../build/task1 not found${NC}"
    exit 1
fi

echo "Running task1 integration tests..."
echo "=================================="

run_test "NoArgs" "Usage: ../../build/task1 <x> <flag>
Flags: -h -p -s -e -a -f"

run_test "InvalidFormat" "Error: invalid integer format for x" "-h" "50"

run_test "FlagH50" "50 100" "50" "-h"

run_test "FlagH33" "33 66 99" "33" "-h"

run_test "Prime33" "33 is composite" "33" "-p"

run_test "Prime11" "11 is prime" "11" "-p"

run_test "FlagS11" "B" "11" "-s"

run_test "FlagS32" "2 0" "32" "-s"

run_test "FlagA32" "528" "32" "-a"

run_test "Factorial5" "120" "5" "-f"

echo "=================================="
echo -e "Total: $TOTAL tests"
echo -e "${GREEN}Passed: $PASSED${NC}"
if [ $FAILED -gt 0 ]; then
    echo -e "${RED}Failed: $FAILED${NC}"
    exit 1
else
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
fi