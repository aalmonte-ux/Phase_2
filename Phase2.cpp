#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ANSI color codes for styling
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";
const string WHITE = "\033[37m";

// Function declarations
void waitForEnter();
void TrainingLoop();
void startNewGame();
void BattleLoop();

// PLAYER STATS
int stats[5] = {50, 10, 15, 5};
             //HP, ATK, END, EP
double epRegen = 0.0;   
int trainCount[5] = {0, 0, 0, 0, 0};


// Gates / Skills
const int NUM_SKILLS = 8;
bool skillsUnlocked[NUM_SKILLS + 1] = {false};
bool gateActive[NUM_SKILLS + 1] = {false};

// Player skills and training history
vector<string> playerSkills;
vector<string> trainingHistory;


void waitForEnter() {
    cout << CYAN << "*Press Enter to continue...*" << RESET;
    cin.ignore();
}

// ------------------- START NEW GAME -------------------
void startNewGame() {
    cout << BLUE << "\n--- NEW GAME STARTED ---\n\n" << RESET;
    string name;
    cout << "Enter your character name: ";
    cin >> name;
    cin.ignore();

    cout << MAGENTA
         << "*The sun rises over Cocoyashi Village. Peace once thrived here, but shadows fall.*\n"
         << "*Arlong and his crew have seized the village, leaving fear behind.*\n"
         << "*You, " << name << ", stand powerless as tragedy unfolds.*\n"
         << "*Bell-mère’s sacrifice sparks a burning resolve within you.*\n"
         << "*Your journey begins: grow stronger, return, and protect those you love.*\n\n"
         << RESET;



             waitForEnter();
          
    TrainingLoop();
}

// ------------------- TRAINING LOOP -------------------
void TrainingLoop() {
    const int totalTurns = 48;

    for (int turn = 1; turn <= totalTurns; turn++) {
        bool confirmed = false;

        while (!confirmed) {
            cout << GREEN << "\n========================" << RESET << "\n";
            cout << YELLOW << "--- Training Turn " << turn << " / " << totalTurns << " ---\n" << RESET;

            cout << "*You wake on a quiet island; remnants of the storm surround you.*\n";
            cout << "*A tattered scroll lies at your feet: 'The Eight Inner Gates'.*\n";
            cout << "*Your body aches, but your spirit is determined.*\n\n";

            cout << "Choose training focus:\n";
            cout << "1. HP\n2. ATK\n3. END\n4. EP\n5. EP Regen\n6. Self-Discovery\n";

            int choice;
            while (true) {
                cout << "Choose training focus (1-6): ";
                if (!(cin >> choice)) {  // if input fails (not an int)
                    cin.clear();         // clear fail state
                    cin.ignore(); // discard bad input
                    cout << RED << "Invalid input! Enter a number 1-6.\n" << RESET;
                    continue; // ask again
                }
                cin.ignore(); 
                if (choice >= 1 && choice <= 6) break; // valid
                cout << RED << "Choice must be 1-6!\n" << RESET;
            }


            int index = -1;
            double gain = 0.0;

            if (choice >= 1 && choice <= 4) {
                index = choice - 1;
                int n = trainCount[index] + 1;
                switch(index) {
                    case 0: gain = 21 + 4*(n-1); break; // HP
                    case 1: gain = 11 + 2*(n-1); break; // ATK
                    case 2: gain = 15 + 3*(n-1); break; // END
                    case 3: gain = 15 + 3*(n-1); break; // EP
                }
                cout << CYAN << "\n*You focus intently...*\n" << RESET;
                cout << GREEN
                     << (index==0?"HP":index==1?"ATK":index==2?"END":"EP")
                     << " +" << gain << "!\n" << RESET;
            }
            else if (choice == 5) { // EP Regen
                index = 4;
                int n = trainCount[index] + 1;
                gain = 2.5 + 0.5*(n-1);
                cout << CYAN << "\n*You focus your life energy rhythmically...*\n" << RESET;
                cout << GREEN << "EP Regen +" << gain << "!\n" << RESET;
            }

            cout << "*Commit to this training? (y/n):* ";
            char confirmInput;
            cin >> confirmInput; cin.ignore();

            if (confirmInput=='y' || confirmInput=='Y') {
                if(index==4) epRegen += gain;
                else stats[index] += static_cast<int>(gain);
                trainCount[index]++;
                trainingHistory.push_back(
                    index==0?"HP":index==1?"ATK":index==2?"END":index==3?"EP":"EP Regen"
                );
                cout << GREEN << "*Strength and control surge through you.*\n" << RESET;
                confirmed = true;
            } else {
                cout << RED << "*You reconsider and choose another focus.*\n" << RESET;
            }

            if(choice==6) { // Self-Discovery
                bool allUnlocked = true;
                for(int g=1; g<=NUM_SKILLS; g++) {
                    if(!skillsUnlocked[g]) { allUnlocked=false; break; }
                }
                if(allUnlocked) { cout << CYAN << "*All hidden powers awakened.*\n" << RESET; continue; }

                for(int g=1; g<=NUM_SKILLS; g++) {
                    if(!skillsUnlocked[g] && (g==1 || skillsUnlocked[g-1])) {
                        skillsUnlocked[g] = true;
                        string skillName;
                        switch(g) {
                            case 1: skillName="Gate of Opening (G1)"; break;
                            case 2: skillName="Chain Handling"; break;
                            case 3: skillName="Keigan Barrage"; break;
                            case 4: skillName="Front Lotus (Omote Renge)"; break;
                            case 5: skillName="Gate of Opening – Mastery"; break;
                            case 6: skillName="Gate of Healing (G2)"; break;
                            case 7: skillName="Chain Barrage"; break;
                            case 8: skillName="Reverse Lotus (Ura Renge)"; break;
                        }
                        playerSkills.push_back(skillName);
                        trainingHistory.push_back("Self-Discovery");
                        cout << MAGENTA << "\n*Hidden power awakens!* Skill unlocked: " << skillName << "!\n" << RESET;
                        break;
                    }
                }
                confirmed = true;
            }

            cout << BLUE << "\n--- Current Stats ---\n" << RESET;
            cout << "HP: " << stats[0] << " | ATK: " << stats[1] << " | END: " << stats[2] << "\n";
            cout << "EP: " << stats[3] << " | EP Regen: " << epRegen << "\n";
            cout << "Skills: "; for(string s:playerSkills) cout<<s<<" | "; cout<<"\n";
            waitForEnter();
        }
    }



    BattleLoop();
}

