### 一、UI控件

#### 1.1 各个控件常用属性

| 属性  | 说明     |
| :---- | :------- |
| x     | x坐标    |
| y     | y坐标    |
| w     | 宽度     |
| h     | 高度     |
| name  | 控件名称 |
| text  | 文本     |
| style | 样式     |

#### 1.2 window窗口控件

##### 1.2.1 属性

| 属性      | 说明           | 可选属性值                                   |
| :-------- | :------------- | :------------------------------------------- |
| anim_hint | 窗口动画       | htranslate(水平平移 );  vtranslate(垂直平移) |
| theme     | 主题资源的名称 |                                              |

备注：window没有x，y，w，h，name属性，window默认占满全屏

##### 1.2.2 示例

```xml
<window name="main" anim_hint="htranslate" style="black"> 
</window> 
```

#### 1.3 label文本控件

##### 1.3.1 属性

请看[1.1](#1.1 各个控件常用属性)

##### 1.3.2 示例

```xml
<label name="bkgnd" x="0" y="0" w="100%" h="100%" style="bg0"/>
```

#### 1.4 app_bar容器控件

一个简单的容器控件，一般在窗口的顶部 ,它本身不提供布局功能(可用layout参数指定)，和view功能一致，仅提供具有语义的标签，让xml更具有可读性 

##### 1.4.1 属性

请看[1.1](#1.1 各个控件常用属性)

##### 1.4.2 示例

```xml
<app_bar x="0" y="0" w="100%" h="40">
	<label name="dev_name" x="0" y="0" w="200" h="100%" text="远大洁净新风机" style="title_left"/>
	<label name="sys_time" x="200" y="0" w="-200" h="100%" style="title_right"/>
</app_bar>
```

#### 1.5 view容器控件

一个通用的容器控件，也可以用作自绘 

##### 1.5.1 属性

请看[1.1](#1.1 各个控件常用属性)

##### 1.5.2 示例

```xml
<view x="0" y="44" w="88" h="44" layout="r:1 c:2">
	<image name="timing_status" image="clock" draw_type="icon"/>
	<image name="alarm_status"  image="bell"  draw_type="icon"/>
</view>
```

#### 1.6 image图片控件

##### 1.6.1 属性

| 属性      | 说明               | 可选属性值 |
| :-------- | :----------------- | :--------- |
| image     | 要加载的图片文件名 |            |
| draw_type | 图片绘制方法       | 请看下表   |

| draw_type选项    | 说明                                                         |
| :--------------- | :----------------------------------------------------------- |
| default          | 缺省显示。将图片按原大小显示在目标矩形的左上角               |
| icon             | 图标显示。同居中显示，但会根据屏幕密度调整大小               |
| center           | 居中显示。将图片按原大小显示在目标矩形的中央                 |
| scale            | 缩放显示。将图片缩放至目标矩形的大小(不保证宽高成比例)       |
| scale_auto       | 自动缩放显示。将图片缩放至目标矩形的宽度或高度(选取最小的比例)，并居中显示 |
| scale_w          | 宽度缩放显示。将图片缩放至目标矩形的宽度，高度按此比例进行缩放，超出部分不显示 |
| scale_h          | 高度缩放显示。将图片缩放至目标矩形的高度，宽度按此比例进行缩放，超出部分不显示 |
| repeat           | 平铺显示                                                     |
| repeat_x         | 水平方向平铺显示，垂直方向缩放                               |
| repeat_y         | 垂直方向平铺显示，水平方向缩放                               |
| patch9           | 9宫格显示                                                    |
| patch3_x         | 水平方向3宫格显示，垂直方向居中显示                          |
| patch3_y         | 垂直方向3宫格显示，水平方向居中显示                          |
| patch3_x_scale_y | 水平方向3宫格显示，垂直方向缩放显示                          |
| patch3_y_scale_x | 垂直方向3宫格显示，水平方向缩放显示                          |
| animation        | 动画                                                         |

##### 1.6.2 示例

示例1：

```xml
<image name="alarm_status" image="bell" draw_type="icon"/>
```

示例2：

```xml
<window>
  <image name="fade" image="logo" x="center" y="10" w="200" h="60" opacity="0" animation="opacity(from=50, to=255, yoyo_times=1000, duration=1000)"/>
  <image name="fade" image="logo" x="center" y="80" w="200" h="60" opacity="0" animation="opacity(from=50, to=255, yoyo_times=1000, duration=1000, delay=1000)" />
  <image name="fade" image="logo" x="center" y="150" w="200" h="60" opacity="0" animation="opacity(from=50, to=255, yoyo_times=1000, duration=1000, delay=2000)" />
  <image name="move" image="logo" x="0" y="middle:60" w="200" h="60" animation="move(x_from=0, x_to=200, yoyo_times=1000, duration=1000, delay=3000)"/>
  <progress_bar name="value" x="center" y="middle" w="90%" h="40" animation="value(from=50, to=100, yoyo_times=1000, duration=1000, delay=4000)"/>
  <button name="close" x="center" y="bottom:10" w="25%" h="30" text="Close"/>
</window>
```

#### 1.7 rich_text富文本控件

实现简单的图文混排 

##### 1.7.1 属性

| 属性     | 说明   |
| :------- | :----- |
| line_gap | 行间距 |

##### 1.7.2 示例

```xml
<rich_text x="188" w="-188" h="100%" text="<font color=&quota;white&quota; align_v=&quota;top&quota; size=&quota;18&quota;>μg/m</font><font color=&quota;white&quota; align_v=&quota;top&quota; size=&quota;10&quota;>3</font>" />

<rich_text line_gap="5" x="0" y="210" w="100%" h="200" text="<image name=&quota;bricks&quota;/><font color=&quota;gold&quota; align_v=&quota;bottom&quota; size=&quota;24&quota;>hello awtk!</font><font color=&quota;green&quota; size=&quota;20&quota;>ProTip! The feed shows you events from people you follow and repositories you watch. 
hello world. </font><font color=&quota;red&quota; size=&quota;20&quota;>确定取消中文字符测试。确定。取消。中文字符测试。</font>" />
```

#### 1.8 image_animation图片动画控件

##### 1.8.1 属性

| 属性      | 说明                           | 可选属性值               |
| :-------- | ------------------------------ | :----------------------- |
| image     | 图片名称的前缀                 |                          |
| sequence  | 播放的序列                     | 字符可选值为:0-9,a-z,A-Z |
| loop      | 是否循环播放                   |                          |
| auto_play | 是否自动播放                   | true ; false             |
| interval  | 每张图片播放的时间(毫秒)       |                          |
| delay     | 自动播放时延迟播放的时间(毫秒) |                          |

##### 1.8.2 示例

```xml
<image_animation name="fan_1" image="fan_1" sequence="ab" auto_play="false" interval="500" delay="100" y="m"/>
```

#### 1.9 button按钮控件

##### 1.9.1 属性

|  属性  |                             说明                             |
| :----  | :----------------------------------------------------------  |
| repeat | 重复释放EVT_CLICK事件的时间间隔。为0则不重复释放EVT_CLICK事件 |

##### 1.9.2 示例

```xml
 <button name="frequency_dec" w="20%" h="100%" style="dec_btn"/>
```

#### 1.10 calibration_win电阻屏幕校准

##### 1.10.1 属性

请看[1.1](#1.1 各个控件常用属性)

##### 1.10.2 示例

```xml
<calibration_win name="cali" w="100%" h="100%" text="Please click the center of cross">
</calibration_win>
```

#### 1.11 list_view列表视图控件

##### 1.11.1 属性

| 属性                 | 说明                               | 可选属性值   |
| :------------------- | :--------------------------------- | :----------- |
| item_height          | 列表项的高度                       |              |
| auto_hide_scroll_bar | 如果不需要滚动条时，自动隐藏滚动条 | true ; false |

##### 1.11.2 示例

```xml
<list_view x="4"  y="76" w="-8" h="400" item_height="40">
    <scroll_view name="view" x="0"  y="0" w="100%" h="100%">
      <list_item style="odd_clickable" layout="r1 c0">
        <image draw_type="icon" w="20%" image="bell"/>
        <label w="20%" text="24.4℃"/>
        <label w="20%" text="26.4℃"/>
        <label w="20%" text="20%"/>
        <label w="20%" text="30%"/>
      </list_item>
    </scroll_view>
    <scroll_bar_m name="bar" x="right" y="0" w="6" h="100%" value="0"/>
 </list_view>
```

#### 1.12 scroll_view滚动视图控件

##### 1.12.1 属性

| 属性      | 说明              | 可选属性值   |
| --------- | :---------------- | :----------- |
| virtual_w | 虚拟宽度          |              |
| virtual_h | 虚拟高度          |              |
| xoffset   | x偏移量           |              |
| yoffset   | y偏移量           |              |
| xslidable | 是否允许x方向滑动 | true ; false |
| yslidable | 是否允许y方向滑动 | true ; false |

##### 1.12.2 示例

```xml
<scroll_view x="20"  y="20" w="200" h="200" virtual_w="400" virtual_h="200" xoffset="100" layout="w30 r1 m:2 s:2">
```

#### 1.13 list_item控件

##### 1.13.1 属性

请看[1.1](#1.1 各个控件常用属性)

##### 1.13.2 示例

```xml
<list_item style="even_clickable" layout="r1 c0">
	<image draw_type="icon" w="20%" image="bell"/>
	<label w="20%" text="24.4℃"/>
	<label w="20%" text="26.4℃"/>
	<label w="20%" text="20%"/>
	<label w="20%" text="30%"/>
</list_item>
```

#### 1.14 scroll_bar滚动条控件

scroll_bar有两种类型：电脑版的scroll_bar_d和手机版的scroll_bar_m 

##### 1.14.1 属性

| 属性         | 说明               | 可选属性值   |
| :----------- | :----------------- | :----------- |
| virtual_size | 虚拟宽度或高度     |              |
| value        | 当前的值           |              |
| row          | 行的高度           |              |
| animatable   | 滚动时是否启用动画 | true ; false |

##### 1.14.2 示例

```xml
 <scroll_bar_d name="bar" x="right" y="0" w="12" h="100%" value="0"/>
 <scroll_bar_m name="bar" x="right" y="0" w="6"  h="100%" value="0"/>
```

#### 1.15 pages控件

只有一个Page处于active状态，处于active状态的Page才能显示并接收事件。 

##### 1.15.1 属性

| 属性   | 说明           |
| :----- | :------------- |
| active | 当前活跃的page |

##### 1.15.2 示例

```xml
<pages x="right" y="40" w="80%" h="440" active="0"> 
    <view w="100%" h="60%" layout="r:4 c:3">
      <label   text="室内温度" />
      <edit  right_margin="16" text="22.0" input_type="ufloat" min="22.0" max="150" step="0.1" auto_fix="true" />
       <edit right_margin="16" text="2.0" input_type="ufloat" min="2.0" max="150" step="0.1" auto_fix="true"/>
        
      <label   text="送风温差" />
       <edit  right_margin="16" text="4.0" input_type="ufloat" min="0.0" max="150" step="0.1" auto_fix="true"/>
       <edit right_margin="16" text="0.0" input_type="ufloat" min="0.0" max="150" step="0.1" auto_fix="true"/>

      <label   text="室内湿度" />
      <edit right_margin="16" text="75.0" input_type="ufloat" min="0.0" max="150" step="0.1" auto_fix="true"/>
       <edit right_margin="16" text="5.0" input_type="ufloat" min="0.0" max="150" step="0.1" auto_fix="true"/>
       
      <label   text="循环延时" />
      <edit right_margin="16" text="0.0" input_type="ufloat" min="0.0" max="150" step="0.1" auto_fix="true"/>
       <edit right_margin="16" text="2.0" input_type="ufloat" min="0.0" max="150" step="0.1" auto_fix="true"/>
    </view>

    <view w="100%" h="60%" layout="r:4 c:2">
      <label   text="高温报警" />
      <edit right_margin="16" text="35.0" input_type="ufloat" min="22.0" max="150" step="0.1" auto_fix="true" />
      <label   text="低温报警" />
      <edit right_margin="16" text="10.0" input_type="ufloat" min="4.0" max="150" step="0.1" auto_fix="true"/>
      <label   text="高湿报警" />
      <edit right_margin="16" text="90.0" input_type="ufloat" min="0.0" max="150" step="0.1" auto_fix="true"/>
      <label   text="低湿报警" />
      <edit right_margin="16" text="10.0" input_type="ufloat" min="0.0" max="150" step="0.1" auto_fix="true"/>
    </view>
  </pages>

  <list_view x="0" y="40" w="20%" h="440" item_height="40" auto_hide_scroll_bar="true">
    <scroll_view name="view" x="0"  y="0" w="-12" h="100%">
      <tab_button text="控制参数设定" value="true"/>
      <tab_button text="报警设置" />
    </scroll_view>
    <scroll_bar_d name="bar" x="right" y="0" w="12" h="100%" value="0"/>
  </list_view>
```

#### 1.16 edit编辑文本控件

##### 1.16.1 属性

| 属性             | 说明                                      | 可选属性值                                                   |
| :--------------- | :---------------------------------------- | :----------------------------------------------------------- |
| readonly         | 编辑器是否为只读                          | true ; false                                                 |
| password_visible | 密码是否可见                              | true ; false                                                 |
| auto_fix         | 输入无效时，是否自动改正                  | true ; false                                                 |
| top_margin       | 上边距                                    |                                                              |
| bottom_margin    | 下边距                                    |                                                              |
| left_margin      | 左边距                                    |                                                              |
| right_margin     | 右边距                                    |                                                              |
| tips             | 输入提示                                  |                                                              |
| input_type       | 输入类型。XXX：需要在min/max/step之前设置 | "int"; "float"; "uint";"ufloat",;"text";"password","hex";"email"; "phone" |
| min              | 最小值或最小长度                          |                                                              |
| max              | 最大值或最大长度                          |                                                              |
| step             | 步长                                      |                                                              |

##### 1.16.2 示例

```xml
<edit  right_margin="16" text="22.0" input_type="ufloat" min="22.0" max="150" step="0.1" auto_fix="true" />
```

#### 1.17 tab_button标签按钮控件

##### 1.17.1 属性

| 属性        | 说明                 | 可选属性值   |
| :---------- | -------------------- | :----------- |
| value       | 值                   | true ; false |
| active_icon | 当前项的图标的名称   |              |
| icon        | 非当前项的图标的名称 |              |

##### 1.17.2 示例

```xml
<tab_button icon="contact" active_icon="contact_active" text="Contact" value="true" />
```

#### 1.18 grid 网络控件

一个简单的容器控件，用于网格排列一组控件。 它本身不提供布局功能(可用layout参数指定)，和view功能一致，仅提供具有语义的标签，让xml更具有可读性。 

##### 1.18.1 属性

请看[1.1](#1.1 各个控件常用属性)

##### 1.18.2 示例

```xml
<grid x="20" y="bottom:20" w="50%" h="100" layout="r:2 c:3 xm:2 s:10">
  <image draw_type="icon" image="earth"/>
  <image draw_type="icon" image="rgba" />
  <image draw_type="icon" image="rgb" />
  <image draw_type="icon" image="message"/>
  <image draw_type="icon" image="red_btn_n"/>
</grid>
```

#### 1.19 row水平容器

一个简单的容器控件，用于水平排列一组控件，它本身不提供布局功能(可用layout参数指定)，和view功能一致，仅提供具有语义的标签，让xml更具有可读性。 

##### 1.19.1 属性

请看[1.1](#1.1 各个控件常用属性)

##### 1.19.2 示例

```xml
<row h="30" layout="row:1 col:3" w="200" x="30" y="0">
	<label  text="时"/>
	<label  text="分"/>
	<label  text="秒"/>
</row>
```

#### 1.20 column列容器

一个简单的容器控件，垂直排列一组控件 ，它本身不提供布局功能(可用layout参数指定)，和view功能一致，仅提供具有语义的标签，让xml更具有可读性。 

##### 1.20.1 属性

请看[1.1](#1.1 各个控件常用属性)

##### 1.20.2 示例

```xml
<column x="20" y="160" w="50%" h="60" layout="r:2 c:1 ym:2 s:10" >
    <check_button name="c1" text="Book"/>
    <check_button name="c2" text="Food"/>
</column>
```

#### 1.21 text_selector文本选择器控件

通常用于选择年月日等，目前需要先设置options和visible_nr，再设置其它参数(在XML中也需要按此顺序) 

##### 1.21.1 属性

| 属性           | 说明                                                         | 可选属性值                                                   |
| :------------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| visible_nr     | 可见的选项数量(只能是3或者5，缺省为5)                        |                                                              |
| selected_index | 当前选中的选项                                               |                                                              |
| options        | 设置可选项(冒号分隔值和文本，分号分隔选项，如:1:red;2:green;3:blue) | 对于数值选项，也可以指定一个范围，用『-』分隔起始值和结束值，如："1-7"表示1到7 |

##### 1.21.2 示例

```xml
<row h="90" layout="row:1 col:3" w="200" x="30" y="30">
	<text_selector options="1-24" text="15" visible_nr="3"/>
	<text_selector options="1-60" text="10" visible_nr="3"/>
	<text_selector options="1-60" text="16" visible_nr="3"/>
</row>
```

#### 1.22 progress_bar进度条控件

##### 1.22.1 属性

| 属性      | 说明                   | 可选属性值   |
| :-------- | :--------------------- | :----------- |
| value     | 进度条的值[0-100]      |              |
| vertical  | 进度条的是否为垂直方向 | true ; false |
| show_text | 是否显示文本           | true ; false |

##### 1.22.2 示例

```xml
<progress_bar name="bar2" x="260" y="80" w="30" h="118" value="20" vertical="true"/>
```

#### 1.23 group_box组控件

##### 1.23.1 属性

请看[1.1](#1.1 各个控件常用属性)

##### 1.23.2 示例

```xml
<group_box layout="rows:1 cols:10 spacing:2 margin:2">
    <button repeat="300" name="Q" text="Q"/>
    <button repeat="300" name="W" text="W"/>
    <button repeat="300" name="E" text="E"/>
    <button repeat="300" name="R" text="R"/>
    <button repeat="300" name="T" text="T"/>
    <button repeat="300" name="Y" text="Y"/>
    <button repeat="300" name="U" text="U"/>
    <button repeat="300" name="I" text="I"/>
    <button repeat="300" name="O" text="O"/>
    <button repeat="300" name="P" text="P"/>
 </group_box>
```

#### 1.24 check_button多选控件

##### 1.24.1 属性

| 属性  | 说明 | 可选属性值   |
| :---- | :--- | :----------- |
| value | 值   | true ; false |

##### 1.24.2 示例

```xml
 <column x="20" y="160" w="50%" h="60" layout="r:2 c:1 ym:2 s:10" >
    <check_button name="c1" text="Book"/>
    <check_button name="c2" text="Food"/>
  </column>
```

#### 1.25 radio_button单选控件

##### 1.25.1 属性

| 属性  | 说明 |  可选属性值  |
| :---  | :--  | :----------  |
| value |  值  | true ; false |

##### 1.25.2 示例

```xml
<column x="20" y="230" w="50%" h="90" layout="r:3 c:1 ym:2 s:10" >
    <radio_button name="r1" text="Book"/>
    <radio_button name="r2" text="Food"/>
    <radio_button name="r3" text="Pencil" value="true"/>
</column>
```

#### 1.26 spin_box控件

##### 1.26.1 属性

与[edit控件](#1.16 edit编辑文本控件)一样

##### 1.26.2 示例

```xml
<spin_box x="40" y="middle" w="54" h="100%" min="0" input_type="int" max="255" step="1" auto_fix="true" name="r" />
```

#### 1.27 slider滑块控件

##### 1.27.1 属性

|   属性   |         说明         |  可选属性值  |
| :------  | :------------------  | :----------  |
|  value   |          值          |              |
|   min    |        最小值        |              |
|   max    |        最大值        |              |
|   step   |    拖动的最小单位    |              |
| vertical | 滑块的是否为垂直方向 | true ; false |

##### 1.27.2 示例

```xml
<slider style="img" x="center" y="90" w="80%" h="30" value="30" min="5" max="50" step="5" />
```

#### 1.28 combo_box控件

##### 1.28.1 属性

|      属性      |                             说明                             |
| :------------  | :----------------------------------------------------------  |
|  open_window   |      为点击按钮时，要打开窗口的名称 ，该窗口包含了选项       |
| selected_index |                        当前选中的选项                        |
|     value      |                              值                              |
|    options     | 设置可选项(冒号分隔值和文本，分号分隔选项，如:1:red;2:green;3:blue) |

除了上面属性还包括[edit控件](#1.16 edit编辑文本控件)的属性

##### 1.28.2 示例

```xml
 <window name="main" anim_hint="htranslate">
  <combo_box left_margin="6" readonly="true" x="10" y="5" w="200" h="30" text="left" options="left;center;right;"/>
  <combo_box open_window="color" readonly="true" x="10" y="50" w="200" h="30" text="red"/>
  <combo_box readonly="true" x="10" y="bottom:5" w="200" h="30" text="left" options="1:left;2:center;3:right;"/>
  <combo_box open_window="color" readonly="true" x="10" y="bottom:50" w="200" h="30" text="red"/>

  <button name="close" x="center" y="middle" w="50%" h="30" text="close"/>
</window>
```

#### 1.29 combo_box_item控件

通常将combo_box_item写在一个xml文件中(如color.xml)，然后用于<combo_box open_window="color">

##### 1.29.1 属性

| 属性     | 说明       | 可选属性值   |
| :------- | :--------- | :----------- |
| value    | 值         |              |
| selected | 是否被选中 | true ; false |
| value    | 值         |              |

##### 1.29.2 示例

```xml
<popup theme="color" close_when_click_outside="true" h="128" >
  <list_view x="0"  y="0" w="100%" h="100%" item_height="30">
    <scroll_view name="view" x="0"  y="0" w="-12" h="100%">
      <combo_box_item tr_text="red"/>
      <combo_box_item tr_text="green" />
      <combo_box_item tr_text="blue" />
      <combo_box_item tr_text="orange" />
      <combo_box_item tr_text="gold" />
      <combo_box_item tr_text="black" />
      <combo_box_item tr_text="white" />
    </scroll_view>
    <scroll_bar_d name="bar" x="right" y="0" w="12" h="100%" value="0"/>
  </list_view>
</popup>
```

#### 1.30 popup窗口

##### 1.30.1 属性

| 属性                     | 说明                       | 可选属性值   |
| :----------------------- | :------------------------- | :----------- |
| theme                    | 主题资源的名称             |              |
| close_when_click         | 点击时是否关闭窗口         | true ; false |
| close_when_click_outside | 点击到窗口外时是否关闭窗口 | true ; false |

##### 1.30.2 示例

```xml
<popup theme="color" close_when_click_outside="true" h="128" >
  <list_view x="0"  y="0" w="100%" h="100%" item_height="30">
    <scroll_view name="view" x="0"  y="0" w="-12" h="100%">
      <combo_box_item tr_text="red"/>
      <combo_box_item tr_text="green" />
      <combo_box_item tr_text="blue" />
      <combo_box_item tr_text="orange" />
      <combo_box_item tr_text="gold" />
      <combo_box_item tr_text="black" />
      <combo_box_item tr_text="white" />
    </scroll_view>
    <scroll_bar_d name="bar" x="right" y="0" w="12" h="100%" value="0"/>
  </list_view>
</popup>
```

#### 1.31 dialog对话框窗口

对话框由dialog_title和dialog_client组成

##### 1.31.1 属性

| 属性      | 说明           | 可选属性值                                                   |
| :-------- | :------------- | :----------------------------------------------------------- |
| anim_hint | 窗口动画       | center_scale (中心缩放 );  top_to_bottom(顶部部弹出);  bottom_to_top (底部弹出 ) |
| theme     | 主题资源的名称 |                                                              |

##### 1.31.2 示例

```xml
<dialog anim_hint="center_scale" h="160" name="timing" w="480" x="c" y="m">
	<dialog_title h="30" text="定时设置" w="100%" x="0" y="0"/>
	<dialog_client h="-30" w="100%" x="0" y="bottom">
		<row h="30" layout="row:1 col:3" w="200" x="30" y="0">
			<label  text="时"/>
			<label  text="分"/>
			<label  text="秒"/>
		</row>
		<row h="90" layout="row:1 col:3" w="200" x="30" y="30">
			<text_selector options="1-24" text="15" visible_nr="3"/>
			<text_selector options="1-60" text="10" visible_nr="3"/>
			<text_selector options="1-60" text="16" visible_nr="3"/>
		</row>
		<button h="30" name="ok" text="开" w="150" x="right:30" y="23"/>
		<button h="30" name="cancle" text="关" w="150" x="right:30" y="76"/>
	</dialog_client>
</dialog> 
```

#### 1.32 switch开关控件

##### 1.32.1 属性

|       属性        |                           说明                            |  可选属性值  |
| :---------------  | :-------------------------------------------------------  | :----------  |
|       value       |                            值                             | true ; false |
| max_xoffset_ratio | 当开关处于关闭时，图片偏移相对于图片宽度的比例(缺省为1/3) |              |
|   round_radius    |                      图片的圆角半径                       |              |

##### 1.32.2 示例

```xml
<window name="switch" anim_hint="htranslate">
  <switch x="10" y="60" w="90" h="22" />
  <switch x="200" y="60" w="90" h="22" round_radius="10" />
  <button name="close" x="center" y="middle" w="50%" h="30" text="close"/>
</window>
```

#### 1.33 guage仪表控件

##### 1.33.1 属性

|     属性      |                        说明                         |
| :-----------  | :-------------------------------------------------  |
|     angle     | 指针角度。12点钟方向为0度，顺时钟方向为正，单位为度 |
|   bg_image    |                      背景图片                       |
| pointer_image |  指针图片。图片须垂直向上，图片的中心点为旋转方向   |

##### 1.33.2 示例

```xml
<window style="dark" anim_hint="htranslate" >
 <guage x="c" y="m" w="300" h="300" value="30" bg_image="guage_bg" pointer_image="guage_pointer" />
 <button name="close" x="center" y="bottom:10" w="25%" h="30" text="Close"/>
</window>
```

#### 1.34 time_clock时钟控件

##### 1.34.1 属性

|     属性     |   说明   |
| :----------  | :------  |
|     hour     |   小时   |
|    minute    |   分钟   |
|    second    |    秒    |
|    image     | 中心图片 |
|   bg_image   | 背景图片 |
|  hour_image  | 时针图片 |
| minute_image | 分针图片 |
| second_image | 秒针图片 |

##### 1.34.2 示例

```xml
<window anim_hint="htranslate" >
  <time_clock x="c" y="m" w="300" h="300" hour="11" minute="59" second="55"
    bg_image="clock_bg" image="clock" 
    hour_image="clock_hour" minute_image="clock_minute" second_image="clock_second"/>
  <button name="close" x="center" y="bottom:10" w="25%" h="30" text="Close"/>
</window>
```

#### 1.35  tab_button_group控件

##### 1.35.1 属性

|  属性   |         说明         |  可选属性值  |
| :-----  | :------------------  | :----------  |
| compact | 是否紧凑型排版子控件 | true ; false |

##### 1.35.2 示例

```xml
 <window anim_hint="htranslate" theme="tab_bottom_compact">
  <pages x="c" y="20" w="90%" h="-60" value="1">
    <view w="100%" h="100%">
      <label x="c" y="m" w="100%" h="60" text="General" /> 
      <button name="close" x="c" y="bottom:100" w="80" h="40" text="Close" />
    </view>
    <view w="100%" h="100%">
      <label x="c" y="m" w="100%" h="60" text="Network" /> 
      <button name="close" x="c" y="bottom:100" w="80" h="40" text="Close" />
    </view>
    <view w="100%" h="100%">
      <label x="c" y="m" w="100%" h="60" text="Security" /> 
      <button name="close" x="c" y="bottom:100" w="80" h="40" text="Close" />
    </view>
  </pages>
  <tab_button_group x="c" y="bottom:10" w="90%" h="30" compact="true" >
    <tab_button text="General"/>
    <tab_button text="Network" value="true" />
    <tab_button text="Security"/>
  </tab_button_group>
</window>
```

#### 1.36 color相关控件

color相关控件包括：颜色选择器color_picker、 颜色分量color_component 、色块控件color_tile

##### 1.36.1 属性

1 color_picker属性

| 属性  | 说明 |
| :---  | :--  |
| value | 颜色 |

2 color_tile属性

|     属性     |   说明   |
| :----------  | :------  |
|   bg_color   | 背景颜色 |
| border_color | 边框颜色 |

##### 1.36.2 示例

```xml
<window>
  <color_picker x="0" y="0" w="100%" h="100%" value="orange">
   <color_component x="0" y="0" w="200" h="200" name="sv"/>
   <color_component x="210" y="0" w="20" h="200" name="h"/>
   <color_tile x="0" y="210" w="50%" h="20" name="new" bg_color="green"/>
   <color_tile x="right" y="210" w="50%" h="20" name="old" bg_color="blue"/>
   <edit x="0" y="240" w="50%" h="20" name="new" input_type="hex"/>
   <edit x="right" y="240" w="50%" h="20" name="old" readonly="true"/>
   <view x="0" y="270" w="100%" h="-240" layout="h20 c1 s2">
    <view >
     <label x="0" y="middle" w="30" h="100%" text="R"/>
     <spin_box x="40" y="middle" w="54" h="100%" min="0" input_type="int" max="255" step="1" auto_fix="true" name="r" />
     <slider x="98" y="middle" w="-100" h="100%" name="r" />
    </view>

    <view >
     <label x="0" y="middle" w="30" h="100%" text="G"/>
     <spin_box x="40" y="middle" w="54" h="100%" min="0" input_type="int" max="255" step="1" auto_fix="true" name="g" />
     <slider x="98" y="middle" w="-100" h="100%" name="g" />
    </view>

    <view >
     <label x="0" y="middle" w="30" h="100%" text="B"/>
     <spin_box x="40" y="middle" w="54" h="100%" min="0" input_type="int" max="255" step="1" auto_fix="true" name="b" />
     <slider x="98" y="middle" w="-100" h="100%" name="b" />
    </view>

    <view >
     <label x="0" y="middle" w="30" h="100%" text="H"/>
     <spin_box x="40" y="middle" w="54" h="100%" min="0" input_type="int" max="360" step="1" auto_fix="true" name="h" />
     <slider x="98" y="middle" w="-100" h="100%" name="h" />
    </view>

    <view >
     <label x="0" y="middle" w="30" h="100%" text="S"/>
     <spin_box x="40" y="middle" w="54" h="100%" min="0" input_type="int" max="100" step="1" auto_fix="true" name="s" />
     <slider x="98" y="middle" w="-100" h="100%" name="s" />
    </view>

    <view >
     <label x="0" y="middle" w="30" h="100%" text="V"/>
     <spin_box x="40" y="middle" w="54" h="100%" min="0" input_type="int" max="100" step="1" auto_fix="true" name="v" />
     <slider x="98" y="middle" w="-100" h="100%" name="v" />
    </view>
   </view>
  </color_picker>
  <button name="close" x="center" y="bottom:5" w="25%" h="30" text="Close"/>
</window>
```

