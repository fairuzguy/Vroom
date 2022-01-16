# Vroom 0.1.0

2D/3D multiplatform graphics engine with signed distance fields. Still in development. 

There is a way to make this work on windows, but I've ommitted it for now to focus on Apple devices since they support function passes to shaders in Metal, which other graphics APIs don't have (yet). This is an important feature for SDFs, I can update the distance function every frame instead of letting the shader figure it out with a million switch statements. You can also build for Android and the web on a mac environment so it's really just windows being left out. So as of now, this repo only has the macOS dev environment to play around with.
_________

-- 16 January 2022 Status Update --

There's a few things that need to be cleaned up. First is, targeting Metal is the only logical way to implement SDF-based rendering (both 2D and 3D). Metal allows a function to be passed to the shader stage, so we don't need to use up all the uniforms on the planet for a measly 500 SDF objects on an average device. All other graphics APIs - Vulkan, OpenGL, ... - don't include this capability, so it's going to be difficult to work cross platform. Though it is feasible with slower memory options (and hopefully function pointers or some analogous method in the future).

Next is ensuring 2D works first, then building 3D on top of that (allows for viewports and such) and will probably allow for a texturing system to be extended to 3D surfaces at some point. 2D SDFs are tricky in that some parameters respect the aspect ratio. Some shapes like a box will work nicely, but a circle with a single radius for example will look like an ellipse if the window isn't square, unless we use aspect ratio constraints to calculate the "second" radius that is required at runtime. It needs care, especially with more complex shapes (especially those with parameters that don't respect x/y directions). Looks like it will be a fun time.
________
