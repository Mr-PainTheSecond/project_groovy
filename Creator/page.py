from enum import Enum
from const import *
import pygame

class NotesTypes(Enum):
    NONE = 0
    SIXTEENTH = 1
    QUARTER = 2
    HALF = 3
    FULL = 4


class Page:
    def __init__(self, beat):
        self.notes = {
            "yellow": NotesTypes.NONE,
            "blue": NotesTypes.NONE,
            "green": NotesTypes.NONE,
            "red": NotesTypes.NONE
        }
        
        self.counter = 0
        
        self.beat = beat
        
    def interpretNote(self, note):
        if len(note) == 0: return True
        
        noteType = ""
        
        if "0" in note:
            noteType = "yellow"
        elif "1" in note:
            noteType = "blue"
        elif "2" in note:
            noteType = "green"
        elif "3" in note:
            noteType = "red"
        else:
            raise Exception("Invalid note type found")
        
        self.counter += 1
        
        if len(note) == 1:
            self.notes[noteType] = NotesTypes.SIXTEENTH
            
            if self.counter >= 4:
                return True
        
        if "/" in note:
            self.notes[noteType] = NotesTypes.QUARTER
        elif "?" in note:
            self.notes[noteType] = NotesTypes.HALF
        elif "L" in note:
            self.notes[noteType] = NotesTypes.FULL
        else:
            self.notes[noteType] = NotesTypes.SIXTEENTH
        
        
        if self.counter >= 4 or ";" in note:
            return True
        else:
            return False

class Note(pygame.sprite.Sprite):
    def __init__(self, x, y, color):
        super().__init__()
        
        self.baseX = x
        self.baseY = y
        self.color = color
        
        self.rect = pygame.Rect(x, y, 100, 100)
        
    
    def onScreen(self):
        return self.rect.x > 0 and (self.rect.y + self.rect.h) > 0 and self.rect.x < WIDTH and (self.rect.y) < HEIGHT
    
    def update(self):
        self.rect.y += 1
        
        if (self.onScreen()):
            pygame.draw.rect(pygame.display.get_surface(), self.color, self.rect)
        
        