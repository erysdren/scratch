
-- imports
local br_actor = require("br_actor")

-- create world actor
local world = br_actor:new(nil, BR_ACTOR_NONE)
world.identifier = "World"

-- create camera actor
local camera = br_actor:new(world, BR_ACTOR_CAMERA)
camera.identifier = "Camera"
