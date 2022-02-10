#include <iostream>
#include<stack>
#include<vector>
#include <algorithm>
using namespace std;

class BigDecimalInt{
private:
        vector<int>bigint;
        stack<string>ans;
        string decStr;
        int sign;
        int size1;
public:

BigDecimalInt(){} // default constructor

//parameter (string) constructor
BigDecimalInt(string decStr)
{
    sign = 1;
    int s = -1;
    for(int i=0; i<decStr.length(); i++){
        if(!isdigit(decStr[i])){
                s = i;
            sign = 0;
            break;
        }
    }
        for(int i=0; i<decStr.length(); i++){
                if(i!=s){
            bigint.push_back(int(decStr[i]) - '0');
            }
}
}

//parameter (int) constructor
BigDecimalInt(int decInt){
decStr = to_string(decInt);
sign = 1;
    int s = -1;
    for(int i=0; i<decStr.length(); i++){
        if(!isdigit(decStr[i])){
                s = i;
            sign = 0;
            break;
        }
    }
        for(int i=0; i<decStr.length(); i++){
                if(i!=s){
            bigint.push_back(int(decStr[i]) - '0');
            }
}
}
//get size
int size(){
return bigint.size();
}

//operator +
BigDecimalInt operator + ( BigDecimalInt &anotherDec){
     if(!sign && anotherDec.sign){
        sign = 1;
        return anotherDec - *this ;
    }
    else if(sign && !anotherDec.sign){
            anotherDec.sign = 1;
        return *this - anotherDec;
    }

    BigDecimalInt h;
    if(size() >= anotherDec.size()){
    int it = size()-1;
    int sum = 0;
    for(auto i = anotherDec.bigint.rbegin(); i != anotherDec.bigint.rend(); ++i){
        sum = *i + bigint[it];
        h.ans.push(to_string(sum%10));
        if(it == 0 && sum >= 10){
            h.ans.push("1");
        }
        else if(sum >= 10){
            bigint[it-1] += 1;
        }
        it--;
    }
    while(it>=0){
        if(it == 0 && bigint[it] >= 10){
            h.ans.push("0");
            h.ans.push("1");
        }
        else if(bigint[it] >= 10){
            bigint[it-1] += 1;
            h.ans.push("0");
        }
        else{
             h.ans.push(to_string(bigint[it]));
        }
        it--;
    }
}

else{
    int it = anotherDec.size()-1;
    int sum = 0;
     for(auto i = bigint.rbegin(); i != bigint.rend(); ++i){
        sum = *i + anotherDec.bigint[it];
        h.ans.push(to_string(sum%10));
        if(it == 0 && sum >= 10){
            h.ans.push("1");
        }
        else if(sum >= 10){
            anotherDec.bigint[it-1] += 1;
        }
        it--;
    }
    while(it>=0){
        if(it == 0 && anotherDec.bigint[it] >= 10){
            h.ans.push("0");
            h.ans.push("1");
        }
        else if(anotherDec.bigint[it] >= 10){
            anotherDec.bigint[it-1] += 1;
            h.ans.push("0");
        }
        else{
             h.ans.push(to_string(anotherDec.bigint[it]));
        }
        it--;
    }
}
if(!sign && !anotherDec.sign){
    h.ans.push("-");
}
    return h;
}

//operator -
BigDecimalInt operator - (BigDecimalInt anotherDec){
   BigDecimalInt g;
if(!sign && anotherDec.sign){
    anotherDec.sign = !anotherDec.sign;
    return *this + anotherDec;
}
else if(sign && !anotherDec.sign){
    anotherDec.sign = 1;
    return *this + anotherDec;
}
else{
    if(size() > anotherDec.size()){
        int ir = size()-1;
        int p = 0;
        for(auto i = anotherDec.bigint.rbegin(); i != anotherDec.bigint.rend(); ++i){
            if(bigint[ir] - *i < 0){
               if(bigint[ir-1] == 0){
                    int u = ir-1;
                  while(bigint[u] == 0){
                        bigint[u] = 9;
                         u--;
                  }
                  bigint[u] -= 1;
                g.ans.push(to_string((bigint[ir]+ 10) - *i));
            }
            else{
                bigint[ir-1] -= 1;
                g.ans.push(to_string((bigint[ir] + 10)- *i));
            }
        }
            else{
                    int p = bigint[ir] - *i;
                g.ans.push(to_string(p));
            }
            ir--;
        }
        while(ir>=0){
            g.ans.push(to_string(bigint[ir]));
            ir--;
        }
         if(!sign && !anotherDec.sign){g.ans.push("-");}
    }

    else if(size() < anotherDec.size()){
            int ir = anotherDec.size()-1;
        for(auto i = bigint.rbegin(); i != bigint.rend(); ++i){
            if(anotherDec.bigint[ir] - *i < 0){
               if(anotherDec.bigint[ir-1] == 0){
                    int u = ir-1;
                  while(anotherDec.bigint[u] == 0){
                        anotherDec.bigint[u] = 9;
                         u--;
                  }
                  anotherDec.bigint[u] -= 1;
                g.ans.push(to_string((anotherDec.bigint[ir] + 10)- *i));
            }
            else{
                anotherDec.bigint[ir-1] -= 1;
                g.ans.push(to_string((anotherDec.bigint[ir] + 10)- *i));
            }
        }
            else{
                    int p = anotherDec.bigint[ir] - *i;
                g.ans.push(to_string(p));
            }
            ir--;
        }
        while(ir>=0){
            g.ans.push(to_string(anotherDec.bigint[ir]));
            if(ir == 0){g.ans.push("-");}
            ir--;
        }
        if(!sign && !anotherDec.sign){g.ans.pop();}
    }

    else{
         int j = 0;
         int y = 2;
         while(j < size()){
            if(bigint[j] > anotherDec.bigint[j]){
                y = 0;
                break;
            }
            else if(bigint[j] < anotherDec.bigint[j]){
                y=1;
                break;
            }
            j++;
         }
         if(y==0){
             int ir = size()-1;
            for(int i = size()-1; i>=j; i--){
             if(bigint[ir] - anotherDec.bigint[i] < 0){
               if(bigint[ir-1] == 0){
                    int u = ir-1;
                  while(bigint[u] == 0){
                        bigint[u] = 9;
                         u--;
                  }
                  bigint[u] -= 1;
                g.ans.push(to_string((bigint[ir]+10)- anotherDec.bigint[i]));
            }
            else{
                bigint[ir-1] -= 1;
                g.ans.push(to_string((bigint[ir] + 10)- anotherDec.bigint[i]));
            }
        }
            else{
                    int p = bigint[ir] - anotherDec.bigint[i];
                g.ans.push(to_string(p));
            }
            ir--;
        }
        if(!sign && !anotherDec.sign){g.ans.push("-");}
    }
    else if(y==1){
        int ir = size()-1;
        for(int i = size()-1; i>=j; i--){
            if(anotherDec.bigint[ir] - bigint[i] < 0){
               if(anotherDec.bigint[ir-1] == 0){
                    int u = ir-1;
                  while(anotherDec.bigint[u] == 0){
                        anotherDec.bigint[u] = 9;
                         u--;
                  }
                  anotherDec.bigint[u] -= 1;
                g.ans.push(to_string((anotherDec.bigint[ir] + 10)- bigint[i]));
            }
            else{
                anotherDec.bigint[ir-1] -= 1;
                g.ans.push(to_string((anotherDec.bigint[ir] + 10)- bigint[i]));
            }
        }
            else{
                    int p = anotherDec.bigint[ir] - bigint[i];
                g.ans.push(to_string(p));
            }
            ir--;
        }
        g.ans.push("-");
        if(!sign && !anotherDec.sign){g.ans.pop();}
    }
    else{
        g.ans.push("0");
    }
}
    return g;
}
}

//operator << cout
friend ostream& operator << (ostream& out, BigDecimalInt b);

};

//operator << cout
ostream& operator << (ostream& out, BigDecimalInt b){
    while(!b.ans.empty()){
        out<<b.ans.top();
        b.ans.pop();
    }
    return out;
}

int main()
{
    int choose;
    string s,s1;
    while(true){
        cout<<"Welcome to FCI Calculator\n----------------------------------------\n1- Perform Addition\n2- Perform Subtraction\n3- Exit\n";
        cin>>choose;
        if(choose == 1){
                cout<<"enter first number";
                cin>>s;
                cout<<"enter first number";
                cin>>s1;
            BigDecimalInt num1(s);
            BigDecimalInt num2(s1);
            BigDecimalInt num3 = num1 + num2;
            cout << "num2 + num1 = " << num3 << endl;
        }
        else if(choose == 2){
                cout<<"enter first number";
                cin>>s;
                cout<<"enter first number";
                cin>>s1;
            BigDecimalInt num1(s);
            BigDecimalInt num2(s1);
            BigDecimalInt num3 = num1 - num2;
            cout << "num2 - num1 = " << num3 << endl;
        }
        else{
            break;
        }
    }
    return 0;
}
