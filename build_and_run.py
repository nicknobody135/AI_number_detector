import subprocess

cmd = (
    'gcc '
    'C:\\Users\\Lenovo\\Desktop\\Coding\\c_and_cpp\\c\\medium_projects\\AI_number_detector\\main.c '
    'C:\\Users\\Lenovo\\Desktop\\Coding\\c_and_cpp\\c\\medium_projects\\AI_number_detector\\game_setup\\game_setup.c '
    'C:\\Users\\Lenovo\\Desktop\\Coding\\c_and_cpp\\c\\medium_projects\\AI_number_detector\\load_images.c '
    'C:\\Users\\Lenovo\\Desktop\\Coding\\c_and_cpp\\c\\medium_projects\\AI_number_detector\\render_the_screen\\render_the_screen.c '
    'C:\\Users\\Lenovo\\Desktop\\Coding\\c_and_cpp\\c\\medium_projects\\AI_number_detector\\update_the_state_of_things\\mouse_updates\\update_mouse.c '
    'C:\\Users\\Lenovo\\Desktop\\Coding\\c_and_cpp\\c\\medium_projects\\AI_number_detector\\clock\\clock.c '
    'C:\\Users\\Lenovo\\Desktop\\Coding\\c_and_cpp\\c\\medium_projects\\AI_number_detector\\update_the_state_of_things\\update_the_state_of_things.c '
    'C:\\Users\\Lenovo\\Desktop\\Coding\\c_and_cpp\\c\\medium_projects\\AI_number_detector\\update_the_state_of_things\\button_management\\update_buttons.c '
    'C:\\Users\\Lenovo\\Desktop\\Coding\\c_and_cpp\\c\\medium_projects\\AI_number_detector\\drawing_management\\drawing_management.c '
    '-o C:\\Users\\Lenovo\\Desktop\\Coding\\c_and_cpp\\c\\medium_projects\\AI_number_detector\\main.exe '
    '-I"C:\\raylib\\raylib_desktop\\src" '
    'C:\\raylib\\raylib\\src\\static\\libraylib.a '
    '-lopengl32 -lgdi32 -lwinmm -static'
)
subprocess.run(cmd)
subprocess.run("C:\\Users\\Lenovo\\Desktop\\Coding\\c_and_cpp\\c\\medium_projects\\AI_number_detector\\main.exe")
