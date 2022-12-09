### Cetroleopter Engine

![logo_motor](https://user-images.githubusercontent.com/73583005/199374861-d922d9cb-46e2-48f1-bbcb-1b8dc3789e2c.png)

 #Our first game engine... ( ͡° ͜ʖ ͡°)

Cetroleopter Engine its a 3D graphics Engine for Game Development developped with C++ developped by Álvaro Milla & Alexandre Carreras.

### Engine Features:

## UI:

-**File**: where you can save and load the configuration (and the scene), and also can exit the engine (I don't know why you would do that, taking in account how great our engine is 
( ͡° ͜ʖ ͡°))

-**Edit**: here you can hide and show the settings window and the console window. The settings window has window settings, FPS setings and harware specifics. The console window just reads the console and print it. You can also load preselected fbx files with their respective Textures.

-**Create**: this option offers a varietty of primitives to load into our the engine such as a cube or a cone.

-**View**: this tab may be one of the most interesting ones. It displays diferent options to see our loaded object in the scene. Wireframe, Disable Textures, Cull Faces, Disable lights and disable Ambien Oclusion. 

-**Help**: this window let you clic a link to this amazing engine, and also open an About window that shows you the license of this project, the libraries used and a link to our github page.

-**GameObjects**: this window shows the objects in a tree, and lets you click a button to see the specifics of the objects in the inspector.(make a doble click on the arrow)

-**Inspector**: this window show the specifics of the object that we are looking at. Currenty there is Texture, Mesh and Transform components of an object are available, camera could be perfectly added

## Drag&Drop Feature:

Models and textures can be dropped directly into the engine, a new game object per mesh in the model and the texture will also be applied into that model. Cetroleopter Engine supports .fbx for the objects and dds/.png for the textures, there are not more formats in our plan, but we would be glad to add some :-)

## Scene Serialization

Everything is setted up to work, nothing crashes  while saving it or loading it, but it only saves the scene name :-/

## Transformation & Hierarchy features:

We added this recently, it was a pain but it is functional! 
Hierarchy is another story. All the features of a transform component are implemented to support local to world position, supporting the children of an object. But we had problems with ImGui and we cannot modify the hierarchy ;_-(
(Transform is currently an experimental feature)

## Play & Stop features:

Everything implemented but does not work, we found out that once an ImGui window has several ImGui components inside the last ones added cease to work, this is the case.

## Camera Features:

# Camera Component
Camera is a component used by the main engine camera and also attached as a local component to game objects.

# Mouse picking
It allows to click an object and select it for edditing it by making a raycast between the mouse pointer direction proyection and the object's bounding box.
(Mouse picking is currently an experimental feature)

## Resource Management features:

We have a chunk of the ressource management features, as showing the assets in a window and generating the library files.

## Custom File Format

Models, meshes and textures are saved to your own format under Library folder, the .FcVg Franccesco Virgolini file, the fastest file of the whole world.

## Can also load complex maya fbx

![1](https://user-images.githubusercontent.com/73582929/206307942-84bfe4bd-dfe3-4a29-b0dc-34e138f8929c.png)

![2](https://user-images.githubusercontent.com/73582929/206307981-5213742c-b7de-422f-bf6d-10eef25e3c8b.png)

## Experimental Features list:

Those are features wich have been fully implemented but wich for unknown reasons work in a very buggy way (some more than others).

- Mesh transformations
- Mouse picking

## Engine Controls:

- **W**: Move Forward

- **A**: Move Left

- **S**: Move Backwards

- **D**: Move Right

- **ALTL + Mouse Left Click**: Changes the Rotation of the Camera

- **Mouse Wheel Forward**: Camera Zoom Forward

- **Mouse Wheel Backward**: Camera Zoom Backwards

- **Shift while mooving**: speeds up the movement of the camera

## Developers:

- Álvaro Milla:
  - Github Account: [mrmille](https://github.com/mrmile)

- Alexandre Carreras:
  - Github Account: [TheGewehr](https://github.com/TheGewehr)
  
## Official Github Page:

https://thegewehr.github.io/Cetroleopter-Engine/
