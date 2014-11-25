# Copyright 2008, Didier Bur,  tweaked by takesh h 2009
#
# Permission to use, copy, modify, and distribute this software for 
# any purpose and without fee is hereby granted, provided that the above
# copyright notice appear in all copies.
# 
# THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#----------------------------------------------------------------------------
# Name : Fast texture Writer
# Description : a tool to quickly extract textures from a SU model, to the current directory
# Menu Item : [Plugin] - [Export All Textures]  An entry to menu "Plugin" added by takesh h
# Modifications by bentleykf(niall.campbell@gmail.com)
# 	fast_tw : - modified to use write instead of write_all (used to capture namespace to update model material)
#   	        - modified to save to 'textures' folder
#    	       	- modified to eliminate illegal character file names
#		Menu Item : [Plugin] - [Export All Textures] - [Update Texture Paths] updates the path
#			of each texture in the model to its exported file
#		fast_tr : [Plugin] - [Export All Textures] - [Import All Textures] Replaces textures 
#			in model with namespace equivalents of textures from the chosen directory.
# Date : Feb. 12 2008 (tweak by takesh h: April. 17 2009) (mods by bentleykf(niall.campbell@gmail.com): January. 8 2011)
# (mods by julied20 (julie.djeffal@gmail.com): November 25 2014)
# Type : for developers only
#----------------------------------------------------------------------------
require 'sketchup.rb'

module FastTW

	def self.fast_tw(update_paths)
		# Create virtual face
		p1=Geom::Point3d.new(0,0,10000)
		p2=Geom::Point3d.new(1,0,10000)
		p3=Geom::Point3d.new(1,1,10000)
		p4=Geom::Point3d.new(0,1,10000)
		face=Sketchup.active_model.entities.add_face [p1,p2,p3,p4]
		tw = Sketchup.create_texture_writer
		fname_hash = Hash.new()
		
		#Modification by julied20
		#fdirname = File.dirname(Sketchup.active_model.path) + "/textures/"
		path = UI.select_directory(title: "Choose a directory to Export the Textures PD")
		fdirname = path + "/textures/"
		
		dir_exists = File.directory?(fdirname)
		
		if(!dir_exists)
			#Modification by julied20 
			#Dir.mkdir(fdirname, 755)
			Dir.mkdir(fdirname, 0755)
		end #if
		

		# Iterate through materials, assign to face, load in tw
		Sketchup.active_model.materials.each do |mat|
			if mat.texture
				texture = mat.texture
			# --- START --------------  check for filename conflicts
				filebase = File.basename(texture.filename)
				fileext  = File.extname(texture.filename)
				filename = filebase[0,filebase.length-fileext.length]
				illegal_char = Sketchup.is_valid_filename?(filename)
				
				if(illegal_char)
					filename = filename.delete('^A-Za-z0-9')
				end #if
				if(fname_hash[filename])
					i=0
					not_unique = true
					while not_unique
						i+=1
						if(!fname_hash[filename+(i.to_s)])
							filename = filename + (i.to_s)
							not_unique = false
						end #if
					end #while
				end #if
			# --- END ---------------- end check for filename conflicts
				fname_hash[filename] = filename #store filename to check conflicts
				
				
				
				face.material = mat
				tw.load face, true
				# should write texture here????
				filenbase = fdirname + filename + fileext
				filenbase = filenbase.to_s
				result = tw.write(face, true, filenbase)
				
			# --- START -------------- update material with path of written texture
				
				if update_paths
					theight = texture.height
					twidth  = texture.width
					mat.texture = filenbase
					mat.texture.size = [twidth,theight]
				end #if
				
			# --- END ---------------- end update material path
				
				#tw.load face, true
			end #if mat.texture
		end #each
		# Output textures
		# tw.write_all(File.dirname(Sketchup.active_model.path) + "/", false)
		# Delete virtual face
		edges=face.edges
		edges.each { |e| e.erase! if e.valid? }
	end	#def
	
	### fast_tr added by bentleykf(niall.campbell@gmail.com)
	def self.fast_tr
		entries_hash = Hash.new()
		
		dirpath = UI.openpanel("Choose A File Inside The Texture Import Folder", File.dirname(Sketchup.active_model.path), "*.jpg;*.png;*.psd;*.tif;*.tga;*.bmp")
		fdirname = File.dirname(dirpath)
		
		Dir.foreach(fdirname) { |filebase|
			fileext  = File.extname(filebase)
			filename = filebase[0,filebase.length-fileext.length]
			entries_hash[filename] = filename	+ fileext
		}
		
		Sketchup.active_model.materials.each do |mat|
			if mat.texture
				texture = mat.texture
				filebase = File.basename(texture.filename)
				fileext  = File.extname(texture.filename)
				filename = filebase[0,filebase.length-fileext.length]
				if (entries_hash[filename])
					theight = texture.height
					twidth  = texture.width
					#should copy texture back to textures folder??? just run fast_tw at end of file
					mat.texture = fdirname + "/" + entries_hash[filename]
					mat.texture.size = [twidth,theight]
				end #if
				
			end #if
		end #do

		FastTW.fast_tw(true)
		
		
	end #def
	
end #module

### menu added by takesh
if(not file_loaded?("fast_tw_4.rb"))

	Sketchup.write_default("Export All Textures","UTP",true) if Sketchup.read_default("Export All Textures","UTP","fail") == "fail"
	
	### submenu added by bentleykf(niall.campbell@gmail.com)
	submenu = UI.menu("Plugins").add_submenu("Export All Textures")
	submenu.add_item("Export All Textures") {FastTW.fast_tw(Sketchup.read_default("Export All Textures","UTP",true))}
	submenu.add_item("Import All Textures") {FastTW.fast_tr}
	
	submenu.add_separator
	
	cmd = UI::Command.new("Update Texture Paths") {
		update_paths = Sketchup.read_default("Export All Textures","UTP",true)
		if update_paths
			Sketchup.write_default("Export All Textures","UTP",false)
		else
			Sketchup.write_default("Export All Textures","UTP",true)
		end
	}
	
	cmd.set_validation_proc {
		Sketchup.read_default("UExport All Textures","UTP",true) ? MF_CHECKED : MF_UNCHECKED
	}
	
	submenu.add_item(cmd)
	
end

file_loaded("fast_tw_4.rb")
###