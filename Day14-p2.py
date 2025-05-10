import re

in_file = "./Day14-input"

fp = open(in_file, "r")
mem_pat = re.compile(r"^mem\[(\d+)\] = (\d+)$")
memory = dict()

num_fbits = 0
mask = "goat"
for line in fp:
    if line.startswith("mask"):
        mask = line[7:]
        num_fbits = 2 ** mask.count("X")
        continue
    elif line.startswith("mem"):
        m = mem_pat.search(line)
        if m == None:
            print("fuck.")
            exit(1)
        raw_addr = list(format(int(m.group(1)), "036b"))
        val = int(m.group(2))
        for i in range(num_fbits):
            addr = raw_addr.copy()
            fbits = format(i, "036b")
            fbits_index = 0
            for index in range(36):
                match mask[index]:
                    case "1":
                        addr[index] = "1"
                    case "X":
                        addr[index] = fbits[35-fbits_index]
                        fbits_index += 1
            num_addr = int("".join(addr), 2)
            memory[num_addr] = val


fp.close()

print(sum([memory[x] for x in memory]))
