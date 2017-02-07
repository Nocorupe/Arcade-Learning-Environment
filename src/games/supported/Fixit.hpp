#ifndef __FIXIT_HPP__
#define __FIXIT_HPP__

#include "../RomSettings.hpp"


// RL wrapper for Fixit
class FixitSettings : public RomSettings {

    public:

        FixitSettings();

        // reset
        void reset();

        // is end of game
        bool isTerminal() const;

        // get the most recently observed reward
        reward_t getReward() const;

        // the rom-name
        const char* rom() const { return "fixit"; }

        // create a new instance of the rom
        RomSettings* clone() const;

        // is an action part of the minimal set?
        bool isMinimal(const Action& a) const;

        // process the latest information from ALE
        void step(const System& system);

        // saves the state of the rom settings
        void saveState(Serializer & ser);
    
        // loads the state of the rom settings
        void loadState(Deserializer & ser);

        virtual const int lives() { return isTerminal() ? 0 : m_lives; }

    private:

        bool m_terminal;
        reward_t m_reward;
        reward_t m_score;
        int m_lives;
      
        static ActionVect actions;
};

#endif // __FIXIT_HPP__

