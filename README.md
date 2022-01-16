# Vroom 0.1.0

2D/3D multiplatform graphics engine with signed distance fields. Still in development.
_________

-- 16 January 2022 Status Update --

There's a few things that need to be cleaned up. First is, targeting Metal is the only logical way to implement SDF-based rendering (both 2D and 3D). Metal allows a function to be passed to the shader stage, so we don't need to use up all the uniforms on the planet for a measly 500 SDF objects on an average device. All other graphics APIs - Vulkan, OpenGL, ... - don't include this capability, so it's going to be difficult to work cross platform. Though it is feasible with slower memory options (and hopefully function pointers or some analogous method in the future).
________
