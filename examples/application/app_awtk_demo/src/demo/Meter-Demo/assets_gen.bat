::---------------------------------------------------------------------------------------------------
::һ��˫���������⡢�ַ��������塢ͼƬ��UI�ȶ������ļ�(���е���assets_gen.py)                                   
::�����޸� AWTK_BIN_DIR=E:/zlgopen/awtk/bin Ϊ����awtk��Ӧ��binĿ¼	
::����%PY_VERSION% assets_gen.py %AWTK_BIN_DIR%  ./src/assets/raw ./src/assets/inc˵����
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

@set AWTK_BIN_DIR=E:/zlgopen/awtk/bin
@set PY_VERSION=python
@if exist %SystemRoot%\py.exe (
	@set PY_VERSION=py -2
)

%PY_VERSION% assets_gen.py %AWTK_BIN_DIR%  ./src/assets/raw ./src/assets/inc
%PY_VERSION% assets_c_gen.py ./src/assets
