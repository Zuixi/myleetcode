### 设计一个有getMin功能的栈

**描述：**
> 实现一个特殊的栈，在实现栈的基本功能基础上，实现返回栈最小元素的操作。

**要求：**
1. `pop`,`push`,`getMin`操作时间为`o(n)`;
2. 设计栈的类型可以使用现成的栈结构;

**解答：**

使用两个栈，一个栈保存当前栈中的元素，其功能和正常栈一样，记为dataStack;
另外一个栈保存每一步的最小值，记为stackMin;

**1. 压入数据规则**：

当前数据为a,将其压入dataStack，然后判断stackMin是否为空；
    若为空，则a压入stackMin中；
    若不为空，则比较a和stackMin栈顶元素哪个更小；
    若a小或相等，则a压入stackMin中；
    若栈顶元素小，则stackMin不压入任何内容；

示例1：

依次压入`[3,4,5,1,2,1]`,dataStack和stackMin的变化如下
```
    dataStack       operation       stackMin
        1           sycn push           1
        2           2 > 1               null
        1           sycn push           1
        5           5 > 3               null
        4           4 > 3               null
        3           sycn push           3
```
**2. 弹出数据规则：**

先弹出dataStack中的栈顶元素，记为`value`，然后比较stackMin的栈顶元素和`value`哪一个更小；
stackMin的栈顶元素是逐渐变小的；stackMin栈顶元素即是栈中最小值，也是dataStack中的最小值，value值只能小于等于dataStack栈顶元素的值；
若value值等于stackMin栈顶元素，则stackMin弹出元素；
若value值大于stackMin栈顶元素，则stackMin不弹出元素；

**3. 查询当前栈中最小值操作：**

stackMin中的栈顶元素始终保留当前栈中最小值，即栈顶元素就可以；

**4. 代码实现：**

* [**C++最小栈实现**](../src/c%2B%2B/stack/stackMin.cpp)

**5. 复杂度分析：**

时间复杂度`O(1)`,空间复杂度`O(n)`