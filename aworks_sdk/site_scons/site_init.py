#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import subprocess
from subprocess import Popen,PIPE
import os
import re
import glob
import shutil
import tempfile
import time
import importlib
import fnmatch
import pdb
import inspect

# 获取当前路径
scons_common_dir = os.path.join(u'.',u'apollo',u'scons_common');

# 生成配置文件的builder
def configure_file_builder(target, source, env):
    if len(target) != 1 :
        raise ValueError("target must be only one");
    if len(source) < 3 :
        raise ValueError("source must be only three");

    user_config_py_file = str(source[2]);
    (user_config_py_file_dir,user_config_py_file_name) = os.path.split(user_config_py_file);
    (user_config_module_name,ext_name) = os.path.splitext(user_config_py_file_name)

    user_config_module = importlib.import_module( user_config_module_name );
    user_config_object = user_config_module.get_config_object();
    
    template_file_name = str(source[0]);
    def_config_file_name = str(source[1]);
    output_file_name = str(target[0]);

    configure_file(template_file_name,output_file_name,def_config_file_name,user_config_object);
    return None;

def tool_add_configure_file_builder(env):
    tool_merge_lib = Builder(action=configure_file_builder)
    env.Append(BUILDERS = {'configure_file' : tool_merge_lib})

def doxgen_build_function(target, source, env):
    cur_dir = os.getcwd();

    src_abs_path = os.path.abspath(str(source[0]))
    src_dir,src_name=os.path.split(src_abs_path)

    os.chdir(src_dir);
    os.system('doxygen '+  src_name);

    os.chdir(cur_dir);
    return None

def tool_add_doxygen(env):
    """A Tool to add a header from $HEADER to the source file"""
    tool_doxygen = Builder(action=doxgen_build_function)
    env.Append(BUILDERS = {'doxygen' : tool_doxygen})

    return None



def mergelib_function_keil(target, source, env):
    AR_CMD = 'arm-none-eabi-ar'
    CUR_DIR = os.getcwd()

    if len(target) != 1 :
        error_exit(u"target must be only one")
    target = str(target[0]);
    target = os.path.abspath(target);

    # 创建一个临时文件，用到ar -M 需要输入重定向
    fd, tmp_ar_name = tempfile.mkstemp()

    file = os.fdopen(fd, 'w+')
    file.write('create ' + target)

    print_auto_encoding('target: ' + target)
    for src in source :
        src_file_path = str(src);
        if os.path.isfile(src_file_path) :
            print_auto_encoding('add ' + src_file_path)
            file.write('\naddlib ' + src_file_path)

    file.write('\nsave')
    file.write('\nend')

    # 生成库
    ar_cmd_list = [AR_CMD, '-M']
    print ar_cmd_list

    file.seek(0)
    ps = subprocess.Popen(ar_cmd_list, stdin=file)
    ps.wait()
    if ps.returncode != 0:
        error_exit(target + ' failed')

    file.close()

    # 添加索引
    AR_CMD = env['AR']
    ar_cmd_list = AR_CMD + ' -s ' + target
    print ar_cmd_list
    ps = subprocess.Popen(ar_cmd_list)
    ps.wait()
    if ps.returncode != 0:
        error_exit(target + ' add indexes failed')

    while True:
        try:
            os.remove(tmp_ar_name)
            break;
        except :
            print_auto_encoding( u'error rm;')
            time.sleep(1)

    return None

def tool_add_merge_keil_lib(env):
    tool_merge_lib = Builder(action=mergelib_function_keil)
    env.Append(BUILDERS = {'merge_lib' : tool_merge_lib})


def mk_armcc_environment(build_common_config):
    env = DefaultEnvironment(
        tools = ['as','cc','cc','ar','link', tool_add_doxygen],
        ENV = {'PATH' : os.environ['PATH']},
        CC='armcc',
        AR='armar',
        RANLIB='armar',
        LIBPREFIX="",
        LIBSUFFIX=".lib",
        AS='armasm',
        CXX='armcc',    
        LINK='armlink',
        CFLAGS=build_common_config.AW_CFLAGS,
        ASFLAGS=build_common_config.AW_ASFLAGS ,
        ARFLAGS = '-r -c -s',
        RANLIBFLAGS = '-r -c -s',
        CXXFLAGS=build_common_config.AW_CXXFLAGS,
        CPPDEFINES=build_common_config.AW_CPPDEFINES,
        PROGSUFFIX='.axf',
        OBJSUFFIX = '.o')

    tool_add_merge_keil_lib(env);
    Export('env')
    return env;

if sys.version_info > (3,6):
    pass;
elif sys.version_info > (2,7) and sys.version_info < (3,0):
    pass;
else :
    print('unsupported python version');
    sys.out.flush();
    sys.exit(-1);
    pass;

def include_file(filename):
    file = open(filename,u'rb');
    str_lines = file.read();
    file.close();
    x = 1
    _locals = {};
    file_byte_code = compile(str_lines,filename,'exec');

    exec(file_byte_code,globals(),_locals);

    
    _globals = globals();
    while len(_locals) > 0:
        temp_item = _locals.popitem();
        if inspect.isfunction(temp_item[1] ) or inspect.ismodule(temp_item[1] ):
            _globals[temp_item[0] ] = temp_item[1];
    pass;

# 导入python3和python2兼容支持
include_file(os.path.join(scons_common_dir,u'python2_python3_port.py') )




# 导入通用工具包
include_file(os.path.join(scons_common_dir,u'build_aworks_common_tools.py') );
# 导入arm-non-eabi-gcc工具包
include_file(os.path.join(scons_common_dir,u'arm-none-eabi-gcc_tools.py') );

