import numpy as np
from scanf import scanf


while True:
    ar = input("Vetor de cores: ")

    values = scanf("%f, %f, %f", ar)
    
    values = np.array(values)/255

    print(values)

