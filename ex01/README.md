# Reverse Polish Notation Computer

The goal of the exercise is to compute an inverted Polish mathematical expression. Handling the following operations "+ - / *". and digits less than 10 passed as arguments.

The description "Polish" refers to the nationality of logician [Jan Łukasiewicz](https://en.wikipedia.org/wiki/Jan_%C5%81ukasiewicz "Jan Łukasiewicz"), who invented Polish notation in 1924. Way before computers were mainstream. He argued that this notation is logically better than the notation we are used to where operands surrond the operators.

Notation we're used to:
*a + b* (a, b are the operands and + is the operator)

RPN (postfix)

*a b +*

Using this notation we wouldn't have to use parentheses and another layer of complexity:

|                | operation 1            | RPN equivalent            | operation 2            | RPN equivalent          |
| -------------- | ---------------------- | ------------------------- | ---------------------- | ----------------------- |
| operations     | (a + b) * c            | a b + c *                 | a + b * c              | a b c * +               |
| decompositions | a + b = r1<br />r1 * c | a b + => r1<br />r1 c *  | b * c = r2<br />a + r2 | b c * => r2<br />a r2 + |

That's why from a compiler's point of view the RPN is far superior since it wouldn't need to manage nor worry about precedence/priority.
