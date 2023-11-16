import os

def print_file_content(file_path):
    with open(file_path, 'r') as file:
        content = file.read()
        print(f"File Name: {os.path.relpath(file_path)}")
        print(f"Content:\n```\n{content}\n```\n")

def explore_folder(folder_path):
    for root, dirs, files in os.walk(folder_path):
        for file_name in files:
            file_path = os.path.join(root, file_name)
            print_file_content(file_path)

# Retrieving the current working directory
current_directory = os.getcwd()

# Prompting user for relative folder path
folder_path = input("Enter the relative folder path: ")

# Creating the absolute folder path by concatenating current directory and relative folder path
absolute_folder_path = os.path.join(current_directory, folder_path)

explore_folder(absolute_folder_path)

