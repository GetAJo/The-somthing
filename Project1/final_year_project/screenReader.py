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
        f.write(', '.join(numbers) + "\n")

def clear_file(output_file):
    with open(output_file, 'w') as f:
        f.write("")

if __name__ == "__main__":
    # Check if correct number of arguments are provided
    if len(sys.argv) > 4:
        x1 = int(sys.argv[1])
        y1 = int(sys.argv[2])
        x2 = int(sys.argv[3])
        y2 = int(sys.argv[4])
        
        output_file = "output.txt"
        frame_duration = 1 / 5  # Set the frame duration

        # Clear the file at the start
        clear_file(output_file)
        
        try:
            while True:
                start_time = time.time()

                # Capture and extract numbers
                extracted_numbers = capture_screen(x1, y1, x2, y2)

                # Append extracted numbers to file
                append_text_to_file(output_file, extracted_numbers)

                # Calculate sleep duration to maintain frame rate
                elapsed_time = time.time() - start_time
                time_to_sleep = max(0, frame_duration - elapsed_time)
                time.sleep(time_to_sleep)

        except KeyboardInterrupt:
            print("Program terminated by user.")
            sys.exit(0)
    else:
        print("Please provide x1, y1, x2, and y2 as arguments.")
