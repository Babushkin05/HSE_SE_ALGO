p = 16 # меняемый размер массива
m = [0 for _ in range(p)]
for c1 in range(5):
    for c2 in range(5):
        for c3 in range(5):
            m = [0 for _ in range(p)]
            for i in range(100): # менять кол-во вставок в зависимости от p
                if((c1*i + c2*i*i + c3*i**3)%1!=0):
                    break
                m[(c1*i + c2*i*i + c3*i**3)%p] += 1
            if(all(x!=0 for x in m) and c3!=0):
                print(m,c1, c2, c3)