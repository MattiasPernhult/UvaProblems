# UvaProblems
My solutions for the Uva Online Judge problems. 15 of them was part of a course (Advanced Programming) that a had during my bachelor degree in software development at Malmö University.

## Solved Problems (Advanced Programming course)
##### 10300 - Ecological Premium
Simple problem, just do exactly as the the text says.
##### 591 - Box of Bricks
Calculate the average that each box should have, then loop throgh the array and if that value is larger than the
average add that value subtracted by the average to a total variable. Then after the loop just print the total.
##### 10878 - Decode the tape
Get the binary sequence for the first row, then cast this into a number (which is an ASCII number), then cast this
number into a char and you will end up with the character for that row, repeat this until you reach the end.
##### 839 - Not so Mobile
It's possible to solve by using a recursive function, just read each line (lw, ld,
rw and rd), if wl is 0 then call the function again and the return value later on will be set to wl, do exactly
the samething with wr. Then just check if lw * ld != rw * rd and if so then the mobile is not equilibrium.
##### 10608 - Friends
Use the Union-Find datastructure to solve this one.
##### 10307 - Killing Aliens in Borg Maze
Construct a graph based on the input then use BFS-traversal (so you get the shortest path from each start 
to every alien and also each alien to alien). Then use either Prims or Kruskals algorithm to get the shortest path.
##### 374 - Big Mod
If coded in Java use the class BigInteger which has a function modpow.
##### 11054 - Wine trading in Gergovia
Greedy algorithm, foreach testcase save all houses in an array, then use a for loop that goes from 0 to houses-1, 
then foreach house take the value as an absolute value and add it to a variable (total), then add the value that the
house has to the next house.
##### 10340 - All in All
Start by setting an int (position) to 0, that will keep track of first word (which position) and another (length) to 0. 
Then use a for loop that goes through the second word, if the that char match the char 
that the first word has then increment position and length by one. When the forloop finish check if the variable length 
has the same length as the first word, if so then it is a subsequence.
##### 10943 - How do you add?
DP problem, the pattern that I used in this one was graph[1][i] = i and graph[i][1] = 1 where 1 >= i <= 100. 
And the rest for the graph is graph[i][j] = (graph[i][j-1] + graph[i-1][j]) % 1000000.
##### 116 - Unidirectional TSP
The solution to this one is to start at the second last column and foreach row there is three possible ways to go (col+1,row-1 && col+1,row && col+1,row+1).
Take the smallest one and add that one, then when all rows are done for that column, you go to the third last column and repeat this until you reach the first column (also do the same with the first). 
Remember to save the path (the smallest for each cell).
Then just pick the smallest one in the first column and follow the path (which you saved foreach cell) and you will end up with the smallest possible way.
##### 185 - Roman Numerals
To figure out if the roman number combination is correct or incorrect is quite easy. To solve the arabic sum just test all
all possible ways, if there is none then it's impossible, if there is one way it's valid and if there is more than one
way it's ambiguous.
##### 920 - Sunny Mountains
Use line sweep method to solve this one. Start by sorting the x coordinates in falling order. Then loop through each
coordinate (keep track of the highest hill) if that coordinate (y) is higher than the highest hill then
calculate how much part of that hill that is sunny, add that sunny part to an variable total and after the forloop
is done print the total.
##### 10078 - The Art Gallery
The solution to this problem is to check if a polygon is convex, and this can be done using the 
Counter-Clockwise Test (Left-turn) and Clockwise-Test(Right-turn).
##### 10245 - The Closest Pair Problem
Used two solutions for this one, the bruteforce algorithm and the divide-and-conquer algorithm.
Used this two because bruteforce has exponential timecomplexity and I thought it would give time limit once submitted to Uva, 
but it didn't because I used BufferedStreamReader instead of the Scanner.
