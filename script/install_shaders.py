import argparse
import os
import shutil
import sys

from collections import OrderedDict

class ShaderInfo(object):
	'''
	Creates a ShaderInfo object containing:
		path = The (source) path of the compiled shader.
		shaderName = The shader file.
	'''
	def __init__(self, path, name):
		self.path = path
		self.name = name

def _Extract(path):
	'''
	Get shader file name from end of file path
	'''
	return str(path).rsplit(os.sep, 1)[-1]

def _ExtractOSLShader(path):
	'''
	Create a ShaderInfo object
	'''
	shaderName = _Extract(path)
	return ShaderInfo(path, shaderName)

def _InstallFile(shaderInfo, destination, copy):
	'''
	Move or copy the compiled shader to the destination directory.
	'''
	flatFile = os.path.join(destination, shaderInfo.name)
	if copy:
		shutil.copyfile(shaderInfo.path, flatFile)
	else:
		shutil.move(shaderInfo.path, flatFile)

def _InstallShaders(shaderPaths, destination, copy):
	'''
	shaders: A set of compiled shaders.
	destination: The installation directory.
	'''
	shaderDict = OrderedDict()
	success = True

	for shaderPath in shaderPaths:
		if shaderPath.endswith(".oso"):
			shaderInfo = _ExtractOSLShader(shaderPath)
		else:
			print("ERROR: {} is not a .oso shader.".format(shaderPath))
			continue

		shaderName = shaderInfo.name
		# # # # # # # # # #
		# Check if shader is already installed
		if shaderName in shaderDict:
			print ("ERROR: {}'s shader name is the same as {}'s name: {}"
	  			.format(shaderPath, shaderDict[shaderName], shaderName))
			success = False
			continue

		shaderDict[shaderName] = shaderPath

		_InstallFile(shaderInfo, destination, copy)

	return success

def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--copy", default = False, action = "store_true", 
						help = "Copy the compiled shader to the destination "
							   "directory instead of moving it.")
	parser.add_argument("destination", help = "Destination directory")
	parser.add_argument("shaderPaths", nargs = "+", help = "Compiled shader paths from library")
	
	args = parser.parse_args()
	success = _InstallShaders(args.shaderPaths, args.destination, args.copy)

	return 0 if success else 1

if __name__ == "__main__":
	sys.exit(main())