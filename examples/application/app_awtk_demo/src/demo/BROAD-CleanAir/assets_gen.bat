::---------------------------------------------------------------------------------------------------
::一、双击生成主题、字符串、字体、图片、UI等二进制文件(其中调用assets_gen.py)                                   
::二、修改 AWTK_BIN_DIR=E:/zlgopen/awtk/bin 为本地awtk对应的bin目录
::三、assets_gen.bat说明
::	  1 为空(使用800*480屏幕)：
::		即assets_gen.bat
::	  2 -480_272(使用480*272屏幕):
::		即assets_gen.bat -480_272	
::四、%PY_VERSION% assets_gen.py %AWTK_BIN_DIR%  ./src/assets/raw ./src/assets/inc说明：
::    1 为空：
::      即assets_gen.py AWTK_BIN_DIR ./src/assets/raw ./src/assets/inc，生成主题、字符串、字体、图片、UI等二进制文件
::    2 -style 
::      即assets_gen.py AWTK_BIN_DIR ./src/assets/raw ./src/assets/inc -style，  生成主题
::    3 -string
::      即assets_gen.py AWTK_BIN_DIR ./src/assets/raw ./src/assets/inc -string， 生成字符串
::    4 -font
::      即assets_gen.py AWTK_BIN_DIR ./src/assets/raw ./src/assets/inc -font，   生成字体
::    5 -image
::      即assets_gen.py AWTK_BIN_DIR ./src/assets/raw ./src/assets/inc -image，  生成图片
::    6 -ui
::      即assets_gen.py AWTK_BIN_DIR ./src/assets/raw ./src/assets/inc -ui，     生成ui文件
	
::----------------------------------------------------------------------------------------------------
@set LCD="%1"
@if %LCD%=="-480_272" (
	@xcopy src\assets\raw_480_272\ui	 	src\assets\raw\ui 			/Y
	@xcopy src\assets\raw_480_272\styles 	src\assets\raw\styles 		/Y
	@xcopy src\assets\raw_480_272\images\x1 src\assets\raw\images\x1 	/Y
	@xcopy src\assets\raw_480_272\images\x2 src\assets\raw\images\x2 	/Y
	@xcopy src\assets\raw_480_272\images\x3 src\assets\raw\images\x3 	/Y
)

@set AWTK_BIN_DIR=E:/zlgopen/awtk/bin
@set PY_VERSION=python
@if exist %SystemRoot%\py.exe (
	@set PY_VERSION=py -2
)

%PY_VERSION% assets_gen.py %AWTK_BIN_DIR%  ./src/assets/raw ./src/assets/inc
%PY_VERSION% assets_c_gen.py ./src/assets
