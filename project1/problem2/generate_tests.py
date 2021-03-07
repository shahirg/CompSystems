import random
if __name__ == "__main__":
    lines=input("Number of lines: ")
    negatives = 20
    neg_rate = int(lines/20)
    with open("test{}.txt".format(lines),'w+') as f:
        for i in range(lines):
            if (i+1)%neg_rate == 0:
                f.write("-10\n")
            else:
                f.write("{}\n".format(random.randint(1,100)))