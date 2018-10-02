# Mappy

A simulator for self-driven cars traffic.

## Concept

The purpose of this simulation is to explore road traffic in which vehicles are autonomous and can share information with each other.

At the beginning, a car has no other data than its randomly chosen first position and destination.
Then each vehicle tries to get to the exit as quickly as possible, taking into account the information it receives from other vehicles.

Every time a car moves, it communicate its next moves and its speed to the other cars.
The speed is a function of the number of vehicles **planning** to move to a certain square. The more cars plan to go to a square, the slower they drive.

## Architecture

Each car is represented by a single process which connects to a virtual machine.
The virtual machine is event-driven, single threaded, and allows graphical clients to connect.

## Experiments and Results

The first instance was to compare a selfish (rules based) artificial intelligence to a simple A*.
It was tested on several "city" networks.
The average travel time of the A* is about **15%** shorter than the selfish one.

The second experiment was to try to handle intersection. Intersections are the places where cars waste the most time.
Several studies (links at the end) show interest in traffic light intersections and try to create an efficient multiagent framework for handling self-driven cars at intersections.
The problem is that those solutions take advantage of a third party server at the intersection which gives priority to each vehicle.
The whole point of the Mappy simulator is to explore peer to peer behavior and not to depends on a centralized authority.

The idea then is to set up a distributed system to manage vehicles behavior at intersections.
This version of the simulator does not have such a system but simulates it by randomly reducing travel time at intersections.
The average travel time of the A* is now about **35%** shorter than the selfish algorithm.

The next step would be to implement an actual distributed system between cars and to take more advantage of the P2P system to share more information between cars.

This simulation is very simple and study traffic on a global scale. It does not reflect the reality of what could be the traffic in a city where all cars were to be autonomous.
Nevertheless, it shows how computerized drivers could improve traffic efficiency.

## Useful Links

http://senseable.mit.edu/light-traffic/
http://www.cs.utexas.edu/~aim/
http://www.cs.utexas.edu/~aim/papers/partC17-Sharon.pdf

https://www.engadget.com/2018/09/17/audi-autonomous-cars-25th-hour-traffic-jams/?guccounter=1
