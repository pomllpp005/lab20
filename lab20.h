#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iomanip>

using namespace std;

class Equipment{
    int hpmax;
    int atk;
    int def;
public:
    Equipment(int hp, int a, int d) : hpmax(hp), atk(a), def(d) {}
    vector<int> getStat(){
        return {hpmax, atk, def};
    }			
};

class Unit{
    string name;
    string type;		
    int hp;
    int hpmax;
    int atk;
    int def;
    bool guard_on;
    bool dodge_on; 
    Equipment *equipment; 
public:			
    Unit(string,string); 
    void showStatus();
    void newTurn();
    int attack(Unit &);
    int ultimateAttack(Unit &); 
    int beAttacked(int);
    int heal();	
    void guard();
    void dodge(); 
    bool isDead();
    void equip(Equipment *);  
};

Unit::Unit(string t,string n){ 
    type = t;
    name = n;
    if(type == "Hero"){
        hpmax = rand()%20+120;
        atk = rand()%5+14;
        def = rand()%3+9;
    }else if(t == "Monster"){
        hpmax = rand()%20+250;
        atk = rand()%5+25;
        def = rand()%3+5;
    }
    hp = hpmax;	
    guard_on = false;
    dodge_on = false; // เริ่มต้นสถานะการหลบหลีกเป็น false
    equipment = NULL;
}

void Unit::showStatus(){
    if(type == "Hero"){
        cout << "---------------------------------------\n"; 
        cout << name << "\n"; 
        cout << "HP: " << hp << "/" << hpmax << "\tATK: "<< atk << "\t\tDEF: "<< def;		
        cout << "\n---------------------------------------\n";
    }	
    else if(type == "Monster"){
        cout << "\t\t\t\t---------------------------------------\n"; 
        cout << "\t\t\t\t" << name << "\n"; 
        cout << "\t\t\t\tHP: " << hp << "\t\tATK: "<< atk << "\t\tDEF: "<< def;
        cout << "\n\t\t\t\t---------------------------------------\n";
    }
}

void Unit::newTurn(){
    guard_on = false; 
    dodge_on = false; // รีเซ็ตสถานะการหลบหลีกเมื่อเริ่มเทิร์นใหม่
}

int Unit::beAttacked(int oppatk){
    int dmg;
    if(oppatk > def){
        dmg = oppatk-def;	
        if(guard_on) dmg = dmg/3;
        if(dodge_on){
            if(rand()%2 == 0){ // ความน่าจะเป็น 1/2 ที่จะหลบหลีกสำเร็จ
                dmg = 0; // หลบหลีกสำเร็จ
            }else{
                dmg *= 2; // หลบหลีกไม่สำเร็จ ความเสียหายเป็น 2 เท่า
            }
        }
    }	
    hp -= dmg;
    if(hp <= 0){hp = 0;}
    
    return dmg;	
}

int Unit::attack(Unit &opp){
    return opp.beAttacked(atk);
}

int Unit::ultimateAttack(Unit &opp){
    return opp.beAttacked(atk*2);
}

int Unit::heal(){
    int h = rand()%21 + 10;
    if(hp + h > hpmax) h = hpmax - hp;
    hp = hp + h;
    return h;
}

void Unit::guard(){
    guard_on = true;
}	

void Unit::dodge(){
    dodge_on = true;
}

bool Unit::isDead(){
    if(hp <= 0) return true;
    else return false;
}

void Unit::equip(Equipment *newEquipment){
    if(equipment != NULL){
        // ถอด Equipment เก่า
        vector<int> oldStats = equipment->getStat();
        hpmax -= oldStats[0];
        atk -= oldStats[1];
        def -= oldStats[2];
    }

    // สวม Equipment ใหม่
    equipment = newEquipment;
    vector<int> newStats = equipment->getStat();
    hpmax += newStats[0];
    atk += newStats[1];
    def += newStats[2];

    // ปรับ HP หาก hpmax ลดลงและ hp เกิน hpmax ใหม่
    if(hp > hpmax){
        hp = hpmax;
    }
}

void drawScene(char p_action,int p,char m_action,int m){
    cout << "                                                       \n";
    if(p_action == 'A'){
        cout << "                                       "<< -p <<"\n";
    }else{
        cout << "                                                       \n";	
    }	
    cout << "                                *               *      \n";
    cout << "                                **  *********  **      \n";
    cout << "                                ****         ****      \n";
    if(m_action == 'A'){
        cout << "                 " << setw(5) << -m << "           *** **   ** ***       Attack!\n";
    }else if(m_action == 'G'){
        cout << "                                 *** **   ** ***       Guard!\n";
    }else if(m_action == 'D'){
        cout << "                                 *** **   ** ***       Dodge!\n";
    }else if(m_action == 'U'){
        cout << "                 " << setw(5) << -m << "           *** **   ** ***       Ultimate Attack!\n";
    }else{
        cout << "                                 *** **   ** ***       \n";	
    }
    cout << "                                  ** **   ** **        \n";
    cout << "                   ***             *         *         \n";
    if(p_action == 'A'){
        cout << "        Attack!    ***  *           *********          \n";		
    }else if(p_action == 'H'){
        cout << "      Heal! +" << setw(2) << p << "    ***  *           *********          \n";
    }else if(p_action == 'G'){
        cout << "         Guard!    ***  *           *********          \n";
    }else if(p_action == 'D'){
        cout << "         Dodge!    ***  *           *********          \n";
    }else{
        cout << "                   ***  *           *********          \n";	
    }
    cout << "                    *  *       ***  *  *  *            \n";
    cout << "                  *****           **   *   *           \n";
    cout << "                    *                  *    ***        \n";
    cout << "                   * *               **        *       \n";
    cout << "                  *   *                                \n";
    cout << "                                                       \n";
};

void playerWin(){	
    cout << "*******************************************************\n";
    for(int i = 0; i < 3; i++) cout << "*                                                     *\n";
    cout << "*                   YOU WIN!!!                        *\n";
    for(int i = 0; i < 3; i++) cout << "*                                                     *\n";
    cout << "*******************************************************\n";
};

void playerLose(){
    cout << "*******************************************************\n";
    cout << "*                                                     *\n";
    cout << "*                   YOU LOSE!!!                       *\n";
    cout << "*                                                     *\n";
    cout << "*******************************************************\n";
};