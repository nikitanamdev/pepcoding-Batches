#include <iostream>
#include <vector>
#include <string>
using namespace std;

//basic.===================================

int subsequence(string str, string ans)
{
    if (str.size() == 0)
    {
        cout << ans << " ";
        return 1;
    }

    char ch = str[0];
    string roq = str.substr(1);
    int count = 0;

    count += subsequence(roq, ans + ch); //char want to contribute.
    count += subsequence(roq, ans);      //char didnt want to contribute.

    return count;
}

int permuation(string str, string ans)
{
    if (str.length() == 0)
    {
        cout << ans << " ";
        return 1;
    }

    int count = 0;
    int isSet = 0;
    for (int i = 0; i < str.length(); i++)
    {
        char ch = str[i];
        int mask = 1 << (ch - 'a');
        if ((isSet & mask) == 0)
        {
            string one = str.substr(0, i);
            string two = str.substr(i + 1);

            count += permuation(one + two, ans + ch);
            isSet |= mask;
        }
    }

    return count;
}

string codes[] = {"+", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wx", "yz", "*", "#"};

int keyPad(string ques, string ans)
{
    if (ques.length() == 0)
    {
        cout << ans << " ";
        return 1;
    }

    char ch = ques[0];
    string roq = ques.substr(1);
    string code = codes[ch - '0'];

    int count = 0;
    for (int i = 0; i < code.length(); i++)
    {
        count += keyPad(roq, ans + code[i]);
    }

    return count;
}

void basic()
{
    // << subsequence("abc", "") << endl;
    // cout << permuation("aaa", "") << endl;
    cout << keyPad("235", "");
}

//pathProblem.===========================
int functionCall = 0;
string res = "";

int mazePath(int sr, int sc, int er, int ec, string ans)
{
    functionCall++;
    if (sr == er && sc == ec)
    {
        // cout<<ans<<" ";
        return 0;
    }

    int count = 0;
    int lefts = 0;
    int rights = 0;
    int diagonals = 0;
    if (sc + 1 <= ec)
    {
        lefts = mazePath(sr, sc + 1, er, ec, ans + "H");
        //  lefts+="H";
    }

    if (sr + 1 <= er)
    {
        rights = mazePath(sr + 1, sc, er, ec, ans + "V");
        //  rights+="V";
    }

    if (sr + 1 <= er && sc + 1 <= ec)
    {
        diagonals = mazePath(sr + 1, sc + 1, er, ec, ans + "D");
        //    diagonals+="D";
    }

    // string ans_="";
    // if(ans_.length()<lefts.length()) ans_=lefts;
    // if(ans_.length()<rights.length()) ans_=rights;
    // if(ans_.length()<diagonals.length()) ans_=diagonals;

    return max(max(lefts, rights), diagonals) + 1;
}

int mazePath_multi(int sr, int sc, int er, int ec, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << " ";
        return 1;
    }

    int count = 0;
    for (int i = 1; sc + i <= ec; i++)
    {
        count += mazePath_multi(sr, sc + i, er, ec, ans + "H" + to_string(i));
    }

    for (int i = 1; sr + i <= er; i++)
    {
        count += mazePath_multi(sr + i, sc, er, ec, ans + "V" + to_string(i));
    }

    for (int i = 1; sr + i <= er && sc + i <= ec; i++)
    {
        count += mazePath_multi(sr + i, sc + i, er, ec, ans + "D" + to_string(i));
    }

    return count;
}

int boardPath(int si, int ei, string ans)
{
    if (si == ei)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    for (int dice = 1; dice <= 6 && si + dice <= ei; dice++)
    {
        count += boardPath(si + dice, ei, ans + to_string(dice));
    }

    return count;
}

void pathProblem()
{
    cout << mazePath(0, 0, 3, 5, "") << endl;
    cout << functionCall << endl;
    cout << res << endl;

    // cout<<mazePath_multi(0,0,2,2,"")<<endl;
    // cout<<boardPath(0,10,"")<<endl;
}

//FloodFillQuestions.=================================
bool isValidLocation(vector<vector<bool>> &isdone, int x, int y)
{
    if (x < 0 || y < 0 || x >= isdone.size() || y >= isdone[0].size() || isdone[x][y])
    {
        return false;
    }
    return true;
}

