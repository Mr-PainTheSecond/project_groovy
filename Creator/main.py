import pygame
import json
from const import *
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


def createNotes(songObjs: list[Page],):
    notes = pygame.sprite.Group()
    
    y_offset = HEIGHT / 8
    
    for obj in songObjs:
        y = y_offset - (obj.beat * y_offset)
        notesOnBeat = obj.notes
        
        if notesOnBeat["yellow"] != NotesTypes.NONE:
        
            notes.add(Note(WIDTH * 0.125, y, (255, 255, 0)))
        if notesOnBeat["blue"] != NotesTypes.NONE:
                
            notes.add(Note(WIDTH * 0.375, y, (0, 0, 255)))
        if notesOnBeat["green"] != NotesTypes.NONE:
                        
            notes.add(Note(WIDTH * 0.625, y, (0, 255, 0)))
        if notesOnBeat["red"] != NotesTypes.NONE:
                        
            notes.add(Note(WIDTH * 0.875, y, (255, 0, 0)))
    
    
    return notes

def offsetNotes(notes: pygame.sprite.Group, beat):
    y_offset = HEIGHT / 8
    for note in notes.sprites():
       note.rect.y = note.baseY - (beat * y_offset)
       print(note.rect.y)
    
if __name__ == "__main__":
    pygame.init()
    
    
    window = pygame.display.set_mode((WIDTH, HEIGHT))
    gameRunning = True
    
    fileName = filedialog.askopenfilename()
    jsonFile = None
    
    with open(fileName, "r") as file:
        contents = file.read()
        
        jsonFile = json.loads(contents)
    
    songData: list = jsonFile["Song"]
    songObjs = []
    
    beat = 0
    newMeasure = True
    firstNonEmpty = None
    
    for note in songData:
        currentObj = None
        if newMeasure:
            currentObj = Page(beat)
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
    notes = createNotes(songObjs)
    offsetNotes(notes, beat)
    
    while gameRunning:
        for event in pygame.event.get():
            
            if event.type == pygame.QUIT:
                gameRunning = False
        
        displayRect = pygame.rect.Rect(0, 0, window.get_width(), window.get_height())
        
        color = pygame.Color(83, 83, 83)
        
        pygame.draw.rect(pygame.display.get_surface(), color, displayRect)
        
        drawBars(WIDTH, HEIGHT)
        
        notes.update()
        pygame.display.update()