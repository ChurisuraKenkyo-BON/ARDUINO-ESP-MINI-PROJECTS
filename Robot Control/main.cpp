#include <iostream>
#include <windows.h>
#include <stack>
#include <queue>

using namespace std;

class RobotControl{
private:
    stack<string>magazine;
    stack<string>reverseLoadout;
    queue<string>lastLoadout;
public:
    void Move(char);
    void LoadAmmo(char);
    void Fire();
    void Turn(char);
    void Loadout(char);
};

void RobotControl::Move(char a){
    string direction;
    if(a=='W')
       direction="Forward";
    else if(a=='S')
        direction="Backward";
    else if(a=='A')
        direction="Left";
    else if(a=='D')
        direction="Right";
    cout << "Moving " << direction;
        for(int i=0;i<5;i++){
            cout << ".";
            Sleep(1000);
    }
    cout << "\nMoved " << direction<<endl;
}

void RobotControl::LoadAmmo(char a){
    int maxSize=20;
    if(magazine.size()==maxSize)
        cout << "Magazine is full\n";
    else if(a=='H'){
        magazine.push("HE");
        lastLoadout.push("HE");
        reverseLoadout.push("HE");
        cout << "Loaded HE Ammo\n";
    }
    else{
        magazine.push("AP");
        lastLoadout.push("AP");
        reverseLoadout.push("AP");
        cout << "Loaded AP Ammo\n";
    }
}

void RobotControl::Fire(){
    if(magazine.size()==0)
        cout << "Magazine is Empty\n";
    else{
        cout << "Firing " << magazine.top() << " Ammo";
        for(int i=0;i<3;i++){
        cout << ".";
        Sleep(1000);
    }
        cout << "\nFired " << magazine.top() << " Ammo\n";
        magazine.pop();
    }
}

void RobotControl::Turn(char a){
    string direction;
    if(a=='Q')
        direction="Left";
    else
        direction="Right";
    cout << "Turning " << direction;
    for(int i=0;i<2;i++){
        cout << ".";
        Sleep(1000);
        cout << "Finish";
    }
}

void RobotControl::Loadout(char a){
    string x;
    if(!magazine.empty()){
        cout << "Magazine is not empty. Can't load loadout";
    }
    else if(a=='R'){
        while(!lastLoadout.empty()){
            x=lastLoadout.front();
            magazine.push(x);
            lastLoadout.pop();
        }
        cout << "Copied Last Loadout\n";
    }
    else{
        while(!reverseLoadout.empty()){
            x=reverseLoadout.top();
            magazine.push(x);
            reverseLoadout.pop();
        }
        cout << "Reversed Previous Loadout\n";
    }
}

int main()
{
    char action;
    RobotControl r1;
    cout << "Robot Controls\n[W]Move Forward\t [H]Load HE Ammo\n[S]Move Backward [P]Load AP Ammo\n";
    cout << "[A]Move Left\t [Q]Turret Left Turn\n[D]Move Right\t [E]Turret Right Turn\n[F]Fire \t [R]Last Loadout\n[T]Reverse Loadout\n[M]Exit\n";
    while(true){
        cin >> action;
        if(action=='W'||action=='S'||action=='A'||action=='D')
            r1.Move(action);
        else if(action=='F')
            r1.Fire();
        else if(action=='H'||action=='P')
            r1.LoadAmmo(action);
        else if(action=='Q'||action=='E')
            r1.Turn(action);
        else if(action=='R'||action=='T')
            r1.Loadout(action);
        else
            break;
    }

    return 0;
}
