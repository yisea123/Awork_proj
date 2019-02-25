#!/usr/bin/python

import os
import sys
import glob
import shutil
import copy

def joinPath(root, subdir):
  return os.path.normpath(os.path.join(root, subdir))


def writeToFile(file_name, str):
  fd = os.open(file_name, os.O_RDWR|os.O_CREAT|os.O_TRUNC)
  os.write(fd, str)
  os.close(fd)


def genIncludes(files, dir_name):
  str1 = ""
  for f in files:
    incf = copy.copy(f);
    incf=incf.replace(dir_name, "assets/inc");
    incf=incf.replace('\\', '/');
    str1 += '#include "'+incf+'"\n'

  return str1


def GetFileBaseName(file_name, root_dir_name, subdir_name, suffix):
  name = file_name.replace(root_dir_name, '');
  name = name.replace('\\', '/');
  name = name.replace('/' + subdir_name + '/', '');
  name = name.replace(suffix, '');
  return name;


def gen_assets_c(assets_dir, assets_c_path):
  assets_inc_dir = joinPath(assets_dir, 'inc')
  if not os.path.exists(assets_inc_dir) :
    print('assets inc dir not exist')
    exit()

  result = '#include "awtk.h"\n'
  result += '#include "base/assets_manager.h"\n'

  result += '#ifndef WITH_FS_RES\n'
  
  files=glob.glob(joinPath(assets_inc_dir, 'strings/*.data')) \
    + glob.glob(joinPath(assets_inc_dir, 'styles/*.data')) \
    + glob.glob(joinPath(assets_inc_dir, 'ui/*.data')) 
  result += genIncludes(files, assets_inc_dir);

  result += "#ifdef WITH_STB_IMAGE\n"
  files=glob.glob(joinPath(assets_inc_dir, 'images/*.res')) 
  result += genIncludes(files, assets_inc_dir)
  result += "#else\n"
  files=glob.glob(joinPath(assets_inc_dir, 'images/*.data')) 
  result += genIncludes(files, assets_inc_dir)
  result += '#endif/*WITH_STB_IMAGE*/\n'
  
  result += "#ifdef WITH_STB_FONT\n"
  result += "#ifdef WITH_MINI_FONT\n"
  files=glob.glob(joinPath(assets_inc_dir, 'fonts/default.mini.res')) 
  result += genIncludes(files, assets_inc_dir)
  result += "#else/*WITH_MINI_FONT*/\n"
  files=glob.glob(joinPath(assets_inc_dir, 'fonts/default.res')) 
  result += genIncludes(files, assets_inc_dir)
  result += '#endif/*WITH_MINI_FONT*/\n'
  result += "#else/*WITH_STB_FONT*/\n"
  files=glob.glob(joinPath(assets_inc_dir, 'fonts/*.data')) 
  result += genIncludes(files, assets_inc_dir)
  result += '#endif/*WITH_STB_FONT*/\n'

  result += '#endif/*WITH_FS_RES*/\n'

  result += '\n';
  result += 'ret_t assets_init(void) {\n'
  result += '  assets_manager_t* rm = assets_manager();\n\n'
  result += ''

  result += '#ifdef WITH_FS_RES\n'
  result += '#ifdef WITH_MINI_FONT\n'
  result += '  asset_info_t* info = assets_manager_load(rm, ASSET_TYPE_FONT, "default.mini");\n'
  result += '  if (info) {\n'
  result += '    strcpy(info->name, "default");\n'
  result += '  }\n'
  result += '#else \n'
  result += '  assets_manager_load(rm, ASSET_TYPE_FONT, "default");\n'
  result += '#endif\n'
  result += '  assets_manager_load(rm, ASSET_TYPE_STYLE, "default");\n'
  result += '#else\n'
  
  result += '#ifdef WITH_STB_FONT\n'
  files=glob.glob(joinPath(assets_inc_dir, 'fonts/*.res'))
  for f in files:
    if f.find('.mini.res') == -1:
      basename = GetFileBaseName(copy.copy(f), assets_inc_dir, 'fonts', '.res')
      result += '  assets_manager_add(rm, font_' + basename + ');\n'
  result += '#else\n'
  files=glob.glob(joinPath(assets_inc_dir, 'fonts/*.data'))
  for f in files:
    basename = GetFileBaseName(copy.copy(f), assets_inc_dir, 'fonts',  '.data')
    result += '  assets_manager_add(rm, font_' + basename + ');\n'
  result += '#endif\n'

  files=glob.glob(joinPath(assets_inc_dir, 'images/*.data'))
  for f in files:
    incf = copy.copy(f);
    basename = GetFileBaseName(copy.copy(f), assets_inc_dir, 'images',  '.data')
    result += '  assets_manager_add(rm, image_' + basename + ');\n'

  files=glob.glob(joinPath(assets_inc_dir, 'styles/*.data'))
  for f in files:
    incf = copy.copy(f);
    basename = GetFileBaseName(copy.copy(f), assets_inc_dir, 'styles',  '.data')
    result += '  assets_manager_add(rm, style_' + basename + ');\n'

  files=glob.glob(joinPath(assets_inc_dir, 'ui/*.data'))
  for f in files:
    incf = copy.copy(f);
    basename = GetFileBaseName(copy.copy(f), assets_inc_dir, 'ui', '.data')
    result += '  assets_manager_add(rm, ui_' + basename + ');\n'

  result += '#endif\n'

  result += '\n'
  result += '  tk_init_assets();\n'
  result += '  return RET_OK;\n'
  result += '}\n'
  writeToFile(assets_c_path, result);


def check_python_version():
	major_version = sys.version_info[0]
	if major_version > 2:
		print("The python version is %d.%d. But python2.x is required.(Version 2.7 is well tested!)" %(major_version, sys.version_info[1]))
		return True
	return False

if check_python_version():
		exit()

if len(sys.argv) <= 1 :
  print('assets_c_gen.py assets_dir')
  exit()

assets_dir = os.path.abspath(sys.argv[1])
assets_c_path = joinPath(assets_dir, '../assets.c')

gen_assets_c(assets_dir, assets_c_path)

