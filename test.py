import os, sys

def generate(file_name, m, n):
    from random import randint

    digits = []  # arreglo que se escribirá en el archivo

    # Generar primer número
    num1 = [randint(1, 9)]  # primer dígito ≠ 0
    for _ in range(m - 1):
        num1.append(randint(0, 9))

    # Generar segundo número
    num2 = [randint(1, 9)]  # primer dígito ≠ 0
    for _ in range(n - 1):
        num2.append(randint(0, 9))

    # Armar la estructura que pide el archivo
    digits.append(m)
    digits.extend(num1)
    digits.append(n)
    digits.extend(num2)

    print(f'Arreglo generado para archivo: {digits}')
    print(f'Número 1: {"".join(map(str, num1))}')
    print(f'Número 2: {"".join(map(str, num2))}')

    # Guardar en archivo
    with open(file_name, "w") as f:
        for d in digits:
            f.write(f'{d}\n')

    # Retornar tupla de listas
    return num1, num2


m = int(sys.argv[1])
n = int(sys.argv[2])
k = int(sys.argv[3])

num1, num2 = generate(file_name="temp.txt", m = m, n = n)
num1 = int("".join(map(str, num1)))
num2 = int("".join(map(str, num2)))

os.system("clear")


print("Numero 1:", num1)
print("Numero 2:", num2)
print(f"Resultado esperado: {num1 * num2}")
print('-' * 10)

os.system("gcc main.c -o temp")
os.system(f"./temp {k} -T -V < temp.txt")

print('-' * 10)

os.system('rm temp temp.txt')