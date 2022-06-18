import block

# Technically, 14 since air block exists, however it does not have a corresponding texture in the texture atlas so just ignore it
TOTAL_BLOCKS = 13
ATLAS_HEIGHT = TOTAL_BLOCKS

def getTexCoords() -> list:
    coords = []
    for i in range(TOTAL_BLOCKS):
        coords.append(i / ATLAS_HEIGHT)
    return coords

coords = getTexCoords()

blocks = [
    block.Block(textureY = coords[0], alpha = 1.0, name = "Grass Block"), 
    block.Block(textureY = coords[1], alpha = 1.0, name = "Cobblestone Block"), 
    block.Block(textureY = coords[2], alpha = 1.0, name = "Dirt Block"), 
    block.Block(textureY = coords[3], alpha = 1.0, name = "Stone Block"), 
    block.Block(textureY = coords[4], alpha = 1.0, name = "Coal Ore Block"), 
    block.Block(textureY = coords[5], alpha = 1.0, name = "Iron Ore Block"), 
    block.Block(textureY = coords[6], alpha = 1.0, name = "Gold Ore Block"), 
    block.Block(textureY = coords[7], alpha = 1.0, name = "Redstone Ore Block"), 
    block.Block(textureY = coords[8], alpha = 1.0, name = "Diamond Ore Block"), 
    block.Block(textureY = coords[9], alpha = 1.0, name = "Emerald Ore Block"),
    block.Block(textureY = coords[10], alpha = 1.0, name = "Oak Wood Block"), 
    block.Block(textureY = coords[11], alpha = 1.0, name = "Leaf Block"), 
    block.Block(textureY = coords[12], alpha = 0.7, name = "Water Block")
]

firstLineAppended = ""
currentLinesAppended = ""
lastLinesAppended = ""
with open("./shaders/block/blockvertexshader.vert", "r") as shaderFile:
    lines = shaderFile.readlines()
    skip = False
    for line in lines:
        if "#version" in line:
            firstLineAppended += line
        elif "void main()" in line or skip:
            lastLinesAppended += line
            skip = True
        else:
            currentLinesAppended += line

with open("./shaders/block/blockvertexshader.vert", "w") as shaderOutFile:
    shaderOutFile.write(firstLineAppended)
    shaderOutFile.write(f"\n#define TOTAL_BLOCKS {TOTAL_BLOCKS}")
    shaderOutFile.write(currentLinesAppended)  
    shaderOutFile.write("const float[TOTAL_BLOCKS] textureCoordsY = {\n")
    for block in blocks:
        shaderOutFile.write(f"   {block.textureY}, // {block.name}\n")
    shaderOutFile.write("};\n")

    shaderOutFile.write("\nconst float[TOTAL_BLOCKS] blockOpacities = {\n")
    for block in blocks:
        shaderOutFile.write(f"   {block.alpha}, // {block.name}\n")
    shaderOutFile.write("};\n\n")  
    shaderOutFile.write(lastLinesAppended)

