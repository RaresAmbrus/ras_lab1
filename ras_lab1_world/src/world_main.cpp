/*
 *  world_node.cpp
 *
 *
 *  Created on: Aug 25, 2014
 *  Authors:   Rares Ambrus
 *            raambrus <at> kth.se
 */

/* Copyright (c) 2014, Rares Ambrus, CVAP, KTH
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
      * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
      * Neither the name of KTH nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL KTH BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


// ROS includes.
#include <ros/ros.h>
#include <ros/time.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Point.h>

// Boost includes
#include <stdio.h>
#include <stdlib.h>

// Random seed
#include <ctime>

int main(int argc, char **argv)
{
    // Set up ROS.
    ros::init(argc, argv, "world_node");
    ros::NodeHandle n;
    ros::Rate r(10); // 50 Hz

    // Create random number generators
    srand(time(NULL));
    double axis_intercept = 0.4; // the wall will pass through (0, axis_intercept) -> make sure it is close to the robot in the beginning
    double start_y = ((double)(rand()%50)-25);
    double start_x = -100;
    double end_x = 100;
    double end_y = -start_y -2*axis_intercept;

    ROS_INFO_STREAM("Wall position initialized to: ("<<start_x<<","<<start_y<<") and ("<<end_x<<","<<end_y<<")");

    ros::Publisher vis_pub = n.advertise<visualization_msgs::Marker>( "world_marker", 0 );
    visualization_msgs::Marker marker;
    marker.header.frame_id = "odom";
    marker.header.stamp = ros::Time();
    marker.ns = "world";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::LINE_STRIP;
    marker.action = visualization_msgs::Marker::ADD;
    marker.scale.x = 0.01;
    marker.scale.y = 0.01;
    marker.scale.z = 10;
    marker.color.a = 1.0;
    marker.color.r = 1.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;

    geometry_msgs::Point startPoint;
    startPoint.x = start_x;
    startPoint.y = start_y;
    startPoint.z = 0.1;

    geometry_msgs::Point endPoint;
    endPoint.x = end_x;
    endPoint.y = end_y;
    endPoint.z = 0.1;
    marker.points.push_back(startPoint);
    marker.points.push_back(endPoint);

    // Main loop.
    while (n.ok())
    {
        vis_pub.publish(marker);
        ros::spinOnce();
        r.sleep();
    }

    return 0;
} 
