import numpy as np
from scanf import scanf


while True:
    ar = input("Vetor de cores: ")

    values = scanf("%d, %d, %d", ar)
    
    values = np.array(values)/255

    print(values)

