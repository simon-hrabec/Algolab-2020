# Legions - solution
This is a sister problem to the Inball problem from 2 weeks ago. The concept is identical, but there are few differences. In Inball there are N lines that define possible half spaces. In Legions we have lines but it is not explicitelly defined in which direction is the line moving. We have to figure that out. Legions are just in 2D, whereas Inball could have more dimmensions, depending on the problem instance. In this problem we are guaranteed the lines to form a convex hull - the result will be a finite number. Another difference is that in Inball the equations were in form `Ax1+ Bx2 + Cx3 + ... < c` but in this problem we have the lines in form `Ax + By + c = 0`. And the final and most important difference - in Inball we had the lines static, but here they are moving.
- When Inball and Legions are the same problem
- Line moving direction
- Incorporating line speed into the solution
- Integer overflow

## When Inball and Legions are the same problem
In the intro I wrote that these two problems are conceptually identical. It is useful to define an instance of the problems where we could use both solutions. I wrote about the differences, but it is also good to look for what is the same - in this case we are also guaranteed the norm of the vector to be an integer, which makes everything much easier.
If we have Inball instance only with 2 dimensions and we have lines that create a convex hull and Legions with the same lines, all moving with speed 1 and Asterix's location within the convex hull then the solution for these 2 problems will be identical.

## Line moving direction
In Inball the half space is defined by the equation. Here, it is not. We have to use the initial Asterix's location to find out in which direction the line will move. We are guaranteed the initial position to not lie on the line itself. The gods of Algolab had mercy (or got too weak - I hope they wont read this before the exam ^^) and told us stright away that we can find the **signed** distance of a point from a line using the given equation - `(a*px + b*py + c)/sqrt(a^2+b^2)`. To determine the direction we do not care about the actual value, only about the sign. Hence, we can ignore the denominator of that fraction since it is always positive and only look at the numerator. If we use `CGAL::SMALLER` for our LP and dont want to use `lp.set_r(equation_id, CGAL::LARGER)` on individual equations, we can use the lines with negative distance as they are and invert the equations that have positive distance.

## Incorporating line speed into the solution
After finding the connection between Legions and Inball it is quite intuitive to see what to do with the speed. If all the legions are moving twice fast the result should be smaller by factor of 2. We can conclude that the radius variable needs to be multipled by the speed coeficient for each equation (together with the norm).

## Integer overflow
One tricky part is not to forget about overflows. To check the signed distance we need to multiply and sum the numbers. The numbers are guaranteed to fit into the range `2^24`. When we multiply them and add them, we can reach up to `2^49`, which does not fit into 32 bit integer. Therefore at the place where we do the multiplication we need to either have to cast some of the numbers or have the types already bigger. I use `int64_t` (aka `long` on the codeexpert platform). It is bigger than double (for integers), it is faster (to read data) and it always prints in the normal notation.

# Running time
    Test set 1 (20 pts / 3 s) - 0.038s
    Test set 2 (20 pts / 3 s) - 0.106s
    Test set 3 (20 pts / 3 s) - 1.466s
    Test set 4 (20 pts / 3 s) - 1.643s
    Test set 5 (20 pts / 3 s) - 1.695s
