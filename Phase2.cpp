#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// ANSI color codes for styling
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";

// Global Variables
string name;



// Player stats: HP, ATK, END, EP
int stats[4] = {50, 10, 15, 5};
double epRegen = 0.0;
int trainCount[5] = {0,0,0,0,0};

// Skill system
const int NUM_SKILLS = 8;
bool skillsUnlocked[NUM_SKILLS + 1] = {false}; 
int skillCooldown[NUM_SKILLS + 1] = {0};      


vector<string> playerSkills;
vector<string> trainingHistory;


// Arlong's stats
int bstatsBase[3] = {2500, 520, 600};
int bstatsKiribachi[3] = {1600, 550, 600};
int bstatsEnraged[3] = {900, 600, 660};

// Utility Functions
void waitForEnter() {
    cout << CYAN;
    cout << "*Press Enter to continue...*";
    cout << RESET;
    cin.ignore();
}
int calcDamage(int atk, int def, double multiplier=1.0) {
    int dmg = ceil((atk * multiplier - def) / 2.0);
    if(dmg < 1) dmg = 1;
    return dmg;
}

int getValidatedInput(int min, int max) {
    
    int choice;
    
    while (true) 
    {
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << RED;
            cout << "Invalid input! Enter a number ";
            cout << min;
            cout << "-";
            cout << max;
            cout << ".\n";
            cout << RESET;
            continue;
        }
        
        cin.ignore(10000, '\n');
        if (choice < min || choice > max) {
            cout << RED;
            cout << "Choice must be ";
            cout << min;
            cout << "-";
            cout << max;
            cout << "!\n";
            cout << RESET;
            continue;
        }
        return choice;
    }
}
//TRAINING LOOP
void TrainingLoop() {

    const int totalTurns    = 48;      // Total training turns
    for (int turn = 1; turn <= totalTurns; turn++) 
    {

        bool confirmed       = false;

        while (!confirmed) {

            //HEADER
            
            cout << GREEN << "\n\n======================================================";
            cout << RESET;
            cout << endl;
            
            cout << YELLOW;
            cout << "--- Training Turn ";
            cout << turn;
            cout << " / ";
            cout << totalTurns;
            cout << " ---";
            cout << endl;
            cout << RESET;

            // STORY NARRATION
            
            cout << MAGENTA;
            cout << "\n*The morning sun pierces the heavy mist that blankets the island.*";
            cout << endl;
            cout << "*Remnants of the storm litter the shore: branches broken, leaves scattered, water pools reflecting the light.*";
            cout << endl;
            cout << "*A tattered scroll flutters gently in the breeze, the words barely legible: 'The Eight Inner Gates'.*";
            cout << endl;
            cout << "*You kneel, feeling the faint resonance of power inside your chest.*";
            cout << endl;
            cout << "\n*Your body aches, your muscles tense, your bones stiff from previous training.*";
            cout << endl;
            cout << "*But your spirit ignites like wildfire. Determination surges.*";
            cout << endl;
            cout << "*The wind carries distant sounds of crashing waves, like a drum urging you forward.*\n";
            cout << endl;
            cout << RESET;

            waitForEnter(); // First pause 

            //TRAINING OPTIONS
            cout << CYAN;
            cout << "\nChoose your focus for this day of training.";
            cout << endl;
            cout << "Each choice will shape your body, mind, and spirit.\n";
            cout << endl;
            cout << "1. HP (Strengthen your body and resilience)";
            cout << endl;
            cout << "2. ATK (Sharpen your offensive power)";
            cout << endl;
            cout << "3. END (Harden your endurance and defense)";
            cout << endl;
            cout << "4. EP (Develop your inner energy to use skills effectively)";
            cout << endl;
            cout << "5. EP Regen (Learn to restore energy more efficiently)";
            cout << endl;
            cout << "6. Self-Discovery (Unlock hidden potential and secret skills)";
            cout << endl;
            cout << RESET;

            int choice = getValidatedInput(1, 6);
            int index  = -1;
            double gain= 0.0;

            // STAT GAINS
            if (choice >= 1 && choice <= 4) {

                index              = choice - 1;
                int n              = trainCount[index] + 1;

                switch (index) {
                    
                    case 0: gain = 21 + 4 * (n - 1);
                    break;
                    
                    case 1: gain = 11 + 2 * (n - 1); 
                    break;
                    
                    case 2: gain = 15 + 3 * (n - 1); 
                    break;
                    
                    case 3: gain = 15 + 3 * (n - 1); 
                    break;
                    
                }

                cout << CYAN;
                cout << "\n*You center your mind, taking a deep breath.*";
                cout << endl;
                cout << "*Every muscle, every fiber, every sinew feels the pull of your intention.*";
                cout << endl;
                cout << "*Your vision narrows. The world blurs around you.*";
                cout << endl;
                cout << "*You focus entirely on " 
                     << (index == 0 ? "your body" :
                        index == 1 ? "your strikes" :
                        index == 2 ? "your endurance" : "your energy") 
                     << ".*";
                     cout << endl;
                cout << "*Time slows. Your heartbeat and breath synchronize into a perfect rhythm.*";
                cout << endl;
                
                cout << RESET;

                cout << GREEN;
                cout << (index == 0 ? "HP" : index == 1 ? "ATK" : index == 2 ? "END" : "EP") 
                     << " +" ;
                cout << gain;
                cout << "!" ;
                cout << endl;
                
                cout << RESET;
            }
            else if (choice == 5) {

                index = 4;
                int n = trainCount[index] + 1;
                gain = 2.5 + 0.5 * (n - 1);

                cout << CYAN;
                cout << "\n*You close your eyes and feel the energy flowing within.*";
                cout << endl;
                cout << "*Breath in, breath out, a pulse through your veins.*";
                cout << endl;
                cout << "*The island's quiet encourages your spirit to awaken.*";
                cout << endl;
                cout << "*EP flows through you like a gentle stream, rejuvenating your inner core.*";
                cout << endl;
                cout << RESET;

                cout << GREEN;
                cout << "EP Regen +";
                cout << gain;
                cout << "!";
                cout << endl;
                cout << RESET;
            }

            // ---------------- CONFIRMATION ----------------
            cout << "*Do you commit to this training? (y/n):* ";
            char confirmInput;
            cin >> confirmInput;
            cin.ignore(10000, '\n');

            if (confirmInput == 'y' || confirmInput == 'Y') {

                if (index == 4) 
                    epRegen += gain;
                else 
                    stats[index] += static_cast<int>(gain);

                trainCount[index]++;
                trainingHistory.push_back(
                    index == 0 ? "HP" : 
                    index == 1 ? "ATK" : 
                    index == 2 ? "END" : 
                    index == 3 ? "EP" : "EP Regen"
                );

                cout << GREEN;
                cout << "*Power surges through you.*";
                cout << endl;
                cout << "*Your body, mind, and soul feel strengthened.*";
                cout << endl;
                cout << "*A sense of accomplishment and potential fills you.*";
                cout << endl;
                cout << RESET;

                confirmed = true;
            }
            else if (choice != 6) {
                cout << RED;
                cout << "*You pause, reconsidering your focus, and adjust your approach.*";
                cout << endl;
                cout << RESET;
            }

            //SELF-DISCOVERY SKILLS
            if (choice == 6) {

                for (int g = 1; g <= NUM_SKILLS; g++) {
                    if (!skillsUnlocked[g] && (g == 1 || skillsUnlocked[g - 1])) {

                        skillsUnlocked[g] = true;
                        string skillName;

                        switch (g) {
                            case 1: skillName = "Gate of Opening (G1)"; 
                            break;
                            
                            case 2: skillName = "Chain Handling"; 
                            break;
                            
                            case 3: skillName = "Kei-ga-n Barrage!"; 
                            break;
                            
                            case 4: skillName = "Front Lotus (Omote Renge)"; 
                            break;
                            
                            case 5: skillName = "Gate of Opening – Mastery"; 
                            break;
                            
                            case 6: skillName = "Gate of Healing (G2)"; 
                            break;
                            
                            case 7: skillName = "Chain Barrage"; 
                            break;
                            
                            case 8: skillName = "Reverse Lotus (Ura Renge)"; 
                            break;
                        }

                        playerSkills.push_back(skillName);
                        trainingHistory.push_back("Self-Discovery");

                        cout << MAGENTA;
                        cout << "\n*Hidden power awakens!*";
                        cout << endl;
                        cout << "*Skill unlocked: ";
                        cout << skillName;
                        cout << ".*";
                        cout << endl;
                        cout << RESET;

                        waitForEnter(); // Second pause for skill unlock

                        break;
                    }
                }
                confirmed = true;
            }

            // CURRENT STATS
            cout << BLUE;
            cout << "\n================ CURRENT STATS ================\n";
            cout << RESET;
            cout << "HP:       " << stats[0] << "    |    ATK:       " ;
            cout << stats[1];
            cout << "    |    END:       " ;
            cout << stats[2];
            cout << endl;
            cout << "EP:       ";
            cout << stats[3];
            cout << "    |    EP Regen:   ";
            cout << epRegen;
            cout << endl;
            cout << "Skills: ";
            
            for(size_t i=0;i<playerSkills.size();i++){
    cout << playerSkills[i];
    if(i != playerSkills.size()-1) cout << ", ";
}

            cout << " | ";
            cout << "\n================================================\n";
            cout << RESET;

            waitForEnter();  // Third pause 

        } // end while confirmed
    } // end for turn
}

