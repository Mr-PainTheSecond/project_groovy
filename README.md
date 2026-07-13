# ProjectGroovy

WIP rythm game made by Santiago Sanhueza

**How to Play**
In its current form, you will need Unreal Engine 5 (UE5) to play the game.
To download, follow the official Epic Games instructions [here](https://www.unrealengine.com/download)

You will then need to open the `ProjectGroovy.uproject` file and do the following:
- Click on File -> Open Level...
- In the `Content/Maps` directory, you will see a level titled `TestLevel`. This is where the test room is.
- Once the level has loaded, click on the play button and the game will begin to function.

*Aside*:
A few notes on usage, since the game is in a very early alpha stage. All the following should
not be an issue on later versions.
- The controls are DFGH, D being for the leftmost note and H at the rightmost note.
- Press P to pause the game
- The game does not register inputs until you are tabbed into the windows, but the notes
start moving right away. You get four measures of leeway before notes start apperaing. Make
sure to be tabbed in.
- Right now, after the game stops reading notes, the game does not end on its own. Press escape to leave
the game.


# Big Picture

The gamemode and character are repurposed from the First-Person default game mode, with movement, both in the world
and within the camera, being disabled, and the first person model that the player components uses being removed.
The Actor `BP_NotePad` controls most of the game. 

When created, it will create the measure bars and the notes themselves.
Notes can appear in every 1/4 beat, but they are not forced to. Measure bars will spawn unconditionally every beat to 
represent the start of a new measure. 

The supported notes length are: Sixteenth notes, Quarter Notes, Half Notes, and Whole Notes.

Throughout the game's development, I
will also treat Eigth notes and Sixteenth notes as the same.

Dotted notes are currently not supported, nor the combinations
of two notes into one. 

There are four unique music notes, which from the left to right are: *Yellow*: 0, *Blue*: 1, *Green* 2, *Red* 3. Whenever the game or this documentation refers to the notes are numbers, this is what they currespond to.  

# Spawning Actors
When the BeginPlay event is triggered on `BP_NotePad`, it will read out the `noteArray` from `BP_RhythmGameMode`, which contains
every note of the song. It will then use the actor's transform, a vector, and the variable `cubeOffsetScale` to determien the new location of the note. It will then rotate the new note to be the same as `BP_NotePad`. Every iterations decrements `cubeOffsetScale` by 25. Every iteration where `cubeOffsetScale` has decreased by 100 from the last creation of `BP_Beats` (the measure bar), a new instance of `BP_Beats`. 

`BP_NotePad` has a collision capsule at its front. When this collides with the player, it will create a new instance of `BP_NotePad` on top of the existing one (*note* this is still pretty rough lol).

Below the scene is an instance of `BP_DeletePad`. Whenever anything end of the moving components stop overlapping with it, it will delete the
actor.

# Note Creation
Whenever any note is created, which are `BP_PlayNote`, and `BP_QuaterNote` and all of its children, will read what note they are associated
with from the `noteArray`, which is a number from 0 to 3. This will determine the following:
- What Material Instance is used
- What keyboard input corresponds with it.
- The slight offset of position in notes.

# Actor Movement
The movement is determined by the following:
- A constant vector `baseMovement`, only have non-zero values in the `y-component`.
- The `BPM`. Song dependent, the higher the `BPM`, the faster objectes moves.
- Delta Seconds, so the movement speed is independent of frame rate.
- The actor's transformation.

# Intepreting Notes
Currently, song data is stored in `Content/Data/test_song.json`. This stores the `BPM` and the actual
song content. The song is stored in `Song` as an array. Each element in the array currensponds to a 1/4 beat.
This is what each entry represents:

"" means rest/no new note.

NM, where N is a note and M is a modifer.

N is any number between 0-3 representing the notes

M can be the following:
- *Nothing*, which means a sixteenth note.
- */*, which means it a quarter note.
- *?*, which means it is a half note.
- *L*, which means it a whole note.

When the game is initialized, `BP_RhythmGameMode` reads the JSON data and stores both the data in `Song` and on `BPM`.
Afterwards, `BP_NotePad` decides which note length to use and what type of music note it should be. 

# Reading Player Input*
Every note has an `active` attribute. This determines whether the note is currently playable.

Whenever a key is pressed, the program searches for the first note that the `active` attribute set to 
true, which should always be the one closest to the player.

The actor `BP_Notes` has a mesh which indicates where the player is aiming to click the notes. Slightly above the `BP_Notes`,
there are several hitboxes which determine how well the player has hit the note if the notes isn't perfectly colliding with `BP_Notes`.

With that in mind, here are the scenarios a note can go through:
- If the closest note is not colliding with `BP_Notes` or its surronding hitboxes, nothing will happen.
- If the closest note is collding with `BP_Notes`, `BP_GreatHitbox`, `BP_GoodHitbox`, or `BP_OkHitbox`, and the right key is pressed, points will be awarded and `active` is set to false.
- If the closest note is collding with `BP_Notes`, `BP_GreatHitbox`, `BP_GoodHitbox`, `BP_OkHitbox`, `BP_EarlyHitbox`, or `BP_LateHitbox` but the wrong key is pressed, no points will be awarded and `active` will be set to false.
- If the closest note is colliding with `BP_EarlyHitbox` or `BP_LateHitbox`, and the right key is pressed, no points will be awarded and `active` will be set to false.
- If the note end its collision with `BP_LateHitbox` while `active` is still true, no points will be awarded and `active` will be set to false.

*note: There isn't a point system right now, but there will be in the future* 

Every note that isn't a sixteenth note also has a few extra rules. On top of the hitbox determining the start of the notes, it has two intermediate hitboxes and one towards the end. The player is expected to hold the key they have played to continue playing the note
unti it ends. This is kept track of by the `beingPlayed` attribute. 

If the player lets go of the key before colliding with the hitbox towards the end, the note will be counted as ending early, and not
awards as many points.

If the `BP_Notes` collides with one of the intemediate hitboxes while `beingPlayed` is still true, the player will be awarded
with extra points.

Once the hitbox in the end enters the group that determines the scoring, it works the same way as pressing the buttons as described above,
except letting go of the wrong key is impossible and `beingPlayed` is set to false as opposed `active` (already set to false when the notes begins to play)
