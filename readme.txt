https://github.com/Yeannick/Programming4-Retake-Tron

Minigin :

GameObject class is final. Otherwise anything in the game can be considered a GameObject and could inherit from GameObject but this creates a giant mess in terms of structure.
we prefer Composition.

GameObject owns Components, Components each do 1 task and together form a working GamePlay.

the components do inherit from BaseComponent. This allows me to Create a single Vector of Components that the GameObject is responsible for

GameLoop has FixedUpdate ,which isnt much used in the game but every engine needs a Update for Physics and networking ,
Update standard , can update anything like Character Movement , Projectiles that dont follow the laws of physics , ...
LateUpdate , for when you want to be sure that all the GameObjects are Updated , also usefull for removing GameObjects who are marked for destroy.

and ofcourse Render to show something on screen.

SceneManager : changed to how Overlord engine handels Scenes , use of an ActiveScene that gets updated instead of all the Scenes at the same time.

SpriteComponent : can render a certain sprite from a spritesheet. Instead of rendering immediatly we push the info to a RenderQueue.
this is a sorted Queue that draws background elements first. this uses the Z axis (depth ).

BoxCollider2D : took inspiration from the Library Box2d. 
Is a Rectangular Collider used for hitdetection with the use of the PhysicsManager You can check whether  BoxColliders overlap
or if a Point is inside the rect. is a component

JsonFileReader : as seen in Tool Development , JSON is very handy for the notation of objects. It is Readable and easy to read in from. Uses RapidJson

SoundClip : uses SDL_MIXER , can play both SoundEffects and Music. only difference is in what Mix_... variable the sample is stored

soundclip loads , plays and pauses the sound.

SoundSystem : base class where both the nullSoundSystem and the SDLSoundsystem inherit from.

SDLSoundSystem : has a impl class that handles the Soundqueue.
SoundQueue works on a seperate thread 

Sound Service locator : A service locator to access the soundsystems Service without coupling myself to the class that implements it.

Observer and subject : i decided that everything could be an observer , GameObjects , Components , other systems.
the Notify system works with and enum class EventType where we can say what kind of event has happened and an EventArgs struct with can be inherit from (kind of the idea) to allow for extra information about the event to be passed with

UI : UI manager that handles UI element Button , looks for hits with the mouse and than calls the buttons OnUp or OnDown function

Tron :
GameManager to switch levels, is an Observer 
GameCommands has the 3 command for the actions : attack , rotate , and move

the rest of tron files are basically just components for movement , score , health  or Buttons for UI
