#include <iostream>
using namespace std;

int minimumPenalty(string X, string Y, int gap_penalty, int mismatch_penalty)
{
    int column = X.size();
    int row = Y.size();

    int dp[row + 1][column + 1];

    // Filling out Row and Column with gap penalties
    for (int i = 0; i <= row; i++)
    {
        dp[i][0] = i * gap_penalty;
    }
    for (int j = 0; j <= column; j++)
    {
        dp[0][j] = j * gap_penalty;
    }

    // Filling out DP table
    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= column; j++)
        {
            if (X[j - 1] == Y[i - 1])
            {
                dp[i][j] = min(min(dp[i][j - 1] + gap_penalty, dp[i - 1][j] + gap_penalty), dp[i - 1][j - 1]);
            }
            else
            {
                dp[i][j] = min(min(dp[i][j - 1] + gap_penalty, dp[i - 1][j] + gap_penalty), dp[i - 1][j - 1] + mismatch_penalty);
            }
        }
    }

    // Printing DP table
    for (int i = 0; i <= row; i++)
    {
        for (int j = 0; j <= column; j++)
        {
            cout << dp[i][j] << "   ";
        }
        cout << endl;
    }

    // Backtracking DP table
    string alignX = "", alignY = "";
    int i = row, j = column;

    while (i > 0 || j > 0) // Handles all the situations
    {
        if (X[j - 1] == Y[i - 1])
        {
            alignX = X[j - 1] + alignX;
            alignY = Y[i - 1] + alignY;
            i--;
            j--;
        }
        else
        {
            int left = dp[i][j - 1] + gap_penalty;
            int up = dp[i - 1][j] + gap_penalty;
            int diagonal = dp[i - 1][j - 1] + mismatch_penalty;

            if (diagonal <= left && diagonal <= up)
            {
                alignX = X[j - 1] + alignX;
                alignY = Y[i - 1] + alignY;
                i--;
                j--;
            }
            else if (left <= up)
            {
                alignX = X[j - 1] + alignX;
                alignY = "_" + alignY; // Moving to left will cause a gap in the first sequence
                j--;
            }
            else
            {
                alignX = "_" + alignX;
                alignY = Y[i - 1] + alignY; // Moving to right will cause a gap in the second sequence
                i--;
            }
        }
    }

    cout << alignX << endl;
    cout << alignY << endl;

    return dp[row][column];
}

int main()
{
    string first, second;
    cin >> first >> second;

    int gap_penalty, mismatch_penalty;
    cin >> gap_penalty >> mismatch_penalty;

    int minPenalty = minimumPenalty(first, second, gap_penalty, mismatch_penalty);

    cout << minPenalty << endl;

    return 0;
}
