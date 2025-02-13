"""

"""
def generate():
    from random import randint

    with open("data/test.txt", 'w', encoding="utf-8") as file:
        sum = 0
        for i in range(5000):
            a = randint(0, 10**8)
            sum += a
            file.write(str(a))
            file.write("\n")

    print(sum)