int floodfill(vector<vector<bool>> &isdone, int sr, int sc, int er, int ec, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    isdone[sr][sc] = true;

    if (isValidLocation(isdone, sr + 1, sc))
    {
        count += floodfill(isdone, sr + 1, sc, er, ec, ans + "D");
    }

    if (isValidLocation(isdone, sr, sc + 1))
    {
        count += floodfill(isdone, sr, sc + 1, er, ec, ans + "R");
    }

    if (isValidLocation(isdone, sr - 1, sc))
    {
        count += floodfill(isdone, sr - 1, sc, er, ec, ans + "U");
    }

    if (isValidLocation(isdone, sr, sc - 1))
    {
        count += floodfill(isdone, sr, sc - 1, er, ec, ans + "L");
    }

    isdone[sr][sc] = false;

    return count;
}

int floodfill_(vector<vector<bool>> &isdone, int sr, int sc, int er, int ec, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << endl;
        return 0;
    }

    int count = 0;
    isdone[sr][sc] = true;
    int max_ = 0;
    if (isValidLocation(isdone, sr + 1, sc))
    {
        max_ = max(max_, floodfill_(isdone, sr + 1, sc, er, ec, ans + "D"));
    }

    if (isValidLocation(isdone, sr, sc + 1))
    {
        max_ = max(max_, floodfill_(isdone, sr, sc + 1, er, ec, ans + "R"));
    }

    if (isValidLocation(isdone, sr - 1, sc))
    {
        max_ = max(max_, floodfill_(isdone, sr - 1, sc, er, ec, ans + "U"));
    }

    if (isValidLocation(isdone, sr, sc - 1))
    {
        max_ = max(max_, floodfill_(isdone, sr, sc - 1, er, ec, ans + "L"));
    }

    isdone[sr][sc] = false;

    return max_ + 1;
}

int floodfill_dir(vector<vector<bool>> &isdone, int sr, int sc, int er, int ec, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << endl;
        return 1;
    }

    int count = 0;
    isdone[sr][sc] = true;

    string dir_[8] = {"R", "D", "L", "U", "a", "b", "c", "d"};
    int dir[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};

    for (int d = 0; d < 8; d++)
    {
        int x = sr + dir[d][0];
        int y = sc + dir[d][1];

        if (isValidLocation(isdone, x, y))
        {
            count += floodfill_dir(isdone, x, y, er, ec, ans + dir_[d]);
        }
    }

    isdone[sr][sc] = false;

    return count;
}

void flodfillQuestions()
{
    vector<vector<bool>> isdone = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
    };
    cout << floodfill_dir(isdone, 0, 0, 2, 3, "") << endl;
}

//setQuestion.===================================================

int targetSum(vector<int> &arr, int vidx, int target, string ans)
{
    if (vidx == arr.size() || target <= 0)
    {
        if (target == 0)
        {
            cout << ans << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;
    count += targetSum(arr, vidx + 1, target - arr[vidx], ans + to_string(arr[vidx]) + " ");
    count += targetSum(arr, vidx + 1, target, ans);
    return count;
}

int equiSet(vector<int> &arr, int vidx, int set1, int set2, string ans1, string ans2)
{
    if (vidx == arr.size())
    {
        if (set1 == set2)
        {
            cout << ans1 << " = " << ans2 << endl;
            return 1;
        }
        return 0;
    }

    int count = 0;

    // count += equiSet(arr, vidx + 1, set1, set2, ans1, ans2);

    count += equiSet(arr, vidx + 1, set1 + arr[vidx], set2, ans1 + to_string(arr[vidx]) + " ", ans2);
    count += equiSet(arr, vidx + 1, set1, set2 + arr[vidx], ans1, ans2 + to_string(arr[vidx]) + " ");

    return count;
}

void setQuestion()
{
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70};
    // cout << targetSum(arr, 0, 60, "") << endl;
    cout << equiSet(arr, 1, 10, 0, "10 ", "") << endl;
}

void solve()
{
    // basic();
    // pathProblem();
    // flodfillQuestions();
    setQuestion();
}

int main(int args, char **argv)
{
    solve();
    return 0;
}