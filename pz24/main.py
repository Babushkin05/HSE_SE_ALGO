# example
# abacabadava
# z : [0, 0, 1, 0, 3, 0, 1, 0, 1, 0, 1]
# pref: [0, 0, 1, 0, 1, 2, 3, 0, 1, 0, 1]

def compute_z_function(s):
    n = len(s)
    zf = [0] * n
    zf[0] = n
    left, right = 0, 0
    for i in range(1, n):
        zf[i] = max(0, min(right - i, zf[left - i]))
        while i + zf[i] < n and s[zf[i]] == s[i + zf[i]]:
            zf[i]+=1
        if i + zf[i] > right:
            left = i
            right = i + zf[i]
    return zf

def compute_prefix_function(s):
    n = len(s)
    p = [0] * n
    for i in range(1, n):
        k = p[i - 1]
        while k > 0 and s[k] != s[i]:
            k = p[k - 1]
        if s[i] == s[k]:
            k += 1
        p[i] = k
    return p

def z_to_prefix(z):
    n = len(z)
    prefix = [0] * n
    for i in range(1, n):
        for j in range(z[i] - 1, -1, -1):
            if prefix[i + j] == 0:
                prefix[i + j] = j + 1
            else:
                break
    return prefix

def prefix_to_z(pi):
    n = len(pi)
    s = ""
    next = 'a'
    for i in range(n):
        if pi[i] == 0:
            s += next
            next = chr(ord(next) + 1)
        else:
            s += s[pi[i] - 1]
    return compute_z_function(s)

str1 = "abacabadava"
str2 = "vovavov"
str3 = "babubabush"

data = [str1, str2, str3]

for test in data:
    print(f"{test} pref : {compute_prefix_function(test)}")
    print(f"{test} z : {compute_z_function(test)}")

    print(f"pref \t\t\t z_to_pref(z)\n{compute_prefix_function(test)} {z_to_prefix(compute_z_function(test))}")
    print(f"z \t\t\t pref_to_z(pref)\n{compute_z_function(test)} {prefix_to_z(compute_prefix_function(test))}\n")