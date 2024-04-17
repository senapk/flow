#!/bin/python3

import os

lines = open("src/source.hpp").read().split("\n")

output = []
size = len(lines)

print("loading guides into flow.hpp")

for line in lines:
    if line.startswith("//LOAD_GUIDE"):
        label = line.split(" ")[1]
        print("  " + label)
        path = "guides/" + label + ".hpp"
        if not os.path.isfile(path):
            print(f"guide {label} not found")
            exit(1)
        content = open(path).read()
        while content[-1] == "\n":
            content = content[:-1]
        output.append(content)
    else:
        output.append(line)

with open("flow.hpp", "w") as f:
    f.write("\n".join(output) + "\n")


