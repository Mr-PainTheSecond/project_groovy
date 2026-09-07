import pygame
import pygame.mixer as mixer
import json

import const
from page import Page, Note, NotesTypes
from tkinter import filedialog
import sys



def drawBars(width, height):
    
    bars = []
    bars.append(pygame.Rect(0, 0, 25, height))
    bars.append(pygame.Rect((width * 0.25) - 12.5, 0, 25, height))
    bars.append(pygame.Rect((width * 0.5) - 12.5, 0, 25, height))
    bars.append(pygame.Rect((width * 0.75) - 12.5, 0, 25, height))
    bars.append(pygame.Rect(width - 25, 0, 25, height))
    
    color = pygame.Color(67, 70, 75)
    
    for bar in bars: 
                
        pygame.draw.rect(pygame.display.get_surface(), color, bar)


def createNotes(songObjs: list[Page], BPM):
    notes = pygame.sprite.Group()
    
    y_offset = const.HEIGHT / 8
    
    for obj in songObjs:
        y = y_offset - (obj.beat * y_offset)
        notesOnBeat = obj.notes
        
        noteWidth = 100
        noteHeight = 50
        
        if notesOnBeat["yellow"] != NotesTypes.NONE:
        
            notes.add(Note(const.WIDTH * 0.125, y, (255, 255, 0), BPM, noteWidth, noteHeight))
        if notesOnBeat["blue"] != NotesTypes.NONE:
                
            notes.add(Note(const.WIDTH * 0.375, y, (0, 0, 255), BPM, noteWidth, noteHeight))
        if notesOnBeat["green"] != NotesTypes.NONE:
                        
            notes.add(Note(const.WIDTH * 0.625, y, (0, 255, 0), BPM, noteWidth, noteHeight))
        if notesOnBeat["red"] != NotesTypes.NONE:
                        
            notes.add(Note(const.WIDTH * 0.875, y, (255, 0, 0), BPM, noteWidth, noteHeight))
    
    
    return notes

def offsetNotes(notes: pygame.sprite.Group, beat):
    y_offset = const.HEIGHT / 8
    for note in notes.sprites():
       # In game, song start with 4 beats of silence before playing mp3
       note.rect.y = note.baseY - (16 * y_offset)

   
if __name__ == "__main__":
    pygame.init()
    pygame.font.init()
    
    window = pygame.display.set_mode((const.WIDTH, const.HEIGHT))
    gameRunning = True
    
    fileName = filedialog.askopenfilename()
    jsonFile = None
    
    with open(fileName, "r") as file:
        contents = file.read()
        
        jsonFile = json.loads(contents)
    
    songData: list = jsonFile["Song"]
    songObjs: list[Page] = []
    
    beat = 0
    newMeasure = True
    firstNonEmpty = None
    beatsPerMin = jsonFile["BPM"]
    
    for note in songData:
        currentObj = None
        if newMeasure:
            currentObj = Page(beat, beatsPerMin)
            songObjs.append(currentObj)
        else:
            currentObj = songObjs[beat]
            
        newMeasure = currentObj.interpretNote(note)
        
        if newMeasure:
            beat += 1
        
        if not firstNonEmpty and len(note) != 0:
            firstNonEmpty = currentObj
            
    if firstNonEmpty:
        print(firstNonEmpty.notes)
        beat = firstNonEmpty.beat
    
        pageIndex = songObjs.index(firstNonEmpty)
    notes = createNotes(songObjs, beatsPerMin)
    # offsetNotes(notes, beat)
    
    font = pygame.font.Font("..\\content\\font\\georgia.TTF", 30)
    
    clock = pygame.time.Clock()
    songStarted = False
    mixer.music.load("..\\Content\\Songs\\MU_Billie.mp3")
    timeStamp = 15.0 / beatsPerMin * -16.0
    
    beatBars = pygame.sprite.Group()
    selectMode = False
    
    y_offset = const.HEIGHT / 8
    for i in range(0, len(songObjs), 4):
        barY = y_offset - (songObjs[i].beat * y_offset)
        beatBars.add(Note(0, barY, (128, 128, 128), beatsPerMin, const.WIDTH, 50))
    
    print(notes.sprites()[1].baseY - notes.sprites()[0].baseY)
    
    numKeys = [pygame.K_0, pygame.K_1, pygame.K_2, pygame.K_3, pygame.K_4, pygame.K_5, pygame.K_6, pygame.K_7, pygame.K_8, pygame.K_9]
    typedBeat = ""
    while gameRunning:
        for event in pygame.event.get():
            
            if event.type == pygame.QUIT:
                gameRunning = False
                
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    gameRunning = False
                if event.key == pygame.K_p and songStarted:
                    if not const.paused:
                        const.paused = True
                        mixer.music.pause()
                    else:
                        const.paused = False
                        mixer.music.unpause()
                if event.key == pygame.K_s:
                    print("here")
                    selectMode = True
                    mixer.music.pause()
                    const.paused = True
                if event.key == pygame.K_TAB and selectMode:
                    selectMode = False
                    mixer.music.unpause()
                if event.key in numKeys:
                    numTyped = numKeys.index(event.key)
                    typedBeat += str(numTyped)
                    print(typedBeat)
                    
        
        displayRect = pygame.rect.Rect(0, 0, window.get_width(), window.get_height())
        
        color = pygame.Color(83, 83, 83)
        
        pygame.draw.rect(pygame.display.get_surface(), color, displayRect)
        
        drawBars(const.WIDTH, const.HEIGHT)
        
        beatBars.update()
        notes.update()
        
        if selectMode:
            fontSurf = font.render("TYPE BEAT. TAB TO CANCEL. ENTER TO GO TO BEAT", False, (255, 255, 255))
            fontRect = fontSurf.get_rect(center = (const.WIDTH / 2, const.HEIGHT / 2))
            window.blit(fontSurf, fontRect)
        
        pygame.display.update()
        
        timeStamp += 1.0 / const.FRAME_RATE
        if not songStarted and timeStamp >= 0:
            songStarted = True
            pygame.mixer.music.play()
            
        clock.tick(const.FRAME_RATE)
        
            
            
    pygame.quit()
    pygame.font.quit()