【examples】说明



1. 目录说明

   | 目录名称                    | 内容说明                            |
   | --------------------------- | ----------------------------------- |
   | application                 | 应用例程                            |
   | component                   | 组件例程                            |
   | feature                     | 处理器特性测试                      |
   | system                      | 系统相关例程                        |
   | peripheral (common / m105x) | 包含标准外设例程和m105x特有外设例程 |





2. 例程使用说明
  每个例程都由一个*.c构成，都含有一个入口函数

  如task例程：examples\system\task\demo_task_static.c

  ```
    /** 
     * \brief 静态任务操作的入口函数
     *
     * \param[in] 无
     *
     * \return 无
     */
    void demo_task_static_entry (void){
        ...
    }
  ```

  用户直接调用 demo_task_static_entry() 即可运行例程。





3. 例程文件最顶端的注释，是执行该例程需要执行的操作步骤和实验现象

   如task例程：examples\system\task\demo_task_static.c

   ```
   - 操作步骤：
     1. 本例程需在aw_prj_params.h头文件里使能
        - AW_DEV_GPIO_LED
        - AW_COM_CONSOLE
     2. 将板子中的RX1、TX1通过USB转串口和PC连接，串
        波特率为115200，8位数据长度，1个停止位，无
   - 实验现象：
     1.LED_RUN以500ms的时间间隔亮灭.
     2.串口打印当前执行任务名
     3.任务2串口打印20次后，任务被删除，不再打印。
   ```

   