void BattleLoop() {
    int playerHP = stats[0];
    double playerEP = stats[3];
    bool gateActive[NUM_SKILLS + 1] = {false};
    bool bossStaggered = false;
    int turn = 1;

    int bstatsBase[3] = {2500, 520, 600};
    int bstatsKiribachi[3] = {1600, 550, 600};
    int bstatsEnraged[3] = {900, 600, 660};

    int bossHP = bstatsBase[0];
    int bossATK = bstatsBase[1];
    int bossEND = bstatsBase[2];
    int bossPhase = 1;

    cout << GREEN << "\n--- Battle Start: Arlong ---\n" << RESET;
    cout << "*The infamous Arlong awaits. Cocoyashi's fate is in your hands.*\n";
    cout << "*You recall Bell-mère's sacrifice and eight years of training.*\n";

    while (playerHP > 0 && bossHP > 0) {
        cout << YELLOW << "\n========================" << RESET << "\n";
        cout << CYAN << "--- Turn " << turn << " ---\n" << RESET;
        cout << "Player HP: " << playerHP << " | EP: " << playerEP << "\n";
        cout << "Boss HP: " << bossHP << " | Phase: ";
        if (bossPhase == 1) cout << "Base\n";
        else if (bossPhase == 2) cout << "Kiribachi\n";
        else if (bossPhase == 3) cout << "Enraged\n";

        playerEP += epRegen;
        if (gateActive[1]) playerEP -= 7;
        if (gateActive[6]) playerEP -= 9;
        if (playerEP < 0) {
            playerEP = 0;
            stats[1] /= 1.5;
            stats[2] /= 1.4;
            cout << RED << "*Gates crashed! ATK and END reduced.*\n" << RESET;
        }

        cout << "Choose action:\n";
        cout << "1. Basic Attack\n2. Use Skill\n3. Toggle Gate\n";
        int action; cin >> action; cin.ignore();

        if (action == 1) {
            int dmg = stats[1] - bossEND; if (dmg < 0) dmg = 0; bossHP -= dmg;
            cout << GREEN << "*You strike with the fury of eight years of training!*" << RESET << "\n";
            cout << "Dealt " << dmg << " damage!\n";
        } else if (action == 2) {
            if (playerSkills.empty()) cout << RED << "*No skills unlocked yet!*" << RESET << "\n";
            else {
                cout << "Choose skill:\n";
                for (size_t i = 0; i < playerSkills.size(); i++) cout << i+1 << ". " << playerSkills[i] << "\n";
                int skChoice; cin >> skChoice; cin.ignore();
                if (skChoice < 1 || skChoice > playerSkills.size()) cout << RED << "*Invalid skill.*" << RESET << "\n";
                else {
                    string skill = playerSkills[skChoice-1];
                    if (skill == "Gate of Opening (G1)" && turn < 3)
                        cout << RED << "*G1 cannot be activated until Turn 3.*" << RESET << "\n";
                    else {
                        cout << GREEN << "*You unleash " << skill << "!*\n" << RESET;
                        if (skill == "Front Lotus (Omote Renge)" || skill == "Reverse Lotus (Ura Renge)") {
                            cout << MAGENTA << "*Arlong is staggered!*\n" << RESET;
                            bossStaggered = true;
                        }
                        bossHP -= stats[1] * 2;
                        cout << "Dealt " << stats[1] * 2 << " damage!\n";
                    }
                }
            }
        } else if (action == 3) {
            cout << "Toggle Gate: 1. G1  2. G2\nChoice: ";
            int gateChoice; cin >> gateChoice; cin.ignore();
            if ((gateChoice == 1 && skillsUnlocked[1]) || (gateChoice == 6 && skillsUnlocked[6])) {
                gateActive[gateChoice] = !gateActive[gateChoice];
                cout << (gateChoice == 1 ? "G1" : "G2") << " is now " << (gateActive[gateChoice] ? "ON" : "OFF") << "\n";
            } else cout << RED << "*Gate cannot be toggled or not unlocked.*\n" << RESET;
        } else cout << RED << "*Invalid action.*\n" << RESET;

        if (!bossStaggered && bossHP > 0) {
            int dmgTaken = bossATK - stats[2]; if (dmgTaken < 0) dmgTaken = 0; playerHP -= dmgTaken;
            cout << RED << "*Arlong attacks!*" << RESET << "\n";
            cout << "You took " << dmgTaken << " damage.\n";
        } else if (bossStaggered) {
            cout << MAGENTA << "*Arlong misses his turn!*\n" << RESET;
            bossStaggered = false;
        }

        if (bossPhase == 1 && bossHP <= 1600) 
        { bossPhase = 2; 
        bossATK = bstatsKiribachi[1]; 
        bossEND = bstatsKiribachi[2]; 
        cout << RED << "*Arlong grows aggressive!*" << RESET << "\n"; }
        
        else if (bossPhase == 2 && bossHP <= 900) 
        { bossPhase = 3; 
        bossATK = bstatsEnraged[1];
        bossEND = bstatsEnraged[2]; 
        cout << RED << "*Arlong enters berserk!*" << RESET << "\n"; }

        if (playerHP <= 0) {
            cout << RED << "\n*You were defeated... thrown into the sea.*\n*[Alternate Ending Triggered: The Loop]*\n" << RESET;
            return;
        }
        if (bossHP <= 0) {
            cout << GREEN << "\n*Arlong has fallen! Cocoyashi Village is free!*" << RESET << "\n";
            cout << "*Villagers celebrate; Nami runs to you, tears and laughter in her eyes.*\n";
            cout << "Nami: 'Keigan... you came back!'\n";
            cout << "Keigan: '*I promised... I’m here to end it.*'\n";
            cout << "*The Straw Hats cheer, Luffy grinning from ear to ear.*\n";
            cout << "Luffy: 'Oi, Keigan! You’re strong — come with us!'\n";
            cout << "Keigan: 'Guess I’ll handle the bookkeeping, then.'\n";
            cout << "*The crew erupts in laughter; freedom feels lighter than ever.*\n";
            return;
        }

        turn++;
    }
}


int main() {
    int option;

    while (true) {
        cout << BLUE << "MAIN MENU\n1. New Game\n2. Quit\nEnter option: " << RESET;
        cin >> option; cin.ignore();

        if (option == 1) {
            startNewGame();
            break; // exit after game ends
        }
        else if (option == 2) {
            cout << RED << "*Goodbye!*" << RESET << "\n";
            break;
        }
        else {
            cout << RED << "Invalid option! Please choose again.\n" << RESET;
        }
    }

    return 0;
}

