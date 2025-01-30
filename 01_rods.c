#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if a rod length is provided as a command-line argument

    if (argc != 2) {
        printf("Usage: %s <number of rods>\n", argv[0]);
        return 1;
    }

    int rodLength = atoi(argv[1]);
    if (rodLength <= 0) {
        printf("Invalid rod length\n");
        return 1;
    }
    printf("Please input length, value (e.g., 32, 10) and press Enter.\n");
    printf("Press Enter on an empty line to end the input.\n");

    int lengths[100], values[100];
    int pieceCount = 0;

    char line[50];
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '\n')
            break;
        int length, value;
        if (sscanf(line, "%d,%d", &length, &value) == 2) {
            lengths[pieceCount] = length;
            values[pieceCount]  = value;
            pieceCount++;

        } else {
            printf("Invalid input\n");
        }
    }

    int dp[rodLength + 1];
    int cut[rodLength + 1];

    for (int i = 0; i <= rodLength; i++) {
        dp[i]  = 0;
        cut[i] = -1;
    }

    for (int i = 1; i <= rodLength; i++) {
        for (int j = 0; j < pieceCount; j++) {
            if (lengths[j] <= i && dp[i] < dp[i - lengths[j]] + values[j]) {
                dp[i]  = dp[i - lengths[j]] + values[j];
                cut[i] = j;
            }
        }
    }

    // Output the cutting list and remainder

    int remainingLength = rodLength;
    int totalValue      = dp[rodLength];
    int cutCounts[100]  = {0};

    printf("Cutting list:\n");
    while (remainingLength > 0 && cut[remainingLength] != -1) {
        int pieceIndex = cut[remainingLength];
        cutCounts[pieceIndex]++;
        remainingLength -= lengths[pieceIndex];
    }

    for (int i = 0; i < pieceCount; i++) {
        if (cutCounts[i] > 0) {
            printf("%d @ %d = %d\n", cutCounts[i], lengths[i],
                   cutCounts[i] * values[i]);
        }
    }

    // Print the remainder

    printf("Remainder: %d\n", remainingLength);

    // Print the total value

    printf("Value: %d\n", totalValue);

    return 0;
}
