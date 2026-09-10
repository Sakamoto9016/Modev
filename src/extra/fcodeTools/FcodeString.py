import re
from pathlib import Path

fl="raw.txt"
print("Modev™\nF-code String Reformatter",end="\n\n")
if Path(fl).exists() and Path(fl).is_file():
    print("Working",fl,end="...")
    with open(fl,"r",encoding="utf-8") as f:
        text=f.read()
    lines=[]
    for name,code in re.findall(r'\{"([^"]+)",\s*Moon::func::([A-Za-z0-9]+)\}',text):
        lines.append(f"[{code}]{name}")
    print("Done.")
    print("Overwriting",fl,end="...")
    with open("raw.txt","w",encoding="utf-8") as f:f.write("\n".join(lines)+"\n")
    print("Done.")
else:
    print("Hoe. Where is",fl,"file?")
    print("Halt.")


