#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int month[13];

void updateLeapyear(int year) {
    if (year % 400 == 0) month[2] = 29;
    else if (year % 100 == 0) month[2] = 28;
    else if (year % 4 == 0) month[2] = 29;
    else month[2] = 28;
}

void storemonth() {
    month[1] = 31;
    month[2] = 28;
    month[3] = 31;
    month[4] = 30;
    month[5] = 31;
    month[6] = 30;
    month[7] = 31;
    month[8] = 31;
    month[9] = 30;
    month[10] = 31;
    month[11] = 30;
    month[12] = 31;
}

int concat(int d, int m, int y) {
    char buf[20];
    sprintf(buf, "%d%d%d", d, m, y); // removes leading zeros
    return atoi(buf);
}

int findlucky(int d1, int m1, int y1, int d2, int m2, int y2) {
    storemonth();
    int result = 0;

    while (1) {
        int x = concat(d1, m1, y1);
        if (x % 4 == 0 || x % 7 == 0)
            result++;

        if (d1 == d2 && m1 == m2 && y1 == y2)
            break;

        updateLeapyear(y1);

        d1++;
        if (d1 > month[m1]) {
            d1 = 1;
            m1++;
            if (m1 > 12) {
                m1 = 1;
                y1++;
            }
        }
    }
    return result;
}
int main() {
    
     char input[50];
    int d1, m1, y1, d2, m2, y2;

    // Read whole line to avoid scanf issues
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d-%d-%d %d-%d-%d", &d1, &m1, &y1, &d2, &m2, &y2);

    printf("%d\n", findlucky(d1, m1, y1, d2, m2, y2));   
    return 0;
}
