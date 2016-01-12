#ifndef CONFIG_H
#define CONFIG_H


class Config
{
public:
    Config(){}

    //General
    static const int KEYS_TIMER = 10;
    static const int NB_CELLS = 1000;
    static const double START_LIFE = 1000;

    // mouvements
    static const double DIAGONAL_SPEED_MULTIPLICATOR = 0.707;
    static const double BASE_SPEED_CELL = 5;
    static const double BONUS_SPEED_REGRESSION = 0.95;

    //Settler
    static const int SETTLER_OFF_AREA = 500;
    static const int SETTLER_ON_AREA = 3000;
    static const int PROBABILITY_MALUS_CELL = 10;
    static const int PROBABILITY_BONUS_CELL = 10;

    //colider
    static const double COLIDER_ACTIVE_AREA = 3000;
    static const int COLIDER_TIMER = 100;


    //BorderGuard
    static const int BORDERGUARD_AREA = 5000;
    static const int BORDERGUARD_SLEEP = 600;

    //direction
    static const char DIRECTION_AUTHORIZED_ALL = 0b11111111;
    static const char DIRECTION_AUTHORIZED_NONE = 0b00000000;
    static const char DIRECTION_UNAUTHORIZED_UP = 0b11111110;
    static const char DIRECTION_UNAUTHORIZED_DOWN = 0b11111011;
    static const char DIRECTION_UNAUTHORIZED_LEFT = 0b11111101;
    static const char DIRECTION_UNAUTHORIZED_RIGHT = 0b11110111;

    //Key
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
