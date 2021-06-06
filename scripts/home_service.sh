#!/bin/bash

terminator -e "
	cd $(pwd)/../..;
    source devel/setup.bash;
    export TURTLEBOT_GAZEBO_WORLD_FILE=$(pwd)/../map/sukithOffice.world;
    roslaunch turtlebot_gazebo turtlebot_world.launch" &

sleep 15

terminator -e "
	cd $(pwd)/../..;
    source devel/setup.bash;
    export TURTLEBOT_GAZEBO_MAP_FILE=$(pwd)/../map/smap.yaml;
    roslaunch turtlebot_gazebo amcl_demo.launch " &

sleep 5

terminator -e "
	cd $(pwd)/../..;
	source devel/setup.bash;
    rosrun rviz rviz -d $(pwd)/../rvizConfig/home_service.rviz" &

sleep 20

terminator -e "
	cd $(pwd)/../..; 
    source devel/setup.bash; 
    rostopic echo /object_state" &

terminator -e "
	cd $(pwd)/../..; 
    source devel/setup.bash; 
    rosrun add_markers add_markers" &

sleep 1

terminator -e "
	cd $(pwd)/../..; 
    source devel/setup.bash; 
    rosrun pick_objects pick_objects"


