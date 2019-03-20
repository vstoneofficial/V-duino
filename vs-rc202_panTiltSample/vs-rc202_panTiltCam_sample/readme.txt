[サンプルスケッチの使い方]
ROSの基本的な操作については理解しているものとして記述している。

--[Arduino IDEへのライブラリの追加]-----------------------------
ros/arduinoIDE内の「ros_lib」フォルダを、VS-RC202のライブラリを追加したときと同じ手順で、
ArduinoIDEのライブラリとして追加する。
このライブラリはWindows環境でもコンパイル可能である。

ライブラリに関する詳細は以下のURLを参照
http://wiki.ros.org/rosserial_arduino


--[ROSパッケージのセットアップ]----------------------------------
パンチルトカメラサンプルを動作させるためには、添付するpicco_ptcパッケージの他、
以下の公開パッケージが必要なので、それぞれセットアップする。

・ar_tools -カメラ画像からARマーカを認識するパッケージ
ROSWiki：http://wiki.ros.org/ar_tools
パッケージ内のマーカ画像ファイルを印刷して使用するため、catkinを用いてソースからインストールする方が望ましい。

・uvc_camera -接続されたカメラから画像を取得するパッケージ
ROSWiki：http://wiki.ros.org/uvc_camera

・camera_calibration -カメラのキャリブレーションを行うパッケージ
ROSWiki：http://wiki.ros.org/camera_calibration

・rosserial -シリアル接続された機器をROSから制御するためのパッケージ
ROSWiki：http://wiki.ros.org/rosserial

・その他の不足パッケージ
各人のROS使用状況によって、不足パッケージが発生することがある。
エラーメッセージをもとに不足しているパッケージをセットアップする。


--[picco_ptcパッケージのセットアップと使用]----------------------
Ubuntuのコマンドラインを使用する。
入力するコマンドは”ダブルクォーテーションで囲って表現する”。

vs-rc202_panTiltCam_sample/ros/catkin_ws/src以下の「picco_ptc」フォルダを、ROSがセットアップされたPCの
/home/ユーザ名/catkin_ws/src内に配置し、catkin_makeする。

ar_poseをcatkinでインストールした場合、
catkin_ws/src/ar_tools/ar_pose/data/4x4内の「4x4_gif.tar.gz」を解凍し、「4x4_384_75.gif」をA4用紙に印刷する。

PCにパンチルトカメラロボットのUSBカメラ、VS-RC202をそれぞれ接続し、認識されたデバイスファイル名を確認する。
デバイスは/dev/で確認できる。
デバイス認識時にファイルが生成されるため、接続前後で増加したファイルが対象のデバイスファイルである。
一般に、カメラはvideoX、VS-RC202はttyUSBXもしくはttyXXXのような名前で認識される。

src/picco_ptc/launchフォルダ内の「ptc_ARmarker.launch」を開き、
カメラのデバイスファイル名を適切に設定する。

roscoreを起動する。

VS-RC202へのアクセス権を設定する。
”sudo chmod 666 /dev/デバイスファイル名”

rosserialで通信する。
”rosrun rosserial_python serial_node.py _port:=/dev/デバイスファイル名 _baud:=115200”

ptc_ARmarker.launchを使用する。
”roslaunch picco_ptc ptc_ARmarker.launch”

先ほど印刷したARマーカをカメラに写して認識させた状態でマーカを移動させると、
パンチルトカメラがそれを追従するように動作する。

ARマーカの認識が悪い時は、camera_calibrationを使ってキャリブレーションファイルを作成することで改善が見込める。

また、ptc_slider.launchを使用すれば、スライダーを使って、パンチルトを操作することが可能である。






