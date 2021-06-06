#!/bin/bash


terminator -e "
  cd $(pwd)/../..;
  source devel/setup.bash;
  export TURTLEBOT_GAZEBO_WORLD_FILE=$(pwd)/../../src/map/simple_home.world ;
  roslaunch turtlebot_gazebo turtlebot_world.launch" &

sleep 10

terminator -e "cd $(pwd)/../..; source devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch" &

sleep 2

terminator -e "cd $(pwd)/../..; source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 2

terminator -e "cd $(pwd)/../..; source devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch"