void CheckGateCrash(double &playerEP, int &ATK, int &END, bool &gate1, bool &gate2, bool mastery=false) {
    if(playerEP < 0) {
        playerEP = 0;
        ATK = ceil(ATK / (mastery ? 1.4 : 1.5));
        END = ceil(END / (mastery ? 1.4 : 1.5));
        gate1 = false;
        gate2 = false;
        cout << RED << "*Your Gates crash! ATK and END are severely reduced.*\n" << RESET;
    }
}


// BATTLE LOOP

void BattleLoop() {

    int playerHP          = stats[0];
    double playerEP       = stats[3];
    bool gateActiveLocal[NUM_SKILLS + 1] = {false};
    bool bossStaggered    = false;
    int turn              = 1;
    int bossHP            = bstatsBase[0];
    int bossATK           = bstatsBase[1];
    int bossEND           = bstatsBase[2];
    int bossPhase         = 1;

    cout << GREEN;
    cout << "\n======================================================";
    cout << endl;
    cout << "--- Battle Start: Arlong ---";
    cout << endl;
    cout << "======================================================";
    cout << RESET;
    cout << endl;

    cout << MAGENTA;
    cout << "*The infamous Arlong awaits. Cocoyashi's fate is in your hands.*\n";
    cout << "*The salty breeze mixes with the tension in the air.*\n";
    cout << "*You tighten your fists, feeling every scar from your training.*\n";
    cout << "*Your heart pounds. Today, you face your ultimate test.*\n";
    cout << RESET;

    waitForEnter();

    while(playerHP > 0 && bossHP > 0) {

        // START OF TURN: EP Regen and Gate Drain
        playerEP += epRegen;

        if(gateActiveLocal[1]) { 
            playerEP -= 7;
            cout << YELLOW << "*Gate of Opening drains 7 EP.*" << RESET << endl; }
        if(gateActiveLocal[6]) {
            playerEP -= 9;
            cout << YELLOW << "*Gate of Healing drains 9 EP.*" << RESET << endl; }

        // Check Gate Crash
        if(playerEP < 0) {
            playerEP = 0;
            stats[1] = static_cast<int>(stats[1] / (skillsUnlocked[5] ? 1.4 : 1.5));
            stats[2] = static_cast<int>(stats[2] / (skillsUnlocked[5] ? 1.4 : 1.5));
            gateActiveLocal[1] = false;
            gateActiveLocal[6] = false;
            cout << RED << "*Your Gates crash! ATK and END are severely reduced.*\n" << RESET;
        }

        // TURN HEADER
        cout << YELLOW << "\n======================================================\n" << RESET;
        cout << CYAN << "--- Turn " << turn << " ---" << RESET << endl;
        cout << BLUE << "Player HP: " << playerHP << "    |    EP: " << playerEP << endl;
        cout << "Boss HP: " << bossHP << "    |    Phase: ";
        if(bossPhase == 1) cout << "Base\n";
        else if(bossPhase == 2) cout << "Kiribachi\n";
        else cout << "Enraged\n";
        cout << "======================================================\n" << RESET;

        // PLAYER ACTION
        cout << CYAN << "\nChoose your action for this turn:\n";
        cout << "1. Basic Attack\n2. Use Skill\n3. Toggle Gate\n" << RESET;
        int action = getValidatedInput(1, 3);

        int dmg = 0;

        // BASIC ATTACK
        if(action == 1) {
            int baseATK = stats[1];
            double multiplier = 1.0;
            if(gateActiveLocal[1]) multiplier *= 1.8;
            if(gateActiveLocal[6]) multiplier *= 2.2;

            dmg = ceil((baseATK * multiplier - bossEND) / 2.0);
            if(dmg < 1) dmg = 1;
            bossHP -= dmg;

            cout << GREEN << "*You deal " << dmg << " damage to Arlong!*" << RESET << endl;
        }

        // USE SKILL
        else if(action == 2) {

            if(playerSkills.empty()) {
                cout << RED << "*No skills unlocked yet!*\n" << RESET;
            } else {

                cout << CYAN << "Choose a skill:\n" << RESET;
                for(size_t i = 0; i < playerSkills.size(); i++)
                    cout << i + 1 << ". " << playerSkills[i] << endl;

                int skChoice = getValidatedInput(1, playerSkills.size());
                string skill = playerSkills[skChoice - 1];

                // Gate of Opening (G1)
                if(skill == "Gate of Opening (G1)") {
                    if(turn < 3) cout << RED << "*G1 cannot be activated until Turn 3.*\n" << RESET;
                    else if(playerEP < 35) cout << RED << "*Not enough EP.*\n" << RESET;
                    else {
                        gateActiveLocal[1] = true;
                        playerEP -= 35;
                        cout << GREEN << "*Gate of Opening activated! ATK ×1.8.*\n" << RESET;
                    }
                }
                // Gate of Healing (G2)
                else if(skill == "Gate of Healing (G2)") {
                    if(!gateActiveLocal[1] || playerEP < 45) cout << RED << "*Cannot activate G2.*\n" << RESET;
                    else {
                        gateActiveLocal[6] = true;
                        playerEP -= 45;
                        cout << GREEN << "*Gate of Healing activated! ATK ×2.2.*\n" << RESET;
                    }
                }
                // Kei-ga-n Barrage
                else if(skill == "Kei-ga-n Barrage!") {
                    if(skillCooldown[3] > 0) cout << RED << "*Skill on cooldown.*\n" << RESET;
                    else if(playerEP < 12) cout << RED << "*Not enough EP.*\n" << RESET;
                    else {
                        dmg = calcDamage(stats[1], bossEND, 0.45);
                        bossHP -= dmg;
                        playerEP -= 12;
                        skillCooldown[3] = 2;
                        cout << GREEN << "*Kei-ga-n Barrage deals " << dmg << " damage!*" << RESET << endl;
                    }
                }
                // Front Lotus
                else if(skill == "Front Lotus (Omote Renge)") {
                    if(skillCooldown[4] > 0) cout << RED << "*Skill on cooldown.*\n" << RESET;
                    else if(!skillsUnlocked[3] || !gateActiveLocal[1] || playerEP < 13)
                        cout << RED << "*Cannot use Front Lotus.*\n" << RESET;
                    else {
                        dmg = ceil((stats[1]*0.95 - bossEND*0.7)/2.0);
                        if(dmg < 1) dmg = 1;
                        bossHP -= dmg;
                        playerEP -= 13;
                        skillCooldown[4] = 3;
                        bossStaggered = true;
                        cout << GREEN << "*Front Lotus hits! Damage: " << dmg << "*\n" << RESET;
                    }
                }
                // Chain Barrage
                else if(skill == "Chain Barrage") {
                    if(skillCooldown[7] > 0) cout << RED << "*Skill on cooldown.*\n" << RESET;
                    else if(!skillsUnlocked[2] || playerEP < 14) cout << RED << "*Cannot use Chain Barrage.*\n" << RESET;
                    else {
                        dmg = ceil((stats[1]*0.5 - bossEND*0.9)/2.0);
                        if(dmg < 1) dmg = 1;
                        bossHP -= dmg;
                        playerEP -= 14;
                        skillCooldown[7] = 3;
                        cout << GREEN << "*Chain Barrage deals " << dmg << " damage.*\n" << RESET;
                    }
                }
                // Reverse Lotus
                else if(skill == "Reverse Lotus (Ura Renge)") {
                    if(skillCooldown[8] > 0) cout << RED << "*Skill on cooldown.*\n" << RESET;
                    else if(!gateActiveLocal[6] || playerEP < 25)
                        cout << RED << "*Cannot use Reverse Lotus.*\n" << RESET;
                    else {
                        dmg = ceil((stats[1]*1.25 - bossEND*0.65)/2.0);
                        if(gateActiveLocal[6]) dmg += ceil(stats[1]*0.3);
                        bossHP -= dmg;
                        playerEP -= 25;
                        skillCooldown[8] = 5;
                        cout << GREEN << "*Reverse Lotus hits! Damage: " << dmg << "*\n" << RESET;
                    }
                }

            }
        }

        // TOGGLE GATE
        else if(action == 3) {
            cout << CYAN << "\nToggle Gate: 1. G1    2. G2\nChoice: " << RESET;
            int gchoice = getValidatedInput(1, 2);
            int gateIndex = (gchoice == 1 ? 1 : 6);
            if(skillsUnlocked[gateIndex]) {
                if(!gateActiveLocal[gateIndex] && playerEP < (gateIndex==1?35:45))
                    cout << RED << "*Not enough EP to activate this Gate.*\n" << RESET;
                else {
                    gateActiveLocal[gateIndex] = !gateActiveLocal[gateIndex];
                    cout << GREEN << (gateIndex==1?"G1":"G2") << " is now " << (gateActiveLocal[gateIndex]?"ON":"OFF") << "\n" << RESET;
                }
            } else cout << RED << "*Gate not unlocked yet.*\n" << RESET;
        }

        // BOSS ATTACK
        if(!bossStaggered && bossHP > 0) {
            int dmgTaken = ceil((bossATK - stats[2])/2.0);
            if(dmgTaken < 1) dmgTaken = 1;
            playerHP -= dmgTaken;
            cout << RED << "*Arlong attacks! You take " << dmgTaken << " damage.*\n" << RESET;
        } else bossStaggered = false;

        // BOSS PHASE CHANGE
        if(bossPhase == 1 && bossHP <= 1600) { 
            bossPhase = 2;
            bossATK = bstatsKiribachi[1]; 
            bossEND = bstatsKiribachi[2]; 
            cout << RED << "*Arlong becomes more aggressive!*\n" << RESET; }
        else if(bossPhase == 2 && bossHP <= 900) {
            bossPhase = 3; 
            bossATK = bstatsEnraged[1];
            bossEND = bstatsEnraged[2]; 
            cout << RED << "*Arlong goes berserk!*\n" << RESET; }

        // DECREMENT SKILL COOLDOWNS
        for(int i=0;i<=NUM_SKILLS;i++) if(skillCooldown[i]>0) skillCooldown[i]--;

        // WIN/LOSS CHECK
        if(playerHP <= 0) { cout << RED << "*You were defeated...*\n"; return; }
        if(bossHP <= 0) { cout << GREEN << "*Arlong defeated!*\n"; return; }

        turn++;
    }
}



