/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /*
   * 思路：x ^ y 等价于 (x | y) & ~(x & y)
   * 其中，根据德摩根定律, x | y 等价于 ~(~x & ~y)
   * 因此，最终表达式为 ~(~x & ~y) & ~(x & y)
   */

  // 计算 x | y 的部分: ~(~x & ~y)
  int or_xy = ~(~x & ~y);

  // 计算 ~(x & y) 的部分
  int nand_xy = ~(x & y);

  // 将两部分结果相与
  return or_xy & nand_xy;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /*
   * 最小的32位补码整数是 -2^31, 其二进制表示为 1后面跟31个0。
   * 这个值可以通过将整数1向左移动31位得到。
   */
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /*
   * 思路:
   * 1. 最大的补码数 Tmax (0x7FFF...) 有一个特性: Tmax + 1 == ~Tmax (两者都等于Tmin)。
   *    这个条件可以用 !((x + 1) ^ (~x)) 来判断。
   *
   * 2. 但是，当 x = -1 (0xFFFF...) 时，上述条件也成立: (-1 + 1) == 0, ~(-1) == 0。
   *    所以我们需要排除 x = -1 的情况。
   *
   * 3. 区分 Tmax 和 -1：
   *    当 x = Tmax 时，x + 1 = Tmin (非零)。
   *    当 x = -1 时，x + 1 = 0 (零)。
   *    我们可以用 !!(x + 1) 来检查 x + 1 是否非零。
   *    如果 x = Tmax, !!(x+1) 是 1。
   *    如果 x = -1, !!(x+1) 是 0。
   *
   * 4. 将两个条件用 & 连接，即可得到最终结果。
   */
  int is_tmax_or_neg1 = !((x + 1) ^ ~x);
  int is_not_neg1 = !!(x + 1);
  
  return is_tmax_or_neg1 & is_not_neg1;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /*
   * 思路:
   * 1. 创建一个掩码 mask，它的所有奇数位都是1，偶数位都是0。
   *    这个掩码就是 0xAAAAAAAA。
   * 2. 由于不能使用大常量，我们从 0xAA 开始构造这个掩码：
   *    a. 先构造 16 位的 0xAAAA: (0xAA << 8) | 0xAA
   *    b. 再构造 32 位的 0xAAAAAAAA: (0xAAAA << 16) | 0xAAAA
   * 3. 如果 x 的所有奇数位都为1，那么 (x & mask) 的结果应该等于 mask。
   * 4. 使用异或来判断相等： !((x & mask) ^ mask)
   */

  // 构造掩码 0xAAAAAAAA
  int mask = 0xAA;
  mask = (mask << 8) | mask;
  mask = (mask << 16) | mask;

  // 提取 x 的奇数位
  int odd_bits_of_x = x & mask;
  
  // 判断提取出的位是否和掩码完全相同
  return !(odd_bits_of_x ^ mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /*
   * 思路：
   * 根据二进制补码的定义，一个数 x 的相反数 -x 等于对 x 按位取反后再加 1。
   * 这个规则是补码算术的基础。
   * 例如，-x = (~x) + 1
   */
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /*
   * 思路:
   * 将 0x30 <= x <= 0x39 分解为两个条件：
   * 1. x >= 0x30  (等价于 x - 0x30 >= 0)
   * 2. x <= 0x39  (等价于 0x39 - x >= 0)
   * 
   * 使用补码来模拟减法 a - b = a + (~b + 1)。
   * 使用右移和逻辑非来判断一个数是否 >= 0。
   * 如果 num >= 0, 它的符号位是0, (num >> 31) 的结果是0, !(0) 是1。
   * 如果 num < 0, 它的符号位是1, (num >> 31) 的结果是-1, !(-1) 是0。
   */

  // 检查 x >= 0x30
  // 计算 x - 0x30
  int lower_bound_check = x + (~0x30 + 1);
  // 检查 x - 0x30 是否为非负数
  int is_ge_30 = !(lower_bound_check >> 31);

  // 检查 x <= 0x39
  // 计算 0x39 - x
  int upper_bound_check = 0x39 + (~x + 1);
  // 检查 0x39 - x 是否为非负数
  int is_le_39 = !(upper_bound_check >> 31);
  
  // 两个条件必须同时满足
  return is_ge_30 & is_le_39;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*
   * 思路：利用位掩码进行选择。
   * 目标是构造一个掩码 mask，当 x!=0 时为全1(0xFFFFFFFF)，当 x==0 时为全0。
   *
   * 1. 将 x 转换为逻辑值:
   *    !x  ->  如果 x!=0, 结果是0; 如果 x==0, 结果是1。
   *
   * 2. 将逻辑值转换为掩码:
   *    我们知道 -1 的补码表示是全1 (0xFFFFFFFF)。
   *    !x + ~0  (等价于 !x - 1):
   *      - 如果 x!=0: 0 + (-1) = -1 (0xFFFFFFFF)
   *      - 如果 x==0: 1 + (-1) = 0  (0x00000000)
   *    这个结果 mask 正好是我们需要的。
   *
   * 3. 使用掩码选择 y 或 z:
   *    (y & mask) | (z & ~mask)
   *      - 如果 mask 是全1, 结果是 y。
   *      - 如果 mask 是全0, 结果是 z。
   */

  // 构造掩码。~0 是 -1
  int mask = !x + ~0;
  
  // 使用掩码选择
  return (y & mask) | (z & ~mask);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /*
   * 思路:
   * 核心是判断 y - x >= 0。但 y - x 会导致溢出，需要分情况讨论。
   *
   * 1. 获取 x 和 y 的符号位 (0为正, 1为负)
   *    sign_x = x >> 31;
   *    sign_y = y >> 31;
   *
   * 2. 情况一：x 和 y 符号不同
   *    - 如果 x 负 y 正 (sign_x=1, sign_y=0)，则 x <= y 必然成立。
   *    - 如果 x 正 y 负 (sign_x=0, sign_y=1)，则 x <= y 必然不成立。
   *    - 在这种情况下，结果完全取决于 x 的符号位。
   *    - 符号不同的条件是 sign_x ^ sign_y 不为0。
   *
   * 3. 情况二：x 和 y 符号相同
   *    - 此时 y - x 不会溢出。
   *    - 我们可以安全地计算 y - x 的符号位来判断大小。
   *    - y - x >= 0 的条件是 (y + ~x + 1) 的符号位为0。
   *    - 符号相同的条件是 !(sign_x ^ sign_y)。
   *
   * 4. 组合结果
   *    (符号不同 AND x是负数) OR (符号相同 AND (y-x)是非负数)
   */

  int sign_x = x >> 31;
  int sign_y = y >> 31;

  // case 1: 符号不同 (diff_sign_check 为 0xFFFFFFFF 或 0x0)
  int diff_sign_check = sign_x ^ sign_y;
  // 此时结果取决于x是否为负数 (sign_x)。如果x负，返回1。
  int diff_sign_result = diff_sign_check & sign_x;

  // case 2: 符号相同 (same_sign_check 为 0xFFFFFFFF 或 0x0)
  int same_sign_check = ~diff_sign_check;
  // 计算 y-x 的符号位
  int diff = y + (~x + 1);
  int diff_sign = diff >> 31;
  // 如果 y-x 非负，diff_sign为0，!diff_sign为1。
  int same_sign_result = same_sign_check & !diff_sign;

  return diff_sign_result | same_sign_result;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /*
   * 思路:
   * 目标是找到一个运算，能区分 0 和所有非零数。
   *
   * 1. 观察一个数 x 和它的相反数 -x 的符号位。
   *    -x 可以通过 ~x + 1 计算。
   *
   * 2. 对于任何非零数 x (除了 Tmin)，x 和 -x 的符号位是不同的。
   *    一个为正(符号位0)，一个为负(符号位1)。
   *    所以 x | -x 的结果，其符号位必然是1。
   *
   * 3. 对于 x = 0，x 和 -x 都是0，所以 x | -x 的结果是0，符号位是0。
   *
   * 4. 对于 x = Tmin, x 和 -x 都是 Tmin，所以 x | -x 的结果是 Tmin，符号位是1。
   *
   * 5. 综上，(x | -x) 的符号位：
   *    - 当 x = 0 时，为 0。
   *    - 当 x != 0 时，为 1。
   *
   * 6. 我们可以通过右移31位来提取这个符号位。
   *    (x | (~x + 1)) >> 31 的结果：
   *      - 如果 x = 0, 结果是 0。
   *      - 如果 x != 0, 结果是 -1 (0xFFFFFFFF)。
   *
   * 7. 最后，我们对这个结果加 1，即可得到目标：
   *      - 0 + 1 = 1
   *      - -1 + 1 = 0
   */
  
  int negX = ~x + 1;
  int sign = (x | negX) >> 31;
  
  return sign + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  return 0;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  return 2;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  return 2;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
