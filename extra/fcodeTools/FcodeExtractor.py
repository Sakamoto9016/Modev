import re
from pathlib import Path

fl="raw.txt"
print("Modev™\nF-code Extractor",end="\n\n")
if Path(fl).exists() and Path(fl).is_file():
    print("Extracting",fl,end="...")
    with open(fl,"r",encoding="utf-8") as f:text=f.read()
    matches=re.findall(r'static\s+int\s+([A-Za-z_][A-Za-z0-9_]*)\s*\(\s*lua_State\s*\*\s*L\s*\)',text)
    print("Done.")
    print("Overwriting",fl,end="...")
    with open(fl,"w",encoding="utf-8") as f:f.write("\n".join(matches))
    print("Done.")
else:
    print("Are you actually want me to extract it or not? Where is",fl,"file?")
    print("Halt.")
