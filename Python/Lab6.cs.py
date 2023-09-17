import os, subprocess, math, time, sys
path = "/home/stradiavanti/Workspaces/Shell Scripts/lab6/"
p1 = f"{path}{sys.argv[1]}"
p2 = f"{path}{sys.argv[2]}"
if subprocess.run(["test", "-f", p1]).returncode == 0:
    if int(subprocess.run(["stat", "-c", "%s", p1], encoding="utf-8", stdout=subprocess.PIPE).stdout) > 0:
        print(f"\nСортирую файл {p1}\n")
        subprocess.run(["sort", p1])
        with open(p2, "w") as outf:
            subprocess.run(["cat", p1], stdout=outf)
        print(f"\nФайл {p2}\n")
        subprocess.run(["cat", p2])
    else : print("Ошибка: Файл пуст.")
else : print("Ошибка: Файл несуществует.")


    


