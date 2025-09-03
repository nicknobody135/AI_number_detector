import subprocess

cmd = (
    'gcc '
    'main.c '
    'game_setup\\game_setup.c '
    'load_images.c '
    'render_the_screen\\render_the_screen.c '
    'update_the_state_of_things\\mouse_updates\\update_mouse.c '
    'clock\\clock.c '
    'update_the_state_of_things\\update_the_state_of_things.c '
    'update_the_state_of_things\\button_management\\update_buttons.c '
    'drawing_management\\drawing_management.c '
    'file_management\\update_the_files.c '
    '-o main.exe '
    '-I"C:\\raylib\\raylib_desktop\\src" '
    'extras\\libraylib.a '
    '-lopengl32 -lgdi32 -lwinmm -static'
)
subprocess.run(cmd)
subprocess.run("main.exe")