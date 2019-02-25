1.Demo介绍
 此demo以emwin为基础，实现了一个简易的视频播放器
 目前只支持480 * 272
 
2.使用此demo需要添加的头文件路径：
"${workspace_loc:/${ProjName}/app_video_demo}"
"${workspace_loc:/${ProjName}/app_video_demo/mjpeg}"
"${workspace_loc:/${ProjName}/app_video_demo/mjpeg/jpeg/include}"

3.添加头文件路径方法：
选中工程，依次点击Project -> properties -> C/C++ Build ->Settings -> Cross ARM C Compiler -> Includes，将2中路径复制在此处
选中工程，依次点击Project -> properties -> C/C++ Build ->Settings -> Cross ARM C++ Compiler -> Includes，将2中路径复制在此处
