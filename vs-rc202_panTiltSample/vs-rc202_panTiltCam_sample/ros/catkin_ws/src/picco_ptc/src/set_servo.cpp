#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <iostream>

#include "ros/ros.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int16MultiArray.h"
#include "sensor_msgs/JointState.h"

#include <tf/transform_listener.h>

//--[定数定義]-------------------------------------------------------------//
#define PAN_LIMMIT 1800				//パン方向のサーボ指令値限界d
#define TILT_LIMMIT 300				//チルト方向のサーボ指令値限界
#define SERVO_K_Y 10
#define SERVO_K_P 5
#define SERVO_QTY 2				//サーボの個数

//--[プロトタイプ宣言]-------------------------------------------------------//
void joint_servo_callback(const sensor_msgs::JointState::ConstPtr &);

//--[グローバル変数]-------------------------------------------------------//
int servo_data[2] = {0, 0};			//サーボ指令角
float servo_param;

int main(int argc, char* argv[]){

    //-- [名前空間指定] --------------------------------------------------//
    using ros::init;				// ros::init指定
    using ros::ok;				// ros::ok指定
    using ros::spinOnce;			// ros::spinOnce指定
    using ros::NodeHandle;			// ros::NodeHandle指定
    using ros::Rate;				// ros::Rate指定
    using ros::Subscriber;                  	// ros::Subscriber設定
    using ros::Publisher;                   	// ros::Publisher設定
    using ros::Time;				// ros::Time指定

    //初期化API ノード名：std_int16_publisher
    init(argc, argv, "set_servo");

    //ノードハンドラ
    NodeHandle n;

    //tfリスナー生成
    tf::TransformListener listener;

    //Publisher設定
    Publisher pub2vsrc = n.advertise<std_msgs::Int16MultiArray>("joint_degrees", 100);
    Publisher pub2rsp  = n.advertise<sensor_msgs::JointState>("ptc/joint_states", 100);

    //Subscliber設定
    Subscriber sub = n.subscribe<sensor_msgs::JointState>("joint_states", 100, joint_servo_callback);

    //loop rate設定
    Rate rate(60);

    //パラメータ取得
    n.param("servo_param", servo_param, (float)1250);
    

    //メッセージ作成
    std_msgs::Int16MultiArray pub_msg;
    pub_msg.data.clear();
    sensor_msgs::JointState jointState;
    jointState.name.resize(SERVO_QTY);
    jointState.position.resize(SERVO_QTY);


    while(ok()){

	//CAMERA->AR 座標変換取得
	tf::StampedTransform caTransform;	//CAMERA -> AR 座標変換式
	bool tfExists = true;			//座標変換式		
	try{
	    listener.lookupTransform("camera", ros::Time(0), "ar_marker", ros::Time(0), "base", caTransform);
	}
	catch(tf::TransformException &ex){
	    //エラー処理
	    ROS_INFO("cant find caTrajectory");
	    tfExists = false;
	}

	if(tfExists){
		
	    double markerX = caTransform.getOrigin().x();
	    double markerY = caTransform.getOrigin().y();
	    double markerZ = caTransform.getOrigin().z();
	    ROS_INFO("marker(%5.4f, %5.4f, %5.4f)",markerX,markerY,markerZ);

            double yaw = atan(markerX/markerZ);
            double pit = atan(markerY/markerZ);

	    //マーカが左右方向に0.05rad以上動けば追従
	    if(yaw > 0.05){
	        servo_data[0] += ceil(SERVO_K_Y*yaw);
	    }else if(yaw < -0.05){
                servo_data[0] += floor(SERVO_K_Y*yaw);
            }
		    
	    //マーカが上下方向に0.03rad以上動けば追従
	    if(pit > 0.03){
	        servo_data[1] += ceil(SERVO_K_P*pit);
	    }else if(pit < -0.03){
                servo_data[1] += floor(SERVO_K_P*pit);
            }
        }

	//サーボ限界角の判定	
	if(servo_data[0] > PAN_LIMMIT){
            servo_data[0] = PAN_LIMMIT;
        }else if(-1*servo_data[0] > PAN_LIMMIT){
            servo_data[0] = -1* PAN_LIMMIT;
        }
        if(servo_data[1] > TILT_LIMMIT){
            servo_data[1] = TILT_LIMMIT;
        }else if(-1*servo_data[1] > TILT_LIMMIT){
            servo_data[1] = -1* TILT_LIMMIT;
        }

        //VS-RC202用メッセージに指令角をセット
        pub_msg.data.push_back(servo_data[0]);
        pub_msg.data.push_back(servo_data[1]);

        //robot state publisher用メッセージにタイムスタンプとサーボ指令角をセット
        jointState.header.stamp = Time::now();
        jointState.name[0] = "base2pan";
        jointState.position[0] = -servo_data[0]/servo_param;
        jointState.name[1] = "pan2camera";
        jointState.position[1] = -servo_data[1]/servo_param;

        //パブリッシュ
        pub2vsrc.publish(pub_msg);
        pub2rsp.publish(jointState);

        //dataクリア
        pub_msg.data.clear();

        //spin Once
        spinOnce();
        rate.sleep();
        
    }


}


void joint_servo_callback(const sensor_msgs::JointState::ConstPtr& joints){

    servo_data[0] = (int)(servo_param*joints->position[0]);
    servo_data[1] = -(int)(servo_param*joints->position[1]);


    return;
}
