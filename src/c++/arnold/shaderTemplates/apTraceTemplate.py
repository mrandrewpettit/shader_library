import pymel.core as pm
import mtoa.utils as utils
import mtoa.ui.ae.utils as eaUtils
from mtoa.ui.ae.shaderTemplate import ShaderAETemplate

class AEapTraceTemplate(ShaderAETemplate):
    
	def setup(self):
		# Add the shader swatch to the AE
		self.addSwatch()
		self.beginScrollLayout()

		# Add a list that allows to replace the shader for other one
		self.addCustom("message", "AEshaderTypeNew", "AEshaderTypeReplace")

		# Begins a "Color Section"
		self.beginLayout("Trace Parameters", collapse=False)
		# Add a control for the "constantColor" shader attribute
		self.addControl("position", label = "Position")
		self.addControl("direction", label = "Direction")
		self.addControl("opacity", label = "Opacity")
		self.addControl("selfTraceset", label = "Self Trace Set")
		self.addControl("breakEdge", label = "Break Edge")

		self.endLayout()

		# include/call base class/node attributes
		pm.mel.AEdependNodeTemplate(self.nodeName)

		# Add Section for the extra controls not displayed before
		self.addExtraControls()
		self.endScrollLayout()
