def rwn(i,out):
    with open(i)as file:
        lines = file.readlines()
    with open(out,"w")as file:
        counter = 1
        for line in lines:
            file.write("/*"+ str(counter) +"*/ "+line)
            counter += 1
    return len(lines)

rwn("f.txt","new.txt")
