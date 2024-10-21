import pyautogui
from PIL import Image
import pytesseract
import time
import re
import sys

def capture_screen(x1, y1, x2, y2):

    width = x2 - x1
    height = y2 - y1
    screenshot = pyautogui.screenshot(region=(x1, y1, width, height))

    text = pytesseract.image_to_string(screenshot)

    numbers = re.findall(r'\d+', text) 

    return numbers

def append_text_to_file(output_file, numbers):
    with open(output_file, 'a') as f:
        f.write("\nExtracted numbers from screen:\n")
        f.write(', '.join(numbers)) 

def clear_file(output_file):
    with open(output_file, 'w') as f:
        f.write("") 

x1, y1 = 100, 100 
x2, y2 = 400, 300  
output_file = "output.txt"

clear_file(output_file)

frame_duration = 1 / 5  

try:
    while True:
        start_time = time.time()  
        if (KeyboardInterrupt == True):
            print("Program terminated by user.")
            sys.exit(0)  

        extracted_numbers = capture_screen(x1, y1, x2, y2)

        append_text_to_file(output_file, extracted_numbers)

        elapsed_time = time.time() - start_time

        time_to_sleep = max(0, frame_duration - elapsed_time)
        time.sleep(time_to_sleep)

except KeyboardInterrupt:
    print("Program terminated by user.")
    sys.exit(0)
