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
    local input="$*"

    TOTAL=$((TOTAL + 1))

    local actual=$(echo -e "$input" | ../../build/task2 2>&1)

    if [ "$actual" == "$expected" ]; then
        echo -e "${GREEN}✓${NC} $test_name"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗${NC} $test_name"
        echo -e "  Input:    ${YELLOW}${input}${NC}"
        echo -e "  Expected: ${YELLOW}${expected}${NC}"
        echo -e "  Got:      ${RED}${actual}${NC}"
        FAILED=$((FAILED + 1))
    fi
}

if [ ! -f "../../build/task2" ]; then
    echo -e "${RED}Error: ../../build/task2 not found${NC}"
    exit 1
fi

echo "Running task2 integration tests..."
echo "=================================="

run_test "SimpleSequence" $'Error: Invalid format\nSuccess: 13\nSuccess: 2\nSuccess: 5\nSuccess: 29' \
"5\n6\n1\n3\n10\n-5"

run_test "InvalidInputChar" "Error: Invalid format" "1\nh"

run_test "ValidRange" "Success: 541" "1\n100"

run_test "NegativeRange" "Error: Invalid format" "1\n-20"

run_test "Overflow" $'Error: Overflow\nSuccess: 48611' \
"2\n100000000000000000000000000000000000000000\n5000"

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
