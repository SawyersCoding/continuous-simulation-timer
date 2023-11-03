/**
 * @file updateable.h
 * @author Sawyer Stanley (sawyerscoding@gmail.com)
 * @brief An interface for objects that can be updated. Used by ContinuousSimTimers to update 
 * objects at regular intervals. 
 * @version 0.1
 * @date 2023-11-02
 */

#ifndef UPDATEABLE_H
#define UPDATEABLE_H

class Updateable{

    public:
        virtual void update() = 0;

};

#endif // UPDATEABLE_H