// START NEW GAME
void startNewGame() {
    skillCooldown[2] = 2;           // Kei-ga-n Barrage
    
    cout << BLUE;
    cout << "\n======================================================";
    cout << endl;
    cout << "--- NEW GAME STARTED ---";
    cout << endl;
    cout << "======================================================";
    cout << RESET;
    cout << endl;

    cout << CYAN;
    cout << "Enter your character name: ";
    cin >> name;
    cin.ignore(10000, '\n');

    cout << MAGENTA;
    cout << "\n\n*The first rays of the morning sun spill over Cocoyashi Village, casting golden light on the rooftops.*\n";
    cout << "*A soft breeze carries the scent of the sea, but the air is heavy with fear and tension.*\n";
    cout << "\n*Bell-mère stands tall in the village square, her eyes blazing with determination as she faces Arlong.*\n";
    cout << "Bell-mère: \"I paid for my daughters! I will not let you take them!\"\n";
    cout << "\n*The sound of the gunshot echoes through the air, followed by a tense silence.*\n";
    cout << "*Nami screams, her voice trembling in fear, clutching onto your hand.*\n\n";
    cout << name << ": \"YOU—! How dare you!\"\n";
    cout << "*You rush forward, fueled by anger and desperation. Your fists connect with Arlong's chest, but he barely flinches.*\n";
    cout << "Arlong (laughs cruelly): \"Pathetic. Is that all you’ve got?\"\n";
    cout << "*\nA powerful wave knocks you off balance, and the icy waters of the sea engulf you.*\n";
    cout << "*You sink beneath the surface, the world around you turning dark and silent.*\n\n";
    cout << RESET;

    waitForEnter();  

    cout << MAGENTA;
    cout << "\n*Your lungs burn as you struggle to break free, but your body is weak and battered.*\n";
    cout << "*Amid the darkness, a faint voice echoes in your mind, almost like a whisper:* \n";
    cout << "\"Train. Train until you are stronger than the storm, stronger than your fear.\"\n";
    cout << "*Images of your past training flash before your eyes—hours of sweat, pain, and determination.*\n";
    cout << "*Your fists clench instinctively, and a spark of resolve ignites within your heart.*\n";
    cout << "*You kick off the seabed, surfacing with renewed purpose. Today, your journey truly begins.*\n\n";
    cout << RESET;

    waitForEnter();  

    cout << GREEN;
    cout << "\n\n*You rise from the water, soaked and shivering, but your spirit burns brighter than ever.*\n";
    cout << "*The path ahead is long, but you know one thing for certain:* You will train, you will grow, and you will return to face Arlong.\n\n";
    cout << RESET;

    TrainingLoop();
    BattleLoop();
}


//MAIN MENU
int main() {
    int option;
    while(true) {
        cout << BLUE << "\nMAIN MENU\n";
        cout << "1. New Game\n";
        cout << "2. Quit\n";
        cout << "Enter option: " << RESET;
        option = getValidatedInput(1,2);

        if(option==1) {
            
            startNewGame();
            break;
            
        }
        else 
        {
            cout << RED;
            cout << "*Goodbye!*";
            cout << RESET;
            cout << "\n";
            break;
        }
    }
    return 0;
}
