import serial
import time
import pygame
import speech_recognition as sr
import tkinter as tk
from tkinter import ttk
from serial.tools import list_ports

# Pygame initialization for sound
pygame.mixer.init()

# File paths for the sounds

celebrate_sound = r"C:\Users\Yash\Desktop\Humanoid Robot\CELEBRATION.mp3"
dance_sound = r"C:\Users\Yash\Desktop\Humanoid Robot\DANCE.mp3"
left_sound = r"C:\Users\Yash\Desktop\Humanoid Robot\LEFT.mp3"
right_sound = r"C:\Users\Yash\Desktop\Humanoid Robot\RIGHT.mp3"
reset_sound = r"C:\Users\Yash\Desktop\Humanoid Robot\RESETTING.mp3"
hello_sound = r"C:\Users\Yash\Desktop\Humanoid Robot\HELLO.mp3"
info_sound = r"C:\Users\Yash\Desktop\Humanoid Robot\INFO.mp3"
temp_sound = r"C:\Users\Yash\Desktop\Humanoid Robot\TEMP.mp3"
# Initialize the counter
name_counter = 0

# Sound files for different responses of name
name_sound = r"C:\Users\Yash\Desktop\Humanoid Robot\NAME.mp3"
name_sound_2 = r"C:\Users\Yash\Desktop\Humanoid Robot\name2.mp3"
name_sound_3 = r"C:\Users\Yash\Desktop\Humanoid Robot\name3.mp3"


# Speech recognizer setup
recognizer = sr.Recognizer()
recognizer.energy_threshold = 4000  # Adjust the energy threshold as needed

# Command synonyms for voice recognition
command_synonyms = {
    'happy': ['happy', 'joyful', 'smile'],
    'sad': ['sad', 'unhappy'],
    'angry': ['angry', 'mad', 'anger', 'annoyed'],
    'surprise': ['surprised', 'surprise', 'shock'],
    'turn left': ['turn left', 'left'],
    'turn right': ['turn right', 'right'],
    'reset': ['reset', 'default'],
    'hello': ['hello', 'greet', 'hi'],
    'what is your name': ['name','what is your name', 'who are you'],
    'celebrate': ['celebrate', 'party', 'ronaldo'],
    'dance': ['dance', 'groove', 'disco', 'hustle'],
    'info' : ['info', 'information', 'about', 'tell us about yourself'],
    'temp' : ['temp', 'temperature', 'weather', 'how hot is it'],
    'exit': ['exit', 'quit']
}

# Function to send commands to Arduino
def send_command(command):
    if 'ser' in globals():
        ser.write(command.encode())
    else:
        print("Serial port is not defined.")

# Voice recognition function
def recognize_command():
    with sr.Microphone() as source:
        print("Listening...")
        recognizer.adjust_for_ambient_noise(source)
        audio = recognizer.listen(source)

    try:
        print("Recognizing...")
        command = recognizer.recognize_google(audio).lower()
        print("You said:", command)
        return command

    except sr.UnknownValueError:
        print("Sorry, I didn't catch that. Please try again.")
        return None

    except sr.RequestError as e:
        print("Could not request results from Google Speech Recognition service; {0}".format(e))
        return None

# Command functions
def happy():
    send_command('happy')

def sad():
    send_command('sad')

def turn_left():
    send_command('turn left')
    pygame.mixer.music.load(left_sound)
    pygame.mixer.music.play()

def turn_right():
    send_command('turn right')
    pygame.mixer.music.load(right_sound)
    pygame.mixer.music.play()

def reset():
    send_command('reset')
    pygame.mixer.music.load(reset_sound)
    pygame.mixer.music.play()

def hello():
    send_command('hello')
    pygame.mixer.music.load(hello_sound)
    pygame.mixer.music.play()

