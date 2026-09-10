import re
from pathlib import Path

fl="raw.txt"
print("Modev™\nF-code Binder",end="\n\n")
if Path(fl).exists() and Path(fl).is_file():
    print("Binding",fl,end="...")
    with open("raw.txt","r",encoding="utf-8") as f:
        names=[line.strip() for line in f if line.strip()]
    print("Done.")
    print("Overwriting",fl,end="...")
    with open("raw.txt","w",encoding="utf-8") as f:
        for name in names:
            f.write(f'{{"{name}",Moon::func::{name}}},\n')
    print("Done.")
else:
    print("Are you actually want me to bind it or not? Where is",fl,"file?")
    print("Halt.")
