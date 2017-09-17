### Path Planning Project

In this project we design a path planning algorithm which is deployed in the
udacity term 3 simulator. The simulator gives us the needed information of our
surroundings. We know our own position and the path of the lanes and we get the
position and speed of other vehicles on the road from sensor fusion.


#### Finite State Machine
 We propose a finite state machine with three different states. These
 are the following:
 - KL: Keep lane
 - LCL: Lane change left
 - LCR: Lane change right

###### Keep Lane
We stay in our current lane if we are in the middle lane or if a vehicle is in
front of us and we can't get pass because the left and right lanes are occupied.

###### Lane Change Left and Lane Change Right
We overtake if a vehicle gets in front of us and if the neighboring lanes
are free. We also try to stay in the middle lane if possible for better
positioning

#### Trajectory
Our trajectory consists of a third order polynomial, which is fit through a set
of sparse anchor points. Spreading these anchor points farther away result in
smoother lane changes but we need bigger safe distances in return. For further
smoothness we use some of our previous generated way points instead of fitting
completely new polynomials every cycle.

If a car is in front of us and we can't overtake it, we will generate way points
that match roughly the speed of this vehicle.
