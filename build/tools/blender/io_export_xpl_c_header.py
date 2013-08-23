bl_info = {
	"name": "Export XPL C Header (.h)",
	"author": "Jeff LaMarche and Justin Bowes",
	"version": (1, 0),
	"blender": (2, 5, 7),
	"api": 35622,
	"location": "File > Export",
	"description": "Export Model to XPL C Header file",
	"warning": "",
	"wiki_url": "",
	"tracker_url": "",
	"category": "Import-Export"}

'''
Usage Notes:


'''

import bpy
from bpy.props import *
import mathutils, math, struct
import os
from os import remove
import time
import bpy_extras
from bpy_extras.io_utils import ExportHelper 
import time
import shutil
import bpy
import mathutils

def triangulateNMesh(object):
	bneedtri = False
	scene = bpy.context.scene
	bpy.ops.object.mode_set(mode='OBJECT')
	for i in scene.objects: i.select = False #deselect all objects
	object.select = True
	scene.objects.active = object #set the mesh object to current
	print("Checking mesh if needs to convert quad to Tri...")
	object.data.update(calc_tessface=True)
	for face in object.data.tessfaces:
		if (len(face.vertices) > 3):
			bneedtri = True
			break
	
	bpy.ops.object.mode_set(mode='OBJECT')
	if bneedtri == True:
		print("Converting quad to tri mesh...")
		me_da = object.data.copy() #copy data
		me_ob = object.copy() #copy object
		#note two copy two types else it will use the current data or mesh
		me_ob.data = me_da
		bpy.context.scene.objects.link(me_ob)#link the object to the scene #current object location
		for i in scene.objects: i.select = False #deselect all objects
		me_ob.select = True
		scene.objects.active = me_ob #set the mesh object to current
		bpy.ops.object.mode_set(mode='EDIT') #Operators
		bpy.ops.mesh.select_all(action='SELECT')#select all the face/vertex/edge
		bpy.ops.mesh.quads_convert_to_tris() #Operators
		bpy.context.scene.update()
		bpy.ops.object.mode_set(mode='OBJECT') # set it in object
		print("Triangulate Mesh Done!")
		print("Remove Merge tmp Mesh [ " ,object.name, " ] from scene!" )
		bpy.ops.object.mode_set(mode='OBJECT') # set it in object
		bpy.context.scene.objects.unlink(object)
	else:
		print("No need to convert tri mesh.")
		me_ob = object
	return me_ob


def writeString(file, string):
	file.write(bytes(string, 'UTF-8'))
	
