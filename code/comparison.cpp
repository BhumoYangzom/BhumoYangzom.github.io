#include <bits/stdc++.h>
using namespace std;

string ltrm(const string &);
string rtrm(const string &);

vector <string > split (const string &);

vector<int> compareThreeValues (vector<int> a, vector<int> b) {
}
int main()
{
ofstream fout(getenv("OUTPUT_PATH"));

string temp;
getline(cin, temp);

vector<string> temp1 = split(rtrm(temp));
vector<int > a(3);

for (int i=0; i<3; i++)
{
int item1 = stoi(temp1[i]);
a[i] = item1;
}


}