def name():
    global name_counter
    send_command('name')

    # Increment the counter
    name_counter += 1

    # Play different sounds based on the counter value
    if name_counter == 1:
        pygame.mixer.music.load(name_sound)
    elif name_counter == 2:
        pygame.mixer.music.load(name_sound_2)
    elif name_counter == 3:
        pygame.mixer.music.load(name_sound_3)
    else:
        # Reset the counter after reaching a certain value
        name_counter = 0
        pygame.mixer.music.load(name_sound)  # Default sound when counter resets

    # Play the loaded sound
    pygame.mixer.music.play()


def ronaldo():
    send_command('ronaldo')
    time.sleep(1)
    pygame.mixer.music.load(celebrate_sound)
    pygame.mixer.music.play()

def dance():
    send_command('dance')
    pygame.mixer.music.load(dance_sound)
    pygame.mixer.music.play()

def surprise():
    send_command('surprise')

def angry():
    send_command('angry')

def info():
    send_command('info')
    pygame.mixer.music.load(info_sound)
    pygame.mixer.music.play()

def temp():
    send_command('temp')
    if 'ser' in globals() and ser is not None:
        adata = ser.readline().decode().strip()
        print(adata)
        try:
            temperature = float(adata)
            if temperature > 25.00:
                pygame.mixer.music.load(temp_sound)
                pygame.mixer.music.play()
        except ValueError:
            print("Invalid temperature reading.")
    else:
        print("Serial port is not defined or not properly initialized.")

def drawEqualizer():
    send_command('equalizer')

# Function to create the tkinter UI
def create_ui():
    global com_port_var, ser  # Declare com_port_var and ser as global
    
    root = tk.Tk()
    root.title("Robot Controller")

     # Create a frame to hold the COM port selection
    setup_frame = ttk.Frame(root, padding="10")
    setup_frame.grid(row=0, column=0, padx=10, pady=10, sticky="ew")

    # COM port selection
    com_port_label = ttk.Label(setup_frame, text="Select COM Port:")
    com_port_label.grid(row=0, column=0, padx=5, pady=5)

    com_ports = [port.device for port in list_ports.comports()]  # Get available COM ports
    com_port_var = tk.StringVar()
    if com_ports:
        com_port_var.set(com_ports[0])  # Default to the first available COM port
    else:
        print("No COM ports detected.")
    com_port_menu = ttk.OptionMenu(setup_frame, com_port_var, *com_ports)
    com_port_menu.grid(row=0, column=1, padx=5, pady=5)

    # Attempt to connect to the selected COM port
    try:
        ser = serial.Serial(com_port_var.get(), 9600)
        print(f"Connected to {com_port_var.get()}")
    except serial.SerialException:
        print("Failed to connect. Please check the COM port.")

        # Create a frame to hold the command buttons
    button_frame = ttk.Frame(root, padding="10")
    button_frame.grid(row=1, column=0, padx=10, pady=10, sticky="nsew")

    # Create buttons for each command
    commands = [
        ('Happy', happy),
        ('Sad', sad),
        ('Turn Left', turn_left),
        ('Turn Right', turn_right),
        ('Reset', reset),
        ('Hello', hello),
        ('Name', name),
        ('Celebrate', ronaldo),
        ('Dance', dance),
        ('Surprise', surprise),
        ('Angry', angry),
        ('Info', info),
        ('Temperature', temp),
        ('Exit', root.quit)
    ]

    # Create and grid buttons
    for i, (cmd_text, cmd_func) in enumerate(commands):
        button = ttk.Button(button_frame, text=cmd_text, command=cmd_func, width=15)
        button.grid(row=i//2, column=i%2, padx=5, pady=5)

    # Configure resizing behavior
    root.columnconfigure(0, weight=1)
    root.rowconfigure(0, weight=1)
    button_frame.columnconfigure((0, 1), weight=1)

    root.mainloop()


# Run the tkinter UI
if __name__ == "__main__":
    create_ui()

# Clean up pygame mixer and serial port
pygame.mixer.quit()
try:
    ser.close()
except NameError:
    pass  # Ignore if ser is not defined