def do_export(context, props, filepath):
	mat_x90 = mathutils.Matrix.Rotation(-math.pi/2, 4, 'X')
	ob = context.active_object
	me_ob = triangulateNMesh(ob)
	current_scene = context.scene	
	apply_modifiers = props.apply_modifiers

	mesh = me_ob.to_mesh(current_scene, apply_modifiers, 'PREVIEW')
	
	basename = mesh.name.capitalize()
	
	if props.world_space:
		mesh.transform(ob.matrix_world)

	if props.rot_x90:
		mesh.transform(mat_x90)
		
	mesh.calc_normals()

	file = open(filepath, "wb") 
	theHeader = '\n\
/*************************************************************** \n\
	XPL format model \n\
	Blender export of %s\n\
****************************************************************/ \n\
\n\
#include "k2_model.h"\n\
\n' % basename
	writeString(file, theHeader)

	if len(mesh.uv_textures) > 0:
		writeString(file, '\n\
#ifndef K2_MODEL_H_\n\
typedef struct vertex_normal_uv {\n\
	xvec3		vertex;\n\
	xvec3		normal;\n\
	xvec2		uv;\n\
} vertex_normal_uv_t;\n\
#endif\n')
		writeString(file, '\n\
static const vertex_normal_uv_t %s_vertex_data[] = {\n' % basename)
		#for face in uv: #loop through the faces
		uv_layer = mesh.tessface_uv_textures.active
		for face in mesh.tessfaces:
			faceUV = uv_layer.data[face.index]
			i=0
			for index in face.vertices:
				if len(face.vertices) == 3:
					vert = mesh.vertices[index]
					writeString(file, '\t{ /*v*/ {{%f, %f, %f}}, ' % (vert.co.x, vert.co.y, vert.co.z) )
					writeString(file, '\t/*n*/ {{%f, %f, %f}}, ' % (vert.normal.x, vert.normal.y, vert.normal.z))
					writeString(file, '\t/*t*/ {{%f, %f}}' % ( faceUV.uv[i][0], faceUV.uv[i][1] ) )
					writeString(file, '},\n')
					i+=1
		writeString(file, '};\n\n')
	elif len(mesh.vertex_colors) > 0:
		writeString(file, '\n\
#ifndef K2_MODEL_H_\n\
typedef struct vertex_normal_color {\n\
	xvec3		vertex;\n\
	xvec3		normal;\n\
	xvec4		color;\n\
} vertex_normal_color_t;\n\
#endif\n')
		writeString(file, '\n\
static const vertex_normal_color_t %s_vertex_data[] = {\n' % basename)
		color_layer = mesh.tessface_vertex_colors.active
		for face in mesh.tessfaces:
			if len(face.vertices) == 3:
				faceC = color_layer.data[face.index]
				i=0
				vcolors = [faceC.color1, faceC.color2, faceC.color3, faceC.color4]
				for index in face.vertices:
					vert = mesh.vertices[index]
					writeString(file, '\t{ /*v*/ {{%f, %f, %f}}, ' % (vert.co.x, vert.co.y, vert.co.z) )
					writeString(file, '\t/*n*/ {{%f, %f, %f}}, ' % (vert.normal.x, vert.normal.y, vert.normal.z))
					writeString(file, '\t/*c*/ {{%f, %f, %f, %f}}' % ( vcolors[i][0], vcolors[i][1], vcolors[i][2], props.vertex_alpha) )
					writeString(file, '},\n')
					i+=1
		writeString(file, '};\n\n')
	else:
		writeString(file, '\n\
#ifndef K2_MODEL_H_\n\
typedef struct vertex_normal {\n\
	xvec3		vertex;\n\
	xvec3		normal;\n\
} vertex_normal_t;\n\
#endif\n')
		writeString(file, 'static const vertex_normal_t %s_vertex_data[] = {\n' % basename)
		for face in mesh.tessfaces:
			if len(face.vertices) == 3:
				for index in face.vertices:
					vert = mesh.vertices[index]
					writeString(file, '\t{ /*v*/ {{%f, %f, %f}}, ' % (vert.co.x, vert.co.y, vert.co.z) )
					writeString(file, '\t/*n*/ {{%f, %f, %f}} ' % (vert.normal.x, vert.normal.y, vert.normal.z))
					writeString(file, '},\n')
		writeString(file, '};\n\n')
		
	file.flush()
	file.close()

	return True


###### EXPORT OPERATOR #######
class Export_objc(bpy.types.Operator, ExportHelper):
	'''Exports the active Object as an  XPL C Header File.'''
	bl_idname = "export_object.c"
	bl_label = "Export XPL C Header (.h)"

	filename_ext = ".h"
	
	apply_modifiers = BoolProperty(name="Apply Modifiers",
							description="Applies the Modifiers",
							default=True)

	rot_x90 = BoolProperty(name="Convert to Y-up",
							description="Rotate 90 degrees around X to convert to y-up",
							default=True)
	
	world_space = BoolProperty(name="Export into Worldspace",
							description="Transform the Vertex coordinates into Worldspace",
							default=False)
							
							
	vertex_alpha = FloatProperty(name="Vertex Color Alpha",
							description="Uniform alpha for vertex colors (not set by painting)",
							default=1.0)

	
	@classmethod
	def poll(cls, context):
		return context.active_object.type in ['MESH', 'CURVE', 'SURFACE', 'FONT']

	def execute(self, context):
		start_time = time.time()
		print('\n_____START_____')
		props = self.properties
		filepath = self.filepath
		filepath = bpy.path.ensure_ext(filepath, self.filename_ext)

		exported = do_export(context, props, filepath)
		
		if exported:
			print('finished export in %s seconds' %((time.time() - start_time)))
			print(filepath)
			
		return {'FINISHED'}

	def invoke(self, context, event):
		wm = context.window_manager

		if True:
			# File selector
			wm.fileselect_add(self) # will run self.execute()
			return {'RUNNING_MODAL'}
		elif True:
			# search the enum
			wm.invoke_search_popup(self)
			return {'RUNNING_MODAL'}
		elif False:
			# Redo popup
			return wm.invoke_props_popup(self, event) #
		elif False:
			return self.execute(context)


### REGISTER ###

def menu_func(self, context):
	self.layout.operator(Export_objc.bl_idname, text="XPL C Header (.h)")

def register():
	bpy.utils.register_module(__name__)

	bpy.types.INFO_MT_file_export.append(menu_func)

def unregister():
	bpy.utils.unregister_module(__name__)

	bpy.types.INFO_MT_file_export.remove(menu_func)

if __name__ == "__main__":
	register()
