#!/bin/bash

terminator -e "
	cd $(pwd)/../..;
    	source devel/setup.bash;
    	export TURTLEBOT_GAZEBO_WORLD_FILE=$(pwd)/../map/simple_home.world;
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
    	roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 20


terminator -e "
	cd $(pwd)/../..; 
    	source devel/setup.bash; 
    	rosrun add_markers_test add_markers_test"
