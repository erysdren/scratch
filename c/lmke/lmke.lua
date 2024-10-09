#!/bin/lua -E

--[[
MIT License

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
*/
--]]

-- private configuration
local DEBUG = true
local RECIPE = "lmkefile.lua"

-- public configuration
CC = os.getenv("CC")
if not CC then CC = "cc" end
CXX = os.getenv("CXX")
if not CXX then CXX = "c++" end

-- state
local REQUESTED_TARGETS = {}
local DEFINITIONS = {}
local TARGETS = {}

-- set variable value
function set(key, value)
	DEFINITIONS[key] = value
end

-- unset variable value
function unset(key)
	DEFINITIONS[key] = nil
end

-- get variable value
function get(key)
	return DEFINITIONS[key]
end

-- split string by separator
local function split_string(str, sep)
	local t = {}
	for s in string.gmatch(str, "([^" .. sep .. "]+)") do
		table.insert(t, s)
	end
	return t
end

-- parse cli argument
local function parse_argument(argnum, argval)
	-- figure out if it's a definition or a target
	local is_def = 0
	for i = 1, #argval do
		if argval:sub(i, i) == "=" then
			if is_def ~= 0 then
				print("Error: argument " .. argnum .. " is malformed.")
				os.exit(1)
			end
			is_def = 1
			break
		end
	end

	if is_def ~= 0 then
		local split = split_string(argval, "=")
		if #split == 1 then
			print("Error: argument " .. argnum .. " is malformed.")
			os.exit(1)
		end
		set(split[1], split[2])
	else
		table.insert(REQUESTED_TARGETS, argval)
	end
end

-- add generic target
function add_target(target)
	if type(target) ~= "table" then
		print("Argument to add_target must be a table!")
		os.exit(1)
	end
	table.insert(TARGETS, target)
end

-- run build recipe
local function do_recipe(filename)
	print("Loading recipe \"" .. filename .. "\"\n")
	assert(loadfile(filename))()
	return true
end

-- setup base configuration
set("CC", os.getenv("CC") or "cc")
set("CXX", os.getenv("CXX") or "c++")
set("RM", os.getenv("RM") or "rm -f")

-- parse command line arguments
for i,v in ipairs(arg) do
	parse_argument(i, v)
end

-- do build recipe
if not do_recipe(RECIPE) then
	print("Error: Couldn't find \"" .. RECIPE .. "\" in current directory")
	os.exit(1)
end

-- talk to you
if DEBUG == true then
	local targets = ""
	for i,v in ipairs(TARGETS) do
		targets = targets .. "\t" .. v.name .. " (" .. v.type .. ")\n"
	end
	print("Targets:\n" .. targets)
	local defs = ""
	for k,v in pairs(DEFINITIONS) do
		defs = defs .. "\t" .. k .. "=" .. v .. "\n"
	end
	print("Definitions:\n" .. defs)
end

-- no targets specified, just exit with a warning
if #REQUESTED_TARGETS == 0 then
	print("Warning: No targets specified.")
	os.exit(0)
end
