1.demo介绍

  此demo以aw_delayed_work.h API为基础，实现了一个延迟作业。
  
2.demo现象

  （1）串口打印出："Start delayed work,process work after 3s"；
  （2）demo运行3s之后，调用work_callback函数。

3.操作步骤

  （1）在aw_prj_params.h中打开 串口1 和 AW_COM_CONSOLE设备宏；
  （2）将板子中的RX1、TX1通过USB转串口和PC连接，串口调试助手设置：波特率为115200，8位数据长度，1个停止位，无流控。