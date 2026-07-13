from PIL import Image
import sys


if __name__ == "__main__":
    src_file = ""
    if len(sys.argv) != 2:
        src_file = input("Please enter a source PNG file")
    else:
        src_file = sys.argv[1]
    
    reg_img = Image.open(src_file).convert("RGBA")
    
    old_pixel = reg_img.getdata()
    bw_pixels = []
    
    for r, g, b, a in old_pixel:
        if a != 0:
            bw_pixels.append((255, 255, 255, 255))
        else:
           bw_pixels.append((0, 0, 0, 0))
    
    bwImage = Image.new("RGBA", reg_img.size)
    bwImage.putdata(bw_pixels)
    bwImage.save(src_file.replace(".png", "") + "_white.png")   

