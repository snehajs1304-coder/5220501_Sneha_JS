 Problem Statement
Given a time in 12-hour AM/PM format, convert it to military (24-hour) time.

Note:

12:00:00AM → 00:00:00 on a 24-hour clock.

12:00:00PM → 12:00:00 on a 24-hour clock.

🔹 Example
If s = "12:01:00PM"
➤ Return "12:01:00"

If s = "12:01:00AM"
➤ Return "00:01:00"

🔹 Function Description
Complete the timeConversion function. It should return a new string representing the input time in 24-hour format.

Function Signature
char* timeConversion(char* s);
Parameters:
char* s: a time in 12-hour format

Returns:
char*: the time in 24-hour format

🔹 Input Format
A single string s that represents a time in 12-hour clock format (i.e., hh:mm:ssAM or hh:mm:ssPM).

🔹 Constraints
All input times are valid

🔹 Sample Input
     07:05:45PM
🔹 Sample Output
    19:05:45