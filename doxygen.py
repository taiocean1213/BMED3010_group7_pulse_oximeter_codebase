Import("env", "projenv")

def generate_doxygen(source, target, env):
    import subprocess
    subprocess.run("doxygen")

env.AddPostAction("$BUILD_DIR/${PROGNAME}.elf", generate_doxygen)