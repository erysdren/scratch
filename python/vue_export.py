#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# based on the following spec:
# https://help.autodesk.com/view/3DSMAX/2024/ENU/?guid=GUID-BEADCF00-3BBA-4722-9D7D-C07C15F8A33B
# (if this link dies, contact erysdren for a local copy)

# imports
import os, sys, struct
import bpy, bmesh
from bpy_extras.io_utils import ExportHelper, ImportHelper
from bpy.props import StringProperty, BoolProperty, IntProperty
from math import degrees

# bl_info
bl_info = {
	"name": "3D Studio VUE format",
	"author": "erysdren (it/she/they)",
	"version": (1, 0, 0),
	"blender": (4, 5, 0),
	"location": "File > Export",
	"description": "3D Studio VUE format export",
	"warning": "",
	"doc_url": "https://erysdren.me/",
	"support": "COMMUNITY",
	"category": "Export",
}

#
# register, unregister, etc
#

def menu_func_export(self, context):
	self.layout.operator(Export3DStudioVUE.bl_idname, text="3D Studio VUE (.vue)")

def register():
	bpy.utils.register_class(Export3DStudioVUE)
	bpy.types.TOPBAR_MT_file_export.append(menu_func_export)

def unregister():
	bpy.utils.unregister_class(Export3DStudioVUE)
	bpy.types.TOPBAR_MT_file_export.remove(menu_func_export)

if __name__ == "__main__":
	register()

#
# main export class
#

class Export3DStudioVUE(bpy.types.Operator, ExportHelper):
	"""Export a 3D Studio VUE (.vue) File"""
	bl_idname = "export.3ds_vue"
	bl_label = "Export 3D Studio VUE (.vue) "

	filename_ext = ".vue"
	filter_glob : StringProperty(default="*.vue", options={"HIDDEN"})
	only_selected : BoolProperty(name="Only Selected", description="Only write the objects that are currently selected", default=False)
	write_version : BoolProperty(name="Version", description="Write version identifier at the top of the file", default=True)
	version_number : IntProperty(name="Version", description="Version number to write", default=201)
	first_frame : IntProperty(name="First Frame", description="First frame to write", default=1)
	last_frame : IntProperty(name="Last Frame", description="Last frame to write", default=250)
	write_whole_animation : BoolProperty(name="Write Whole Animation", description="Write the whole scene's animation", default=False)
	write_cameras : BoolProperty(name="Cameras", description="Export camera views", default=False)
	write_lights : BoolProperty(name="Lights", description="Export lights", default=False)

	def execute(self, context):
		f = open(self.properties.filepath, "w")
		if self.properties.write_version:
			f.write(f"VERSION {self.properties.version_number}\n\n")
		start = context.scene.frame_start if self.properties.write_whole_animation else self.properties.first_frame
		end = context.scene.frame_end + 1 if self.properties.write_whole_animation else self.properties.last_frame + 1
		for frame in range(start, end):
			f.write(f"frame {frame}\n")
			context.scene.frame_set(frame)
			objects = context.selected_objects if self.properties.only_selected else context.scene.objects
			for o in objects:
				if o.type == "CAMERA":
					if self.properties.write_cameras:
						loc = o.matrix_world.to_translation()
						ang = o.matrix_world.to_euler("XYZ")
						right, up, back = o.matrix_world.to_3x3().transposed()
						forward = -back
						to = loc + forward
						# camera <x> <y> <z> <tox> <toy> <toz> <roll> <focal>
						f.write(f"camera {loc[0]} {loc[1]} {loc[2]} {to[0]} {to[1]} {to[2]} {ang[2]} {o.data.lens}\n")
				elif o.type == "LIGHT":
					if self.properties.write_lights:
						loc = o.matrix_world.to_translation()
						col = o.data.color
						if o.data.type == "POINT":
							# light <light name> <x> <y> <z> <r> <g> <b>
							f.write(f"light \"{o.name}\" {loc[0]} {loc[1]} {loc[2]} {col[0]} {col[1]} {col[2]}\n")
						elif o.data.type == "SPOT":
							right, up, back = o.matrix_world.to_3x3().transposed()
							forward = -back
							to = loc + forward
							falloff = degrees(o.data.spot_size)
							hot = falloff - (falloff * o.data.spot_blend) % 360 # ?? not sure this is right
							shadow = 1 if o.data.use_shadow else 0
							# spotlight <light name> <x> <y> <z> <tox> <toy> <toz> <r> <g> <b> <hot angle> <falloff angle> <shadow flag>
							f.write(f"spotlight \"{o.name}\" {loc[0]} {loc[1]} {loc[2]} {to[0]} {to[1]} {to[2]} {col[0]} {col[1]} {col[2]} {hot} {falloff} {shadow}\n")
				elif o.type == "MESH":
					m = o.matrix_world.to_3x3()
					t = o.matrix_world.to_translation()
					# transform <object name> <transform matrix>
					f.write(f"transform \"{o.name}\"")
					for i in range(3):
						for j in range(3):
							f.write(f" {m[i][j]}")
					f.write(f" {t[0]} {t[1]} {t[2]}")
					f.write("\n")
			f.write("\n")
		f.close()
		return {"FINISHED"}
