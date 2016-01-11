#ifndef CONFIG_H
#define CONFIG_H


class Config
{
public:
    Config(){}

    //General
    static const int KEYS_TIMER = 20;
    static const int NB_CELLS = 20000;
    static const double START_LIFE = 500;
    static const double BASE_SPEED_CELL = 5;

    //Settler
    static const int SETTLER_OFF_AREA = 100;
    static const int SETTLER_ON_AREA = 10000;
    static const int PROBABILITY_MALUS_CELL = 0;
    static const int PROBABILITY_BONUS_CELL = 100;

    //BorderGuard
    static const int BORDERGUARD_AREA = 11000;

    //Keys
    static const char INIT_AUTHORIZED_DIRECTION = 0b11111111;
    static const char INIT_KEYS_STATMENT = 0b00000000;
    /*w*/ static const char ACTION_UP = 0b00000001;
    /*a*/ static const char ACTION_LEFT = 0b00000010;
    /*s*/ static const char ACTION_DOWN = 0b00000100;
    /*d*/ static const char ACTION_RIGHT = 0b00001000;
    /*w+a*/ static const char ACTION_UP_LEFT = 0b00000011;
    /*a+s*/ static const char ACTION_DOWN_LEFT = 0b00000110;
    /*s+d*/ static const char ACTION_DOWN_RIGHT = 0b00001100;
    /*d+w*/ static const char ACTION_UP_RIGHT = 0b00001001;

};

#endif // CONFIG_H
