#include<iostream>
#include<vector>
using namespace std;

//#include "Header.h"

int main()
{
    int wait=0;
    int theone;
    int extra1=0;
    int extra2=0;
    char char1;
    char char2;
    char char3;
    char flag='n';
    int num=1;
    int x;
    int y;
    int count=30;
    
    srand (time(NULL));
    
    vector<char>cover;
    vector<int>nums;
    vector<int>waiter;
    vector<int>mines;
    vector<char>chars;
    
    for(int i=0;i<261;i++)
    {
        waiter.push_back(0);
        nums.push_back(0);
        mines.push_back(0);
        chars.push_back('0');
        cover.push_back('+');
    }
    
    
    
    
    cout<<"\n";
    
    
    for(int i=0;i<count;i++)
    {
        x=rand();
        y=x%260+1;
        
        if(mines[y]==0)
        {
                mines[y]=1;
        }
        else
        {
            i--;
        }
    }    
    
    
    
    
    for(int i=0;i<261;i++)
    {
        if(mines[i]!=0)
            chars[i]='M';
    }
    
    
    x=0;
    
    if(chars[1]!='M')   //top left
    {
        if(chars[2]=='M')
        {
            nums[1]++;
        }
        if(chars[27]=='M')
        {
            nums[1]++;
        }
        if(chars[28]=='M')
        {
            nums[1]++;
        }
    }
    
    if(chars[26]!='M')  //top right
    {
        if(chars[25]=='M')
        {
            nums[26]++;
        }
        if(chars[51]=='M')
        {
            nums[26]++;
        }
        if(chars[52]=='M')
        {
            nums[26]++;
        }
    }
    
    if(chars[235]!='M') //bottom left
    {
        if(chars[209]=='M')
        {
            nums[235]++;
        }
        if(chars[210]=='M')
        {
            nums[235]++;
        }
        if(chars[236]=='M')
        {
            nums[235]++;
        }
    }
    
    if(chars[260]!='M') //bottom right
    {
        if(chars[233]=='M')
        {
            nums[260]++;
        }
        if(chars[234]=='M')
        {
            nums[260]++;
        }
        if(chars[259]=='M')
        {
            nums[260]++;
        }
    }
    
    for(int i=2;i<26;i++)   //top
    {
        if(chars[i]!='M')
        {
            if(chars[i-1]=='M')
                nums[i]++;
            if(chars[i+1]=='M')
                nums[i]++;
            if(chars[i+25]=='M')
                nums[i]++;
            if(chars[i+26]=='M')
                nums[i]++;
            if(chars[i+27]=='M')
                nums[i]++;
        }
    }
    
    for(int i=236;i<260;i++)   //bottom
    {
        if(chars[i]!='M')
        {
            if(chars[i-1]=='M')
                nums[i]++;
            if(chars[i+1]=='M')
                nums[i]++;
            if(chars[i-25]=='M')
                nums[i]++;
            if(chars[i-26]=='M')
                nums[i]++;
            if(chars[i-27]=='M')
                nums[i]++;
        }
    }
    
    for(int i=26;i<210;i++)   //left
    {
        if(i%26==1&&chars[i]!='M')
        {
            if(chars[i-26]=='M')
                nums[i]++;
            if(chars[i-25]=='M')
                nums[i]++;
            if(chars[i+1]=='M')
                nums[i]++;
            if(chars[i+26]=='M')
                nums[i]++;
            if(chars[i+27]=='M')
                nums[i]++;
        }
    }
    
    for(int i=50;i<235;i++)   //right
    {
        if(i%26==0&&chars[i]!='M')
        {
            if(chars[i-27]=='M')
                nums[i]++;
            if(chars[i-26]=='M')
                nums[i]++;
            if(chars[i-1]=='M')
                nums[i]++;
            if(chars[i+25]=='M')
                nums[i]++;
            if(chars[i+26]=='M')
                nums[i]++;
        }
    }
    
    for(int i=28;i<234;i++)   //all else
    {
        if(i%26!=0&&i%26!=1&&chars[i]!='M')
        {
            if(chars[i-27]=='M')
                nums[i]++;
            if(chars[i-26]=='M')
                nums[i]++;
            if(chars[i-25]=='M')
                nums[i]++;
            if(chars[i-1]=='M')
                nums[i]++;
            if(chars[i+1]=='M')
                nums[i]++;
            if(chars[i+25]=='M')
                nums[i]++;
            if(chars[i+26]=='M')
                nums[i]++;
            if(chars[i+27]=='M')
                nums[i]++;
        }
    }
    
    for(int i=0;i<261;i++)
    {
        if(nums[i]==1)
            chars[i]='1';
        if(nums[i]==2)
            chars[i]='2';
        if(nums[i]==3)
            chars[i]='3';
        if(nums[i]==4)
            chars[i]='4';
        if(nums[i]==5)
            chars[i]='5';
        if(nums[i]==6)
            chars[i]='6';
        if(nums[i]==7)
            chars[i]='7';
        if(nums[i]==8)
            chars[i]='8';
    }
    
    
while(1)
{
    
    
    cout<<"\n\nMines left: "<<count<<"\n\n    a b c d e f g h i j k l m n o p q r s t u v w x y z\n    ---------------------------------------------------\n 0| ";
    num=1;
    for(int i=0;i<260;i++)
    {
        if(cover[i+1]=='+')
            cout<<cover[i+1]<<" ";
        else
            cout<<chars[i+1]<<" ";
        
        
        if(i%26==25&&num!=10)
        {
            cout<<"|"<<num-1<<"\n "<<num<<"| ";
            num++;
        }
            
    }
    cout<<"|9\n    ---------------------------------------------------\n    a b c d e f g h i j k l m n o p q r s t u v w x y z";
   
    cout<<"\n\nChoose a space: ";
    cin>>char1>>char2;

    flag='n';
    if(char1=='F')
    {
        cin>>char3;
        char1=char2;
        char2=char3;
        flag='y';
        count--;
    }
        wait=1;
    if(char1=='a')
        extra1=1;
    else if(char1=='b')
        extra1=2;
    else if(char1=='c')
        extra1=3;
    else if(char1=='d')
        extra1=4;
    else if(char1=='e')
        extra1=5;
    else if(char1=='f')
        extra1=6;
    else if(char1=='g')
        extra1=7;
    else if(char1=='h')
        extra1=8;
    else if(char1=='i')
        extra1=9;
    else if(char1=='j')
        extra1=10;
    else if(char1=='k')
        extra1=11;
    else if(char1=='l')
        extra1=12;
    else if(char1=='m')
        extra1=13;
    else if(char1=='n')
        extra1=14;
    else if(char1=='o')
        extra1=15;
    else if(char1=='p')
        extra1=16;
    else if(char1=='q')
        extra1=17;
    else if(char1=='r')
        extra1=18;
    else if(char1=='s')
        extra1=19;
    else if(char1=='t')
        extra1=20;
    else if(char1=='u')
        extra1=21;
    else if(char1=='v')
        extra1=22;
    else if(char1=='w')
        extra1=23;
    else if(char1=='x')
        extra1=24;
    else if(char1=='y')
        extra1=25;
    else if(char1=='z')
        extra1=26;
    
    if(char2=='0')
        extra2=0;
    else if(char2=='1')
        extra2=1;
    else if(char2=='2')
        extra2=2;
    else if(char2=='3')
        extra2=3;
    else if(char2=='4')
        extra2=4;
    else if(char2=='5')
        extra2=5;
    else if(char2=='6')
        extra2=6;
    else if(char2=='7')
        extra2=7;
    else if(char2=='8')
        extra2=8;
    else if(char2=='9')
        extra2=9;

        theone=extra1+26*extra2;
        
    
    if(flag=='y')
    {
        chars[theone]='F';
    }
        cover[theone]='-';
        
        waiter[wait]=theone;
        
while(wait!=0&&flag=='n')
{
        
    
    if(chars[theone]=='0')
    {
        if(theone==1)   //top left
        {
            
            if(nums[2]==0&&cover[2]=='+')
            {
                wait++;
                waiter[wait]=2;
            }
                cover[2]='-';
            if(nums[27]==0&&cover[27]=='+')
            {
                wait++;
                waiter[wait]=27;
            }
                cover[27]='-';
            if(nums[28]==0&&cover[28]=='+')
            {
                wait++;
                waiter[wait]=28;
            }
                cover[28]='-';
        }
        if(theone==26&&cover[26]=='+')  //top right
        {
            if(nums[25]==0&&cover[25]=='+')
            {
                wait++;
                waiter[wait]=25;
            }
                cover[25]='-';
            if(nums[51]==0&&cover[51]=='+')
            {
                wait++;
                waiter[wait]=51;
            }
                cover[51]='-';
            if(nums[52]==0&&cover[52]=='+')
            {
                wait++;
                waiter[wait]=52;
            }
                cover[52]='-';
        }
        if(theone==235&&cover[235]=='+') //bottom left
        {
            if(nums[209]==0&&cover[209]=='+')
            {
                wait++;
                waiter[wait]=209;
            }
                cover[209]='-';
            
            if(nums[210]==0&&cover[210]=='+')
            {
                wait++;
                waiter[wait]=210;
            }
                cover[210]='-';
            
            if(nums[236]==0&&cover[236]=='+')
            {
                wait++;
                waiter[wait]=236;
            }
                cover[236]='-';
            
        }
        if(theone==260&&cover[260]=='+') //bottom right
        {
            if(nums[233]==0&&cover[233]=='+')
            {
                wait++;
                waiter[wait]=233;
            }
                cover[233]='-';
            
            if(nums[234]==0&&cover[234]=='+')
            {
                wait++;
                waiter[wait]=234;
            }
                cover[234]='-';
            
            if(nums[259]==0&&cover[259]=='+')
            {
                wait++;
                waiter[wait]=259;
            }
                cover[259]='-';
            
        }
        for(int i=2;i<26;i++)   //top
        {
            if(theone==i)
            {
                if(nums[i-1]==0&&cover[i-1]=='+')
                {
                    wait++;
                    waiter[wait]=i-1;
                }
                    cover[i-1]='-';
                if(nums[i+1]==0&&cover[i+1]=='+')
                {
                    wait++;
                    waiter[wait]=i+1;
                }
                    cover[i+1]='-';
                if(nums[i+25]==0&&cover[i+25]=='+')
                {
                    wait++;
                    waiter[wait]=i+25;
                }
                    cover[i+25]='-';
                if(nums[i+26]==0&&cover[i+26]=='+')
                {
                    wait++;
                    waiter[wait]=i+26;
                }
                    cover[i+26]='-';
                if(nums[i+27]==0&&cover[i+27]=='+')
                {
                    wait++;
                    waiter[wait]=i+27;
                }
                    cover[i+27]='-';
                
            }
        }
        for(int i=236;i<260;i++)   //bottom
        {
            if(theone==i)
            {
                if(nums[i-1]==0&&cover[i-1]=='+')
                {
                    wait++;
                    waiter[wait]=i-1;
                }
                    cover[i-1]='-';
                
                if(nums[i+1]==0&&cover[i+1]=='+')
                {
                    wait++;
                    waiter[wait]=i+1;
                }
                    cover[i+1]='-';
                
                if(nums[i-25]==0&&cover[i-25]=='+')
                {
                    wait++;
                    waiter[wait]=i-25;
                }
                    cover[i-25]='-';
                if(nums[i-26]==0&&cover[i-26]=='+')
                {
                    wait++;
                    waiter[wait]=i-26;
                }
                    cover[i-26]='-';
                if(nums[i-27]==0&&cover[i-27]=='+')
                {
                    wait++;
                    waiter[wait]=i-27;
                }
                    cover[i-27]='-';
            }
        }
        for(int i=26;i<210;i++)   //left
        {
            if(i%26==1&&theone==i)
            {
                if(nums[i-26]==0&&cover[i-26]=='+')
                {
                    wait++;
                    waiter[wait]=i-26;
                }
                    cover[i-26]='-';
                if(nums[i-25]==0&&cover[i-25]=='+')
                {
                    wait++;
                    waiter[wait]=i-25;
                }
                    cover[i-25]='-';
                
                if(nums[i+1]==0&&cover[i+1]=='+')
                {
                    wait++;
                    waiter[wait]=i+1;
                }
                    cover[i+1]='-';
                if(nums[i+26]==0&&cover[i+26]=='+')
                {
                    wait++;
                    waiter[wait]=i+26;
                }
                    cover[i+26]='-';
                if(nums[i+27]==0&&cover[i+27]=='+')
                {
                    wait++;
                    waiter[wait]=i+27;
                }
                    cover[i+27]='-';
            }
        }
        for(int i=50;i<235;i++)   //right
        {
            if(i%26==0&&theone==i)
            {
                if(nums[i-27]==0&&cover[i-27]=='+')
                {
                    wait++;
                    waiter[wait]=i-27;
                }
                    cover[i-27]='-';
                if(nums[i-26]==0&&cover[i-26]=='+')
                {
                    wait++;
                    waiter[wait]=i-26;
                }
                    cover[i-26]='-';
                if(nums[i-1]==0&&cover[i-1]=='+')
                {
                    wait++;
                    waiter[wait]=i-1;
                }
                    cover[i-1]='-';
                if(nums[i+25]==0&&cover[i+25]=='+')
                {
                    wait++;
                    waiter[wait]=i+25;
                }
                    cover[i+25]='-';
                if(nums[i+26]==0&&cover[i+26]=='+')
                {
                    wait++;
                    waiter[wait]=i+26;
                }
                    cover[i+26]='-';
            }
        }
        for(int i=28;i<234;i++)   //all else
        {
            if(i%26!=0&&i%26!=1&&theone==i)
            {
                if(nums[i-27]==0&&cover[i-27]=='+')
                {
                    wait++;
                    waiter[wait]=i-27;
                }
                    cover[i-27]='-';
                if(nums[i-26]==0&&cover[i-26]=='+')
                {
                    wait++;
                    waiter[wait]=i-26;
                }
                    cover[i-26]='-';
                if(nums[i-25]==0&&cover[i-25]=='+')
                {
                    wait++;
                    waiter[wait]=i-25;
                }
                    cover[i-25]='-';
                if(nums[i-1]==0&&cover[i-1]=='+')
                {
                    wait++;
                    waiter[wait]=i-1;
                }
                    cover[i-1]='-';
                if(nums[i+1]==0&&cover[i+1]=='+')
                {
                    wait++;
                    waiter[wait]=i+1;
                }
                    cover[i+1]='-';
                if(nums[i+25]==0&&cover[i+25]=='+')
                {
                    wait++;
                    waiter[wait]=i+25;
                }
                    cover[i+25]='-';
                if(nums[i+26]==0&&cover[i+26]=='+')
                {
                    wait++;
                    waiter[wait]=i+26;
                }
                    cover[i+26]='-';
                if(nums[i+27]==0&&cover[i+27]=='+')
                {
                    wait++;
                    waiter[wait]=i+27;
                }
                    cover[i+27]='-';
            }
        }
    
    }
        
        theone=waiter[wait];
        wait--;
}
       
    
}
    
    
}