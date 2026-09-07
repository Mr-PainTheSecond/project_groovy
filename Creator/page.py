from enum import Enum
import const
import pygame

class NotesTypes(Enum):
    NONE = 0
    SIXTEENTH = 1
    QUARTER = 2
    HALF = 3
    FULL = 4


class Page:
    def __init__(self, beat, BPM):
        self.notes = {
            "yellow": NotesTypes.NONE,
            "blue": NotesTypes.NONE,
            "green": NotesTypes.NONE,
            "red": NotesTypes.NONE
        }
        
        self.counter = 0
        
        self.beat = beat
        
        # If notes move at one BPM, it would take 15 seconds to go from note A to note B
        # Since first 16 notes are filler, we subtract 16 from beat
        self.timeStamp = (15 / BPM) * (beat - 16)
        
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
    def __init__(self, x, y, color, BPM, w, h):
        super().__init__()
        
        baseMovement = float(const.HEIGHT * 0.545) / 60.0 / float(const.FRAME_RATE)
        self.speed = baseMovement * BPM
        
        self.baseX = x
        self.baseY = y
        
        self.currentX = x
        self.currentY = y
        self.color = color
        
        self.rect = pygame.Rect(x, float(y), w, h)
        
    
    def onScreen(self):
        return (self.currentX + self.rect.w) > 0 and (self.currentY + self.rect.h) > 0 and self.currentX < const.WIDTH and (self.currentY) < const.HEIGHT
    
    def update(self):
        if not const.paused:
            self.currentY += self.speed
        
        if (self.onScreen()):
            self.rect = pygame.Rect(self.currentX, self.currentY, self.rect.w, self.rect.h)
            pygame.draw.rect(pygame.display.get_surface(), self.color, self.rect)
        
