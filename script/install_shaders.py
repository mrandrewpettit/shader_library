import argparse
import os
import shutil
import sys

from collections import OrderedDict

class ShaderInfo(object):
	'''
	Creates a ShaderInfo object containing:
		pathname = The (source) path name of the compiled shader.
		flatname = The flattened name of the compiled shader file.
	'''
	def __init__(self, pathname, flatname):
		self.pathname = pathname
		self.flatname = flatname

def _Flatten(pathname):
	'''
	Replace directory path separators with '_'
		data/FooBar.oso -> data_FooBar.oso
	'''
	return str(pathname).replace(os.sep, '_')

def _FlattenOSLShader(pathname):
	'''
	Create a ShaderInfo object
	'''
	flatname = _Flatten(pathname)
	return ShaderInfo(pathname, flatname)

def _InstallFile(shader_info, destination, copy):
	'''
	Move or copy the compiled shader to the destination directory.
	'''
	flatFile = os.path.join(destination, shader_info.flatname)
	if copy:
		shutil.copyfile(shader_info.pathname, flatFile)
	else:
		shutil.move(shader_info.pathname, flatFile)

def InstallShaders(shaders, destination, copy):
	'''
	shaders: A set of compiled shaders.
	destination: The installation directory.
	'''
	shader_dict = OrderedDict()
	success = True

	for shader in shaders:
		if shader.endswith(".oso"):
			shader_info = _FlattenOSLShader(shader)
		else:
			print("ERROR: {} is not a .oso shader.".format(shader))
			continue

		flatname = shader_info.flatname

		# Check if shader is already installed
		if flatname in shader_dict:
			print ("ERROR: {}'s flattened name is the same as {}'s name: {}"
	  			.format(shader, shader_dict[flatname], flatname))
			success = False
			continue

		shader_dict[flatname] = shader

		_InstallFile(shader_info, destination, copy)

	return success

def _main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--copy", default = False, action = "store_true", 
						help = "Copy the compiled shader to the destination "
							   "directory instead of moving it.")
	parser.add_argument("destination", help = "Destination directory")
	parser.add_argument("shaders", nargs = "+", help = "Compiled shaders")
	
	args = parser.parse_args()
	success = InstallShaders(args.shaders, args.destination, args.copy)

	return 0 if success else 1

if __name__ == "__main__":
	sys.exit(_main())