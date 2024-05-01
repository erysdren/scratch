--[[
Copyright (c) 2024 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
]]

-- actor.h
BR_ACTOR_NONE = 0
BR_ACTOR_MODEL = 1
BR_ACTOR_LIGHT = 2
BR_ACTOR_CAMERA = 3
_BR_ACTOR_RESERVED = 4
BR_ACTOR_BOUNDS = 5
BR_ACTOR_BOUNDS_CORRECT = 6
BR_ACTOR_CLIP_PLANE = 7
BR_ACTOR_HORIZON_PLANE = 8
BR_ACTOR_MAX = 9

-- actor.h
BR_RSTYLE_DEFAULT = 0
BR_RSTYLE_NONE = 1
BR_RSTYLE_POINTS = 2
BR_RSTYLE_EDGES = 3
BR_RSTYLE_FACES = 4
BR_RSTYLE_BOUNDING_POINTS = 5
BR_RSTYLE_BOUNDING_EDGES = 6
BR_RSTYLE_BOUNDING_FACES = 7
BR_RSTYLE_ANTIALIASED_LINES = 8
BR_RSTYLE_ANTIALIASED_FACES = 9
BR_RSTYLE_MAX = 10

-- setup metatable
local br_actor = {}
br_actor.__index = br_actor

-- v1db_p.h
-- BrActorAdd(br_actor *parent, br_actor *a);
function br_actor:addChild(child)
	table.insert(self.children, child)
end

-- v1db_p.h
-- BrActorRemove(br_actor *a);
function br_actor:removeChild(child)
	self.children[child] = nil
end

-- v1db_p.h
-- BrActorSearch(br_actor *root, char *pattern);
function br_actor:findChildren(pattern)
	local children = {}
	local num_children = 0
	for key,value in pairs(self.children) do
		if string.find(value.identifier, pattern) ~= nil then
			table.insert(children, value)
			num_children = num_children + 1
		end
	end
	if num_children == 0 then
		return nil
	else
		return children
	end
end

-- v1db_p.h
-- BrActorAllocate(br_uint_8 actor_type, void *type_data);
function br_actor:new(actor_parent, actor_type)
	-- setup self
	local self = setmetatable({}, br_actor)
	-- add default values
	self.parent = actor_parent or nil
	self.type = actor_type or BR_ACTOR_NONE
	self.children = {}
	self.model = nil
	self.material = nil
	self.identifier = ""
	self.render_style = BR_RSTYLE_DEFAULT
	-- self.__ptr = BrActorAllocate(actor_type)
	-- check parent type
	if self.parent ~= nil then
		if type(self.parent) ~= "br_actor" then
			error("Parent type is not br_actor!")
		else
			self.parent:addChild(self)
		end
	end
	-- return self
	return self
end

-- v1db_p.h
-- BrActorFree(br_actor *a);
function br_actor:__gc()
	-- BrActorFree(self.__ptr)
end

-- wrap type function
local original_type = type
type = function(o)
	local otype = original_type(o)
	if otype == "table" and getmetatable(o) == br_actor then
		return "br_actor"
	end
	return otype
end

-- return metatable
return br_actor
