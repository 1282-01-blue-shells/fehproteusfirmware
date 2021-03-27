#ifndef FEHMOTOR_H
#define FEHMOTOR_H

#include "derivative.h"

/**
* @brief Access to the motor attatchments for the Proteus
*
* Allows user to interact with individual motor speed and direction
*/
class FEHMotor
{
public:

    // Create motor states for all separate motors
    typedef enum
    {
        Motor0 = 0,
        Motor1,
        Motor2,
        Motor3
    } FEHMotorPort;

    /**
     * @brief Declares an addition of a new motor attatchment to the Proteus
     * 
     * @param motorport
     *      The motor port that a new motor has been attatched to
     * 
     * @param max_voltage
     *      Max voltage for corresponding motor
     * 
     * Initializes motor port and max voltage to nothing greater than 12V.
     * Also calculates {@code _max_percent} as a linear relationship
     */
    FEHMotor( FEHMotorPort motorport, float max_voltage );

    /**
     * @brief Stops motion of motor
     * 
     * Sets {@code _power} to 0 if it is not already at 0
     */
    void Stop();

    /**
     * @brief Sets motor speed to a percentage of its maximum speed
     * 
     * @param percent
     *      The percentage of the motor maximum speed utilized for
     *      motion
     * 
     * Sets power of motor based on {@param percent} and calls private
     * member {@code SetPower} to process the specified percentage
     */
	void SetPercent( float percent );

private:
    void SetPower( int power );
    float _max_percent;
    FEHMotorPort _motorport;
	char _power;
};

#endif // FEHMOTOR_H
