# BigNumber
一門名叫物件導向程式設計的作業
## BN_ArithmeticOperator
### operator +
- BNint and BNint
- BNint and BNfloat
- BNfloat and BNfloat
- BNint and int (or int and BNint)

### operator -
- BNint and BNint
- BNint and BNfloat
- BNfloat and BNfloat
- BNint and int (or int and BNint)

### operator *
- BNint and BNint
- BNint and BNfloat
- BNfloat and BNfloat
- BNint and int (or int and BNint)

### operator /
- BNint and BNint
- BNint and BNfloat
- BNfloat and BNfloat
- BNint and int (or int and BNint)

### operator %
- BNint and BNint
- BNint and int (or int and BNint)

### operator ++
### operator --

## BN_AssignmentOperator
### operator =
- BN to BN
- BN to int
### operator +=
- BN to BN
- BN to int
### operator -=
- BN to BN
- BN to int
### operator *=
- BN to BN
- BN to int
### operator /=
- BN to BN
- BN to int
### operator %=
- BN to BN
- BN to int


## BN_Basic
### Constructor
- BN()
- BN(string)
- BN(BN) (copy constructor)
- BN(short)
- BN(int)
- BN(long long)
- BN(double)
- BN(string, string)


## BN_OtherOperator
### operator <<
- denominator is 10^n
- other numerator and denominator (e.g 1/3, 3/7)


## BN_RelationalOperator
### operator ==
#### BN to BN
- compare numerator (both denominator are 1) 
- make denominator be same and compare  
TODO

### operator !=
#### BN to BN
- !(a == b)

### operator >
#### BN to BN
- integer compare (both denominator are 1)
- make denominator be same and compare  
TODO

### operator >=
#### BN to BN
- (a > b || a == b)

### operator <
#### BN to BN
- !(a > b || a == b)

### operator <=
#### BN to BN
- !(a > b)


## utility
### basicAdd
basic addition for integer
### basicSub
basic substruction for integer
### basicMul
basic multipication for integer
### basicDiv
basic division for integer

### abs
return |num|
### reciprocal
return 1/num
### gcd
return gcd
### lcm
return lcm
### power
return base ^ num
### factorial
return num!
### isValidPower
return if the power number valid (0.5 * n and n is integer)
### simplifyNum
make num be irreducible fraction (3/6 -> 1/2)


# FrontEndAnalyze
## convert
infix to postfix and check equation is valid or not
## set
### integer
[variable name]=[number or expression]
### decimal
[variable name]=[number or expression]
### get
[variable name]  
get variable
### delete
[variable name]  
delete variable
### list
list all variable and it's value
### clear
clear all variable
