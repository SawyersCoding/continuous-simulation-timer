# continuous-simulation-timer

This timer is useful for executing code you wish to run at regular real-world timer intervals.

Consider a simulation with entities that change state as simulation-time progresses. These entities would implement the Updateable interface and be added to a ContinuouSimTimer's set of Updateable entities. At a specified rate, the timer will asyncronously invoke the update method on each of the Updateable entities. This allows real-world time to continue while the simulation updates.

Ongoing issues. 

1) Timing. Within the main loop of a timer that has started, conditions are checked, values are incremented, and sometimes exteral loops are entered. This implementation assumes this operations are completed instantly.

To accomodate for this, I would like to try using the system's current time in milliseconds to track time instead of dealing with the Sleep/usleep functions. This will fix the real-world timing issue (I believe), but not necessarily the consistent update rate. That issue, though, is equivalent to frame rate issues and must be accounted for by the user.

2) I'm not sure of the effects when several entities that are updating asyncronously attempt to alter the same value in another class. This will require some testing.

If the effects are undesireable, creating a proxy with which an entitiy can interact that then needs to be reconsiled upon the joining of threads is something I'd like to attempt.