::---------------------------------------------------------------------------------------------------
::һ��˫���������⡢�ַ��������塢ͼƬ��UI�ȶ������ļ�(���е���assets_gen.py)                                   
::�����޸� AWTK_BIN_DIR=E:/zlgopen/awtk/bin Ϊ����awtk��Ӧ��binĿ¼
::����assets_gen.bat˵��
::	  1 Ϊ��(ʹ��800*480��Ļ)��
::		��assets_gen.bat
::	  2 -480_272(ʹ��480*272��Ļ):
::		��assets_gen.bat -480_272	
::�ġ�%PY_VERSION% assets_gen.py %AWTK_BIN_DIR%  ./src/assets/raw ./src/assets/inc˵����
::    1 Ϊ�գ�
::      ��assets_gen.py AWTK_BIN_DIR ./src/assets/raw ./src/assets/inc���������⡢�ַ��������塢ͼƬ��UI�ȶ������ļ�
::    2 -style 
::      ��assets_gen.py AWTK_BIN_DIR ./src/assets/raw ./src/assets/inc -style��  ��������
::    3 -string
::      ��assets_gen.py AWTK_BIN_DIR ./src/assets/raw ./src/assets/inc -string�� �����ַ���
::    4 -font
::      ��assets_gen.py AWTK_BIN_DIR ./src/assets/raw ./src/assets/inc -font��   ��������
::    5 -image
::      ��assets_gen.py AWTK_BIN_DIR ./src/assets/raw ./src/assets/inc -image��  ����ͼƬ
::    6 -ui
::      ��assets_gen.py AWTK_BIN_DIR ./src/assets/raw ./src/assets/inc -ui��     ����ui�ļ�
	
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
