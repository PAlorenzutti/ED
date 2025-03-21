
import os
from glob import glob


input_files = list(sorted(glob("in/in*.txt", recursive=True)))

for in_file in input_files:
    out_file = in_file.replace("in", "out")
    err_file = in_file.replace("in", "err")

    cmd = f"valgrind ./../main < {in_file} > {out_file} 2> {err_file}"

    print(cmd)
    os.system(cmd)
    print("------------------")
