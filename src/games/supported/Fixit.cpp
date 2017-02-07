#include "Fixit.hpp"
#include "../RomUtils.hpp"

ActionVect FixitSettings::actions;

FixitSettings::FixitSettings() {
    reset();
}


/* create a new instance of the rom */
RomSettings* FixitSettings::clone() const { 
    
    RomSettings* rval = new FixitSettings();
    *rval = *this;
    return rval;
}


/* process the latest information from ALE */
void FixitSettings::step(const System& system) {

    // update the reward
    reward_t score = getDecimalScore( 0xD4,0xD3,0xD2, &system);

    m_reward = score - m_score;
    m_score = score;

    // update terminal status
    int lives_byte = readRam(&system, 0xC2);
    m_terminal = (lives_byte == 0x00);

    // popcount
    int a = lives_byte & 0xFF;
    a = (a & 0x55) + ((a & 0xAA) >> 1); 
    a = (a & 0x33) + ((a & 0xCC) >> 2); 
    a = (a & 0x0F) + ((a & 0xF0) >> 4); 
    m_lives = a;
}


/* is end of game */
bool FixitSettings::isTerminal() const {

    return m_terminal;
};


/* get the most recently observed reward */
reward_t FixitSettings::getReward() const { 

    return m_reward; 
}


/* is an action part of the minimal set? */
bool FixitSettings::isMinimal(const Action &a) const {

    switch (a) {
        case PLAYER_A_NOOP:
        case PLAYER_A_FIRE:
        case PLAYER_A_UP:
        case PLAYER_A_RIGHT:
        case PLAYER_A_LEFT:
        case PLAYER_A_DOWN:
            return true;
        default:
            return false;
    }
}


/* reset the state of the game */
void FixitSettings::reset() {
    
    m_reward   = 0;
    m_score    = 0;
    m_terminal = false;
    m_lives = 3;
}

        
/* saves the state of the rom settings */
void FixitSettings::saveState(Serializer & ser) {
  ser.putInt(m_reward);
  ser.putInt(m_score);
  ser.putBool(m_terminal);
  ser.putInt(m_lives);
}

// loads the state of the rom settings
void FixitSettings::loadState(Deserializer & ser) {
  m_reward = ser.getInt();
  m_score = ser.getInt();
  m_terminal = ser.getBool();
  m_lives = ser.getInt();
}

