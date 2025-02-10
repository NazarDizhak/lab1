with open("data/test.txt" ,'r', encoding="utf-8") as file:
    print(sum([len(a.strip()) for a in file.readlines()]))