import pytesseract 
from PIL import Image 

pytesseract.pytesseract.tesseract_cmd = r'D:\Variable\mamba\envs\forpy\Scripts\pytesseract.exe' 


img = Image.open("d:\Code\python\hhh.png") 
text = pytesseract.image_to_string(img,lang='chi_sim') 
print(text)