#!/bin/bash

assert() {
  expected="$1"
  input="$2"

  ./chibicc "$input" > tmp.s || exit
  gcc -static -o tmp tmp.s
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert 0 0
assert 42 42
assert 10 "3+7"
assert 21 "5+20-4"
assert 41 " 12 + 34 - 5 "
assert 47 '5+6*7'
assert 15 '5*(9-6)'
assert 4 '(3+5)/2'
assert 10 '-10+20'
assert 0 '+5-+5'
assert 30 '-10*-3'
assert 10 '+10*-3++4*+10'
assert 65 '-(5+-3*10)--(-10*-4)'
assert 10 '-(4*-5)/((-(2+1)*-2)/3)'

echo OK
