[�T���v���X�P�b�`�̎g����]
ROS�̊�{�I�ȑ���ɂ��Ă͗������Ă�����̂Ƃ��ċL�q���Ă���B

--[Arduino IDE�ւ̃��C�u�����̒ǉ�]-----------------------------
ros/arduinoIDE���́uros_lib�v�t�H���_���AVS-RC202�̃��C�u������ǉ������Ƃ��Ɠ����菇�ŁA
ArduinoIDE�̃��C�u�����Ƃ��Ēǉ�����B
���̃��C�u������Windows���ł��R���p�C���\�ł���B

���C�u�����Ɋւ���ڍׂ͈ȉ���URL���Q��
http://wiki.ros.org/rosserial_arduino


--[ROS�p�b�P�[�W�̃Z�b�g�A�b�v]----------------------------------
�p���`���g�J�����T���v���𓮍삳���邽�߂ɂ́A�Y�t����picco_ptc�p�b�P�[�W�̑��A
�ȉ��̌��J�p�b�P�[�W���K�v�Ȃ̂ŁA���ꂼ��Z�b�g�A�b�v����B

�Ear_tools -�J�����摜����AR�}�[�J��F������p�b�P�[�W
ROSWiki�Fhttp://wiki.ros.org/ar_tools
�p�b�P�[�W���̃}�[�J�摜�t�@�C����������Ďg�p���邽�߁Acatkin��p���ă\�[�X����C���X�g�[����������]�܂����B

�Euvc_camera -�ڑ����ꂽ�J��������摜���擾����p�b�P�[�W
ROSWiki�Fhttp://wiki.ros.org/uvc_camera

�Ecamera_calibration -�J�����̃L�����u���[�V�������s���p�b�P�[�W
ROSWiki�Fhttp://wiki.ros.org/camera_calibration

�Erosserial -�V���A���ڑ����ꂽ�@���ROS���琧�䂷�邽�߂̃p�b�P�[�W
ROSWiki�Fhttp://wiki.ros.org/rosserial

�E���̑��̕s���p�b�P�[�W
�e�l��ROS�g�p�󋵂ɂ���āA�s���p�b�P�[�W���������邱�Ƃ�����B
�G���[���b�Z�[�W�����Ƃɕs�����Ă���p�b�P�[�W���Z�b�g�A�b�v����B


--[picco_ptc�p�b�P�[�W�̃Z�b�g�A�b�v�Ǝg�p]----------------------
Ubuntu�̃R�}���h���C�����g�p����B
���͂���R�}���h�́h�_�u���N�H�[�e�[�V�����ň͂��ĕ\������h�B

vs-rc202_panTiltCam_sample/ros/catkin_ws/src�ȉ��́upicco_ptc�v�t�H���_���AROS���Z�b�g�A�b�v���ꂽPC��
/home/���[�U��/catkin_ws/src���ɔz�u���Acatkin_make����B

ar_pose��catkin�ŃC���X�g�[�������ꍇ�A
catkin_ws/src/ar_tools/ar_pose/data/4x4���́u4x4_gif.tar.gz�v���𓀂��A�u4x4_384_75.gif�v��A4�p���Ɉ������B

PC�Ƀp���`���g�J�������{�b�g��USB�J�����AVS-RC202�����ꂼ��ڑ����A�F�����ꂽ�f�o�C�X�t�@�C�������m�F����B
�f�o�C�X��/dev/�Ŋm�F�ł���B
�f�o�C�X�F�����Ƀt�@�C������������邽�߁A�ڑ��O��ő��������t�@�C�����Ώۂ̃f�o�C�X�t�@�C���ł���B
��ʂɁA�J������videoX�AVS-RC202��ttyUSBX��������ttyXXX�̂悤�Ȗ��O�ŔF�������B

src/picco_ptc/launch�t�H���_���́uptc_ARmarker.launch�v���J���A
�J�����̃f�o�C�X�t�@�C������K�؂ɐݒ肷��B

roscore���N������B

VS-RC202�ւ̃A�N�Z�X����ݒ肷��B
�hsudo chmod 666 /dev/�f�o�C�X�t�@�C�����h

rosserial�ŒʐM����B
�hrosrun rosserial_python serial_node.py _port:=/dev/�f�o�C�X�t�@�C���� _baud:=115200�h

ptc_ARmarker.launch���g�p����B
�hroslaunch picco_ptc ptc_ARmarker.launch�h

��قǈ������AR�}�[�J���J�����Ɏʂ��ĔF����������ԂŃ}�[�J���ړ�������ƁA
�p���`���g�J�����������Ǐ]����悤�ɓ��삷��B

AR�}�[�J�̔F�����������́Acamera_calibration���g���ăL�����u���[�V�����t�@�C�����쐬���邱�Ƃŉ��P�������߂�B

�܂��Aptc_slider.launch���g�p����΁A�X���C�_�[���g���āA�p���`���g�𑀍삷�邱�Ƃ��\�ł���B






