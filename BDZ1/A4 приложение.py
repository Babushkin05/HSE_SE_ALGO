def alg1(A,n):
    c = 0
    ind = -1

    for i in range(n):
        c1 = 0
        for j in range(n):
            if A[i] == A[j]:
                c1 = c1 + 1
        if c1 > c:
            c = c1
            ind = i
    if c > n/2:
        return A[ind]

def alg2(A,n):
    times = {}
    for i in range(n):
        times[A[i]] = 0
    for i in range(n):
        times[A[i]] += 1
    most_popular = A[0]
    for i in times.keys():
        if times[i] > times[most_popular]:
            most_popular = i

    c = 1

    for i in range(n):
        if most_popular == A[i]:
            c = c + 1
        else:
            c = c - 1

    if c > 0:
        return most_popular

def alg3(A,n):
    if n == 1:
        return A[0]
    c = 1
    A.sort()
    for i in range(1,n):
        if A[i - 1] == A[i]:
            c = c + 1
        else:
            if c > n/2:
                return A[i - 1]
            else:
                c = 1

# первый не стал менять, остальные привел к его виду
def alg1new(A,n):
    c = 0
    ind = -1

    for i in range(n):
        c1 = 0
        for j in range(n):
            if A[i] == A[j]:
                c1 = c1 + 1
        if c1 > c:
            c = c1
            ind = i
    if c > n/2:
        return A[ind]

def alg2new(A,n):

    # Добавил эту часть чтобы изначально знать наипопулярнейший элемент
    times = {}
    for i in range(n):
        times[A[i]] = 0
    for i in range(n):
        times[A[i]] += 1
    most_popular = A[0]
    for i in times.keys():
        if times[i] > times[most_popular]:
            most_popular = i
    # -------------------------------------
    c = 1

    for i in range(n):
        if most_popular == A[i]: # поменял A[ind] на most_popular
            c = c + 1
        else:
            c = c - 1
        # убрал проверку с на 0 из цикла
    if c > 0: # поменял возврат функции
        return most_popular

def alg3new(A,n):
    if n == 1:
        return A[0]
    c = 1
    A.sort()
    for i in range(1,n):
        if A[i - 1] == A[i]:
            c = c + 1
        else:
            if c > n/2:
                return A[i - 1]
            else:
                c = 1
    if c > n/2:  # Добавил после цикла проверку условия,
        return A[i - 1] # чтобы не терять макс. элемент

m = [1,2,1,2,1,2,1]

print(alg1(m,len(m)),alg2(m,len(m)),alg3(m,len(m)))


